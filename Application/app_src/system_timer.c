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
/*		ローカル変数定義						*/
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
 *	タイマイベント設定
 *-----------------------------------------------
 *	引数
 *		無し
 *	戻り値
 *		無し
 *	処理内容
 *  	各時間経過毎にイベントを設定する
 *	呼出タイミング
 *		1ms毎
 ************************************************/
void int_system_timer(void)
{
/*------------------------ 1msec --------------------------*/
                                                    
	/********* ポンプ出力用 フラグ　**************/
	if( u1g_fg_charge_pump_enable == 1 ){
		P_RELAY_1 = ~P_RELAY_1;
	}
	else{
		P_RELAY_1 = 1;
	}

	//sw_input_check();					/*SW入力確認		*/
	u2g_c_interval_plus++;					/*ｴﾝｺｰﾀﾞ間隔ｶｳﾝﾀ*/
		
	/* pwmからブレーキ切替時間カウント */
	if( u1g_pwm_break_timer_counter < 255 ){
		u1g_pwm_break_timer_counter ++;
	}
//	参考　0xffffffff[msec]は約５０日
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
		
		//	安城検査工程用に追加したタイマ		
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
		if( u1g_count_timer_1ms >= U1L_100_TIME)		/*100ms経過,100msｶｳﾝﾀ加算はここで*/
			{
				u1g_count_timer_1ms = U1L_ZERO;
				u1l_count_100ms++;
				Fg_timer_100ms_f = U1L_MAX;		/*100ms経過ﾌﾗｸﾞｾｯﾄ(8bit)*/
				
				if( u1g_t_break_max_timer_counter < 255 ){
					u1g_t_break_max_timer_counter ++;	//トランジスタブレーキ最大出力時間ｶｳﾝﾀ */
				}				
				if(u1l_count_100ms >= U1L_10_TIME)		/*1s経過,1sｶｳﾝﾀ加算はここで*/
					{
						u1l_count_100ms = U1L_ZERO;
					}
				else{}
			}
		else{}
			
}

/**************************************************************/
/*     ｼｽﾃﾑﾀｲﾏｰﾘｾｯﾄ                                           */
/**************************************************************/
void reset_system_timer(void)
{
		u1g_count_timer_1ms = U1L_ZERO;
		Fg_timer_100ms_f = U1L_ZERO;
}

void int_main_timer(void)
{
	u1g_fg_next_main_go = 1;/*メイン周期*/
}