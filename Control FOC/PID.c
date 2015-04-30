//============================================================
//
// File Name    : 'PID.c'
// Project      :  FOC
// Title        :
// Author       : Федорин А.К.
// Created      : 17/04/2015
// Revised      :
// Version      : 1
// Target MCU   : STM32F4XX
// Compiler     : Keil 5.10.0.2
// Editor Tabs  : 2
//
// NOTE:
//============================================================
#include "PID.h"
#include "Zettlex.h"
#include "Config.h"
#include "USART.h"



#define	TICK_PID		4
int32_t CounterPid = TICK_PID;

int32_t drive;
SPid 		plantPID;

t_StatePid	StatePid = OFF;

/**
  * @brief  InitPID
  * @param  None
  * @retval None
  */
void InitPID(void)
{
	plantPID.Position = 0x010000;
	
	plantPID.pGain = 0.032;
	plantPID.pMin  = -10;
	plantPID.pMax	 = 10;

	plantPID.iMin   = -4720;
	plantPID.iMax   = 5720;
	plantPID.iGain  = 0.00085;
	plantPID.iState = 0;
 	
	plantPID.dState = 0;
	plantPID.dGain  = 0;
	
}

/**
  * @brief  ControlPID
  * @param  None
  * @retval None
  */
void ControlPID(void)
{
	double LeftDeviation;
	double RightDeviation;
	
	if (CounterPid-- <= 0)
	{
		CounterPid = TICK_PID;

		if (StatePid == ON)
		{
			if (GetZettlexPosition() > plantPID.Position)
			{
				RightDeviation = GetZettlexPosition() - plantPID.Position;
				LeftDeviation  = DEFINITION_ZETTLEX - LeftDeviation;
			}
			else
			{
				LeftDeviation  = plantPID.Position  - GetZettlexPosition();
				RightDeviation = DEFINITION_ZETTLEX - LeftDeviation;		
			}

			
			
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
}

/**
  * @brief  UpdatePID
  * @param  pointer SPid
  * @param  error
  * @param  current position
  * @retval None
  */
double UpdatePID(SPid * pid, double error, double position)
{
  double pTerm = 0, dTerm = 0, iTerm = 0;
 
	pTerm = pid->pGain * error;    				// calculate the proportional term

	if (pTerm > plantPID.pMax)
		pTerm = plantPID.pMax;
	else if (pTerm < plantPID.pMin)
		pTerm = plantPID.pMin;		
	
	pid->iState += error;          				// calculate the integral state with appropriate limiting
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

/**
  * @brief  SetPosition
  * @param  target  position
  * @retval None
  */
void SetPosition(uint32_t position)
{
	plantPID.Position = position;

}

/**
  * @brief  SetStatePid
  * @param  State  -  ON or OFF
  * @retval None
  */
void SetStatePid(t_StatePid _State)
{
	StatePid = _State;
}


///**
//  * @brief  SetStatePid
//  * @param  State  -  ON or OFF
//  * @retval None
//  */
//int32_t Get(void)
//{
//	return 
//}
