
#ifndef __SYS_H__
#define __SYS_H__
/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "sys_define.h"
#include "sensor_gpio.h"
#include "mcp3208.h"
#include "timer.h"
#include "delay.h"
#include "uart.h"
#include "math.h"
#include "json-maker.h"
#include "tiny-json.h"
#include "KALMAN.h"


#define PIN_MC38        GPIO_PIN_3
#define PORT_MC38       GPIOE
#define PIN_PHAO        GPIO_PIN_2         
#define PORT_PHAO       GPIOE

#define CHANNEL_MQ2     (0u)
#define CHANNEL_NTC     (1u)

#define SR_NUMBER       (20u)

/*Sensor - ADC*/
#define CB0             "MQ5"
#define CB1             "NTC"

/*Sensor - I/O*/
#define CB16            "MC38" // cam bien mo cua
#define CB17            "PHAO" // cam bien nuoc
#define CB18            "NULL"
#define CB19            "NULL"

struct Data_Sensor{
  float Value_Sensor;
  char const* Name_Sensor;
  char array_flag;
};

void Sys_Init(void);
void Sensor_Read(void);
void Sensor_Disp(void);
/*
char* json_data( char* dest, char const* name, struct Data_Sensor const* Data_SR );
int data_to_json( char* dest, struct Data_Sensor const* Data_SR );
void Dong_goi_json(char* Name, int Number);
*/
void Dong_goi_json(char* Name, int Number);
void Output(void);
#endif /* __STM8S_UART1_H */
