//�ֻ�:17199916363��΢��ͬ�ţ�
//����֧��QQ:423170204
//����:Lcddiy@hotmail.com
/****************************************************************************************************
//=========================================����˵��================================================//
//  5V      ��     DC5V
//  3v3     ��     DC3.3V
//  GND     ��     GND 
//  LCD_RST ��     PC4
//  LCD_CS  ��     PC9
//  LCD_RS  ��     PC8
//  LCD_WR  ��     PC7
//  LCD_RD  ��     PC6
//  LCD_D0  ��     PB0
//  LCD_D1  ��     PB1
//  LCD_D2  ��     PB2
//  LCD_D3  ��     PB3
//  LCD_D4  ��     PB4
//  LCD_D5  ��     PB5
//  LCD_D6  ��     PB6
//  LCD_D7  ��     PB7
//  �������׳���û��ʹ��SD����չ���ܣ����������Ų���Ҫ����
//  SD_SS��SD_DI��SD_DO��SD_SCK
//  ���ڱ�ģ�鴥��������Ҫ���XPT2046��������оƬ�����Ա����򲻽��д�������
**************************************************************************************************/				
#include "24cxx.h" 
#include "delay.h"

/*****************************************************************************
 * @name       :void AT24CXX_Init(void)
 * @date       :2018-08-09 
 * @function   :Initialize IIC interface
 * @parameters :None
 * @retvalue   :None
******************************************************************************/ 
void AT24CXX_Init(void)
{
	IIC_Init();
}

/*****************************************************************************
 * @name       :u8 AT24CXX_ReadOneByte(u16 ReadAddr)
 * @date       :2018-08-09 
 * @function   :Read out a data at a specified address in the AT24CXX
 * @parameters :ReadAddr:the address of start reading
 * @retvalue   :Read data
******************************************************************************/ 
u8 AT24CXX_ReadOneByte(u16 ReadAddr)
{				  
	u8 temp=0;		  	    																 
    IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Byte(0XA0);	   //����д����
		IIC_Wait_Ack();
		IIC_Send_Byte(ReadAddr>>8);//���͸ߵ�ַ
		IIC_Wait_Ack();		 
	}else IIC_Send_Byte(0XA0+((ReadAddr/256)<<1));   //����������ַ0XA0,д���� 	 

	IIC_Wait_Ack(); 
    IIC_Send_Byte(ReadAddr%256);   //���͵͵�ַ
	IIC_Wait_Ack();	    
	IIC_Start();  	 	   
	IIC_Send_Byte(0XA1);           //�������ģʽ			   
	IIC_Wait_Ack();	 
    temp=IIC_Read_Byte(0);		   
    IIC_Stop();//����һ��ֹͣ����	    
	return temp;
}

/*****************************************************************************
 * @name       :void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite)
 * @date       :2018-08-09 
 * @function   :Write a data at a specified address in AT24CXX
 * @parameters :WriteAddr:the destination address for writing data
								DataToWrite:Data to be written
 * @retvalue   :None
******************************************************************************/ 
void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite)
{				   	  	    																 
    IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Byte(0XA0);	    //����д����
		IIC_Wait_Ack();
		IIC_Send_Byte(WriteAddr>>8);//���͸ߵ�ַ
		IIC_Wait_Ack();		 
	}else
	{
		IIC_Send_Byte(0XA0+((WriteAddr/256)<<1));   //����������ַ0XA0,д���� 
	}	 
	IIC_Wait_Ack();	   
    IIC_Send_Byte(WriteAddr%256);   //���͵͵�ַ
	IIC_Wait_Ack(); 	 										  		   
	IIC_Send_Byte(DataToWrite);     //�����ֽ�							   
	IIC_Wait_Ack();  		    	   
    IIC_Stop();//����һ��ֹͣ���� 
	delay_ms(10);	 
}

/*****************************************************************************
 * @name       :void AT24CXX_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len)
 * @date       :2018-08-09 
 * @function   :begins to write data with a length of Len 
								at the specified address in the AT24CXX
 * @parameters :WriteAddr:the address to start writing
								DataToWrite:the header address of the data array 
								Len:Length of data to be written(2 or 4)
 * @retvalue   :None
******************************************************************************/ 
void AT24CXX_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len)
{  	
	u8 t;
	for(t=0;t<Len;t++)
	{
		AT24CXX_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}

/*****************************************************************************
 * @name       :u32 AT24CXX_ReadLenByte(u16 ReadAddr,u8 Len)
 * @date       :2018-08-09 
 * @function   :begins to read data with a length of Len 
								at the specified address in the AT24CXX,
								used to read 16bits or 32bits data
 * @parameters :ReadAddr:the address of start reading
								len:Length of data to be read(2 or 4)
 * @retvalue   :Read data
******************************************************************************/ 
u32 AT24CXX_ReadLenByte(u16 ReadAddr,u8 Len)
{  	
	u8 t;
	u32 temp=0;
	for(t=0;t<Len;t++)
	{
		temp<<=8;
		temp+=AT24CXX_ReadOneByte(ReadAddr+Len-t-1); 	 				   
	}
	return temp;												    
}

/*****************************************************************************
 * @name       :u8 AT24CXX_Check(void)
 * @date       :2018-08-09 
 * @function   :Check that AT24CXX is normal or not,
								Use AT24CXX's last address (255) to store the token,
								if use the other 24C series, this address needs to be modified,
 * @parameters :None
 * @retvalue   :0-check successfully
								1-check failed
******************************************************************************/
u8 AT24CXX_Check(void)
{
	u8 temp;
	temp=AT24CXX_ReadOneByte(255);//����ÿ�ο�����дAT24CXX			   
	if(temp==0X55)return 0;		   
	else//�ų���һ�γ�ʼ�������
	{
		AT24CXX_WriteOneByte(255,0X55);
	    temp=AT24CXX_ReadOneByte(255);	  
		if(temp==0X55)return 0;
	}
	return 1;											  
}

/*****************************************************************************
 * @name       :void AT24CXX_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead)
 * @date       :2018-08-09 
 * @function   :begins to read out the specified number of data at 
								the specified address in the AT24CXX
 * @parameters :ReadAddr:the address of start reading,it is 0~255 for 24c02
								pBuffer:the header address of the data array 
								NumToRead:Number of data to be read
 * @retvalue   :None
******************************************************************************/
void AT24CXX_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=AT24CXX_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
} 

/*****************************************************************************
 * @name       :void AT24CXX_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)
 * @date       :2018-08-09 
 * @function   :begins to write the specified number of data at 
								the specified address in the AT24CXX
 * @parameters :WriteAddr:the address of start writing,it is 0~255 for 24c02
								pBuffer:the header address of the data array 
								NumToRead:Number of data to be writen
 * @retvalue   :None
******************************************************************************/ 
void AT24CXX_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)
{
	while(NumToWrite--)
	{
		AT24CXX_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}
 











