#include "stm8s.h"
#include "stm8s_tim2.h"
#include "stm8s_clk.h"
#include "uart.h"

int a=0;
//void Config_timer(void);
void Config_Gpio(void);
void Config_timer(void);
void Delay_ms(uint16_t _time);
void swap(int *x, int *y);
void xuly(int n, int str[]);
void delay_ms(int a){
  for(int i=0;i<a;i++)
   for (int index = 0; index < 400; index++);
}

void main(  ){
  int m;
  int arr[]={0,9,4,5,6,3,1,2,8,7};
  Config_Gpio();
  Config_timer();
  UART_Init(9600);
//  Config_timer(); 
//  enableInterrupts();
  UART_Send_String("Thai MCU\n");
  while(1){
    TIM2_Cmd(ENABLE);
    xuly(10,arr);
    m = TIM2_GetCounter();
    TIM2_Cmd(DISABLE);
    UART_Send_Number(m);
    UART_Send_String("(us)\n");
    m = 0;
    delay_ms(1000);    
  }
}



void Config_Gpio(void){
  GPIOE->ODR = 0;
  GPIOE->DDR = (1<<3);
  GPIOE->CR1 = (1<<3);
  GPIOE->CR2 = (1<<3);
}


void Config_timer(void){
  TIM2_DeInit();
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2,ENABLE);
  TIM2_TimeBaseInit(TIM2_PRESCALER_64,250);//1ms
  TIM2_SetCounter(0);
  TIM2_ClearFlag(TIM2_FLAG_UPDATE);  
  //TIM2_Cmd(ENABLE);
}

void Delay_ms(uint16_t _time){
  TIM2_Cmd(ENABLE);
  while(_time--){
    while(TIM2_GetFlagStatus(TIM2_FLAG_UPDATE) == 0);
    TIM2_ClearFlag(TIM2_FLAG_UPDATE);
  }
  TIM2_Cmd(DISABLE);
}

void swap(int *x, int *y){
  int temp = *x;
  *x=*y;
  *y = temp;
}


void xuly(int n, int str[]){
  int i,j;
  for(i=0;i<n-1;i++){
    for(j=i+1;j<n;j++){
      if(str[i]>str[j]){
        swap(&str[i],&str[j]);
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////
#ifdef USE_FULL_ASSERT
void assert_failed(u8* file, u32 line)

while(1)
{
  
}

#endif