
/*************************************************************/
/*  システムタイマー処理 */
/*  10msecごとに入ってくるタイマ */
/*************************************************************/


#ifndef __SYSTEM_TIMER__
#define __SYSTEM_TIMER__

#include "typedefine.h"

void initial_system_timer(void);
void int_main_timer(void);
void reset_system_timer(void);
void int_system_timer(void);

#define U1L_ZERO		((u1)0x00U)
#define U1L_10_TIME		((u1)0x0AU)
#define U1L_100_TIME		((u1)0x64U)
#define U1L_MAX			((u1)0xFFU)
#define U2L_ZERO		((u2)0x00U)
#define	U2L_1000_TIME		((u2)0x3E8U)
#define	U2L_MAX			((u2)0xFFFFU)
#define	U2L_TIME_KAHUKA_LOOSE_MS	((u2)0x0000U)		/* 1.0s 過負荷反転直後の過負荷しきい値を大きくする時間[ms] */
#define	U2L_TIME_KAHUKA_LOOSE_SEC	((u2)0x0001U)		/* 1.0s 過負荷反転直後の過負荷しきい値を大きくする時間[sec] */

#endif
