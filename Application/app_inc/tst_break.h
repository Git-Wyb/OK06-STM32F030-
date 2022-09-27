/************************************************************************/
/*	�g�����W�X�^�u���[�L��`					*/
/*----------------------------------------------------------------------*/
/*History						Date   / Author	*/
/*							170516 / Minoura*/
/************************************************************************/
#ifndef __TST_BREAK_INCLUDED__
#define __TST_BREAK_INCLUDED__

#include "Sys.h"

/*--------------------------------------------------------------------------*/
/*		�萔��`															*/
/*--------------------------------------------------------------------------*/

#define PWM_OFF_PULSE_LENGTH		1216//1518	/* OK03:33rpm 1205rpm /RK02:10.4rpm */
#define BREAK_OFF_PULSE_LENGTH		1216//1432	/* OK03:33rpm 1205rpm */
#define BREAK_ON_PULSE_LENGTH		1279//1518	/* OK03:35rpm 1279rpm */
/* #define BREAK_NO_TIME_PULSE_LENGTH	1562	 OK03:36rpm */
#define BREAK_MAX_PULSE_LENGTH		1461//1736	/* OK03:40rpm 1461rpm */

#define D_BREAK_MAX_LEVEL		(u2)0x8CA0		/* 9ms��9ms */
#define D_BREAK_7_2_LEVEL		(u2)0x7080		/* 9ms��7.2ms */
#define D_BREAK_6_4_LEVEL		(u2)0x6400		/* 9ms��6.4ms */
#define D_BREAK_5_6_LEVEL		(u2)0x5780		/* 9ms��5.6ms */
#define D_BREAK_4_8_LEVEL		(u2)0x4B00		/* 9ms��4.8ms */
#define D_BREAK_4_LEVEL			(u2)0x3E80		/* 9ms��4ms */
#define D_BREAK_3_2_LEVEL		(u2)0x3200		/* 9ms��3.2ms */
#define D_BREAK_3_LEVEL			(u2)0x2EE0		/* 9ms��3ms */
#define D_BREAK_2_4_LEVEL		(u2)0x2580		/* 9ms��2.4ms */
#define D_BREAK_1_6_LEVEL		(u2)0x1900		/* 9ms��1.6ms */
#define D_BREAK_0_8_LEVEL		(u2)0xC80		/* 9ms��0.8ms */
#define D_BREAK_0_72_LEVEL		(u2)0xB40		/* 9ms��0.72ms */
#define D_BREAK_0_4_LEVEL		(u2)0x640		/* 9ms��0.4ms */
#define D_BREAK_MIN_LEVEL		(u2)0x28		/* 9ms��10us 40�J�E���g */
#define D_BREAK_0_LEVEL			(u2)0x0000		/* 9ms��0ms */

#define PULSE_BREAK_WAIT		(u1)20			/* ���x���オ����PWM��OFF�J�n�܂ł̃p���X */
#define PULSE_BREAK_START		(u1)30			/* ���x���オ���ău���[�L�J�n�܂ł̃p���X */
#define TIME_MAX_BREAK_STOP		(u1)20			/* �u���[�L�ő傪�Q�����������~������ */
#define LIMIT_STOP_WAIT_TIME		(u1)3			/* ���̓p���X��������̑҂����� */

//�J����u���[�L�p��`
#define PWM_OFF_PULSE_LENGTH_OP		1216//1443	/* OK03:33rpm 1205rpm /RK02:10.4rpm */
#define BREAK_OFF_PULSE_LENGTH_OP	1216		/* OK03:33rpm 1205rpm */
#define BREAK_ON_PULSE_LENGTH_OP	1279//1501	/* OK03:35rpm 1279rpm */
#define BREAK_MAX_PULSE_LENGTH_OP	1461		/* OK03:40rpm 1461rpm */

#define D_BREAK_2_4_LEVEL_OP	(u2)0x2580		/* 9ms��2.4ms */
#define D_BREAK_MIN_LEVEL_OP	(u2)0x640		/* 9ms��0.4ms */

#define BREAK_MAX_P				68			/* ���u���[�L���� */
#define BREAK_MID_P				70			/* ���u���[�L���� */
#define BREAK_LOW_P				35			/* ��u���[�L���� */

#define BREAK_MAX_FIRST_WAIT		2			/* �ő�u���[�L����҂����� */
#define BREAK_OFF_FIRST_WAIT		3			/* �u���[�LOFF����҂����� */

#define PULSE_BREAK_WAIT_OP		(u1)20			/* ���x���オ����PWM��OFF�J�n�܂ł̃p���X */
#define PULSE_BREAK_START_OP		(u1)8			/* ���x���オ���ău���[�L�J�n�܂ł̃p���X */
#define TIME_MAX_BREAK_STOP_OP		(u1)20			/* �u���[�L�ő傪�Q�����������~������ */
#define LIMIT_STOP_WAIT_TIME_OP		(u1)3			/* ���̓p���X��������̑҂����� */

#define BREAK_OUT_WAIT_TIME			15			/* PWMOFF����u���[�LON�܂ł̑҂�����[ms] PWMOFF�ƂȂ�̂����C��1�񕪒x��Ă����v�Ȃ悤��5ms�]�T���������� */

#define PWM_RESTART_PULSE			3			/* ��葬�x�ȉ���PWM�o�͂��ĊJ����ׂ̔���p���X */

/*--------------------------------------------------------------------------*/
/*		���[�J���^��`														*/
/*--------------------------------------------------------------------------*/
typedef enum {
	E_PWM_OFF_PULSE_LENGTH,			/* PWMOFF���x */
	E_BREAK_OFF_PULSE_LENGTH,		/* �u���[�LOFF���x */
	E_BREAK_ON_PULSE_LENGTH,		/* �u���[�LON���x */
	E_BREAK_MAX_PULSE_LENGTH,		/* �u���[�LMAX���x */
	E_D_BREAK_3_LEVEL,				/* �u���[�LMAX�o�� */
	E_D_BREAK_MIN_LEVEL,			/* �u���[�LMIN�o�� */
	E_PULSE_BREAK_WAIT,				/* ���x���オ����PWM��OFF�J�n�܂ł̃p���X */
	E_PULSE_BREAK_START,			/* ���x���オ���ău���[�L�J�n�܂ł̃p���X */
	E_TIME_MAX_BREAK_STOP,			/* �u���[�L�ő傪�Q�����������~������ */
	E_LIMIT_STOP_WAIT_TIME			/* ���̓p���X��������̑҂����� */
} break_data;	/* �u���[�L�f�[�^ */

typedef enum {
	PWM_ON_BREAK_OFF,			/* �ʏ��� */
	PWM_OFF_BREAK_OFF,			/* PWMOFF��� */
	PWM_OFF_BREAK_ON			/* �u���[�LON��� */
} t_break_step;	/* �u���[�L������� */

/*--------------------------------------------------------------------------*/
/*		�֐��錾		   				    */
/*--------------------------------------------------------------------------*/
extern void check_t_break_main(void);
extern void t_break_counter(void);
extern void t_flag_all_clear(void);
extern void check_encoder_duty_stop_cancel(void);

/*--------------------------------------------------------------------------*/
/*		�O���[�o���ϐ��錾	r_cg_timer_user/u_main�Ŏg�p	    */
/*--------------------------------------------------------------------------*/
extern u2 u2g_t_break_duty;			/* �u���[�L�̃f���[�e�B */
extern u1 u1g_t_break_max_timer_counter;	/* �g�����W�X�^�u���[�L�ő�o�͎��Զ��� */
extern u1 u1g_Fg_pwm_off_for_break;		/* �u���[�LON�̂Ƃ��̓f���[�e�B�͂O�Ƃ���i encoder.c�Ŏg�p�j*/
extern u1 u1g_Fg_pwm_restart;
extern u1 u1g_Fg_pwm_start_pass_code;
extern u1 u1g_Fg_break_start_pass_code;

extern u1 u1g_Fg_break_ok;
extern u1 u1g_t_break_step;
extern u1 u1g_t_break_step_first;
extern u1 u1g_pwm_break_timer_counter;
extern u2 u2g_previous_break_duty;


#endif
