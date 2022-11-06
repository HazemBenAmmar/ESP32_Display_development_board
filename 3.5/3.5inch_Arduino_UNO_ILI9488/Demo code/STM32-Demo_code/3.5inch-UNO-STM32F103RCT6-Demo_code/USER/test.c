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
#include <stdio.h>
#include "lcd.h"
#include "delay.h"
#include "gui.h"
#include "test.h"
#include "touch.h"
#include "key.h" 
#include "led.h"
#include "pic.h"

//========================variable==========================//
u16 ColorTab[5]={RED,GREEN,BLUE,YELLOW,BRED};//定义颜色数组
u16 ColornTab[8]={RED,MAGENTA,GREEN,DARKBLUE,BLUE,BLACK,LIGHTGREEN};
//=====================end of variable======================//

/*****************************************************************************
 * @name       :void DrawTestPage(u8 *str)
 * @date       :2018-08-09 
 * @function   :Drawing test interface
 * @parameters :str:the start address of the Chinese and English strings
 * @retvalue   :None
******************************************************************************/ 
void DrawTestPage(u8 *str)
{
//绘制固定栏up
LCD_Clear(WHITE);
LCD_Fill(0,0,lcddev.width-1,20,BLUE);
//绘制固定栏down
LCD_Fill(0,lcddev.height-20,lcddev.width-1,lcddev.height-1,BLUE);
POINT_COLOR=WHITE;
Gui_StrCenter(0,2,WHITE,BLUE,str,16,1);//居中显示
Gui_StrCenter(0,lcddev.height-18,WHITE,BLUE,"3.5inch UNO Test",16,1);//居中显示
//绘制测试区域
//LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
}

/*****************************************************************************
 * @name       :void main_test(void)
 * @date       :2018-08-09 
 * @function   :Drawing the main Interface of the Comprehensive Test Program
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void main_test(void)
{
	LCD_Clear(WHITE);
	Gui_StrCenter(0,60,RED,BLUE,"综合测试程序",16,1);//居中显示	
	Gui_StrCenter(0,90,MAGENTA,BLUE,"3.5\" ILI9488 320X480",16,1);//居中显示
	delay_ms(1500);		
	delay_ms(1500);
}

/*****************************************************************************
 * @name       :void Test_Color(void)
 * @date       :2018-08-09 
 * @function   :Color fill test(white,black,red,green,blue)
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Test_Color(void)
{
	//DrawTestPage("测试1:纯色填充测试");
	LCD_Fill(0,0,lcddev.width-1,lcddev.height-1,WHITE);
	Show_Str(20,30,BLUE,YELLOW,"BL Test",16,1);delay_ms(800);
	LCD_Fill(0,0,lcddev.width-1,lcddev.height-1,RED);
	Show_Str(20,30,BLUE,YELLOW,"RED ",16,1);delay_ms(800);
	LCD_Fill(0,0,lcddev.width-1,lcddev.height-1,GREEN);
	Show_Str(20,30,BLUE,YELLOW,"GREEN ",16,1);delay_ms(800);
	LCD_Fill(0,0,lcddev.width-1,lcddev.height-1,BLUE);
	Show_Str(20,30,RED,YELLOW,"BLUE ",16,1);delay_ms(800);
}

/*****************************************************************************
 * @name       :void Test_FillRec(void)
 * @date       :2018-08-09 
 * @function   :Rectangular display and fill test
								Display red,green,blue,yellow,pink rectangular boxes in turn,
								1500 milliseconds later,
								Fill the rectangle in red,green,blue,yellow and pink in turn
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Test_FillRec(void)
{
	u8 i=0;
	DrawTestPage("测试3:矩形测试");
	LCD_Fill(0,20,lcddev.width-1,lcddev.height-20,WHITE);
	for (i=0; i<5; i++) 
	{
		POINT_COLOR=ColorTab[i];
		LCD_DrawRectangle(lcddev.width/2-80+(i*15),lcddev.height/2-80+(i*15),lcddev.width/2-80+(i*15)+60,lcddev.height/2-80+(i*15)+60); 
	}
	delay_ms(1500);	
	LCD_Fill(0,20,lcddev.width-1,lcddev.height-20,WHITE); 
	for (i=0; i<5; i++) 
	{
		POINT_COLOR=ColorTab[i];
		LCD_DrawFillRectangle(lcddev.width/2-80+(i*15),lcddev.height/2-80+(i*15),lcddev.width/2-80+(i*15)+60,lcddev.height/2-80+(i*15)+60); 
	}
	delay_ms(1500);
}

/*****************************************************************************
 * @name       :void Test_Circle(void)
 * @date       :2018-08-09 
 * @function   :circular display and fill test
								Display red,green,blue,yellow,pink circular boxes in turn,
								1500 milliseconds later,
								Fill the circular in red,green,blue,yellow and pink in turn
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Test_Circle(void)
{
	u8 i=0;
	DrawTestPage("测试4:圆形测试");
	LCD_Fill(0,20,lcddev.width-1,lcddev.height-20,WHITE);
	for (i=0; i<5; i++)  
		gui_circle(lcddev.width/2-80+(i*25),lcddev.height/2-50+(i*25),ColorTab[i],30,0);
	delay_ms(1500);	
	LCD_Fill(0,20,lcddev.width-1,lcddev.height-20,WHITE); 
	for (i=0; i<5; i++) 
	  	gui_circle(lcddev.width/2-80+(i*25),lcddev.height/2-50+(i*25),ColorTab[i],30,1);
	delay_ms(1500);
}

/*****************************************************************************
 * @name       :void English_Font_test(void)
 * @date       :2018-08-09 
 * @function   :English display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void English_Font_test(void)
{
	DrawTestPage("测试6:英文测试");
	Show_Str(10,30,BLUE,YELLOW,"6X12:abcdefghijklmnopqrstuvwxyz0123456789",12,0);
	Show_Str(10,45,BLUE,YELLOW,"6X12:ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789",12,1);
	Show_Str(10,60,BLUE,YELLOW,"6X12:~!@#$%^&*()_+{}:<>?/|-+.",12,0);
	Show_Str(10,80,BLUE,YELLOW,"8X16:abcdefghijklmnopqrstuvwxyz0123456789",16,0);
	Show_Str(10,100,BLUE,YELLOW,"8X16:ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789",16,1);
	Show_Str(10,120,BLUE,YELLOW,"8X16:~!@#$%^&*()_+{}:<>?/|-+.",16,0); 
	delay_ms(1200);
}

/*****************************************************************************
 * @name       :void Test_Triangle(void)
 * @date       :2018-08-09 
 * @function   :triangle display and fill test
								Display red,green,blue,yellow,pink triangle boxes in turn,
								1500 milliseconds later,
								Fill the triangle in red,green,blue,yellow and pink in turn
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Test_Triangle(void)
{
	u8 i=0;
	DrawTestPage("测试5:Triangle测试");
	LCD_Fill(0,20,lcddev.width-1,lcddev.height-20,WHITE);
	for(i=0;i<5;i++)
	{
		POINT_COLOR=ColorTab[i];
		Draw_Triangel(lcddev.width/2-80+(i*20),lcddev.height/2-20+(i*15),lcddev.width/2-50-1+(i*20),lcddev.height/2-20-52-1+(i*15),lcddev.width/2-20-1+(i*20),lcddev.height/2-20+(i*15));
	}
	delay_ms(1500);	
	LCD_Fill(0,20,lcddev.width-1,lcddev.height-20,WHITE); 
	for(i=0;i<5;i++)
	{
		POINT_COLOR=ColorTab[i];
		Fill_Triangel(lcddev.width/2-80+(i*20),lcddev.height/2-20+(i*15),lcddev.width/2-50-1+(i*20),lcddev.height/2-20-52-1+(i*15),lcddev.width/2-20-1+(i*20),lcddev.height/2-20+(i*15));
	}
	delay_ms(1500);
}

/*****************************************************************************
 * @name       :void Chinese_Font_test(void)
 * @date       :2018-08-09 
 * @function   :chinese display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Chinese_Font_test(void)
{	
	DrawTestPage("测试7:中文测试");
	Show_Str(10,30,BLUE,YELLOW,"16X16:欢迎您",16,0);
	Show_Str(10,50,BLUE,YELLOW,"16X16:Welcome",16,0);
	Show_Str(10,70,BLUE,YELLOW,"24X24:中文测试",24,1);
	Show_Str(10,100,BLUE,YELLOW,"32X32:字体测试",32,1);
	delay_ms(1200);
}

/*****************************************************************************
 * @name       :void Pic_test(void)
 * @date       :2018-08-09 
 * @function   :picture display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Pic_test(void)
{
	DrawTestPage("测试8:图片测试");
	//LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
	Gui_Drawbmp16(30,30,gImage_qq);
	Show_Str(30+12,75,BLUE,YELLOW,"QQ",16,1);
	Gui_Drawbmp16(90,30,gImage_qq);
	Show_Str(90+12,75,BLUE,YELLOW,"QQ",16,1);
	Gui_Drawbmp16(150,30,gImage_qq);
	Show_Str(150+12,75,BLUE,YELLOW,"QQ",16,1);
	delay_ms(1200);
}

/*****************************************************************************
 * @name       :void Rotate_Test(void)
 * @date       :2018-08-09 
 * @function   :rotate test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Rotate_Test(void)
{
	u8 i=0;
	u8 *Direction[4]={"Rotation:0","Rotation:90","Rotation:180","Rotation:270"};
	
	for(i=0;i<4;i++)
	{
	LCD_direction(i);
	DrawTestPage("测试9:旋转测试");
	Show_Str(20,30,BLUE,YELLOW,Direction[i],16,1);
	Gui_Drawbmp16(30,50,gImage_qq);
	delay_ms(1000);delay_ms(1000);
	}
	LCD_direction(USE_HORIZONTAL);
}

/*****************************************************************************
 * @name       :void Touch_Test(void)
 * @date       :2018-08-09 
 * @function   :touch test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Touch_Test(void)
{
	u8 key;
	u16 i=0;
	u16 j=0;
	u16 colorTemp=0;
	TP_Init();
	KEY_Init();
	LED_Init();
	DrawTestPage("测试10:Touch(按KEY0校准)      ");
	LCD_ShowString(lcddev.width-24,0,16,"RST",1);//显示清屏区域
	POINT_COLOR=RED;
	LCD_Fill(lcddev.width-50,2,lcddev.width-50+22,18,RED); 
		while(1)
	{
	 	key=KEY_Scan();
		tp_dev.scan(0); 		 
		if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
		{	
		 	if(tp_dev.x<lcddev.width&&tp_dev.y<lcddev.height)
			{	
				if(tp_dev.x>(lcddev.width-24)&&tp_dev.y<16)
				{
					DrawTestPage("测试10:Touch(按KEY0校准)      ");//清除
					LCD_ShowString(lcddev.width-24,0,16,"RST",1);//显示清屏区域
					POINT_COLOR=colorTemp;
					LCD_Fill(lcddev.width-50,2,lcddev.width-50+22,18,POINT_COLOR); 
				}
				else if((tp_dev.x>(lcddev.width-50)&&tp_dev.x<(lcddev.width-50+22))&&tp_dev.y<20)
				{
				LCD_Fill(lcddev.width-50,2,lcddev.width-50+22,18,ColorTab[j%5]); 
				POINT_COLOR=ColorTab[(j++)%5];
				colorTemp=POINT_COLOR;
				delay_ms(10);
				}

				else TP_Draw_Big_Point(tp_dev.x,tp_dev.y,POINT_COLOR);		//画图	  			   
			}
		}else delay_ms(10);	//没有按键按下的时候 	    
		if(key==1)	//KEY_RIGHT按下,则执行校准程序
		{

			LCD_Clear(WHITE);//清屏
		    TP_Adjust();  //屏幕校准 
			TP_Save_Adjdata();	 
			DrawTestPage("测试10:Touch(按KEY0校准)      ");
			LCD_ShowString(lcddev.width-24,0,16,"RST",1);//显示清屏区域
			POINT_COLOR=colorTemp;
			LCD_Fill(lcddev.width-50,2,lcddev.width-50+22,18,POINT_COLOR); 
		}
		i++;
		if(i==30)
		{
			i=0;
			LED0=!LED0;
			//break;
		}
	}   
}

/*****************************************************************************
 * @name       :void Test_Read(void)
 * @date       :2018-11-13 
 * @function   :read test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Test_Read(void)
{
	u16 lcd_id,color;
	u8 buf[10] = {0},i;
	u8 cbuf[20] = {0};
	DrawTestPage("测试2:读ID和颜色值测试");
	LCD_Fill(0,20,lcddev.width-1,lcddev.height-20,WHITE);
	lcd_id = LCD_Read_ID();
	sprintf((char *)buf,"ID:0x%x",lcd_id);
	Show_Str(50,25,BLUE,YELLOW,buf,16,1);
	for (i=0; i<7; i++) 
	{
		POINT_COLOR=ColornTab[i];
		LCD_DrawFillRectangle(40-10,55+i*25-10,40+10,55+i*25+10);
		color = LCD_ReadPoint(40,55+i*25);
		sprintf((char *)cbuf,"read color:0x%04X",color);
		Show_Str(40+20,55+i*25-8,POINT_COLOR,YELLOW,cbuf,16,1);
	}
	delay_ms(1500);
}

/*****************************************************************************
 * @name       :void POINT_Test(void)
 * @date       :2018-12-29 
 * @function   :point test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void POINT_Test(void)
{
	uint8_t x=lcddev.width/2,y=lcddev.height/2,r=20,t,m,i;

	t = 7*r/10;
	m =100;	//显示速度毫秒值
	
	DrawTestPage("测试11:GUI Loading");
	LCD_Fill(0,20,lcddev.width-1,lcddev.height-20,BLACK);
	POINT_COLOR = WHITE;
	BACK_COLOR = BLACK;
	Show_Str((lcddev.width-96)/2, lcddev.height/2+r+10, POINT_COLOR,BACK_COLOR,"Loading.....",16,1);
	for(i=0;i<2;i++)
	{
		LCD_Draw9Point(x, y-r, WHITE); //画第一个点
		delay_ms(m);
		LCD_Draw9Point(x+t, y-t, WHITE); //画第二个点
		delay_ms(m);
		LCD_Draw9Point(x, y-r, BLACK); //删除第一个点
		delay_ms(m);
		LCD_Draw9Point(x+r, y, WHITE); //画第三个点
		delay_ms(m);
		LCD_Draw9Point(x+t, y-t, BLACK);  //删除第二个点
		delay_ms(m);
		LCD_Draw9Point(x+t, y+t, WHITE);  //画第四个点
		delay_ms(m);
		LCD_Draw9Point(x+r, y, BLACK); //删除第三个点
		delay_ms(m);
		LCD_Draw9Point(x, y+r, WHITE);  //画第五个点
		delay_ms(m);
		LCD_Draw9Point(x+t, y+t, BLACK);  //删除第四个点
		delay_ms(m);
		LCD_Draw9Point(x-t, y+t, WHITE);  //画第六个点
		delay_ms(m);
		LCD_Draw9Point(x, y+r, BLACK);  //删除第五个点
		delay_ms(m);
		LCD_Draw9Point(x-r, y, WHITE);  //画第七个点
		delay_ms(m);
		LCD_Draw9Point(x-t, y+t, BLACK);  //删除第六个点
		delay_ms(m);
		LCD_Draw9Point(x-t, y-t, WHITE);  //画第八个点
		delay_ms(m);
		LCD_Draw9Point(x-r, y, BLACK);  //删除第七个点
		delay_ms(m);
		LCD_Draw9Point(x-t, y-t, BLACK);  //删除第八个点
		delay_ms(m);
	}
	delay_ms(1500);
}

/*****************************************************************************
 * @name       :void Combo_Test(void)
 * @date       :2018-12-29 
 * @function   :combo test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Combo_Test(void)
{
	DrawTestPage("测试12:GUI Combo");
	LCD_Fill(0,20,lcddev.width-1,lcddev.height-20,GRAY);
	//画一个条形输入框
	Draw_TextBox(50, 50, 200, 73);
	//画下拉列表按钮(19*19)像素
	Draw_Button(179, 52, 198, 71);
	Draw_DirectButton(179,52);
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
	SetButton(179, 52, 198, 71);
	LCD_Fill(183, 56, 194, 67, LGRAY);
   	Draw_DirectButton(180,53);
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
	EscButton(179, 52, 198, 71);
	LCD_Fill(183, 56, 194, 67, LGRAY);
	Draw_DirectButton(179,52);
	//拉出下拉列表
	POINT_COLOR=BLACK;
	LCD_DrawRectangle(50, 74, 200, 143);
	LCD_Fill(51, 75, 199, 142, WHITE);
	//写列表中的内容
	LCD_Fill(51, 75, 199, 97, DARKBLUE); //第一个默认为选中状态
	POINT_COLOR=WHITE;
	BACK_COLOR=DARKBLUE;
	Show_Str(53, 79, POINT_COLOR,BACK_COLOR,"STM ICP Bridge",16,1);

	POINT_COLOR=BLACK;
	BACK_COLOR=WHITE;
	Show_Str(53, 101, POINT_COLOR,BACK_COLOR,"STM PP Bridge",16,1);
	Show_Str(53, 124, POINT_COLOR,BACK_COLOR,"None ISP",16,1);
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
	//选中第二个
	LCD_Fill(51, 75, 199, 97, WHITE);	   //先取消第一个
	POINT_COLOR=BLACK;
	BACK_COLOR=WHITE;
	Show_Str(53, 79, POINT_COLOR,BACK_COLOR,"STM ICP Bridge",16,1);

	LCD_Fill(51, 98, 199, 120, DARKBLUE);  //选中第二个
	POINT_COLOR=WHITE;
	BACK_COLOR=DARKBLUE;
	Show_Str(53, 101, POINT_COLOR,BACK_COLOR,"STM PP Bridge",16,1);
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
	//选中第三个
	LCD_Fill(51, 98, 199, 120, WHITE);//先取消选中的第二个
	POINT_COLOR=BLACK;
	BACK_COLOR=WHITE;
	Show_Str(53, 101, POINT_COLOR,BACK_COLOR,"STM PP Bridge",16,1);

	LCD_Fill(51, 121, 199, 142, DARKBLUE);//选中第三个
	POINT_COLOR=WHITE;
	BACK_COLOR=DARKBLUE;
	Show_Str(53, 124, POINT_COLOR,BACK_COLOR,"None ISP",16,1);
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
	//清除
	LCD_Fill(50, 74, 200, 143, GRAY);
	delay_ms(1500);
}

/*****************************************************************************
 * @name       :void ProgresBar_Test(void)
 * @date       :2018-12-29 
 * @function   :ProgresBar test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void ProgresBar_Test(void)
{
	uint8_t i,num=1;
	u16 x1=20;
	u16 y1=30;
	u16 x2=150;//130
	u16 y2=130;//100
			
	DrawTestPage("测试13:GUI ProgresBar");
	LCD_Fill(0,20,lcddev.width-1,lcddev.height-20,WHITE);
	Draw_Button(x1, y1, x2, y2);   // 显示主体窗口
	LCD_Fill(x1+3, y1+3, x2-3, y2-75, DARKBLUE);	 // 显示标题栏 
	Show_Str(x1+25, y1+5, POINT_COLOR,BACK_COLOR,"ProgresBar",16,1); // 按钮上写字
	Draw_Button(x1+5, y1+70, x2-70, y2-5);  // 显示第一个按钮
	Draw_Button(x1+70, y1+70, x2-5, y2-5);  // 显示第二个按钮
	POINT_COLOR=BLACK;	
	BACK_COLOR=LGRAY;
	Show_Str(x1+25, y1+74,POINT_COLOR,BACK_COLOR,"OK",16,1);
	Show_Str(x1+75, y1+74, POINT_COLOR,BACK_COLOR,"Cancel",16,1);
	Show_Str(x1+80, y1+35, POINT_COLOR,BACK_COLOR,"%",16,1);	  
	for(i=x1+26;i<x2-5;i++)
	{
		LCD_Fill(x1+5, y1+53, i, y1+68, RED);
		delay_ms(40);
		LCD_ShowNum(x1+62, y1+35, num,2,16);
		num++;
	}
	LCD_Fill(x1+5, y1+35, x2-5, y1+50, LGRAY);
	Show_Str(x1+25, y1+35, BLUE,BACK_COLOR,"Success!!!",16,1);
	delay_ms(1500);
}

/*****************************************************************************
 * @name       :void BarReport_Test(void)
 * @date       :2018-12-29 
 * @function   :BarReport test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void BarReport_Test(void)
{
	uint16_t i;	

	DrawTestPage("测试14:GUI BarReport");
	LCD_Fill(0,20,lcddev.width-1,lcddev.height-20,WHITE);
	POINT_COLOR = BLACK;
	//画纵坐标
	LCD_DrawLine(20, 50, 20, 210);
	LCD_DrawLine(10, 60, 20, 50);
	LCD_DrawLine(30, 60, 20, 50);
	//画横坐标
	LCD_DrawLine(20, 210, 220, 210);
	LCD_DrawLine(210, 200, 220, 210);
	LCD_DrawLine(210, 220, 220, 210);
	//画条形
	LCD_Fill(35, 80, 55, 209,RED);
	LCD_Fill(75, 130, 95, 209,YELLOW);
	LCD_Fill(115, 60, 135, 209,BLUE);
	LCD_Fill(155, 90, 175, 209,GREEN);
	//条形渐变
	delay_ms(50);
	for(i=81;i<209;i++) //红色条降低
	{
		LCD_Fill(35, 80, 55, i,WHITE);
		delay_ms(10);
	}
	for(i=208;i>100;i--) //红色条升高
	{
		LCD_Fill(35, i, 55, 209,RED);
		delay_ms(10);
	}
	for(i=129;i>80;i--) //黄色条升高
	{
		LCD_Fill(75, i, 95, 130,YELLOW);
		delay_ms(10);
	}
	for(i=25;i<160;i++) //蓝色条降低
	{
		LCD_Fill(115, 24, 135, i,WHITE);
		delay_ms(10);
	}		
	delay_ms(1500);
}

/*****************************************************************************
 * @name       :void Window_Test(void)
 * @date       :2018-12-29 
 * @function   :Window test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Window_Test(void)
{

	uint16_t xstart=2,ystart=30,xend=lcddev.width*2/3,yend=lcddev.height-30;
	uint8_t i=3;
	DrawTestPage("测试15:GUI Window");
	LCD_Fill(0,20,lcddev.width-1,lcddev.height-20,GRAY);
	do
	{
		Draw_Window(xstart,ystart,xend,yend,"OK");
		delay_ms(500);
		delay_ms(500);
		xstart+=15;ystart+=15;xend-=30;yend-=30;
	}while(--i);
	delay_ms(1500);
}

/*****************************************************************************
 * @name       :void Button_Test(void)
 * @date       :2018-12-29 
 * @function   :Button test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Button_Test(void)
{		  	
	DrawTestPage("测试16:GUI Button");
	LCD_Fill(0,20,lcddev.width-1,lcddev.height-20,WHITE);
	Draw_TextBox(30, 60, 170, 90);	 // 显示一个文字输入框
	Draw_Button(180, 60, 235, 90);			 // 显示1个按钮
	POINT_COLOR = BLACK;
	BACK_COLOR = LGRAY;
	Show_Str(184,67,POINT_COLOR,BACK_COLOR,"Search",16,1);

	
	POINT_COLOR = BLUE;
	BACK_COLOR = WHITE;
	Show_Str(30,38,POINT_COLOR,BACK_COLOR,"News",16,1);
	LCD_DrawLine(30,55,62,55);
	Show_Str(118,38,POINT_COLOR,BACK_COLOR,"Pic",16,1);
	LCD_DrawLine(118,55,150,55);
	POINT_COLOR = BLACK;
	Show_Str(70,38,POINT_COLOR,BACK_COLOR,"Label",16,1);
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
	
	LCD_ShowChar(35, 67, POINT_COLOR,BACK_COLOR,'C',16,1);
	delay_ms(500);
	LCD_ShowChar(43, 67, POINT_COLOR,BACK_COLOR,'o',16,1);
	delay_ms(500);
	LCD_ShowChar(51, 67, POINT_COLOR,BACK_COLOR,'r',16,1);
	delay_ms(500);
	LCD_ShowChar(58, 67, POINT_COLOR,BACK_COLOR,'t',16,1);
	delay_ms(500);
	LCD_ShowChar(66, 67, POINT_COLOR,BACK_COLOR,'e',16,1);
	delay_ms(500);
	LCD_ShowChar(74, 67, POINT_COLOR,BACK_COLOR,'x',16,1);
	delay_ms(500);
	LCD_ShowChar(82, 67, POINT_COLOR,BACK_COLOR,'-',16,1);
	delay_ms(500);
	LCD_ShowChar(88, 67, POINT_COLOR,BACK_COLOR,'M',16,1);
	delay_ms(500);


	SetButton(180, 60, 235, 90);			 // 按下“搜索”按钮
	POINT_COLOR = BLACK;
	BACK_COLOR = LGRAY;
	Show_Str(184,67,POINT_COLOR,BACK_COLOR,"Search",16,1);
	delay_ms(500);

	EscButton(180, 60, 235, 90);			 // 放开“搜索”按钮
	POINT_COLOR = BLACK;
	BACK_COLOR = LGRAY;
	Show_Str(184,67,POINT_COLOR,BACK_COLOR,"Search",16,1);
	POINT_COLOR = RED;
	BACK_COLOR = WHITE;		 
	Show_Str(12,100,POINT_COLOR,BACK_COLOR,"The ARM Cortex-M is a group",16,1 );
	Show_Str(12,120,POINT_COLOR,BACK_COLOR,"of 32-bit RISC ARM processor",16,1 );
	Show_Str(12,140,POINT_COLOR,BACK_COLOR,"cores licensed by ARM Holdings.",16,1 );
	Show_Str(12,160,POINT_COLOR,BACK_COLOR,"The cores are intended for ",16,1 );
	Show_Str(12,180,POINT_COLOR,BACK_COLOR,"microcontroller use,and consist",16,1);
	Show_Str(12,200,POINT_COLOR,BACK_COLOR,"of the Cortex-M0/M1/M2/M3/M4.",16,1);
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
	delay_ms(500);
}
