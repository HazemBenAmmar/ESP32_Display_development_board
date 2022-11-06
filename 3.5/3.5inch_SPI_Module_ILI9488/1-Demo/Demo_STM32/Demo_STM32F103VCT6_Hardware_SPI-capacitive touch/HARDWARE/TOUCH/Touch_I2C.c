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
//        if(temp&0x80)           //MSB��ǰ  
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
        if(temp&0x80)           //MSB��ǰ  
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
	IicSendByte_GT911(GT911_CHIPID_W);	//Ѱַ������д����  
	IicWaiteAck_GT911();  
	IicSendByte_GT911((u8)(addr>>8));	    //�ֽڵ�ַH
	IicWaiteAck_GT911(); 
	IicSendByte_GT911((u8)addr);		    //�ֽڵ�ַL
	IicWaiteAck_GT911(); 
  for(i=0;i<len;i++)
  {
	  IicSendByte_GT911(*data++);       //д����ָ����ǰ�ָ���ָ��д����  
		IicWaiteAck_GT911();
  }
	IicStop_GT911();  
	return 1;

}
u8 I2CGT911_Read(u16 addr, u8* data,u8 len)
{
	u8 i;
	IicStart_GT911();  
	IicSendByte_GT911(GT911_CHIPID_W);		//Ѱַ������д�����Ҫд�ֽڵ�ַ��            
	IicWaiteAck_GT911();  
	IicSendByte_GT911((u8)(addr>>8));	     //�ֽڵ�ַH
	IicWaiteAck_GT911(); 
	IicSendByte_GT911((u8)addr);		    //�ֽڵ�ַL
	IicWaiteAck_GT911(); 
    IicStop_GT911();  
	IicStart_GT911();     					//�ٴη�����ʼ����         
	IicSendByte_GT911(GT911_CHIPID_R);  			//�����Ѱַ�Ͷ�����  
	for(i=0;i<len;i++)      			
	{  
		IicAck_GT911();  		
		*data++ = IicReceiveByte_GT911();  
	}  
	IicNack_GT911();  
	IicStop_GT911();  
	return 1;

}



