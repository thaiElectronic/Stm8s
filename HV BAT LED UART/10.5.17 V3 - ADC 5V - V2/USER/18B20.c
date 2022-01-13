

#include "18b20.H"


void delay_us(unsigned int Time)
{
	unsigned int i,j;
	for(i=0;i<Time;i++)
	{
		for(j=0;j<32;j++);
	}
}



void Fn_18B20_Init (void){
 //   unsigned char vruc_Return;
    DQ_DIR = 1;
    DQ_OUT = 1 ;      
    delay_us(8);   
    DQ_OUT = 0 ;     
    delay_us(90) ;   
    DQ_OUT = 1 ; 
    DQ_DIR = 0;
    delay_us(8) ;
//    vruc_Return = DQ_IN ;
    delay_us(100);
    DQ_DIR = 1;
    DQ_OUT = 1 ;
}
unsigned char Fn_18B20_ReadByte(void){
    unsigned char i = 0 ;
    unsigned char Data = 0 ;
    for (i = 8 ; i > 0 ; i--)
    {
        DQ_DIR = 1;
        DQ_OUT = 0 ;
        Data >>= 1 ;
        DQ_OUT = 1 ;
        DQ_DIR = 0;
        if(DQ_IN){
            Data |= 0x80 ;
        }
        delay_us(4) ;
    }
    return (Data) ;
}


void Fn_18B20_WriteByte(unsigned char _vruc_Data){
    unsigned char i = 0 ;
    DQ_DIR = 1;
    for (i = 8 ; i > 0 ; i--)
    {
        DQ_OUT = 0 ;
        if(_vruc_Data&0x01){
            DQ_OUT = 1;
        }
        delay_us(5) ;
        DQ_OUT = 1 ;
        _vruc_Data>>=1 ;
    }
}


float Fn_1820_Read(void){
    float temp;
    unsigned char a,b;
    Fn_18B20_Init();										// Khoi tao DS18b20
    Fn_18B20_WriteByte(0xCC) ;  				// Cho phep VDK truy cap thang den cac lenh bo nho cua DS18b20
    Fn_18B20_WriteByte(0x44) ; 				// Khoi dong qua trinh do va chuyen doi nhiet do ra so nhi phan
    //Fn_DELAY_Short(200);
    Fn_18B20_Init();
    Fn_18B20_WriteByte(0xCC) ;  
    Fn_18B20_WriteByte(0xBE) ;					// Cho phep doc du lieu tu bo nho DS18b20 ra ngoai

    a = Fn_18B20_ReadByte(); 
    temp=((float)(a&0x0f))/16.0;				// Lay phan thuc cua gia tri nhiet do
    b = Fn_18B20_ReadByte(); 				
    a =((a&0xf0)>>4)|((b&0x0f)<<4) ;	// Lay phan nguyen cua gia tri nhiet do
    temp=temp+a;
    return temp;											// Tra ve gia tri nhiet do
}



