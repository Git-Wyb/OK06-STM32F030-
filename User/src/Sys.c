#include "Sys.h"

BaseFlagStruct Un_Flag0 = {0};

static u1  fac_us=0;							//us延时倍乘数			   
static u2 fac_ms=0;							//ms延时倍乘数


void Init_IWDG(void)
{
    RCC_LSICmd(ENABLE);
    /*!< Wait till LSI is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
    {}
    
    /* Enable write access to IWDG_PR and IWDG_RLR registers */
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
    
    /* IWDG counter clock: LSI/32 */
    IWDG_SetPrescaler(IWDG_Prescaler_32);
    
    /* Set counter reload value to obtain 250ms IWDG TimeOut.
     Counter Reload Value = 250ms/IWDG counter clock period。
    f = 1.25k
    */
    IWDG_SetReload(313);    //250ms超时
    
    /* Reload IWDG counter */
    IWDG_ReloadCounter();

    /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
    IWDG_Enable();
}

void IWDG_Clear(void)
{
    IWDG_ReloadCounter();
}

void R_WDT_Restart(void)
{
    IWDG_ReloadCounter();
}

void Init_Delay(void)
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟  HCLK/8
	fac_us = SystemCoreClock / 8000000;				//为系统时钟的1/8
    fac_ms = (u2)fac_us * 1000;
}

//延时nus
//nus为要延时的us数.		    								   
void delay_us(u4 nus)
{		
	u4 temp;	    	 
	SysTick->LOAD = nus*fac_us; 					//时间加载	  		 
	SysTick->VAL = 0x00;        					//清空计数器
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;	//开始倒数	  
	do
	{
		temp = SysTick->CTRL;
	}while((temp&0x01) && !(temp&(1<<16)));		//等待时间到达   
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
	SysTick->VAL = 0X00;      					 //清空计数器	 
}

//延时nms
//注意nms的范围
//SysTick->LOAD为24位寄存器,所以,最大延时为:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK单位为Hz,nms单位为ms
//对72M条件下,nms<=1864 
void delay_ms(u2 nms)
{	 		  	  
	u4 temp;		   
	SysTick->LOAD = (u4)nms * fac_ms;				//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL = 0x00;							//清空计数器
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;	//开始倒数  
	do
	{
		temp = SysTick->CTRL;
	}while((temp & 0x01) && !(temp & (1<<16)));		//等待时间到达   
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
	SysTick->VAL = 0X00;       					//清空计数器	  	    
}


