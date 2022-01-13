#ifndef _EmonLib_h
#define _EmonLib_h

#include "stm8s_gpio.h"

//#define inPinV GPIO_Pin_0
//
//#define inPortV GPIOA	


void current(unsigned int _inPinI, float _ICAL);
float calcIrms(unsigned int NUMBER_OF_SAMPLES);

void current1(unsigned int _inPinI, float _ICAL);
float calcIrms1(unsigned int Number_of_Samples, float _ICAL);

#endif
