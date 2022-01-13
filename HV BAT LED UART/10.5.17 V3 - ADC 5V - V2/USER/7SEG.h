/*
 * _7SEG.h
 *
 * Created: 10/11/2014 4:14:58 PM
 *  Author: Duan
 */ 


#ifndef _7SEG_H_
#define _7SEG_H_

#include "STM8CONFIG.h"

#define MAXLED	3


#define PINLED_A        GPIOC_ODR.PIN5
#define PINLED_B        GPIOC_ODR.PIN7
#define PINLED_C        GPIOE_ODR.PIN5
#define PINLED_D        GPIOC_ODR.PIN3
#define PINLED_E        GPIOC_ODR.PIN4
#define PINLED_F        GPIOC_ODR.PIN6
#define PINLED_G        GPIOC_ODR.PIN1
#define PINLED_DP       GPIOC_ODR.PIN2


#define PINLED_1        GPIOD_ODR.PIN4
#define PINLED_2        GPIOD_ODR.PIN3
#define PINLED_3        GPIOD_ODR.PIN2


#define MAXTIMEBLINK		300
#define HALFTIMEBLINK		150

extern unsigned char vruc_7SEG_Ram2Disp[MAXLED];
extern unsigned char vruc_7SEG_CountLED;
extern unsigned int  vrui_7SEG_Count2Blink;


extern unsigned char Fn_7SEG_Dec2Seg (unsigned char _vruc_Data);
extern void Fn_7SEG_OutData (unsigned char _vruc_Data);
extern void Fn_7SEG_Control (unsigned char _vruc_Cmd);
extern void Fn_7SEG_Display (void);
extern void Fn_7SEG_Init (void);


#endif /* 7SEG_H_ */


