#include "RFID.h"

unsigned char serNum[5];       
unsigned char AserNum[5]; 

unsigned char Fn_RFID_SPI_RW(unsigned char Buff)
{
   unsigned char bit_ctr;
   for(bit_ctr=0;bit_ctr<8;bit_ctr++) // output 8-bit
   {
      if(Buff&0x80)
         MOSI = 1;
      else
         MOSI = 0;      
	  Fn_DELAY_Short(1);
      Buff = (Buff << 1);           // shift next bit into MSB..
      SCK = 1;                      // Set SCK high..
      //MOSI = 1;
      if(MISO)
         Buff = Buff|1;               // capture current MISO bit   
	  Fn_DELAY_Short(1);
      SCK = 0;                    // ..then set SCK low again
      //MOSI = 0;
   }
   return(Buff);                   // return read uchar
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
unsigned char Fn_RFID_isCard() 
{
	unsigned char vruc_Status;
	unsigned char str[MAX_LEN];
	
	vruc_Status = Fn_RFID_MFRC522Request(PICC_REQIDL, str);	
    if (vruc_Status == MI_OK) {
		return true;
	} else { 
		return false; 
	}
 }
 //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
unsigned char Fn_RFID_ReadCardSerial()
{	
	unsigned char vruc_Status;
	unsigned char str[MAX_LEN];
	
	vruc_Status = Fn_RFID_Anticoll(str);
	memcpy(serNum, str, 5);
	
	if (vruc_Status == MI_OK) {
		return true;
	} else {
		return false;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Fn_RFID_Init(void)
{
	GPIOC->DDR &= ~(1<<4);     //MISO RFID pin input
	SAD = 0;
	RST_RFID = 1;
	POWER_RFID = 0;
	Fn_RFID_Reset();
	Fn_RFID_WriteMFRC522(TModeReg, 0x8D);		
	Fn_RFID_WriteMFRC522(TPrescalerReg, 0x3E);	
	Fn_RFID_WriteMFRC522(TReloadRegL, 30);           
	Fn_RFID_WriteMFRC522(TReloadRegH, 0);
	Fn_RFID_WriteMFRC522(TxAutoReg, 0x40);
	Fn_RFID_WriteMFRC522(ModeReg, 0x3D);
	Fn_RFID_AntennaOn();		
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Fn_RFID_Reset(void)
{
	Fn_RFID_WriteMFRC522(CommandReg, PCD_RESETPHASE);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Fn_RFID_WriteMFRC522(unsigned char _vruc_addr, unsigned char _vruc_val)
{
	SAD = 0;

	Fn_RFID_SPI_RW ((_vruc_addr<<1)&0x7E);	
	Fn_RFID_SPI_RW (_vruc_val);
	
	SAD = 1;

}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Fn_RFID_AntennaOn(void)
{
	unsigned char vruc_Temp;

	vruc_Temp = Fn_RFID_ReadMFRC522(TxControlReg);
	if (!(vruc_Temp & 0x03))
	{
		Fn_RFID_SetBitMask(TxControlReg, 0x03);
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
unsigned char Fn_RFID_ReadMFRC522(unsigned char _vruc_addr)
{
	unsigned char vruc_Val;
	SAD = 0;
	Fn_RFID_SPI_RW (((_vruc_addr<<1)&0x7E) | 0x80);	
	vruc_Val = Fn_RFID_SPI_RW (0x00);
	SAD = 1;

	return vruc_Val;	
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Fn_RFID_SetBitMask(unsigned char _vruc_reg, unsigned char _vruc_mask)  
{ 
    unsigned char tmp;
    tmp = Fn_RFID_ReadMFRC522(_vruc_reg);
    Fn_RFID_WriteMFRC522(_vruc_reg, tmp | _vruc_mask);  // set bit mask
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Fn_RFID_ClearBitMask(unsigned char _vruc_reg, unsigned char _vruc_mask)  
{
    unsigned char tmp;
    tmp = Fn_RFID_ReadMFRC522(_vruc_reg);
    Fn_RFID_WriteMFRC522(_vruc_reg, tmp & (~_vruc_mask));  // clear bit mask
} 
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Fn_RFID_CalculateCRC(unsigned char *pIndata, unsigned char len, unsigned char *pOutData)
{
    unsigned char i, n;
    Fn_RFID_ClearBitMask(DivIrqReg, 0x04);			//CRCIrq = 0
    Fn_RFID_SetBitMask(FIFOLevelReg, 0x80);		
    for (i=0; i<len; i++)
    {   
		Fn_RFID_WriteMFRC522(FIFODataReg, *(pIndata+i));   
	}
    Fn_RFID_WriteMFRC522(CommandReg, PCD_CALCCRC);

    i = 0xFF;
    do 
    {
        n = Fn_RFID_ReadMFRC522(DivIrqReg);
        i--;
    }
    while ((i!=0) && !(n&0x04));		

    pOutData[0] = Fn_RFID_ReadMFRC522(CRCResultRegL);
    pOutData[1] = Fn_RFID_ReadMFRC522(CRCResultRegM);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
unsigned char Fn_RFID_MFRC522ToCard(unsigned char _vruc_command, unsigned char *sendData, unsigned char _vruc_sendLen, unsigned char *backData, unsigned int *backLen)
{
    unsigned char vruc_Status = MI_ERR;
    unsigned char irqEn = 0x00;
    unsigned char waitIRq = 0x00;
	unsigned char lastBits;
    unsigned char n;
    unsigned int i;

    switch (_vruc_command)
    {
        case PCD_AUTHENT:	
		{
			irqEn = 0x12;
			waitIRq = 0x10;
			break;
		}
		case PCD_TRANSCEIVE:	
		{
			irqEn = 0x77;
			waitIRq = 0x30;
			break;
		}
		default:
			break;
    }
   
    Fn_RFID_WriteMFRC522(CommIEnReg, irqEn|0x80);	
    Fn_RFID_ClearBitMask(CommIrqReg, 0x80);			
    Fn_RFID_SetBitMask(FIFOLevelReg, 0x80);		
    
	Fn_RFID_WriteMFRC522(CommandReg, PCD_IDLE);

    for (i=0; i<_vruc_sendLen; i++)
    {   
		Fn_RFID_WriteMFRC522(FIFODataReg, sendData[i]);    
	}

	Fn_RFID_WriteMFRC522(CommandReg, _vruc_command);
    if (_vruc_command == PCD_TRANSCEIVE)
    {    
		Fn_RFID_SetBitMask(BitFramingReg, 0x80);	
	}   
    
	i = 2000;	
    do 
    {
        n = Fn_RFID_ReadMFRC522(CommIrqReg);
        i--;
    }
    while ((i!=0) && !(n&0x01) && !(n&waitIRq));

    Fn_RFID_ClearBitMask(BitFramingReg, 0x80);		
	
    if (i != 0)
    {    
        if(!(Fn_RFID_ReadMFRC522(ErrorReg) & 0x1B))	
        {
            vruc_Status = MI_OK;
            if (n & irqEn & 0x01)
            {   
				vruc_Status = MI_NOTAGERR;	 
			}
            if (_vruc_command == PCD_TRANSCEIVE)
            {
               	n = Fn_RFID_ReadMFRC522(FIFOLevelReg);
              	lastBits = Fn_RFID_ReadMFRC522(ControlReg) & 0x07;
                if (lastBits)
                {   
					*backLen = (n-1)*8 + lastBits;   
				}
                else
                {   
					*backLen = n*8;   
				}

                if (n == 0)
                {   
					n = 1;    
				}
                if (n > MAX_LEN)
                {   
					n = MAX_LEN;   
				}
				
                for (i=0; i<n; i++)
                {   
					backData[i] = Fn_RFID_ReadMFRC522(FIFODataReg);    
				}
            }
        }
        else
        {   
			vruc_Status = MI_ERR;  
		}      
    }
    return vruc_Status;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
unsigned char Fn_RFID_MFRC522Request(unsigned char _vruc_reqMode, unsigned char *TagType)
{
	unsigned char vruc_Status;  
	unsigned int backBits;		

	Fn_RFID_WriteMFRC522(BitFramingReg, 0x07);			
	TagType[0] = _vruc_reqMode;
	vruc_Status = Fn_RFID_MFRC522ToCard(PCD_TRANSCEIVE, TagType, 1, TagType, &backBits);

	if ((vruc_Status != MI_OK) || (backBits != 0x10))
	{    
		vruc_Status = MI_ERR;
	}  
	return vruc_Status;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
unsigned char Fn_RFID_Anticoll(unsigned char *serNum)
{
	unsigned char vruc_Status;
	unsigned char i;
	unsigned char serNumCheck=0;
	unsigned int unLen;
    
	Fn_RFID_WriteMFRC522(BitFramingReg, 0x00);	
 
	serNum[0] = PICC_ANTICOLL;
	serNum[1] = 0x20;
	vruc_Status = Fn_RFID_MFRC522ToCard(PCD_TRANSCEIVE, serNum, 2, serNum, &unLen);

   	if (vruc_Status == MI_OK)
	{
		for (i=0; i<4; i++)
		{   
		 	serNumCheck ^= serNum[i];
		}
		if (serNumCheck != serNum[i])
		{   
			vruc_Status = MI_ERR;    
		}
    }

    return vruc_Status;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
unsigned char Fn_RFID_Auth(unsigned char _vruc_authMode, unsigned char _vruc_BlockAddr, unsigned char *Sectorkey, unsigned char *serNum)
{
	unsigned char vruc_Status;
	unsigned int recvBits;
	unsigned char i;
	unsigned char buff[12]; 

	buff[0] = _vruc_authMode;
	buff[1] = _vruc_BlockAddr;
	for (i=0; i<6; i++)
	{    
		buff[i+2] = *(Sectorkey+i);   
	}
	for (i=0; i<4; i++)
	{    
		buff[i+8] = *(serNum+i);   
	}
	vruc_Status = Fn_RFID_MFRC522ToCard(PCD_AUTHENT, buff, 12, buff, &recvBits);
	
	if ((vruc_Status != MI_OK) || (!(Fn_RFID_ReadMFRC522(Status2Reg) & 0x08)))
	{   
		vruc_Status = MI_ERR;   
	}
	return vruc_Status;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
unsigned char Fn_RFID_Read(unsigned char _vruc_BlockAddr, unsigned char *recvData)
{
	unsigned char vruc_Status;
	unsigned int unLen;
	
	recvData[0] = PICC_READ;
	recvData[1] = _vruc_BlockAddr;
	Fn_RFID_CalculateCRC(recvData,2, &recvData[2]);
	vruc_Status = Fn_RFID_MFRC522ToCard(PCD_TRANSCEIVE, recvData, 4, recvData, &unLen);
	
	if ((vruc_Status != MI_OK) || (unLen != 0x90))
	{
		vruc_Status = MI_ERR;
	}	
	return vruc_Status;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
unsigned char Fn_RFID_Write(unsigned char _vruc_BlockAddr, unsigned char *writeData)
{
    unsigned char vruc_Status;
    unsigned int recvBits;
    unsigned char i;
	unsigned char buff[18]; 
    
    buff[0] = PICC_WRITE;
    buff[1] = _vruc_BlockAddr;
    Fn_RFID_CalculateCRC(buff, 2, &buff[2]);
    vruc_Status = Fn_RFID_MFRC522ToCard(PCD_TRANSCEIVE, buff, 4, buff, &recvBits);

    if ((vruc_Status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A))
    {   
		vruc_Status = MI_ERR;   
	}
        
    if (vruc_Status == MI_OK)
    {
        for (i=0; i<16; i++)
        {    
        	buff[i] = *(writeData+i);   
        }
        Fn_RFID_CalculateCRC(buff, 16, &buff[16]);
        vruc_Status = Fn_RFID_MFRC522ToCard(PCD_TRANSCEIVE, buff, 18, buff, &recvBits);
        
		if ((vruc_Status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A))
        {   
			vruc_Status = MI_ERR;   
		}
    }
    
    return vruc_Status;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Fn_RFID_Halt()
{
    unsigned int unLen;
    unsigned char buff[4]; 

    buff[0] = PICC_HALT;
    buff[1] = 0;
    Fn_RFID_CalculateCRC(buff, 2, &buff[2]);
 
    Fn_RFID_MFRC522ToCard(PCD_TRANSCEIVE, buff, 4, buff,&unLen);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
