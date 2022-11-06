//////////////////////////////////////////////////////////////////////////////////	 

/****************************************************************************************************
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//测试硬件：单片机STM32F103RCT6,正点原子MiniSTM32开发板,主频72MHZ，晶振12MHZ
//QDtech-TFT液晶驱动 for STM32
//淘宝网站：http://jczn.taobao.com
//All rights reserved
**************************************************************************************************/	
 /* @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
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
		main_test(); 		//测试主界面
		Test_Color();  		//简单刷屏填充测试
		Test_FillRec();		//GUI矩形绘图测试
		Test_Circle(); 		//GUI画圆测试
		Test_Triangle();    //GUI三角形绘图测试
		English_Font_test();//英文字体示例测试
		Chinese_Font_test();//中文字体示例测试
		Pic_test();			//图片显示示例测试
		Rotate_Test();   //旋转显示测试
		//如果不带触摸，或者不需要触摸功能，请注释掉下面触摸屏测试项
		Touch_Test();		//触摸屏手写测试  
	}
}

