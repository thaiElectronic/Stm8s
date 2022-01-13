#include "timer.h"

char vruc_Stt = 0;
volatile unsigned char vruc_Count = 0;
void TIMER4_Init(void)
{
  TIM2->PSCR = 0x0A; 
  //15625 * 1s = 15625 =0x3D09
  TIM2->ARRH = 0x3D; // 8 bit high
  TIM2->ARRL = 0x09; // 8 bit low
  TIM2->IER = 0x01;  // Update interrupt enabled
  TIM2->CR1 = 0x01;  // Counter enabled
}

 //sINTERRUPT_HANDLER(TIM2_UPD_OVF_BRK_IRQHandler, 13)
 //{
   //if(vruc_Count == 100)
   //{
 //   vruc_Stt =! vruc_Stt;
   // vruc_Count = 0;
   //}
   // vruc_Count++;
    // if(vruc_Stt)
//      GPIO_WriteHigh(GPIOB, GPIO_PIN_7);
    //else
    //  GPIO_WriteLow(GPIOB, GPIO_PIN_7);
 // TIM2->SR1 = (0<<0);
// }