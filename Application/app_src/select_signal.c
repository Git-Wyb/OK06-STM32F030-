#include "Sys.h"
#include "variables.h"
#include "constants.h"
#include "functions.h"
#define DATF_LIGHT_VERSION
#include <string.h>
#include <stdlib.h>
#include "access_flash.h"
#include "a_data_exchange.h"
//#include "serial_transmission.h"

static void a_vol_f_set_overload(void);
static void a_vol_set_error_data(void);
static void a_vol_check_f_signal_rank_highest(void);
static void a_vol_check_f_signal_rank_high(void);
static void a_vol_check_f_signal_rank_low(void);
static void a_vol_check_f_signal_rank_lower(void);




void select_signal(void)
{
	a_vol_f_set_overload();

	u1g_pass_route_next_signal = 0;
	a_vol_check_f_signal_rank_highest();
	if( u1g_pass_route_next_signal == 0 ){
		a_vol_check_f_signal_rank_high();
		if( u1g_pass_route_next_signal == 0 ){
			a_vol_check_f_signal_rank_low();
			if( u1g_pass_route_next_signal == 0 ){
				a_vol_check_f_signal_rank_lower();
				if( u1g_pass_route_next_signal == 0 ){
					u1g_signal = 255;
				}
				else{}
			}
			else{}
		}
		else{}
	}
	else{}
}
	

static void a_vol_f_set_overload(void)
{
	if(!u1g_kahuka_input){
		u1g_previous_kahuka_input = 0;
	}
	else if(u1g_kahuka_input && u1g_previous_kahuka_input){
		u1g_kahuka_input = 0;
		u1g_previous_kahuka_input = 1;
	}
	else if(u1g_kahuka_input && (!u1g_previous_kahuka_input)){
		u1g_previous_kahuka_input = 1;
	}
	else{}
	
	
	if(u1g_different_mode == 1){
		clear_all_event_flags();
	}
	else{}
}

static void a_vol_set_error_data(void)
{
	if(u1g_mode == U1G_OPEN_MODE){
		u1g_error_mode = ERR_OPEN_OVERLOAD;
		
		a_vog_error_status_store(u1g_current_mode,u1g_signal,u1g_section_kahuka_occured);
	}
	else if(u1g_mode == U1G_CLOSE_MODE){
	
	
		if(u1g_Fg_ver_ad_error == 1){
			u1g_error_mode = ERR_POWER_PORT;		
		}else if(u1g_Fg_temp_ad_error == 1){
			u1g_error_mode = ERR_TEMP_PORT;			
		}else{
			u1g_error_mode = ERR_CLOSE_OVERLOAD;	
		}
		a_vog_error_status_store(u1g_current_mode,u1g_signal,u1g_section_kahuka_occured);
	}
	else{}
}

static void a_vol_check_f_signal_rank_highest(void)
{
	u1 u1a_temp = 0;

	if(u1g_kamen_total_input == 1){
		switch(u1g_current_mode){
			
			case 106:
			case 108:
			case 121:
			case 122:
			case 162:
			case 182:
			case 189:
			case 190:
			
				u1g_signal = 12;
				u1g_kamen_total_input = 0;
				u1g_pass_route_next_signal = 1;
				return;

			default:
				u1g_kamen_total_input = 0;
				break;
		}
	}
	else{}

	if(u1g_full_open_input == 1){
		u1g_signal = 8;
		u1g_full_open_input = 0;
		u2g_cnt_no_dire_p = 0x00;

	
		Fg_f_reset_able = 1;
		u1g_pass_route_next_signal = 1;
		return;
	}
	else{}	

	if((u1g_kahuka_input == 1) && (Fg_pwm_out == 1)){
		u1g_signal = 9;
		switch(u1g_current_mode){
			case 103:	
			case 106:	
			case 107:	
			case 108:	
			case 125:	
			case 182:	
				a_vol_set_error_data();		
				break;
			default:
				
				break;
		}
		if(u1g_mode == U1G_OPEN_MODE){

			Fg_f_reset_able = 1;
		}
		else{}
		u1g_kahuka_input = 0;
		u1g_pass_route_next_signal = 1;
		return;
	}
	else{}

	if(u1g_encoder_A_no_pulse || u1g_encoder_B_no_pulse){
		u1g_signal = 20;
		u1g_error_mode = ERR_ENCODER;	
		
		u1a_temp = u1g_huka_ad_value;
		a_vog_error_status_store(u1g_current_mode,u1g_signal,u1a_temp);
		u1g_encoder_A_no_pulse = 0;
		u1g_encoder_B_no_pulse = 0;
		osikiri_reset();
		u1g_pass_route_next_signal = 1;
		return;
	}
	else{}

	if(u1g_Fg_break_over_stop == 1){
		u1g_signal = 21;
		u1g_error_mode = ERR_HIGH_SPEED;	
		
		u1a_temp = u1g_mode;
		a_vog_error_status_store(u1g_current_mode,u1g_signal,u1a_temp);
		u1g_Fg_break_over_stop = 0;
		osikiri_reset();
		u1g_pass_route_next_signal = 1;
		return;
	}
	else{}

	if(u1g_thermal_input == 1){
		u1g_signal = 22;
		u1g_error_mode = ERR_THERMAL;

		u1a_temp = (u1)s2g_temp_now_signed;
		a_vog_error_status_store(u1g_current_mode,u1g_signal,u1a_temp);
		u1g_thermal_input = 0;
		osikiri_reset();
		u1g_pass_route_next_signal = 1;
		return;
	}
	else {}
	
	if(u1g_bousou_input == 1){
		u1g_signal = 22;
		u1g_error_mode = ERR_FET;
		
		u1a_temp = u1g_huka_ad_value;
		a_vog_error_status_store(u1g_current_mode,u1g_signal,u1a_temp);
		u1g_bousou_input = 0;
		osikiri_reset();
		u1g_pass_route_next_signal = 1;
		return;
	}
	else{}
}

static void a_vol_check_f_signal_rank_high(void)
{
	u1 u1a_90s_temp = 0;

	if(u1g_total_timer_input == 1){
		u1g_total_timer_input = 0;
		
		if(u1g_mode != 0){
			u1g_signal = 16;
			u1g_error_mode = ERR_TIME_OVER;	
			
			u1a_90s_temp = u1g_huka_ad_value;
			a_vog_error_status_store(u1g_current_mode,u1g_signal,u1a_90s_temp);
			ope_key_stop();
			Fg_key_stop_only = 0;
			u1g_key_open_only = 0;
			u1g_key_close_only = 0;
			osikiri_reset();
			u1g_pass_route_next_signal = 1;
			return;
		}
		
		else{}
	}
	else{}

	if(u1g_jougen_kitei_area_input == 1){
		switch(u1g_current_mode){
			case 10:
			case 102:
			case 118:
			case 119:
			
				u1g_signal = 24;
				u1g_jougen_kitei_area_input = 0;
				u1g_pass_route_next_signal = 1;
				return;
		
			default:
				u1g_jougen_kitei_area_input = 0;
				break;
		}
	}
	else{}
	
	if(Fg_osikiri_open == 1){
		u1g_signal = 6;
		u1g_pass_route_next_signal = 1;
		return;
	}
	else{}
	
	if(Fg_osikiri_close == 1){
		u1g_signal = 7;
		u1g_pass_route_next_signal = 1;
		return;
	}
	else{}
	
	if(u1g_key_3sw == 1){
		u1g_signal = 5;
		u1g_key_3sw = 0;
		u1g_pass_route_next_signal = 0;
		u1g_pass_route_next_signal = 1;
		return;
	}
	else{}
	
	if( (Fg_key_stop == 1) && (Fg_uart_fact_check_stop == FALSE) ){
		u1g_signal = 3;
		u1g_pass_route_next_signal = 1;
		return;
	}
	else{}
	
	if(Fg_key_open == 1){
		u1g_signal = 1;
		Fg_key_open = 0;
		
		if(u1g_f_50mm_range_out == 1){
			switch(u1g_current_mode){
				case 101:
				case 106:
				case 108:
				case 109:
				case 110:
				case 121:
				case 122:
				case 123:
				case 129:
					u1g_current_mode = 107;
					u1g_signal = 255;
					break;
				case 127:
					u1g_current_mode = 125;
					u1g_signal = 255;
					break;
				default:
					break;
			}
		}
		else{}
		
		u1g_pass_route_next_signal = 1;
		return;
	}
	else{}
	
	if(Fg_key_close == 1){
		if( ( s2g_cnt_plus >= s2g_size_ram[0]) && ( u1g_current_mode >= 100 ) && ( u1g_current_mode < 130 )){ /* ‘S•ÂˆÊ’u‚É‚¢‚éê‡‚Í•ÂM†‚É‚æ‚éó‘Ô‘JˆÚ‚Í–³Œø */
		}
		else{
			u1g_signal = 2;
		}
		Fg_key_close = 0;
		u1g_pass_route_next_signal = 1;
		return;
	}
	else{}
	
	if(u1g_timer_kahuka_loose_input == 1){
		
		switch(u1g_current_mode){
			
			case 116:
			case 194:
				u1g_signal = 14;
				u1g_timer_kahuka_loose_input = 0;
				u1g_pass_route_next_signal = 1;
				return;

			default:
				u1g_timer_kahuka_loose_input = 0;
				break;
		}
	}
	else{}
	
	if(u1g_timer_5sec_input == 1){
		
		switch(u1g_current_mode){
			case 11: 
				u1g_signal = 15;
				u1g_timer_5sec_input = 0;
				u1g_pass_route_next_signal = 1;
				return;
		
			default:
				u1g_timer_5sec_input = 0;
				break;
		}
	}
	else{}
}

static void a_vol_check_f_signal_rank_low(void)
{	
}

static void a_vol_check_f_signal_rank_lower(void)
{
	u1 u1l_ans = 0;

	if( u1g_f_complete_lock == 1 ){
		u1g_f_complete_lock = 0;
		switch( u1g_current_mode ){
		case 121:
		case 122:
		case 169:
		case 170:
		case 189:
		case 190:
			u1g_signal = 11;
			u1g_pass_route_next_signal = 1;
			return;
		default:
			break;
		}
	} else{
	}

	if( u1g_f_suspend_lock == 1 )
    {
		u1g_f_suspend_lock = 0;
		switch( u1g_current_mode )
        {
            case 121:
            case 169:
            case 189:
                u1g_signal = 13;
                u1g_pass_route_next_signal = 1;
                return;
            default:
                break;
		}
	}
    else
    {}

	if( u1g_f_lock_timeout_restart == 1 ){
		u1g_f_lock_timeout_restart = 0;
		switch( u1g_current_mode ){
		case 122:
		case 170:
		case 190:
			u1g_signal = 10;
			u1g_pass_route_next_signal = 1;
			return;
		default:
			break;
		}
	} else{
	}

	if( u1g_f_stop_shortclose == 1 ){
		u1g_f_stop_shortclose = 0;
		switch( u1g_current_mode ){
		case 5:
		case 28:
		case 104:
		case 126:
		case 176:
		case 177:
		case 196:
		case 197:
			u1g_signal = 25;
			u1g_pass_route_next_signal = 1;
			return;
		default:
			break;
		}
	} else{
	}
    
	if( u1g_f_stop_shortopen == 1 ){
		u1g_f_stop_shortopen = 0;
		switch( u1g_current_mode ){
		case 23:
		case 174:
			u1g_signal = 18;
			u1g_pass_route_next_signal = 1;
			return;
		default:
			break;
		}
	} else{
	}
    
	if( u1g_timer_2sec_input == 1 ){
		u1g_timer_2sec_input = 0;
		switch( u1g_current_mode ){
		case 125:
		case 173:
		case 193:
			u1g_signal = 17;
			u1g_pass_route_next_signal = 1;
			return;
		default:
			break;
		}
	} else{
	}
    
	if( u1g_f_rangein_kagen_kitei == 1 ){
		switch( u1g_current_mode ){
		case 101:
		case 128:
		case 129:
		case 130:
		case 199:
			u1g_signal = 19;
			u1g_pass_route_next_signal = 1;
			return;
		default:
			break;
		}
	} else{
	}

	if( u1g_f_start_lock_output == 1 ){
		u1g_f_start_lock_output = 0;
		switch( u1g_current_mode ){
		case 109:
		case 110:
		case 163:
		case 164:
		case 183:
		case 184:
			u1g_signal = 23;
			u1g_pass_route_next_signal = 1;
			return;
		default:
			break;
		}
	} else{
	}
    
	if( u1g_f_rangeout_kagen == 1 ){
		u1g_f_rangeout_kagen = 0;
		switch( u1g_current_mode ){
		case 128:
		case 130:
		case 180:
		case 199:
			u1g_signal = 26;
			u1g_pass_route_next_signal = 1;
			return;
		default:
			break;
		}
	} else{
	}
    
	if( u1g_f_limit_6min_lock == 1 ){
		u1g_f_limit_6min_lock = 0;
		switch( u1g_current_mode ){
		case 121:
		case 122:
		case 169:
		case 170:
		case 189:
		case 190:
			u1g_signal = 31;
			u1g_pass_route_next_signal = 1;
			return;
		default:
			break;
		}
	} else{
	}
	
	if( u1g_f_limit_5times_lock == 1 ){
		u1g_f_limit_5times_lock = 0;
		
		switch( u1g_current_mode ){
		case 121:
		case 122:
		case 169:
		case 170:
		case 189:
		case 190:
			u1g_signal = 32;
			u1g_pass_route_next_signal = 1;
			return;
		default:
			break;
		}
		
	} else{
	}
	
	if( u1g_f_move_sol == 1 ){
		u1g_f_move_sol = 0;
		switch( u1g_current_mode ){
		case 1:
		case 13:
		case 22:
		case 107:
		case 120:
		case 161:
		case 181:
		case 185:
			u1g_signal = 27;
			u1g_pass_route_next_signal = 1;
			return;
		default:
			break;
		}
	} else{
	}
	
	if( u1g_f_delay_lock == 1 ){
		u1g_f_delay_lock = 0;
		switch( u1g_current_mode ){
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
		
			u1g_signal = 30;
			u1g_pass_route_next_signal = 1;
			return;
		case 21:
			
			u1l_ans = learn_fullclose_position();
			if(u1l_ans == 1){
				u1g_signal = 30;
				u1g_pass_route_next_signal = 1;//mino
			}
			return;
		default:
			break;
		}
	} else{
	}
	
	if( u1g_f_start_shortbreak == 1 ){
		u1g_f_start_shortbreak = 0;
		switch( u1g_current_mode ){
		case 109:
		case 163:
		case 183:
			u1g_signal = 28;
			u1g_pass_route_next_signal = 1;
			return;
		default:
			break;
		}
	} else{
	}
	
	if( u1g_f_end_shortbreak == 1 ){
		u1g_f_end_shortbreak = 0;
		switch( u1g_current_mode ){
		case 110:
		case 164:
		case 184:
			u1g_signal = 29;
			u1g_pass_route_next_signal = 1;
			return;
		default:
			break;
		}
	} else{
	}
	
	if( u1g_f_sw_off_stop == 1 ){
		u1g_f_sw_off_stop = 0;
		switch( u1g_current_mode ){
		case 105:
			u1g_signal = 4;
			u1g_pass_route_next_signal = 1;
			return;
		default:
			break;
		}
	} else{
	}
}

void clear_all_event_flags(void)
{
	switch( u1g_current_mode ){
	case 128:	
	case 130:	
	case 199:
		
		break;
	default:
		u1g_timer_5sec_input = 0;
		u1g_timer_kahuka_loose_input = 0;
		u1g_timer_2sec_input = 0;
		u1g_kamen_total_input = 0;	
		u1g_total_timer_input = 0;
		u1g_jougen_kitei_area_input = 0;

		u1g_f_complete_lock = 0;
		u1g_f_suspend_lock = 0;
		u1g_f_stop_shortopen = 0;
		u1g_f_stop_shortclose = 0;
		u1g_f_rangeout_kagen = 0;
		break;
	}
}
void ope_key_stop(void)
{
		Fg_f_break = 1;	
		Fg_key_stop = 0x00;								
		u1g_ope_state_f = 0x2;							
		sw_in_end();									
}
