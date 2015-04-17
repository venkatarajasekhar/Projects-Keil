

#include "spi.h"
#include "Keys.h"
#include "InitPin.h"
#include "USART.h"

#include "Config.h"
#include "stm32f4xx_gpio.h"
#include "Zettlex.h"

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

extern void ZettlexInitUART(void);

void SystemInitialize(void)
{
	SystemCoreClockUpdate();
	
	InitPin();
	InitSPI();
	InitUART();
	ZettlexInitUART();
}


#define	TICK_BLINKY		500
int32_t Counter = TICK_BLINKY;

#define	TICK_START_MOTOR		6000
int32_t CounterStartMotor = TICK_START_MOTOR;

#define	TICK_PID		100
int32_t CounterPid = TICK_PID;


uint8_t	StateCalib = 0;


typedef struct
{
	uint32_t Position;
  double dState;          // Last position input
  double iState;          // Integrator state
  double iMax, iMin;     	// Maximum and minimum allowable integrator state
  double    iGain,        // integral gain
            pGain,        // proportional gain
            dGain;        // derivative gain
} SPid;



SPid plantPID = 
{
	0x20000,
	0,
	0,
//	0,0,
//	0,
	162,-162,
	0.002,
	0.0080,
	0,//0.0580
};


double UpdatePID(SPid * pid, double error, double position)
{
  double pTerm, dTerm, iTerm;
 
  pTerm = pid->pGain * error;    // calculate the proportional term
	
	if (pTerm > 300)
		pTerm = 300;
	else if (pTerm < -300)
		pTerm = -300;
	
  pid->iState += error;          // calculate the integral state with appropriate limiting
  if (pid->iState > pid->iMax) 
      pid->iState = pid->iMax;     
  else if (pid->iState < pid->iMin) 
      pid->iState = pid->iMin;
	
  iTerm = pid->iGain * pid->iState;    // calculate the integral term
	if (position > pid->dState)
		dTerm = pid->dGain * (position - pid->dState);
	else
		dTerm = -pid->dGain * (pid->dState - position);
	
  pid->dState = position;
	
  return (pTerm + iTerm - dTerm);
}


#define USER_POSITION					0x10000
#define DEFINITION_ZETTLEX		262143

	signed int drive;


void Blinky(void)
{
	State_t	StateMotor;
  State_t StateM1;
	double LeftDeviation;
	double RightDeviation;
	
	if (GetZettlexPosition() > plantPID.Position)
	{
		RightDeviation = GetZettlexPosition() - plantPID.Position;
		LeftDeviation  = DEFINITION_ZETTLEX - LeftDeviation;
	}
	else
	{
		LeftDeviation  = plantPID.Position - GetZettlexPosition();
		RightDeviation = DEFINITION_ZETTLEX - LeftDeviation;		
	}
	
//pFOC->pExecSpeedRampM1(300,0);
//	while(1)
//	{

//	}
	
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
		CmdSend(GetZettlexPosition() >>16);
		CmdSend(GetZettlexPosition());
				CmdSend(0);
				CmdSend(0);		
		
	}
	
	
	if (CounterPid-- <= 0)
	{
		CounterPid = TICK_PID;
		
		if (RightDeviation > LeftDeviation)
		{
			drive = UpdatePID(&plantPID, -LeftDeviation, GetZettlexPosition());
		}
		else
		{
			drive = UpdatePID(&plantPID, RightDeviation, GetZettlexPosition());			
		}
		pFOC->pExecSpeedRampM1(drive,0);
			
		

	}	
	
}


void SetPosition(uint32_t position)
{
	plantPID.Position = position;
		CmdSend(GetZettlexPosition() >>16);
		CmdSend(GetZettlexPosition());
				CmdSend(0);
				CmdSend(0);	
	
}
