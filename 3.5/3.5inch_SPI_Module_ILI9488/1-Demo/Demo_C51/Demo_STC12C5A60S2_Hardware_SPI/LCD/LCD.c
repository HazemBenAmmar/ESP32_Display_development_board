//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//����Ӳ������Ƭ��STC12C5A60S2,����30M  ��Ƭ��������ѹ3.3V
//TFTҺ������ for C51
//�Ա���վ��http://qdtech.taobao.com
//All rights reserved
//********************************************************************************
//=========================================��Դ����================================================//
//5V��DC 5V��Դ
//GND�ӵ�
//=======================================Һ���������߽���==========================================//
//��ģ��Ĭ��������������ΪSPI
//Һ����ģ��            ��Ƭ��
// SDI(MOSI)     ��       P15        //SPIд�ź�
// SDO(MISO)     ��       P16        //SPI���źţ��������Ҫ�����ܣ��˹ܽſɲ���
//=======================================Һ���������߽���==========================================//
//Һ����ģ��            ��Ƭ��
//  CS           ��       P13       //Ƭѡ�����ź�
//  RESET        ��       P33       //��λ�ź�
//  DC           ��       P12       //����/����ѡ������ź�
//  SCK          ��       P17       //SPIʱ���ź�
//  LED          ��       P32       //��������źţ����ʹ��STC89C52RC��Ƭ�����߲���Ҫ���ƣ���3.3V
//=========================================����������=========================================//
//STC89C52RC��Ƭ��ROM̫С���޷����д��������ܵĳ������Դ���������Ҫ����
//��ʹ�ô�������ģ�鱾������������ɲ�����
//������ʹ�õ�������������ΪSPI
//������ģ��            ��Ƭ��
//  T_CLK        ��       P36       //������SPIʱ���ź�
//  T_CS         ��       P37       //������Ƭѡ�����ź�
//  T_DIN        ��       P34       //������SPIд�ź�
//  T_DO         ��       P35       //������SPI���ź�
//  T_IRQ        ��       P40       //��������Ӧ����źţ��絥Ƭ����P4�飬�����и�����������IO���޸Ĵ��붨��
//**************************************************************************************************/	
#include "sys.h"
#include "lcd.h"

//LCD�Ļ�����ɫ�ͱ���ɫ	   
u16 POINT_COLOR=0x0000;	//������ɫ
u16 BACK_COLOR=0xFFFF;  //����ɫ 
//����LCD��Ҫ����
//Ĭ��Ϊ����
_lcd_dev lcddev;

void  delay_ms_new(unsigned char ms)
{
     unsigned int i;
	 do{
	      i = MAIN_Fosc / 14000;
		  while(--i)	;   //14T per loop
     }while(--ms);
}

void	SPI_init(void)	
{
	SPCTL = (SSIG << 7)+(SPEN << 6)+(DORD << 5)+(MSTR << 4)+(CPOL << 3)+(CPHA << 2)+SPEED_4;
}

/*****************************************************************************
 * @name       :void SPI_WriteByte(u8 byte)
 * @date       :2018-08-09 
 * @function   :Write a byte of data using C51's Hardware SPI
 * @parameters :d:Data to be written
 * @retvalue   :None
******************************************************************************/
void SPI_WriteByte(u8 byte)
{			
			SPDAT = byte;		//����һ���ֽ�
			while((SPSTAT & SPIF)==0)	;	//�ȴ��������
			SPSTAT = SPIF+WCOL;			//��0 SPIF��WCOL��־
}

/*****************************************************************************
 * @name       :void LCD_WR_REG(u8 data)
 * @date       :2018-08-09 
 * @function   :Write an 8-bit command to the LCD screen
 * @parameters :data:Command value to be written
 * @retvalue   :None
******************************************************************************/
void LCD_WR_REG(u8 Reg)	 
{	
	LCD_CS=0;
	LCD_RS=0;
	SPI_WriteByte(Reg);
	LCD_CS=1;
} 

/*****************************************************************************
 * @name       :void LCD_WR_DATA(u8 data)
 * @date       :2018-08-09 
 * @function   :Write an 8-bit data to the LCD screen
 * @parameters :data:data value to be written
 * @retvalue   :None
******************************************************************************/
void LCD_WR_DATA(u8 Data)
{
	LCD_CS=0;
	LCD_RS=1;
	SPI_WriteByte(Data);
	LCD_CS=1;
}

/*****************************************************************************
 * @name       :void LCD_WR_DATA_16Bit(u16 Data)
 * @date       :2018-08-09 
 * @function   :Write an 16-bit command to the LCD screen
 * @parameters :Data:Data to be written
 * @retvalue   :None
******************************************************************************/	 
void LCD_WR_DATA_16Bit(u16 Data)
{
  //18Bit	
	LCD_WR_DATA((Data>>8)&0xF8);//RED
	LCD_WR_DATA((Data>>3)&0xFC);//GREEN
	LCD_WR_DATA(Data<<3);//BLUE
}

/*****************************************************************************
 * @name       :void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
 * @date       :2018-08-09 
 * @function   :Write data into registers
 * @parameters :LCD_Reg:Register address
                LCD_RegValue:Data to be written
 * @retvalue   :None
******************************************************************************/
void LCD_WriteReg(u8 LCD_Reg, u8 LCD_RegValue)
{
  LCD_WR_REG(LCD_Reg);
	LCD_WR_DATA(LCD_RegValue);
}

/*****************************************************************************
 * @name       :void LCD_WriteRAM_Prepare(void)
 * @date       :2018-08-09 
 * @function   :Write GRAM
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	
void LCD_WriteRAM_Prepare(void)
{
 	LCD_WR_REG(lcddev.wramcmd);	  
}

/*****************************************************************************
 * @name       :void LCD_Clear(u16 Color)
 * @date       :2018-08-09 
 * @function   :Full screen filled LCD screen
 * @parameters :color:Filled color
 * @retvalue   :None
******************************************************************************/	
void LCD_Clear(u16 Color)
{
	u16 i,j;
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);	
    for(i=0;i<lcddev.width;i++)
	 {
	  for (j=0;j<lcddev.height;j++)
	   	{
        	 LCD_WR_DATA_16Bit(Color);
	    }

	  }
}

/*****************************************************************************
 * @name       :void LCD_DrawPoint(u16 x,u16 y)
 * @date       :2018-08-09 
 * @function   :Write a pixel data at a specified location
 * @parameters :x:the x coordinate of the pixel
                y:the y coordinate of the pixel
 * @retvalue   :None
******************************************************************************/	
void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_SetWindows(x,y,x,y);//���ù��λ�� 
	LCD_WR_DATA_16Bit(POINT_COLOR); 	    
} 	 

/*****************************************************************************
 * @name       :void LCD_Reset(void)
 * @date       :2018-08-09 
 * @function   :Reset LCD screen
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	
void LCD_Reset(void)
{
	LCD_RESET=1;
	delay_ms_new(50);	
	LCD_RESET=0;
	delay_ms_new(50);
	LCD_RESET=1;
	delay_ms_new(50);
}

/*****************************************************************************
 * @name       :void LCD_Init(void)
 * @date       :2018-08-09 
 * @function   :Initialization LCD screen
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	 	 
void LCD_Init(void)
{
	SPI_init(); //��ʼ��Ӳ��SPI
	LCD_Reset(); //��ʼ��֮ǰ��λ
//************* ILI9488��ʼ��**********//	
	LCD_WR_REG(0XF7);
	LCD_WR_DATA(0xA9);
	LCD_WR_DATA(0x51);
	LCD_WR_DATA(0x2C);
	LCD_WR_DATA(0x82);
	LCD_WR_REG(0xC0);
	LCD_WR_DATA(0x11);
	LCD_WR_DATA(0x09);
	LCD_WR_REG(0xC1);
	LCD_WR_DATA(0x41);
	LCD_WR_REG(0XC5);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x0A);
	LCD_WR_DATA(0x80);
	LCD_WR_REG(0xB1);
	LCD_WR_DATA(0xB0);
	LCD_WR_DATA(0x11);
	LCD_WR_REG(0xB4);
	LCD_WR_DATA(0x02);
	LCD_WR_REG(0xB6);//���Ʒ���Ĵ���
	LCD_WR_DATA(0x02);
	LCD_WR_DATA(0x22);//0x42��0x22
	LCD_WR_REG(0xB7);
	LCD_WR_DATA(0xc6);
	LCD_WR_REG(0xBE);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x04);
	LCD_WR_REG(0xE9);
	LCD_WR_DATA(0x00);
	LCD_WR_REG(0x36);
	LCD_WR_DATA((1<<3)|(0<<7)|(1<<6)|(1<<5));
	LCD_WR_REG(0x3A);
	LCD_WR_DATA(0x66);
	LCD_WR_REG(0xE0);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x07);
	LCD_WR_DATA(0x10);
	LCD_WR_DATA(0x09);
	LCD_WR_DATA(0x17);
	LCD_WR_DATA(0x0B);
	LCD_WR_DATA(0x41);
	LCD_WR_DATA(0x89);
	LCD_WR_DATA(0x4B);
	LCD_WR_DATA(0x0A);
	LCD_WR_DATA(0x0C);
	LCD_WR_DATA(0x0E);
	LCD_WR_DATA(0x18);
	LCD_WR_DATA(0x1B);
	LCD_WR_DATA(0x0F);
	LCD_WR_REG(0XE1);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x17);
	LCD_WR_DATA(0x1A);
	LCD_WR_DATA(0x04);
	LCD_WR_DATA(0x0E);
	LCD_WR_DATA(0x06);
	LCD_WR_DATA(0x2F);
	LCD_WR_DATA(0x45);
	LCD_WR_DATA(0x43);
	LCD_WR_DATA(0x02);
	LCD_WR_DATA(0x0A);
	LCD_WR_DATA(0x09);
	LCD_WR_DATA(0x32);
	LCD_WR_DATA(0x36);
	LCD_WR_DATA(0x0F);
	LCD_WR_REG(0x11);
	delay_ms(120);
	LCD_WR_REG(0x29);	

	//����LCD���Բ���
	LCD_direction(USE_HORIZONTAL);//����LCD��ʾ���� 
	LCD_BL=1;//��������	 
}
 
/*****************************************************************************
 * @name       :void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
 * @date       :2018-08-09 
 * @function   :Setting LCD display window
 * @parameters :xStar:the bebinning x coordinate of the LCD display window
								yStar:the bebinning y coordinate of the LCD display window
								xEnd:the endning x coordinate of the LCD display window
								yEnd:the endning y coordinate of the LCD display window
 * @retvalue   :None
******************************************************************************/ 
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
{	
	LCD_WR_REG(lcddev.setxcmd);	
	LCD_WR_DATA(xStar>>8);
	LCD_WR_DATA(0x00FF&xStar);		
	LCD_WR_DATA(xEnd>>8);
	LCD_WR_DATA(0x00FF&xEnd);

	LCD_WR_REG(lcddev.setycmd);	
	LCD_WR_DATA(yStar>>8);
	LCD_WR_DATA(0x00FF&yStar);		
	LCD_WR_DATA(yEnd>>8);
	LCD_WR_DATA(0x00FF&yEnd);	

	LCD_WriteRAM_Prepare();	//��ʼд��GRAM				
}   

/*****************************************************************************
 * @name       :void LCD_SetCursor(u16 Xpos, u16 Ypos)
 * @date       :2018-08-09 
 * @function   :Set coordinate value
 * @parameters :Xpos:the  x coordinate of the pixel
								Ypos:the  y coordinate of the pixel
 * @retvalue   :None
******************************************************************************/ 
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{	  	    			
	LCD_SetWindows(Xpos,Ypos,Xpos,Ypos);	
} 

/*****************************************************************************
 * @name       :void LCD_direction(u8 direction)
 * @date       :2018-08-09 
 * @function   :Setting the display direction of LCD screen
 * @parameters :direction:0-0 degree
                          1-90 degree
													2-180 degree
													3-270 degree
 * @retvalue   :None
******************************************************************************/ 
void LCD_direction(u8 direction)
{ 
			lcddev.setxcmd=0x2A;
			lcddev.setycmd=0x2B;
			lcddev.wramcmd=0x2C;
	switch(direction){		  
		case 0:						 	 		
			lcddev.width=LCD_W;
			lcddev.height=LCD_H;		
			LCD_WriteReg(0x36,(1<<3)|(0<<6)|(0<<7));//BGR==1,MY==0,MX==0,MV==0
		break;
		case 1:
			lcddev.width=LCD_H;
			lcddev.height=LCD_W;
			LCD_WriteReg(0x36,(1<<3)|(0<<7)|(1<<6)|(1<<5));//BGR==1,MY==1,MX==0,MV==1
		break;
		case 2:						 	 		
			lcddev.width=LCD_W;
			lcddev.height=LCD_H;	
			LCD_WriteReg(0x36,(1<<3)|(1<<6)|(1<<7));//BGR==1,MY==0,MX==0,MV==0
		break;
		case 3:
			lcddev.width=LCD_H;
			lcddev.height=LCD_W;
			LCD_WriteReg(0x36,(1<<3)|(1<<7)|(1<<5));//BGR==1,MY==1,MX==0,MV==1
		break;	
		default:break;
	}		
	
}	 





