/**
  ********************************************************************************
  * @file    stm8s_uart1.c
  * @author  MCD Application Team
  * @version V2.2.0
  * @date    30-September-2014
  * @brief   This file contains all the functions for the UART2 peripheral.
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
volatile char vruc_CountCheckSum = 0;
char RX_FLAG_END_LINE = 0;
char RRX[string_size];
char vruc_ArrayCheckSum[5];
unsigned int RXI = 0;
char temp_char;
char Number[1];
char vruc_StartCheckSum = 0;

void UART_Init(uint32_t BaudRate)
{
  uint8_t BRR2_1 = 0, BRR2_2 = 0;
  uint32_t BaudRate_Mantissa = 0, BaudRate_Mantissa100 = 0;
 
  GPIOD->DDR |=  (1<<5);
  GPIOD->DDR &= ~(1<<6);

  BaudRate_Mantissa    = ((uint32_t)16000000 / (BaudRate << 4));
  BaudRate_Mantissa100 = (((uint32_t)16000000 * 100) / (BaudRate << 4));
  BRR2_1 = (uint8_t)((uint8_t)(((BaudRate_Mantissa100 - (BaudRate_Mantissa * 100))<< 4) / 100) & (uint8_t)0x0F); 
  BRR2_2 = (uint8_t)((BaudRate_Mantissa >> 4) & (uint8_t)0xF0);
  UART2->BRR2 = (uint8_t)(BRR2_1 | BRR2_2);
  UART2->BRR1 = (uint8_t)BaudRate_Mantissa;
  
  UART2->CR1  = (0<<5);
  UART2->CR2  = (1<<2) | (1<<3) | (1<<5);
}

void UART_Send_Char(char _varChar)
{
  UART2->DR = _varChar;
  while(!(UART2->SR & (1<<7)));
}

void UART_Send_String(char *_varString)
{
   while(*_varString)
    {
        UART_Send_Char(*_varString);
        _varString++;
    }
}

void UART_Send_Number( float _varNumber)
{
  sprintf(Number,"%0.2f",_varNumber);
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

INTERRUPT_HANDLER(UART2_RX_IRQHandler, 21)
 {
   temp_char = UART2->DR;
   if(temp_char == '*')
   {
     vruc_StartCheckSum = 1;
     vruc_CountCheckSum = 0;
   }
   else if(vruc_StartCheckSum==1)
   {
     vruc_CountCheckSum++;
     vruc_ArrayCheckSum[vruc_CountCheckSum-1] = temp_char;
     if(vruc_CountCheckSum == 2)
     {
        vruc_ArrayCheckSum[vruc_CountCheckSum++] = 0;
        vruc_CountCheckSum = 0;
        RRX[RXI] = 0;
        RXI = 0;
        RX_FLAG_END_LINE=1;
        vruc_StartCheckSum = 0;
     }
   }
   else 
   {
     RRX[RXI] = temp_char;
     RXI++;
   }  
 }
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/