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
#include "delay.h"
#include "sys.h"
#include "lcd.h"
#include "touch.h"
#include "gui.h"
#include "test.h"

int main(void)
{	
	SystemInit();//��ʼ��RCC ����ϵͳ��ƵΪ72MHZ
	delay_init(72);	     //��ʱ��ʼ��
	LCD_Init();	   //Һ������ʼ��
  //ѭ������
	while(1)
	{
		main_test(); 		     //����������
		Test_Read();         //��ID����ɫֵ����
		Test_Color();  		   //��ˢ��������
		Test_FillRec();		   //GUI���λ�ͼ����
		Test_Circle(); 		   //GUI��Բ����
		Test_Triangle();     //GUI�����λ�ͼ����
		English_Font_test(); //Ӣ������ʾ������
		Chinese_Font_test(); //��������ʾ������
		Pic_test();			     //ͼƬ��ʾʾ������
		Rotate_Test();       //��ת��ʾ����
		POINT_Test();        // Loading ���� 
		Combo_Test();		     // �����б����
		ProgresBar_Test();	 // ����������	
		BarReport_Test();	   // ���α������
		Window_Test();		   // ���ڲ���	
		Button_Test();		   // ��ť����	
		//����������������߲���Ҫ�������ܣ���ע�͵����津����������
		//Touch_Test();		//��������д����		
	}
}

