

#ifndef _18B20_
#define _18B20_

#include "stm8s.h"
#include "STM8CONFIG.h"
#include "Delay.h"
#include "UART.h"
#include "Timer.h"



#define DQ_IN       GPIOB_IDR.PIN3
#define DQ_OUT      GPIOB_ODR.PIN3
#define DQ_DIR      GPIOB_DDR.PIN3


void Fn_18B20_Init (void);
unsigned char Fn_18B20_ReadByte(void);
void Fn_18B20_WriteByte(unsigned char _vruc_Data);
float Fn_1820_Read(void);



#endif


