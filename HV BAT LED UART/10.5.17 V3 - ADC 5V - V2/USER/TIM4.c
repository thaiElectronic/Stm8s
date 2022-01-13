#include "TIM4.h"
#include "system.h"

unsigned int vrui_TIM4_Cnt;

INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23)          // 1ms
{
	/* code */
    vrui_TIM4_Cnt++;
   if(vrui_TIM4_Cnt >= 1000)                            // 1s
   {
      SPEAKER = !SPEAKER;
      vrui_TIM4_Cnt = 0;
   }
    Fn_TIM4_ClearITPendingBit(TIM4_IT_UPDATE);
}
void Fn_TIM4_Init(void){
	/* Time base configuration */
	Fn_TIM4_TimeBaseInit(TIM4_PRESCALER_128, TIM4_PERIOD);
	/* Clear TIM4 update flag */
	Fn_TIM4_ClearFlag(TIM4_FLAG_UPDATE);
	/* Enable update interrupt */
	Fn_TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);

	/* enable interrupts */
	enableInterrupts();

	/* Enable TIM4 */
	Fn_TIM4_Cmd(ENABLE);
}
void Fn_TIM4_TimeBaseInit(TIM4_Prescaler_TypeDef TIM4_Prescaler, uint8_t TIM4_Period)
{
    /* Set the Prescaler value */
    TIM4->PSCR = (uint8_t)(TIM4_Prescaler);
    /* Set the Autoreload value */
    TIM4->ARR = (uint8_t)(TIM4_Period);
}
void Fn_TIM4_ClearFlag(TIM4_FLAG_TypeDef TIM4_FLAG)
{
    /* Clear the flags (rc_w0) clear this bit by writing 0. Writing ‘1’ has no effect*/
    TIM4->SR1 = (uint8_t)(~TIM4_FLAG);
}
void Fn_TIM4_ITConfig(TIM4_IT_TypeDef TIM4_IT, FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
        /* Enable the Interrupt sources */
        TIM4->IER |= (uint8_t)TIM4_IT;
    }
    else
    {
        /* Disable the Interrupt sources */
        TIM4->IER &= (uint8_t)(~TIM4_IT);
    }
}
void Fn_TIM4_Cmd(FunctionalState NewState)
{
    /* set or Reset the CEN Bit */
    if (NewState != DISABLE)
    {
        TIM4->CR1 |= TIM4_CR1_CEN;
    }
    else
    {
        TIM4->CR1 &= (uint8_t)(~TIM4_CR1_CEN);
    }
}
void Fn_TIM4_ClearITPendingBit(TIM4_IT_TypeDef TIM4_IT)
{
    /* Clear the IT pending Bit */
    TIM4->SR1 = (uint8_t)(~TIM4_IT);
}
/* TIM4 configuration:
	- TIM4CLK is set to 16 MHz, the TIM4 Prescaler is equal to 128 so the TIM1 counter		//TIM4_PRESCALER_128
	clock used is 16 MHz / 128 = 125 000 Hz
	- With 125 000 Hz we can generate time base:
	max time base is 2.048 ms if TIM4_PERIOD = 255 --> (255 + 1) / 125000 = 2.048 ms
	min time base is 0.016 ms if TIM4_PERIOD = 1  --> (  1 + 1) / 125000 = 0.016 ms
	- In this example we need to generate a time base equal to 1 ms
	so TIM4_PERIOD = (0.001 * 125000 - 1) = 124 
*/