#include "stm8s.h"
#include "uart.h"
void delay_ms(int a){
  for(int i=0;i<a;i++)
   for (int index = 0; index < 400; index++);
}


int main( void ){
  UART_Init(9600);
 // enableInterrupts();
// UART1_Pustf("Thai MCU!\n");
  while(1)
  {
   UART_Send_String("Thai mcu\n");
    //UART1_Pustf("Thai MCU\n");
    delay_ms(500);
  }
}


/*
char a[50] ,temp;

char dem=0;
int IT=0;


INTERRUPT_HANDLER(UART1_RX_IRQHandler, 18){
   
     temp= UART1->DR;
     if(temp!='!')
     {
       a[dem] = temp;
       dem++;
     }
     else
     {
       a[dem] = 0;
       dem = 0;
       IT=1;
     }  
 }

*/