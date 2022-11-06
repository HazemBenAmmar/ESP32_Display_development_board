//手机:17199916363（微信同号）
//技术支持QQ:423170204
//邮箱:Lcddiy@hotmail.com
/****************************************************************************************************
//=========================================接线说明================================================//
//  5V      接     DC5V
//  3v3     接     DC3.3V
//  GND     接     GND 
//  LCD_RST 接     PC4
//  LCD_CS  接     PC9
//  LCD_RS  接     PC8
//  LCD_WR  接     PC7
//  LCD_RD  接     PC6
//  LCD_D0  接     PB0
//  LCD_D1  接     PB1
//  LCD_D2  接     PB2
//  LCD_D3  接     PB3
//  LCD_D4  接     PB4
//  LCD_D5  接     PB5
//  LCD_D6  接     PB6
//  LCD_D7  接     PB7
//  由于配套程序没有使用SD卡扩展功能，所以下引脚不需要接线
//  SD_SS、SD_DI、SD_DO、SD_SCK
//  由于本模块触摸测试需要外接XPT2046触摸采样芯片，所以本程序不进行触摸测试
**************************************************************************************************/				
#ifndef __TOUCH_H__
#define __TOUCH_H__
#include "sys.h"

#define TP_PRES_DOWN 0x80  //触屏被按下	  
#define TP_CATH_PRES 0x40  //有按键按下了 	  
										    
//触摸屏控制器
typedef struct
{
	u8 (*init)(void);			//初始化触摸屏控制器
	u8 (*scan)(u8);				//扫描触摸屏.0,屏幕扫描;1,物理坐标;	 
	void (*adjust)(void);		//触摸屏校准
	u16 x0;						//原始坐标(第一次按下时的坐标)
	u16 y0;
	u16 x; 						//当前坐标(此次扫描时,触屏的坐标)
	u16 y;						   	    
	u8  sta;					//笔的状态 
								//b7:按下1/松开0; 
	                            //b6:0,没有按键按下;1,有按键按下.         			  
////////////////////////触摸屏校准参数/////////////////////////								
	float xfac;					
	float yfac;
	short xoff;
	short yoff;	   
//新增的参数,当触摸屏的左右上下完全颠倒时需要用到.
//touchtype=0的时候,适合左右为X坐标,上下为Y坐标的TP.
//touchtype=1的时候,适合左右为Y坐标,上下为X坐标的TP.
	u8 touchtype;
}_m_tp_dev;

extern _m_tp_dev tp_dev;	 	//触屏控制器在touch.c里面定义

//与触摸屏芯片连接引脚	   
//与触摸屏芯片连接引脚	   
#define PEN  PCin(1)    //PC1  INT
#define DOUT PCin(2)     //PC2  MISO		 PC2--PB14
#define TDIN PCout(3)    //PC3  MOSI		 PC3--PB15
#define TCLK PCout(0)    //PC0  SCLK	 PC0--PB13
#define TCS  PCout(13)   //PC13 CS    
     

void TP_Write_Byte(u8 num);						//向控制芯片写入一个数据
u16 TP_Read_AD(u8 CMD);							//读取AD转换值
u16 TP_Read_XOY(u8 xy);							//带滤波的坐标读取(X/Y)
u8 TP_Read_XY(u16 *x,u16 *y);					//双方向读取(X+Y)
u8 TP_Read_XY2(u16 *x,u16 *y);					//带加强滤波的双方向坐标读取
void TP_Drow_Touch_Point(u16 x,u16 y,u16 color);//画一个坐标校准点
void TP_Draw_Big_Point(u16 x,u16 y,u16 color);	//画一个大点
u8 TP_Scan(u8 tp);								//扫描
void TP_Save_Adjdata(void);						//保存校准参数
u8 TP_Get_Adjdata(void);						//读取校准参数
void TP_Adjust(void);							//触摸屏校准
u8 TP_Init(void);								//初始化
																 
void TP_Adj_Info_Show(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2,u16 x3,u16 y3,u16 fac);//显示校准信息
 		  
#endif

















