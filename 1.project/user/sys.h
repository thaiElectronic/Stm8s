
#ifndef __SYS_H__
#define __SYS_H__
/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "sys_define.h"
#include "sensor_gpio.h"
#include "stm8s_tim4.h"
#include "mcp3208.h"
#include "timer.h"
#include "delay.h"
#include "uart.h"
#include "math.h"
#define SR_NUMBER       (20u)
#define TIME_SEND       (100)
#define KALMAN          (0.1u)
void Sys_Init(void);
void Sys_Run(void);
#endif /* __STM8S_UART1_H */
