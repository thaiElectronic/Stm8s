
#include "sys.h"

#define PIN_COI_CHIP    GPIO_PIN_6
#define PORT_COI_CHIP   GPIOB

#define PIN_RELAY1      GPIO_PIN_0
#define PIN_RELAY2      GPIO_PIN_1

#define PROT_RELAY_LED     GPIOE // 2 relay chung port



#define PIN_LED_RED     GPIO_PIN_3
#define PIN_LED_BLUE    GPIO_PIN_2
#define PROT_LED        GPIOE // 2 led chung port


int main( void ){
  
  InitialiseSystemClock();
  UART_Init(9600);
//TIMER4_Init();
  MCP3208_Init();
//GPIO_Init(GPIOB, GPIO_PIN_7, GPIO_MODE_OUT_PP_LOW_FAST);
//enableInterrupts();

  while (1){

//GPIO_WriteLow(PROT_RELAY_LED, PIN_RELAY2);
//GPIO_WriteLow(PROT_RELAY_LED, PIN_RELAY1);
//GPIO_WriteLow(PROT_RELAY_LED, PIN_LED_RED);
//Fn_Delayms(1000);
//GPIO_WriteHigh(PROT_RELAY_LED, PIN_RELAY1);
//GPIO_WriteHigh(PROT_RELAY_LED, PIN_RELAY2);
//GPIO_WriteHigh(PROT_RELAY_LED, PIN_LED_RED);
//Fn_Delayms(1000);
  MCP3208_Test();
  Fn_Delayms(1000);
  }
}
/*
#include "sys.h"
#include "STM8S.h"
#include "SSD1306.h"
unsigned char buffer[buffer_size];
void setup_clock(void);
void setup_GPIOs(void);
void main(void)
{
     unsigned char p = 0;
     signed int i = -9;
     float f = -10.0;
     setup_clock();
     setup_GPIOs();
     OLED_init();
     while(1)
     {
         i = -9;
         f = -10.0;
         OLED_fill(0x00);
         OLED_fill(0xFF);
         Fn_Delayms(600);
         OLED_fill(0xAA);
         Fn_Delayms(600);
         OLED_fill(0x55);
         Fn_Delayms(600);
         OLED_clear_buffer();
         OLED_fill(0x00);
         OLED_print_string(36, 0, "MicroArena");
         OLED_print_string(16, 1, "fb.com/MicroArena");
         Draw_Line(0, 19, 127, 19, ON);
         Draw_Line(0, 60, 127, 60, ON);
         Fn_Delayms(900);
         Draw_Line(3, 16, 3, 63, ON);
         Draw_Line(124, 16, 124, 63, ON);
         Fn_Delayms(900);
         Draw_Rectangle(122, 58, 5, 21, OFF, ON, SQUARE);
         Fn_Delayms(900);
         Draw_Circle(63, 40, 7, ON, ON);
         Fn_Delayms(2000);
         OLED_fill(0x00);
         OLED_clear_buffer();
         OLED_print_string(36, 0, "SShahyriar");
         Draw_Rectangle(27, 21, 100, 58, ON, ON, ROUND);
         Fn_Delayms(900);
         Draw_Circle(63, 40, 9, ON, OFF);
         Fn_Delayms(2000);
         OLED_fill(0x00);
         OLED_clear_buffer();
         for(p = 0; p < 254; p++)
         {
             f += 0.1;
             i += 1;
             OLED_print_float(42, 2, f, 1);
             OLED_print_int(42, 3, i);
             OLED_print_chr(42, 4, p);
             Fn_Delayms(99);
         }
     };
}
void setup_clock(void)
{
       CLK_DeInit();
       CLK_HSECmd(ENABLE);
       while(CLK_GetFlagStatus(CLK_FLAG_HSERDY) == 0);
       CLK_LSICmd(DISABLE);
       CLK_HSICmd(ENABLE);
       while(CLK_GetFlagStatus(CLK_FLAG_HSIRDY) == 0);
       CLK_ClockSwitchCmd(ENABLE);
       CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV8);
       CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
       CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSE,
       DISABLE, CLK_CURRENTCLOCKSTATE_ENABLE);
       CLK_PeripheralClockConfig(CLK_PERIPHERAL_I2C, ENABLE);
        CLK_PeripheralClockConfig(CLK_PERIPHERAL_SPI, DISABLE);
       CLK_PeripheralClockConfig(CLK_PERIPHERAL_ADC, DISABLE);
       CLK_PeripheralClockConfig(CLK_PERIPHERAL_AWU, DISABLE);
       CLK_PeripheralClockConfig(CLK_PERIPHERAL_UART2, DISABLE);
       CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER1, DISABLE);
       CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2, DISABLE);
       CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER3, DISABLE);
       CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4, DISABLE);
}
void setup_GPIOs(void)
{
       GPIO_DeInit(I2C_PORT);
}
*/
