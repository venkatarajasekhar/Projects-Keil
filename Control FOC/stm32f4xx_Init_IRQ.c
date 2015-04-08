

#include "Config.h"

/**
  * @brief  This function handles ADC1/ADC2 interrupt request.
  * @param  None
  * @retval None
  */
void ADC_IRQHandler(void)
{
	pFOC->_ADC_Handler();
}

/**
  * @brief  This function handles first motor TIMx Update interrupt request.
  * @param  None
  * @retval None
  */
void TIMx_UP_M1_IRQHandler(void)
{
	pFOC->_TIM_M1_Handler();
}

#if defined(DUALDRIVE)
/**
  * @brief  This function handles second motor TIMx Update interrupt request.
  * @param  None
  * @retval None
  */
void TIMx_UP_M2_IRQHandler(void)
{
	pFOC->_TIM_M2_Handler()();
}
#endif

/**
  * @brief  This function handles first motor DMAx TC interrupt request. 
  *         Required only for R1 with rep rate > 1
  * @param  None
  * @retval None
  */
void DMAx_R1_M1_IRQHandler(void)
{
	pFOC->_DMA_M1_Handler();
}

#if defined(DUALDRIVE)
/**
  * @brief  This function handles second motor DMAx TC interrupt request. 
  *         Required only for R1 with rep rate > 1
  * @param  None
  * @retval None
  */
void DMAx_R1_M2_IRQHandler(void)
{
	pFOC->_DMA_M2_Handler(); 
}
#endif


#if ((defined ENCODER) || (defined AUX_ENCODER) || (defined HALL_SENSORS) \
                                                  || (defined AUX_HALL_SENSORS))
/**
  * @brief  This function handles TIMx global interrupt request for M1 Speed Sensor.
  * @param  None
  * @retval None
  */
void SPD_TIM_M1_IRQHandler(void)
{
	pFOC->_SPD_TIM_M1_Handler();
}
#endif

#if defined(DUALDRIVE)
#if ((defined ENCODER2) || (defined AUX_ENCODER2) || (defined HALL_SENSORS2) \
                                                  || (defined AUX_HALL_SENSORS2))
/**
  * @brief  This function handles TIMx global interrupt request for M2 Speed Sensor.
  * @param  None
  * @retval None
  */
void SPD_TIM_M2_IRQHandler(void)
{
	pFOC->_SPD_TIM_M2_Handler();
}
#endif
#endif

#ifdef SERIAL_COMMUNICATION
/*Start here***********************************************************/
/*GUI, this section is present only if serial communication is enabled*/
/**
  * @brief  This function handles USART interrupt request.
  * @param  None
  * @retval None
  */
void USART_IRQHandler(void)
{
	pFOC->_USART_Handler();
}
#endif

extern void CmdSend(int16_t Temp);
/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	pFOC->_SysTick_Handler();
	Blinky();
		//	CmdSend(pFOC->pGetRegM1(MC_PROTOCOL_REG_MEAS_EL_ANGLE));
}






