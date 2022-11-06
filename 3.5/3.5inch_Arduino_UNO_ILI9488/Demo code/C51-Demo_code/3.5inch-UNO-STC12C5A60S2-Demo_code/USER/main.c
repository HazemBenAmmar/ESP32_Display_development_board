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
#include "sys.h"
#include "lcd.h"
#include "gui.h"
#include "test.h"
#include "touch.h"

//主函数
void main(void)
{ 

	//设置STC_12LE5A60S2单片机的P3.2为推挽输出，用于控制背光亮灭
	//其他普通C51单片机无此配置请屏蔽下面这条语句
	P3M1 &= ~(1<<2),P3M0 |=  (1<<2); 

	//液晶屏初始化
	LCD_Init();

	//循环进行各项测试	
	while(1)
	{
		main_test(); 		//测试主界面
		Test_Read();     //读ID和颜色值测试
		Test_Color();  		//简单刷屏填充测试
		Test_FillRec();		//GUI矩形绘图测试
		Test_Circle(); 		//GUI画圆测试
		Test_Triangle();   //GUI三角形填充测试
		English_Font_test();//英文字体示例测试
		Chinese_Font_test();//中文字体示例测试
		Pic_test();			//图片显示示例测试
		Rotate_Test();  //屏幕旋转测试
		POINT_Test();        // Loading 测试 
		Combo_Test();		     // 下拉列表测试
		ProgresBar_Test();	 // 进度条测试	
		BarReport_Test();	   // 条形报表测试
		Window_Test();		   // 窗口测试	
		Button_Test();		   // 按钮测试
	//不使用触摸或者模块本身不带触摸，请屏蔽下面触摸屏测试	
	//	Touch_Test();		//触摸屏手写测试
	//需要触摸校准时，请将触摸手写测试屏蔽，将下面触摸校准测试项打开
	//	Touch_Adjust();  //触摸校准
	}   
}
