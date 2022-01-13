
#ifndef __MCP3208_H__
#define __MCP3208_H__
/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "stm8s_spi.h"
#include "stm8s_gpio.h"
#include "uart.h"

#define MCP3208_CSHigh  GPIO_WriteHigh(GPIOE,GPIO_PIN_5); 
#define MCP3208_CSLow   GPIO_WriteLow(GPIOE,GPIO_PIN_5);

void MCP3208_Init(void);
unsigned char MCP3208_Transfer(unsigned char data);
unsigned int MCP3208_AnalogRead(unsigned char pin);
void MCP3208_Test(void);
//unsigned int Map(unsigned int x, unsigned int in_min, unsigned int in_max, unsigned int out_min, unsigned int out_max);
//float Map(float x, float in_min, float in_max, float out_min, float out_max);
int Map(int x, int in_min, int in_max, int out_min, int out_max);

#endif /* __STM8S_UART1_H */
