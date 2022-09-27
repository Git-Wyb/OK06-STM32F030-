#include "Sys.h"
#include "variables.h"
#include "constants.h"
#include "functions.h"
#include "anjou_test.h"

#define U1L_TIME_RELAY_ON_WAIT		(u1)111		

u1 u1g_power_start = 0;

void mode_stop(void)
{
	static u1 u1a_relay_1_on_wait_cnt = 0;
	u1 u1a_temp_status = 0;
	
	u1a_temp_status = 0;
////	Fg_sol_out = 0;
////	u2g_systimer_1ms_sol_out = 0;
	
	if( u1g_different_mode == 1 ){
		u1g_step = select_step_stop();
		u1g_step_motion = 0;
		Fg_f_ene_sepablo = 0;			
		if(u1g_pre_mode != u1g_mode){
			u2g_systimer_1ms_for_signal = 0;
			u2g_systimer_1sec_for_signal = 0;
			u2g_c_move_consist = 0;				
			Fg_f_move_consist = 0;				
		}
		else{}
	}
	else{}


	switch( u1g_step ){
		case 0:
			if(100 <= u1g_current_mode){
				u2g_wait_motion_time_1ms = 0;
				u2g_wait_motion_time_1sec = TIME_BREAK_STOP;

				if( u1g_power_start == 1){
					u1a_temp_status = (u1)(motion_break());
				}
				else{
					u2g_c_interval_plus = 0x0000;	
				}
			}else{	
				if( check_torque_test_exec() == U1G_FACT_TRQ_EXEC ){	
					u2g_wait_motion_time_1ms = TIME_TESTER_SHORT_MS;
					u2g_wait_motion_time_1sec = 0;
				}else{
					u2g_wait_motion_time_1ms = 0;
					u2g_wait_motion_time_1sec = TIME_BREAK_STOP;
				}
				
				if( u1g_f_ok_set_on_shortbreak == 1 ){	
					u1a_temp_status = (u1)(motion_break());
				}else{
					u2g_c_interval_plus = 0x0000;
				}
			}
				
			if( ( u1g_fg_power_on == 1) && ( u1a_relay_1_on_wait_cnt >= U1L_TIME_RELAY_ON_WAIT )){
				u1g_fg_power_on = 0;
				u1g_power_start = 1;
			}		
			else{}
			
			if(u1a_relay_1_on_wait_cnt < U1L_TIME_RELAY_ON_WAIT){
				u1a_relay_1_on_wait_cnt++;
			}
			else{}
//			//u1a_temp_status = (u1)(motion_break());			

			if( u1a_temp_status != 0 ){
				u1g_step_motion = 0;
				u1g_step++;
			}
			else{}
			u1g_shutter_state = SF_BREAK;
			
			break;
			
		case 1:
			u2g_wait_motion_time_1ms = 0;
			u2g_wait_motion_time_1sec = TOTAL_TIMER;
			u1a_temp_status = motion_stop();
			if( u1a_temp_status != 0 ){
				u1g_step_motion = 0;
			}
			else{}
			u1g_shutter_state = SF_STOP;
			break;
			
		default:
			u1g_step = 0;
			break;
	}
}

void mode_wait_lock(void)
{
	u1 u1a_temp_status = 0;
	u1a_temp_status = 0;
	
	if( u1g_different_mode == 1 ){
		u1g_step = select_step_stop();
		u1g_step_motion = 0;
		if(u1g_pre_mode != u1g_mode){
			u2g_systimer_1ms_for_signal = 0;
			u2g_systimer_1sec_for_signal = 0;
		}
		else{}
	}
	else{}
	
	switch( u1g_step ){
		case 0:
			
			u2g_wait_motion_time_1ms = TIME_PRE_BREAK;
			u2g_wait_motion_time_1sec = TIME_BREAK_STOP;
			u2g_c_interval_plus = 0x0000;
			u1a_temp_status = (u1)(motion_close_startup());
			if( u1a_temp_status != 0 ){
				u1g_step_motion = 0;
////				u1g_step++;
			}
			else{}
			u1g_shutter_state = SF_CLOSE;

			break;
			
		case 1:
			u2g_wait_motion_time_1ms = 0;
			u2g_wait_motion_time_1sec = TOTAL_TIMER;
			u1a_temp_status = motion_stop();
			if( u1a_temp_status != 0 ){
				u1g_step_motion = 0;
			}
			else{}
			u1g_shutter_state = SF_STOP;
			break;
			
		default:
			u1g_step = 0;
			break;
	}
}

void mode_shortbreak(void)
{
	u1 u1a_temp_status = 0;
	u1a_temp_status = 0;
	
	if( u1g_different_mode == 1 ){
		u1g_step = 0;
		u1g_step_motion = 0;
		if(u1g_pre_mode != u1g_mode){
			u2g_systimer_1ms_for_signal = 0;
			u2g_systimer_1sec_for_signal = 0;
		}
		else{}
	}
	else{}
	
	switch( u1g_step ){
		case 0:
			
			u2g_wait_motion_time_1ms = TIME_PRE_BREAK;
			u2g_wait_motion_time_1sec = TIME_BREAK_STOP;
			u1a_temp_status = (u1)(motion_shortbreak());
			if( u1a_temp_status != 0 ){
				u1g_step_motion = 0;
////				u1g_step++;
			}
			else{}
			u1g_shutter_state = SF_BREAK;

			break;
			
		case 1:
			u2g_wait_motion_time_1ms = 0;
			u2g_wait_motion_time_1sec = TOTAL_TIMER;
			u1a_temp_status = motion_stop();
			if( u1a_temp_status != 0 ){
				u1g_step_motion = 0;
			}
			else{}
			u1g_shutter_state = SF_BREAK;
			break;
			
		default:
			u1g_step = 0;
			break;
	}
}


void mode_open_u(void)
{
	u1 u1a_temp_status = 0;
	
	u1a_temp_status = 0;
	if( u1g_different_mode == 1 ){
		u1g_step = select_step_open();
		u1g_step_motion = 0;
		Fg_f_ene_sepablo = 0;				
		if(u1g_pre_mode != u1g_mode){
			u2g_systimer_1ms_for_signal = 0;
			u2g_systimer_1sec_for_signal = 0;
			u2g_c_move_consist = 0;					
			Fg_f_move_consist = 0;					
		}
		else{}
	}
	else{}
	
	switch( u1g_step ){
		case 0:
			u2g_wait_motion_time_1ms = TIME_PRE_BREAK;
			u2g_wait_motion_time_1sec = 0;
			u1g_kahuka_input = 0;		//4.05
			u1g_c_kahuka = 0;		//4.05
			u1a_temp_status = (u1)(motion_break());
			if( u1a_temp_status != 0 ){
				u1g_step_motion = 0;
				u1g_step++;
			}
			else{}
			u1g_shutter_state = SF_BREAK;
			break;
			
		case 1:
			u2g_wait_motion_time_1ms = TIME_PRE_MOTION;
			u2g_wait_motion_time_1sec = 0;
			u1g_kahuka_input = 0;		//4.05
			u1g_c_kahuka = 0;		//4.05
			u1a_temp_status = motion_open_startup();
			if( u1a_temp_status != 0 ){
				calcu_std_huka();
				u1g_step_motion = 0;
				u1g_step++;
			}
			else{}
			u1g_shutter_state = SF_PRE_OPEN;
			break;
			
		case 2:
			u1g_threshold_huka = 1;	
			u2g_wait_motion_time_1ms = TIME_SOFT_MOTION_MS;
			u2g_wait_motion_time_1sec = TIME_SOFT_MOTION_SEC;
			u1a_temp_status = motion_soft_open();
			if( u1a_temp_status != 0 ){
				u1g_step_motion = 0;
				u1g_step++;
				Fg_f_finish_soft_start = 1;
			}
			else{}
			u1g_shutter_state = SF_SOFT_OPEN;
			break;
			
		case 3:
			u2g_wait_motion_time_1ms = 0;
			u2g_wait_motion_time_1sec = TOTAL_TIMER;
			u1a_temp_status = motion_open();
			if( u1a_temp_status != 0 ){
				u1g_step_motion = 0;
				u1g_total_timer_input = 1;
				u1g_huka_ad_value = (u1)u2g_ad_now[(CURR - CURR)]/4;
				u1g_step++;
			}
			else{}
			u1g_shutter_state = SF_OPEN;
			break;
			
		default:
			u1g_step = 0;
			break;
	}
	
}


void mode_close_u(void)
{
////	Fg_sol_out = 0;
////	u2g_systimer_1ms_sol_out = 0;
	u1 u1a_temp_status = 0;
	
	u1a_temp_status = 0;

	if( u1g_different_mode == 1 ){
		u1g_step = select_step_close();
		u1g_step_motion = 0;
		Fg_f_ene_sepablo = 0;					
		if(u1g_pre_mode != u1g_mode){
			u2g_systimer_1ms_for_signal = 0;
			u2g_systimer_1sec_for_signal = 0;
			u2g_c_move_consist = 0;					
			Fg_f_move_consist = 0;				
		}
		else{}
	}
	else{}
	
	switch( u1g_step ){
		case 0:
			u2g_wait_motion_time_1ms = TIME_PRE_BREAK;
			u2g_wait_motion_time_1sec = 0;
			u1g_kahuka_input = 0;		//4.05
			u1g_c_kahuka = 0;		//4.05
			u1a_temp_status = (u1)(motion_break());
			if( u1a_temp_status != 0 ){
				u1g_step_motion = 0;
				u1g_step++;
			}
			else{}
			u1g_shutter_state = SF_BREAK;
			break;
			
		case 1:
			u2g_wait_motion_time_1ms = TIME_PRE_MOTION;
			u2g_wait_motion_time_1sec = 0;
			u1g_kahuka_input = 0;		//4.05
			u1g_c_kahuka = 0;		//4.05
			u1a_temp_status = motion_close_startup();
			if( u1a_temp_status != 0 ){
				calcu_std_huka();
				u1g_step_motion = 0;
				u1g_step++;
			}
			else{}
			u1g_shutter_state = SF_PRE_CLOSE;
			break;
			
		case 2:
			u1g_threshold_huka = 1;	
			u2g_wait_motion_time_1ms = TIME_SOFT_MOTION_MS;
			u2g_wait_motion_time_1sec = TIME_SOFT_MOTION_SEC;
			u1a_temp_status = motion_soft_close();
			if( u1a_temp_status != 0 ){
				u1g_step_motion = 0;
				u1g_step++;
				Fg_f_finish_soft_start = 1;
			}
			else{}
			u1g_shutter_state = SF_SOFT_CLOSE;
			break;
			
		case 3:
			u2g_wait_motion_time_1ms = 0;
			u2g_wait_motion_time_1sec = TOTAL_TIMER;
			u1a_temp_status = motion_close();
			if( u1a_temp_status != 0){
				u1g_step_motion = 0;
				u1g_total_timer_input = 1;
				u1g_huka_ad_value = (u1)u2g_ad_now[(CURR - CURR)]/4;
				u1g_step++;
			}
			else{}
			u1g_shutter_state = SF_CLOSE;
			break;
			
		default:
			u1g_step = 0;
			break;
	}
	
}


void mode_osikiri_open(void)
{
	u1 u1a_temp_status = 0;
	
	u1a_temp_status = 0;

	if( u1g_different_mode == 1 ){
		u1g_step = select_step_osikiri_open();
		u1g_step_motion = 0;
		Fg_f_ene_sepablo = 0;				
		if(u1g_pre_mode != u1g_mode){
			u2g_systimer_1ms_for_signal = 0;
			u2g_systimer_1sec_for_signal = 0;
			u2g_c_move_consist = 0;					
			Fg_f_move_consist = 0;						
		}
		else{}
	}
	else{}
	
#if 0
	u2g_systimer_1ms_sol_out = 0;	
	
	if( u2g_systimer_1ms_sol_out < TIME_SOL_OUT ){
		Fg_sol_out = 1;
	}
	else{
		Fg_sol_out = 0;
	}
#endif
	
	switch( u1g_step ){
		case 0:
			u2g_wait_motion_time_1ms = TIME_PRE_BREAK;
			u2g_wait_motion_time_1sec = 0;
			u1g_kahuka_input = 0;		//4.05
			u1g_c_kahuka = 0;		//4.05
			u1a_temp_status = (u1)(motion_break());
			if( u1a_temp_status != 0 ){
				u1g_step_motion = 0;
				u1g_step++;
			}
			else{}
			u1g_shutter_state = SF_BREAK;
			break;
			
		case 1:
			u2g_wait_motion_time_1ms = TIME_PRE_MOTION;
			u2g_wait_motion_time_1sec = 0;
			u1g_kahuka_input = 0;		//4.05
			u1g_c_kahuka = 0;		//4.05
			u1a_temp_status = motion_open_startup();
			if( u1a_temp_status != 0 ){
				u1g_step_motion = 0;
				u1g_step++;
			}
			else{}
			u1g_shutter_state = SF_PRE_OPEN;
			break;
			
		case 2:
			u2g_wait_motion_time_1ms = TIME_SOFT_MOTION_MS;
			u2g_wait_motion_time_1sec = TIME_SOFT_MOTION_SEC;
			u1a_temp_status = motion_soft_open();
			if( u1a_temp_status != 0 ){
				u1g_step_motion = 0;
				u1g_step++;
			}
			else{}
			u1g_shutter_state = SF_SOFT_OPEN;
			break;
			
		case 3:
			u2g_wait_motion_time_1ms = 0;
			u2g_wait_motion_time_1sec = TOTAL_TIMER;
			u1a_temp_status = motion_open();
			if( u1a_temp_status != 0 ){
				u1g_step_motion = 0;
				u1g_total_timer_input = 1;
				u1g_huka_ad_value = (u1)u2g_ad_now[(CURR - CURR)]/4;
				u1g_step++;
			}
			else{}
			u1g_shutter_state = SF_OPEN;
			break;
			
		default:
			u1g_step = 0;
			break;
	}
	
}


void mode_osikiri_close(void)
{
////	Fg_sol_out = 0;
////	u2g_systimer_1ms_sol_out = 0;
	u1 u1a_temp_status = 0;
	
	u1a_temp_status = 0;

	if( u1g_different_mode == 1 ){
		u1g_step = select_step_osikiri_close();
		u1g_step_motion = 0;
		Fg_f_ene_sepablo = 0;					
		if(u1g_pre_mode != u1g_mode){
			u2g_systimer_1ms_for_signal = 0;
			u2g_systimer_1sec_for_signal = 0;
			u2g_c_move_consist = 0;					
			Fg_f_move_consist = 0;					
		}
		else{}
	}
	else{}
	
	switch( u1g_step ){
		case 0:
			u2g_wait_motion_time_1ms = TIME_PRE_BREAK;
			u2g_wait_motion_time_1sec = 0;
			u1g_kahuka_input = 0;		//4.05
			u1g_c_kahuka = 0;		//4.05
			u1a_temp_status = (u1)(motion_break());
			if( u1a_temp_status != 0 ){
				u1g_step_motion = 0;
				u1g_step++;
			}
			else{}
			u1g_shutter_state = SF_BREAK;
			break;
			
		case 1:
			u2g_wait_motion_time_1ms = TIME_PRE_MOTION;
			u2g_wait_motion_time_1sec = 0;
			u1g_kahuka_input = 0;		//4.05
			u1g_c_kahuka = 0;		//4.05
			u1a_temp_status = motion_close_startup();
			if( u1a_temp_status != 0 ){
				u1g_step_motion = 0;
				u1g_step++;
			}
			else{}
			u1g_shutter_state = SF_PRE_CLOSE;
			break;
			
		case 2:
			u2g_wait_motion_time_1ms = TIME_SOFT_MOTION_MS;
			u2g_wait_motion_time_1sec = TIME_SOFT_MOTION_SEC;
			u1a_temp_status = motion_soft_close();
			if( u1a_temp_status != 0 ){
				u1g_step_motion = 0;
				u1g_step++;
			}
			else{}
			u1g_shutter_state = SF_SOFT_CLOSE;
			break;
			
		case 3:
			u2g_wait_motion_time_1ms = 0;
			u2g_wait_motion_time_1sec = TOTAL_TIMER;
			u1a_temp_status = motion_close();
			if( u1a_temp_status != 0 ){
				u1g_step_motion = 0;
				u1g_total_timer_input = 1;
				u1g_huka_ad_value = (u1)u2g_ad_now[(CURR - CURR)]/4;
				u1g_step++;
			}
			else{}
			u1g_shutter_state = SF_CLOSE;
			break;
			
		default:
			u1g_step = 0;
			break;
	}
	
}


u1 select_step_stop(void)
{
	switch(u1g_shutter_state){
		case SF_STOP:
			return 1;
			
		default:
			return 0;
	}
	
}

u1 select_step_open(void)
{
	switch(u1g_shutter_state){
		case SF_OPEN:
		case SF_SAIKOU_OP:
			return 3;
			
		case SF_SOFT_OPEN:
		case SF_SOFT_SAI_OP:
			return 2;
		
		case SF_PRE_OPEN:
		case SF_PRE_SAI_OP:
			return 1;
			
		default:
			return 0;
	}

}

u1 select_step_close(void)
{
	switch(u1g_shutter_state){
		case SF_CLOSE:
		case SF_SAIKOU_CL:
			return 3;
			
		case SF_SOFT_CLOSE:
		case SF_SOFT_SAI_CL:
			return 2;
		
		case SF_PRE_CLOSE:
		case SF_PRE_SAI_CL:
			return 1;
			
		default:
			return 0;
	}

}

u1 select_step_osikiri_open(void)
{
	switch(u1g_shutter_state){
		case SF_OPEN:
		case SF_SAIKOU_OP:
			return 3;
			
		case SF_SOFT_OPEN:
		case SF_SOFT_SAI_OP:
			return 2;
			
		case SF_PRE_OPEN:
		case SF_PRE_SAI_OP:
			return 1;
			
		default:
			return 0;
	}

}

u1 select_step_osikiri_close(void)
{
	switch(u1g_shutter_state){
		case SF_CLOSE:
		case SF_SAIKOU_CL:
			return 3;
			
		case SF_SOFT_CLOSE:
		case SF_SOFT_SAI_CL:
			return 2;
			
		case SF_PRE_CLOSE:
		case SF_PRE_SAI_CL:
			return 1;
			
		default:
			return 0;
	}

}

