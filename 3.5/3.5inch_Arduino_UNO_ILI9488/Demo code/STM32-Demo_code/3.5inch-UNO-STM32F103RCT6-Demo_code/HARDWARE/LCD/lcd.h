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
#ifndef __LCD_H
#define __LCD_H		
#include "sys.h"	 
#include "stdlib.h"

//LCD��Ҫ������
typedef struct  
{										    
	u16 width;			//LCD ���
	u16 height;			//LCD �߶�
	u16 id;				  //LCD ID
	u8  dir;			  //���������������ƣ�0��������1��������	
	u16	 wramcmd;		//��ʼдgramָ��
	u16  rramcmd;   //��ʼ��gramָ��
	u16  setxcmd;		//����x����ָ��
	u16  setycmd;		//����y����ָ��
}_lcd_dev; 	

//LCD����
extern _lcd_dev lcddev;	//����LCD��Ҫ����
/////////////////////////////////////�û�������///////////////////////////////////	 
#define USE_HORIZONTAL  	  0 //����Һ����˳ʱ����ת���� 	0-0����ת��1-90����ת��2-180����ת��3-270����ת
#define LCD_USE8BIT_MODEL   1	//�������������Ƿ�ʹ��8λģʽ 0,ʹ��16λģʽ.1,ʹ��8λģʽ

//////////////////////////////////////////////////////////////////////////////////	  
//����LCD�ĳߴ�
#define LCD_W 320
#define LCD_H 480

//TFTLCD������Ҫ���õĺ���		   
extern u16  POINT_COLOR;//Ĭ�Ϻ�ɫ    
extern u16  BACK_COLOR; //������ɫ.Ĭ��Ϊ��ɫ

////////////////////////////////////////////////////////////////////
//-----------------LCD�˿ڶ���---------------- 
#define GPIO_TYPE  GPIOC  //GPIO������
#define LED      10        //�����������      PC10
#define LCD_CS   9       //Ƭѡ����            PC9
#define LCD_RS   8       //�Ĵ���/����ѡ������ PC8 
#define LCD_RST  4       //��λ����            PC4
#define LCD_WR   7       //д����              PC7
#define LCD_RD   6       //������              PC6


//GPIO��λ�����ߣ�
#define	LCD_CS_SET  GPIO_TYPE->BSRR=1<<LCD_CS    //Ƭѡ�˿�  	
#define	LCD_RS_SET	GPIO_TYPE->BSRR=1<<LCD_RS    //����/����    
#define	LCD_RST_SET	GPIO_TYPE->BSRR=1<<LCD_RST   //��λ			  
#define	LCD_WR_SET	GPIO_TYPE->BSRR=1<<LCD_WR    //д 	
#define LCD_RD_SET  GPIO_TYPE->BSRR=1<<LCD_RD    //��		  

//GPIO��λ�����ͣ�							    
#define	LCD_CS_CLR  GPIO_TYPE->BRR=1<<LCD_CS     //Ƭѡ�˿�  	
#define	LCD_RS_CLR	GPIO_TYPE->BRR=1<<LCD_RS     //����/����  	 
#define	LCD_RST_CLR	GPIO_TYPE->BRR=1<<LCD_RST    //��λ			  
#define	LCD_WR_CLR	GPIO_TYPE->BRR=1<<LCD_WR     //д
#define LCD_RD_CLR  GPIO_TYPE->BRR=1<<LCD_RD     //��	  		  

//PB0~15,��Ϊ������
//ע�⣺���ʹ��8λģʽ�������ߣ���Һ���������ݸ�8λ�ǽӵ�MCU�ĸ�8λ������
//�����������8λģʽ��ʾ������ΪҺ����DB10-DB17��Ӧ������Ƭ��GPIOB_Pin8-GPIOB_Pin15
//�����������16λģʽ��DB0-DB7�ֱ��GPIOB_Pin0-GPIOB_Pin7,DB10-DB17��Ӧ������Ƭ��GPIOB_Pin8-GPIOB_Pin15
#define DATAOUT(x) GPIOB->ODR=x; //�������
#define DATAIN     GPIOB->IDR;   //��������

//������ɫ
#define WHITE       0xFFFF
#define BLACK      	0x0000	  
#define BLUE       	0x001F  
#define BRED        0XF81F
#define GRED 			 	0XFFE0
#define GBLUE			 	0X07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN 			0XBC40 //��ɫ
#define BRRED 			0XFC07 //�غ�ɫ
#define GRAY  			0X8430 //��ɫ
//GUI��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
 
#define LIGHTGREEN     	0X841F //ǳ��ɫ
#define LIGHTGRAY     0XEF5B //ǳ��ɫ(PANNEL)
#define LGRAY 			 		0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ
#define     DARKGRAY     0X8410	  //���ɫ

#define LGRAYBLUE      	0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE          0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)
	    															  
void LCD_Init(void);
void LCD_write(u16 VAL);
u16 LCD_read(void);
void LCD_Clear(u16 Color);	 
void LCD_SetCursor(u16 Xpos, u16 Ypos);
void LCD_DrawPoint(u16 x,u16 y);//����
u16  LCD_ReadPoint(u16 x,u16 y); //����	   
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd);
u16 LCD_RD_DATA(void);//��ȡLCD����								    
void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue);
void LCD_WR_REG(u16 data);
void LCD_WR_DATA(u16 data);
void LCD_ReadReg(u16 LCD_Reg,u8 *Rval,int n);
void LCD_WriteRAM_Prepare(void);
void LCD_ReadRAM_Prepare(void);   
void Lcd_WriteData_16Bit(u16 Data);
u16 Lcd_ReadData_16Bit(void);
void LCD_direction(u8 direction );
u16 LCD_Read_ID(void);

		  		 
#endif  
	 
	 



