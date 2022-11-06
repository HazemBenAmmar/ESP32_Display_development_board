//手机:17199916363（微信同号）
//技术支持QQ:423170204
//邮箱:Lcddiy@hotmail.com
/****************************************************************************************************
//=========================================接线说明================================================//
//  5V      接     DC5V
//  3v3     接     DC3.3V
//  GND     接     GND 
//  LCD_RST 接     P33
//  LCD_CS  接     P13
//  LCD_RS  接     P12
//  LCD_WR  接     P11
//  LCD_RD  接     P10
//  LCD_D0  接     P20
//  LCD_D1  接     P21
//  LCD_D2  接     P22
//  LCD_D3  接     P23
//  LCD_D4  接     P24
//  LCD_D5  接     P25
//  LCD_D6  接     P26
//  LCD_D7  接     P27
//  由于配套程序没有使用SD卡扩展功能，所以下引脚不需要接线
//  SD_SS、SD_DI、SD_DO、SD_SCK
//  由于本模块触摸测试需要外接XPT2046触摸采样芯片，所以本程序不进行触摸测试
**************************************************************************************************/					
#ifndef __TOUCH_H
#define __TOUCH_H	
	
/* touch panel interface define */
#define  CMD_RDX  0xD0	 //触摸IC读坐标积存器
#define  CMD_RDY  0x90
//IO连接
sfr   P4    = 0xC0;
sbit DCLK	   =    P3^6;   
sbit TCS        =    P3^7;
sbit DIN       =    P3^4;	
sbit DOUT      =    P3^5;																						   
sbit Penirq    =    P4^0;   //检测触摸屏响应信号

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
extern struct tp_pix_  tp_pixad,tp_pixlcd;	 //当前触控坐标的AD值,前触控坐标的像素值   
extern u16 vx,vy;  //比例因子，此值除以1000之后表示多少个AD值代表一个像素点
extern u16 chx,chy;//默认像素点坐标为0时的AD起始值
u8 tpstate(void);
void spistar(void);  
void Touch_Adjust(void);
void point(void); //绘图函数
u16 ReadFromCharFrom7843();         //SPI 读数据
void TP_Draw_Big_Point(u16 x,u16 y,u16 color);
u8 Convert_Pos(void);
#endif  
	 
	 



