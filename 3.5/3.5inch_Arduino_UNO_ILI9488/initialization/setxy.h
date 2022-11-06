void LCD_SetWindows(u16 x1, u16 y1,u16 x2,u16 y2)
{		
	LCD_WR_REG(0x2A);	
	LCD_WR_DATA(x1>>8);
	LCD_WR_DATA(0x00FF&x1);		
	LCD_WR_DATA(x2>>8);
	LCD_WR_DATA(0x00FF&x2);

	LCD_WR_REG(0x2B);	
	LCD_WR_DATA(y1>>8);
	LCD_WR_DATA(0x00FF&y1);		
	LCD_WR_DATA(y2>>8);
	LCD_WR_DATA(0x00FF&y2);
	LCD_WR_REG(0x2C);	//Start writing to the GRAM			
}   
	

