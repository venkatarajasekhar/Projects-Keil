

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include "misc.h"
#include "Zettlex.h"


//----------------------------------------------------------------
	/* UART selection */
#define USART			UART5

	/* Configure USART pin for control Zettlex */
#define	GPIO_RX			GPIOD
#define PIN_Rx     2	

#define	GPIO_TX			GPIOC
#define PIN_Tx     	12

//----------------------------------------------------------------

#define SizeUsartTx	10
#define SizeUsartRx	10
#define AnswLen			6

uint8_t	ZettlexTxBuf[SizeUsartTx];
int16_t	ZettlexTxCnt;
int16_t	ZettlexTxPos;
uint8_t	RxBuf[SizeUsartRx];
int16_t	RxCnt = 0;
int16_t	RxPos = 0;

int8_t	ZettlexStatus = 0;
uint8_t	BuffCheckFrame[SizeUsartTx];

DataZettlex_t Zettlex;



//**************************************************************
//Имя фукции: InitUART
//Описание: 	
//вход. значения:
//вых.  значения:
//**************************************************************
void ZettlexInitUART(void)
{
	USART_InitTypeDef 			USART_InitStructure;
	NVIC_InitTypeDef 				NVIC_InitStructure;	
	GPIO_InitTypeDef 				GPIO_InitStruct;	
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;	
	RCC->APB1ENR |=	RCC_APB1ENR_UART5EN;

	// USART config
	NVIC_InitStructure.NVIC_IRQChannel										= UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 4;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority					= 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
	

	GPIO_PinAFConfig(GPIO_RX, PIN_Rx, GPIO_AF_UART5);
	GPIO_PinAFConfig(GPIO_TX, PIN_Tx, GPIO_AF_UART5);	
	
	// Rx
  GPIO_InitStruct.GPIO_Pin   = 1<<PIN_Rx;
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(GPIO_RX, &GPIO_InitStruct);
	
	// Tx
  GPIO_InitStruct.GPIO_Pin   = 1<<PIN_Tx;
	GPIO_Init(GPIO_TX, &GPIO_InitStruct);
	
	
	// USART init
	USART_InitStructure.USART_BaudRate 						= 230400;
	USART_InitStructure.USART_WordLength					= USART_WordLength_8b;
	USART_InitStructure.USART_StopBits						= USART_StopBits_1;
	USART_InitStructure.USART_Parity							= USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode								= USART_Mode_Rx |USART_Mode_Tx; 
	USART_Init(USART, &USART_InitStructure);
	USART_Cmd(USART, ENABLE);
	
	USART_ITConfig(USART, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART, USART_IT_IDLE, ENABLE);	
}


//**************************************************************
//Имя фукции: USART1_IRQHandler
//Описание: 	Прерывание USART линии 2
//вход. значения:
//вых.  значения:
//**************************************************************
void UART5_IRQHandler(void)
{
	unsigned char b;
 
	if(USART_GetITStatus(USART, USART_IT_RXNE) != RESET)
	{
		b = USART->DR;
		ReceivedDataZettlex(b);														// Обработка принятого байта
	}
	else if(USART_GetITStatus(USART, USART_IT_IDLE) == SET)
	{
		ProcessData();
	}		

	
	if(USART->SR & USART_SR_ORE)															// Сброс ошибки переполнения буфера
	{	
		USART->SR;
		USART->DR;
	}	
}	

//**************************************************************
//Имя фукции:	ReceivedDataZettlex
//Описание:		Прием данных Zettlex
//вход. значения:
//вых.  значения:
//**************************************************************
void ReceivedDataZettlex(uint8_t b)
{
	uint16_t crc, tr;
	uint16_t PersNum;


	RxBuf[RxPos++] = b;											// Сохранение принятого байта

	if(AnswLen <= RxPos)										// Проверка переполнения буфера
	{
		RxPos = 0;
	}

}

//**************************************************************
//Имя фукции:	PreparationData
//Описание:		Подготовка данных для расчета CRC
//вход. значения:
//вых.  значения:
//**************************************************************
void PreparationData(void)
{
	BuffCheckFrame[0] = RxBuf[0];
	BuffCheckFrame[1] = RxBuf[1];
	BuffCheckFrame[2] = RxBuf[2];
	BuffCheckFrame[3] = RxBuf[3] & 0xFC;				// Обнуление CRC16[15:0]
	BuffCheckFrame[4] = 0;
	BuffCheckFrame[5] = 0;
}

//**************************************************************
//Имя фукции:	ParseFrame
//Описание:		Разбор посылки
//вход. значения:
//вых.  значения:
//**************************************************************
void ParseFrame(void)
{
	if (RxBuf[0] & (1 << 6))
		Zettlex.Flags.PV = 1;
	else
		Zettlex.Flags.PV = 0;
	
	if (RxBuf[0] & (1 << 5))
		Zettlex.Flags.ZPD = 1;
	else
		Zettlex.Flags.ZPD = 0;
	
	Zettlex.Position  = ((uint32_t)RxBuf[3] & 0x7C) >> 2;
	Zettlex.Position += ((uint32_t)RxBuf[2] & 0x7F) << 5;	
	Zettlex.Position += ((uint32_t)RxBuf[1] & 0x7F) << 12;
	Zettlex.Position += ((uint32_t)RxBuf[0] & 0x07) << 19;
	
	Zettlex.Crc  = (uint16_t)RxBuf[5] & 0x7F;
	Zettlex.Crc +=((uint16_t)RxBuf[4] & 0x7F) << 7;
	Zettlex.Crc += (uint16_t)RxBuf[3] << 14;
}

//**************************************************************
//Имя фукции:	ProcessData
//Описание:		Обработка данных
//вход. значения:
//вых.  значения:
//**************************************************************
void ProcessData(void)
{
	ParseFrame();
	PreparationData();
	
	if ((CRC16_BUYPASS(&BuffCheckFrame[0],AnswLen) == Zettlex.Crc)
		&& (Zettlex.Flags.PV == 1)
		&& (Zettlex.Flags.ZPD == 1))
	{
		Zettlex.Flags.BadFrame = 0;
	}
	else
		Zettlex.Flags.BadFrame = 1;		
	
	RxPos = 0;
	USART->SR;
	USART->DR;
}


//**************************************************************
//Имя фукции:	CRC16_BUYPASS
//Описание:		Расчет CRC
//вход. значения:
//вых.  значения:
//**************************************************************
uint16_t CRC16_BUYPASS(uint8_t *data, uint8_t len) 
{ 
	#define POLYNOMIAL 0x8005	 
	 
  uint16_t crc = 0x0000; 
  uint8_t j; 
  int i; 
  for (j=len; j>0; j--) { 
    crc ^= (uint16_t)(*data++) << 8; 
    for (i=0; i<8; i++) { 
      if (crc & 0x8000) crc = (crc<<1) ^ POLYNOMIAL; 
      else crc <<= 1; 
    } 
  } 
  return (crc); 
} 

//**************************************************************
//Имя фукции:	GetZettlexPosition
//Описание:		Возвращает текущую позицию Zettlex
//вход. значения:
//вых.  значения:
//**************************************************************
uint32_t GetZettlexPosition (void)
{
	return Zettlex.Position;
}

