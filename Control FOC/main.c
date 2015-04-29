
#include "Config.h"
#include "spi.h"
#include "Zettlex.h"
#include "PID.h"

const FOC_t* pFOC = &pADDRESS[0];

State_t StateMotor1;
int 		Value;
int 		CounterFaultSpeed;

//#define Current (2.0 * 65536 * RSHUNT * AMPLIFICATION_GAIN / MCU_SUPPLY_VOLTAGE)

int main()
{
	FlafsZettlex_t StateZettlex;
	
	SystemInitialize();
	
	pFOC->pCmdInitRAM();
	pFOC->pCmdInitLib();

	SetStatePid(OFF);	
	pFOC->pExecSpeedRampM1(0,0);
	pFOC->pSetRegM1(MC_PROTOCOL_REG_SPEED_KI, 600);	
	pFOC->pSetRegM1(MC_PROTOCOL_REG_SPEED_KP, 5700);	
	pFOC->pCmdMotor1(MC_PROTOCOL_CMD_STOP_MOTOR);

		delay_(50);
	

//		while(1)
//	{
//			if (pFOC->pGetStateM1() == IDLE)
//			{
//				pFOC->pExecSpeedRampM1(10,0);
//				pFOC->pCmdMotor1(MC_PROTOCOL_CMD_START_MOTOR);
//		delay_(2000000);				
//				pFOC->pSetRegM1(MC_PROTOCOL_REG_SPEED_KI, 1000);	
//				pFOC->pSetRegM1(MC_PROTOCOL_REG_SPEED_KP, 20700);				
//			}
//			else if (pFOC->pGetStateM1() == FAULT_OVER)
//			{
//				pFOC->pCmdMotor1(MC_PROTOCOL_CMD_FAULT_ACK);
//			}

//		
//		
//		if ( (pFOC->pGetRegM1(MC_PROTOCOL_REG_SPEED_MEAS) > 600)
//			|| (pFOC->pGetRegM1(MC_PROTOCOL_REG_SPEED_MEAS) < -600) )
//		{
//			if (CounterFaultSpeed++ >	2000)
//				pFOC->pCmdMotor1(MC_PROTOCOL_CMD_STOP_MOTOR);
//		}
//		else
//			CounterFaultSpeed = 0;		
//	};
	
	while(1)
	{
		StateZettlex = GetZettlexFlags();
	
		if ((StateZettlex.NoAnswer == 1) || (StateZettlex.BadFrame == 1))
		{
			SetStatePid(OFF);
			pFOC->pExecSpeedRampM1(0,0);
			//pFOC->pCmdMotor1(MC_PROTOCOL_CMD_STOP_MOTOR);
		}
		else
		{
			SetStatePid(ON);
		
			if (pFOC->pGetStateM1() == IDLE)
			{
				pFOC->pExecSpeedRampM1(0,0);
				pFOC->pCmdMotor1(MC_PROTOCOL_CMD_START_MOTOR);
		delay_(2000000);				
				pFOC->pSetRegM1(MC_PROTOCOL_REG_SPEED_KI, 1000);	
				pFOC->pSetRegM1(MC_PROTOCOL_REG_SPEED_KP, 18700);					
			}
			else if (pFOC->pGetStateM1() == FAULT_OVER)
			{
				pFOC->pCmdMotor1(MC_PROTOCOL_CMD_FAULT_ACK);
			}
		}
		
		
		if ( (pFOC->pGetRegM1(MC_PROTOCOL_REG_SPEED_MEAS) > 600)
			|| (pFOC->pGetRegM1(MC_PROTOCOL_REG_SPEED_MEAS) < -600) )
		{
			if (CounterFaultSpeed++ >	2000)
				pFOC->pCmdMotor1(MC_PROTOCOL_CMD_STOP_MOTOR);
		}
		else
			CounterFaultSpeed = 0;
		
		
		Value  = pFOC->pGetRegM1(MC_PROTOCOL_REG_STATUS);
		StateMotor1	= pFOC->pGetStateM1();
		delay_(100);
	};
}




