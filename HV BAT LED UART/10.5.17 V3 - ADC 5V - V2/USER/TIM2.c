
#include "TIM2.h"



void Fn_TIMER2_Init (void)
{
    TIM2->PSCR = 0x04;
    TIM2->ARRH  = 0xFF;
    TIM2->ARRL  = 0xFF;
    TIM2->EGR  = 0x01;
    TIM2->CR1 |= (1<<7);
    TIM2->IER &= ~(1<<0);
}


void Fn_TIMER2_Run (void){
    TIM2->CR1 |= (1<<0);
}

void Fn_TIMER2_Stop (void){
    TIM2->CR1 &= ~(1<<0);
}


void Fn_TIMER2_Load (unsigned int _vruc_Timer){
    TIM2->CNTRH = (_vruc_Timer>>8) & 0xFF;
    TIM2->CNTRL = _vruc_Timer & 0xFF;
}

void Fn_TIMER2_Delayus  (unsigned int _vrui_Timer){
    unsigned int vrui_Temp;
    vrui_Temp = 0xFFFF - _vrui_Timer;
    Fn_TIMER2_Load(vrui_Temp);
    Fn_TIMER2_Run();
    while(!(TIM2->SR1 & 0x01)){
        Fn_STM8_IWDRReLoad();
    }
    Fn_TIMER2_Stop();
    TIM2->SR1 &= ~0x01;
}


void Fn_TIMER2_Delayms (unsigned int _vrui_Timer){
    while(_vrui_Timer--){
        Fn_TIMER2_Delayus(1000);
    }
}