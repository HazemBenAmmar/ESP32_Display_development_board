/**********************************************************************************************************/ 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//����Ӳ����Ӳ������STM32F103VCT6������8M������Ƶ72M
//Һ������ for STM32
//�Ա���վ��http://jczn.taobao.com
//All rights reserved
/*********************************************************************************************************/ 
//=========================================��Դ����================================================//
//     LCDģ��                       STM32��Ƭ��
//      VCC                 ��        DC5V/3.3V      //��Դ
//      GND                 ��          GND          //��Դ��
//=======================================Һ���������߽���==========================================//
//��ģ��Ĭ��������������ΪSPI����
//     LCDģ��                      STM32��Ƭ��    
//    SDI(MOSI)             ��          PA7         //Һ����SPI��������д�ź�
//    SDO(MISO)             ��          PA6         //Һ����SPI�������ݶ��źţ��������Ҫ�������Բ�����
//=======================================Һ���������߽���==========================================//
//     LCDģ�� 					            STM32��Ƭ�� 
//       LED                ��          PB9         //Һ������������źţ��������Ҫ���ƣ���5V��3.3V
//       SCK                ��          PA5         //Һ����SPI����ʱ���ź�
//      DC/RS               ��          PC4         //Һ��������/��������ź�
//       RST                ��          PB0         //Һ������λ�����ź�
//       CS                 ��          PA4         //Һ����Ƭѡ�����ź�
//=========================================������������============================================//
//���ģ�鲻���������ܻ��ߴ��д������ܣ����ǲ���Ҫ�������ܣ�����Ҫ���д���������
//	   LCDģ��                       STM32��Ƭ�� 
//      T_IRQ(C_INT)        ��          PC10         //�����������ж��ź�
//      T_DO (C_SDA)        ��          PC2          //������SPI���߶��ź�
//      T_DIN               ��          PC3          //������SPI����д�ź�
//      T_CS (C_RST)        ��          PC0          //������Ƭѡ�����ź�
//      T_CLK(C_SCL)        ��          PC1          //������SPI����ʱ���ź�
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
void xianshi(void);//��ʾ��Ϣ

void refshow(void);//ˢ����ʾ	 
u8 stringfind(u8 *buf,u8 *val);

u8 ddown=0;//��ǰ�����µ��ǵڼ�������
u8 bw=65;//�������
u8 buput[9];//���뻺��
u8 buputlen=0;//����
u8 interface=16;
u16 bsecolor=BLUE;//��ťѡ�ֺ����ɫ
u16 bbcolor=RED;//��ť����ɫ��
u16 bfontcolor=WHITE;//��ť����ɫ
u16 xianshicolor=RED;//��Ϣ��ʾ��ɫ
 
u16 saveid;//�����ID
u8 savebus;	//����Ľӿ�   

u16 strtoint(u8 *str)
{
	u16 i;
	i=(((u16)(str[0]-'0')*16+(str[1]-'0'))<<8)+(str[2]-'0')*16+(str[3]-'0');	  
	return i;	 
}
void refput()//ˢ����ʾ
{
	int i,x,y;
	x=80;
	y=50;
	POINT_COLOR=RED;//�������� 

	LCD_ShowString(10,y,100,16,16,"SET IC:");	
	LCD_Fill(x,y,x+100,y+16,WHITE);  	
	for(i=0;i<buputlen;i++)
	{
	   LCD_ShowxNum(x,y,buput[i]-'0',1,16,1);
	   x+=9;
	}

}
void showbutton(u8 val,u16 color)//��ʾ����
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
		POINT_COLOR=bfontcolor;//��������
		LCD_ShowString(45,365,50,16,16,"8BIT");
		LCD_ShowString(142,365,50,16,16,"16BIT");
	}
	 
	POINT_COLOR=bfontcolor;//��������
	if(val<10)
	{
		LCD_ShowxNum(dx+25,dy+20,val,1,16,1);
	}else if(val==10)  //���
	{
	   LCD_ShowString(dx+10,dy+20,50,16,16,"CLEAR");
	}else if(val==11)  //ȷ��
	{
	   LCD_ShowString(dx+20,dy+20,100,16,16,"OK");
	}

}
		
void Load_Drow_Dialog(void)
{
	LCD_Clear(WHITE);//����   
 	POINT_COLOR=BLUE;//��������Ϊ��ɫ 
	LCD_ShowString(lcddev.width-24,0,200,16,16,"RST");//��ʾ��������
  POINT_COLOR=RED;//���û�����ɫ 
}
void xianshi()//��ʾ��Ϣ
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
	}else	//����״̬
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
void refshow(void)	 //ˢ����ʾ
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
void jiance(u8 key) //��ⰴ��
{
	if(key==1)	//KEY_RIGHT����,��ִ��У׼����
	{
		LCD_Clear(WHITE);//����
	    TP_Adjust();  //��ĻУ׼ 
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
		refshow();//ˢ����ʾ
	}

}
u8 idfind(u8 *buf,u8 *val,u8 len)
{
	 u8 i;
	 u8 dz=0;//��ǰƥ�䵽�������ݵĵڼ���
	 for(i=0;i<len;i++)
	 {	 	
	 	if(buf[i]==val[dz])
		{
			dz++;
			if((val[dz]<='~')&&(val[dz]>=' '))//û��
    		{
			}
			else  //����
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
u8 chuankou()  //ɨ�贮��
{  
	u8 len;	
	u8 rr=0;//�Ƿ�Ҫ���³�ʼ��
	u8 b1;
	u16 id1;
	u8 idstr[4];
	u8 i;
	if(USART_RX_STA&0x8000)
	{	
		len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���

		if(len>9)
		{
			 LCD_Clear(BLACK);
	  		 delay_ms(100);

		   	if(idfind(USART_RX_BUF,"if=8",len)>0) //����Ϊ8λ
			{
				lcddev.bus16=8;
				rr=1;
			}
			if(idfind(USART_RX_BUF,"if=16",len)>0) //����Ϊ8λ
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
		   if(rr==1) //���³�ʼ��
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
				if(ceshishuju()==1) //����������
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

	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
 	LED_Init();			     //LED�˿ڳ�ʼ��
  SPI_Flash_Init();//��ʼ��Flash;
	KEY_Init();	 //������ʼ��	 
	
	//����LCD���ò���
	SPI_Flash_Read((void *)&lcddev.id,100,2); 
	SPI_Flash_Read((void *)&lcddev.bus16,102,1); 

	lcddev.id=0x9488;
  lcddev.bus16=2;
	lcddev.busauto=0;
	lcddev.shezhi=0;	   	  
 
	if(lcddev.id==0x9488) //SPI��
	{ 
		lcddev.bus16=2;//SPI���߽ӿ�
	}	

	SPI1_Init();	//SPI1��ʼ��
	LCD_Init();	
	tp_dev.init();//������ʼ��	 			
 	POINT_COLOR=RED;//��������Ϊ��ɫ 


	 if(lcddev.shezhi==0)
	 {
	    if(ceshishuju()==1) //����������
	   	{
	    	xianshi();
	    	showqq();
				delay_ms(500);
				for(i=0;i<9;i++)
				{
				state++;
				refshow();//ˢ����ʾ //SPI9588����ִ��
				delay_ms(500);
				}
				state=0;
				
		}
 	  }else //����״̬
	  {
		  xianshi();
	  	  for(i=0;i<14;i++)
		  { 
		  	showbutton(i,bbcolor);
		  }
	  }

//	copyimage();//����һ���ߣ����100
//	beepms(200);
	while(1)
	{ 
	    
	   key=KEY_Scan(0);//ɨ�谴��		   
	   tp_dev.scan(0); //ɨ�败��
	   chuankou();//ɨ�贮��
	
			
		if(tp_dev.sta&TP_PRES_DOWN)			//������������
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
				key=KEY_Scan(0);//ɨ�谴��
		    	tp_dev.scan(0);	
				if(tp_dev.sta&TP_PRES_DOWN)			//������������
				{			
				 	if(tp_dev.x<lcddev.width&&tp_dev.y<lcddev.height)
					{	
						 if(lcddev.shezhi==0)
						 {
							if(tp_dev.x>(lcddev.width-24)&&tp_dev.y<16)Load_Drow_Dialog();//���
							else TP_Draw_Big_Point(tp_dev.x,tp_dev.y,RED);		//��ͼ	  
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
				    			showbutton(ddown-1,bbcolor);//ˢ�¼��̰�ť 		
				  			 }
			  				 ddown=0;
						}
					}
				} 							
			} 			
		}

	    
	   jiance(key);//��ⰴ��

		i++;
		if(i==65000)
		{
			i=0;
			LED0=!LED0;
		}
	}
}


