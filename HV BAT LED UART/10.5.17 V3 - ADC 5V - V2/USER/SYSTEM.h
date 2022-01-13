

#ifndef _SYSTEM_
#define _SYSTEM_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//#include <stdint.h>

//#include "stm8s.h"
#include "stm8s_conf.h"
#include "STM8SCONFIG.h"
#include "Delay.h"
#include "UART.h"
//#include "Flash.h"
//#include "TIM4.h"

#define TRUE      1
#define FALSE     0 

#define stop      0
#define up        1 
#define down      2 

extern unsigned char counter1, counter2;
extern unsigned char signal_in, pulseUpDown;
extern unsigned char receivedBits; 
extern unsigned char dataBuffer[10]; //1 byte ID, 4 bytes RFID Tag serial number, 1 byte line parity, 4 bytes column parity bits.
extern unsigned char parity,colParity;

extern uint16_t Conversion_Value;
extern unsigned int VR_num;
extern unsigned char vruc_n;
extern char Number[3];

extern unsigned char SPI_TXBuffer[2];
extern unsigned char SPI_RXBuffer[2];
extern unsigned char SPI_Flag;
extern unsigned char SPI_TXFlag;
extern unsigned char SPI_RXFlag;
extern unsigned char SPI_MANUAL_Flag;


#define led1               GPIOB_ODR.PIN5
#define led2               GPIOB_ODR.PIN4
#define led3               GPIOC_ODR.PIN3
#define led4               GPIOC_ODR.PIN4
#define led5               GPIOC_ODR.PIN5
#define led6               GPIOC_ODR.PIN6
#define led7               GPIOC_ODR.PIN7
#define led8               GPIOD_ODR.PIN4
#define led9               GPIOA_ODR.PIN1
#define led10              GPIOA_ODR.PIN2
#define led11              GPIOA_ODR.PIN3
#define led12              GPIOD_ODR.PIN1

void Fn_STM8_IWDTInit (void);
void Fn_STM8_IWDRReLoad (void);
void Fn_SYS_Init_GPIO (void);

void GPIO_Config(void);
void CLK_Config(void);
void EXTI_Config(void);
void TIM2_PWM1_Config(uint16_t CCR1_Val);
void TIM2_PWM2(uint16_t TIM2_Pulse);
void TIM4_Config(void);
void UART1_Config(void);
void ADC1_Config(void);
void SPI_Config(void);
void SPI_init(void);
void Motor_VR(unsigned char Dir);
void Control_VR(int VR);

uint16_t get_VR1(void);
uint16_t get_VR2(void);

//void Fn_SYS_RFID(void);

void hex2Ascii (void);
void delay_time(unsigned long counter);
void sendTxD (unsigned char txd);
void init_PWM (void);

void Fn_SYS_7SEG (unsigned char _vruc_Number);
void Fn_SYS_DisplayLED (void);
void Fn_SYS_NumberLED (unsigned int vrui_Display);
#endif


