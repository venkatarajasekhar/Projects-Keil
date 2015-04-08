//============================================================
//
// File Name    : 'spi.c'
// Project      :  
// Title        :
// Author       : Федорин А.К.
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
//	Секция включаемых файлов
//============================================================
#include "stm32f4xx.h"
#include "spi.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_spi.h"

//**************************************************************
//Имя фукции:	InitSPI
//Описание:		Инициализация SPI
//вход. значения: 
//вых. значения:
//**************************************************************
void InitSPI(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	SPI_InitTypeDef  SPI_InitStruct;
	
	
	if      (SPI == SPI1)
		RCC->APB2ENR  |= RCC_APB2ENR_SPI1EN;
	else if (SPI == SPI2)
		RCC->APB1ENR  |= RCC_APB1ENR_SPI2EN;
	

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN;

	
  GPIO_InitStruct.GPIO_Pin   = 1 << PIN_CS;
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIO_CS, &GPIO_InitStruct);	
		
  GPIO_InitStruct.GPIO_Pin   = 1 << PIN_SCK;
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_25MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIO_SCK, &GPIO_InitStruct);	

  GPIO_InitStruct.GPIO_Pin   = 1 << PIN_MOSI;
	GPIO_Init(GPIO_MOSI, &GPIO_InitStruct);
	
  GPIO_InitStruct.GPIO_Pin   = 1 << PIN_MISO;
	GPIO_Init(GPIO_MISO, &GPIO_InitStruct);	
	

	GPIO_PinAFConfig(GPIO_SCK, 	PIN_SCK,  GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIO_MOSI, PIN_MOSI, GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIO_MISO, PIN_MISO, GPIO_AF_SPI2);

	/*--------------- Reset SPI init structure parameters values -----------------*/
  
  SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex; /* Initialize the SPI_Direction member */
  SPI_InitStruct.SPI_Mode = SPI_Mode_Master;											/* initialize the SPI_Mode member */
  SPI_InitStruct.SPI_DataSize = SPI_DataSize_16b;                 /* initialize the SPI_DataSize member */
  SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;                         /* Initialize the SPI_CPOL member */
  SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;                       /* Initialize the SPI_CPHA member */
  SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;                          /* Initialize the SPI_NSS member */
  SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;  /* Initialize the SPI_BaudRatePrescaler member */
  SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;                 /* Initialize the SPI_FirstBit member */
  SPI_InitStruct.SPI_CRCPolynomial = 7;                           /* Initialize the SPI_CRCPolynomial member */
	SPI_Init(SPI, &SPI_InitStruct);
	
	SPI_Cmd(SPI,ENABLE);	
	
	CHIP_SELECT_ON;
}

//**************************************************************
//Имя фукции:			SendByteSPI
//Описание:				Передача байта
//вход. значения:	Байт данных
//вых.  значения:	Считанное значение
//**************************************************************
unsigned char SendByteSPI(unsigned char TXdata)
{
	u8	result;

	SPI->DR = TXdata;																			/* Send pattern. 							*/
		while(!(SPI->SR & SPI_SR_RXNE));										/* Wait for receive complete. */
	
	result = SPI->DR;																			/* Read received data. 				*/
	
	return(result);
}



//**************************************************************
/**
  * @brief  delay
  * @param  Value(us)
  * @retval None
  */
void delay_(__IO uint32_t nCount)
{
  __IO uint32_t index = 0; 
  for(index = (168/3 * nCount); index != 0; index--)
  {
  }
}

enum
{
	NO_INIT,
	INIT,
};


int32_t	StateDRV8301 = NO_INIT;
int32_t CounterDRV = TICK_DRV;


const u16	dataTx[5] = 
{
	CMD_WRITE | ADRESS_CONTROL_REG1 | OC_ADJ_SET_60 | REPORT_ONLY | PWM_INPUTS_6 | NORMAL_MODE |GateDriveCurrent_1700mA,
	CMD_WRITE | ADRESS_CONTROL_REG2 | CYCLE_BY_CYCLE | SHUNT_AMPLIFIER2_CONNECTS | SHUNT_AMPLIFIER1_CONNECTS |GainOfShuntAmplifier_20V | REPORT_BOTH_OT_AND_OC,	
	CMD_READ  | ADRESS_CONTROL_REG1,
	CMD_READ  | ADRESS_CONTROL_REG2,
	0
};

uint8_t DRV8301(void)
{
	u8  Status = 0;
	u16 Buff1 = 0;
	u16 Buff2 = 0;
	
	
	if (CounterDRV >= 0)
	{
		CounterDRV--;
	}
	else if (StateDRV8301 == NO_INIT)
	{	
		CounterDRV = TICK_DRV;
		
		CHIP_SELECT_OFF;
			delay_(1);

			SPI_I2S_ReceiveData(SPI);		
			SPI_I2S_SendData(SPI, dataTx[0]);
			while (!SPI_I2S_GetFlagStatus(SPI, SPI_I2S_FLAG_RXNE)){};
		CHIP_SELECT_ON;
			delay_(10);		

		CHIP_SELECT_OFF;	
			delay_(1);	
			SPI_I2S_ReceiveData(SPI);	
			SPI_I2S_SendData(SPI, dataTx[2]);
			while (!SPI_I2S_GetFlagStatus(SPI, SPI_I2S_FLAG_RXNE)){};
		CHIP_SELECT_ON;
			delay_(10);	

		CHIP_SELECT_OFF;	
			delay_(1);				
			SPI_I2S_ReceiveData(SPI);	
			SPI_I2S_SendData(SPI, 0);
			while (!SPI_I2S_GetFlagStatus(SPI, SPI_I2S_FLAG_RXNE)){};
			Buff1 = SPI_I2S_ReceiveData(SPI);	
		CHIP_SELECT_ON;
			delay_(10);

		CHIP_SELECT_OFF;
			delay_(1);		
			SPI_I2S_SendData(SPI, dataTx[1]);
			while (!SPI_I2S_GetFlagStatus(SPI, SPI_I2S_FLAG_RXNE)){};

		CHIP_SELECT_ON;		
			delay_(10);		
		
		CHIP_SELECT_OFF;	
			delay_(1);	
			SPI_I2S_ReceiveData(SPI);	
			SPI_I2S_SendData(SPI, dataTx[3]);
			while (!SPI_I2S_GetFlagStatus(SPI, SPI_I2S_FLAG_RXNE)){};
		CHIP_SELECT_ON;
			delay_(10);	

		CHIP_SELECT_OFF;	
			delay_(1);				
			SPI_I2S_ReceiveData(SPI);	
			SPI_I2S_SendData(SPI, 0);
			while (!SPI_I2S_GetFlagStatus(SPI, SPI_I2S_FLAG_RXNE)){};
			Buff2 = SPI_I2S_ReceiveData(SPI);	
		CHIP_SELECT_ON;		
				
		if ((Buff1 != (dataTx[0] & 0x7FFF)) || (Buff2 != (dataTx[1] & 0x7FFF)))
			Status = 1;
		else
			StateDRV8301 = INIT;				
	}
//	else
//	{
//		CHIP_SELECT_OFF;		
//			delay_(1);

//		SPI_I2S_SendData(SPI, dataTx[0]);
//		while (!SPI_I2S_GetFlagStatus(SPI, SPI_I2S_FLAG_RXNE)){};
//			delay_(1);		
//			
//		SPI_I2S_SendData(SPI, dataTx[2]);
//		while (SPI_I2S_GetFlagStatus(SPI, SPI_I2S_FLAG_RXNE)){};
//			delay_(1);			
//			
//		SPI_I2S_SendData(SPI, 0);
//		while (SPI_I2S_GetFlagStatus(SPI, SPI_I2S_FLAG_RXNE)){};
//			delay_(1);

//		if (SPI_I2S_ReceiveData(SPI) != dataTx[2])
//			Status = 1;
//			
//		SPI_I2S_SendData(SPI, dataTx[1]);
//		while (SPI_I2S_GetFlagStatus(SPI, SPI_I2S_FLAG_RXNE)){};
//		
//		CHIP_SELECT_ON;	
//	}
	return Status;
}
