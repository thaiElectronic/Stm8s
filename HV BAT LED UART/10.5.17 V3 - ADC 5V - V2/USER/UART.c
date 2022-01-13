#include "stm8s.h"
#include "system.h"
#include "UART.h"
#include "stdio.h"
#define string_size 90
extern char RX_FLAG_END_LINE;
extern char RRX[string_size];
unsigned int RXI = 0;
char temp_char;
char Number_uart[5];
unsigned char   RFID_UART_Num[7];
unsigned char   vruc_UART_i;
char            vrsc_UART_ReceiveBuffer[64];
volatile unsigned char vruc_UART_Start, vruc_UART_Stop;
unsigned int    vrui_UART_CountReceive;

//void Fn_UART_Init (uint32_t BaudRate)
//{
//  CLK->CKDIVR = 0;
//  CLK->PCKENR1 = 0xff;
//  CLK->PCKENR2 = 0xff;
//  GPIOD->DDR |=  (1<<5);
//  GPIOD->DDR &= ~(1<<6);
//  // baudrate 16MHZ / 57600 = 277 = 0x115
//  // baudrate 16MHZ / 9600 = 1666 = 0x682
//  switch(BaudRate)
//  {
//    case 9600:
//      UART1->BRR1 = 0x68; 
//      UART1->BRR2 = 0x02;
//      break;
//    case 57600:
//      UART1->BRR1 = 0x11; 
//      UART1->BRR2 = 0x05;
//      break;
////    case 115200:
////      UART1->BRR1 = 0x56; 
////      UART1->BRR2 = 0xC0;
////      break;
//    break;
//  }
//  UART1->CR1  = (0<<5);
//  UART1->CR2  = (1<<2) | (1<<3) | (1<<5);
// // enableInterrupts();
//}
void Fn_UART_GetChar (void)
{
    if((UART1->SR & (1<<5)))
    {
      if(vruc_UART_i<7)
      {
        RFID_UART_Num[vruc_UART_i] = UART1->DR;
        vruc_UART_i++;
      }
    }
}

/*
char Fn_UART_GetChar (void)
{
    while(!(UART1->SR & (1<<5)));
    return ((char)UART1->DR);
}*/

void Fn_UART_SendChar (char _vruc_Data)
{
  UART1->DR = _vruc_Data;
  while(!(UART1->SR & (1<<7)));
}
          


void Fn_UART_Pustf (char *_vruc_String)
{
   while(*_vruc_String)
    {
        Fn_UART_SendChar(*_vruc_String);
        _vruc_String++;
    }
}
void Fn_UART_PustNum(unsigned int _vrl_Number)
{
//    unsigned char num[4], vruc_i;
//    for(vruc_i = 0; vruc_i < 4; vruc_i++)
//    {
//        num[vruc_i]    = _vrl_Number%10;
//        _vrl_Number /= 10;
//    }
//    while(vruc_i > 0)
//    {
//        Fn_UART_SendChar (0x30 + num[vruc_i - 1]);
//        vruc_i--;
//    }
    sprintf(Number_uart,"%d.",_vrl_Number);
    Fn_UART_Pustf(Number_uart);
}

INTERRUPT_HANDLER(UART1_RX_IRQHandler, 18)
 {
   
     temp_char = UART1->DR;
     if(temp_char!='*')
     {
       RRX[RXI] = temp_char;
       RXI++;
     }
     else
     {
       RRX[RXI] = 0;
       RXI = 0;
       RX_FLAG_END_LINE=1;
     }  
 }
