
#include "Sys.h"
#include "Timer.h"
#include "variables.h"
#include "constants.h"
#include "functions.h"
#include "Gpio.h"
#include "input_encoder.h"
#include "a_data_exchange.h"
#include <string.h>
#include <stdlib.h>
#include "tst_break.h"

u2 u2g_t_break_duty = 0;		
u1 u1g_t_break_step = 0;		
u1 Fg_t_break_off_count_start = 0;	
s2 s2g_t_break_off_start_plus = 0;	
u1 u1g_t_break_max_timer_counter = 0;
u1 Fg_t_break_max_time = 0;		
u1 Fg_t_break_timer_start = 0;	
u1 u1g_Fg_pwm_off_for_break = 0;
u1 u1g_Fg_break_over_stop = 0;	

s2 s2g_t_break_pwm_restart_plus = 0;

u1 u1g_Fg_pwm_restart = 0;		

u1 u1g_Fg_pwm_start_pass_code = 0;	
u1 u1g_Fg_break_start_pass_code = 0;

u1 u1g_Fg_break_ok = 0;
u1 u1g_t_break_step_first = 0;
u1 u1g_pwm_break_timer_counter = 0;
u2 u2g_previous_break_duty = 0;

static void t_break_on(void);
static void pwm_off_break_off_setting(void);
static void pwm_off_break_on_setting(void);
static void pwm_off_break_max_setting(void);
static void pwm_on_break_off_setting(void);
static void break_off_pwm_restart(void);
static void pwm_break_time(void);
static u1 check_break_step_change( u1 u1_step_pulse ,s2 s2_start_pulse );
static void break_step0_to_1(void);
static u1 check_stop_pulse( u1 u1a_t_break_step );
static u2 get_break_data( break_data data_order );

void check_t_break_main(void)
{	
	u1 u1l_enable_next_step = 0;

	u2 u2a_break_on_pulse_length = 0;
	u2 u2a_pulse_break_start = 0;
	
	switch( u1g_t_break_step){
		case PWM_ON_BREAK_OFF:
			pwm_on_break_off_setting();
	
			break_step0_to_1();
			
			if(u1g_t_break_step == PWM_OFF_BREAK_OFF){
				Fg_t_break_off_count_start = 0;
				u1g_t_break_step_first = 0;
			}
			else{}
			
			break;
		case PWM_OFF_BREAK_OFF:
			pwm_break_time();
			pwm_off_break_off_setting();
			
			u2a_break_on_pulse_length = get_break_data(E_BREAK_ON_PULSE_LENGTH);
			u2a_pulse_break_start = get_break_data(E_PULSE_BREAK_START);

			if( u2g_d_rpm_current >= u2a_break_on_pulse_length ){
				
				if( Fg_t_break_off_count_start == 0){
					Fg_t_break_off_count_start = 1;
					s2g_t_break_off_start_plus = s2g_cnt_plus;
				}
				else{}
		
				if( u1g_Fg_break_ok == 1 ){
					u1l_enable_next_step = check_break_step_change( (u1)u2a_pulse_break_start,s2g_t_break_off_start_plus );
					u1g_t_break_step = u1l_enable_next_step + u1g_t_break_step;
					
					if( u1g_t_break_step == PWM_OFF_BREAK_ON ){
						u1g_t_break_step_first = 0;
						s2g_t_break_off_start_plus = 0;
						Fg_t_break_off_count_start = 0;
					}
				}
			}
			else{
				Fg_t_break_off_count_start = 0;
			}
			break;
			
		case PWM_OFF_BREAK_ON:
			pwm_off_break_on_setting();

			if( ( u1g_mode == U1G_CLOSE_MODE) || ( u1g_mode == U1G_OSIKIRI_CLOSE_MODE) ){
				t_break_on();
				if( u2g_t_break_duty > D_BREAK_3_LEVEL ){
					u2g_t_break_duty = D_BREAK_3_LEVEL;
				}
			}

			else if( ( u1g_mode == U1G_OPEN_MODE) || ( u1g_mode == U1G_OSIKIRI_OPEN_MODE) ){
				t_break_on();
			}
			else{}
			break;
		default:
			break;
	}
	u2g_previous_break_duty = u2g_t_break_duty;	
	break_off_pwm_restart();
	
	u1g_t_break_step = check_stop_pulse(u1g_t_break_step);

}

static void t_break_on(void)
{
	static u1 u1a_break_off_counter = 0;
	u2 u2a_break_on_pulse_length = 0;
	u2 u2a_break_max_pulse_length = 0;
	u2 u2a_break_off_pulse_length = 0;

	u2a_break_max_pulse_length = get_break_data(E_BREAK_MAX_PULSE_LENGTH);
	u2a_break_on_pulse_length = get_break_data(E_BREAK_ON_PULSE_LENGTH);
	u2a_break_off_pulse_length = get_break_data(E_BREAK_OFF_PULSE_LENGTH);
	
	if( u2g_d_rpm_current >= u2a_break_max_pulse_length ){
		if( Fg_t_break_max_time < BREAK_MAX_FIRST_WAIT ){
			Fg_t_break_max_time ++;
			u1g_t_break_max_timer_counter = 0;		
			pwm_off_break_max_setting();			
			u2g_t_break_duty = u2g_previous_break_duty;
		}
		else if(Fg_t_break_max_time >= BREAK_MAX_FIRST_WAIT){
			pwm_off_break_max_setting();
			
			u2g_t_break_duty = (BREAK_MAX_P * ( u2g_d_rpm_current - u2a_break_max_pulse_length )) + D_BREAK_0_72_LEVEL;
			if( u1g_t_break_max_timer_counter >= TIME_MAX_BREAK_STOP){
			
				s2g_t_break_off_start_plus = 0;		
				Fg_t_break_off_count_start = 0;
				u1g_t_break_step = PWM_ON_BREAK_OFF;
				Fg_t_break_max_time = 0;
				u1g_t_break_max_timer_counter = 0;
				Fg_t_break_timer_start = 0;
				
				u1g_Fg_break_over_stop = 1;	
			}
			else{}
		}
		else{}
		u1a_break_off_counter = 0;	
	}
	else if( (u2g_d_rpm_current >= u2a_break_on_pulse_length) && (Fg_t_break_max_time >= BREAK_MAX_FIRST_WAIT) ){
		pwm_off_break_max_setting();
		u2g_t_break_duty = BREAK_MID_P * ( u2g_d_rpm_current - u2a_break_on_pulse_length );

		u1g_t_break_max_timer_counter = 0;
		u1a_break_off_counter = 0;	
	}
	else if( u2g_d_rpm_current >= u2a_break_off_pulse_length ){
		pwm_off_break_on_setting();
		u2g_t_break_duty = BREAK_LOW_P * ( u2g_d_rpm_current - u2a_break_off_pulse_length );
		Fg_t_break_max_time = 0;

		u1g_t_break_max_timer_counter = 0;
		u1a_break_off_counter = 0;
	}
	else if(u2g_d_rpm_current < u2a_break_off_pulse_length ){
		Fg_t_break_max_time = 0;
		if( u1a_break_off_counter < BREAK_OFF_FIRST_WAIT){
			u1a_break_off_counter ++;
		}
		if(u1a_break_off_counter >= BREAK_OFF_FIRST_WAIT){ 
			u1a_break_off_counter = 0;
			u1g_t_break_step = PWM_OFF_BREAK_OFF;
			Fg_t_break_max_time = 0;
			u1g_t_break_max_timer_counter = 0;
			pwm_off_break_off_setting();
		}
		else{
			pwm_off_break_on_setting();
			u2g_t_break_duty = D_BREAK_MIN_LEVEL;
		}
	}
	else{}

	if( u2g_t_break_duty > D_BREAK_5_6_LEVEL ){
		u2g_t_break_duty = D_BREAK_5_6_LEVEL;
	}
}

static void break_off_pwm_restart(void)
{
	u1 u1l_enable_next_step = 0;
	
	if( u1g_t_break_step != PWM_ON_BREAK_OFF ){

		if( u2g_d_rpm_current <= STAND_PLUS_LENGTH ){
			
			if( u1g_Fg_pwm_restart == 0 ){
				
				u1g_Fg_pwm_restart = 1;			
				s2g_t_break_pwm_restart_plus = s2g_cnt_plus;
			}
			else{	
				u1l_enable_next_step = check_break_step_change( PWM_RESTART_PULSE , s2g_t_break_pwm_restart_plus );

				if( u1l_enable_next_step == 1 ){
					pwm_on_break_off_setting();	
					u1g_t_break_step = PWM_ON_BREAK_OFF;
					s2g_t_break_pwm_restart_plus = 0;	
					u1g_Fg_pwm_restart = 0;	
					u1g_Fg_break_ok = 0;
					s2g_t_break_off_start_plus = 0;
					Fg_t_break_off_count_start = 0;
					
				}
				else{}
			}
		}
		else{}
	}
	else{}
}

static void break_step0_to_1(void)
{
	u1 u1l_enable_next_step = 0;
	
	u2 u2a_pwm_off_pulse_length = 0;
	u2 u2a_pulse_break_wait = 0;
	
	u2a_pwm_off_pulse_length = get_break_data(E_PWM_OFF_PULSE_LENGTH);
	u2a_pulse_break_wait = get_break_data(E_PULSE_BREAK_WAIT);
	
	if( u2g_d_rpm_current >= u2a_pwm_off_pulse_length ){
		if( Fg_t_break_off_count_start == 0){
			Fg_t_break_off_count_start = 1;
			s2g_t_break_off_start_plus = s2g_cnt_plus;
		}
	
		u1l_enable_next_step = check_break_step_change( (u1)u2a_pulse_break_wait,s2g_t_break_off_start_plus );
		u1g_t_break_step = u1l_enable_next_step;
	}
	else{
		s2g_t_break_off_start_plus = 0;
		Fg_t_break_off_count_start = 0;
	}
}

static void pwm_off_break_off_setting(void)
{
	u1g_Fg_pwm_off_for_break = 1;
	u2g_d_pwm = D_PWM_MIN;			
	u2g_t_break_duty = D_BREAK_0_LEVEL;
	u1g_Fg_pwm_start_pass_code = 0;
////	TDR07 = 0x00;
	R_TAU0_Channel6_Stop();	
////	TO0 &= ~_0080_TAU_CH7_OUTPUT_VALUE_1;
	u1g_Fg_break_start_pass_code = 0;
}

static void pwm_off_break_on_setting(void)
{
	u2 u2a_d_break_min_level = 0;
	
	u2a_d_break_min_level = get_break_data(E_D_BREAK_MIN_LEVEL);
	
	if( u1g_Fg_break_start_pass_code == 0 ){
		R_TAU0_Channel6_Start();
		u1g_Fg_break_start_pass_code = 1;
	}
	u1g_Fg_pwm_off_for_break = 1;
	u2g_d_pwm = D_PWM_MIN;
	u2g_t_break_duty = u2a_d_break_min_level;
}

static void pwm_off_break_max_setting(void)
{
	u2 u2a_d_break_3_level = 0;
	
	u2a_d_break_3_level = get_break_data(E_D_BREAK_3_LEVEL);
	
	if( u1g_Fg_break_start_pass_code == 0 ){
		R_TAU0_Channel6_Start();
		u1g_Fg_break_start_pass_code = 1;
	}
	u1g_Fg_pwm_off_for_break = 1;
	u2g_d_pwm = D_PWM_MIN;
	u2g_t_break_duty = u2a_d_break_3_level;
}

static void pwm_on_break_off_setting(void)
{
	u1g_Fg_pwm_off_for_break = 0;
	u2g_t_break_duty = D_BREAK_0_LEVEL;
////	TDR07 = 0x00;
	R_TAU0_Channel6_Stop();
////	TO0 &= ~_0080_TAU_CH7_OUTPUT_VALUE_1;
	u1g_Fg_break_start_pass_code = 0;
}

void t_flag_all_clear(void)
{
	s2g_t_break_off_start_plus = 0;		
	Fg_t_break_off_count_start = 0;
	u1g_t_break_step = PWM_ON_BREAK_OFF;
	Fg_t_break_max_time = 0;
	u1g_t_break_max_timer_counter = 0;
	u2g_t_break_duty = D_BREAK_0_LEVEL;
	u1g_Fg_pwm_off_for_break = 0;
	Fg_t_break_timer_start = 0;

////	TDR07 = 0x00;
	R_TAU0_Channel6_Stop();	
////	TO0 &= ~_0080_TAU_CH7_OUTPUT_VALUE_1;
	u1g_Fg_break_start_pass_code = 0;
}

static void pwm_break_time(void)
{
	if( u1g_t_break_step_first == 0){
		u1g_t_break_step_first = 1;
		u1g_pwm_break_timer_counter = 0;
		u1g_Fg_break_ok = 0;
	}
	
	if( u1g_pwm_break_timer_counter >= BREAK_OUT_WAIT_TIME){
		u1g_Fg_break_ok = 1;
	}
}

static u1 check_break_step_change(u1 u1_step_pulse,s2 s2_start_pulse)
{
	u1 u1l_tr_break_step = 0;
	
	if( ( u1g_mode == 1) || ( u1g_mode == 3) ){	
		if( s2g_cnt_plus <= ( (s2)s2_start_pulse - (s2)u1_step_pulse )){
			u1l_tr_break_step = 1;	
		}
	}
	else if( ( u1g_mode == 2) || ( u1g_mode == 4) ){	
		if( s2g_cnt_plus >= ( (s2)s2_start_pulse + (s2)u1_step_pulse ) ){
			u1l_tr_break_step = 1;	
		}
	}
	else{}
	
	return u1l_tr_break_step;
}

void check_encoder_duty_stop_cancel(void){
	
	if( Fg_pwm_out == 1 ){
		
		if(  Fg_soft_start_f != 1 ){
			if( u2g_c_interval_plus > 20 ){
				u2g_d_pwm += NORMAL_21MS_MORE_DUTY;	//RK02:	+20 -> OK04 109
			}
		}
	}	
}

static u1 check_stop_pulse( u1 u1a_t_break_step ){

	static u1 u1a_stop_pulse_cnt = 0;
	static s2 s2a_pre_cnt_plus = 0;
	u1 u1a_ret_break_step = u1a_t_break_step;

	if( u1g_t_break_step == PWM_ON_BREAK_OFF ){
		u1a_stop_pulse_cnt = 0;			
		s2a_pre_cnt_plus = s2g_cnt_plus;
	}else{
		
		if(s2a_pre_cnt_plus != s2g_cnt_plus){
			u1a_stop_pulse_cnt = 0;
			s2a_pre_cnt_plus = s2g_cnt_plus;
		}
		else{}
		
		if(u1a_stop_pulse_cnt >= LIMIT_STOP_WAIT_TIME){
			u1a_ret_break_step--;
			u1a_stop_pulse_cnt = 0;
			
			s2g_t_break_off_start_plus = 0;
			Fg_t_break_off_count_start = 0;
			Fg_t_break_max_time = 0;
			u1g_t_break_max_timer_counter = 0;
		}else{
			u1a_stop_pulse_cnt++;
		}
	}
	
	return u1a_ret_break_step;
}


static u2 get_break_data( break_data data_order ){
	
	u2 u2a_ret_data = 0;
	
	if( ( u1g_mode == U1G_CLOSE_MODE) || ( u1g_mode == U1G_OSIKIRI_CLOSE_MODE) ){
		
		switch( data_order ){
		case E_PWM_OFF_PULSE_LENGTH:	
			u2a_ret_data = PWM_OFF_PULSE_LENGTH;
			break;
		case E_BREAK_OFF_PULSE_LENGTH:
			u2a_ret_data = BREAK_OFF_PULSE_LENGTH;
			break;
		case E_BREAK_ON_PULSE_LENGTH:
			u2a_ret_data = BREAK_ON_PULSE_LENGTH;
			break;
		case E_BREAK_MAX_PULSE_LENGTH:
			u2a_ret_data = BREAK_MAX_PULSE_LENGTH;
			break;
		case E_D_BREAK_3_LEVEL:
			u2a_ret_data = D_BREAK_2_4_LEVEL;
			break;
		case E_D_BREAK_MIN_LEVEL:	
			u2a_ret_data = D_BREAK_MIN_LEVEL;
			break;
		case E_PULSE_BREAK_WAIT:		
			u2a_ret_data = PULSE_BREAK_WAIT;
			break;
		case E_PULSE_BREAK_START:	
			u2a_ret_data = PULSE_BREAK_START;
			break;
		case E_TIME_MAX_BREAK_STOP:	
			u2a_ret_data = TIME_MAX_BREAK_STOP;
			break;
		case E_LIMIT_STOP_WAIT_TIME:
			u2a_ret_data = LIMIT_STOP_WAIT_TIME;
			break;
		default:
			break;
		}

	}
	else if( ( u1g_mode == U1G_OPEN_MODE) || ( u1g_mode == U1G_OSIKIRI_OPEN_MODE) ){
		
		switch( data_order ){
		case E_PWM_OFF_PULSE_LENGTH:	
			u2a_ret_data = PWM_OFF_PULSE_LENGTH_OP;
			break;
		case E_BREAK_OFF_PULSE_LENGTH:	
			u2a_ret_data = BREAK_OFF_PULSE_LENGTH_OP;
			break;
		case E_BREAK_ON_PULSE_LENGTH:
			u2a_ret_data = BREAK_ON_PULSE_LENGTH_OP;
			break;
		case E_BREAK_MAX_PULSE_LENGTH:	
			u2a_ret_data = BREAK_MAX_PULSE_LENGTH_OP;
			break;
		case E_D_BREAK_3_LEVEL:		
			u2a_ret_data = D_BREAK_2_4_LEVEL_OP;
			break;
		case E_D_BREAK_MIN_LEVEL:	
			u2a_ret_data = D_BREAK_MIN_LEVEL_OP;
			break;
		case E_PULSE_BREAK_WAIT:		
			u2a_ret_data = PULSE_BREAK_WAIT_OP;
			break;
		case E_PULSE_BREAK_START:	
			u2a_ret_data = PULSE_BREAK_START_OP;
			break;
		case E_TIME_MAX_BREAK_STOP:		
			u2a_ret_data = TIME_MAX_BREAK_STOP_OP;
			break;
		case E_LIMIT_STOP_WAIT_TIME:	
			u2a_ret_data = LIMIT_STOP_WAIT_TIME_OP;
			break;
		default:
			break;
		}
	}
	else{}
	return u2a_ret_data;
}
