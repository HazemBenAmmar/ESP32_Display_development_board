/**********************************************************************************************************/ 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//����Ӳ����Ӳ������STM32F103VCT6������8M������Ƶ72M
//Һ������ for STM32
//�Ա���վ��http://jczn.taobao.com
//All rights reserved
//��Ȩ���У�����ؾ���
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
//       LED                ��          PB6         //Һ������������źţ��������Ҫ���ƣ���5V��3.3V
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
#ifndef __LCD_INIT_H
#define __LCD_INIT_H
#include "sys.h"

#define USE_HORIZONTAL 0  //���ú�������������ʾ 0��1Ϊ���� 2��3Ϊ����


#define LCD_W 240
#define LCD_H 240



//-----------------LCD�˿ڶ���---------------- 

#define LCD_SCLK_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_5)//SCL=SCLK 
#define LCD_SCLK_Set() GPIO_SetBits(GPIOA,GPIO_Pin_5)

#define LCD_MOSI_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_7)//SDA=MOSI 
#define LCD_MOSI_Set() GPIO_SetBits(GPIOA,GPIO_Pin_7)

#define LCD_RES_Clr()  GPIO_ResetBits(GPIOB,GPIO_Pin_0)//RES 
#define LCD_RES_Set()  GPIO_SetBits(GPIOB,GPIO_Pin_0)

#define LCD_DC_Clr()   GPIO_ResetBits(GPIOC,GPIO_Pin_4)//DC  
#define LCD_DC_Set()   GPIO_SetBits(GPIOC,GPIO_Pin_4)
 		     
#define LCD_CS_Clr()   GPIO_ResetBits(GPIOA,GPIO_Pin_4)//CS  
#define LCD_CS_Set()   GPIO_SetBits(GPIOA,GPIO_Pin_4)

#define LCD_BLK_Clr()  GPIO_ResetBits(GPIOB,GPIO_Pin_6)//BLK 
#define LCD_BLK_Set()  GPIO_SetBits(GPIOB,GPIO_Pin_6)




void LCD_GPIO_Init(void);//��ʼ��GPIO
void LCD_Writ_Bus(u8 dat);//ģ��SPIʱ��
void LCD_WR_DATA8(u8 dat);//д��һ���ֽ�
void LCD_WR_DATA(u16 dat);//д�������ֽ�
void LCD_WR_REG(u8 dat);//д��һ��ָ��
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);//�������꺯��
void LCD_Init(void);//LCD��ʼ��
#endif




