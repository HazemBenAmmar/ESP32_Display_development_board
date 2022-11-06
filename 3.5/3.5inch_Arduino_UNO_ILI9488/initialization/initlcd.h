void LCD_GPIO_Init(void)
{
	......
//Init the GPIOs for LCD	
}
void LCD_RESET(void)
{
	LCD_RST_CLR;
	delay_ms(100);	
	LCD_RST_SET;
	delay_ms(50);
}
void LCD_Init(void)
{
	//LCD_GPIO_Init();//Init the GPIOs for LCD
	//LCD_RESET();//You should ResetLCD before Init.

  	//ILI9488≥ı ºªØ
  LCD_WR_REG(0x01);
  delay_ms(50);
  LCD_WR_REG(0x28);
  LCD_WR_REG(0xC0);
  LCD_WR_DATA(0x10);
  LCD_WR_DATA(0x10);
  LCD_WR_REG(0xC1);
  LCD_WR_DATA(0x41);
  LCD_WR_REG(0xC5);  
  LCD_WR_DATA(0x00); 
  LCD_WR_DATA(0x22);
  LCD_WR_DATA(0x80);
  LCD_WR_DATA(0x40);
  LCD_WR_REG(0x36);
  LCD_WR_DATA(0x08);
  LCD_WR_REG(0xB0);
  LCD_WR_DATA(0x00);
  LCD_WR_REG(0xB1);
  LCD_WR_DATA(0xB0);
  LCD_WR_DATA(0x11);
  LCD_WR_REG(0xB4);
  LCD_WR_DATA(0x02);
  LCD_WR_REG(0xB6);
  LCD_WR_DATA(0x02);
  LCD_WR_DATA(0x02);
  LCD_WR_DATA(0x3B);
  LCD_WR_REG(0xB7);
  LCD_WR_DATA(0xC6);
  LCD_WR_REG(0x3A);
  LCD_WR_DATA(0x55);
  LCD_WR_REG(0xF7);
  LCD_WR_DATA(0xA9); 
  LCD_WR_DATA(0x51);
  LCD_WR_DATA(0x2C);
  LCD_WR_DATA(0x82);
  LCD_WR_REG(0x11);
  delay_ms(150);
  LCD_WR_REG(0x29);
}

