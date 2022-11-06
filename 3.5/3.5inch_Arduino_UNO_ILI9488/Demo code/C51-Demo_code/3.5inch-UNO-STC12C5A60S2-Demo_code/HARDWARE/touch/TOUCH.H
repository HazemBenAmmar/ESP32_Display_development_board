//�ֻ�:17199916363��΢��ͬ�ţ�
//����֧��QQ:423170204
//����:Lcddiy@hotmail.com
/****************************************************************************************************
//=========================================����˵��================================================//
//  5V      ��     DC5V
//  3v3     ��     DC3.3V
//  GND     ��     GND 
//  LCD_RST ��     P33
//  LCD_CS  ��     P13
//  LCD_RS  ��     P12
//  LCD_WR  ��     P11
//  LCD_RD  ��     P10
//  LCD_D0  ��     P20
//  LCD_D1  ��     P21
//  LCD_D2  ��     P22
//  LCD_D3  ��     P23
//  LCD_D4  ��     P24
//  LCD_D5  ��     P25
//  LCD_D6  ��     P26
//  LCD_D7  ��     P27
//  �������׳���û��ʹ��SD����չ���ܣ����������Ų���Ҫ����
//  SD_SS��SD_DI��SD_DO��SD_SCK
//  ���ڱ�ģ�鴥��������Ҫ���XPT2046��������оƬ�����Ա����򲻽��д�������
**************************************************************************************************/					
#ifndef __TOUCH_H
#define __TOUCH_H	
	
/* touch panel interface define */
#define  CMD_RDX  0xD0	 //����IC�����������
#define  CMD_RDY  0x90
//IO����
sfr   P4    = 0xC0;
sbit DCLK	   =    P3^6;   
sbit TCS        =    P3^7;
sbit DIN       =    P3^4;	
sbit DOUT      =    P3^5;																						   
sbit Penirq    =    P4^0;   //��ⴥ������Ӧ�ź�

struct tp_pix_
{
	u16 x;
	u16 y;
};
struct tp_pixu32_
{
	u32 x;
	u32 y;
};
extern struct tp_pix_  tp_pixad,tp_pixlcd;	 //��ǰ���������ADֵ,ǰ�������������ֵ   
extern u16 vx,vy;  //�������ӣ���ֵ����1000֮���ʾ���ٸ�ADֵ����һ�����ص�
extern u16 chx,chy;//Ĭ�����ص�����Ϊ0ʱ��AD��ʼֵ
u8 tpstate(void);
void spistar(void);  
void Touch_Adjust(void);
void point(void); //��ͼ����
u16 ReadFromCharFrom7843();         //SPI ������
void TP_Draw_Big_Point(u16 x,u16 y,u16 color);
u8 Convert_Pos(void);
#endif  
	 
	 


