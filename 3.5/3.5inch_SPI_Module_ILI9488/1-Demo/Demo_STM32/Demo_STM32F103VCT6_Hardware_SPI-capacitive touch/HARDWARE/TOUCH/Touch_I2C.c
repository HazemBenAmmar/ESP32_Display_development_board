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
#include "Touch_I2C.h"

u8 GT911_CHIPID_W=0xba;
u8 GT911_CHIPID_R=0xbb;

//PC1   SCK
//PC2   SDA

void I2C_DELAY(u16 nus)
{
	volatile u32 i,j;
	for(i=0;i<nus;i++)
	{
		for(j=0;j<2;j++);	// 350K
		//for(j=0;j<3;j++);	// 300K
		//for(j=0;j<12;j++);	// 100K

	}
}


//static void IicStart(void)  
//{  
//  
//    I2C_SDA_H;  
//    I2C_DELAY(2); 
//    I2C_SCL_H;  
//    I2C_DELAY(4);  
//    I2C_SDA_L;  
//    I2C_DELAY(4);  
//    I2C_SCL_L;            //-  
//  
//    I2C_DELAY(2);      //  
//    I2C_SDA_H;  
//    I2C_DELAY(2);  
//}  
//  
//static void IicStop(void)  
//{  
//    I2C_SDA_L;  
//    I2C_DELAY(2); 
//    I2C_SCL_L;  
//    I2C_DELAY(2);  
//  
//    I2C_SCL_H;  
//    I2C_DELAY(2);  
//    I2C_SDA_H;            //  
//    I2C_DELAY(2);  
//    I2C_SCL_L;               
//      
//    I2C_DELAY(2);        //  
//}  
//static void IicAck(void)  //  
//{  
//    I2C_SCL_L;  
//    I2C_DELAY(2); 
//    I2C_SDA_L;  
//    I2C_DELAY(4);  
//  
//    I2C_SCL_H;  
//    I2C_DELAY(4);   //  
//    I2C_SCL_L;  
//  
//    I2C_DELAY(2);  
//    I2C_SDA_H;  
//    I2C_DELAY(2);  
//}  
//  
//static void IicNack(void)  //  
//{  
//    I2C_SCL_L;  
//    I2C_DELAY(2); 
//    I2C_SDA_H;  
//    I2C_DELAY(4);  
//  
//    I2C_SCL_H;  
//    I2C_DELAY(4);   //  
//    I2C_SCL_L;  
//  
//    I2C_DELAY(2);  
//    I2C_SDA_H;  
//    I2C_DELAY(2);  
//}  
//static void IicWaiteAck(void)  
//{     
//    I2C_SCL_L; 
//    I2C_DELAY(2); 
//    I2C_SDA_H;  
//    I2C_DELAY(4);  
//  
//    I2C_SCL_H;  
//    I2C_DELAY(4);  
//    I2C_SCL_L;  
//  
//    I2C_DELAY(2);  
//}  
//static void IicSendByte(u8 temp)  
//{  
//    u8 i;  
//  
//    for(i=0;i<8;i++)  
//    {  
//        I2C_SCL_L;  
//        I2C_DELAY(4);  
//        if(temp&0x80)           //MSB在前  
//            I2C_SDA_H;  
//        else  
//            I2C_SDA_L;  
//		I2C_DELAY(1);  
//        I2C_SCL_H;  
//        I2C_DELAY(4);  
//        I2C_SCL_L;  
//        temp<<=1;  
//    }  
//      
//    I2C_DELAY(2);  
//    I2C_SDA_H;  
//    I2C_DELAY(2);  
//          
//}  
//  
//static u8 IicReceiveByte(void)  
//{  
//    u8 i,temp=0;  
//  
//    I2C_DELAY(2);  
//    I2C_SDA_H;                  //  
//    I2C_DELAY(2);             
//  
//    for(i=0;i<8;i++)  
//    {  
//        temp<<=1;  
//        I2C_SCL_L;  
//        I2C_DELAY(4);  
//        I2C_SCL_H;  
//        I2C_DELAY(5);  
//  
//        if(I2C_SDA_IN)  
//            temp=temp|0x01;  
//        else  
//            temp=temp&0xFE;   
//    }  
//  
//    I2C_SCL_L;  
//    I2C_DELAY(2);  
//    return temp;      
//}  

static void IicStart_GT911(void)  
{  
  
    I2C_SDA_H;  
    I2C_DELAY(2); 
    I2C_SCL_H;  
    I2C_DELAY(4);  
    I2C_SDA_L;  
    I2C_DELAY(4);  
    I2C_SCL_L;            //-  
    I2C_DELAY(2); 
}  
  
static void IicStop_GT911(void)  
{  
    I2C_DELAY(5); 
    I2C_SDA_L; 
    I2C_DELAY(2); 
    I2C_SCL_L;  
    I2C_DELAY(2);  
  
    I2C_SCL_H;  
    I2C_DELAY(2);  
    I2C_SDA_H;            //  
    I2C_DELAY(2);  
}  
static void IicAck_GT911(void)  //  
{  
    I2C_SCL_L; 
    I2C_DELAY(2); 
    I2C_SDA_L;  
    I2C_DELAY(20);  
  
    I2C_SCL_H;  
    I2C_DELAY(4);   //  
    I2C_SCL_L;  
  
    I2C_DELAY(2);  
    I2C_SDA_H;  
    I2C_DELAY(2);  
}  
  
static void IicNack_GT911(void)  //  
{  
    I2C_SCL_L;  
    I2C_DELAY(2); 
    I2C_SDA_H;  
    I2C_DELAY(4);  
  
    I2C_SCL_H;  
    I2C_DELAY(4);   //  
    I2C_SCL_L;  
    I2C_DELAY(2); 
}  
static void IicWaiteAck_GT911(void)  
{     
    I2C_SCL_L;  
    I2C_DELAY(20);  
    I2C_SDA_H;  
    I2C_DELAY(4);  
  
    I2C_SCL_H;  
    I2C_DELAY(20);  
    I2C_SCL_L;  
  
    I2C_DELAY(2);  
}  
static void IicSendByte_GT911(u8 temp)  
{  
    u8 i;  
    I2C_SCL_L;  
    I2C_DELAY(1);
    for(i=0;i<8;i++)  
    {  
        I2C_SCL_L;  
        I2C_DELAY(4);  
        if(temp&0x80)           //MSB在前  
            I2C_SDA_H;  
        else  
            I2C_SDA_L;  
		I2C_DELAY(1);  
        I2C_SCL_H;  
        I2C_DELAY(4);  
        temp<<=1;  
    }  
      
//    I2C_DELAY(2);  
//    I2C_SDA_H;  
//    I2C_DELAY(2);  
          
}  
  
static u8 IicReceiveByte_GT911(void)  
{  
    u8 i,temp=0;  
  
    I2C_DELAY(2);  
    I2C_SDA_H;                  //  
    I2C_DELAY(2);             
  
    for(i=0;i<8;i++)  
    {  
        temp<<=1;  
        I2C_SCL_L;  
        I2C_DELAY(4);  
        I2C_SCL_H;  
        I2C_DELAY(5);  
  
        if(I2C_SDA_IN)  
            temp=temp|0x01;  
        else  
            temp=temp&0xFE;   
    }  
  
    I2C_SCL_L;  
    I2C_DELAY(2);  
    return temp;      
}  




u8 I2CGT911_Write(u16 addr, u8* data,u8 len)
{

  u8 i;
	IicStart_GT911();  
	IicSendByte_GT911(GT911_CHIPID_W);	//寻址，发送写命令  
	IicWaiteAck_GT911();  
	IicSendByte_GT911((u8)(addr>>8));	    //字节地址H
	IicWaiteAck_GT911(); 
	IicSendByte_GT911((u8)addr);		    //字节地址L
	IicWaiteAck_GT911(); 
  for(i=0;i<len;i++)
  {
	  IicSendByte_GT911(*data++);       //写完了指针就是按指针的指向写数据  
		IicWaiteAck_GT911();
  }
	IicStop_GT911();  
	return 1;

}
u8 I2CGT911_Read(u16 addr, u8* data,u8 len)
{
	u8 i;
	IicStart_GT911();  
	IicSendByte_GT911(GT911_CHIPID_W);		//寻址，发送写命令（先要写字节地址）            
	IicWaiteAck_GT911();  
	IicSendByte_GT911((u8)(addr>>8));	     //字节地址H
	IicWaiteAck_GT911(); 
	IicSendByte_GT911((u8)addr);		    //字节地址L
	IicWaiteAck_GT911(); 
    IicStop_GT911();  
	IicStart_GT911();     					//再次发出起始条件         
	IicSendByte_GT911(GT911_CHIPID_R);  			//这次是寻址和读命令  
	for(i=0;i<len;i++)      			
	{  
		IicAck_GT911();  		
		*data++ = IicReceiveByte_GT911();  
	}  
	IicNack_GT911();  
	IicStop_GT911();  
	return 1;

}



