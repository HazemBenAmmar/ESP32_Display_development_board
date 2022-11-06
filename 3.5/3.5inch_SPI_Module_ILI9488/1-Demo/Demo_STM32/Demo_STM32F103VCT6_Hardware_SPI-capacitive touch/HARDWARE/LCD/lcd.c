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
#include "lcd.h"
#include "stdlib.h"
#include "font.h" 
#include "usart.h"	 
#include "delay.h"	   
#include "spi.h"	 
				 
//LCD�Ļ�����ɫ�ͱ���ɫ	   
u16 POINT_COLOR=0x0000;	//������ɫ
u16 BACK_COLOR=0xFFFF;  //����ɫ 

u16  HDP=0;
u16  HT=0;
u16  HPS=0;
u16  LPS=0;
u8   HPW=0;

u16  VDP=0;
u16  VT=0;
u16  VPS=0;
u16  FPS=0;
u8   VPW=0;	  

//����LCD��Ҫ����
//Ĭ��Ϊ����
_lcd_dev lcddev;
	
		   
//д�Ĵ�������
//regval:�Ĵ���ֵ
void LCD_WR_REG(u16 regval)
{ 
	switch(lcddev.bus16)
	{
		case 1:
		LCD->LCD_REG=regval;//д��Ҫд�ļĴ������
		break;
		case 0:
			if(lcddev.id!=0x9341)
			{
			LCD->LCD_REG = regval;		//д��Ҫд�ļĴ������	 
			LCD->LCD_REG = regval<<8;		//д��Ҫд�ļĴ������
			}else
			{
				LCD->LCD_REG = regval<<8;		//д��Ҫд�ļĴ������
			}
		break;
		case 2:
		SPILCD_CS_RESET;  //LCD_CS=0
	  SPILCD_RS_RESET;
		SPI_WriteByte(SPI1,regval&0x00FF);
		SPILCD_CS_SET;  //LCD_CS=1
		break;
	}		 
}
//д�Ĵ�������
//data:Ҫд���ֵ
void LCD_WR_DATA(u16 data)
{
	switch(lcddev.bus16)	
	{
		case 1:
		LCD->LCD_RAM=data;
		break;
		case 0:			
		LCD->LCD_RAM=data;
		LCD->LCD_RAM=data<<8;			
		break;
		case 2:
		SPILCD_CS_RESET;  //LCD_CS=0
		SPILCD_RS_SET;	
        if(lcddev.id==0x9488)
        {
          //18Bit	
        	SPI_WriteByte(SPI1,(data>>8)&0xF8);//RED
        	SPI_WriteByte(SPI1,(data>>3)&0xFC);//GREEN
        	SPI_WriteByte(SPI1,data<<3);//BLUE
        }
        else
        {
    		SPI_WriteByte(SPI1,data>>8);
    		SPI_WriteByte(SPI1,data);
        }
		SPILCD_CS_SET;  //LCD_CS=1
		break;
	} 	 
}

//9341�ļĴ�������
void LCD_WR_DATA9341(u16 data)
{
	switch(lcddev.bus16)	
	{
		case 1:
		LCD->LCD_RAM=data;
		break;
		case 0:
			if(lcddev.id!=0x9341)
			{
				LCD->LCD_RAM=data;
				LCD->LCD_RAM=data<<8;
			}else
			{
				LCD->LCD_RAM=data<<8;
			}		
		break;
		case 2:
		SPILCD_CS_RESET;  //LCD_CS=0
		SPILCD_RS_SET;	
		SPI_WriteByte(SPI1,data>>8);
		SPI_WriteByte(SPI1,data);
		SPILCD_CS_SET;  //LCD_CS=1
		break;
	} 	 
}
void LCD_WR_DATA8(u8 da)   //д8λ����,������SPI�ӿ�
{
	SPILCD_CS_RESET;  //LCD_CS=0
	SPILCD_RS_SET;				    	   
	SPI_WriteByte(SPI1,da);	
	SPILCD_CS_SET;  //LCD_CS=1   			 
}
//��LCD����
//����ֵ:������ֵ
u16 LCD_RD_DATA(void)
{	
									    	   
	if(lcddev.bus16==1) //16λ�ӿ�
	{
		return LCD->LCD_RAM;	
	}
	else			//��������-8λ����ģʽ
	{
		u16 h,l;
		h=LCD->LCD_RAM;
		l=LCD->LCD_RAM;
		return h+(l>>8);
	}		 
}					   
//д�Ĵ���
//LCD_Reg:�Ĵ�����ַ
//LCD_RegValue:Ҫд�������
void LCD_WR_REG_DATA(u8 LCD_Reg, u16 LCD_RegValue)
{
	LCD_WR_REG(LCD_Reg);
	if(lcddev.id!=0x9341)
	{
	LCD_WR_DATA(LCD_RegValue);
	}else
	{
		LCD_WR_DATA9341(LCD_RegValue);
	}
}	   
//���Ĵ���
//LCD_Reg:�Ĵ�����ַ
//����ֵ:����������
u16 LCD_ReadReg(u8 LCD_Reg)
{
	u16 myid=0;
	u8 x=0;
	while(x<5 && (myid==0||myid==0xffff))	  //��5��
	{	
		LCD_WR_REG_DATA(0x0000,0x0001);										   
		delay_us(200);
		LCD_WR_REG(LCD_Reg);		//д��Ҫ���ļĴ������
		delay_us(5);		  
		myid=LCD_RD_DATA();		//���ض�����ֵ
		x++;
	}
	return myid;
}   
//��ʼдGRAM
void LCD_WriteRAM_Prepare(void)
{
	LCD_WR_REG(lcddev.wramcmd);  
}	 
//��ILI93xx����������ΪGBR��ʽ��������д���ʱ��ΪRGB��ʽ��
//ͨ���ú���ת��
//c:GBR��ʽ����ɫֵ
//����ֵ��RGB��ʽ����ɫֵ
u16 LCD_BGR2RGB(u16 c)
{
	u16  r,g,b,rgb;   
	b=(c>>0)&0x1f;
	g=(c>>5)&0x3f;
	r=(c>>11)&0x1f;	 
	rgb=(b<<11)+(g<<5)+(r<<0);		 
	return(rgb);
} 
//��mdk -O1ʱ���Ż�ʱ��Ҫ����
//��ʱi
void opt_delay(u8 i)
{
	while(i--);
}
//��ȡ��ĳ�����ɫֵ	 
//x,y:����
//����ֵ:�˵����ɫ
u16 LCD_ReadPoint(u16 x,u16 y)
{
	LCD_SetCursor(x,y);	
	if(lcddev.id==0x1943||lcddev.id==0x1907||lcddev.id==0x1905)
	{
		LCD_WR_REG(0x2E);  
	}
	else
	{
	   LCD_WR_REG(lcddev.wramcmd);
	}
	if(lcddev.id==0x9325||lcddev.id==0x9328||lcddev.id==0x9335)
	{
		opt_delay(2);
		return 	LCD_BGR2RGB( LCD_RD_DATA());

	}	
    return LCD_RD_DATA();									
}			 



//���ù��λ��
//Xpos:������
//Ypos:������
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{	 
    LCD_WR_REG(lcddev.setxcmd);	
	  LCD_WR_DATA8(Xpos>>8); 
		LCD_WR_DATA8(Xpos&0XFF);		
	  LCD_WR_DATA8(319>>8);	    
		LCD_WR_DATA8(319&0x00ff);
    LCD_WR_REG(lcddev.setycmd);	
    LCD_WR_DATA8(Ypos>>8); 
	  LCD_WR_DATA8(Ypos&0XFF);		
    LCD_WR_DATA8(479>>8);	    
		LCD_WR_DATA8(479&0x00ff);	 
} 
 

//����
//x,y:����
//POINT_COLOR:�˵����ɫ
void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_SetCursor(x,y);		//���ù��λ�� 
	LCD_WriteRAM_Prepare();	//��ʼд��GRAM
	LCD_WR_DATA(POINT_COLOR); 
}
u8 ceshishuju()  //����������
{
	u16 cc=1;
	u16 i;
	u16 da; 	
	u16 ll=0;
 	ll=POINT_COLOR;

   if(lcddev.id!=0x1943&&lcddev.id!=0x0043&&lcddev.id!=0x1905&&lcddev.id!=0x0050&&lcddev.id!=0x1907&&lcddev.id!=0x0070)
   {
  	 return 1;
   }
	
	for(i=0;i<16;i++)
	{
		POINT_COLOR=cc<<i;
		LCD_DrawPoint(i,0);	
	}
	LCD_DrawPoint(i+1,0);
	for(i=0;i<16;i++)
	{
		da=LCD_ReadPoint(i,0);	
		da=LCD_ReadPoint(i,0);	
		if(da!=(cc<<i))//�����쳣
		{
			LCD_Clear(BLACK);
			POINT_COLOR=RED;
			LCD_ShowString(0,0,200,16,16,"DATA ERROR AT");
			LCD_ShowNum(100,0,cc<<i,6,16);
			LCD_ShowNum(100,40,da,6,16);
		   	POINT_COLOR=ll;
			return 0;
		}
	} 		 

	POINT_COLOR=ll;
	return 1;
}

//��ʼ��lcd
void LCD_Init(void)
{ 	
// 	u16 x1=0;
	GPIO_InitTypeDef GPIO_InitStructure;
//	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
//    FSMC_NORSRAMTimingInitTypeDef  readWriteTiming; 
//	FSMC_NORSRAMTimingInitTypeDef  writeTiming;

   	// Enable FSMC, GPIOD, GPIOE clocks
  	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE,ENABLE);

	// Set PD.00(D2), PD.01(D3), PD.04(NOE), PD.05(NWE), PD.07(NE1), PD.08(D13),
  	// PD.09(D14), PD.10(D15), PD.13(A18), PD.14(D0), PD.15(D1) as alternate 
  	// function push pull 
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |
                                  GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10| 
                                  GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_Init(GPIOD, &GPIO_InitStructure);

  	// Set PE.07(D4), PE.08(D5), PE.09(D6), PE.10(D7), PE.11(D8), PE.12(D9), PE.13(D10),
  	// PE.14(D11), PE.15(D12) as alternate function push pull */
  	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | 
                                   GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | 
                                   GPIO_Pin_15;
  	GPIO_Init(GPIOE, &GPIO_InitStructure);

  	//PB14 --> LCD_RST
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
 

			SPILCD_RST_RESET ;	//LCD_RST=0	 
			delay_ms(50); // delay 20 ms 
	    SPILCD_RST_SET ;	//LCD_RST=1		
			delay_ms(50);

				
			lcddev.wramcmd=0X2C;
	 		lcddev.setxcmd=0X2A;
			lcddev.setycmd=0X2B;  	 
			lcddev.width=320;
			lcddev.height=480;
      //LCDʹ�õ�ICΪ9488 �����ǽӿ�ΪSPI
      LCD_WR_REG(0XF7);
    	LCD_WR_DATA8(0xA9);
    	LCD_WR_DATA8(0x51);
    	LCD_WR_DATA8(0x2C);
    	LCD_WR_DATA8(0x82);
    	LCD_WR_REG(0xC0);
    	LCD_WR_DATA8(0x11);
    	LCD_WR_DATA8(0x09);
    	LCD_WR_REG(0xC1);
    	LCD_WR_DATA8(0x41);
    	LCD_WR_REG(0XC5);
    	LCD_WR_DATA8(0x00);
    	LCD_WR_DATA8(0x0A);
    	LCD_WR_DATA8(0x80);
    	LCD_WR_REG(0xB1);
    	LCD_WR_DATA8(0xB0);
    	LCD_WR_DATA8(0x11);
    	LCD_WR_REG(0xB4);
    	LCD_WR_DATA8(0x02);
    	LCD_WR_REG(0xB6);//���Ʒ���
    	LCD_WR_DATA8(0x02);
    	LCD_WR_DATA8(0x22);//0X42�ĳ�0X22
    	LCD_WR_REG(0xB7);
    	LCD_WR_DATA8(0xc6);
    	LCD_WR_REG(0xBE);
    	LCD_WR_DATA8(0x00);
    	LCD_WR_DATA8(0x04);
    	LCD_WR_REG(0xE9);
    	LCD_WR_DATA8(0x00);
    	LCD_WR_REG(0x36);
    	LCD_WR_DATA8((1<<3)|(0<<6)|(0<<7));//BGR==1,MY==0,MX==0,MV==0
    	LCD_WR_REG(0x3A);
    	LCD_WR_DATA8(0x66);
    	LCD_WR_REG(0xE0);
    	LCD_WR_DATA8(0x00);
    	LCD_WR_DATA8(0x07);
    	LCD_WR_DATA8(0x10);
    	LCD_WR_DATA8(0x09);
    	LCD_WR_DATA8(0x17);
    	LCD_WR_DATA8(0x0B);
    	LCD_WR_DATA8(0x41);
    	LCD_WR_DATA8(0x89);
    	LCD_WR_DATA8(0x4B);
    	LCD_WR_DATA8(0x0A);
    	LCD_WR_DATA8(0x0C);
    	LCD_WR_DATA8(0x0E);
    	LCD_WR_DATA8(0x18);
    	LCD_WR_DATA8(0x1B);
    	LCD_WR_DATA8(0x0F);
    	LCD_WR_REG(0XE1);
    	LCD_WR_DATA8(0x00);
    	LCD_WR_DATA8(0x17);
    	LCD_WR_DATA8(0x1A);
    	LCD_WR_DATA8(0x04);
    	LCD_WR_DATA8(0x0E);
    	LCD_WR_DATA8(0x06);
    	LCD_WR_DATA8(0x2F);
    	LCD_WR_DATA8(0x45);
    	LCD_WR_DATA8(0x43);
    	LCD_WR_DATA8(0x02);
    	LCD_WR_DATA8(0x0A);
    	LCD_WR_DATA8(0x09);
    	LCD_WR_DATA8(0x32);
    	LCD_WR_DATA8(0x36);
    	LCD_WR_DATA8(0x0F);
    	LCD_WR_REG(0x11);
    	delay_ms(120);
    	LCD_WR_REG(0x29);
      delay_ms(50);
	    LCD_Clear(WHITE); 
	
}  
//��������
//color:Ҫ���������ɫ
void LCD_Clear(u16 color)
{
	u32 index=0;      
	u32 totalpoint=lcddev.width;
	totalpoint*=lcddev.height; 	//�õ��ܵ���
	LCD_SetCursor(0x00,0x0000);	//���ù��λ�� 
	LCD_WriteRAM_Prepare();     //��ʼд��GRAM	 	  
	for(index=0;index<totalpoint;index++)
	{
		LCD_WR_DATA(color);
	}

}  
//��ָ����������䵥����ɫ
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
{          
	u16 i,j;
	u16 xlen=0;
	if(ex > (lcddev.width-1))
	{
	  ex = lcddev.width-1;
	}
	if(ey > (lcddev.height-1))
	{
		ey = lcddev.height-1;
	}
	xlen=ex-sx+1;	   
	for(i=sy;i<=ey;i++)
	{									   
	 	LCD_SetCursor(sx,i);      				//���ù��λ�� 
		LCD_WriteRAM_Prepare();     			//��ʼд��GRAM	  
		for(j=0;j<xlen;j++)LCD_WR_DATA(color);	//���ù��λ�� 	    
	}
}  
//��ָ�����������ָ����ɫ��			 
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color)
{  
	u16 height,width;
	u16 i,j;
	width=ex-sx+1; 		//�õ����Ŀ��
	height=ey-sy+1;		//�߶�
 	for(i=0;i<height;i++)
	{
 		LCD_SetCursor(sx,sy+i);   	//���ù��λ�� 
		LCD_WriteRAM_Prepare();     //��ʼд��GRAM
		for(j=0;j<width;j++)LCD->LCD_RAM=color[i*height+j];//д������ 
	}	  
}  
//����
//x1,y1:�������
//x2,y2:�յ�����  
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		LCD_DrawPoint(uRow,uCol);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}    
//������	  
//(x1,y1),(x2,y2):���εĶԽ�����
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}
//��ָ��λ�û�һ��ָ����С��Բ
//(x,y):���ĵ�
//r    :�뾶
void Draw_Circle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //�ж��¸���λ�õı�־
	while(a<=b)
	{
		LCD_DrawPoint(x0+a,y0-b);             //5
 		LCD_DrawPoint(x0+b,y0-a);             //0           
		LCD_DrawPoint(x0+b,y0+a);             //4               
		LCD_DrawPoint(x0+a,y0+b);             //6 
		LCD_DrawPoint(x0-a,y0+b);             //1       
 		LCD_DrawPoint(x0-b,y0+a);             
		LCD_DrawPoint(x0-a,y0-b);             //2             
  	LCD_DrawPoint(x0-b,y0-a);             //7     	         
		a++;
		//ʹ��Bresenham�㷨��Բ     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
} 									  
//��ָ��λ����ʾһ���ַ�
//x,y:��ʼ����
//num:Ҫ��ʾ���ַ�:" "--->"~"
//size:�����С 12/16
//mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
{  							  
    u8 temp,t1,t;
	u16 y0=y;
	u16 colortemp=POINT_COLOR;      			     
	//���ô���		   
	num=num-' ';//�õ�ƫ�ƺ��ֵ
	if(!mode) //�ǵ��ӷ�ʽ
	{
	    for(t=0;t<size;t++)
	    {   
			if(size==12)temp=asc2_1206[num][t];  //����1206����
			else temp=asc2_1608[num][t];		 //����1608���� 	                          
	        for(t1=0;t1<8;t1++)
			{			    
		        if(temp&0x80)POINT_COLOR=colortemp;
				else POINT_COLOR=BACK_COLOR;
				LCD_DrawPoint(x,y);	
				temp<<=1;
				y++;
				if(y>=lcddev.height){POINT_COLOR=colortemp;return;}//��������
				if((y-y0)==size)
				{
					y=y0;
					x++;
					if(x>=lcddev.width){POINT_COLOR=colortemp;return;}//��������
					break;
				}
			}  	 
	    }    
	}else//���ӷ�ʽ
	{
	    for(t=0;t<size;t++)
	    {   
			if(size==12)temp=asc2_1206[num][t];  //����1206����
			else temp=asc2_1608[num][t];		 //����1608���� 	                          
	        for(t1=0;t1<8;t1++)
			{			    
		        if(temp&0x80)LCD_DrawPoint(x,y); 
				temp<<=1;
				y++;
				if(y>=lcddev.height){POINT_COLOR=colortemp;return;}//��������
				if((y-y0)==size)
				{
					y=y0;
					x++;
					if(x>=lcddev.width){POINT_COLOR=colortemp;return;}//��������
					break;
				}
			}  	 
	    }     
	}
	POINT_COLOR=colortemp;	    	   	 	  
}   
//m^n����
//����ֵ:m^n�η�.
u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}			 
//��ʾ����,��λΪ0,����ʾ
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//color:��ɫ 
//num:��ֵ(0~4294967295);	 
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,' ',size,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,0); 
	}
} 
//��ʾ����,��λΪ0,������ʾ
//x,y:�������
//num:��ֵ(0~999999999);	 
//len:����(��Ҫ��ʾ��λ��)
//size:�����С
//mode:
//[7]:0,�����;1,���0.
//[6:1]:����
//[0]:0,�ǵ�����ʾ;1,������ʾ.
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
{  
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)LCD_ShowChar(x+(size/2)*t,y,'0',size,mode&0X01);  
				else LCD_ShowChar(x+(size/2)*t,y,' ',size,mode&0X01);  
 				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01); 
	}
} 
//��ʾ�ַ���
//x,y:�������
//width,height:�����С  
//size:�����С
//*p:�ַ�����ʼ��ַ		  
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p)
{         
	u8 x0=x;
	width+=x;
	height+=y;
    while((*p<='~')&&(*p>=' '))//�ж��ǲ��ǷǷ��ַ�!
    {       
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//�˳�
        LCD_ShowChar(x,y,*p,size,1);
        x+=size/2;
        p++;
    }  
}

void showimage(u16 x,u16 y) //��ʾ40*40ͼƬ
{  
	u16 i,j,k;
	u16 da;
	k=0;
	for(i=0;i<40;i++)
	{	
		LCD_SetCursor(x,y+i);
		LCD_WriteRAM_Prepare();     			//��ʼд��GRAM	
		for(j=0;j<40;j++)
		{
			da=qqimage[k*2+1];
			da<<=8;
			da|=qqimage[k*2]; 
			LCD_WR_DATA(da);					
			k++;  			
		}
	}
}
 void copyimage() //����һ����
{
	u16 i;
	u16 da;
	u16 ll;

    ll=POINT_COLOR;
	POINT_COLOR=RED;
	 for(i=100;i<150;i++)
	 {
		LCD_DrawPoint(i,100);
	 }
	LCD_ShowNum(0,0,POINT_COLOR,5,16);//��ʾ��ɫֵ��ʮ����

	 for(i=100;i<150;i++)
	 {
		da=LCD_ReadPoint(i,100);
		da=LCD_ReadPoint(i,100);
		POINT_COLOR=da;
		LCD_DrawPoint(i,120);
	 	if(i==100)
		{
			LCD_ShowNum(0,20,da,5,16); //��ʾ�����ĵ�һ�������ɫֵ��ʮ����
		}
		if(i==101)
		{
			LCD_ShowNum(0,40,da,5,16);
		}
		if(i==102)
		{
			LCD_ShowNum(0,60,da,5,16);
		}
	
	 }

	 POINT_COLOR=ll;
	 while(1)
	 {
	 }
}
