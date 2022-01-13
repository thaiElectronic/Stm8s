/**
  ********************************************************************************
  * @file    stm8s_uart1.h
  * @author  Nguyen Quang Bien
  * @version 
  * @date    
  * @brief   
  *******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_FRAME_H
#define __UART_FRAME_H

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
typedef struct
{
  unsigned char Relay0;
  unsigned char Relay1;
}Control_Relay;
extern Control_Relay vrcr_RelayStt;
void ftoa(float n, char* res, int afterpoint);
void create_string_data(float arr[], char *str);
char checksumRX(char arr1[],char arr2[]);
void detect_string(char arr[]);
#endif /* __STM8S_UART1_H */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/