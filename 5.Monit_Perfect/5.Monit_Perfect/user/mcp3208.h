
#ifndef __MCP3208_H__
#define __MCP3208_H__
/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "stm8s_spi.h"
#include "stm8s_gpio.h"
#include "uart.h"

#define PIN_CS0_MCP3208         GPIO_PIN_5
#define PORT_CS0_MCP3208        GPIOE

#define PIN_CS1_MCP3208         GPIO_PIN_6
#define PORT_CS1_MCP3208        GPIOE

#define MCP3208_CS0_HIGH        GPIO_WriteHigh(PORT_CS0_MCP3208,PIN_CS0_MCP3208); 
#define MCP3208_CS0_LOW         GPIO_WriteLow(PORT_CS0_MCP3208,PIN_CS0_MCP3208);

#define MCP3208_CS1_HIGH        GPIO_WriteHigh(PORT_CS1_MCP3208,PIN_CS1_MCP3208); 
#define MCP3208_CS1_LOW         GPIO_WriteLow(PORT_CS1_MCP3208,PIN_CS1_MCP3208);

void MCP3208_Init(void);
unsigned char MCP3208x0_Transfer(unsigned char data);
unsigned int MCP3208x0_AnalogRead(unsigned char pin);

unsigned char MCP3208x1_Transfer(unsigned char data);
unsigned int MCP3208x1_AnalogRead(unsigned char pin);
void MCP3208_Test(void);
//unsigned int Map(unsigned int x, unsigned int in_min, unsigned int in_max, unsigned int out_min, unsigned int out_max);
float Map(float x, float in_min, float in_max, float out_min, float out_max);
//int Map(int x, int in_min, int in_max, int out_min, int out_max);

#endif /* __STM8S_UART1_H */
