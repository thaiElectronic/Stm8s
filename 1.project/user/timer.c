#include "timer.h"

void TIM4_Init(void){
  CLK->CKDIVR = 0;
  CLK->PCKENR1 = 0xff;
  CLK->PCKENR2 = 0xff;
  
  TIM4->CR1 = 0x81;  // Counter enabled 
  TIM4->PSCR = 0x06; // 0x03 = 3(DEC);gia tri bo chia = 2^PSCR = 2^3 = 8;
  TIM4->ARR = 0xFA;  //  sau 10us update
  TIM4->IER = 0x01;  // Update interrupt enabled
}

