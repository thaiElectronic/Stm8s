#include "DELAY.H"


void Fn_Delayus(unsigned int _vrui_Delayus)
{
    unsigned short delay_loops;
    register unsigned short i;

    delay_loops = (_vrui_Delayus + 3) / 5 * CYCLES_PER_US; 

    for (i = 0; i < delay_loops; i++)
    {
        ;
    }
}


void Fn_Delayms(unsigned int _vrui_Delayms)
{
    while (_vrui_Delayms--)
    {
        Fn_Delayus(1000);
    }
}