//手机:17199916363（微信同号）
//技术支持QQ:423170204
//邮箱:Lcddiy@hotmail.com
// IMPORTANT: Adafruit_TFTLCD LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.
// SEE RELEVANT COMMENTS IN Adafruit_TFTLCD.h FOR SETUP.

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include "CN_font.h"

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
// For the Arduino Uno, Duemilanove, Diecimila, etc.:
//   D0 connects to digital pin 8  (Notice these are
//   D1 connects to digital pin 9   NOT in order!)
//   D2 connects to digital pin 2
//   D3 connects to digital pin 3
//   D4 connects to digital pin 4
//   D5 connects to digital pin 5
//   D6 connects to digital pin 6
//   D7 connects to digital pin 7
// For the Arduino Mega, use digital pins 22 through 29
// (on the 2-row header at the end of the board).

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#include <MCUFRIEND_kbv.h>

MCUFRIEND_kbv tft;
// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Adafruit_TFTLCD tft;

void Show_Chinese(uint8_t *str,uint16_t x, uint16_t y, uint16_t fc, uint16_t bc,uint16_t fsize,uint8_t mode)
{    
    uint16_t i,j,k,num=0,color,mult;
    uint8_t code_h=0,code_l=0;
    char rdata;
    boolean first = true;
    if(x>(tft.width()-fsize)||y>(tft.height()-fsize))
    { 
       return;
    }
    switch(fsize)
    {
      case 16:
        num=sizeof(font_16x16)/sizeof(Chinese_16_Font);
        mult=2;
      break;
      case 24:
        num=sizeof(font_24x24)/sizeof(Chinese_24_Font);
        mult=3;        
      break;
      case 32:
        num=sizeof(font_32x32)/sizeof(Chinese_32_Font);
        mult=4;
      break;
      default:
      break;  
    }  
    while(*str!='\0')
    {     
      for(k=0;k<num;k++)
      {     
           if(fsize==16)
           {
              code_h=pgm_read_byte(&font_16x16[k].GBCode[0]);
              code_l=pgm_read_byte(&font_16x16[k].GBCode[1]);
           }
           else if(fsize==24)
           {
              code_h=pgm_read_byte(&font_24x24[k].GBCode[0]);
              code_l=pgm_read_byte(&font_24x24[k].GBCode[1]);
           }
           else if(fsize==32)
           {
              code_h=pgm_read_byte(&font_32x32[k].GBCode[0]);
              code_l=pgm_read_byte(&font_32x32[k].GBCode[1]);
           } 
           if((code_h==*str) && (code_l==*(str+1)))
           {
              first = true;
              tft.setAddrWindow(x, y, x+fsize-1, y+fsize-1); 
              for(j=0;j<fsize*mult;j++)
              {
                 for(i = 0;i<8;i++)  
                 {
                     if(fsize==16)
                     {
                        rdata=pgm_read_byte(&font_16x16[k].Mdata[j]);
                     }
                     else if(fsize==24)
                     {
                        rdata=pgm_read_byte(&font_24x24[k].Mdata[j]);
                     }
                     else if(fsize==32)
                     {
                        rdata=pgm_read_byte(&font_32x32[k].Mdata[j]);
                     } 
                    if(mode) //叠加模式
                    {
                      if(rdata&(0x80>>i))
                      {
                          tft.drawPixel(x+((j*8+i)%fsize),y+((j*8+i)/fsize),fc);
                       }      
                    }
                    else   //非叠加模式
                    {
                      if(rdata&(0x80>>i))
                      {
                           color = fc;
                       }
                       else
                       {
                          color = bc;
                       }
                       tft.pushColors(&color, 1, first);
                      first = false;
                   }
               }
            } 
         }
      } 
      str+=3; 
      x+=fsize;              
    }   
}

void setup(void) {
  Serial.begin(9600);
  Serial.println(F("TFT LCD test"));

#ifdef USE_ADAFRUIT_SHIELD_PINOUT
  Serial.println(F("Using Adafruit 2.4\" TFT Arduino Shield Pinout"));
#else
  Serial.println(F("Using Adafruit 2.4\" TFT Breakout Board Pinout"));
#endif

  Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());

  tft.reset();

  uint16_t identifier = tft.readID();
  if(identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if(identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if(identifier == 0x4535) {
    Serial.println(F("Found LGDP4535 LCD driver"));
  }else if(identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if(identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  }else if(identifier == 0x7783) {
    Serial.println(F("Found ST7781 LCD driver"));
  }else if(identifier == 0x8230) {
    Serial.println(F("Found UC8230 LCD driver"));  
  }
  else if(identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else if(identifier==0x0101)
  {     
      identifier=0x9341;
       Serial.println(F("Found 0x9341 LCD driver"));
  }
  else if(identifier==0x7793)
  {     
       Serial.println(F("Found ST7793 LCD driver"));
  }else if(identifier==0x9488)
  {     
       Serial.println(F("Found ST7793 LCD driver"));
  }else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Adafruit 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_ADAFRUIT_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Adafruit_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    identifier=0x9488;
   
  }

  tft.begin(identifier);
  tft.fillScreen(WHITE);
 
}

void loop(void) {
   tft.fillScreen(BLACK);
  unsigned long start = micros();
  Show_Chinese("中文字体显示",10, 10, RED, WHITE,16,0);
  Show_Chinese("中文字体显示",10, 26, RED, WHITE,16,1);
  Show_Chinese("中文字体显示",10, 42, GREEN, WHITE,24,0);
  Show_Chinese("中文字体显示",10, 66, GREEN, WHITE,24,1);
  Show_Chinese("中文字体显示",10, 90, BLUE, WHITE,32,0);
  Show_Chinese("中文字体显示",10, 122, BLUE, WHITE,32,1);

  Show_Chinese("中文字体显示",10, 164, CYAN, WHITE,16,1);
  Show_Chinese("中文字体显示",10, 180, MAGENTA, WHITE,24,1);
  Show_Chinese("中文字体显示",10, 204, YELLOW, WHITE,32,1);

  Show_Chinese("中文字体显示",10, 246, WHITE, WHITE,16,1);
  Show_Chinese("中文字体显示",10, 262, WHITE, WHITE,24,1);
  Show_Chinese("中文字体显示",10, 286, WHITE, WHITE,32,1);

  delay(1000);delay(1000);delay(1000);delay(1000);delay(1000);
}
