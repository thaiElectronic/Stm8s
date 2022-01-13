
#ifndef __SENSOR_GPIO_H__
#define __SENSOR_GPIO_H__
/* Includes ------------------------------------------------------------------*/
#include "stm8s_gpio.h"
/*---------------------------------Define pinout Open door---------------------------------*/
#define PIN_MC38        GPIO_PIN_0
#define PORT_MC38       GPIOB
/*---------------------------------Define pinout Water---------------------------------*/
#define PIN_PHAO        GPIO_PIN_1         
#define PORT_PHAO       GPIOB
/*---------------------------------Define pinout Buzzz---------------------------------*/
#define PIN_COI_CHIP     GPIO_PIN_6
#define PORT_COI_CHIP    GPIOB
/*---------------------------------Define pinout Relay---------------------------------*/
#define PIN_RELAY1       GPIO_PIN_0
#define PIN_RELAY2       GPIO_PIN_1
/*---------------------------------Define pinout LED power---------------------------------*/
#define PIN_LED_RED      GPIO_PIN_3
#define PIN_LED_BLUE     GPIO_PIN_2
#define PROT_RELAY_LED   GPIOE // 2 led chung port
  
#define RING_ON         GPIO_WriteHigh(PORT_COI_CHIP, PIN_COI_CHIP)         
#define RING_OFF        GPIO_WriteLow(PORT_COI_CHIP, PIN_COI_CHIP)

#define Relay1_ON       GPIO_WriteLow(PROT_RELAY_LED, PIN_RELAY1)
#define Relay1_OFF      GPIO_WriteHigh(PROT_RELAY_LED, PIN_RELAY1)

#define Relay2_ON       GPIO_WriteLow(PROT_RELAY_LED, PIN_RELAY2)
#define Relay2_OFF      GPIO_WriteHigh(PROT_RELAY_LED, PIN_RELAY2)

#define LED_RED_ON       GPIO_WriteLow(PROT_RELAY_LED, PIN_LED_RED)
#define LED_RED_OFF      GPIO_WriteHigh(PROT_RELAY_LED, PIN_LED_RED)

#define LED_BLUE_ON       GPIO_WriteLow(PROT_RELAY_LED, PIN_LED_BLUE)
#define LED_BLUE_OFF      GPIO_WriteHigh(PROT_RELAY_LED, PIN_LED_BLUE)

#define RELAY0 0
#define RELAY1 2

void GPIOSENSOR_Init(void);
void GPIOSENSOR_ControlRelay(unsigned char vruc_stt, unsigned char vruc_mode);
#endif /* __STM8S_UART1_H */
