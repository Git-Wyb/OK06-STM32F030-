#ifndef __GPIO_H__
#define __GPIO_H__

#include "stm32f0xx.h"
#include "Sys.h"

#define GPIOx_IN(GPIOx,PINx)   (u1){(GPIOx->IDR & PINx) ? 1 : 0}
#define GPIOx_OUT(GPIOx,PINx,y)   {if(y){GPIOx->BSRR = PINx;}else{GPIOx->BRR = PINx;}}

/*
IO OUT: PB3/PB4/PB5
IO IN: PB13/PB14/PB15
*/

#define PB15 GPIOx_IN(GPIOB,GPIO_Pin_15)
#define PB14 GPIOx_IN(GPIOB,GPIO_Pin_14)
#define PB13 GPIOx_IN(GPIOB,GPIO_Pin_13)

#define PA3 GPIOx_IN(GPIOA,GPIO_Pin_3)
#define PA4 GPIOx_IN(GPIOA,GPIO_Pin_4)
#define P_ENCODER_A PA3
#define P_ENCODER_B PA4

#define OPEN_SW     PB15
#define STOP_SW     PB14
#define CLOSE_SW    PB13
#define P_OPEN_SW   (u1)(~OPEN_SW & 0x01)
#define P_STOP_SW   (u1)(~STOP_SW & 0x01)
#define P_CLOSE_SW  (u1)(~CLOSE_SW & 0x01)

#define P_RELAY_1_0 GPIOx_OUT(GPIOB,GPIO_Pin_4,0)
#define P_RELAY_1_1 GPIOx_OUT(GPIOB,GPIO_Pin_4,1)
#define P_RELAY_2_0 GPIOx_OUT(GPIOB,GPIO_Pin_3,0)
#define P_RELAY_2_1 GPIOx_OUT(GPIOB,GPIO_Pin_3,1)
#define P_RELAY_3_0 GPIOx_OUT(GPIOB,GPIO_Pin_5,0)
#define P_RELAY_3_1 GPIOx_OUT(GPIOB,GPIO_Pin_5,1)

#define	P_EM_RESET_N_0  GPIOx_OUT(GPIOB,GPIO_Pin_12,0)
#define	P_EM_RESET_N_1  GPIOx_OUT(GPIOB,GPIO_Pin_12,1)

#define P_PWM_OUT_0     GPIOx_OUT(GPIOA,GPIO_Pin_6,0)
#define P_PWM_OUT_1     GPIOx_OUT(GPIOA,GPIO_Pin_6,1)

#define P_VER_POWER_0   GPIOx_OUT(GPIOA,GPIO_Pin_0,0)
#define P_VER_POWER_1   GPIOx_OUT(GPIOA,GPIO_Pin_0,1)

#define P_T_BREAK_0     GPIOx_OUT(GPIOA,GPIO_Pin_7,0)
#define P_T_BREAK_1     GPIOx_OUT(GPIOA,GPIO_Pin_7,1)

#define P_ECU_TEST1     1//GPIOx_IN(GPIOF,GPIO_Pin_7)
#define P_ECU_TEST2     1//GPIOx_IN(GPIOF,GPIO_Pin_6)

void Init_Gpio(void);
u1 P_OPEN_SW_Input(void);
u1 P_STOP_SW_Input(void);
u1 P_CLOSE_SW_Input(void);
void MCO_ClockOutPut_PA8(void);

#endif
