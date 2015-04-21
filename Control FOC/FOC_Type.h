


#ifndef __FOC_Type_H
#define __FOC_Type_H

#include "MC_type.h"
#include "MCInterfaceClass.h"
#include "Parameters conversion_F4xx.h"

#define ADDRESS  	0x80F0000

typedef void (*pf)(void);
typedef int  (*pfg)(void);
typedef int  (*pfs)(int);
typedef int  (*pfss)(signed int,unsigned short int);
typedef int  (*pfss1)(signed int,signed int);

typedef __packed struct
{
	pf _ADC_Handler;
	pf _TIM_M1_Handler;
	pf _DMA_M1_Handler;
	pf _SPD_TIM_M1_Handler;
	pf _SysTick_Handler;
#if defined(DUALDRIVE)
	pf _TIM_M2_Handler;
	pf _DMA_M2_Handler;
	pf _SPD_TIM_M2_Handler;
#endif
#ifdef SERIAL_COMMUNICATION
	pf _USART_Handler;	
#endif			
	
	pf  pCmdInitLib;
	pf  pCmdInitRAM;	
	pfs pCmdMotor1;	
	pfs pGetRegM1;	
	pfss1 pSetRegM1;
	
	pfss pExecSpeedRampM1;
	pfss pExecTorqueRampM1;
	
	CommandState_t (*IsCommandAcknowledged) (void);
	State_t 				(*pGetStateM1) (void);
	
#if defined(DUALDRIVE)
	State_t 				(*pGetStateM2) (void);
#endif		
	
	char s_fwVer[32];																		/* FIRMWARE_VERS */
//	unsigned short  ValidSign;
//	unsigned short  CRC16;
}FOC_t;



#endif
