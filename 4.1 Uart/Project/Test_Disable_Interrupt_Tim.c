#include "stm8s.h"
  
/*
  Code Test GPIO_Pin_B5 k su dung ngat timer -> Auto Run
*/

void Config_Gpio(void);

void delay_ms(int a){
  for(int i=0;i<a;i++)
   for (int index = 0; index < 400; index++);
}

int main( void ){
  Config_Gpio();
 
  while(1){
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