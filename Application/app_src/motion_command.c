#include "Sys.h"
#include "variables.h"
#include "constants.h"
#include "functions.h"
#include <string.h>
#include <stdlib.h>

u2 motion_break(void)
{
	u1 u1a_temp_status = 0;
	
	u1a_temp_status = 0;
	Fg_soft_start_f = 0;

	switch( u1g_step_motion ){
		case 0:
			if(Fg_cw == 1){
				if(Fg_ccw == 0){
					open_end_port_set();
				}
				else{
					break_port_set();
				}
			}
			else if(Fg_ccw == 1){
				if(Fg_cw == 0){
					close_end_port_set();
				}
				else{
					break_port_set();
				}
			}
			else{
				break_port_set();
			}
			
			wait_motion_start();
			u1g_step_motion++;
			break;
		
		case 1:
			u2g_wait_motion_time_1ms = TIME_MOTION_END;
			u2g_wait_motion_time_1sec = 0;
			u1a_temp_status = wait_motion_check();
			if( u1a_temp_status != 0 ){
				u2g_c_interval_plus = 0x0000;
				u1g_step_motion++;
			}
			else{}
			break;

		case 2:
			break_port_set();
///* 			wait_motion_time = timer; */
			wait_motion_start();
			u1g_step_motion++;
			break;
		
		case 3:
			u1a_temp_status = wait_motion_check();
			if( u1a_temp_status != 0 ){
				u2g_c_interval_plus = 0x0000;
				return 1;
			}
			else{}
			break;

		default:
			u1g_step_motion = 0;
			break;
	}
	
	u2g_c_interval_plus = 0x0000;
		
	return 0;
}

u1 motion_stop(void)
{
	u1 u1a_temp_status = 0;
	
	u1a_temp_status = 0;
	Fg_soft_start_f = 0;

	switch( u1g_step_motion ){
		case 0:
			stop_port_set();
///* 			wait_motion_time = timer; */
			wait_motion_start();
			u1g_step_motion++;
			break;
			
		case 1:
			u1a_temp_status = wait_motion_check();
			if( u1a_temp_status != 0 ){
				u2g_c_interval_plus = 0x0000;
				return 0;
			}
			else{}
			break;
		
		default:
			u1g_step_motion = 0;
			break;
	}
		
	u2g_c_interval_plus = 0x0000;
		
	return 0;
}

u1 motion_open_startup(void)
{
	u1 u1a_temp_status = 0;
	
	u1a_temp_status = 0;
	Fg_soft_start_f = 0;

	switch( u1g_step_motion ){
		case 0:
			open_startup_port_set();
///* 			wait_motion_time = timer; */
			wait_motion_start();
			u1g_step_motion++;
			break;
		
		case 1:
			u1a_temp_status = wait_motion_check();
			if( u1a_temp_status != 0 ){
///* 				u1g_d_mv = 0; */
				u2g_c_interval_plus = 0x0000;
				return 1;
			}
			else{}
			break;

		default:
			u1g_step_motion = 0;
			break;
	}
		
	u2g_c_interval_plus = 0x0000;
		
	return 0;
}


u1 motion_soft_open(void)
{
	u1 u1a_temp_status = 0;
	
	u1a_temp_status = 0;
	Fg_soft_start_f = 1;
	
	switch( u1g_step_motion ){
		case 0:
			soft_open_port_set();
///* 			wait_motion_time = timer; */
			wait_motion_start();
			u1g_step_motion++;
			break;
		
		case 1:
			u1a_temp_status = wait_motion_check();
			if( u1a_temp_status != 0 ){
//				u2g_c_interval_plus = 0x0000;
				return 1;
			}
			else{}
			break;
		
		default:
			u1g_step_motion = 0;
			break;
	}
	return 0;
}

u1 motion_open(void)
{
	u1 u1a_temp_status = 0;
	
	u1a_temp_status = 0;
	Fg_soft_start_f = 0;

	switch( u1g_step_motion ){
		case 0:
			open_port_set();
///* 			wait_motion_time = timer; */
			wait_motion_start();
			u1g_step_motion++;
			break;
		
		case 1:
			u1a_temp_status = wait_motion_check();
			if( u1a_temp_status != 0 ){
///* 				u1g_total_timer_input = 1; */
				return 1;
			}
			else{}
			break;
		
		default:
			u1g_step_motion = 0;
			break;
	}
	return 0;
}


u1 motion_close_startup(void)
{
	u1 u1a_temp_status = 0;
	
	u1a_temp_status = 0;
	Fg_soft_start_f = 0;

	switch( u1g_step_motion ){
		case 0:
			close_startup_port_set();
///* 			wait_motion_time = timer; */
			wait_motion_start();
			u1g_step_motion++;
			break;
		
		case 1:
			u1a_temp_status = wait_motion_check();
			if( u1a_temp_status != 0 ){
///* 				u1g_d_mv = 0; */
				u2g_c_interval_plus = 0x0000;
				return 1;
			}
			else{}
			break;
			
		default:
			u1g_step_motion = 0;
			break;
	}
		
	u2g_c_interval_plus = 0x0000;
		
	return 0;
}

u1 motion_soft_close(void)
{
	u1 u1a_temp_status = 0;
	
	u1a_temp_status = 0;
	Fg_soft_start_f = 1;

	switch( u1g_step_motion ){
		case 0:
			soft_close_port_set();
///* 			wait_motion_time = timer; */
			wait_motion_start();
			u1g_step_motion++;
			break;
		
		case 1:
			u1a_temp_status = wait_motion_check();
			if( u1a_temp_status != 0 ){
//				u2g_c_interval_plus = 0x0000;
				return 1;
			}
			else{}
			break;
			
		default:
			u1g_step_motion = 0;
			break;
	}
	return 0;
}

u1 motion_close(void)
{
	u1 u1a_temp_status = 0;
	
	u1a_temp_status = 0;
	Fg_soft_start_f = 0;

	switch( u1g_step_motion ){
		case 0:
			close_port_set();
///* 			wait_motion_time = timer; */
			wait_motion_start();
			u1g_step_motion++;
			break;
		
		case 1:
			u1a_temp_status = wait_motion_check();
			if( u1a_temp_status != 0 ){
///* 				u1g_total_timer_input = 1; */
				return 1;
			}
			else{}
			break;
		
		default:
			u1g_step_motion = 0;
			break;
	}
	return 0;
}

u1 motion_shortbreak(void)
{
	u1 u1a_temp_status = 0;
	
	u1a_temp_status = 0;
	Fg_soft_start_f = 0;
	u2g_c_interval_plus = 0x0000;

	switch( u1g_step_motion ){
		case 0:
			break_port_set();
			wait_motion_start();
			u1g_step_motion++;
			break;
			
		case 1:
			u1a_temp_status = wait_motion_check();
			if( u1a_temp_status != 0 ){
//                return 0;
			}
			else{}
			break;
		
		default:
			u1g_step_motion = 0;
			break;
	}
	return 0;
}




void wait_motion_start(void)
{
	u2g_systimer_1ms_wait_motion = 0;
	u2g_systimer_1sec_wait_motion = 0;
}

u1 wait_motion_check(void)
{
	if( u2g_systimer_1ms_wait_motion >= u2g_wait_motion_time_1ms){
		if( u2g_systimer_1sec_wait_motion >= u2g_wait_motion_time_1sec){
			return 1;
		}
		else{
			return 0;
		}
	}
	else{
		return 0;
	}
}

void open_end_port_set(void)
{
	Fg_pwm_out = 0;
	Fg_pump_out = 1;
	Fg_cw = 1;
	Fg_ccw = 0;
}

void close_end_port_set(void)
{
	Fg_pwm_out = 0;
	Fg_pump_out = 1;
	Fg_cw = 0;
	Fg_ccw = 1;
}

void break_port_set(void)
{
	Fg_pwm_out = 0;
	Fg_pump_out = 1;
	Fg_cw = 0;
	Fg_ccw = 0;
}

void stop_port_set(void)
{
	Fg_pwm_out = 0;
	Fg_pump_out = 0;
	Fg_cw = 0;
	Fg_ccw = 0;
}

void open_startup_port_set(void)
{
	Fg_pwm_out = 0;
	Fg_pump_out = 1;
	Fg_cw = 1;
	Fg_ccw = 0;
}

void soft_open_port_set(void)
{
	Fg_pwm_out = 1;
	Fg_pump_out = 1;
	Fg_cw = 1;
	Fg_ccw = 0;
}

void open_port_set(void)
{
	Fg_pwm_out = 1;
	Fg_pump_out = 1;
	Fg_cw = 1;
	Fg_ccw = 0;
}

void close_startup_port_set(void)
{
	Fg_pwm_out = 0;
	Fg_pump_out = 1;
	Fg_cw = 0;
	Fg_ccw = 1;
}

void soft_close_port_set(void)
{
	Fg_pwm_out = 1;
	Fg_pump_out = 1;
	Fg_cw = 0;
	Fg_ccw = 1;
}

void close_port_set(void)
{
	Fg_pwm_out = 1;
	Fg_pump_out = 1;
	Fg_cw = 0;
	Fg_ccw = 1;
}
