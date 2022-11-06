/**********************************************************************************************************/ 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//测试硬件：硬件采用STM32F103VCT6开发板8M晶振，主频72M
//液晶驱动 for STM32
//淘宝网站：http://jczn.taobao.com
//All rights reserved
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
//       LED                接          PB9         //液晶屏背光控制信号，如果不需要控制，接5V或3.3V
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
#include "key.h"
#include "sys.h" 
#include "delay.h"
							    
//按键初始化函数
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
	//初始化KEY0-->GPIOA.13,KEY1-->GPIOA.15  上拉输入
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);//使能PORTA,PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;//PE2~4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE2,3,4

	//初始化 WK_UP-->GPIOA.0	  下拉输入
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0设置成输入，默认下拉	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.0

}
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY2按下 
//4，KEY3按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY2>KEY3!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||KEY3==1))
	{
		delay_ms(15);//去抖动 
		key_up=0;
		if(KEY0==0)return 1;
		else if(KEY1==0)return 2;
		else if(KEY2==0)return 3;
		else if(KEY3==1)return 4;
	}else if(KEY0==1&&KEY1==1&&KEY2==1&&KEY3==0)key_up=1; 	    
 	return 0;// 无按键按下
}
