#include "Gpio.h"


//PB15/PB14/PB13 => OPEN/STOP/CLOSE; PB3/PB4/PB5 => CCW/MOTT/CW
void Init_Gpio(void)
{
    GPIO_InitTypeDef    GPIO_InitStructure;
    
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
#if HIGH_LEVEL
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//GPIO_PuPd_NOPULL;
#else
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
#endif
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    P_VER_POWER_0;
    P_EM_RESET_N_0;
    P_PWM_OUT_0;
}


//void MCO_ClockOutPut_PA8(void)
//{
//    GPIO_InitTypeDef    GPIO_InitStructure;
//    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
//    
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//GPIO_PuPd_NOPULL;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);
//    
//    GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_0);
//    
//    RCC->CFGR &= ~0x0f000000;
//    RCC->CFGR |= RCC_CFGR_MCO_HSI;
////    RCC->CFGR |= RCC_CFGR_MCO_HSE;
//}

//u1 P_OPEN_SW_Input(void)
//{
//    return (u1)(~GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15) & 0x01);
//}

//u1 P_STOP_SW_Input(void)
//{
//    return (u1)(~GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14) & 0x01);
//}

//u1 P_CLOSE_SW_Input(void)
//{
//    return (u1)(~GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13) & 0x01);
//}
