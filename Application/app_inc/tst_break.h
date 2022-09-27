/************************************************************************/
/*	トランジスタブレーキ定義					*/
/*----------------------------------------------------------------------*/
/*History						Date   / Author	*/
/*							170516 / Minoura*/
/************************************************************************/
#ifndef __TST_BREAK_INCLUDED__
#define __TST_BREAK_INCLUDED__

#include "Sys.h"

/*--------------------------------------------------------------------------*/
/*		定数定義															*/
/*--------------------------------------------------------------------------*/

#define PWM_OFF_PULSE_LENGTH		1216//1518	/* OK03:33rpm 1205rpm /RK02:10.4rpm */
#define BREAK_OFF_PULSE_LENGTH		1216//1432	/* OK03:33rpm 1205rpm */
#define BREAK_ON_PULSE_LENGTH		1279//1518	/* OK03:35rpm 1279rpm */
/* #define BREAK_NO_TIME_PULSE_LENGTH	1562	 OK03:36rpm */
#define BREAK_MAX_PULSE_LENGTH		1461//1736	/* OK03:40rpm 1461rpm */

#define D_BREAK_MAX_LEVEL		(u2)0x8CA0		/* 9ms中9ms */
#define D_BREAK_7_2_LEVEL		(u2)0x7080		/* 9ms中7.2ms */
#define D_BREAK_6_4_LEVEL		(u2)0x6400		/* 9ms中6.4ms */
#define D_BREAK_5_6_LEVEL		(u2)0x5780		/* 9ms中5.6ms */
#define D_BREAK_4_8_LEVEL		(u2)0x4B00		/* 9ms中4.8ms */
#define D_BREAK_4_LEVEL			(u2)0x3E80		/* 9ms中4ms */
#define D_BREAK_3_2_LEVEL		(u2)0x3200		/* 9ms中3.2ms */
#define D_BREAK_3_LEVEL			(u2)0x2EE0		/* 9ms中3ms */
#define D_BREAK_2_4_LEVEL		(u2)0x2580		/* 9ms中2.4ms */
#define D_BREAK_1_6_LEVEL		(u2)0x1900		/* 9ms中1.6ms */
#define D_BREAK_0_8_LEVEL		(u2)0xC80		/* 9ms中0.8ms */
#define D_BREAK_0_72_LEVEL		(u2)0xB40		/* 9ms中0.72ms */
#define D_BREAK_0_4_LEVEL		(u2)0x640		/* 9ms中0.4ms */
#define D_BREAK_MIN_LEVEL		(u2)0x28		/* 9ms中10us 40カウント */
#define D_BREAK_0_LEVEL			(u2)0x0000		/* 9ms中0ms */

#define PULSE_BREAK_WAIT		(u1)20			/* 速度が上がってPWMをOFF開始までのパルス */
#define PULSE_BREAK_START		(u1)30			/* 速度が上がってブレーキ開始までのパルス */
#define TIME_MAX_BREAK_STOP		(u1)20			/* ブレーキ最大が２ｓ続いたら停止させる */
#define LIMIT_STOP_WAIT_TIME		(u1)3			/* 入力パルス無し判定の待ち時間 */

//開動作ブレーキ用定義
#define PWM_OFF_PULSE_LENGTH_OP		1216//1443	/* OK03:33rpm 1205rpm /RK02:10.4rpm */
#define BREAK_OFF_PULSE_LENGTH_OP	1216		/* OK03:33rpm 1205rpm */
#define BREAK_ON_PULSE_LENGTH_OP	1279//1501	/* OK03:35rpm 1279rpm */
#define BREAK_MAX_PULSE_LENGTH_OP	1461		/* OK03:40rpm 1461rpm */

#define D_BREAK_2_4_LEVEL_OP	(u2)0x2580		/* 9ms中2.4ms */
#define D_BREAK_MIN_LEVEL_OP	(u2)0x640		/* 9ms中0.4ms */

#define BREAK_MAX_P				68			/* 強ブレーキ強さ */
#define BREAK_MID_P				70			/* 中ブレーキ強さ */
#define BREAK_LOW_P				35			/* 弱ブレーキ強さ */

#define BREAK_MAX_FIRST_WAIT		2			/* 最大ブレーキ初回待ち時間 */
#define BREAK_OFF_FIRST_WAIT		3			/* ブレーキOFF初回待ち時間 */

#define PULSE_BREAK_WAIT_OP		(u1)20			/* 速度が上がってPWMをOFF開始までのパルス */
#define PULSE_BREAK_START_OP		(u1)8			/* 速度が上がってブレーキ開始までのパルス */
#define TIME_MAX_BREAK_STOP_OP		(u1)20			/* ブレーキ最大が２ｓ続いたら停止させる */
#define LIMIT_STOP_WAIT_TIME_OP		(u1)3			/* 入力パルス無し判定の待ち時間 */

#define BREAK_OUT_WAIT_TIME			15			/* PWMOFFからブレーキONまでの待ち時間[ms] PWMOFFとなるのがメイン1回分遅れても大丈夫なように5ms余裕を持たせる */

#define PWM_RESTART_PULSE			3			/* 一定速度以下でPWM出力を再開する為の判定パルス */

/*--------------------------------------------------------------------------*/
/*		ローカル型定義														*/
/*--------------------------------------------------------------------------*/
typedef enum {
	E_PWM_OFF_PULSE_LENGTH,			/* PWMOFF速度 */
	E_BREAK_OFF_PULSE_LENGTH,		/* ブレーキOFF速度 */
	E_BREAK_ON_PULSE_LENGTH,		/* ブレーキON速度 */
	E_BREAK_MAX_PULSE_LENGTH,		/* ブレーキMAX速度 */
	E_D_BREAK_3_LEVEL,				/* ブレーキMAX出力 */
	E_D_BREAK_MIN_LEVEL,			/* ブレーキMIN出力 */
	E_PULSE_BREAK_WAIT,				/* 速度が上がってPWMをOFF開始までのパルス */
	E_PULSE_BREAK_START,			/* 速度が上がってブレーキ開始までのパルス */
	E_TIME_MAX_BREAK_STOP,			/* ブレーキ最大が２ｓ続いたら停止させる */
	E_LIMIT_STOP_WAIT_TIME			/* 入力パルス無し判定の待ち時間 */
} break_data;	/* ブレーキデータ */

typedef enum {
	PWM_ON_BREAK_OFF,			/* 通常状態 */
	PWM_OFF_BREAK_OFF,			/* PWMOFF状態 */
	PWM_OFF_BREAK_ON			/* ブレーキON状態 */
} t_break_step;	/* ブレーキ処理状態 */

/*--------------------------------------------------------------------------*/
/*		関数宣言		   				    */
/*--------------------------------------------------------------------------*/
extern void check_t_break_main(void);
extern void t_break_counter(void);
extern void t_flag_all_clear(void);
extern void check_encoder_duty_stop_cancel(void);

/*--------------------------------------------------------------------------*/
/*		グローバル変数宣言	r_cg_timer_user/u_mainで使用	    */
/*--------------------------------------------------------------------------*/
extern u2 u2g_t_break_duty;			/* ブレーキのデューティ */
extern u1 u1g_t_break_max_timer_counter;	/* トランジスタブレーキ最大出力時間ｶｳﾝﾀ */
extern u1 u1g_Fg_pwm_off_for_break;		/* ブレーキONのときはデューティは０とする（ encoder.cで使用）*/
extern u1 u1g_Fg_pwm_restart;
extern u1 u1g_Fg_pwm_start_pass_code;
extern u1 u1g_Fg_break_start_pass_code;

extern u1 u1g_Fg_break_ok;
extern u1 u1g_t_break_step;
extern u1 u1g_t_break_step_first;
extern u1 u1g_pwm_break_timer_counter;
extern u2 u2g_previous_break_duty;


#endif
