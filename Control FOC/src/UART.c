//**************************************************************
//Имя фукции: InitUART
//Описание: 	
//вход. значения:
//вых.  значения:
//**************************************************************
//=========================================================================

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include "misc.h"

#define	GPIO_RX			GPIOC
#define	GPIO_TX			GPIOC
#define	GPIO_RE			GPIOG
#define	GPIO_DE 		GPIOA

	/* Configure USART1 Rx as input floating */
#define PIN_Rx1     7	
#define PIN_Tx1     6
#define PIN_RE1			8
#define PIN_DE1			8

#define USART			USART6

void InitUART(void)
{
	USART_InitTypeDef 			USART_InitStructure;
	NVIC_InitTypeDef 				NVIC_InitStructure;	
	GPIO_InitTypeDef 				GPIO_InitStruct;	
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;	
	RCC->APB2ENR |=	RCC_APB2ENR_USART6EN;

	// USART config
	NVIC_InitStructure.NVIC_IRQChannel										= USART6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 5;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority					= 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
	

	GPIO_PinAFConfig(GPIO_RX, PIN_Rx1, GPIO_AF_USART6);
	GPIO_PinAFConfig(GPIO_TX, PIN_Tx1, GPIO_AF_USART6);	
	
	// DE
  GPIO_InitStruct.GPIO_Pin   = 1<<PIN_RE1;
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIO_RE, &GPIO_InitStruct);	
	
	// RE
  GPIO_InitStruct.GPIO_Pin   = 1<<PIN_DE1;
	GPIO_Init(GPIO_DE, &GPIO_InitStruct);

	// Rx
  GPIO_InitStruct.GPIO_Pin   = 1<<PIN_Rx1;
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(GPIO_RX, &GPIO_InitStruct);
	
	// Tx
  GPIO_InitStruct.GPIO_Pin   = 1<<PIN_Tx1;
	GPIO_Init(GPIO_TX, &GPIO_InitStruct);
	
	
	
	GPIO_SetBits(GPIO_DE, 1<<PIN_DE1);
	GPIO_ResetBits(GPIO_RE, 1<<PIN_RE1);	
	
	
	
	// USART init
	USART_InitStructure.USART_BaudRate 						= 115200;
	USART_InitStructure.USART_WordLength					= USART_WordLength_8b;
	USART_InitStructure.USART_StopBits						= USART_StopBits_1;
	USART_InitStructure.USART_Parity							= USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode								= USART_Mode_Rx |USART_Mode_Tx; 
	USART_Init(USART, &USART_InitStructure);
	USART_Cmd(USART, ENABLE);
	
}
#define SizeUsartTx	300

uint8_t	TxBuf[SizeUsartTx];
int16_t	TxCnt;
int16_t	TxPos;
int8_t	Status = 0;

//**************************************************************
//Имя фукции: USART1_IRQHandler
//Описание: 	Прерывание USART линии 2
//вход. значения:
//вых.  значения:
//**************************************************************
void USART6_IRQHandler(void)
{
	unsigned char b;
  
//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
//	{
//		b = USART1->DR;
//		CallCmdProcess2( 2, b);														// Обработка принятого байта
//	}
	if(USART_GetITStatus(USART, USART_IT_TXE) != RESET)
	{
		if(TxCnt>0)
		{
		  USART->DR = TxBuf[TxPos++];
		  TxCnt--;
		}
		else
		{ 																							// Нечего передавать
		  USART_ITConfig(USART, USART_IT_TXE, DISABLE);	// Запрещаем прерывание передатчика
		  USART_ITConfig(USART, USART_IT_TC, ENABLE);		// Разрешаем прерывание окончания передачи
		}
	}
	if(USART_GetITStatus(USART, USART_IT_TC) != RESET)
	{
		USART_ITConfig(USART, USART_IT_TC, DISABLE);
	//	CLEAR_BIT(GPIOA->BSRR, (1<<PIN_RE_DE1));					// TX Off
		USART->DR;
	//	CallCmdProcess2( 0xff, 0);
		Status = 0;
	}
	if(USART->SR & USART_SR_ORE)
	{	// Сброс ошибки переполнения буфера
//		USART1->CR1 &= ~USART_CR1_RE;
		USART->SR;
		USART->DR;
//		USART1->CR1 |= USART_CR1_RE;
	}	
}	

int CountTx = 0;

void CmdSend(int16_t Temp)
{
	if(Status == 0)
	{
		TxBuf[CountTx*2 + 0] = Temp >> 8;
		TxBuf[CountTx*2 + 1] = Temp;

		
		if (++CountTx >= SizeUsartTx/2 )
		{
			CountTx = 0;
			USART->DR = TxBuf[0];
			TxPos=1;
			TxCnt=SizeUsartTx-1;
			USART_ITConfig(USART, USART_IT_TXE, ENABLE);
			
			Status = 1;
		}
	}
}


