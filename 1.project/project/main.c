#include "sys.h"
#include "KALMAN.h"

#define _Number 1480

//int main()
//{
//  Sys_Init();
//  while(1)
//  {
//    Sys_Run();
//  }
//}
///////////////////////////////////////////////////////////////////////////////
//

//
float Vrms;
float Irms;
float sampleI;
float filteredI;
float sqI,sumI;              
float startV;  
//float ICAL = 27.8;
float offsetI = 2048; 
float value_adc_kalman;
float sum_value = 0.0;
float value_adc1 = 0;
float value_adc = 0;
float value; 
float value_kalman = 0.0; 
int i = 0;



float calcIrms1(unsigned int Number_of_Samples, float ICAL)
{
   int SupplyVoltage=5000;

  for (unsigned int n = 0; n < Number_of_Samples; n++){
    value_adc = MCP3208x0_AnalogRead(6);
    sampleI = updateEstimate(0,value_adc);
    offsetI = (float)(offsetI + (sampleI-offsetI)/2048);
    filteredI = (float)sampleI - offsetI;

    sqI = (float)filteredI * filteredI;
    sumI = (float) sumI+sqI;
  }

  float I_RATIO = (float)ICAL *((SupplyVoltage/1000.0) / (2048));
  Irms = (float)I_RATIO * sqrt(sumI / Number_of_Samples);

  //Reset accumulators
  sumI = 0;
  //--------------------------------------------------------------------------------------

  return Irms;
}


int main(){
  
  InitialiseSystemClock();
  UART_Init(57600);
  SimpleKalmanFilter(0, 1, 1, 0.01);
  MCP3208_Init();

   // SimpleKalmanFilter(0, 1, 1, 0.15);

  //Fn_Delayms(2000);
  while(1){
    value = calcIrms1(1480,124.00069);
    UART_Send_String("value: ");
    UART_Send_Number(value*1000);
    UART_Send_String(" (mA)\n");
    Fn_Delayms(100);
   
//   value_adc = MCP3208x0_AnalogRead(6);
//   value_kalman = updateEstimate(0,value_adc);
//   UART_Send_String("ADC: ");
//   UART_Send_Number(value_kalman);
//   UART_Send_String("\n");
//   Fn_Delayms(1000);
  }
}