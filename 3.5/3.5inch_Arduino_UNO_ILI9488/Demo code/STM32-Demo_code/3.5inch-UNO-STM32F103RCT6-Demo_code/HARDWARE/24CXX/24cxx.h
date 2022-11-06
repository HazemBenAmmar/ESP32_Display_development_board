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
#ifndef __24CXX_H
#define __24CXX_H
#include "myiic.h"   

#define AT24C01		127
#define AT24C02		255
#define AT24C04		511
#define AT24C08		1023
#define AT24C16		2047
#define AT24C32		4095
#define AT24C64	    8191
#define AT24C128	16383
#define AT24C256	32767  
//Mini STM32开发板使用的是24c02，所以定义EE_TYPE为AT24C02
#define EE_TYPE AT24C02
					  
u8 AT24CXX_ReadOneByte(u16 ReadAddr);							//指定地址读取一个字节
void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite);		//指定地址写入一个字节
void AT24CXX_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len);//指定地址开始写入指定长度的数据
u32 AT24CXX_ReadLenByte(u16 ReadAddr,u8 Len);					//指定地址开始读取指定长度数据
void AT24CXX_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite);	//从指定地址开始写入指定长度的数据
void AT24CXX_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead);   	//从指定地址开始读出指定长度的数据

u8 AT24CXX_Check(void);  //检查器件
void AT24CXX_Init(void); //初始化IIC
#endif
















