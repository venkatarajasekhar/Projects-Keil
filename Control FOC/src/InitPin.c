//============================================================
//
// File Name    : 'InitPin.c'
// Project      :  Универсальный контроллер
// Title        :
// Author       : Федорин А.К.
// Created      : 13/03/2015
// Revised      :
// Version      : 1
// Target MCU   : STM32F4XX
// Compiler     : Keil 5.10.0.2
// Editor Tabs  : 2
//
// NOTE:
//============================================================

//============================================================
//	Секция включаемых файлов
//============================================================
#include "stm32f4xx.h"
#include "Keys.h"
#include "stm32f4xx_gpio.h"

extern uint8_t PinKey[ C_NUM_KEYS ];
extern GPIO_TypeDef *PortKey[ C_NUM_KEYS ];

void InitPin(void)
{
	uint8_t	i;
	GPIO_InitTypeDef GPIO_InitStruct;	
	

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
	
	for(i = 0; i < C_NUM_KEYS; i++)
	{
		GPIO_InitStruct.GPIO_Pin   = 1 << PinKey[ i ];
		GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;
		GPIO_Init(PortKey[i], &GPIO_InitStruct);			
	}
	
	// LED
  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_10;
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE, &GPIO_InitStruct);
	GPIO_SetBits(GPIOE, GPIO_Pin_10);
	
	//EN_GATE	
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_15;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_SetBits(GPIOA, GPIO_Pin_15);
	
	//DC_CAL
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_10;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_ResetBits(GPIOB, GPIO_Pin_10);	
	

	// Pull-up Hall sensors
	GPIOH->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << ((uint16_t)10 * 2));
	GPIOH->PUPDR |= (((uint32_t)GPIO_PuPd_UP) << (10 * 2));
	GPIOH->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << ((uint16_t)11 * 2));
	GPIOH->PUPDR |= (((uint32_t)GPIO_PuPd_UP) << (11 * 2));
	GPIOH->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << ((uint16_t)12 * 2));
	GPIOH->PUPDR |= (((uint32_t)GPIO_PuPd_UP) << (12 * 2));	
	
}




