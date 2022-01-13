#include "EXTI.h"

unsigned char	vruc_EXTI_Flag;

INTERRUPT_HANDLER(EXTI_PORTD_IRQHandler, 6)
{
	if(!(((uint8_t)GPIOD->IDR)&(1<<2))){
		vruc_EXTI_Flag = 1;
	}
}

void Fn_EXTI_Config(void){
	GPIOD->CR1 &= (uint8_t)(~(1<<2));
	GPIOD->CR2 &= (uint8_t)(~(1<<2));
	GPIOD->DDR &= (uint8_t)(~(1<<2));		/* Set Input mode */
	GPIOD->CR1 |= (uint8_t)(1<<2);			/* Pull-Up or Push-Pull */
	GPIOD->CR2 |= (uint8_t)(1<<2);			/* Interrupt or Slow slope */
	Fn_EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD, EXTI_SENSITIVITY_FALL_ONLY);
	enableInterrupts();
}

void Fn_EXTI_SetExtIntSensitivity(EXTI_Port_TypeDef Port, EXTI_Sensitivity_TypeDef SensitivityValue)
{
    /* Set external interrupt sensitivity */
    switch (Port)
    {
    case EXTI_PORT_GPIOA:
        EXTI->CR1 &= (uint8_t)(~EXTI_CR1_PAIS);
        EXTI->CR1 |= (uint8_t)(SensitivityValue);
        break;
    case EXTI_PORT_GPIOB:
        EXTI->CR1 &= (uint8_t)(~EXTI_CR1_PBIS);
        EXTI->CR1 |= (uint8_t)((uint8_t)(SensitivityValue) << 2);
        break;
    case EXTI_PORT_GPIOC:
        EXTI->CR1 &= (uint8_t)(~EXTI_CR1_PCIS);
        EXTI->CR1 |= (uint8_t)((uint8_t)(SensitivityValue) << 4);
        break;
    case EXTI_PORT_GPIOD:
        EXTI->CR1 &= (uint8_t)(~EXTI_CR1_PDIS);
        EXTI->CR1 |= (uint8_t)((uint8_t)(SensitivityValue) << 6);
        break;
    case EXTI_PORT_GPIOE:
        EXTI->CR2 &= (uint8_t)(~EXTI_CR2_PEIS);
        EXTI->CR2 |= (uint8_t)(SensitivityValue);
        break;
    default:
        break;
    }
}