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
#ifndef __LCD_H
#define __LCD_H		
#include "sys.h"	 
#include "stdlib.h"

//LCD重要参数集
typedef struct  
{										    
	u16 width;			//LCD 宽度
	u16 height;			//LCD 高度
	u16 id;				  //LCD ID
	u8  dir;			  //横屏还是竖屏控制：0，竖屏；1，横屏。	
	u16	 wramcmd;		//开始写gram指令
	u16  rramcmd;   //开始读gram指令
	u16  setxcmd;		//设置x坐标指令
	u16  setycmd;		//设置y坐标指令
}_lcd_dev; 	

//LCD参数
extern _lcd_dev lcddev;	//管理LCD重要参数
/////////////////////////////////////用户配置区///////////////////////////////////	 
#define USE_HORIZONTAL  	  0 //定义液晶屏顺时针旋转方向 	0-0度旋转，1-90度旋转，2-180度旋转，3-270度旋转
#define LCD_USE8BIT_MODEL   1	//定义数据总线是否使用8位模式 0,使用16位模式.1,使用8位模式

//////////////////////////////////////////////////////////////////////////////////	  
//定义LCD的尺寸
#define LCD_W 320
#define LCD_H 480

//TFTLCD部分外要调用的函数		   
extern u16  POINT_COLOR;//默认红色    
extern u16  BACK_COLOR; //背景颜色.默认为白色

////////////////////////////////////////////////////////////////////
//-----------------LCD端口定义---------------- 
#define GPIO_TYPE  GPIOC  //GPIO组类型
#define LED      10        //背光控制引脚      PC10
#define LCD_CS   9       //片选引脚            PC9
#define LCD_RS   8       //寄存器/数据选择引脚 PC8 
#define LCD_RST  4       //复位引脚            PC4
#define LCD_WR   7       //写引脚              PC7
#define LCD_RD   6       //读引脚              PC6


//GPIO置位（拉高）
#define	LCD_CS_SET  GPIO_TYPE->BSRR=1<<LCD_CS    //片选端口  	
#define	LCD_RS_SET	GPIO_TYPE->BSRR=1<<LCD_RS    //数据/命令    
#define	LCD_RST_SET	GPIO_TYPE->BSRR=1<<LCD_RST   //复位			  
#define	LCD_WR_SET	GPIO_TYPE->BSRR=1<<LCD_WR    //写 	
#define LCD_RD_SET  GPIO_TYPE->BSRR=1<<LCD_RD    //读		  

//GPIO复位（拉低）							    
#define	LCD_CS_CLR  GPIO_TYPE->BRR=1<<LCD_CS     //片选端口  	
#define	LCD_RS_CLR	GPIO_TYPE->BRR=1<<LCD_RS     //数据/命令  	 
#define	LCD_RST_CLR	GPIO_TYPE->BRR=1<<LCD_RST    //复位			  
#define	LCD_WR_CLR	GPIO_TYPE->BRR=1<<LCD_WR     //写
#define LCD_RD_CLR  GPIO_TYPE->BRR=1<<LCD_RD     //读	  		  

//PB0~15,作为数据线
//注意：如果使用8位模式数据总线，则液晶屏的数据高8位是接到MCU的高8位总线上
//举例：如果接8位模式则本示例接线为液晶屏DB10-DB17对应接至单片机GPIOB_Pin8-GPIOB_Pin15
//举例：如果是16位模式：DB0-DB7分别接GPIOB_Pin0-GPIOB_Pin7,DB10-DB17对应接至单片机GPIOB_Pin8-GPIOB_Pin15
#define DATAOUT(x) GPIOB->ODR=x; //数据输出
#define DATAIN     GPIOB->IDR;   //数据输入

//画笔颜色
#define WHITE       0xFFFF
#define BLACK      	0x0000	  
#define BLUE       	0x001F  
#define BRED        0XF81F
#define GRED 			 	0XFFE0
#define GBLUE			 	0X07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN 			0XBC40 //棕色
#define BRRED 			0XFC07 //棕红色
#define GRAY  			0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	0X841F //浅绿色
#define LIGHTGRAY     0XEF5B //浅灰色(PANNEL)
#define LGRAY 			 		0XC618 //浅灰色(PANNEL),窗体背景色
#define     DARKGRAY     0X8410	  //深灰色

#define LGRAYBLUE      	0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE          0X2B12 //浅棕蓝色(选择条目的反色)
	    															  
void LCD_Init(void);
void LCD_write(u16 VAL);
u16 LCD_read(void);
void LCD_Clear(u16 Color);	 
void LCD_SetCursor(u16 Xpos, u16 Ypos);
void LCD_DrawPoint(u16 x,u16 y);//画点
u16  LCD_ReadPoint(u16 x,u16 y); //读点	   
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd);
u16 LCD_RD_DATA(void);//读取LCD数据								    
void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue);
void LCD_WR_REG(u16 data);
void LCD_WR_DATA(u16 data);
void LCD_ReadReg(u16 LCD_Reg,u8 *Rval,int n);
void LCD_WriteRAM_Prepare(void);
void LCD_ReadRAM_Prepare(void);   
void Lcd_WriteData_16Bit(u16 Data);
u16 Lcd_ReadData_16Bit(void);
void LCD_direction(u8 direction );
u16 LCD_Read_ID(void);

		  		 
#endif  
	 
	 



