
#ifndef __SENSOR_GPIO_H__
#define __SENSOR_GPIO_H__
/* Includes ------------------------------------------------------------------*/
#include "stm8s_gpio.h"
typedef struct{
	unsigned char	vruc_DataOld;
	unsigned int 	vruc_CountAccess;
	unsigned char 	vruc_FlagChange;
        unsigned char   vruc_hold;
}	SS_TypeInput;
extern SS_TypeInput	vrts_ButtonA, vrts_ButtonB;

void GPIOSENSOR_ReadInput(unsigned char vruc_Input, SS_TypeInput *vrts_DataInput);
void GPIOSENSOR_Init(void);
#endif /* __STM8S_UART1_H */
