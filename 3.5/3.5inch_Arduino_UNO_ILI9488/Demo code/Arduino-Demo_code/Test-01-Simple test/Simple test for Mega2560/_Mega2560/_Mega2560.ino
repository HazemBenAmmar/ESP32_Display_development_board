//手机:17199916363（微信同号）
//技术支持QQ:423170204
//邮箱:Lcddiy@hotmail.com
// Breakout/Arduino UNO pin usage:
// LCD Data Bit :   7   6   5   4   3   2   1   0
// Uno dig. pin :   7   6   5   4   3   2   9   8
// Uno port/pin : PD7 PD6 PD5 PD4 PD3 PD2 PB1 PB0
// Mega dig. pin:  29  28  27  26  25  24  23  22
//              : PH4  PH3 PE3 PG5 PE5 PE4 PH6 PH5
#define LCD_RD   A0
#define LCD_WR   A1     
#define LCD_RS   A2        
#define LCD_CS   A3       
#define LCD_REST A4

void Lcd_Writ_Bus(unsigned char d)
{
  PORTH &= ~(0x78);
  PORTH |= ((d&0xC0) >> 3) | ((d&0x3) << 5);
  PORTE &= ~(0x38);
  PORTE |= ((d & 0xC) << 2) | ((d & 0x20) >> 2);
  PORTG &= ~(0x20);
  PORTG |= (d & 0x10) << 1;  	
 *(portOutputRegister(digitalPinToPort(LCD_WR))) &=  ~digitalPinToBitMask(LCD_WR);
 *(portOutputRegister(digitalPinToPort(LCD_WR)))|=  digitalPinToBitMask(LCD_WR);
}


void Lcd_Write_Com(unsigned char dat)
{   
  *(portOutputRegister(digitalPinToPort(LCD_RS))) &=  ~digitalPinToBitMask(LCD_RS);//LCD_RS=0;
  Lcd_Writ_Bus(dat);
}

void Lcd_Write_Dat(unsigned char dat)
{
  *(portOutputRegister(digitalPinToPort(LCD_RS)))|=  digitalPinToBitMask(LCD_RS);//LCD_RS=1;
  Lcd_Writ_Bus(dat);
}

void Lcd_Write_Data_16(unsigned int dat)
{
  *(portOutputRegister(digitalPinToPort(LCD_RS)))|=  digitalPinToBitMask(LCD_RS);//LCD_RS=1;
  Lcd_Writ_Bus(dat>>8);
  Lcd_Writ_Bus(dat);
}

void LCD_WriteReg(unsigned char com,unsigned char dat)
{
  Lcd_Write_Com(com);
  Lcd_Write_Dat(dat);
}

void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{
  Lcd_Write_Com(0x2A);
  Lcd_Write_Dat(x1>>8);
  Lcd_Write_Dat(x1);
  Lcd_Write_Dat(x2>>8);
  Lcd_Write_Dat(x2);
        
  Lcd_Write_Com(0x2B);
  Lcd_Write_Dat(y1>>8);
  Lcd_Write_Dat(y1);
  Lcd_Write_Dat(y2>>8);
  Lcd_Write_Dat(y2); 
  Lcd_Write_Com(0x2C);             
}

void Lcd_Init(void)
{
  digitalWrite(LCD_REST,HIGH);
  delay(20); 
  digitalWrite(LCD_REST,LOW);
  delay(100);
  digitalWrite(LCD_REST,HIGH);
  delay(50);

  digitalWrite(LCD_CS,HIGH);
  digitalWrite(LCD_WR,HIGH);
  digitalWrite(LCD_RD,HIGH);
  digitalWrite(LCD_CS,LOW);  //CS

  //ILI9488
  Lcd_Write_Com(0x01);
  delay(50);
  Lcd_Write_Com(0x28);
  Lcd_Write_Com(0xC0);
  Lcd_Write_Dat(0x10);
  Lcd_Write_Dat(0x10);
  Lcd_Write_Com(0xC1);
  Lcd_Write_Dat(0x41);
  Lcd_Write_Com(0xC5);  
  Lcd_Write_Dat(0x00); 
  Lcd_Write_Dat(0x22);
  Lcd_Write_Dat(0x80);
  Lcd_Write_Dat(0x40);
  Lcd_Write_Com(0x36);
  Lcd_Write_Dat(0x08);
  Lcd_Write_Com(0xB0);
  Lcd_Write_Dat(0x00);
  Lcd_Write_Com(0xB1);
  Lcd_Write_Dat(0xB0);
  Lcd_Write_Dat(0x11);
  Lcd_Write_Com(0xB4);
  Lcd_Write_Dat(0x02);
  Lcd_Write_Com(0xB6);
  Lcd_Write_Dat(0x02);
  Lcd_Write_Dat(0x02);
  Lcd_Write_Dat(0x3B);
  Lcd_Write_Com(0xB7);
  Lcd_Write_Dat(0xC6);
  Lcd_Write_Com(0x3A);
  Lcd_Write_Dat(0x55);
  Lcd_Write_Com(0xF7);
  Lcd_Write_Dat(0xA9); 
  Lcd_Write_Dat(0x51);
  Lcd_Write_Dat(0x2C);
  Lcd_Write_Dat(0x82);
  Lcd_Write_Com(0x11);
  delay(150);
  Lcd_Write_Com(0x29);                   
}

void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c)                   
{	
  unsigned int i,j;
  Lcd_Write_Com(0x2C); //write_memory_start
  digitalWrite(LCD_RS,HIGH);
  digitalWrite(LCD_CS,LOW);
  l=l+x;
  Address_set(x,y,l,y);
  j=l*2;
  for(i=1;i<=j;i++)
  {
    Lcd_Write_Data_16(c);
  }
  digitalWrite(LCD_CS,HIGH);   
}

void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c)                   
{	
  unsigned int i,j;
  Lcd_Write_Com(0x2C); //write_memory_start
  digitalWrite(LCD_RS,HIGH);
  digitalWrite(LCD_CS,LOW);
  l=l+y;
  Address_set(x,y,x,l);
  j=l*2;
  for(i=1;i<=j;i++)
  { 
    Lcd_Write_Data_16(c);
  }
  digitalWrite(LCD_CS,HIGH);   
}

void Rect(unsigned int x,unsigned int y,unsigned int w,unsigned int h,unsigned int c)
{
  H_line(x  , y  , w, c);
  H_line(x  , y+h, w, c);
  V_line(x  , y  , h, c);
  V_line(x+w, y  , h, c);
}

void Rectf(unsigned int x,unsigned int y,unsigned int w,unsigned int h,unsigned int c)
{
  unsigned int i;
  for(i=0;i<h;i++)
  {
    H_line(x  , y  , w, c);
    H_line(x  , y+i, w, c);
  }
}
int RGB(int r,int g,int b)
{return r << 16 | g << 8 | b;
}
void LCD_Clear(unsigned int j)                   
{	
  unsigned long int i,m;
 Address_set(0,0,320-1,480-1);
  digitalWrite(LCD_CS,LOW);

  *(portOutputRegister(digitalPinToPort(LCD_RS)))|=  digitalPinToBitMask(LCD_RS);//LCD_RS=1;

  for(i=0;i<153600;i++)
  {
      Lcd_Writ_Bus(j>>8);
      Lcd_Writ_Bus(j);
  }
  digitalWrite(LCD_CS,HIGH);   
}
void setup()
{
  /*
  for(int p=2;p<10;p++)
  {
    pinMode(p,OUTPUT);
  }*/
  DDRH |= 0x78;
  DDRE |= 0x38;
  DDRG |= 0x20;
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);
  pinMode(A4,OUTPUT);
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
  digitalWrite(A4, HIGH);

  Lcd_Init();

// LCD_Clear(0xf800);
}

void loop()
{  
   LCD_Clear(0xffff);
   LCD_Clear(0x0000);
   LCD_Clear(0xf800);
   LCD_Clear(0x07E0);
   LCD_Clear(0x001F);
  /*   
  for(int i=0;i<1000;i++)
  {
    Rect(random(300),random(300),random(300),random(300),random(65535)); // rectangle at x, y, with, hight, color
  }*/
  
//  LCD_Clear(0xf800);
}
