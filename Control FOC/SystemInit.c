

#include "spi.h"
#include "Keys.h"
#include "InitPin.h"
#include "USART.h"

#include "Config.h"
#include "stm32f4xx_gpio.h"


//**************************************************************
/**
  * @brief  This function get pointer to structure FOC_t
  * @param  None
  * @retval poiter
  */
FOC_t* 	GetPointToFunctionFOC(void)
{
  return &pADDRESS[0];
}



void SystemInitialize(void)
{
	SystemCoreClockUpdate();
	
	InitPin();
	InitSPI();
	//InitUART();
	delay_(200);
	
}


#define	TICK_BLINKY		500
int32_t Counter = TICK_BLINKY;

#define	TICK_START_MOTOR		6000
int32_t CounterStartMotor = TICK_START_MOTOR;

uint8_t	StateCalib = 0;


void Blinky(void)
{
	State_t	StateMotor;
  State_t StateM1;
	
	
	HandlerKeys();
	
	if (Counter-- <= 0)
	{
		Counter = TICK_BLINKY;
		
		if (DRV8301() || CheckKey(DRIVER_OCTV) || CheckKey(DRIVER_FAULT))
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
