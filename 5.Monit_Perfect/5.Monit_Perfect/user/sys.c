#include "sys.h"
int i;
int vri_i;
int value;
unsigned int vrui_Get_Value[20];
unsigned int vrui_Value_Kalman[20];
unsigned int vrui_Counter = 0;
unsigned int Flag_Read = 0;

char *Name_sensor[SR_NUMBER]= {CB0, CB1,"CB2", "CB3", "CB4", "CB5", "CB6","CB7", "CB8", "CB9", "CB10", "CB11", "CB12",
                        "CB13", "CB14", "CB15", CB16, CB17, CB18, CB19}; 


/*
char *Name_sensor[20]= {CB1, CB2,"CB3", "CB4", "CB5", "CB6", "CB7","CB8", "CB9", "CB10", "CB11", "CB12",
                        "CB13", "CB14", "CB15", "CB16"}; 

struct Data_Sensor{
  float Value_Sensor;
  char const* Name_Sensor;
  char array_flag;
};

*/


  
INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23){
  TIM4->SR1 = 0 ; // Xóa d?u ng?t
  vrui_Counter++;
  if(vrui_Counter <= 8){
    vrui_Get_Value[vrui_Counter-1] = MCP3208x0_AnalogRead(vrui_Counter-1);
   // vrui_Value_Kalman[vrui_Counter-1] = updateEstimate(vrui_Get_Value[vrui_Counter-1]);
  }
  else if(vrui_Counter >=9 && vrui_Counter <= 16){
    vrui_Get_Value[vrui_Counter-1] = MCP3208x1_AnalogRead(vrui_Counter-9);
   // vrui_Value_Kalman[vrui_Counter-1] = updateEstimate(vrui_Get_Value[vrui_Counter-1]);
  }
  else if(vrui_Counter >= 17 && vrui_Counter <= SR_NUMBER){
    if((vrui_Counter-1) == 16){
      vrui_Get_Value[vrui_Counter-1] = GPIO_ReadInputPin(PORT_MC38,PIN_MC38);
    }
    else if((vrui_Counter-1) == 17){
      vrui_Get_Value[vrui_Counter-1] = GPIO_ReadInputPin(PORT_PHAO,PIN_PHAO);
    }
  }
  else if(vrui_Counter >= SR_NUMBER){
    vrui_Counter = 0;
    Flag_Read = 1;
  }
  TIM4_ClearITPendingBit(TIM4_FLAG_UPDATE);
//  TIM4_Cmd(DISABLE);
}

char* json_data( char* dest, char const* name, struct Data_Sensor const* Data_SR ) { 
    dest = json_objOpen( dest, NULL );
 //   dest = json_str( dest, "Name",  Data_SR-> Name_Sensor );
    dest = json_int( dest, name, Data_SR->Value_Sensor );
    dest = json_objClose( dest );
    return dest;
}

int data_to_json( char* dest, char const* name, struct Data_Sensor const* Data_SR ) {
    char* p = json_data( dest, name, Data_SR );
    p = json_end( p );
    return p - dest;
}

void Dong_goi_json(char* Name, int Number){
  
  value = vrui_Get_Value[Number];
  
  if(Number == 16 || Number == 17){
    if(value >= 1) value = 1;
  }
   //value = vrui_Get_Value[Number];
   
  
  struct Data_Sensor const Data_SR = {
 //     .Name_Sensor     = Name,
      .Value_Sensor	= value,     
    };
   char buff[512];
    
   int len = data_to_json( buff, Name, &Data_SR );    
   UART_Send_String( buff);
   UART_Send_String("\n");
}

void Sys_Init(void){
  InitialiseSystemClock();
  UART_Init(9600);
  TIM4_Init();
//GPIO_Init(GPIOE,GPIO_PIN_3, GPIO_MODE_OUT_PP_LOW_FAST);
//TIM2_Init();
  GPIOSENSOR_Init();
  MCP3208_Init();
  SimpleKalmanFilter(1, 1, 0.1);
  enableInterrupts();
}

/*
INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23){
  vrui_Counter++;
  if(vrui_Counter < 8){
    vrui_Get_Value[vrui_Counter-1] = MCP3208x0_AnalogRead(vrui_Counter-1);
  }
  else if(vrui_Counter >=8 && vrui_Counter < 16){
    vrui_Get_Value[vrui_Counter-1] = MCP3208x1_AnalogRead(vrui_Counter-1);
  }
  else if(vrui_Counter >= 16){
    vrui_Counter = 0;
    Flag_Read = 1;
  }
  TIM4_ClearITPendingBit(TIM4_FLAG_UPDATE);
}
*/



void Output(void){
  if(Flag_Read == 1){
      Flag_Read = 0;
      for( i = 0; i < SR_NUMBER; i++){
        Dong_goi_json(Name_sensor[i],i);     
      }
      UART_Send_String("----------------------------");
         UART_Send_String("\n");
     // Sensor_Disp();
    }
  Fn_Delayms(1000);
//  TIM4_Cmd(ENABLE);
}

void Sensor_Disp(void){
  for(vri_i = 0; vri_i < 16; vri_i++){
    if(vri_i < 8){
      UART_Send_String("CB");
      UART_Send_Number(vri_i);
      UART_Send_String(": ");
      UART_Send_Number(vrui_Get_Value[vri_i]);
      UART_Send_String("\n");
    }
    if(vri_i >= 8 && vri_i < 16){
      UART_Send_String("CB");
      UART_Send_Number(vri_i);
      UART_Send_String(": "); 
      UART_Send_Number(vrui_Get_Value[vri_i]);
      UART_Send_String("\n");
    }
  }
}


