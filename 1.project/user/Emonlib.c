#include "EmonLib.h"
#include "math.h"
#include "delay.h"

extern float Vrms;
extern float Irms;

extern unsigned int inPinI;

extern float ICAL;


extern int sampleI;
extern float filteredI;
extern float offsetI;                          //Low-pass filter output

extern float sqV,sumV,sqI,sumI,instP,sumP;              //sq = squared, sum = Sum, inst = instantaneous

#define ADC_BITS    11


#define ADC_COUNTS  (1<<ADC_BITS)

void current(unsigned int _inPinI, float _ICAL)
{
  _inPinI = _inPinI;
  ICAL = _ICAL;
  offsetI = ADC_COUNTS>>1;
}

//--------------------------------------------------------------------------------------
float calcIrms(unsigned int Number_of_Samples, float _ICAL){
    int SupplyVoltage=5000;
    ICAL = _ICAL;
    offsetI = ADC_COUNTS>>1;

  for (unsigned int n = 0; n < Number_of_Samples; n++){
    sampleI = MCP3208x0_AnalogRead(6);

    offsetI = (offsetI + (sampleI-offsetI)/2048);
    filteredI = sampleI - offsetI;

    sqI = filteredI * filteredI;
  
    sumI += sqI;
  }

  float I_RATIO = ICAL *((SupplyVoltage/1000.0) / (2048));
  Irms = I_RATIO * sqrt(sumI / Number_of_Samples);

  sumI = 0;
  //--------------------------------------------------------------------------------------

  return Irms;
}

void current1(unsigned int _inPinI, float _ICAL)
{
  _inPinI = _inPinI;
  ICAL = _ICAL;
  offsetI = ADC_COUNTS>>1;
}
//--------------------------------------------------------------------------------------
float calcIrms1(unsigned int Number_of_Samples, float _ICAL)
{
   int SupplyVoltage=5000;

  for (unsigned int n = 0; n < Number_of_Samples; n++)
  {
    sampleI = analogRead(inPinI);

    offsetI = (offsetI + (sampleI-offsetI)/1024);
    filteredI = sampleI - offsetI;

    sqI = filteredI * filteredI;
    sumI += sqI;
  }

  float I_RATIO = ICAL *((SupplyVoltage/1000.0) / (ADC_COUNTS));
  Irms = I_RATIO * sqrt(sumI / Number_of_Samples);

  //Reset accumulators
  sumI = 0;
  //--------------------------------------------------------------------------------------

  return Irms;
}

