#ifndef     _DELAY_H_
#define	    _DELAY_H_

#include "stm8s.h"

#define	FRIQUENCY	16000000
#define CYCLES_PER_US ((FRIQUENCY + 500000)/1000000)
void Fn_Delayus(unsigned int _vrui_Delay);
void Fn_Delayms(unsigned int _vrui_Delay);
void InitialiseSystemClock();
#endif

