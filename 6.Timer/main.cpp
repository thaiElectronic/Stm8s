#include "stm8s.h"
int a=0;
void Config_timer(void);
void Config_Gpio(void);
int main( void )
{
  Config_timer();
  Config_Gpio();
  enableInterrupts();
  while(1)
  {

  }
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

void Config_Gpio(void)
{
  GPIOD->ODR = 0;
  GPIOD->DDR = (1<<4);
  GPIOD->CR1 = (1<<4);
  GPIOD->CR2 = (1<<4);
}

 INTERRUPT_HANDLER(TIM2_UPD_OVF_BRK_IRQHandler, 13)
 {
    a=!a;
    if(a==0) 
      GPIOD->ODR = (0<<4);
    else
      GPIOD->ODR = (1<<4);
    TIM2->SR1 = (0<<0);
 }
