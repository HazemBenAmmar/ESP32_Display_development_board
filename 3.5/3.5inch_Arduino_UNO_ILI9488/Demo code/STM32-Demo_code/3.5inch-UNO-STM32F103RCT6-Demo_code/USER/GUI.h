//�ֻ�:17199916363��΢��ͬ�ţ�
//����֧��QQ:423170204
//����:Lcddiy@hotmail.com
/****************************************************************************************************
//=========================================����˵��================================================//
//  5V      ��     DC5V
//  3v3     ��     DC3.3V
//  GND     ��     GND 
//  LCD_RST ��     PC4
//  LCD_CS  ��     PC9
//  LCD_RS  ��     PC8
//  LCD_WR  ��     PC7
//  LCD_RD  ��     PC6
//  LCD_D0  ��     PB0
//  LCD_D1  ��     PB1
//  LCD_D2  ��     PB2
//  LCD_D3  ��     PB3
//  LCD_D4  ��     PB4
//  LCD_D5  ��     PB5
//  LCD_D6  ��     PB6
//  LCD_D7  ��     PB7
//  �������׳���û��ʹ��SD����չ���ܣ����������Ų���Ҫ����
//  SD_SS��SD_DI��SD_DO��SD_SCK
//  ���ڱ�ģ�鴥��������Ҫ���XPT2046��������оƬ�����Ա����򲻽��д�������
**************************************************************************************************/					
#ifndef __GUI_H__
#define __GUI_H__

void GUI_DrawPoint(u16 x,u16 y,u16 color);
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);
void Draw_Circle(u16 x0,u16 y0,u16 fc,u8 r);
void Draw_Triangel(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2);
void Fill_Triangel(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2);
void LCD_ShowChar(u16 x,u16 y,u16 fc, u16 bc, u8 num,u8 size,u8 mode);
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);
void LCD_Show2Num(u16 x,u16 y,u16 num,u8 len,u8 size,u8 mode);
void LCD_ShowString(u16 x,u16 y,u8 size,u8 *p,u8 mode);
void GUI_DrawFont16(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode);
void GUI_DrawFont24(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode);
void GUI_DrawFont32(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode);
void Show_Str(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size,u8 mode);
void Gui_Drawbmp16(u16 x,u16 y,const unsigned char *p); //��ʾ40*40 QQͼƬ
void gui_circle(int xc, int yc,u16 c,int r, int fill);
void Gui_StrCenter(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size,u8 mode);
void LCD_DrawFillRectangle(u16 x1, u16 y1, u16 x2, u16 y2);
void LCD_Draw9Point(uint16_t x, uint16_t y, uint16_t color);
void Draw_TextBox(uint16_t xstart, uint16_t ystart, uint16_t xend, uint16_t yend);
void Draw_Button(uint16_t xstart,uint16_t ystart,uint16_t xend,uint16_t yend);
void EscButton(uint16_t xstart,uint16_t ystart,uint8_t xend,uint16_t yend);
void SetButton(uint8_t xstart,uint16_t ystart,uint8_t xend,uint16_t yend);
void Draw_DirectButton(uint16_t xstart, uint16_t ystart);
void Draw_Window(uint16_t xstart,uint16_t ystart,uint16_t xend,uint16_t yend,uint8_t* caption);
#endif

