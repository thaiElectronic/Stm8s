#include "sensor_gpio.h"
#include "sys.h"
SS_TypeInput	vrts_ButtonA, vrts_ButtonB;
void GPIOSENSOR_Init(void)
{
  GPIO_Init(PORT_MC38, PIN_MC38, GPIO_MODE_IN_PU_NO_IT);
  GPIO_Init(PORT_PHAO, PIN_PHAO, GPIO_MODE_IN_PU_NO_IT);
}

void GPIOSENSOR_ReadInput(unsigned char vruc_Input, SS_TypeInput *vrts_DataInput)
{
  vrts_DataInput->vruc_DataOld = vruc_Input;
  if(!vruc_Input)
  {
    if(vrts_DataInput->vruc_DataOld == vruc_Input)
    {
      if(vrts_DataInput->vruc_CountAccess <= 1000)
      {
        vrts_DataInput->vruc_CountAccess++;
        if(vrts_DataInput->vruc_CountAccess == 20)
        {
          vrts_DataInput->vruc_FlagChange = 1;
        }
      }
    }
    else
    {
      vrts_DataInput->vruc_CountAccess = 0;
    }
  }
  else
  {
    vrts_DataInput->vruc_CountAccess = 0;
  }
}