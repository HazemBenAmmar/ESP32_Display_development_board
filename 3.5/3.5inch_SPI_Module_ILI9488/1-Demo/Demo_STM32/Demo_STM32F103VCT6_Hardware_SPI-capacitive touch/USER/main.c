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
#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "24cxx.h"
#include "flash.h"
#include "touch.h"
#include "flash.h"
#include "spi.h"	  

u8 xx=0;
u8 state=0;
u8 idfind(u8 *buf,u8 *val,u8 len);
void beepms(u16 va);
void xianshi(void);//显示信息

void refshow(void);//刷新显示	 
u8 stringfind(u8 *buf,u8 *val);

u8 ddown=0;//当前被按下的是第几个键；
u8 bw=65;//按键宽度
u8 buput[9];//输入缓冲
u8 buputlen=0;//长度
u8 interface=16;
u16 bsecolor=BLUE;//按钮选种后的颜色
u16 bbcolor=RED;//按钮背景色；
u16 bfontcolor=WHITE;//按钮字体色
u16 xianshicolor=RED;//信息显示颜色
 
u16 saveid;//保存的ID
u8 savebus;	//保存的接口   

u16 strtoint(u8 *str)
{
	u16 i;
	i=(((u16)(str[0]-'0')*16+(str[1]-'0'))<<8)+(str[2]-'0')*16+(str[3]-'0');	  
	return i;	 
}
void refput()//刷新显示
{
	int i,x,y;
	x=80;
	y=50;
	POINT_COLOR=RED;//设置字体 

	LCD_ShowString(10,y,100,16,16,"SET IC:");	
	LCD_Fill(x,y,x+100,y+16,WHITE);  	
	for(i=0;i<buputlen;i++)
	{
	   LCD_ShowxNum(x,y,buput[i]-'0',1,16,1);
	   x+=9;
	}

}
void showbutton(u8 val,u16 color)//显示按键
{
	u16 dx;
	u16 dy;
	u16 dc;
	dx=(val%3)*(bw+2);
	dy=(val/3)*(bw+2);
	dx+=20;
	dy+=70;
	dc=12;

	 if(val<12)
	{
		LCD_Fill(dx,dy,dx+bw-1,dy+bw-1,color);
	}else if(val==12||val==13)  //interface
	{
		if(interface==8)
		{
			LCD_Fill((dc-12)*100+20,350,(dc-12)*100+95+20,350+49,bsecolor);
			dc++;
			LCD_Fill((dc-12)*100+20,350,(dc-12)*100+95+20,350+49,bbcolor);
		}else
		{													   
		   	LCD_Fill((dc-12)*100+20,350,(dc-12)*100+95+20,350+49,bbcolor);
			dc++;
			LCD_Fill((dc-12)*100+20,350,(dc-12)*100+95+20,350+49,bsecolor);
		}
		POINT_COLOR=bfontcolor;//设置字体
		LCD_ShowString(45,365,50,16,16,"8BIT");
		LCD_ShowString(142,365,50,16,16,"16BIT");
	}
	 
	POINT_COLOR=bfontcolor;//设置字体
	if(val<10)
	{
		LCD_ShowxNum(dx+25,dy+20,val,1,16,1);
	}else if(val==10)  //清除
	{
	   LCD_ShowString(dx+10,dy+20,50,16,16,"CLEAR");
	}else if(val==11)  //确定
	{
	   LCD_ShowString(dx+20,dy+20,100,16,16,"OK");
	}

}
		
void Load_Drow_Dialog(void)
{
	LCD_Clear(WHITE);//清屏   
 	POINT_COLOR=BLUE;//设置字体为蓝色 
	LCD_ShowString(lcddev.width-24,0,200,16,16,"RST");//显示清屏区域
  POINT_COLOR=RED;//设置画笔蓝色 
}
void xianshi()//显示信息
{   

	u8 idstr[5];
	BACK_COLOR=WHITE;
	POINT_COLOR=RED;	
	
	if(lcddev.shezhi==0)
	{
		LCD_ShowString(0,2,200,16,16,"ID:");	    
		inttohex(lcddev.id,idstr);	  
		LCD_ShowString(50,2,200,16,16,idstr);
		if(lcddev.bus16==1)
		{
			 LCD_ShowString(100,2,200,16,16,"16 Bit");
		}else
		{
			LCD_ShowString(100,2,200,16,16,"8 Bit");
		} 	 
	}else	//设置状态
	{
		LCD_Fill(0,0,239,35,WHITE);

		SPI_Flash_Read((void *)&saveid,100,2); 
  		SPI_Flash_Read((void *)&savebus,102,1); 

		LCD_ShowString(0,2,200,16,16,"SET:ID");	    
		inttohex(saveid,idstr);	  
		LCD_ShowString(60,2,200,16,16,idstr);
		if(savebus==1)
		{
			interface=16;
			LCD_ShowString(100,2,200,16,16,"16 Bit");
		}else
		{
			interface=8;
			LCD_ShowString(100,2,200,16,16,"8 Bit");
		} 	 

		POINT_COLOR=BLACK;
		LCD_ShowString(0,22,200,16,16,"This:ID");	    
		inttohex(lcddev.id,idstr);	  
		LCD_ShowString(60,22,200,16,16,idstr);
		if(lcddev.bus16==1)
		{
			 LCD_ShowString(100,22,200,16,16,"16 Bit");
		}else				   
		{
			LCD_ShowString(100,22,200,16,16,"8 Bit");
		} 

	}

}
void showqq()
{ 
	u16 x,y; 
	x=0;
	y=20;
	while(y<lcddev.height-39)
	{
		x=0;
		while(x<lcddev.width-39)
		{
			showimage(x,y);	
			x+=40;
		}
		y+=40;
	 }


}
void refshow(void)	 //刷新显示
{
		u16 color,rgbw,rgbh,posx;
	u16 i,j,flag;
	//state = 7;
	switch(state)
	{
		case 0:
		LCD_Clear(WHITE);
	    xianshi();
    	showqq();
		break;
		case 1:
		LCD_Clear(BLACK); 
		break;
		case 2:	
		LCD_Clear(WHITE); 
		break;
		case 3:
		LCD_Clear(RED);
		break;
		case 4:
		LCD_Clear(GREEN);
		break;
		case 5:
		LCD_Clear(BLUE);
		break;
		case 6:
		LCD_Clear(10665);
		break;
		case 7:
			color=0;
		posx=0;
		rgbw = lcddev.height/32;
		for(i=0;i<32;i++)
		{
			LCD_Fill(0,posx,lcddev.width-1,posx+rgbw-1,color);
			color += 0x841;
			posx += rgbw;
		}
			break;
		case 8:
			flag = 0;
			for(i=0;i<lcddev.height;i+=40)
			{
				color = flag;
				if(flag == 0)
				{
					flag = 0xffff;
				}
				else
				{
					flag = 0;
				}
				for(j=0;j<lcddev.width;j+=40)
				{
					LCD_Fill(j,i,j+39,i+39,color);
					if(color == 0)
					{
						color = 0xffff;
					}
					else
					{
						color = 0;
					}
				}
			}
			break;
	}	
}
void jiance(u8 key) //检测按键
{
	if(key==1)	//KEY_RIGHT按下,则执行校准程序
	{
		LCD_Clear(WHITE);//清屏
	    TP_Adjust();  //屏幕校准 
		TP_Save_Adjdata();	 
		Load_Drow_Dialog();
	}
	if(key==2)
	{
		state++;
		LCD_Init();
		if(state==9)
		{
			state=0; 
		}
		refshow();//刷新显示
	}

}
u8 idfind(u8 *buf,u8 *val,u8 len)
{
	 u8 i;
	 u8 dz=0;//当前匹配到查找数据的第几个
	 for(i=0;i<len;i++)
	 {	 	
	 	if(buf[i]==val[dz])
		{
			dz++;
			if((val[dz]<='~')&&(val[dz]>=' '))//没完
    		{
			}
			else  //完了
			{
				return i+1;
			}
		}
		else
		{
			dz=0;
		}

	 }
	return 0;
}
u8 chuankou()  //扫描串口
{  
	u8 len;	
	u8 rr=0;//是否要重新初始化
	u8 b1;
	u16 id1;
	u8 idstr[4];
	u8 i;
	if(USART_RX_STA&0x8000)
	{	
		len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度

		if(len>9)
		{
			 LCD_Clear(BLACK);
	  		 delay_ms(100);

		   	if(idfind(USART_RX_BUF,"if=8",len)>0) //设置为8位
			{
				lcddev.bus16=8;
				rr=1;
			}
			if(idfind(USART_RX_BUF,"if=16",len)>0) //设置为8位
			{
				lcddev.bus16=1;
				rr=1;
			} 	
			i= idfind(USART_RX_BUF,"id=",len);
			if(i>0)
			{
				 idstr[0]=USART_RX_BUF[i];
				 idstr[1]=USART_RX_BUF[i+1];
				 idstr[2]=USART_RX_BUF[i+2];
				 idstr[3]=USART_RX_BUF[i+3];

			 	 lcddev.id=strtoint(idstr);
			     rr=1;
			}  		
		   if(rr==1) //重新初始化
		   { 	
		   		state=0; 
				b1=0;
				id1=0;
				while(b1!=lcddev.bus16||id1!=lcddev.id)
				{
					b1=lcddev.bus16;
					id1=lcddev.id;  				                  
					SPI_Flash_Write((void *)&lcddev.id,100,2); 
					SPI_Flash_Write((void *)&lcddev.bus16,102,1); 	   	
	
					SPI_Flash_Read((void *)&lcddev.id,100,2); 
					SPI_Flash_Read((void *)&lcddev.bus16,102,1);  
					beepms(150);
				 }

		   		LCD_Init();	
				if(ceshishuju()==1) //测试数据线
			   	{
			    	xianshi();
			    	showqq();				
				}  			   
		   }
		}



		USART_RX_STA=0;	
	}
	return rr;
}	
void beepms(u16 va)
{
	beep=1;
	delay_ms(va);
    beep=0;
}  				
int main(void)
 {	 
	u16 i=0;	 
	u8 key=0;

	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 	//串口初始化为9600
 	LED_Init();			     //LED端口初始化
  SPI_Flash_Init();//初始化Flash;
	KEY_Init();	 //按键初始化	 
	
	//读出LCD配置参数
	SPI_Flash_Read((void *)&lcddev.id,100,2); 
	SPI_Flash_Read((void *)&lcddev.bus16,102,1); 

	lcddev.id=0x9488;
  lcddev.bus16=2;
	lcddev.busauto=0;
	lcddev.shezhi=0;	   	  
 
	if(lcddev.id==0x9488) //SPI屏
	{ 
		lcddev.bus16=2;//SPI总线接口
	}	

	SPI1_Init();	//SPI1初始化
	LCD_Init();	
	tp_dev.init();//触摸初始化	 			
 	POINT_COLOR=RED;//设置字体为红色 


	 if(lcddev.shezhi==0)
	 {
	    if(ceshishuju()==1) //测试数据线
	   	{
	    	xianshi();
	    	showqq();
				delay_ms(500);
				for(i=0;i<9;i++)
				{
				state++;
				refshow();//刷新显示 //SPI9588程序执行
				delay_ms(500);
				}
				state=0;
				
		}
 	  }else //设置状态
	  {
		  xianshi();
	  	  for(i=0;i<14;i++)
		  { 
		  	showbutton(i,bbcolor);
		  }
	  }

//	copyimage();//拷贝一条线，宽度100
//	beepms(200);
	while(1)
	{ 
	    
	   key=KEY_Scan(0);//扫描按键		   
	   tp_dev.scan(0); //扫描触摸
	   chuankou();//扫描串口
	
			
		if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
		{  
			if(lcddev.shezhi==0)
			{
				if(state!=1)
				{
					LCD_Clear(WHITE);
				}
			}
			while(key==0&&chuankou()==0)
			{			
				key=KEY_Scan(0);//扫描按键
		    	tp_dev.scan(0);	
				if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
				{			
				 	if(tp_dev.x<lcddev.width&&tp_dev.y<lcddev.height)
					{	
						 if(lcddev.shezhi==0)
						 {
							if(tp_dev.x>(lcddev.width-24)&&tp_dev.y<16)Load_Drow_Dialog();//清除
							else TP_Draw_Big_Point(tp_dev.x,tp_dev.y,RED);		//画图	  
						 }	   
					}
				}else
				{
					if(lcddev.shezhi==1)
					{
						if(ddown>0)
						{  
							if(ddown<13)
							{
				    			showbutton(ddown-1,bbcolor);//刷新键盘按钮 		
				  			 }
			  				 ddown=0;
						}
					}
				} 							
			} 			
		}

	    
	   jiance(key);//检测按键

		i++;
		if(i==65000)
		{
			i=0;
			LED0=!LED0;
		}
	}
}


