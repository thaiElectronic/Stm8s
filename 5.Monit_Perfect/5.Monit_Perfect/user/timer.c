#include "timer.h"

//unsigned char vruc_stt2 = 0;
unsigned char vruc_stt = 0;

volatile unsigned char vruc_Count = 0;
unsigned int ms_count = 0;
/*
void TIM4_Init(void){
  TIM4_DeInit();
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4,ENABLE);
  TIM4_TimeBaseInit(TIM4_PRESCALER_64,250);//1ms
  TIM4_SetCounter(0);
  TIM4_ClearFlag(TIM4_FLAG_UPDATE);  
  TIM4_Cmd(ENABLE);
}

INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23){
//  TIM4->SR1 = 0 ; // Xóa d?u ng?t
  ms_count ++;
  if (ms_count > 500 ){ // 1MS * 500 = 500Ms
    ms_count = 0;
    vruc_stt =! vruc_stt;
    if( vruc_stt == 0 ){ GPIOE -> ODR = 0<<3; }
    else GPIOE -> ODR = 1<<3;
    TIM4->SR1 = (0<<0);
  }
}

INTERRUPT_HANDLER(TIM2_UPD_OVF_BRK_IRQHandler, 13){
  int vri_i;
    for(vri_i = 0; vri_i < 10; vri_i++){
        MCP3208x0_AnalogRead(vri_i);
        MCP3208x1_AnalogRead(vri_i);
      }
      //vruc_stt2 = 0;
    TIM2->SR1 = (0<<0);
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

INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23){
//  TIM4->SR1 = 0 ; // Xóa d?u ng?t
  ms_count ++;
  if (ms_count > 30000 ) // 10US * 500 = 5MS
  {
    ms_count = 0 ;
    vruc_stt=!vruc_stt;
    if(vruc_stt==0){  MCP3208_Test();GPIOB->ODR = 0<<7;}
    else GPIOB->ODR = 1<<7;
    TIM4->SR1 = (0<<0);
  }
}
*/

void TIM4_Init(void){
  CLK->CKDIVR = 0;
  CLK->PCKENR1 = 0xff;
  CLK->PCKENR2 = 0xff;
  
  TIM4->CR1 = 0x81;  // Counter enabled 
  TIM4->PSCR = 0x06; // 0x03 = 3(DEC);gia tri bo chia = 2^PSCR = 2^3 = 8;
  TIM4->ARR = 0xFA;  //  sau 10us update
  TIM4->IER = 0x01;  // Update interrupt enabled
 
}

