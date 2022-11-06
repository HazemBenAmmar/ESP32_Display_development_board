#ifndef	_TOUCH_I2C_DRV_H_
#define	_TOUCH_I2C_DRV_H_
#include "stm32f10x.h"

extern u8 GT911_CHIPID_W;
extern u8 GT911_CHIPID_R;

typedef struct GT911_POINT_REG_
{
    u8 trackID;     //track id
    u8 xl;          //point 1 x coordinate (low byte)
    u8 xh;          //point 1 x coordinate (high byte)
    u8 yl;          //point 1 y coordinate (low byte)
    u8 yh;          //point 1 y coordinate (high byte)
    u8 sl;          //point 1 size (low byte)
    u8 sh;          //point 1 size (high byte)
    u8 Res;         //Reserved
}GT911_POINT_REG;

//PC1   SCK
//PC2   SDA

#define	I2C_SCL_H		do{(GPIOC->BSRR=GPIO_BSRR_BS1);}while(0)
#define I2C_SCL_L		do{(GPIOC->BRR=GPIO_BRR_BR1);}while(0)
#define I2C_SDA_H		do{(GPIOC->BSRR=GPIO_BSRR_BS2);}while(0)
#define I2C_SDA_L		do{(GPIOC->BRR=GPIO_BRR_BR2);}while(0)
#define I2C_SDA_IN		(GPIOC->IDR&GPIO_IDR_IDR2)


u8 I2CGT911_Write(u16 addr, u8* data,u8 len);
u8 I2CGT911_Read(u16 addr, u8 * data,u8 len);

#endif


