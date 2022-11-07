#include "Sys.h"
#include "constants.h"
#include "variables.h"

/*******	in main.c		**********/
u1	u1g_current_mode = 0;	
u1	u1g_previous_mode = 0;	
u1	u1g_pre_mode = 0;		
s2	s2g_cnt_plus_start = 0;		
s2	s2g_cnt_plus_start_for_stop = 0;		
u1	u1g_signal = 0;		
u1	u1g_kamen_total_input = 0;		
u1 	u1g_pass_route_next_signal = 0;
u1 	u1g_Fg_close_huka_learn = 0;

u1	u1g_different_mode = 0;		
u1	u1g_step = 0;			

u1	u1g_full_open_input = 0;
u1	u1g_jougen_kitei_area_input = 0;
u1	pulse_35mm_input = 0;

u1	u1g_temp_hosei = 0;
u1	u1g_temp_b_f_p_hugo = 0;		

u2	u2g_max_const_huka_hosei = 0;
u2	u2g_open_std_max_huka_hosei = 0;
u2	u2g_osikomi_const_huka_hosei = 0;	
u2	u2g_open_std_osikomi_huka_hosei = 0;	

u1	u1g_Fg_break_enable_counter = 0;
u1	u1g_Fg_break_enable_time = 0;
u1	u1g_fg_power_on = 0;

TYPE_REQ_UART_ERR req_uart_err = {0};		
/******* 	in motion_commands.c   		**********/
u1	u1g_step_motion = 0;
u2	u2g_wait_motion_time_1ms = 0;
u2	u2g_wait_motion_time_1sec = 0;
u2	u2g_systimer_1ms_wait_motion = 0;
u2	u2g_systimer_1sec_wait_motion = 0;
u2	u2g_systimer_1ms_sol_out = 0;		

/******* 	in mode_process.c   		**********/
u1	u1g_shutter_state = 0;
u1	u1g_threshold_huka = 0;	


u1 u1g_key_open_only = 0;
u1 u1g_key_close_only = 0;
u1 u1g_key_3sw = 0;
//u1 u1g_save_all_data;
u1 u1g_key_3sw_huka_reset = 0;
u1 u1g_key_3sw_jougen = 0;				
u1 u1g_2ope_3ope_signal = 0;

u1 fg_no_answer = 0;
u1 u1g_f_any_key_input = 0;			

/***********	in overload.c		 **********/
u1 	u1g_kahuka_input = 0;
u1 	u1g_previous_kahuka_input = 0;
u1 	u1g_bousou_input = 0;
u2 	u2g_learn_max_huka = 0;
u2 u2g_close_2ji_kamen = 0;
u2 u2g_close_1ji_kamen = 0;
u1 u1g_close_const_kamen = 0;
u1 u1g_limit_ad = 0;					

u2 	u2g_ad_buffer0_temp = 0;
u2 	u2g_ad_buffer_temp = 0;

u1 u1g_temp_hosei_buffer = 0;				
u4 u4g_now_ver = 0;							
s1 s2g_temp_now_signed = 0;
u1 u1g_cold_temp_hosei = 0;

u2  u2g_ad_now[ad_swnum] = {0};	//0 curr/1 ver/ 2 temp			
u1 u1g_ad_ref[ad_swnum] = {0};				
u2 u2g_now_data = 0;						
u2 u2g_raw_q[ad_swnum][4] = {0};				
u1 u1g_curr_num = 0;
u1 u1g_ver_num = 0;
u1 u1g_temp_num = 0;
u1 u1g_f_limit_average = 0;
u1 u1g_limittime = 0;

u1 u1g_Fg_ecu_temp_ad_error = 0;		
u1 u1g_Fg_temp_ad_error = 0;			
u1 u1g_Fg_ecu_ver_ad_error = 0;			
u1 u1g_Fg_ver_ad_error = 0;				

/******		in encoder.c   		**********/
u1 u1g_encoder_A_no_pulse = 0;
u1 u1g_encoder_B_no_pulse = 0;

u1 u1g_thermal_input = 0;
u1 u1g_count_abnormal_speed_pulse = 0;

/******  	in system_timer		**********/
u2	u2g_systimer_1ms_for_signal = 0;				
u2	u2g_systimer_1sec_for_signal = 0;			
u1	u1g_total_timer_input = 0;					
u1	u1g_timer_kahuka_loose_input = 0;			
u1  	u1g_timer_2sec_input = 0;				
u1	u1g_timer_5sec_input = 0;				
u1	u1g_soft_lock_error_5sec_input = 0;


/********* 	in flash_data_read.c	**********/

u1 	u1g_fg_wait_format_complete = 0;
u1 u1g_fg_wait_write_complete = 0;

TYPE_WORD u2g_fg_control_structure = {0};

s4 s4g_d_mv_loss_number = 0;
u1 u1g_f_reset_after_write = 0;
u2 u2g_c_main = 0;
u1 u1g_fg_set_h_size_end = 0;
u1 u1g_c_noservice = 0;
u1 u1g_f_active_format = 0;

u1 u1g_fg_data_erase = 0;					
u1 u1g_fg_block_format = 0;					
u1 u1g_fg_data_read = 0;						
u1 u1g_fg_flash_initial = 0;					

TYPE_ERROR_1 xn_error_set1 = {0};					
TYPE_ERROR_1 xn_error_set0 = {0};		

TYPE_FLASH_LEARN_BODY xng_learned_huka_data = {0};
TYPE_FLASH_ERROR_BODY_1 xng_error_data = {0};	
TYPE_FLASH_ERROR_BODY_2 xng_error_20_data = {0};
TYPE_FLASH_HSIZE_BODY xng_Hsize_series = {0};
TYPE_FLASH_FACT_BODY xng_record_fact = {0};

TYPE_FLASH_LEARN_UNIT xng_flash_learned_hukadata = {0};	
TYPE_FLASH_ERROR_UNIT xng_flash_error_data = {0};		
TYPE_FLASH_ERROR_2_UNIT xng_flash_error_20_data = {0};	
TYPE_FLASH_HSIZE_UNIT xng_flash_Hsize_series = {0};
TYPE_FLASH_FACT_UNIT xng_flash_fact_series = {0};	
FLASH_STU Flash_Write[5] = {0};
u1 flash_write_cmd = 0;

u2 u2g_soft_clear_timer_counter = 0;		

u1 u1g_fg_read_retry = 0;				

u2 u2g_raw_data[NUM_CAPTURE_DATA] = {0};			
u2 u2g_check_temp_ad_data[10] = {0};//NUM_AD_CHECK_DATA
u2 u2g_check_ver_ad_data[10] = {0};

s1 s1g_temp_v = 0;						

u1 u1g_f_timeover_anjo_test = 0;				

u1 u1g_section_kahuka_occured = 0;			

u1 u1g_flash_write_status = 0;	

u1 u1g_huka_ad_value = 0;					

u1 u1g_Fg_previous_kahuka_upper = 0;			
s2 s2g_previous_kahuka_position = 0;			


/******		in access_flash.c	*********/
u1 	u1g_check_sum_learn = 0;
u1 	u1g_check_sum_size = 0;
u1 	u1g_cnt_e2prom_write = 0;				
u1 	u1g_error_mode = 0;					
u1	u1g_Fg_error_mode_3_write_check = 0;
u1	u1g_Fg_power_on = 0;		

u1 	 u1g_c_short_close_p = 0;				

u2 u2g_learn_buffer = 0;					
u2 u2g_learn_buffer_close = 0;				
u2 u2g_std_huka = 0;					
u2 u2g_std_learn = 0;					
u2 u2g_max_learn_b = 0;					
u2 u2g_copy_max_learn_b[(MAX_SECTION + 1)] = {0};	
u2 u2g_open_std_learn = 0;

u1 u1g_ad_num = 0;							
u1 u1g_ad_num_temp = 0;
u2 u2g_max_huka = 0;						
u2 u2g_nor_huka = 0;						
u1 u1g_c_kahuka = 0;						
						
u2 u2g_p_differ[2] = {0};					
u4 u4g_plus_length_buffer = 0;				

u1 u1g_c_no_plus = 0;						
u2 u2g_c_interval_plus = 0;						
u2 u2g_d_pwm = 0;							
s2 s2g_p_differ_current = 0;	

u1 u1g_sw[sw_num] = {0};						
u1 u1g_last_sw[sw_num] = {0};					
u1 u1g_c_sw_off[sw_num] = {0};				
u1 u1g_c_sw_on[sw_num] = {0};					
u1 u1g_cnt_no_in = 0;					
u1 u1g_count_timer_1ms = 0;					

u1 u1g_cnt_thermal = 0;					
s2 s2g_cnt_plus = 0;					
s2 s2g_unknown_cnt_plus = 0;			
s2 s2g_cnt_p_trq_test = 0;				
s2 s2g_cnt_plus_jougen = 0;					

s2 	s2g_size_ram[6] = {0};					
													
s2 s2g_lock_start_position = 0;												
u1 u1g_Fg_hand_close_plus = 0;
													
s2 s2g_kari_size_ram = 0;						
u2 u2g_over_lev_b[(MAX_SECTION + 1)][5] = {0};	
u2 u2g_kamen_over_lev_b[5] = {0};				

u1 u1g_n_section = 0;						
u1 u1g_num_section = 0;					
u1 u1g_num_section_kagen = 0;			
u1 u1g_copy_section = 0;				
u1 u1g_Fg_jougen_area = 0;			
u1 u1g_Fg_copy_jougen_area = 0;		
u1 u1g_n_lev = 0;						
u2 u2g_open_over_lev_b[(MAX_SECTION + 1)][5] = {0};	
u2 u2g_kahuka_mirror[FLASH_DATA_SIZE] = {0};			
u2 u2g_cnt_chng_mode = 0;					
u1 u1g_cnt_chng_mode_huka_reset = 0;		
u1 u1g_cnt_chng_mode_startup = 0;			
u1 u1g_b_p_hosei = 0;						
u1 u1g_b_ver_hosei = 0;						
u1 u1g_p_hosei = 0;							
u2 u2g_kei = 0;
u2 u2g_cal_b = 0;
u1 cnt_break_on = 0;						
u1 cnt_break_off = 0;					
u1 cnt_pwm_off = 0;					
u1 cnt_pwm_on = 0;		
u1 cnt_stop = 0;					
u1 u1g_cnt_breakdown = 0;			

u1 w_b_pulse = 0;					
u2 u2g_std_max_huka = 0;				
u1 cnt_soft_start = 0;				
u1 u1g_c_check_out = 0;					
//u1 u1g_error_ram[max_err_data + 1];
u2  u2g_c_move_consist = 0;				
u2  u2g_c_hand_move = 0;		
u1 u1g_thermal_count = 0;	
u1 f_step_error = 0;		

u1 c_wait = 0;		

u2 	u2g_d_mv = 0;
u2 	u2g_huka_jougen = 0;
s2 s2g_imaginary_close_posi = 0;
u1 	u1g_c_move_m_p = 0;		
u2 	u2g_cnt_no_dire_p = 0;	
u1 u1g_cnt_short_open_p = 0;
u1 	u1g_f_input_pulse = 0;	

u1 u1g_motor_speed = 0;
u1 u1g_previous_motor_speed = 0;

u2 u2g_jougen_open_over_lev_b = 0;
u2 u2g_keep_jougen_open_over_lev_b = 0;


u1 u1g_ope0_done = 0;
u1 u1g_sf_set_kagen = 0;
u2 u2g_buf_check_3sw_set_ok = 0;
u1 u1g_cnt_input_key_stop = 0;
u2 u2g_timer_limit_set_kagen = 0;
u1 u1g_signal_read_stop = 0;
u1 u1g_data_H_size_input[32] = {0};
u1 u1g_index_H_size_input = 0;


u1 u1g_stop_counter = 0;


u1	u1g_uart_buzzer_order = 0;			
u2	u2g_systimer_1ms_timer_for_anjou = 0;
u2	u2g_systimer_1sec_timer_for_anjou = 0;
u1	u1g_f_release_elec = 0;					
u1	u1g_f_ok_set_on_shortbreak = 0;			


u2	u2g_systimer_1ms_special_H_size = 0;
u2	u2g_systimer_1sec_special_H_size = 0;


s2	s2g_cnt_plus_speed_down = 0;

u2 u2g_pre_key = 0;
u1 u1g_cnt_set_level = 0;

u1 u1g_temp_previous_mode = 0;				
u1 u1g_temp_signal = 0;						
u1 u1g_temp_free_data = 0;					


TYPE_BYTE	flag1 = {0};						/* multi_purpose frag1 */
TYPE_BYTE	flag2 = {0};						/* multi_purpose frag2 */
TYPE_BYTE	flag3 = {0};						/* multi_purpose frag3 */
TYPE_BYTE	flag4 = {0};						/* multi_purpose frag4 */
TYPE_BYTE	flag5 = {0};						/* multi_purpose frag5 */
TYPE_BYTE	flag6 = {0};						/* multi_purpose frag6 */
TYPE_BYTE	flag7 = {0};						/* multi_purpose frag7 */
TYPE_BYTE	flag8 = {0};						/* multi_purpose frag8 */
TYPE_BYTE	flag9 = {0};						/* multi_purpose frag */
TYPE_BYTE	flag10 = {0};						/* multi_purpose frag */
TYPE_BYTE	flag11 = {0};						/* multi_purpose frag */
TYPE_BYTE	flag12 = {0};						/* multi_purpose frag */
TYPE_NIBLE		nible1 = {0};					/* multi_purpose nible1 */
TYPE_NIBLE		nible2 = {0};					/* multi_purpose nible2 */
TYPE_NIBLE		nible4 = {0};					/* multi_purpose nible4 */
TYPE_NIBLE		nible5 = {0};					/* multi_purpose nible5 */
TYPE_BYTE	swflag = {0};						/* sw_in frag */
TYPE_BYTE	swoffflag = {0};					/* sw_off frag */
TYPE_WORD	swnflag = {0};					/* sw frag */

TYPE_BYTE		outbuffer_ = {0};					/* output buffer */
TYPE_BYTE		ftimer1s_ = {0};						/* 1s flag_field */
TYPE_BYTE		ftimer100ms_ = {0};						/* 100ms flag_field */
TYPE_BYTE		ftimer10ms_ = {0};						/* 10ms flag_field */
TYPE_BYTE		selectsw_ = {0};				/* 4bit select sw  */
TYPE_BYTE		eeprm_buffer_ = {0};
TYPE_WORD		size_ram_ab_ = {0};
TYPE_WORD		size_ram2_ab_ = {0};
TYPE_WORD		temp_now_ = {0};
TYPE_WORD		num_now_ = {0};
TYPE_LONG		num_move_ = {0};

TYPE_BYTE	flag_NK = {0};						/* multi_purpose frag */
TYPE_BYTE	flag_NK_signal = {0};						/* multi_purpose frag */
TYPE_BYTE	flag_learn_open = {0};			/* learn_open frag */

u1 u1g_f_stop_shortopen = {0};					

TYPE_WORD u2g_size_ram_H_size = {0};

//for debug

u2	u2g_max_const_huka = {0};		
u2	u2g_open_std_max_huka = {0};		
u2	u2g_open_std_osikomi_huka = {0};		//5.5Nm
u2	u2g_osikomi_const_huka = {0};			//5.5Nm
u2	u2g_max_const_huka_1000rpm = {0};		
u2	u2g_osikomi_const_huka_540rpm = {0};	

u2 	u2g_standard_plus_length = {0};		

u1 	u1g_fg_next_main_go = {0};
u1 	u1g_timer_3sw_100msec = {0};
u1 	u1g_fg_charge_pump_enable = {0};

u2	u2g_count_tanrak_break_timer = {0}; 		
u1 	u1g_count_90_sec_timer_0_100 = {0}; 	
u2 	u2g_count_90_sec_timer_100_90000 = {0};
u2 	u2g_soft_clear_counter = {0};

u1 	u1g_speed_up_slow_down = {0};


/********* 	in a_control_sol.c	**********/

u1 u1g_f_move_sol = 0;
u1 u1g_f_limit_6min_lock = 0;
u1 u1g_f_limit_5times_lock = 0;
u1 u1g_f_delay_lock = 0;
u1 u1g_f_end_shortbreak = 0;
u1 u1g_f_start_shortbreak = 0;
u1 u1g_f_start_lock_output = 0;
u1 u1g_f_sw_off_stop = 0;
u1 u1g_f_50mm_range_out = 0;
u1 u1g_f_lock_timeout_restart = 0;
u1 u1g_f_solenoid_mode = 0;				
u1 u1g_f_rangein_kagen_kitei = 0;		

/********* 	in call_mode_process.c	**********/

u1 u1g_f_learn_open_max_huka = 0;		
u1 u1g_f_learn_close_all_huka = 0;		


u1 Fg_uart_fact_finish_trq_test = 0;
u1 Fg_uart_fact_finish_elec_test = 0;
u1 Fg_uart_fact_error = 0;
u1 Fg_uart_fact_check_stop = 0;
/********* 	in a_lock_mode.c	**********/
u1 u1g_Fg_soft_lock_out_duty = 0;

