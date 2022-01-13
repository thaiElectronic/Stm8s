#include "timer.h"

extern unsigned char vruc_stt;
volatile unsigned char vruc_Count = 0;
unsigned int ms_count = 0;
void TIM2_Init(void){
  CLK->CKDIVR = 0;
  CLK->PCKENR1 = 0xff;
  CLK->PCKENR2 = 0xff;
  
//  TIM2->PSCR = 0x0A;  // DEC = 10;
/*
  16MHZ/(2^PSCR) = 16MHz/(2^10) = 15625
  15625 * 1s = 15625 =0x3D09
  TIM2->ARRH = 0x3D; // 8 bit high
  TIM2->ARRL = 0x09; // 8 bit low
//0.5s
  TIM2->ARRH = 0x1b; // 8 bit high
  TIM2->ARRL = 0xd8; // 8 bit low
*/
// TIM2->ARRH = 0x3D; // 8 bit high
//  TIM2->ARRL = 0x09; // 8 bit lo
//  TIM2->IER = 0x01;  // Update interrupt enabled
//  TIM2->CR1 = 0x01;  // Counter enabled
  TIM2->PSCR = 0x06;
  TIM2->ARRH = 0x00; // 8 bit high
  TIM2->ARRL = 0x7D; // 8 bit lo
  TIM2->IER = 0x01;  // Update interrupt enabled
  TIM2->CR1 = 0x01;  // Counter enabled
  
}

INTERRUPT_HANDLER(TIM2_UPD_OVF_BRK_IRQHandler, 13){
  TIM2->SR1 = 0 ; // Xóa d?u ng?t
  ms_count2 ++;
  if (ms_count2 > 1000 ) // 0.5ms * 1000 = 0.5s
  {
    ms_count2 = 0;
    vruc_stt!=vruc_stt;
    if(vruc_stt==1){
      UART_Send_String("ON\n");
      vruc_stt = 0;
    }
    else{
      UART_Send_String("OFF\n");
    }
  }
}

void TIM4_Init(void){
  CLK->CKDIVR = 0;
  CLK->PCKENR1 = 0xff;
  CLK->PCKENR2 = 0xff;
  
  TIM4->CR1 = 0x81;  // Counter enabled 
  TIM4->PSCR = 0x03; // 0x03 = 3(DEC);gia tri bo chia = 2^PSCR = 2^3 = 8;
  TIM4->ARR = 0x14;  //  sau 10us update
  TIM4->IER = 0x01;  // Update interrupt enabled
 
}

//void Run_timer2(){
//  if(vruc_stt==1){
//    UART_Send_String("ON");
//    vruc_stt = 0;
//  }
//  else{
//    UART_Send_String("OFF");
//  }
//}

INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23){
  TIM4->SR1 = 0 ; // Xóa d?u ng?t
  ms_count ++;
  if (ms_count > 50000 ) // 10US * 500 = 5MS
  {
    ms_count = 0 ;
    vruc_stt = 1;
  }
}