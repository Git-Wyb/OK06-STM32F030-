#include "Sys.h"
#include "Gpio.h"
#include "Timer.h"

BaseFlagStruct Un_Flag0 = {0};

static u1  fac_us=0;							//us��ʱ������			   
static u2 fac_ms=0;							//ms��ʱ������


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
     Counter Reload Value = 250ms/IWDG counter clock period��
    f = 1.25k
    */
    IWDG_SetReload(313);    //250ms��ʱ
    
    /* Reload IWDG counter */
    IWDG_ReloadCounter();

    /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
    IWDG_Enable();
}

//void IWDG_Clear(void)
//{
//    IWDG_ReloadCounter();
//}

void R_WDT_Restart(void)
{
    IWDG_ReloadCounter();
}
//SystemCoreClock
void Init_Delay(void)
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//ѡ���ⲿʱ��  HCLK/8
	fac_us = SYS_CLK / 8000000;				//Ϊϵͳʱ�ӵ�1/8
    fac_ms = (u2)fac_us * 1000;
}

//��ʱnus
//nusΪҪ��ʱ��us��.		    								   
void delay_us(u4 nus)
{		
	u4 temp;	    	 
	SysTick->LOAD = nus*fac_us; 					//ʱ�����	  		 
	SysTick->VAL = 0x00;        					//��ռ�����
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;	//��ʼ����	  
	do
	{
		temp = SysTick->CTRL;
	}while((temp&0x01) && !(temp&(1<<16)));		//�ȴ�ʱ�䵽��   
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
	SysTick->VAL = 0X00;      					 //��ռ�����	 
}

//��ʱnms
//ע��nms�ķ�Χ
//SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK��λΪHz,nms��λΪms
//��72M������,nms<=1864 
void delay_ms(u2 nms)
{	 		  	  
	u4 temp;		   
	SysTick->LOAD = (u4)nms * fac_ms;				//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL = 0x00;							//��ռ�����
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;	//��ʼ����  
	do
	{
		temp = SysTick->CTRL;
	}while((temp & 0x01) && !(temp & (1<<16)));		//�ȴ�ʱ�䵽��   
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
	SysTick->VAL = 0X00;       					//��ռ�����	  	    
}


//u1 Key_Scan(void)
//{
//    if((P_OPEN_SW == 1 || P_STOP_SW == 1 || P_CLOSE_SW == 1) && flag_key_scan == 0)
//    {
//        delay_ms(50);
//        if(P_OPEN_SW == 1 || P_STOP_SW == 1 || P_CLOSE_SW == 1)
//        {
//            flag_key_scan = 1;
//            if(P_OPEN_SW)   return 1;
//            else if(P_STOP_SW)  return 2;
//            else if(P_CLOSE_SW) return 3;
//        }
//    }
//    else if(P_OPEN_SW == 0 && P_STOP_SW == 0 && P_CLOSE_SW == 0)
//    {
//        flag_key_scan = 0;
//    }
//    return 0;
//}

//u1 key_in = 0;
//void Key_Sw_Dete(void)
//{
//    key_in = Key_Scan();
//    switch(key_in)
//    {
//        case 1:
//            if(flag_sw_sta == 0)
//            {
//                flag_sw_sta = 1;
//                P_RELAY_3_0;
//                P_RELAY_2_1;
//                P_RELAY_1_1;
//                R_TAU0_Channel4_Start();
//            }
//            break;
//        case 2:
//            flag_sw_sta = 0;
//            P_RELAY_2_0;
//            P_RELAY_3_0;
//            P_RELAY_1_0;
//            R_TAU0_Channel4_Stop();
//            break;
//        case 3:
//            if(flag_sw_sta == 0)
//            {
//                flag_sw_sta = 1;
//                P_RELAY_3_1;
//                P_RELAY_2_0;
//                P_RELAY_1_1;
//            }
//            break;
//        default:
//            if(flag_sw_sta == 0)
//            {
//                P_RELAY_3_0;
//                P_RELAY_2_0;
//                P_RELAY_1_0;
//            }
//            break;
//    }
//}
