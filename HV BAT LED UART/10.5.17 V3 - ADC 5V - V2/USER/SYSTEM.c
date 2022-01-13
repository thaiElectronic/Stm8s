
#include "SYSTEM.h"

unsigned char counter1 = 0, counter2 = 0;
unsigned char signal_in = FALSE, pulseUpDown = up;
unsigned char receivedBits = 0; 
unsigned char dataBuffer[10]; //1 byte ID, 4 bytes RFID Tag serial number, 1 byte line parity, 4 bytes column parity bits.
unsigned char parity,colParity;

unsigned char vruc_n;
char Number[3];

//==============================================================================
/* Ham cau hinh Clock cho he thong */
void CLK_Config(void)
{
    CLK_DeInit();
   // CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV8);      //f_Master = HSI/8 = 2 MHz
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
//    CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV2);            //f_CPU = f_Master/2 = 1 MHz
//    while(CLK_GetFlagStatus(CLK_FLAG_HSIRDY)!=SET);     //wait until HSI ready
}
//==============================================================================
void GPIO_Config(void) /* Ham cau hinh  GPIO */
{
  GPIO_DeInit(GPIOD);
// Initialize I/Os 
  GPIO_Init(GPIOC,(GPIO_Pin_TypeDef)(GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7),GPIO_MODE_OUT_PP_HIGH_FAST); //LED
  GPIO_Init(GPIOD,(GPIO_Pin_TypeDef)(GPIO_PIN_1|GPIO_PIN_4),GPIO_MODE_OUT_PP_HIGH_FAST); //LED
  GPIO_Init(GPIOA,(GPIO_Pin_TypeDef)(GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3),GPIO_MODE_OUT_PP_HIGH_FAST); //LED
  GPIO_Init(GPIOB,(GPIO_Pin_TypeDef)(GPIO_PIN_4|GPIO_PIN_5),GPIO_MODE_OUT_PP_HIGH_FAST); //LED
}

//==============================================================================
void EXTI_Config(void)
{
  GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_IN_PU_IT);  // input data
  GPIO_Init(GPIOD, GPIO_PIN_2, GPIO_MODE_IN_PU_IT);  // input data
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD, EXTI_SENSITIVITY_FALL_ONLY); // INPUT ngat kich phat suon xuong
  EXTI_SetTLISensitivity(EXTI_TLISENSITIVITY_FALL_ONLY);
}
//==============================================================================
/*
   - TIM2_CH1  pin (PD.4)  
   Các TIM2CLK là 16MHz, các Prescaler là 1 nên TIM2 clock truy câp là 16MHz.

   Các TIM2 f= 16 KHz: TIM2 Frequency = TIM2 clock counter / (ARR + 1)
   TIM2 là 125KHz.
   Các TIM2 CCR1 gia tri dang ky 500, nên TIM2 Channel 2 Kênh 1 tao ra  mot
   tin hieu PWM voi tan so 2KHz và mot chu ky nhiem 50%:
   Chu ky nhiem vu TIM2 Channel1 = [TIM2_CCR1 / (TIM2_ARR + 1)] * 100 = 50% 
*/
void TIM2_PWM1_Config(uint16_t CCR1_Value)
{
  /* Time base configuration */
  TIM2_TimeBaseInit(TIM2_PRESCALER_128, 799);
//  /* PWM1 Mode configuration: Channel1 */ 
//  TIM2_OC1Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,CCR1_Value, TIM2_OCPOLARITY_HIGH);
//  TIM2_OC1PreloadConfig(ENABLE);
    /* PWM1 Mode configuration: Channel2 */ 
  TIM2_OC2Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,CCR1_Value, TIM2_OCPOLARITY_HIGH);
  TIM2_OC2PreloadConfig(ENABLE);
  
  TIM2_ARRPreloadConfig(ENABLE);
  /* TIM2 enable counter */
  TIM2_Cmd(ENABLE);
}
//-----------------------------------
void TIM2_PWM2(uint16_t TIM2_Pulse)
{
//    /* Reset the Output Compare Bits & Set the Output Compare Mode */
//  TIM2->CCMR3 = (uint8_t)((uint8_t)(TIM2->CCMR3 & (uint8_t)(~TIM2_CCMR_OCM)) |
//                          (uint8_t)TIM2_OCMode);
  /* Set the Pulse value */
  TIM2->CCR2H = (uint8_t)(TIM2_Pulse >> 8);
  TIM2->CCR2L = (uint8_t)(TIM2_Pulse);
}
//==============================================================================
void TIM4_Config(void)
{
  /* TIM4 configuration:
   - TIM4CLK is set to 16 MHz, the TIM4 Prescaler is equal to 128 so the TIM1 counter
   clock used is 16 MHz / 128 = 125 000 Hz
  - With 125 000 Hz we can generate time base:
      max time base is 2.048 ms if TIM4_PERIOD = 255 --> (255 + 1) / 125000 = 2.048 ms
      min time base is 0.016 ms if TIM4_PERIOD = 1   --> (  1 + 1) / 125000 = 0.016 ms
  - In this example we need to generate a time base equal to 1 ms
   so TIM4_PERIOD = (0.001 * 125000 - 1) = 124 */

  /* Time base configuration */
  TIM4_TimeBaseInit(TIM4_PRESCALER_128, 249); //500Hz
  /* Clear TIM4 update flag */
  TIM4_ClearFlag(TIM4_FLAG_UPDATE);
  /* Enable update interrupt */
  TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
  
  /* enable interrupts */
//  enableInterrupts();

  /* Enable TIM4 */
  TIM4_Cmd(ENABLE);
}
//==============================================================================
void UART1_Config(void)
{
  UART1_Init((uint32_t)115200, UART1_WORDLENGTH_8D,UART1_STOPBITS_1, UART1_PARITY_NO,
                   UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);
  UART1_ITConfig(UART1_IT_RXNE_OR, ENABLE);
  UART1_Cmd(ENABLE);
}
//==============================================================================
void SPI_init(void)
{
  /* SPI configuration */
  SPI_DeInit();
  SPI->CR2 = SPI_CR1_SPE; 
  SPI_Init(SPI_FIRSTBIT_MSB, SPI_BAUDRATEPRESCALER_2, SPI_MODE_SLAVE, SPI_CLOCKPOLARITY_LOW,
           SPI_CLOCKPHASE_1EDGE, SPI_DATADIRECTION_2LINES_FULLDUPLEX, SPI_NSS_SOFT,(uint8_t)0x07);

  SPI->CR2 = 0;    // Chan SS dieu khien bang phan mem
  SPI->ICR = SPI_ICR_RXEI;    // Cho phep ngat truyen nhan SPI
  SPI_Cmd(ENABLE);
}
//==============================================================================
void ADC1_Config(void)
{
//  /*  Init GPIO for ADC2 */ 
    GPIO_Init(GPIOD,(GPIO_Pin_TypeDef)(GPIO_PIN_5|GPIO_PIN_6),GPIO_MODE_IN_FL_NO_IT); 
//    //Channel 0
//    ADC1_Init( ADC1_CONVERSIONMODE_SINGLE ,  ADC1_CHANNEL_0,  ADC1_PRESSEL_FCPU_D2,  ADC1_EXTTRIG_GPIO,  DISABLE,  ADC1_ALIGN_RIGHT,  ADC1_SCHMITTTRIG_ALL,  DISABLE); 
//    //Channel 1
//    ADC1_Init( ADC1_CONVERSIONMODE_SINGLE ,  ADC1_CHANNEL_1,  ADC1_PRESSEL_FCPU_D2,  ADC1_EXTTRIG_GPIO,  DISABLE,  ADC1_ALIGN_RIGHT,  ADC1_SCHMITTTRIG_ALL,  DISABLE); 
//    //Channel 2
//    ADC1_Init( ADC1_CONVERSIONMODE_SINGLE ,  ADC1_CHANNEL_2,  ADC1_PRESSEL_FCPU_D2,  ADC1_EXTTRIG_GPIO,  DISABLE,  ADC1_ALIGN_RIGHT,  ADC1_SCHMITTTRIG_ALL,  DISABLE);
    //Channel 3
    ADC1_Init( ADC1_CONVERSIONMODE_SINGLE ,  ADC1_CHANNEL_3,  ADC1_PRESSEL_FCPU_D2,  ADC1_EXTTRIG_GPIO,  DISABLE,  ADC1_ALIGN_RIGHT,  ADC1_SCHMITTTRIG_ALL,  DISABLE);
    //Channel 4
    ADC1_Init( ADC1_CONVERSIONMODE_SINGLE ,  ADC1_CHANNEL_4,  ADC1_PRESSEL_FCPU_D2,  ADC1_EXTTRIG_GPIO,  DISABLE,  ADC1_ALIGN_RIGHT,  ADC1_SCHMITTTRIG_ALL,  DISABLE);
//    //Channel 5
//    ADC1_Init( ADC1_CONVERSIONMODE_SINGLE ,  ADC1_CHANNEL_5,  ADC1_PRESSEL_FCPU_D2,  ADC1_EXTTRIG_GPIO,  DISABLE,  ADC1_ALIGN_RIGHT,  ADC1_SCHMITTTRIG_ALL,  DISABLE);
//    //Channel 6
//    ADC1_Init( ADC1_CONVERSIONMODE_SINGLE ,  ADC1_CHANNEL_6,  ADC1_PRESSEL_FCPU_D2,  ADC1_EXTTRIG_GPIO,  DISABLE,  ADC1_ALIGN_RIGHT,  ADC1_SCHMITTTRIG_ALL,  DISABLE);
}
//==============================================================================
uint16_t get_VR1(void){
    uint8_t tempL = 0;
    uint16_t tempH = 0,ADCValue;
    ADC1->CSR = 3;	
    ADC1->CR1 |= ADC1_CR1_ADON;
    while((ADC1->CSR & ((uint8_t)0x80)) == 0); 
    tempL = ADC1->DRL;
    tempH = ADC1->DRH;
    ADCValue = (tempL | (tempH << 8));
    
    ADC1_ClearFlag(ADC1_FLAG_EOC);
    return ADCValue;
  }
//==============================================================================
uint16_t get_VR2(void){
    uint8_t tempL = 0;
    uint16_t tempH = 0,ADCValue;
    ADC1->CSR = 4;	
    ADC1->CR1 |= ADC1_CR1_ADON;
    while((ADC1->CSR & ((uint8_t)0x80)) == 0); 
    tempL = ADC1->DRL;
    tempH = ADC1->DRH;
    ADCValue = (tempL | (tempH << 8));
    ADC1_ClearFlag(ADC1_FLAG_EOC);
    return ADCValue;
  }
//==============================================================================

//--------------------------------------------
void Control_VR(int VR)
{
  int ADC_VR;
  ADC_VR = VR_num;
  if(ADC_VR > VR+4)Motor_VR(up);
  else if(ADC_VR < VR-4)Motor_VR(down);
  else Motor_VR(stop);
}
//==============================================================================
void Fn_SYS_Init_GPIO (void){
//   CLK->CKDIVR = 0x00;
//   CLK->ECKR &= ~(1<<0);
//   CLK->CCOR &= ~(1<<0);
    
    GPIOA->DDR = 0xFF;
    GPIOA->CR1 = 0xFF;
    GPIOA->CR2 = 0xFF;
    GPIOA->ODR = 0x00;
    
    GPIOB->DDR = 0xFF;
    GPIOB->CR1 = 0xFF;
    GPIOB->CR2 = 0xFF;
    GPIOB->ODR = 0x00;

    GPIOC->DDR = 0xFF;
    GPIOC->CR1 = 0xFF;
    GPIOC->CR2 = 0xFF;
    GPIOC->ODR = 0x00;   
    
    GPIOD->DDR = 0xFF;
    GPIOD->CR1 = 0xFF;
    GPIOD->CR2 = 0xFF;
    GPIOD->ODR = 0x00;
    
    GPIOE->DDR = 0xFF;
    GPIOE->CR1 = 0xFF;
    GPIOE->CR2 = 0xFF;
    GPIOE->ODR = 0x00;  
    
    GPIOF->DDR = 0xFF;
    GPIOF->CR1 = 0xFF;
    GPIOF->CR2 = 0xFF;
    GPIOF->ODR = 0x00;
}
void Fn_STM8_IWDTInit (void){
    IWDG->KR = 0x55;
    IWDG->PR = 6;
    IWDG->RLR = 0xFF;
    IWDG->KR = 0xcc;
    IWDG->KR = 0xAA;
}
void Fn_STM8_IWDRReLoad (void){
    IWDG->KR = 0xAA;
}




void Fn_SYS_NumberLED (unsigned int vrui_Display)
{
    int iNumber;
    iNumber = vrui_Display;
    if(iNumber>=5)       led12=0;
    else led12=1;
    if(iNumber>80)      led11=0;
    else led11=1;
    if(iNumber>155)      led10=0;
    else led10=1;
    if(iNumber>240)      led9=0;
    else led9=1;
    if(iNumber>325)      led8=0;
    else led8=1;
    if(iNumber>410)      led7=0;
    else led7=1;
    if(iNumber>495)      led6=0;
    else led6=1;
    if(iNumber>580)      led5=0;
    else led5=1;
    if(iNumber>665)      led4=0;
    else led4=1;
    if(iNumber>750)      led3=0;
    else led3=1;    
    if(iNumber>835)      led2=0;
    else led2=1;
    if(iNumber>900)     led1=0;
    else led1=1;
}
//------------------------------------------------------------------------------






