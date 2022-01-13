#include "stm8s.h"
int a=0;
//void Config_timer(void);
void Config_Gpio(void);

void delay_ms(int a)
{
  for(int i=0;i<a;i++)
   for (int index = 0; index < 400; index++);
}

int main( void )
{
//  Config_timer();
  Config_Gpio();
 // enableInterrupts();
  while(1)
  {
    GPIOB->ODR = (1<<5);
    delay_ms(500);
    GPIOB->ODR = (0<<5);
    delay_ms(500);
  }
}


void Config_Gpio(void)
{
  GPIOB->ODR = 0;
  GPIOB->DDR = (1<<5);
  GPIOB->CR1 = (1<<5);
  GPIOB->CR2 = (1<<5);
}

 

/*
    GPIOB->ODR = (1<<7);
    Fn_Delayms(500);
    GPIOB->ODR = (0<<7);
    Fn_Delayms(500);

INTERRUPT_HANDLER(TIM2_UPD_OVF_BRK_IRQHandler, 13){
    a=!a;
    if(a==0) 
      GPIOB->ODR = (0<<7);
    else
      GPIOB->ODR = (1<<7);
    TIM2->SR1 = (0<<0);
 }

void Config_timer(void)
{
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

*/