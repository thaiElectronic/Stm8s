#include "sensor_gpio.h"
#include "sys.h"

void GPIOSENSOR_Init(void){
/*---------------------------------Init GPIO Open door---------------------------------*/
  GPIO_Init(PORT_MC38, PIN_MC38, GPIO_MODE_IN_PU_NO_IT);
/*---------------------------------Init GPIO water---------------------------------*/
  GPIO_Init(PORT_PHAO, PIN_PHAO, GPIO_MODE_IN_PU_NO_IT);
/*---------------------------------Init GPIO buzzz---------------------------------*/  
//  GPIO_Init(PORT_COI_CHIP, PIN_COI_CHIP, GPIO_MODE_OUT_PP_LOW_FAST);
/*---------------------------------Init GPIO Relay---------------------------------*/
  GPIO_Init(PROT_RELAY_LED, PIN_LED_BLUE, GPIO_MODE_OUT_PP_HIGH_FAST); 
  GPIO_Init(PROT_RELAY_LED, PIN_LED_RED, GPIO_MODE_OUT_PP_HIGH_FAST);  
/*---------------------------------Init GPIO LED power---------------------------------*/
  GPIO_Init(PROT_RELAY_LED, PIN_RELAY1, GPIO_MODE_OUT_PP_HIGH_FAST);
  GPIO_Init(PROT_RELAY_LED, PIN_RELAY2, GPIO_MODE_OUT_PP_HIGH_FAST);
}

void GPIOSENSOR_ControlRelay(unsigned char vruc_stt, unsigned char vruc_mode)
{
  if(vruc_mode)
  {
    if(vruc_stt){
      Relay1_ON;
    }
    else
      Relay1_OFF;
  }
  else
  {
    if(vruc_stt){
      Relay2_ON;
    }
      
    else{
      Relay2_OFF;   
    }
  }
}

