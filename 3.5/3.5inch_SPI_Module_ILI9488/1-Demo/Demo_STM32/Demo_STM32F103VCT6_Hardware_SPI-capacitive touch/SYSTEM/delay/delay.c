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
#include "delay.h"
#include "sys.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_UCOS
#include "includes.h"					//ucos 使用	  
#endif
//V1.2修改说明
//修正了中断中调用出现死循环的错误
//防止延时不准确,采用do while结构!

//V1.3修改说明
//增加了对UCOSII延时的支持.
//如果使用ucosII,delay_init会自动设置SYSTICK的值,使之与ucos的TICKS_PER_SEC对应.
//delay_ms和delay_us也进行了针对ucos的改造.
//delay_us可以在ucos下使用,而且准确度很高,更重要的是没有占用额外的定时器.
//delay_ms在ucos下,可以当成OSTimeDly来用,在未启动ucos时,它采用delay_us实现,从而准确延时
//可以用来初始化外设,在启动了ucos之后delay_ms根据延时的长短,选择OSTimeDly实现或者delay_us实现.

//V1.4修改说明 20110929
//修改了使用ucos,但是ucos未启动的时候,delay_ms中中断无法响应的bug.
//V1.5修改说明 20120902
//在delay_us加入ucos上锁，防止由于ucos打断delay_us的执行，可能导致的延时不准。
////////////////////////////////////////////////////////////////////////////////// 	 
static u8  fac_us=0;//us延时倍乘数
static u16 fac_ms=0;//ms延时倍乘数
#ifdef OS_CRITICAL_METHOD 	//如果OS_CRITICAL_METHOD定义了,说明使用ucosII了.
//systick中断服务函数,使用ucos时用到
void SysTick_Handler(void)
{				   
	OSIntEnter();		//进入中断
    OSTimeTick();       //调用ucos的时钟服务程序               
    OSIntExit();        //触发任务切换软中断
}
#endif

//初始化延迟函数
//当使用ucos的时候,此函数会初始化ucos的时钟节拍
//SYSTICK的时钟固定为HCLK时钟的1/8
//SYSCLK:系统时钟
void delay_init()	 
{

#ifdef OS_CRITICAL_METHOD 	//如果OS_CRITICAL_METHOD定义了,说明使用ucosII了.
	u32 reload;
#endif
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟  HCLK/8
	fac_us=SystemCoreClock/8000000;	//为系统时钟的1/8  
	 
#ifdef OS_CRITICAL_METHOD 	//如果OS_CRITICAL_METHOD定义了,说明使用ucosII了.
	reload=SystemCoreClock/8000000;		//每秒钟的计数次数 单位为K	   
	reload*=1000000/OS_TICKS_PER_SEC;//根据OS_TICKS_PER_SEC设定溢出时间
							//reload为24位寄存器,最大值:16777216,在72M下,约合1.86s左右	
	fac_ms=1000/OS_TICKS_PER_SEC;//代表ucos可以延时的最少单位	   
	SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;   	//开启SYSTICK中断
	SysTick->LOAD=reload; 	//每1/OS_TICKS_PER_SEC秒中断一次	
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;   	//开启SYSTICK    
#else
	fac_ms=(u16)fac_us*1000;//非ucos下,代表每个ms需要的systick时钟数   
#endif
}								    

#ifdef OS_CRITICAL_METHOD	//使用了ucos
//延时nus
//nus为要延时的us数.		    								   
void delay_us(u32 nus)
{		
	u32 ticks;
	u32 told,tnow,tcnt=0;
	u32 reload=SysTick->LOAD;	//LOAD的值	    	 
	ticks=nus*fac_us; 			//需要的节拍数	  		 
	tcnt=0;
	told=SysTick->VAL;        	//刚进入时的计数器值
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)tcnt+=told-tnow;//这里注意一下SYSTICK是一个递减的计数器就可以了.
			else tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)break;//时间超过/等于要延迟的时间,则退出.
		}  
	}; 									    
}
//延时nms
//nms:要延时的ms数
void delay_ms(u16 nms)
{	
	if(OSRunning==TRUE)//如果os已经在跑了	    
	{		  
		if(nms>=fac_ms)//延时的时间大于ucos的最少时间周期 
		{
   			OSTimeDly(nms/fac_ms);//ucos延时
		}
		nms%=fac_ms;				//ucos已经无法提供这么小的延时了,采用普通方式延时    
	}
	delay_us((u32)(nms*1000));	//普通方式延时,此时ucos无法启动调度.
}
#else//不用ucos时
//延时nus
//nus为要延时的us数.		    								   
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; //时间加载	  		 
	SysTick->VAL=0x00;        //清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //开始倒数	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	 
}
//延时nms
//注意nms的范围
//SysTick->LOAD为24位寄存器,所以,最大延时为:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK单位为Hz,nms单位为ms
//对72M条件下,nms<=1864 
void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;           //清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	  	    
} 
#endif
































