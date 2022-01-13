
#ifndef __SYS_H__
#define __SYS_H__
/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "sys_define.h"
#include "sensor_gpio.h"
#include "mcp3208.h"
#include "timer.h"
#include "delay.h"
#include "uart.h"

#define PIN_MC38        GPIO_PIN_6
#define PORT_MC38       GPIOB
#define PIN_PHAO        GPIO_PIN_5         
#define PORT_PHAO       GPIOB

#define CHANNEL_MQ2     (0u)
#define CHANNEL_NTC     (1u)
/*
extern unsigned int vrui_MC38;
extern unsigned int vrui_Phao;
extern unsigned int vrui_NTC;
extern unsigned int vrui_MQ2;
*/
void Sys_Init(void);
void Sensor_Read(void);
//void Sensor_disp(void);
//void Sys_process(void);

#endif /* __STM8S_UART1_H */
