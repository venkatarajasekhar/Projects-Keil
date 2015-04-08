//============================================================
//
// File Name    : 'Keys.c'
// Project      :
// Title        :
// Author       : ������� �.�.
// Created      : 25/02/2014
// Revised      :
// Version      : 1
// Target MCU   : STM32F407
// Compiler     : Keil 4.71.2.0
// Editor Tabs  : 2
//
// NOTE:
//============================================================

//============================================================
//	������ ���������� ������
//============================================================
#include "stm32f4xx.h"
#include "Keys.h"

uint8_t PinKey[ C_NUM_KEYS ] = 
{
	8,
	12,
};

GPIO_TypeDef *PortKey[ C_NUM_KEYS ] = 
{
	GPIOD, 
	GPIOE,
};




volatile uint8_t	CounterKey[C_NUM_KEYS];
volatile uint8_t  KeyStatus = 0;
volatile uint8_t  KeyStatusOld = 0;


//============================================================
//��� �������:	HandlerKeys
//��������:			��������� ������
//����. ��������: 
//���.  ��������: ����� ������� �� �������
//============================================================
uint8_t	HandlerKeys (void)
{
volatile	uint8_t	i;
volatile	uint8_t  WordKeyEvent = 0;
	
	//----------------------------------
  for ( i = 0; i < C_NUM_KEYS; i++ )
	{
		if ((KeyStatus & ((uint8_t)1<<i)) == 0) 
		{
			CounterKey[i] = (!(PortKey[ i ]->IDR &  (1 << PinKey[ i ]))) ? CounterKey[i]+1 : 0;
			
			if (CounterKey[i] >= C_MAX_NUM_VALUES)  
			{
				CounterKey[i] = 0;
				KeyStatus |= ((uint8_t)1<<i);			// ��������� ������
			}
		}
		else
		{
			CounterKey[i] = (PortKey[ i ]->IDR & (1 << PinKey[ i ])) ? CounterKey[i]+1 : 0;
			
			if (CounterKey[i] >= C_MAX_NUM_VALUES)  
			{
				CounterKey[i] = 0;
				KeyStatus &= ~((uint8_t)1<<i);			// ��������� �����.
			}
		}
	}

	for ( i = 0; i < C_NUM_KEYS; i++ )
	{
			if ( (KeyStatus ^ KeyStatusOld) & (1<<i) )
			{
				if ( KeyStatus & (1<<i) )
				{// ��������� �������
					WordKeyEvent |= (1<<i);
				}
// 				else
// 				{// ��������� ����������
// 					 WordKeyEvent = i;
// 				}
			}
	}

	KeyStatusOld = KeyStatus;

	return 	WordKeyEvent;
}


//**************************************************************
//��� ������: 	CheckKey
//��������: 		������������ �������� ������, �����. ������
//����. ��������: �����
//���. ��������: 	1- ������,  0- ��������
//**************************************************************
uint8_t	CheckKey  ( uint8_t  num_key )
{
	if ( KeyStatus & (1 << num_key) ) {
		return 1;
	}
	else {
		return 0;
	}
}

