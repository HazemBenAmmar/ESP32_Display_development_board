/**********************************************************************************************************/ 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//测试硬件：硬件采用STM32F103VCT6开发板8M晶振，主频72M
//液晶驱动 for STM32
//淘宝网站：http://jczn.taobao.com
//All rights reserved
//版权所有，盗版必究。
/*********************************************************************************************************/ 
//=========================================电源接线================================================//
//     LCD模块                       STM32单片机
//      VCC                 接        DC5V/3.3V      //电源
//      GND                 接          GND          //电源地
//=======================================液晶屏数据线接线==========================================//
//本模块默认数据总线类型为SPI总线
//     LCD模块                      STM32单片机    
//    SDI(MOSI)             接          PA7         //液晶屏SPI总线数据写信号
//    SDO(MISO)             接          PA6         //液晶屏SPI总线数据读信号，如果不需要读，可以不接线
//=======================================液晶屏控制线接线==========================================//
//     LCD模块 					            STM32单片机 
//       LED                接          PB6         //液晶屏背光控制信号，如果不需要控制，接5V或3.3V
//       SCK                接          PA5         //液晶屏SPI总线时钟信号
//      DC/RS               接          PC4         //液晶屏数据/命令控制信号
//       RST                接          PB0         //液晶屏复位控制信号
//       CS                 接          PA4         //液晶屏片选控制信号
//=========================================触摸屏触接线============================================//
//如果模块不带触摸功能或者带有触摸功能，但是不需要触摸功能，则不需要进行触摸屏接线
//	   LCD模块                       STM32单片机 
//      T_IRQ(C_INT)        接          PC10         //触摸屏触摸中断信号
//      T_DO (C_SDA)        接          PC2          //触摸屏SPI总线读信号
//      T_DIN               接          PC3          //触摸屏SPI总线写信号
//      T_CS (C_RST)        接          PC0          //触摸屏片选控制信号
//      T_CLK(C_SCL)        接          PC1          //触摸屏SPI总线时钟信号
/**********************************************************************************************************/ 
#ifndef __LCD_INIT_H
#define __LCD_INIT_H
#include "sys.h"

#define USE_HORIZONTAL 0  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏


#define LCD_W 240
#define LCD_H 240



//-----------------LCD端口定义---------------- 

#define LCD_SCLK_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_5)//SCL=SCLK 
#define LCD_SCLK_Set() GPIO_SetBits(GPIOA,GPIO_Pin_5)

#define LCD_MOSI_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_7)//SDA=MOSI 
#define LCD_MOSI_Set() GPIO_SetBits(GPIOA,GPIO_Pin_7)

#define LCD_RES_Clr()  GPIO_ResetBits(GPIOB,GPIO_Pin_0)//RES 
#define LCD_RES_Set()  GPIO_SetBits(GPIOB,GPIO_Pin_0)

#define LCD_DC_Clr()   GPIO_ResetBits(GPIOC,GPIO_Pin_4)//DC  
#define LCD_DC_Set()   GPIO_SetBits(GPIOC,GPIO_Pin_4)
 		     
#define LCD_CS_Clr()   GPIO_ResetBits(GPIOA,GPIO_Pin_4)//CS  
#define LCD_CS_Set()   GPIO_SetBits(GPIOA,GPIO_Pin_4)

#define LCD_BLK_Clr()  GPIO_ResetBits(GPIOB,GPIO_Pin_6)//BLK 
#define LCD_BLK_Set()  GPIO_SetBits(GPIOB,GPIO_Pin_6)




void LCD_GPIO_Init(void);//初始化GPIO
void LCD_Writ_Bus(u8 dat);//模拟SPI时序
void LCD_WR_DATA8(u8 dat);//写入一个字节
void LCD_WR_DATA(u16 dat);//写入两个字节
void LCD_WR_REG(u8 dat);//写入一个指令
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);//设置坐标函数
void LCD_Init(void);//LCD初始化
#endif




