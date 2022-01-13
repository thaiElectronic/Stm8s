
#ifndef __MCP3208_H__
#define __MCP3208_H__
/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "stm8s_spi.h"
#include "stm8s_gpio.h"
#include "uart.h"
#include "delay.h"

#define MCP3208_CSHigh  GPIO_WriteHigh(GPIOE,GPIO_PIN_6); 
#define MCP3208_CSLow   GPIO_WriteLow(GPIOE,GPIO_PIN_6);

void MCP3208_Init(void);
unsigned char MCP3208_Transfer(unsigned char data);
unsigned short MCP3208_AnalogRead(unsigned char pin);
void MCP3208_Test(void);

#endif /* __STM8S_UART1_H */
