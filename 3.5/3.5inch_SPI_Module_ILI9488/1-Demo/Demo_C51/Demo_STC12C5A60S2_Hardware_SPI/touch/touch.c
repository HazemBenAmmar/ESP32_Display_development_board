//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//����Ӳ������Ƭ��STC12C5A60S2,����30M  ��Ƭ��������ѹ3.3V
//TFTҺ������ for C51
//�Ա���վ��http://qdtech.taobao.com
//All rights reserved
//********************************************************************************
//=========================================��Դ����================================================//
//5V��DC 5V��Դ
//GND�ӵ�
//=======================================Һ���������߽���==========================================//
//��ģ��Ĭ��������������ΪSPI
//Һ����ģ��            ��Ƭ��
// SDI(MOSI)     ��       P15        //SPIд�ź�
// SDO(MISO)     ��       P16        //SPI���źţ��������Ҫ�����ܣ��˹ܽſɲ���
//=======================================Һ���������߽���==========================================//
//Һ����ģ��            ��Ƭ��
//  CS           ��       P13       //Ƭѡ�����ź�
//  RESET        ��       P33       //��λ�ź�
//  DC           ��       P12       //����/����ѡ������ź�
//  SCK          ��       P17       //SPIʱ���ź�
//  LED          ��       P32       //��������źţ����ʹ��STC89C52RC��Ƭ�����߲���Ҫ���ƣ���3.3V
//=========================================����������=========================================//
//STC89C52RC��Ƭ��ROM̫С���޷����д��������ܵĳ������Դ���������Ҫ����
//��ʹ�ô�������ģ�鱾��������������ɲ�����
//������ʹ�õ�������������ΪSPI
//������ģ��            ��Ƭ��
//  T_CLK        ��       P36       //������SPIʱ���ź�
//  T_CS         ��       P37       //������Ƭѡ�����ź�
//  T_DIN        ��       P34       //������SPIд�ź�
//  T_DO         ��       P35       //������SPI���ź�
//  T_IRQ        ��       P40       //��������Ӧ����źţ��絥Ƭ����P4�飬�����и�����������IO���޸Ĵ��붨��
//**************************************************************************************************/	
#include "sys.h"
#include "touch.h"
#include "lcd.h"
#include "gui.h"

//***���������β�ͬ��ԭ��Ĭ�ϵ�У׼����ֵ���ܻ�������ʶ��׼������У׼����ʹ�ã�������ʹ�ù̶���Ĭ��У׼����
u16 vx=11605,vy=7769;  //�������ӣ���ֵ����1000֮���ʾ���ٸ�ADֵ����һ�����ص� 
u16 chx=3859,chy=226;//Ĭ�����ص�����Ϊ0ʱ��AD��ʼֵ 
//***���������β�ͬ��ԭ��Ĭ�ϵ�У׼����ֵ���ܻ�������ʶ��׼������У׼����ʹ�ã�������ʹ�ù̶���Ĭ��У׼����

struct tp_pix_  tp_pixad,tp_pixlcd;	 //��ǰ���������ADֵ,ǰ�������������ֵ   

//���ش������µ�״̬
u8 tpstate(void)
{
	return 	Penirq;
}

//SPI��ʼ
void spistar(void)                                     
{
	TCS=1;
	DCLK=1;
	DIN=1;
	DCLK=1;
}
//SPIд����
void WriteCharTo7843(unsigned char num)          
{
	unsigned char count=0;
	DCLK=0;
	for(count=0;count<8;count++)
	{
		num<<=1;
		DIN=CY;
		DCLK=0; _nop_();_nop_();_nop_();                //��������Ч
		DCLK=1; _nop_();_nop_();_nop_();
	}
}

//SPI ������
u16 ReadFromCharFrom7843()             
{
	u8 count=0;
	u16 Num=0;
	for(count=0;count<12;count++)
	{
		Num<<=1;		
		DCLK=1; _nop_();_nop_();_nop_();   //�½�����Ч
		DCLK=0; _nop_();_nop_();_nop_();
		if(DOUT)
		{
			Num|=1;
		}
		
	}

return(Num);
}	
//��7846/7843/XPT2046/UH7843/UH7846��ȡadcֵ	  
//0x90=y   0xd0-x
u16 ADS_Read_AD(unsigned char CMD)          
{
	u16 l;
	TCS=0;
	WriteCharTo7843(CMD);        //�Ϳ����ּ��ò�ַ�ʽ��X���� ��ϸ����й�����
	DCLK=1; _nop_();_nop_();_nop_();_nop_();
	DCLK=0; _nop_();_nop_();_nop_();_nop_();
	l=ReadFromCharFrom7843();
	TCS=1;
	return l;
}		   
//��ȡһ������ֵ
//������ȡREAD_TIMES������,����Щ������������,
//Ȼ��ȥ����ͺ����LOST_VAL����,ȡƽ��ֵ 
#define READ_TIMES 15 //��ȡ����
#define LOST_VAL 5	  //����ֵ
u16 ADS_Read_XY(u8 xy)
{
	u16 i, j;
	u16 buf[READ_TIMES];
	u16 sum=0;
	u16 temp;
	for(i=0;i<READ_TIMES;i++)
	{				 
		buf[i]=ADS_Read_AD(xy);	    
	}				    
	for(i=0;i<READ_TIMES-1; i++)//����
	{
		for(j=i+1;j<READ_TIMES;j++)
		{
			if(buf[i]>buf[j])//��������
			{
				temp=buf[i];
				buf[i]=buf[j];
				buf[j]=temp;
			}
		}
	}	  
	sum=0;
	for(i=LOST_VAL;i<READ_TIMES-LOST_VAL;i++)sum+=buf[i];
	temp=sum/(READ_TIMES-2*LOST_VAL);
	return temp;   
} 
//���˲��������ȡ
//��Сֵ��������100.
u8 Read_ADS(u16 *x,u16 *y)
{
	u16 xtemp,ytemp;			 	 		  
	xtemp=ADS_Read_XY(CMD_RDX);
	ytemp=ADS_Read_XY(CMD_RDY);	 									   
	if(xtemp<100||ytemp<100)return 0;//����ʧ��
	*x=xtemp;
	*y=ytemp;
	return 1;//�����ɹ�
}
//2�ζ�ȡADS7846,������ȡ2����Ч��ADֵ,�������ε�ƫ��ܳ���
//50,��������,����Ϊ������ȷ,�����������.	   
//�ú����ܴ�����׼ȷ��
#define ERR_RANGE 20 //��Χ 
u8 Read_ADS2(u16 *x,u16 *y) 
{
	u16 x1,y1;
 	u16 x2,y2;
 	u8 flag;    
    flag=Read_ADS(&x1,&y1);   
    if(flag==0)return(0);
    flag=Read_ADS(&x2,&y2);	
    if(flag==0)return(0);   
    if(((x2<=x1&&x1<x2+ERR_RANGE)||(x1<=x2&&x2<x1+ERR_RANGE))//ǰ�����β�����+-ERR_RANGE��
    &&((y2<=y1&&y1<y2+ERR_RANGE)||(y1<=y2&&y2<y1+ERR_RANGE)))
    {
        *x=(x1+x2)>>1;
        *y=(y1+y2)>>1;		
        return 1;
    }else return 0;	  
} 
//��ȷ��ȡһ������,У׼��ʱ���õ�	   
u8 Read_TP_Once(void)
{
	u8 re=0;
	u16 x1,y1;
	while(re==0)
	{
		while(!Read_ADS2(&tp_pixad.x,&tp_pixad.y));
		delay_ms(10);
		while(!Read_ADS2(&x1,&y1));
		if(tp_pixad.x==x1&&tp_pixad.y==y1)
		{
			re=1; 
		}
	} 
	return re;
}
//��һ��У׼�õĸ�����������
void Drow_Touch_Point(u16 x,u16 y)
{
	POINT_COLOR=RED;
	LCD_DrawLine(x-12,y,x+13,y);//����
	LCD_DrawLine(x,y-12,x,y+13);//����
	LCD_DrawPoint(x+1,y+1);
	LCD_DrawPoint(x-1,y+1);
	LCD_DrawPoint(x+1,y-1);
	LCD_DrawPoint(x-1,y-1);
	gui_circle(x,y,POINT_COLOR,6,0);//������Ȧ
}	  
//��һ�����(2*2�ĵ�)		   
//x,y:����
//color:��ɫ
void TP_Draw_Big_Point(u16 x,u16 y,u16 color)
{	   
	POINT_COLOR=color;
	
	LCD_DrawPoint(x,y);//���ĵ� 
	LCD_DrawPoint(x+1,y);
	LCD_DrawPoint(x,y+1);
	LCD_DrawPoint(x+1,y+1);	 	  	
}	  
//ת�����
//���ݴ�������У׼����������ת����Ľ��,������tp_pixlcd.x,tp_pixlcd.y��
u8 Convert_Pos(void)
{	
	#if USE_HORIZONTAL==1 || USE_HORIZONTAL==3
	u16 temp; 
	#endif 	 
	u8 l=0;
	
	if(Read_ADS2(&tp_pixad.x,&tp_pixad.y))
	{
		l=1;
		tp_pixlcd.x=tp_pixad.x>chx?((u32)tp_pixad.x-(u32)chx)*1000/vx:((u32)chx-(u32)tp_pixad.x)*1000/vx;
		tp_pixlcd.y=tp_pixad.y>chy?((u32)tp_pixad.y-(u32)chy)*1000/vy:((u32)chy-(u32)tp_pixad.y)*1000/vy;
	}
	#if USE_HORIZONTAL==1
//	tp_pixlcd.y=lcddev.height-tp_pixlcd.y; 
	temp=tp_pixlcd.x;
	tp_pixlcd.x=tp_pixlcd.y;
	tp_pixlcd.y=temp;
	//tp_pixlcd.x=lcddev.width-tp_pixlcd.x;//X���꾵��
//	tp_pixlcd.y=lcddev.height-tp_pixlcd.y; 
//	#else
	//tp_pixlcd.x=lcddev.width-tp_pixlcd.x;//X���꾵��
	tp_pixlcd.y=lcddev.height-1-tp_pixlcd.y; //Y���꾵�� 
	#elif USE_HORIZONTAL==2
	tp_pixlcd.x=lcddev.width-1-tp_pixlcd.x;
	tp_pixlcd.y=lcddev.height-1-tp_pixlcd.y;
	#elif USE_HORIZONTAL==3
	temp=tp_pixlcd.x;
	tp_pixlcd.x=tp_pixlcd.y;
	tp_pixlcd.y=temp;
	tp_pixlcd.x=lcddev.width-1-tp_pixlcd.x;
	#endif 
	return l;
}	    
//������У׼����
//�õ��ĸ�У׼����
#define tp_pianyi 50   //У׼����ƫ����	
#define tp_xiaozhun 1000   //У׼����
void Touch_Adjust(void)
{	
	float vx1,vx2,vy1,vy2;  //�������ӣ���ֵ����1000֮���ʾ���ٸ�ADֵ����һ�����ص�
	u16 chx1,chx2,chy1,chy2;//Ĭ�����ص�����Ϊ0ʱ��AD��ʼֵ
	u16 lx,ly;				 
	struct tp_pixu32_ p[4];
	u8  cnt=0;	 
	cnt=0;				
	POINT_COLOR=BLUE;
	BACK_COLOR =WHITE;
	LCD_Clear(WHITE);//����   
	POINT_COLOR=RED;//��ɫ 
	LCD_Clear(WHITE);//���� 
	Drow_Touch_Point(tp_pianyi,tp_pianyi);//����1 
	while(1)
	{
		if(Penirq==0)//����������
		{
			if(Read_TP_Once())//�õ����ΰ���ֵ
			{  								   
				p[cnt].x=tp_pixad.x;
				p[cnt].y=tp_pixad.y;
				cnt++; 
			}			 
			switch(cnt)
			{			   
				case 1:
					LCD_Clear(WHITE);//���� 
					while(!Penirq)  //�ȴ�����
					{
					}
					Drow_Touch_Point(lcddev.width-tp_pianyi-1,tp_pianyi);//����2
					break;
				case 2:
					LCD_Clear(WHITE);//���� 
					while(!Penirq)  //�ȴ�����
					{
					}
					Drow_Touch_Point(tp_pianyi,lcddev.height-tp_pianyi-1);//����3
					break;
				case 3:
					LCD_Clear(WHITE);//���� 
					while(!Penirq)  //�ȴ�����
					{
					}
					Drow_Touch_Point(lcddev.width-tp_pianyi-1,lcddev.height-tp_pianyi-1);//����4
					break;
				case 4:	 //ȫ���ĸ����Ѿ��õ�
	    		   	LCD_Clear(WHITE);//���� 
				   	while(!Penirq)  //�ȴ�����
					{
					}
					
					#if USE_HORIZONTAL==1 || USE_HORIZONTAL==3
					vx1=p[1].y>p[0].y?(p[1].y-p[0].y+1)*1000/(lcddev.width-tp_pianyi-tp_pianyi):(p[0].y-p[1].y-1)*1000/(lcddev.width-tp_pianyi-tp_pianyi);
				 	chx1=p[1].y>p[0].y?p[0].y-(vx1*tp_pianyi)/1000:p[1].y-(vx1*tp_pianyi)/1000;
				   	vy1=p[2].x>p[0].x?(p[2].x-p[0].x-1)*1000/(lcddev.height-tp_pianyi-tp_pianyi):(p[0].x-p[2].x-1)*1000/(lcddev.height-tp_pianyi-tp_pianyi);
					chy1=p[2].x>p[0].x?p[2].x+(vy1*tp_pianyi)/1000:p[0].x+(vy1*tp_pianyi)/1000; 
					
					vx2=p[3].y>p[2].y?(p[3].y-p[2].y+1)*1000/(lcddev.width-tp_pianyi-tp_pianyi):(p[2].y-p[3].y-1)*1000/(lcddev.width-tp_pianyi-tp_pianyi);
					chx2=p[3].y>p[2].y?p[2].y-(vx2*tp_pianyi)/1000:p[3].y-(vx2*tp_pianyi)/1000;
				   	vy2=p[3].x>p[1].x?(p[3].x-p[1].x-1)*1000/(lcddev.height-tp_pianyi-tp_pianyi):(p[1].x-p[3].x-1)*1000/(lcddev.height-tp_pianyi-tp_pianyi);
					chy2=p[3].x>p[1].x?p[3].x+(vy2*tp_pianyi)/1000:p[1].x+(vy2*tp_pianyi)/1000; 
					#elif USE_HORIZONTAL==0 || USE_HORIZONTAL==2
					vx1=p[1].x>p[0].x?(p[1].x-p[0].x+1)*1000/(lcddev.width-tp_pianyi-tp_pianyi):(p[0].x-p[1].x-1)*1000/(lcddev.width-tp_pianyi-tp_pianyi);
				 	chx1=p[1].x>p[0].x?p[1].x+(vx1*tp_pianyi)/1000:p[0].x+(vx1*tp_pianyi)/1000;
				   	vy1=p[2].y>p[0].y?(p[2].y-p[0].y-1)*1000/(lcddev.height-tp_pianyi-tp_pianyi):(p[0].y-p[2].y-1)*1000/(lcddev.height-tp_pianyi-tp_pianyi);
					chy1=p[2].y>p[0].y?p[0].y-(vy1*tp_pianyi)/1000:p[2].y-(vy1*tp_pianyi)/1000; 
					
					vx2=p[3].x>p[2].x?(p[3].x-p[2].x+1)*1000/(lcddev.width-tp_pianyi-tp_pianyi):(p[2].x-p[3].x-1)*1000/(lcddev.width-tp_pianyi-tp_pianyi);
					chx2=p[3].x>p[2].x?p[3].x+(vx2*tp_pianyi)/1000:p[2].x+(vx2*tp_pianyi)/1000;
				   	vy2=p[3].y>p[1].y?(p[3].y-p[1].y-1)*1000/(lcddev.height-tp_pianyi-tp_pianyi):(p[1].y-p[3].y-1)*1000/(lcddev.height-tp_pianyi-tp_pianyi);
					chy2=p[3].y>p[1].y?p[1].y-(vy2*tp_pianyi)/1000:p[3].y-(vy2*tp_pianyi)/1000; 
					
					#endif

					if((vx1>vx2&&vx1>vx2+tp_xiaozhun)||(vx1<vx2&&vx1<vx2-tp_xiaozhun)||(vy1>vy2&&vy1>vy2+tp_xiaozhun)||(vy1<vy2&&vy1<vy2-tp_xiaozhun))
					{
						cnt=0;
						LCD_Clear(WHITE);//���� 
						Drow_Touch_Point(tp_pianyi,tp_pianyi);//����1 
						continue;
					}
					#if USE_HORIZONTAL==1 || USE_HORIZONTAL==3
					vx=(vy1+vy2)/2;vy=(vx1+vx2)/2;
					chx=(chy1+chy2)/2;chy=(chx1+chx2)/2;	
				  #elif USE_HORIZONTAL==0 || USE_HORIZONTAL==2
					vx=(vx1+vx2)/2;vy=(vy1+vy2)/2;
					chx=(chx1+chx2)/2;chy=(chy1+chy2)/2;	
					#endif
					//��ʾУ׼��Ϣ
					LCD_Clear(WHITE);//���� 
					POINT_COLOR=BLACK;
					BACK_COLOR=BLUE;	
					lx=50;ly=50;			
					LCD_ShowString(lx,ly,16,"VX:",1);lx+=40;LCD_ShowNum(lx,ly,vx,6,16);					
					lx=50;ly+=20;
					LCD_ShowString(lx,ly,16,"Vy:",1);lx+=40;LCD_ShowNum(lx,ly,vy,6,16);					
					lx=50;ly+=20; 
					LCD_ShowString(lx,ly,16,"CHX:",1);lx+=40;LCD_ShowNum(lx,ly,chx,6,16);					
				    lx=50;ly+=20; 
					LCD_ShowString(lx,ly,16,"CHY:",1);lx+=40;LCD_ShowNum(lx,ly,chy,6,16);

					lx=30;ly+=30;
					LCD_ShowString(lx,ly,16,"Adjust OK!",1);	
					lx=30;ly+=30;
					LCD_ShowString(lx,ly,16,"Touch Anywhere To Continue",1);										  
					Read_TP_Once(); //�ȴ�����������

					LCD_Clear(WHITE);//����
					return;//У�����				 
			}
		}
	} 
}
	    	