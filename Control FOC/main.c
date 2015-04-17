
#include "Config.h"
#include "spi.h"



const FOC_t* pFOC = &pADDRESS[0];

State_t StateMotor1;
int 		Value;


int main()
{
	SystemInitialize();
	
	pFOC->pCmdInitRAM();
	pFOC->pCmdInitLib();
	__enable_irq();


	while(1)
	{
		if (pFOC->pGetStateM1() == IDLE)
		{
			pFOC->pExecSpeedRampM1(0,0);
			pFOC->pCmdMotor1(MC_PROTOCOL_CMD_START_MOTOR);
		}
		else if (pFOC->pGetStateM1() == FAULT_OVER)
		{
			pFOC->pCmdMotor1(MC_PROTOCOL_CMD_FAULT_ACK);
			
		}
		
		Value  = pFOC->pGetRegM1(MC_PROTOCOL_REG_STATUS);
		StateMotor1	= pFOC->pGetStateM1();
		delay_(100);
	//	CmdSend(pFOC->pGetRegM1(MC_PROTOCOL_REG_MEAS_EL_ANGLE));
	};
}




