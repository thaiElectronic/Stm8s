#include "stm8s.h"

void delay_ms(int a)
{
  for(int i=0;i<a;i++)
   for (int index = 0; index < 400; index++);
}
char a[50] ,temp;

char dem=0;
int IT=0;

void Config_uart(void);
void UART_SendChar(char vruc_Data);
void UART_Pustf(char *vruc_String);

int main( void ){
 Config_uart();
 enableInterrupts();
  while(1)
  {
    if(IT==1)
    {
      UART_Pustf(a);
      IT = 0;
    }
  }
}

void Config_uart(void){
   CLK->CKDIVR = 0;
   CLK->PCKENR1 = 0xff;
   CLK->PCKENR2 = 0xff;
   GPIOD->DDR |=  (1<<5);
   GPIOD->DDR &= ~(1<<6);
/*
  thiet lap toc do baud = 9600;
  9600: BRR1 = 0x68| BRR2 = 0x03

  cách tính: F = 16MHz;
  Dec: 16Mhz/9600 = 1667 -> hex: 0x0683 
*/
   UART1->BRR1 = 0x68;
   UART1->BRR2 = 0x03;
  
/*
  UART_CR1: cau hinh bit lam viec 8 or 9 bit
*/
   UART1->CR1  = (0<<4);
   
/*
    UART_CR2: cho phep truyen nhan du lieu va cho phep ngat hoat dong
     REN: nhan
     TEN: truyen
     RIEN: ngat
*/  
   UART1->CR2  = 0x2c;  

}

void UART_SendChar (char vruc_Data){
    UART1->DR = vruc_Data;
    while(!(UART1->SR & (1<<7)));
}
          
          
void UART_Pustf (char *vruc_String){
    while(*vruc_String)
    {
        UART_SendChar(*vruc_String);
        vruc_String++;
    }
}

INTERRUPT_HANDLER(UART1_RX_IRQHandler, 18)
 {
   
     temp= UART1->DR;
     if(temp!='\n')
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

