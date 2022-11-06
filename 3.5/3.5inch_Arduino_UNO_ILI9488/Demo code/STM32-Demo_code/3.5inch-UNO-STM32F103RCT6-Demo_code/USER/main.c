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
#include "delay.h"
#include "sys.h"
#include "lcd.h"
#include "touch.h"
#include "gui.h"
#include "test.h"

int main(void)
{	
	SystemInit();//初始化RCC 设置系统主频为72MHZ
	delay_init(72);	     //延时初始化
	LCD_Init();	   //液晶屏初始化
  //循环测试
	while(1)
	{
		main_test(); 		     //测试主界面
		Test_Read();         //读ID和颜色值测试
		Test_Color();  		   //简单刷屏填充测试
		Test_FillRec();		   //GUI矩形绘图测试
		Test_Circle(); 		   //GUI画圆测试
		Test_Triangle();     //GUI三角形绘图测试
		English_Font_test(); //英文字体示例测试
		Chinese_Font_test(); //中文字体示例测试
		Pic_test();			     //图片显示示例测试
		Rotate_Test();       //旋转显示测试
		POINT_Test();        // Loading 测试 
		Combo_Test();		     // 下拉列表测试
		ProgresBar_Test();	 // 进度条测试	
		BarReport_Test();	   // 条形报表测试
		Window_Test();		   // 窗口测试	
		Button_Test();		   // 按钮测试	
		//如果不带触摸，或者不需要触摸功能，请注释掉下面触摸屏测试项
		//Touch_Test();		//触摸屏手写测试		
	}
}

