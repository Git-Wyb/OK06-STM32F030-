
/* Start user code for include. Do not edit comment generated here */
#include "Sys.h"
#include "variables.h"
#include "functions.h"
//#include "serial_transmission.h"
#include "flash_data_read.h"
#include "a_data_exchange.h"
/* End user code. Do not edit comment generated here */
#include "Gpio.h"
#include "variables.h"

#ifdef RELEASE
#define STATIC static
#else
#define STATIC
#endif

#define U2L_LIMIT_FIRST_8N			((u2)99)
#define U2L_LIMIT_OVER14N			((u2)221)
#define U2L_LIMIT_10to14			((u2)134)
#define U2L_LIMIT_6to10				((u2)69)

#define S2L_LOCK_STOP_P_OVER14			((s2)38)
#define S2L_LOCK_STOP_P_10TO14			((s2)28)
#define S2L_LOCK_STOP_P_6TO10			((s2)18)
#define S2L_LOCK_STOP_P_UNDER6			((s2)11)
#define U2L_LOCK_STOP_T_MAX			((u2)208)/* 936)  4.5ms*/
#define U2L_LOCK_STOP_T_MEAN			((u2)173)/* 780)  4.5ms*/
#define U4L_LIMITLOCK6MIN			((u4)80000)
#define U1L_LIMITLOCK5TIMES			((u1)5)
#define U2L_END_LOCKDELAY			((u2)1111)
#define S1L_START_SHORTBREAK			((s1)4)
#define U2L_LIMIT_LOCKOUT_FIRSTSTEP		((u2)222)
#define U1L_LIMIT_SUSPEND			((u1)177)
#define U2L_STOP_SHORTBREAK			((u2)444)
#define U1L_SOFT_LOCK_ERROR_TIME		((u2)1111)
#define U2L_LIMITLOCK6MIN_CLEAR			((u2)444)

STATIC s2 s2l_cnt_p_lockout = 0;
STATIC s2 s2l_threshold_stoplockout = 0;
STATIC s2 s2l_temp_p = 0;
STATIC u2 u2l_threshold_limittime = 0;
STATIC u2 u2l_timemoving_lockout = 0;
STATIC s2 s2l_p_temp = 0;
STATIC u2 u2l_c_time2s = 0;
STATIC u1 u1l_f_firststep_lockout = 0;
STATIC u2 u2l_lock_temp_maxload = 0;
STATIC u1 u1l_c_lockquit5times = 0;
STATIC u1 u1l_fg_short_break_cancel_hand_close = 0;

void a_vog_lock_cnt_poutput(void);


static void a_vog_lock_cnt_toutput(void);
static void a_vog_lock_setf_lock_suspend(void);
static void a_vog_lock_restart_output(void);
static void a_vog_lock_set_6minstop(void);
static void a_vog_lock_reset_5timesstop(void);
static void a_vog_lock_set_5timesstop(void);
static void a_vog_lock_set_delayend(void);
static void a_vog_lock_set_offshortbreak(void);
static void a_vog_lock_set_on_shortbreak(void);
static void a_vog_lock_set_swoff_stop(void);
static void a_vog_check_lock_position(void);
static void a_vog_select_max_duty_mode(void);

static void a_vol_lock_set_thresh_pout(void);
static u2 a_u2l_p_check(u2 u2a_cnt_times);
static void a_vol_lock_store_maxload(void);
static void soft_lock_error_rireki(u4 u4a_c_lockout6min );

void a_vog_lock_mode_main(void)
{
	a_vog_check_lock_position();
	
	a_vog_lock_cnt_poutput();
	a_vog_lock_cnt_toutput();
	a_vog_lock_setf_lock_suspend();
	a_vog_lock_restart_output();
	a_vog_lock_set_6minstop();
	a_vog_lock_set_5timesstop();
	a_vog_lock_reset_5timesstop();
	a_vog_lock_set_delayend();
	a_vog_lock_set_offshortbreak();
	a_vog_lock_set_on_shortbreak();
	a_vog_lock_set_swoff_stop();
	a_vog_select_max_duty_mode();
}


static void a_vog_lock_setf_lock_suspend(void)
{
	switch( u1g_current_mode ){
	case 121:
	case 169:
	case 189:
		a_vol_lock_store_maxload();
		
		if( u1l_f_firststep_lockout == 0 ){
		
			if( u2l_timemoving_lockout >= U2L_LIMIT_LOCKOUT_FIRSTSTEP ){
				u2l_timemoving_lockout = 0;
				u1l_f_firststep_lockout = 1;
				u1g_f_suspend_lock = 1;
			} else{}
			return;
		} else{
		}
	
		if( s2l_cnt_p_lockout >= s2l_threshold_stoplockout ){
			s2l_cnt_p_lockout = 0;
			u1g_f_suspend_lock = 1;
			u1l_c_lockquit5times = 0;

		} else if( u2l_timemoving_lockout >= u2l_threshold_limittime ){
			u2l_timemoving_lockout = 0;
			u1g_f_suspend_lock = 1;
			u1l_c_lockquit5times++;
		} else{}
		break;
	case 101:
	case 109:
	case 110:
	case 163:
	case 164:
	case 183:
	case 184:
		u1l_f_firststep_lockout = 0;
		u2l_lock_temp_maxload = 0;
		break;
	default:
		s2l_temp_p = s2g_cnt_plus;
		u2l_timemoving_lockout = 0;
		break;
	}
}

void a_vog_lock_cnt_poutput(void)
{
	switch( u1g_current_mode ){
	case 121:
	case 169:
	case 189:

		if( s2g_cnt_plus > s2l_temp_p ){
			s2l_cnt_p_lockout = s2l_cnt_p_lockout + (s2g_cnt_plus - s2l_temp_p);
			s2l_temp_p = s2g_cnt_plus;
		} else if( s2g_cnt_plus < s2l_temp_p ){
			s2l_cnt_p_lockout = s2l_cnt_p_lockout - (s2l_temp_p - s2g_cnt_plus);
			s2l_temp_p = s2g_cnt_plus;
		} else{}
		break;
	default:
		s2l_cnt_p_lockout = 0;
		break;
	}
}

static void a_vog_lock_cnt_toutput(void)
{
	switch( u1g_current_mode ){
	case 121:
	case 169:
	case 189:

		u2l_timemoving_lockout++;
		break;
	default:
		u2l_timemoving_lockout = 0;
		break;
	}
}


static void a_vol_lock_store_maxload(void)
{
	if( u2l_lock_temp_maxload < u2g_ad_now[(CURR - CURR)] ){
		u2l_lock_temp_maxload = u2g_ad_now[(CURR - CURR)];
	} else{
	}

	
	if( (u1l_f_firststep_lockout == 0) && (u2l_lock_temp_maxload > U2L_LIMIT_FIRST_8N) ){
		u2l_lock_temp_maxload = U2L_LIMIT_FIRST_8N;
	}
	else{}
}




static void a_vol_lock_set_thresh_pout(void)
{
	if( u2l_lock_temp_maxload >= U2L_LIMIT_OVER14N ){
		s2l_threshold_stoplockout = S2L_LOCK_STOP_P_OVER14;
		u2l_threshold_limittime = U2L_LOCK_STOP_T_MAX;
	} else if( u2l_lock_temp_maxload >= U2L_LIMIT_10to14 ){
		s2l_threshold_stoplockout = S2L_LOCK_STOP_P_10TO14;
		u2l_threshold_limittime = U2L_LOCK_STOP_T_MEAN;
	} else if( u2l_lock_temp_maxload >= U2L_LIMIT_6to10 ){
		s2l_threshold_stoplockout = S2L_LOCK_STOP_P_6TO10;
		u2l_threshold_limittime = U2L_LOCK_STOP_T_MEAN;
	} else{
		s2l_threshold_stoplockout = S2L_LOCK_STOP_P_UNDER6;
		u2l_threshold_limittime = U2L_LOCK_STOP_T_MEAN;
	}
}


static void a_vog_lock_restart_output(void)
{
	static u1 u1a_c_suspendtime = 0;

	switch( u1g_current_mode ){
	case 122:
	case 170:
	case 190:	
		if( u1a_c_suspendtime == 0 ){
		
			a_vol_lock_set_thresh_pout();
		} else{
		}
		u2l_lock_temp_maxload = 0;
		u1a_c_suspendtime++;
		if( u1a_c_suspendtime >= U1L_LIMIT_SUSPEND ){
			u1a_c_suspendtime = 0;
			u1g_f_lock_timeout_restart = 1;
		} else{}
		break;
	default:
		u1a_c_suspendtime = 0;
		break;
	}
}


static void a_vog_lock_set_6minstop(void)
{
	static u4 u4a_c_lockout6min = 0;
	static u2 u2a_c_lockout6min_clear = 0;

	switch( u1g_current_mode ){
	case 121:
	case 122:
	case 169:
	case 170:
	case 189:
	case 190:
		u4a_c_lockout6min++;
		u2a_c_lockout6min_clear = 0;
		soft_lock_error_rireki(u4a_c_lockout6min);
		
		if( u4a_c_lockout6min >= U4L_LIMITLOCK6MIN ){
			u4a_c_lockout6min = 0;
			u1g_f_limit_6min_lock = 1;
		
		} else{
		}
		break;
	case 109:
	case 110:
	case 163:
	case 164:
	case 183:
	case 184:
		u2a_c_lockout6min_clear++;
		if( u2a_c_lockout6min_clear >= U2L_LIMITLOCK6MIN_CLEAR ){
			u2a_c_lockout6min_clear = 0;
			u4a_c_lockout6min = 0;
		}
		else{}
		break;
	default:
		u4a_c_lockout6min = 0;
		u2a_c_lockout6min_clear = 0;
		break;
	}
}


void a_vog_lock_set_5timesstop(void)
{
	if( u1l_c_lockquit5times >= U1L_LIMITLOCK5TIMES ){
		u1l_c_lockquit5times = 0;
		u1g_f_limit_5times_lock = 1;
	} else{
	}
}


static void a_vog_lock_reset_5timesstop(void)
{
	switch( u1g_current_mode ){
	case 121:
	case 122:
	case 169:
	case 170:
	case 189:
	case 190:
		break;
	default:
		u1l_c_lockquit5times = 0;
		break;
	}
}

static void a_vog_lock_set_delayend(void)
{
	static u2 u2a_c_lockdelay = 0;

	switch( u1g_current_mode ){
		case 21:
		case 100:
		case 123:
		case 127:
		case 129:
		case 160:
		case 165:
		case 171:
		case 172:
		case 180:
		case 186:
		case 191:
		case 192:

			u2a_c_lockdelay++;
			if( Fg_key_stop == 1 ){
				u2a_c_lockdelay = 0;	
			}
			else{}
			if( u2a_c_lockdelay >= U2L_END_LOCKDELAY ){
				u2a_c_lockdelay = 0;
				u1g_f_delay_lock = 1;
			} else{
			}
			break;
/*		case 160:
			u2a_c_lockdelay++;
			if( u2a_c_lockdelay >= U2L_END_LOCKDELAY ){
				if( s2g_cnt_plus > 0 - 25){
					u2a_c_lockdelay = 0;
					u1g_f_delay_lock = 1;
				}
			} else{
			}
			break;*/
		
	default:
		u2a_c_lockdelay = 0;
			break;
	}
}


static void a_vog_lock_set_offshortbreak(void)
{
	static  u2 u2a_c_end_shortbreak = 0;
	
	switch( u1g_current_mode ){
	case 110:
	case 164:
	case 184:
		u2a_c_end_shortbreak++;
		u2a_c_end_shortbreak = a_u2l_p_check(u2a_c_end_shortbreak);
		if( u2a_c_end_shortbreak >= U2L_STOP_SHORTBREAK ){
			u2a_c_end_shortbreak = 0;
			u1g_f_end_shortbreak = 1;
		} else{
		}
		break;
	default:
		u2a_c_end_shortbreak = 0;
		s2l_p_temp = s2g_cnt_plus;
		break;
	}
}

static u2 a_u2l_p_check(u2 u2a_cnt_times)
{
	/* if( s2g_cnt_plus != s2l_p_temp ){ */
	if( s2g_cnt_plus < s2l_p_temp ){
		u2a_cnt_times = 0;
	} else{
	}
	s2l_p_temp = s2g_cnt_plus;
	return u2a_cnt_times;
}


static void a_vog_lock_set_on_shortbreak(void)
{
	static s2 s2a_p_start_level_1_time_before = 0;
	static s2 s2a_pre_cnt_plus = 0;
	static s2 s2a_break_start_base_pos;		


	if((u1g_different_mode == 1) && (u1g_pre_mode != U1G_STOP_MODE)){
		s2a_p_start_level_1_time_before = s2g_cnt_plus;		
	}
	else{}
	
	switch( u1g_current_mode ){
	case 109:
		
		if( ( (u1g_different_mode == 1) && (u1g_previous_mode != 110) ) ||
			( s2g_cnt_plus > s2a_pre_cnt_plus )	)		
		{
			if(s2g_cnt_plus < s2g_lock_start_position){	
				s2a_break_start_base_pos = s2g_lock_start_position;
			}else{
				s2a_break_start_base_pos = s2g_cnt_plus;
			}
		}
		else{}
	
		
		if( s2g_cnt_plus < s2a_pre_cnt_plus ){
			
			if( s2g_cnt_plus <= (s2a_break_start_base_pos - S1L_START_SHORTBREAK) ){
				u1g_f_start_shortbreak = 1;
			}
			else{}
		}
		else{}
	
		break;
	case 163:
	case 183:
	
		if( s2g_cnt_plus < s2a_pre_cnt_plus ){
			
			if( s2g_cnt_plus <= (s2g_lock_start_position - S1L_START_SHORTBREAK) ){
				u1g_f_start_shortbreak = 1;
			}
			else{}
			
			
			if( (s2a_p_start_level_1_time_before - s2g_cnt_plus) >= S1L_START_SHORTBREAK ){
				u1g_f_start_shortbreak = 1;
			}
			else{}
		}
		else{}
		break;
	default:
		u1g_f_start_shortbreak = 0;
		break;
	}
	
	s2a_pre_cnt_plus = s2g_cnt_plus;	
}

static void a_vog_lock_set_swoff_stop(void)
{
	switch( u1g_current_mode ){
	case 105:
		if( Fg_keyoff_stop == 1 ){
			u1g_f_sw_off_stop = 1;
		} else{
		}
		break;
	default:
		u1g_f_sw_off_stop = 0;
		break;
	}
}


static void soft_lock_error_rireki(u4 u4a_c_lockout6min)
{
	static u1 u1a_lockout_write = 0;	
	u1 u1a_temp = 0;
	
	if( u4a_c_lockout6min >= U1L_SOFT_LOCK_ERROR_TIME ){
		if(u1a_lockout_write == 0){	
			u1g_error_mode = ERR_SOFT_ROCK_OUT;	
			u1a_temp = u1g_huka_ad_value;
			a_vog_error_status_store(u1g_current_mode,u1g_signal,u1a_temp);
		}
		else{}
		u1a_lockout_write = 1;		
	} else{
		u1a_lockout_write = 0;
	}
}

static void a_vog_check_lock_position(void)
{
	static u1 u1l_change_position = 0;		
	static u1 u1l_Fg_change_position_time = 0;	
	

	
	
	if( ( u1g_current_mode >= 160) && ( u1g_current_mode < 180 )){
		if( u1g_mode != U1G_STOP_MODE ){
			u1l_change_position = 1;
		}
	}
	
	if( ( u1g_current_mode >= 180) && ( u1g_current_mode < 200 )){
		if( (u1g_mode == U1G_CLOSE_MODE) || (u1g_mode == U1G_OSIKIRI_CLOSE_MODE) ){
			u1l_change_position = 1;
		}
		else if( ( u1g_mode != U1G_STOP_MODE ) && ( s2g_cnt_plus <= s2g_size_ram[0] ) ){
			u1l_change_position = 0;
		}
		else{}
	}

	if( u1g_different_mode == 1){
		switch( u1g_current_mode ){
			case 160:
				if( u1l_change_position == 1){		
					u1l_Fg_change_position_time = 1;	
				}
				break;
			case 180:
			case 183:
				if( ( u1l_change_position == 1) && ( s2g_cnt_plus > s2g_size_ram[0] ) ){
					u1l_Fg_change_position_time = 1;
				}
				break; 
			default:
			break;
		}
	}

	else{
	
		/************************************************************************************/
		if( u1g_mode == U1G_STOP_MODE){
			if( ( u1g_current_mode >= 160 ) && ( u1g_current_mode < 180 ) ){
				if( s2g_cnt_plus > 0 ){	
					if( u1l_change_position == 0){
						u1g_Fg_hand_close_plus = 1;
						s2g_cnt_plus = 0;
						
					}
				}
				else{
					u1g_Fg_hand_close_plus = 0;
				}
			}
			else if( ( u1g_current_mode >= 180 ) && ( u1g_current_mode < 200 ) ){
				if( s2g_cnt_plus > s2g_size_ram[0] ){
					if( u1l_change_position == 0){
						u1g_Fg_hand_close_plus = 1;
						s2g_cnt_plus = s2g_size_ram[0];
						s2g_lock_start_position= s2g_cnt_plus;
					}
				}
				else{
					u1g_Fg_hand_close_plus = 0;
					if(u1l_change_position == 0){
						if( s2g_lock_start_position <= s2g_cnt_plus ){
							s2g_lock_start_position = s2g_cnt_plus;	
						}
					}
					
				}
			}
			else{}
		}
	}
	
	
	switch( u1g_current_mode ){
		case 163:
			if( u1g_previous_mode == 160  ){		
				s2g_cnt_plus = 0;
				u1l_change_position = 0;
				u1l_Fg_change_position_time = 0;
				s2g_lock_start_position = s2g_cnt_plus;
			}
			else{
				u1l_change_position = 0;
				u1l_Fg_change_position_time = 0;
			}
			break;
		case 183:
		
			if( ( u1g_previous_mode == 180  ) && ( s2g_cnt_plus > s2g_size_ram[0] )){
				if( u1l_Fg_change_position_time == 1 ){				
					s2g_cnt_plus = s2g_size_ram[0];
					s2g_lock_start_position = s2g_cnt_plus;
					u1l_change_position = 0;
					u1l_Fg_change_position_time = 0;
				}
				else{
					u1l_change_position = 0;
				}
			}
			
			if( u1g_previous_mode == 186  ){
				s2g_lock_start_position = s2g_cnt_plus;
				u1l_change_position = 0;
				u1l_Fg_change_position_time = 0;
			}
			
			
			else{
				u1l_Fg_change_position_time = 0;
				u1l_change_position = 0;
			}
			break;	
		default:
		break;
	}
}

static void a_vog_select_max_duty_mode(void)
{
	switch(u1g_current_mode){
		case 121:
		case 169:
		case 189:
			u1g_Fg_soft_lock_out_duty = 1;
			break;
		default:
			u1g_Fg_soft_lock_out_duty = 0;
			break;
	}
}

