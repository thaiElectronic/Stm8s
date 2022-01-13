#include "stm8s.h"
#include "uart.h"
/*
  Code Test GPIO_Pin_B5 -> Auto Run
  code test timer2, timer4
*/

char vruc_Stt = 0;
unsigned int ms_count = 0 ; // S? ph?n nghìn giây
void Config_Gpio(void);
void TIM4_Init(void);
void TIM2_Init(void);
int vruc_stt = 0;

void delay_ms(int a){
  for(int i=0;i<a;i++)
   for (int index = 0; index < 400; index++);
}

int main( void ){
  Config_Gpio();
  UART_Init(9600);
  TIM2_Init();
  enableInterrupts();
  while(1){

  }
}


void Config_Gpio(void){
  GPIOB->ODR = 0;
  GPIOB->DDR = (1<<7);
  GPIOB->CR1 = (1<<7);
  GPIOB->CR2 = (1<<7);
}

void TIM4_Init(void){

  CLK->CKDIVR = 0;
  CLK->PCKENR1 = 0xff;
  CLK->PCKENR2 = 0xff;
  
/*
  ap dung cong thuc tính nhu stm32
  bo dem max trong don vi us
*/
  
  TIM4->CR1 = 0x81;  // Counter enabled 
  TIM4->PSCR = 0x03; // 0x03 = 3(DEC);gia tri bo chia = 2^PSCR = 2^3 = 8;
  TIM4->ARR = 0x14;  //  sau 10us update
  TIM4->IER = 0x01;  // Update interrupt enabled
 

}
/*
INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23){
  
  vruc_stt = !vruc_stt;
  if(vruc_stt ==0)
    GPIOB->ODR = 0 << 7 ; // Ðèn LED 500MS l?t m?t l?n
  else
    GPIOB->ODR = 1 << 7;
  TIM4->SR1 = 0 ; // Xóa d?u ng?t
}
*/

 INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23){
  TIM4->SR1 = 0 ; // Xóa d?u ng?t
  ms_count ++;
  if (ms_count > 50000 ) // 10US * 50000 = 500MS
  {
    ms_count = 0 ;
    vruc_stt = !vruc_stt;
    if(vruc_stt ==0)
      GPIOB->ODR = 0 << 7 ; // Ðèn LED 500MS l?t m?t l?n
    else
      GPIOB->ODR = 1 << 7;
  }
}


void TIM2_Init(void){
  CLK->CKDIVR = 0;
  CLK->PCKENR1 = 0xff;
  CLK->PCKENR2 = 0xff;
  
  TIM2->PSCR = 0x0A; 
  TIM2->ARRH = 0x0C; // 8 bit high
  TIM2->ARRL = 0x35; // 8 bit low
  TIM2->IER = 0x01;  // Update interrupt enabled
  TIM2->CR1 = 0x01;  // Counter enabled
}
int vruc_stt2 = 0;
INTERRUPT_HANDLER(TIM2_UPD_OVF_BRK_IRQHandler, 13){
    vruc_stt2=!vruc_stt2;
    if(vruc_stt2==0){
      UART_Send_String("ON\n");
    }
    else{
      UART_Send_String("OFF\n");
    }
    TIM2->SR1 = (0<<0);
 }
