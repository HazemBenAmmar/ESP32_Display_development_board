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
#ifndef __TEST_H__
#define __TEST_H__

void DrawTestPage(u8 *str);
void Test_Color(void);
void Test_FillRec(void);
void Test_Circle(void);
void Test_Triangle(void);
void English_Font_test(void);
void Chinese_Font_test(void);
void Pic_test(void);
void Load_Drow_Dialog(void);
void Touch_Test(void);
void main_test(void);
void Rotate_Test(void);
void Test_Read(void);
void POINT_Test(void);
void Combo_Test(void);
void ProgresBar_Test(void);
void BarReport_Test(void);
void Window_Test(void);
void Button_Test(void);
#endif