//============================================================
//
// File Name    : 'SystemInit.c'
// Project      :  FOC
// Title        :
// Author       : Федорин А.К.
// Created      : 10/04/2015
// Revised      :
// Version      : 1
// Target MCU   : STM32F4XX
// Compiler     : Keil 5.10.0.2
// Editor Tabs  : 2
//
// NOTE:
//============================================================

#include "spi.h"
#include "Keys.h"
#include "InitPin.h"
#include "USART.h"

#include "Config.h"
#include "stm32f4xx_gpio.h"
#include "Zettlex.h"
#include "PID.h"

//-------------------------------------------------------------
#define	TICK_BLINKY		500
int32_t Counter = TICK_BLINKY;

uint8_t	StateCalib = 0;


/**
  * @brief  This function get pointer to structure FOC_t
  * @param  None
  * @retval poiter
  */
FOC_t* 	GetPointToFunctionFOC(void)
{
  return &pADDRESS[0];
}

/**
  * @brief  SystemInitialize
  * @param  None
  * @retval None
  */
void SystemInitialize(void)
{
	SystemCoreClockUpdate();
	
	InitPin();
	InitSPI();
		__enable_irq();	
	InitUART();
	ZettlexInitUART();
	InitPID();
		delay_(200);

}
extern DataZettlex_t Zettlex;
/**
  * @brief  Blinky
  * @param  None
  * @retval None
  */
void Blinky(void)
{
	State_t	StateMotor;
  State_t StateM1;
	FlafsZettlex_t StateZettlex = GetZettlexFlags();
	uint16_t State = 0;
	
	HandlerKeys();

	if (Counter-- <= 0)
	{
		Counter = TICK_BLINKY;
		
		if (DRV8301() || CheckKey(DRIVER_OCTV) || CheckKey(DRIVER_FAULT) || (StateZettlex.NoAnswer == 1))
		{
			GPIO_SetBits(GPIOE, GPIO_Pin_10);
		}
		else
		{
			if (!GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_10))
				GPIO_SetBits(GPIOE, GPIO_Pin_10);
			else
				GPIO_ResetBits(GPIOE, GPIO_Pin_10);
		}		
	}
}



