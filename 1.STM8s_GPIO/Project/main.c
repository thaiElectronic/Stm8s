#include "stm8s.h"
#include "GPIO.h"

#define GREEN_C1         GPIO_PIN_4     //PD4
#define GREEN_C2         GPIO_PIN_3     //PD3
#define GREEN_C3         GPIO_PIN_6     //PC6
#define GREEN_C4         GPIO_PIN_3     //PC3

#define YELLOW_A1        GPIO_PIN_2     //PA2
#define YELLOW_A2        GPIO_PIN_5     //PD5
#define YELLOW_A3        GPIO_PIN_2     //PD2
#define YELLOW_A4        GPIO_PIN_5     //PC5

#define RED_B1           GPIO_PIN_1     //PA1
#define RED_B2           GPIO_PIN_6     //PD6
#define RED_B3           GPIO_PIN_7     //PC7
#define RED_B4           GPIO_PIN_4     //PC4

#define A1_1    GPIO_WriteHigh(GPIOA,YELLOW_A1);
#define A1_0    GPIO_WriteLow(GPIOA,YELLOW_A1);

#define B1_1    GPIO_WriteHigh(GPIOA,RED_B1);
#define B1_0    GPIO_WriteLow(GPIOA,RED_B1);

#define C1_1    GPIO_WriteHigh(GPIOD,GREEN_C1);
#define C1_0    GPIO_WriteLow(GPIOD,GREEN_C1);


void delay_ms(int a)
{
  for(int i=0;i<a;i++)
   for (int index = 0; index < 400; index++);
}

void SetGpio_ConfigGpio(void)
{
  GPIO_DeInit(GPIOA);
  GPIO_DeInit(GPIOC);
  GPIO_DeInit(GPIOD);
  GPIOC->DDR |= (1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7);
  GPIOC->CR1 |= (1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7);
  GPIOC->CR2 |= (1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7);
  
  GPIOD->DDR |= (1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6);
  GPIOD->CR1 |= (1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6);
  GPIOD->CR2 |= (1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6);
  
  GPIOA->DDR |= (1<<1)|(1<<2);
  GPIOA->CR1 |= (1<<1)|(1<<2);
  GPIOA->CR2 |= (1<<1)|(1<<2);

//  GPIO_Init(GPIOA,BUTTON,GPIO_MODE_IN_PU_NO_IT);
}


int main( void ){
  
  
  GPIOB->DDR = 1<<7; // cau hinh chan PB7 la che do ngo ra
  GPIOB->CR1 = 1<<7; // cau hinh chan PB7 la push pull
  GPIOB->CR2 = 1<<7; // chon toc do cho chan PB5 la 10MHz
  
  while(1){
    A1_1; B1_0; C1_1;
    delay_ms(1000);
    A1_0; B1_1; C1_1;
    delay_ms(1000);
  }
}
