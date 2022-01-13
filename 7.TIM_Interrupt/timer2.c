#include "timer2.h"

char vruc_stt = 0;

void TIMER2_Init(void){
  CLK->CKDIVR = 0;
  CLK->PCKENR1 = 0xff;
  CLK->PCKENR2 = 0xff;
  //16MHZ/1024 = 15625
  TIM2->PSCR = 0x0A; 
  //15625 * 1s = 15625 =0x3D09
  TIM2->ARRH = 0x3D; // 8 bit high
  TIM2->ARRL = 0x09; // 8 bit low
  TIM2->IER = 0x01;  // Update interrupt enabled
  TIM2->CR1 = 0x01;  // Counter enabled
}

 INTERRUPT_HANDLER(TIM2_UPD_OVF_BRK_IRQHandler, 13)
 {
    vruc_stt=!vruc_stt;
    if(vruc_stt==0) 
      GPIOB->ODR = (0<<7);
    else
      GPIOB->ODR = (1<<7);
 
    TIM2->SR1 = (0<<0);
 }