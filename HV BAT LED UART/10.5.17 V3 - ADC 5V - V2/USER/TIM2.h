


#ifndef _TIM2_
#define _TIM2_

#include "stm8s.h"
#include "STM8CONFIG.h"


extern void Fn_STM8_IWDRReLoad (void);
void Fn_TIMER2_Init (void);
void Fn_TIMER2_Run (void);
void Fn_TIMER2_Stop (void);
void Fn_TIMER2_Load (unsigned int _vruc_Timer);
void Fn_TIMER2_Delayus  (unsigned int _vrui_Timer);
void Fn_TIMER2_Delayms (unsigned int _vrui_Timer);





#endif


