/**
  ********************************************************************************
  * @file    stm8s_uart1.c
  * @author  MCD Application Team
  * @version V2.2.0
  * @date    30-September-2014
  * @brief   This file contains all the functions for the UART1 peripheral.
   ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "uart.h"
#include "stm8s.h"
#include "string.h"
#include "stdio.h"
#define string_size 80
char RX_FLAG_END_LINE = 0;
char RRX[string_size];
unsigned int RXI = 0;
char temp_char;
char Number[1];

void UART_Init(unsigned int select)
{
  CLK->CKDIVR = 0;
  CLK->PCKENR1 = 0xff;
  CLK->PCKENR2 = 0xff;
  GPIOD->DDR |=  (1<<5);
  GPIOD->DDR &= ~(1<<6);
  // baudrate 16MHZ / 57600 = 277 = 0x115
  // baudrate 16MHZ / 9600 = 1666 = 0x682
  switch(select)
  {
    case 9600:
      UART1->BRR1 = 0x68; 
      UART1->BRR2 = 0x02;
      break;
    case 57600:
      UART1->BRR1 = 0x11; 
      UART1->BRR2 = 0x05;
      break;
    break;
  }
  UART1->CR1  = (0<<5);
  UART1->CR2  = (1<<2) | (1<<3) | (1<<5);
  enableInterrupts();
}
void UART_Send_Char(char _varChar)
{
  UART1->DR = _varChar;
  while(!(UART1->SR & (1<<7)));
}
void UART_Send_String(char *_varString)
{
   while(*_varString)
    {
        UART_Send_Char(*_varString);
        _varString++;
    }
}
void UART_Send_Number(int _varNumber)
{
  sprintf(Number,"%d.",_varNumber);
  UART_Send_String(Number);
}
void UART_Send_Array_RX(void)
{
  UART_Send_String(RRX);
}
int  UART_Compare(char *string)
{
  if(strstr(RRX,string)!=NULL)
     return 1;	
     return 0;
}

int  UART_Flag(void)
{
  if(RX_FLAG_END_LINE == 1)
    {	
	RX_FLAG_END_LINE = 0;
	return 1;
    }
  return 0;
}
INTERRUPT_HANDLER(UART1_RX_IRQHandler, 18)
 {
   
     temp_char = UART1->DR;
     if(temp_char!='\n')
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
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/