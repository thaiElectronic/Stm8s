/**
  ********************************************************************************
  * @file    stm8s_uart1.h
  * @author  Nguyen Quang Bien
  * @version 
  * @date    
  * @brief   
  *******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_H
#define __UART_H

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
void UART_Init(unsigned int select);
void UART_Send_String(char *_varString);
void UART_Send_Char(char _varChar);
void UART_Send_Number(int _varNumber);
void UART_Send_Array_RX(void);
int  UART_Compare(char *string);
int  UART_Flag(void);
#endif /* __STM8S_UART1_H */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/