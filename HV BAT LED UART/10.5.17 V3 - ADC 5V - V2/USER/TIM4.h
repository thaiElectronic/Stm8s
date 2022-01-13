#ifndef _TIM4_H_
#define _TIM4_H_

#include "stm8s.h"
#include "SYSTEM.h"

#define TIM4_PERIOD	124

/** TIM4 Prescaler */
typedef enum
{
  TIM4_PRESCALER_1  = ((uint8_t)0x00),
  TIM4_PRESCALER_2    = ((uint8_t)0x01),
  TIM4_PRESCALER_4    = ((uint8_t)0x02),
  TIM4_PRESCALER_8     = ((uint8_t)0x03),
  TIM4_PRESCALER_16   = ((uint8_t)0x04),
  TIM4_PRESCALER_32     = ((uint8_t)0x05),
  TIM4_PRESCALER_64    = ((uint8_t)0x06),
  TIM4_PRESCALER_128   = ((uint8_t)0x07)
} TIM4_Prescaler_TypeDef;

/** TIM4 Flags */
typedef enum
{
  TIM4_FLAG_UPDATE                   = ((uint8_t)0x01)
}TIM4_FLAG_TypeDef;
/** TIM4 interrupt sources */
typedef enum
{
  TIM4_IT_UPDATE                     = ((uint8_t)0x01)
}TIM4_IT_TypeDef;

extern unsigned int vrui_TIM4_Cnt;

void Fn_TIM4_Init(void);
void Fn_TIM4_TimeBaseInit(TIM4_Prescaler_TypeDef TIM4_Prescaler, uint8_t TIM4_Period);
void Fn_TIM4_ClearFlag(TIM4_FLAG_TypeDef TIM4_FLAG);
void Fn_TIM4_ITConfig(TIM4_IT_TypeDef TIM4_IT, FunctionalState NewState);
void Fn_TIM4_Cmd(FunctionalState NewState);
void Fn_TIM4_ClearITPendingBit(TIM4_IT_TypeDef TIM4_IT);

#endif