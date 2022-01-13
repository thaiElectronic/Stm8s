#ifndef _EXTI_H_
#define _EXTI_H_

#include "stm8s.h"
#include "UART.h"

extern unsigned char	vruc_EXTI_Flag;

typedef enum {
  EXTI_PORT_GPIOA = (uint8_t)0x00, /*!< GPIO Port A */
  EXTI_PORT_GPIOB = (uint8_t)0x01, /*!< GPIO Port B */
  EXTI_PORT_GPIOC = (uint8_t)0x02, /*!< GPIO Port C */
  EXTI_PORT_GPIOD = (uint8_t)0x03, /*!< GPIO Port D */
  EXTI_PORT_GPIOE = (uint8_t)0x04  /*!< GPIO Port E */
} EXTI_Port_TypeDef;

typedef enum {
  EXTI_SENSITIVITY_FALL_LOW  = (uint8_t)0x00, /*!< Interrupt on Falling edge and Low level */
  EXTI_SENSITIVITY_RISE_ONLY = (uint8_t)0x01, /*!< Interrupt on Rising edge only */
  EXTI_SENSITIVITY_FALL_ONLY = (uint8_t)0x02, /*!< Interrupt on Falling edge only */
  EXTI_SENSITIVITY_RISE_FALL = (uint8_t)0x03  /*!< Interrupt on Rising and Falling edges */
} EXTI_Sensitivity_TypeDef;

void Fn_EXTI_Config(void);
void Fn_EXTI_SetExtIntSensitivity(EXTI_Port_TypeDef Port, EXTI_Sensitivity_TypeDef SensitivityValue);

#endif