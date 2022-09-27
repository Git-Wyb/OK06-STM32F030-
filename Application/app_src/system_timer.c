#include "typedefine.h"
#include "variables.h"
#include "constants.h"
#include "functions.h"
//#include "serial_transmission.h"
#include "anjou_test.h"
#include "flash_data_read.h"
#include "system_timer.h"
#include "r_cg_userdefine.h"
#include "tst_break.h"

/*------------------------------------------------------------------------------*/
/*		���[�J���ϐ���`						*/
/*------------------------------------------------------------------------------*/
static u1 u1l_count_100ms = 0;
/************************************************/
/*              initial System Timer            */
/************************************************/
void initial_system_timer(void)
{
	u1g_fg_next_main_go = 0;               
}

/************************************************
 *	�^�C�}�C�x���g�ݒ�
 *-----------------------------------------------
 *	����
 *		����
 *	�߂�l
 *		����
 *	�������e
 *  	�e���Ԍo�ߖ��ɃC�x���g��ݒ肷��
 *	�ďo�^�C�~���O
 *		1ms��
 ************************************************/
void int_system_timer(void)
{
/*------------------------ 1msec --------------------------*/
                                                    
	/********* �|���v�o�͗p �t���O�@**************/
	if( u1g_fg_charge_pump_enable == 1 ){
		P_RELAY_1 = ~P_RELAY_1;
	}
	else{
		P_RELAY_1 = 1;
	}

	//sw_input_check();					/*SW���͊m�F		*/
	u2g_c_interval_plus++;					/*�ݺ��ފԊu����*/
		
	/* pwm����u���[�L�ؑ֎��ԃJ�E���g */
	if( u1g_pwm_break_timer_counter < 255 ){
		u1g_pwm_break_timer_counter ++;
	}
//	�Q�l�@0xffffffff[msec]�͖�T�O��
		if(u2g_systimer_1ms_wait_motion < (u2)U2L_1000_TIME ){
			u2g_systimer_1ms_wait_motion++;
		}
		else{
			u2g_systimer_1ms_wait_motion = U1L_ZERO;
			u2g_systimer_1sec_wait_motion++;
		}		
		if(u2g_systimer_1ms_for_signal < (u2)U2L_1000_TIME ){
			u2g_systimer_1ms_for_signal++;
		}
		else{
			u2g_systimer_1ms_for_signal = U1L_ZERO;
			if(u2g_systimer_1sec_for_signal < (u2)U2L_MAX ){
				u2g_systimer_1sec_for_signal++;
			}
			else{}
		}
		
		//	���錟���H���p�ɒǉ������^�C�}		
		if(u2g_systimer_1ms_timer_for_anjou < (u2)U2L_1000_TIME ){
			u2g_systimer_1ms_timer_for_anjou++;
		}
		else{
			u2g_systimer_1ms_timer_for_anjou = U1L_ZERO;
			if(u2g_systimer_1sec_timer_for_anjou < (u2)U2L_MAX ){
				u2g_systimer_1sec_timer_for_anjou++;
			}
			else{}
		}
			
		if((u2g_systimer_1sec_for_signal == U2L_TIME_KAHUKA_LOOSE_SEC)
		   && (u2g_systimer_1ms_for_signal == U2L_TIME_KAHUKA_LOOSE_MS)){
			u1g_timer_kahuka_loose_input = 1;
		}
		else if((u2g_systimer_1sec_for_signal == TIME_2sec)
			&& (u2g_systimer_1ms_for_signal == U1L_ZERO)){
			u1g_timer_2sec_input = 1;
		} 
		else if((u2g_systimer_1sec_for_signal == TIME_5sec)
			&& (u2g_systimer_1ms_for_signal == U1L_ZERO)){
		}
		
		else if((u2g_systimer_1sec_for_signal == TIME_90sec)
			&& (u2g_systimer_1ms_for_signal == U1L_ZERO)){
			u1g_total_timer_input = 1;
			u1g_huka_ad_value = (u1)u2g_ad_now[(CURR - CURR)]/4;
		}
		else{}
	
		u1g_c_no_plus++;
		if( u1g_c_no_plus >= 0xfe )
			{
				u1g_c_no_plus = 0xfd;
			}
		else{}

		u1g_count_timer_1ms++;
		if( u1g_count_timer_1ms >= U1L_100_TIME)		/*100ms�o��,100ms�������Z�͂�����*/
			{
				u1g_count_timer_1ms = U1L_ZERO;
				u1l_count_100ms++;
				Fg_timer_100ms_f = U1L_MAX;		/*100ms�o���׸޾��(8bit)*/
				
				if( u1g_t_break_max_timer_counter < 255 ){
					u1g_t_break_max_timer_counter ++;	//�g�����W�X�^�u���[�L�ő�o�͎��Զ��� */
				}				
				if(u1l_count_100ms >= U1L_10_TIME)		/*1s�o��,1s�������Z�͂�����*/
					{
						u1l_count_100ms = U1L_ZERO;
					}
				else{}
			}
		else{}
			
}

/**************************************************************/
/*     ������ϰؾ��                                           */
/**************************************************************/
void reset_system_timer(void)
{
		u1g_count_timer_1ms = U1L_ZERO;
		Fg_timer_100ms_f = U1L_ZERO;
}

void int_main_timer(void)
{
	u1g_fg_next_main_go = 1;/*���C������*/
}