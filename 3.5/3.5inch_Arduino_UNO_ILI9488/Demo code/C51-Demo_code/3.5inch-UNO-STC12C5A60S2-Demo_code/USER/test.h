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