#ifndef __TIMER_H__
#define __TIMER_H__

#include "stm32f0xx.h"
#include "Sys.h"
#include "Gpio.h"

#define U1L_ZERO		((u1)0x00U)
#define U1L_10_TIME		((u1)0x0AU)
#define U1L_100_TIME		((u1)0x64U)
#define U1L_MAX			((u1)0xFFU)
#define U2L_ZERO		((u2)0x00U)
#define	U2L_1000_TIME		((u2)0x3E8U)
#define	U2L_MAX			((u2)0xFFFFU)
#define	U2L_TIME_KAHUKA_LOOSE_MS	((u2)0x0000U)		/* 1.0s 過負荷反転直後の過負荷しきい値を大きくする時間[ms] */
#define	U2L_TIME_KAHUKA_LOOSE_SEC	((u2)0x0001U)		/* 1.0s 過負荷反転直後の過負荷しきい値を大きくする時間[sec] */


#define D_PWM_MAX_T         0x2AB0 //10928,100%
//#define D_BREAK_MAX_LEVEL   0x8CA0 //36000

void Init_Timer6(void);
void Init_Timer16(void);
void Init_Timer17(void);
void Init_Timer15(void);
void int_input_encoder(void);
void R_TAU0_Channel4_Start(void);
void R_TAU0_Channel4_Stop(void);
void R_TAU0_Channel6_Start(void);
void R_TAU0_Channel6_Stop(void);
void int_system_timer(void);
void reset_system_timer(void);
void int_input_encoder_test(void);

#endif
