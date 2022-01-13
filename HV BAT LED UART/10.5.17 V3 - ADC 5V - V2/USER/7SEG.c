/*
 * _7SEG.c
 *
 * Created: 10/11/2014 4:15:27 PM
 *  Author: Duan
 */ 

#include "7SEG.h"


unsigned char vruc_7SEG_Ram2Disp[MAXLED];
unsigned char vruc_7SEG_CountLED;
unsigned int  vrui_7SEG_Count2Blink;
const unsigned char vruc_7SEG_Number[14] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f,0x00,0x1C/*U*/,0x33/*R*/,0x54/*N*/};

unsigned char Fn_7SEG_Dec2Seg (unsigned char _vruc_Data)
{
    return(~vruc_7SEG_Number[_vruc_Data]);
}

void Fn_7SEG_OutData (unsigned char _vruc_Data)
{
	/* A */
	if (_vruc_Data & 0x01)
	{
	    PINLED_A = 1;
	} 
	else
	{
	    PINLED_A = 0;
	}
	/* B */
	if (_vruc_Data & 0x02)
	{
	    PINLED_B = 1;
	} 
	else
	{
	    PINLED_B = 0;
	}
	/* C */
	if (_vruc_Data & 0x04)
	{
	    PINLED_C = 1;
	} 
	else
	{
	    PINLED_C = 0;
	}
	/* D */
	if (_vruc_Data & 0x08)
	{
	    PINLED_D = 1;
	} 
	else
	{
	    PINLED_D = 0;
	}
	/* E */
	if (_vruc_Data & 0x10)
	{
	    PINLED_E = 1;
	} 
	else
	{
	    PINLED_E = 0;
	}
	/* F */
	if (_vruc_Data & 0x20)
	{
	    PINLED_F = 1;
	} 
	else
	{
	    PINLED_F = 0;
	}
	/* G */
	if (_vruc_Data & 0x40)
	{
	    PINLED_G = 1;
	} 
	else
	{
	    PINLED_G = 0;
	}
	/* DP */
	if (_vruc_Data & 0x80)
	{
	    PINLED_DP = 1;
	} 
	else
	{
	    PINLED_DP = 0;
	}
}

void Fn_7SEG_Control (unsigned char _vruc_Cmd)
{
	if (_vruc_Cmd & 0x01)
	{
		PINLED_1 = 1;
	} 
	else
	{
		PINLED_1 = 0;
	}
	/****************************************/
	if (_vruc_Cmd & 0x02)
	{
		PINLED_2 = 1;
	} 
	else
	{
		PINLED_2 = 0;
	}
	/****************************************/
	if (_vruc_Cmd & 0x04)
	{
		PINLED_3 = 1;
	} 
	else
	{
		PINLED_3 = 0;
	}
	/****************************************/
}





void Fn_7SEG_Display (void)
{
	Fn_7SEG_Control(0x0F);
    vruc_7SEG_CountLED++;
	if(vruc_7SEG_CountLED >= MAXLED)
	{
		vruc_7SEG_CountLED = 0;
	}
	if(vruc_7SEG_Ram2Disp[vruc_7SEG_CountLED] & 0x80)
	{
		Fn_7SEG_OutData((Fn_7SEG_Dec2Seg(vruc_7SEG_Ram2Disp[vruc_7SEG_CountLED]-0x80) & 0x7F));
	}
	else
	{
		Fn_7SEG_OutData((Fn_7SEG_Dec2Seg(vruc_7SEG_Ram2Disp[vruc_7SEG_CountLED])));
	}
	Fn_7SEG_Control((1<<vruc_7SEG_CountLED));
}

void Fn_7SEG_Init (void)
{
	vruc_7SEG_Ram2Disp[0] =12;
	vruc_7SEG_Ram2Disp[1] =11;
	vruc_7SEG_Ram2Disp[2] =13;
}