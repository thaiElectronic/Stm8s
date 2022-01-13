/**
  ********************************************************************************
  * @file    stm8s_uart1.h
  * @author  Nguyen Quang Bien
  * @version 
  * @date    
  * @brief   
  *******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO__
#define __GPIO__

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

typedef enum
{
  GPIO_MODE_IN_FL_NO_IT      = (uint8_t)0x00,  /*!< Input floating, no external interrupt */
  GPIO_MODE_IN_PU_NO_IT      = (uint8_t)0x40,  /*!< Input pull-up, no external interrupt */
  GPIO_MODE_IN_FL_IT         = (uint8_t)0x20,  /*!< Input floating, external interrupt */
  GPIO_MODE_IN_PU_IT         = (uint8_t)0x60,  /*!< Input pull-up, external interrupt */
  GPIO_MODE_OUT_OD_LOW_FAST  = (uint8_t)0xA0,  /*!< Output open-drain, low level, 10MHz */
  GPIO_MODE_OUT_PP_LOW_FAST  = (uint8_t)0xE0,  /*!< Output push-pull, low level, 10MHz */
  GPIO_MODE_OUT_OD_LOW_SLOW  = (uint8_t)0x80,  /*!< Output open-drain, low level, 2MHz */
  GPIO_MODE_OUT_PP_LOW_SLOW  = (uint8_t)0xC0,  /*!< Output push-pull, low level, 2MHz */
  GPIO_MODE_OUT_OD_HIZ_FAST  = (uint8_t)0xB0,  /*!< Output open-drain, high-impedance level,10MHz */
  GPIO_MODE_OUT_PP_HIGH_FAST = (uint8_t)0xF0,  /*!< Output push-pull, high level, 10MHz */
  GPIO_MODE_OUT_OD_HIZ_SLOW  = (uint8_t)0x90,  /*!< Output open-drain, high-impedance level, 2MHz */
  GPIO_MODE_OUT_PP_HIGH_SLOW = (uint8_t)0xD0   /*!< Output push-pull, high level, 2MHz */
}GPIO_Mode_TypeDef;



typedef enum
{
  GPIO_PIN_0    = ((uint8_t)0x01),  /*!< Pin 0 selected */
  GPIO_PIN_1    = ((uint8_t)0x02),  /*!< Pin 1 selected */
  GPIO_PIN_2    = ((uint8_t)0x04),  /*!< Pin 2 selected */
  GPIO_PIN_3    = ((uint8_t)0x08),   /*!< Pin 3 selected */
  GPIO_PIN_4    = ((uint8_t)0x10),  /*!< Pin 4 selected */
  GPIO_PIN_5    = ((uint8_t)0x20),  /*!< Pin 5 selected */
  GPIO_PIN_6    = ((uint8_t)0x40),  /*!< Pin 6 selected */
  GPIO_PIN_7    = ((uint8_t)0x80),  /*!< Pin 7 selected */
  GPIO_PIN_LNIB = ((uint8_t)0x0F),  /*!< Low nibble pins selected */
  GPIO_PIN_HNIB = ((uint8_t)0xF0),  /*!< High nibble pins selected */
  GPIO_PIN_ALL  = ((uint8_t)0xFF)   /*!< All pins selected */
}GPIO_Pin_TypeDef;


#define IS_GPIO_MODE_OK(MODE) \
  (((MODE) == GPIO_MODE_IN_FL_NO_IT)    || \
   ((MODE) == GPIO_MODE_IN_PU_NO_IT)    || \
   ((MODE) == GPIO_MODE_IN_FL_IT)       || \
   ((MODE) == GPIO_MODE_IN_PU_IT)       || \
   ((MODE) == GPIO_MODE_OUT_OD_LOW_FAST)  || \
   ((MODE) == GPIO_MODE_OUT_PP_LOW_FAST)  || \
   ((MODE) == GPIO_MODE_OUT_OD_LOW_SLOW)  || \
   ((MODE) == GPIO_MODE_OUT_PP_LOW_SLOW)  || \
   ((MODE) == GPIO_MODE_OUT_OD_HIZ_FAST)  || \
   ((MODE) == GPIO_MODE_OUT_PP_HIGH_FAST)  || \
   ((MODE) == GPIO_MODE_OUT_OD_HIZ_SLOW)  || \
   ((MODE) == GPIO_MODE_OUT_PP_HIGH_SLOW))

#define IS_GPIO_PIN_OK(PIN)  ((PIN) != (uint8_t)0x00)



void GPIO_DeInit(GPIO_TypeDef* GPIOx);
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef GPIO_Pin, GPIO_Mode_TypeDef GPIO_Mode);
void GPIO_Write(GPIO_TypeDef* GPIOx, uint8_t PortVal);
void GPIO_WriteHigh(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef PortPins);
void GPIO_WriteLow(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef PortPins);
void GPIO_WriteReverse(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef PortPins);
uint8_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx);
uint8_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);
BitStatus GPIO_ReadInputPin(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef GPIO_Pin);
void GPIO_ExternalPullUpConfig(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef GPIO_Pin, FunctionalState NewState);



#endif /* __STM8S_UART1_H */



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/