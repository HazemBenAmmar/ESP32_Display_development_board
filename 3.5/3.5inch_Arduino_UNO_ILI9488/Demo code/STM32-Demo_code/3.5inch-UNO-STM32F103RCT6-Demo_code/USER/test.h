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
