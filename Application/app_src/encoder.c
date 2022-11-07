#include "Sys.h"
#include "Timer.h"
#include "variables.h"
#include "constants.h"
#include "functions.h"
#include "Gpio.h"
#include "input_encoder.h"
#include "a_data_exchange.h"

//#include "serial_transmission.h"
#include <string.h>
#include <stdlib.h>
#include "tst_break.h"
#include "anjou_test.h"

u2 u2g_d_rpm_current = 0;	
s4 s4g_d_mv = 0;
u4 u4g_plus_length = 0;		
u1 u1g_counter_minus = 0;

static u1 u1l_rev_pwm_f = 0;	
static u4 u4l_high_length = 0;
static u4 u4l_low_length = 0;

u1 u1g_kirikae = 0;
u1 u1a_fg_current_pulse_over_flow = 0;
static void change_pulse_width_to_rpm(void); 
static void check_abnormal_pulse(void);
static void set_pwm_d(void);
static void plus_operate_main(void);
static void ope_pulse_count_main(void);
static void ope_add_p_c(void);
static void ope_redu_p_c(void);
static void zene_pulse_count(void);
static void move_num_cont(void);
static void p_in_motor_stop(void);
static void no_direct_p_in(void);

void int_input_encoder(void){
    
	if( (u4g_plus_length_buffer <= TOO_S_PULSE_LENGTH) && (u1a_fg_current_pulse_over_flow == 0) ){

	}
	else{
		if( P_ENCODER_A == 1 ){
			if( u1a_fg_current_pulse_over_flow == 0){
				u4l_high_length = u4g_plus_length_buffer;
			}
			else{
				u4l_high_length = 0xfffffffe;
			}
			/* if( u1a_fg_imfb_in == 1 ){ */
				u1g_f_input_pulse = 1;
				ope_pulse_count_main();			
				u2g_c_interval_plus = 0x0000;
				Fg_final_state = P_ENCODER_B;         
			/* } */
			/* else{}	 */

			if( (U4L_VALUE_FFFF - u4l_low_length) < u4l_high_length ){	
				u4g_plus_length = U4L_VALUE_FFFF;
			}else{
				u4g_plus_length  = (u4)u4l_low_length + (u4)u4l_high_length;
			}
			check_abnormal_pulse();
            u4l_low_length = 0;
			u4l_high_length = 0;
            
			change_pulse_width_to_rpm();          
		}
		else{
			if( u1a_fg_current_pulse_over_flow == 0){
				u4l_low_length = u4g_plus_length_buffer;
				Fg_mid_state = P_ENCODER_B;	              
			}
			else{
				u4l_low_length = 0xfffffffe;
				Fg_mid_state = P_ENCODER_B;
			}
		}
	}

}

static void check_abnormal_pulse(void)
{
	
	if(u4g_plus_length < ABNORMAL_PLUS_LENGTH){
		if(u1g_count_abnormal_speed_pulse < 255){
			u1g_count_abnormal_speed_pulse++;
		}
		else{}
	}
	else{
		if(u1g_count_abnormal_speed_pulse > BOUSOU_LONG_NOISE_PENA){
			u1g_count_abnormal_speed_pulse = (u1)(u1g_count_abnormal_speed_pulse - BOUSOU_LONG_NOISE_PENA);
		}
		else{
			u1g_count_abnormal_speed_pulse = 0;
		}
	}
}



void pulse_in_operation(void){
// 	ope_pulse_count_main();		
	p_in_motor_stop();			
	state_output_ope();			
	Fg_f_pwm_req = 1;				
	if( u1g_ope_state_f == 1 )		
		{
			plus_operate_main();
/* 			set_pwm_d(); */
		}
	else
		{
/* 			u2g_p_differ[1] = 0x00; */
/* 			u2g_p_differ[0] = 0x00; */
		}
}

void set_d_pwm (void){

	if( (u1g_ope_state_f == 0x1) && (Fg_pwm_out == 1)){
		if(Fg_f_pwm_req == 1 ){
			Fg_f_pwm_req = 0;						
			u2g_c_interval_plus = 0x0000;		
		}
		else{
			if( Fg_soft_start_f == 0x01){
//		u1g_rev_pwm_f = U1_SPEED_BEST;		
				if( u2g_c_interval_plus >= TH_S_START_ADD_1 ){
					if( u1g_c_no_plus >= TH_S_START_ADD_2 ){
						u1g_c_no_plus = 0x00;
						u1l_rev_pwm_f = U1_SPEED_UP;
						s4g_d_mv = SOFT_START_20MS_MORE_DUTY;
					}
					else{}
				}
				else{}
			}
			else{
////				u1l_rev_pwm_f = U1_SPEED_BEST;
				if( u2g_c_interval_plus >= TH_N_SPEED_ADD_1){
					if( u1g_c_no_plus >= TH_N_SPEED_ADD_2 ){
				  /*0x10*/
						u1g_c_no_plus = 0x00;
						u1l_rev_pwm_f = U1_SPEED_UP;

//		//				if( u2g_c_interval_plus <= 0x000a){
//							//Meaningless statement 警告につきコメントアウト
//							// u2g_d_mv += 0x00 ;
//		//				}
//		//				else{
//		//					if( u2g_c_interval_plus <= 0x000c){
//		//						s4g_d_mv = 0x01;   /*0x01*/
//		//					}
//		//					else{
								s4g_d_mv = NORMAL_28MS_MORE_DUTY;	/* 109 + 50 = 159 check_encoder_duty_stop_cancel()で加算している */
		//					}
		//				}

					}
					else{}
				}
				else{}
			}
///* 			set_pwm_d(); */
///* 			u1g_rev_pwm_f = U1_SPEED_BEST; */
		}
		set_pwm_d();
	}
	
	else{
	}
}

static void set_pwm_d(void)
{
	s4 s4l_t_d_pwm = 0;
	u2 u2a_d_pwm_max_limit = 0;
	u2 u2a_d_pwm_max_limit_temp = 0;
	s4l_t_d_pwm = 0;
	
	s4l_t_d_pwm = (s4)(u2g_d_pwm) + (s4)(s4g_d_mv);
	
	if( u1g_Fg_soft_lock_out_duty == 0){
		u2a_d_pwm_max_limit = D_PWM_MAX_NORMAL;
	}
	else{
		u2a_d_pwm_max_limit = D_PWM_MAX_SOFT_LOCK;	
	}
	
	if(u2a_d_pwm_max_limit > 1){	
		u2a_d_pwm_max_limit_temp = u2a_d_pwm_max_limit - 1;
	}else{
		u2a_d_pwm_max_limit_temp = 0;
	}
	
	if( s4l_t_d_pwm >= (s4)u2a_d_pwm_max_limit_temp){

		u2g_d_pwm = u2a_d_pwm_max_limit;
	}
	else if( s4l_t_d_pwm <= D_PWM_MIN ){

		u2g_d_pwm = D_PWM_MIN;
	}
	else{
		if( u1g_Fg_pwm_off_for_break == 0){	
			u2g_d_pwm = (u2)s4l_t_d_pwm;
		}
	}
//	//s4g_d_mv = 0;
}

static void plus_operate_main(void){
			
	static s4 s4l_d_mv_buffer = 0;
	static s4 s4l_d_mv_buffer2 = 0;
	static s4 s4l_culc_unit1 = 0;			
	static s4 s4l_culc_unit2 = 0;			
	static u1 Fg_before_count = 0;

	static s2 s2l_p_differ_before = 0;
                               
	s2g_p_differ_current = (s2)(u2g_standard_plus_length) - (s2)(u2g_d_rpm_current);

	if( s2g_p_differ_current < 0 ){
		u1l_rev_pwm_f = U1_SPEED_DOWN;
	}
	else if( s2g_p_differ_current > 0 ){
		u1l_rev_pwm_f = U1_SPEED_UP;//1
	}
	else{
		u1l_rev_pwm_f = U1_SPEED_BEST;
	}       
                                                                  
	s4l_culc_unit1 = (s4)( (s4)( s2g_p_differ_current - s2l_p_differ_before ) * KP ) ;
    
        
	s4l_culc_unit2 = (s4)( (s4)s2g_p_differ_current * KI );	
    
                                              
	s4l_d_mv_buffer = (s4)( (s4l_culc_unit1 + s4l_culc_unit2) / KETA_10 );
	
                                                       
	if( ( s4l_d_mv_buffer < 0 ) && ( s4l_d_mv_buffer > UNIT1_UNIT2_DATA_MINUS_100 ) ){
		
		if( Fg_before_count == 1){
			u1g_counter_minus ++;
			Fg_before_count = 1;       
			if( u1g_counter_minus > UNIT1_UNIT2_DATA_PLS_25 ){
				s4l_culc_unit1 = UNIT1_UNIT2_DATA_MINUS_1000;//-1000
				s4l_culc_unit2 = 0;
				u1g_counter_minus = 0;
			}	
			else{}
		}
		else{
			u1g_counter_minus ++;
			Fg_before_count = 1;
		}
	}
	else{	
		Fg_before_count = 0;
		u1g_counter_minus = 0;
		
	}
                                                                //100
	s4l_d_mv_buffer = (s4)( (s4l_culc_unit1 + s4l_culc_unit2) / KETA_100 );	
    
                           
	s4l_d_mv_buffer2 = (s4)(D_PWM_DUTY_100 * (s4)s4l_d_mv_buffer);
    
                                                                    //100
	s4g_d_mv = (s4)((s4l_d_mv_buffer2 + s4g_d_mv_loss_number) / (s4)KETA_100);
    
                                                                    //100
	s4g_d_mv_loss_number = s4l_d_mv_buffer2 - (s4)((s4)s4g_d_mv * (s4)KETA_100);

	s2l_p_differ_before = s2g_p_differ_current;

	if( ( u2g_d_rpm_current >= u2g_standard_plus_length )  ){
			
		Fg_soft_start_f = 0;
	}	
	else{}

	if( Fg_soft_start_f == 1){
		if( u1l_rev_pwm_f == U1_SPEED_DOWN ){
		}
		else{	/* SPEED UP OR BEST */
			s4g_d_mv = (s4)SOFT_START_20MS_LESS_DUTY;//18
		}
		s2l_p_differ_before = 0;
	}
	else{}
	
	if( s4g_d_mv > MAX_CHANGE){//130
		s4g_d_mv = MAX_CHANGE;
	}
	else if( s4g_d_mv < MIN_CHANGE){//-130
		s4g_d_mv = MIN_CHANGE;
	}
	else{}
}

static void ope_pulse_count_main(void){
	if( (u4g_plus_length_buffer <= HIGHT_SPEED_P)&&
		(u1g_mode == U1G_STOP_MODE) )
		{
			if( Fg_f_direction_p == 0 )
				{
					ope_redu_p_c();
				}
			else
				{
					ope_add_p_c();
				}
		}
	else
		{
			zene_pulse_count();	
		}
}

static void p_in_motor_stop(void){
	if( (u1g_mode == U1G_STOP_MODE)||(u1g_ope_state_f >= 2) )
		{
			if( u2g_c_hand_move <= HAND_ERROR )
				{
					u2g_c_hand_move++;
					if( u2g_c_hand_move == HAND_ERROR )	
						{
							u2g_c_hand_move = HAND_ERROR + 2;
							u1g_error_mode = ERR_HAND_MOVE;		
							
							a_vog_error_status_store(u1g_current_mode,u1g_signal,u1g_n_section);
						}
					else{}
				}
			else{}
		
			if( Fg_f_upper_start == 1 )
				{
					if( (s2g_cnt_plus >= (s2)(U2L_JOUGEN_KITEI_AREA))||
						(s2g_cnt_plus <= (s2)(0 - U2L_JOUGEN_KITEI_AREA)) )
						{
							Fg_f_upper_start = 0;
							if(Fg_f_upper_huka == 0)
								{
									Fg_f_no_position = 1;
								}
							else{}
						}
					else{}
				}
			else{}
		}
	else
		{
			u2g_c_hand_move = 0;
		}
}

void state_output_ope(void){
	if( u1g_ope_state_f <= 1 )
		{
			move_num_cont();					
#if 0

			if( Fg_f_fst_close == 0 )
				{
					u1g_c_short_close_p++;
					if( u1g_c_short_close_p >= C_SHORT_CLOSE )
						{
							u1g_c_short_close_p = C_SHORT_CLOSE;
						}
				}
			if( Fg_f_over_xms == 1 )
				{
					u1g_cnt_short_open_p++;
					if( u1g_cnt_short_open_p >= REV_SHORT_PULSE )
						{
							u1g_cnt_short_open_p = REV_SHORT_PULSE;
						}
				}
#endif
		}
	else{}
}

static void ope_add_p_c(void){
	if( s2g_cnt_plus <= (s2)0x7ffe )
		{
			s2g_cnt_plus++;
			if( s2g_unknown_cnt_plus <= (s2)0x7ffe ){
				s2g_unknown_cnt_plus++;
			}
			else{}
		}
	else{}
	if( Fg_f_no_position == 1 )
		{
			if( u1g_mode == U1G_STOP_MODE )
				{
					if( Fg_f_close_mukou == 0 )
						{
//						s2g_cnt_plus = 0x00;
						}
					else
						{
							if( s2g_kari_size_ram < s2g_cnt_plus )
								{
									s2g_kari_size_ram = s2g_cnt_plus - 0x01;
								}
							else{}
						}
				}
			else{}
		}
	else{}
}

static void ope_redu_p_c(void){
//	if( s2g_cnt_plus >= (s2)0x8001 )
	if( s2g_cnt_plus >= (s2)(-32177) )
		{
			s2g_cnt_plus--;
			if( s2g_unknown_cnt_plus >= (s2)-32177 ){
				s2g_unknown_cnt_plus--;
			}
			else{}
		}
	else{}
	if( s2g_cnt_p_trq_test >= (s2)(-32177) )
		{

			if( (U2L_RPM_MIN_PULSE_INPUT <= u2g_d_rpm_current) && (u2g_d_rpm_current <= U2L_RPM_MAX_PULSE_INPUT) ){
				s2g_cnt_p_trq_test--;
			}
			else{}
		}
	else{}
#if 0
	if( (s2g_cnt_plus == U2L_JOUGEN_KITEI_AREA)&&(u1g_mode == U1G_OPEN_MODE) )
	{
		if( u1g_ope_state_f == 1 )
			{
				Fg_f_ene_sepablo = 1;
			}
	}
#endif
}


static void zene_pulse_count(void){

	if( Fg_mid_state == Fg_final_state )
		{
			no_direct_p_in();			
		}
	else if( Fg_final_state == P_DIRECTION )//close
		{
			Fg_f_direction_p = 1;			
			ope_add_p_c();					
			u1g_c_move_m_p = 0x00;			
		}
	else    //open
		{
			Fg_f_direction_p = 0;		
			ope_redu_p_c();				
			u1g_c_move_m_p = 0x00;			
		}
}


static void move_num_cont(void){
	
	if( Fg_f_move_consist != 1 )		
		{
			u2g_c_move_consist++;
			if( u2g_c_move_consist >= CONST_MOVE )		
				{
					Fg_f_move_consist = 1;		
					if( u2g_num_move <= (u2)0xfffe )
						{
							u2g_num_move++;		
							if( (u2g_num_move & 0x000f) == 0x000f )
								{
									u1g_flash_write_status = U1_ERROR_1_WRITE;
								}
							else{}
						}
					else
						{
							u2g_num_move = 0x0000;
						}
				}
			else{}
		}
	else{}
}

static void no_direct_p_in(void){
	
	if( u1g_ope_state_f == 1 )					
		{
			u1g_c_move_m_p++;					
			if( u1g_c_move_m_p >= 0x24 )		
				{
					s2g_cnt_plus = 0x00;
					u1g_c_move_m_p = 0x00;		
					Fg_f_no_position = 1;	
					Fg_f_upper_start = 0;	
					Fg_lock_sw = 0;			
					ope_key_stop();			
					Fg_key_stop_only = 0;
					u1g_key_open_only = 0;
					u1g_key_close_only = 0;
					Fg_osikiri_open = 0;
					Fg_osikiri_close = 0;
					kagen_reset();
					Fg_f_close_mukou = 0;
					
					u1g_encoder_B_no_pulse = 1;	
					u1g_huka_ad_value = (u1)u2g_ad_now[(CURR - CURR)]/4;
				}
			else{}
				
		}
	else
		{
			u2g_cnt_no_dire_p++;						
			if( u2g_cnt_no_dire_p >= STOP_ERROR_PULSE )	
				{
					s2g_cnt_plus = 0x00;
					u2g_cnt_no_dire_p = 0x00;
					Fg_f_no_position = 1;		
					Fg_f_upper_start = 0;		
					Fg_lock_sw = 0;				
					Fg_key_stop_only = 0;
					u1g_key_open_only = 0;
					u1g_key_close_only = 0;
					Fg_osikiri_open = 0;
					Fg_osikiri_close = 0;
					kagen_reset();
					Fg_f_close_mukou = 0;
					
					u1g_encoder_B_no_pulse = 1;	
					u1g_huka_ad_value = (u1)u2g_ad_now[(CURR - CURR)]/4;
				}
			else{}
		}
}

void kagen_reset(void){

	Fg_f_no_position = 1;
	Fg_f_upper_huka = 0;
}

void  sw_in_end(void)
{
		reset_system_timer();
		Fg_f_over_xms = 0;			
}


void pulse_interval_check(void){
	if( u2g_c_interval_plus >= 0x0014 )			
		{
			Fg_f_dis_pwm = 0;		
		}
	else{}
	
	check_encoder_duty_stop_cancel();				
	
	if(u2g_c_interval_plus >= TOO_L_PLS_LEN )
		{
			if( u2g_ad_now[(CURR - CURR)] <= THERMAL_A ){
				u1g_thermal_input = 1;
			}
			else{
				u1g_encoder_A_no_pulse = 1;
				u1g_huka_ad_value = (u1)u2g_ad_now[(CURR - CURR)]/4;
			}	
			
			ope_key_stop();					
			Fg_key_stop_only = 0;
			u1g_key_open_only = 0;
			u1g_key_close_only = 0;
			Fg_f_no_position = 1;			
		
			kagen_reset();		
			Fg_f_close_mukou = 0;
	
			s2g_cnt_plus = 0x00;
		}
	else{}
}


//u1 cnt = 0;
static void change_pulse_width_to_rpm(void){
			
	u4 u4a_d_rpm_buffer = 0;
	
	u4a_d_rpm_buffer = 0;

	u4a_d_rpm_buffer = (u4)u4g_plus_length;
	u4a_d_rpm_buffer = (u4)((u4)PW_TO_RPM / u4a_d_rpm_buffer);//PW_TO_RPM
	u2g_d_rpm_current = (u2)u4a_d_rpm_buffer;		 /* rpm */
}
