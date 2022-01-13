#include "sys.h"
#include "uart_frame.h"

#include "KALMAN.h"
float vrui_Get_Value[20];
float vrui_Value_Kalman[20];
char vruc_Receive_Data[200];
 unsigned int vrui_Counter = 0;
volatile unsigned char Flag_Read = 0;

unsigned int vrui_CountTimeSendData = 0;

void SYS_IWDTInit (void);
void SYS_IWDRReLoad (void);

void SYS_IWDTInit (void)
{
     IWDG->KR = 0xcc; //Start independent watchdog  
     IWDG->KR = 0x55; //Write to unlock  
     IWDG->PR = 0x06; //256 frequency division
     IWDG->RLR = 124; //Set the reload register
     IWDG->KR = 0xaa; //Lock and refresh
}

void SYS_IWDRReLoad (void)
{
    IWDG->KR = 0xAA;
}


void Sys_Init(void){
  int i = 0;
  InitialiseSystemClock();
  UART_Init(9600);
  TIM4_Init();
  GPIOSENSOR_Init();
  MCP3208_Init();
  for(i=0;i<16;i++){
    SimpleKalmanFilter(i, 1, 1, 0.01);
  }
  enableInterrupts();
  LED_RED_ON;
  LED_BLUE_ON;
  SYS_IWDTInit();
}

float Vrms;
float Irms;
float sampleI;
float filteredI;
float sqI,sumI;               
float ICAL = 124.00069;
float offsetI = 2048; 
float current_adc = 0.0;
int counter = 0;
//float calcIrms1(unsigned int Number_of_Samples, float ICAL)
//{
//   int SupplyVoltage=5000;
//
//  for (unsigned int n = 0; n < Number_of_Samples; n++){
//    current_adc = MCP3208x0_AnalogRead(5);
//    sampleI = updateEstimate(0,current_adc);
//    offsetI = (float)(offsetI + (sampleI-offsetI)/2048);
//    filteredI = (float)sampleI - offsetI;
//
//    sqI = (float)filteredI * filteredI;
//    sumI = (float) sumI+sqI;
//  }
//
//  float I_RATIO = (float)ICAL *((SupplyVoltage/1000.0) / (2048));
//  Irms = (float)I_RATIO * sqrt(sumI / Number_of_Samples);
//
//  //Reset accumulators
//  sumI = 0;
//  //--------------------------------------------------------------------------------------
//
//  return Irms;
//}


void Sys_Run(void){
  SYS_IWDRReLoad();
  if(vrui_CountTimeSendData >= TIME_SEND)
  {
    if(Flag_Read == 1){  
      create_string_data(vrui_Value_Kalman,vruc_Receive_Data);
       
      UART_Send_String(vruc_Receive_Data);
      Flag_Read = 0;
    }
    vrui_CountTimeSendData = 0;
  }
  
  if(UART_Flag())
  {
    detect_string(RRX);
    GPIOSENSOR_ControlRelay(vrcr_RelayStt.Relay0, RELAY0);
    GPIOSENSOR_ControlRelay(vrcr_RelayStt.Relay1, RELAY1);
  }
  
  vrui_CountTimeSendData++;
  Fn_Delayms(1);
}

INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23){
  TIM4->SR1 = 0;
  vrui_Counter++;
  if(vrui_Counter <= 8)
  {   
    if(vrui_Counter-1 == 6){
      //current_adc(vrui_Counter-1,vrui_Counter-1);
      current_adc = MCP3208x0_AnalogRead(vrui_Counter-1);
      sampleI = updateEstimate(vrui_Counter-1,current_adc);
      offsetI = (float)(offsetI + (sampleI-offsetI)/2048);
      filteredI = (float)sampleI - offsetI;

      sqI = (float)filteredI * filteredI;
      sumI = (float) sumI+sqI;
      counter++;
      if(counter > 1480){
        float I_RATIO = (float)ICAL *((5000/1000.0) / (2048));
        Irms = (float)I_RATIO * sqrt(sumI / 1480);

        vrui_Value_Kalman[vrui_Counter-1] = Irms*1000; //mA
        //Reset accumulators
        sumI = 0;
        counter = 0;
      }
    }
    else{
      vrui_Get_Value[vrui_Counter-1] = MCP3208x0_AnalogRead(8 - vrui_Counter);
      vrui_Value_Kalman[vrui_Counter-1] = updateEstimate(vrui_Counter-1, vrui_Get_Value[vrui_Counter-1]);      
    }
  }
  
  
  else if(vrui_Counter >= 9 && vrui_Counter <= 16)
  { 
    vrui_Get_Value[vrui_Counter-1] = MCP3208x1_AnalogRead(16 - vrui_Counter);
    vrui_Value_Kalman[vrui_Counter-1] = updateEstimate(vrui_Counter-1, vrui_Get_Value[vrui_Counter-1]);
  }
  
  else if(vrui_Counter >= 17 && vrui_Counter <= SR_NUMBER)
  {
    if((vrui_Counter-1) == 16)
    {
      vrui_Value_Kalman[vrui_Counter-1] = GPIO_ReadInputPin(PORT_PHAO,PIN_PHAO);
    }
    else if((vrui_Counter-1) == 17)
    {
      vrui_Value_Kalman[vrui_Counter-1] = GPIO_ReadInputPin(PORT_MC38,PIN_MC38);
    }
  }
  else if(vrui_Counter > SR_NUMBER)
  {
    vrui_Counter = 0;
    Flag_Read = 1;
  }    

  TIM4_ClearITPendingBit(TIM4_FLAG_UPDATE);
}
