#ifndef	__VARIABLES_H__
#define __VARIABLES_H__

#include "constants.h"
#include "Sys.h"

#define	sw_num 			3					
#define	ad_swnum		3						/*ad convert channel number plus 1*/

//#define	NUM_SINGAL		4

#define	max_num_data	0x1c					
#define	max_err_data	0x24					

//#endif

extern u1	count_for_debug[8];			
extern u2	count_for_debug_uint[4];	
//	in main.c
extern u1	u1g_current_mode;
extern u1	u1g_previous_mode;
extern u1	u1g_pre_mode;	
extern s2	s2g_cnt_plus_start;	
extern s2	s2g_cnt_plus_start_for_stop;	
extern s2 	s2g_lock_start_position; 
extern u1 	u1g_Fg_close_huka_learn;	


extern u1	u1g_signal;
extern u1   u1g_pass_route_next_signal;
extern u1	u1g_kamen_total_input;

extern u1	u1g_different_mode;
extern u1	u1g_step;

extern u1	u1g_full_open_input;
extern u1	u1g_jougen_kitei_area_input;
extern u1	pulse_35mm_input;

extern u1	u1g_temp_hosei;
extern u1	u1g_temp_b_f_p_hugo;		

extern u2	u2g_max_const_huka_hosei;
extern u2	u2g_open_std_max_huka_hosei;
extern u2	u2g_osikomi_const_huka_hosei;	
extern u2	u2g_open_std_osikomi_huka_hosei;	

extern u1	u1g_Fg_break_enable_time;
extern u1	u1g_Fg_break_enable_counter;
extern u1	u1g_Fg_break_over_stop;
extern u1 	u1g_fg_power_on;
//	in select_signal
//extern u1	u1g_signal_stop;

extern TYPE_REQ_UART_ERR req_uart_err;		

// in motion_commands.c
extern u1	u1g_step_motion;
extern u2	u2g_wait_motion_time_1ms;
extern u2	u2g_wait_motion_time_1sec;
extern u2	u2g_systimer_1ms_wait_motion;
extern u2	u2g_systimer_1sec_wait_motion;
extern u2	u2g_systimer_1ms_sol_out;

//	in mode_process.c
extern u1	u1g_shutter_state;
extern u1	u1g_threshold_huka;	
										
extern u1 	u1g_power_start;

// in state_table.c

//#define	NUM_SIG51	14
//#define	NUM_SIG52	14
//#define	NUM_MODE51	6
//#define	NUM_MODE52	7
//const extern u1	state51[NUM_SIG51][NUM_MODE51];
//const extern u1	state52[NUM_SIG52][NUM_MODE52];
#define	NUM_SIGNAL	33
#define	NUM_SIGNAL11	NUM_SIGNAL
#define	NUM_SIGNAL21	NUM_SIGNAL
#define	NUM_SIGNAL31	NUM_SIGNAL
#define	NUM_SIGNAL51	NUM_SIGNAL
#define	NUM_SIGNAL61	NUM_SIGNAL
#define	NUM_SIGNAL71	NUM_SIGNAL

#define	NUM_MODE11	10
#define	NUM_MODE21	4
#define	NUM_MODE31	10
#define	NUM_MODE51	31
#define	NUM_MODE61	20
#define	NUM_MODE71	20

extern	const u1 u1g_state11[NUM_SIGNAL11][NUM_MODE11];
extern	const u1 u1g_state21[NUM_SIGNAL21][NUM_MODE21];
extern	const u1 u1g_state31[NUM_SIGNAL31][NUM_MODE31];
extern	const u1 u1g_state51[NUM_SIGNAL51][NUM_MODE51];
extern	const u1 u1g_state61[NUM_SIGNAL61][NUM_MODE61];
extern	const u1 u1g_state71[NUM_SIGNAL71][NUM_MODE61];


//	in key_input.c
extern u1 u1g_sw_kinsetu;
extern u1 u1g_sw_blind_full_open;
extern u1 u1g_sw_clutch;
extern u1 u1g_sw_kinsetu_now;
extern u1 u1g_sw_blind_full_open_now;
extern u1 u1g_sw_clutch_now;
extern u1 u1g_key_open_only;
extern u1 u1g_key_close_only;
extern u1 u1g_key_3sw;
extern u1 u1g_key_3sw_huka_reset;
extern u1 u1g_key_3sw_jougen;

extern u1 fg_no_answer;
extern u1 u1g_f_any_key_input;				
//	in overload.c
extern u1 	u1g_kahuka_input;
extern u1 	u1g_previous_kahuka_input;
extern u1 	u1g_bousou_input;
extern u2 	u2g_learn_max_huka;
extern u2 u2g_close_2ji_kamen;
extern u2 u2g_close_1ji_kamen;
extern u1 u1g_close_const_kamen;

extern u1 u1g_temp_hosei_buffer;				
extern u4 u4g_now_ver;						
extern s1 s2g_temp_now_signed;
extern u1 u1g_cold_temp_hosei;

//	in encoder.c
extern u1 u1g_encoder_A_no_pulse;
extern u1 u1g_encoder_B_no_pulse;

extern u1 u1g_thermal_input;
extern u1 u1g_count_abnormal_speed_pulse;

//	in system_timer
extern u2	u2g_systimer_1ms_for_signal;
extern u2	u2g_systimer_1sec_for_signal;
extern u1	u1g_total_timer_input;
extern u1	u1g_timer_kahuka_loose_input;
extern u1   	u1g_timer_2sec_input;
extern u1 	u1g_timer_2sec_input_emc;
extern u1	u1g_timer_5sec_input;
extern u1	u1g_soft_lock_error_5sec_input;
extern u1   	u1g_ijou_send_wait_timer;

//	in eeprom.c
extern u1 timer_eeprom_count;
extern u1 u1g_check_sum_learn;
extern u1 u1g_check_sum_size;

extern u1 	u1g_cnt_e2prom_write;				
extern u1 	u1g_error_mode;				
extern u1	u1g_Fg_error_mode_3_write_check;	
extern u1	u1g_Fg_power_on;			

extern u1  u1g_c_short_close_p;				

extern u2 u2g_ad_buffer0_temp;
extern u2 u2g_ad_buffer_temp;
extern u2 u2g_raw_q[ad_swnum][4];			

extern u2  u2g_ad_now[ad_swnum];			
extern u1 u1g_ad_ref[ad_swnum];				

extern u2 u2g_now_data;
extern u1 u1g_curr_num;
extern u1 u1g_ver_num;
extern u1 u1g_temp_num;
extern u1 u1g_f_limit_average;
extern u2 u2g_now_data;
extern u1 u1g_limittime;

extern u1 u1g_Fg_ecu_temp_ad_error;		
extern u1 u1g_Fg_temp_ad_error;			
extern u1 u1g_Fg_ecu_ver_ad_error;		
extern u1 u1g_Fg_ver_ad_error;	

extern u2 u2g_learn_buffer;					
extern u2 u2g_learn_buffer_close;			
extern u2 u2g_std_huka;						
extern u2 u2g_std_learn;					
extern u2 u2g_max_learn_b;					
extern u2 u2g_copy_max_learn_b[(MAX_SECTION + 1)];	
extern u2 u2g_open_std_learn;

extern u1 u1g_ad_num;					
extern u1 u1g_ad_num_temp;
extern u2 u2g_max_huka;					
extern u2 u2g_nor_huka;					
extern u1 u1g_c_kahuka;					
			
extern u2 u2g_p_differ[2];				
extern u4 u4g_plus_length_buffer;		

extern u1 u1g_c_no_plus;				
extern u2 u2g_c_interval_plus;			
extern u2 u2g_d_pwm;					
extern s2 s2g_p_differ_current;
extern u1 u1g_sw[sw_num];				
extern u1 u1g_last_sw[sw_num];			
extern u1 u1g_c_sw_off[sw_num];		
extern u1 u1g_c_sw_on[sw_num];	
extern u1 u1g_cnt_no_in;			
//extern u1 timer_1ms;					
extern u1 u1g_count_timer_1ms;		

extern u1 u1g_cnt_thermal;				
extern s2 s2g_cnt_plus;					
extern s2 s2g_unknown_cnt_plus;			
extern s2 s2g_cnt_p_trq_test;		
extern s2 s2g_cnt_plus_jougen;		

extern u1 u1g_Fg_hand_close_plus;

extern s2 s2g_size_ram[6];			
							
								
extern s2 s2g_kari_size_ram;				
extern u2 u2g_over_lev_b[(MAX_SECTION + 1)][5];
extern u2 u2g_kamen_over_lev_b[5];				

extern u1 u1g_n_section;						
extern u1 u1g_num_section;					
extern u1 u1g_num_section_kagen;					
extern u1 u1g_copy_section;					
extern u1 u1g_Fg_jougen_area;				
extern u1 u1g_Fg_copy_jougen_area;			
extern u1 u1g_n_lev;							
extern u2 u2g_open_over_lev_b[(MAX_SECTION + 1)][5];	

extern u2 u2g_kahuka_mirror[FLASH_DATA_SIZE];			

extern u2 u2g_cnt_chng_mode;					
extern u1 u1g_cnt_chng_mode_huka_reset;		
extern u1 u1g_cnt_chng_mode_startup;
extern u1 u1g_b_p_hosei;	
extern u1 u1g_b_ver_hosei;	
extern u1 u1g_p_hosei;	
extern u2 u2g_kei;
extern u2 u2g_cal_b;
extern u1 cnt_break_on;	
extern u1 cnt_break_off;
extern u1 cnt_pwm_off;	
extern u1 cnt_pwm_on;	
extern u1 cnt_stop;			
extern u1 u1g_cnt_breakdown;		

extern u1 w_b_pulse;				
extern u2 u2g_std_max_huka;			
extern u1 cnt_soft_start;		
extern u1 u1g_c_check_out;	
//extern u1 u1g_error_ram[max_err_data + 1];		
extern u2  u2g_c_move_consist;				
extern u2  u2g_c_hand_move;		
extern u1 u1g_thermal_count;
extern u1 f_step_error;	

extern u1 c_wait;		

extern u2 u2g_d_mv;
extern u2 u2g_huka_jougen;
extern s2 s2g_imaginary_close_posi;
extern u1 u1g_c_move_m_p;		
extern u2 u2g_cnt_no_dire_p;	
extern u1 u1g_cnt_short_open_p;		
extern u1 u1g_f_input_pulse;


extern u1 u1g_motor_speed;
extern u1 u1g_previous_motor_speed;

extern u2 u2g_jougen_open_over_lev_b;	
extern u2 u2g_keep_jougen_open_over_lev_b;	


extern u1 u1g_ope0_done;
extern u1 u1g_sf_set_kagen;
extern u2 u2g_buf_check_3sw_set_ok;
extern u1 u1g_cnt_input_key_stop;
extern u2 u2g_timer_limit_set_kagen;
extern u1 u1g_signal_read_stop;
extern u1 u1g_data_H_size_input[32];
extern u1 u1g_index_H_size_input;


extern u2 u2g_time_remocon_req_wait_ms;


extern u1	u1g_uart_buzzer_order;				
extern u2	u2g_systimer_1ms_timer_for_anjou;
extern u2	u2g_systimer_1sec_timer_for_anjou;
extern u1	u1g_f_release_elec;						
extern u1	u1g_f_ok_set_on_shortbreak;				

extern u1 u1g_debug_step_torque_test;	
extern u1 u1g_debug_step_denki_test;	


extern s2	s2g_cnt_plus_speed_down;

extern u2 u2g_pre_key;
extern u1 u1g_cnt_set_level;

extern u1 u1g_stop_counter;
extern TYPE_BYTE	flag1;					
#define  Fg_f_error_write	flag1.bit.b7		
#define  Fg_soft_start_f	flag1.bit.b6		
#define  Fg_c_learn			flag1.bit.b5		
#define  Fg_keyoff_f		flag1.bit.b4		
#define  Fg_f_lock_out_start	flag1.bit.b3	
#define  Fg_f_timeover_lock	flag1.bit.b2	
#define  Fg_f_close_mukou	flag1.bit.b1	
#define  Fg_key_stop_only	flag1.bit.b0	

extern TYPE_BYTE	flag2;						/* multi_purpose frag2 */
#define  Fg_f_ad_ok		flag2.bit.b7		
#define  Fg_opef_break		flag2.bit.b6		
#define  Fg_f_stop_sakiosi	flag2.bit.b5		
#define  Fg_f_pwm_req		flag2.bit.b4		
#define  Fg_lock_sw_only	flag2.bit.b3	
#define  Fg_f_close_after	flag2.bit.b2	
#define  Fg_f_break		flag2.bit.b1	
#define  Fg_f_move_consist	flag2.bit.b0	

extern TYPE_BYTE	flag3;						/* multi_purpose frag3 */
#define  Fg_f_error_mode	flag3.bit.b7		
#define  Fg_f_disable_e2prom	flag3.bit.b6	
#define  Fg_f_fin_break	flag3.bit.b5		
#define  Fg_f_curr_ad_end	flag3.bit.b4	
#define  Fg_f_data_out_only	flag3.bit.b3	
#define  Fg_f_rock_wait	flag3.bit.b2		
#define  Fg_f_f_ad_go		flag3.bit.b1	
#define  Fg_key_ha			flag3.bit.b0	

extern TYPE_BYTE	flag4;						/* multi_purpose frag4 */
//#define  		flag4.bit.b7		
#define  Fg_f_over_xms		flag4.bit.b6		
#define  Fg_f_sw_cancel	flag4.bit.b5		
#define  f_full_close	flag4.bit.b4		
#define  Fg_f_end_learn	flag4.bit.b3		
//#define  Fg_f_eneble_write	flag4.bit.b2		
#define  f_ene_eeprom	flag4.bit.b1		
#define  Fg_f_upper_start	flag4.bit.b0		

#define	bit BYTE_FIELD					/* 170217ni */
extern TYPE_BYTE	flag5;						/* multi_purpose frag5 */
#define  Fg_f_no_position 	flag5.BYTE_FIELD.b7		
#define  f_check_p		flag5.bit.b6		
#define  f_check_out	flag5.bit.b5		
#define  f_check_4		flag5.bit.b4
#define  Fg_f_p_1_fugo		flag5.bit.b3
#define  Fg_f_re_read		flag5.bit.b2		
#define  Fg_f_fset_hukachi	flag5.bit.b1		
#define  Fg_f_fin_both		flag5.bit.b0	

extern TYPE_BYTE	flag6;						/* multi_purpose frag6 */
#define  Fg_f_ver_under	flag6.bit.b7		
//#define  Fg_f_temp_under	flag6.bit.b6		
#define  Fg_f_fst_close	flag6.bit.b5		
#define  Fg_f_disable_learn	flag6.bit.b4	
#define  Fg_f_last_stateth	flag6.bit.b3	
#define  Fg_f_reset_breakoff 	flag6.bit.b2
#define  Fg_f_check_9		flag6.bit.b1
#define  Fg_tf_start_huka	flag6.bit.b0

extern TYPE_BYTE	flag7;						/* multi_purpose frag7 */
#define  f_ha_off	 	flag7.bit.b7	
#define  f_ha_in	 	flag7.bit.b6	
#define  f_last_state 	flag7.bit.b5
#define  f_monitor	 	flag7.bit.b4
#define  f_abnormal2 	flag7.bit.b3
#define  Fg_f_abnormal 	flag7.bit.b2
#define  f_fast_close	flag7.bit.b1
#define  f_start_check	flag7.bit.b0

extern TYPE_BYTE	flag8;						/* multi_purpose frag8 */
#define  Fg_f_ene_sepablo	flag8.bit.b7	
#define  f_ene_write	flag8.bit.b6	
#define  f_b_pulse		flag8.bit.b5	
#define  f_end_close	flag8.bit.b4	
#define  Fg_f_p_hugo		flag8.bit.b3	
#define  Fg_f_ver_error	flag8.bit.b2	
#define  Fg_b_f_p_hugo		flag8.bit.b1	
#define  Fg_f_direction_p	flag8.bit.b0	

extern TYPE_BYTE	flag9;						/* multi_purpose frag */
#define  f_ene_pulse_check	flag9.bit.b7		/**/
#define  f_pulse_in		flag9.bit.b6		/**/
#define  f_out_wait		flag9.bit.b5		/**/
#define  f_lock_out1	flag9.bit.b4		/**/
//#define  		flag9.bit.b3		
#define  f_farst_autostop	flag9.bit.b2		/**/
//#define  		flag9.bit.b1		
#define  stop_only_in	flag9.bit.b0		/**/

extern TYPE_BYTE	flag10;						/* multi_purpose frag */
//#define  	flag10.bit.b7		
#define  f_lock_wait	flag10.bit.b6		/**/
//#define  		flag10.bit.b5		
#define  f_conti_open	flag10.bit.b4		/**/
#define  Fg_f_p_0_fugo		flag10.bit.b3		/**/
#define  farst_out_lock	flag10.bit.b2		/**/
#define  f_active_led	flag10.bit.b1		/**/
#define  lock_out_step_f	flag10.bit.b0		/**/

extern TYPE_BYTE	flag11;						/* multi_purpose frag */
#define  Fg_lock_sw		flag11.bit.b7		
#define  Fg_mid_state		flag11.bit.b6		/**/
#define  Fg_final_state	flag11.bit.b5		/**/
#define  f_no_zenpei	flag11.bit.b4		/**/
#define  f_kahuka_mukou	flag11.bit.b3		/**/
//#define  	flag11.bit.b2		
#define  f_lockin		flag11.bit.b1		/**/
#define  Fg_f_ps_zenpei	flag11.bit.b0		

extern TYPE_BYTE	flag12;						/* multi_purpose frag */
#define  Fg_f_open_huka_stop	flag12.bit.b7		/**/
//#define  	flag12.bit.b6		
#define  f_fst_zen_kari	flag12.bit.b5		/**/
#define  f_fst_upper	flag12.bit.b4		/**/
#define  Fg_f_upper_huka	flag12.bit.b3	
#define  timer_1s3		flag12.bit.b2		/**/
#define  Fg_lock_kijun		flag12.bit.b1	
//#define  	flag12.bit.b0		

#define	bit4	NIBLE_FIELD
extern  TYPE_NIBLE		nible1;					/* multi_purpose nible1 */
#define  u1g_mode			nible1.bit4.b1		
#define  u1g_ope_state_f	nible1.bit4.b0		

extern  TYPE_NIBLE		nible2;					/* multi_purpose nible2 */
#define  sf_break_both	nible2.byte			/**/
#define  sf_break		nible2.bit.b1		
#define  sf_break2		nible2.bit.b0	

//extern  TYPE_NIBLE		nible3;					
												/* multi_purpose nible3 */
//#define  			nible3.bit.b1		
//#define  count_ad_timer	nible3.bit.b0		

extern  TYPE_NIBLE		nible4;					/* multi_purpose nible4 */
#define  befor_lev_huka	nible4.NIBLE_FIELD.b1
#define  u1g_lev_huka		nible4.NIBLE_FIELD.b0

extern  TYPE_NIBLE		nible5;					/* multi_purpose nible5 */

extern TYPE_BYTE	swflag;						/* sw_in frag */
#define  u1g_keyin				swflag.byte
#define  Fg_keyin_bouhan		swflag.bit.b5
#define  Fg_keyin_blind_close	swflag.bit.b4
#define  Fg_keyin_blind_open	swflag.bit.b3
#define  Fg_keyin_stop			swflag.bit.b2
#define  Fg_keyin_close			swflag.bit.b1
#define  Fg_keyin_open			swflag.bit.b0

extern TYPE_BYTE	swoffflag;					/* sw_off frag */
#define  u1g_keyoff				swoffflag.byte
//#define  	swoffflag.bit.b7
//#define  	swoffflag.bit.b6
#define  Fg_keyoff_bouhan		swoffflag.bit.b5
#define  Fg_keyoff_blind_close	swoffflag.bit.b4
#define  Fg_keyoff_blind_open	swoffflag.bit.b3
#define  Fg_keyoff_stop		swoffflag.bit.b2
#define  Fg_keyoff_close		swoffflag.bit.b1
#define  Fg_keyoff_open		swoffflag.bit.b0

extern  TYPE_WORD	swnflag;					/* sw frag */
#define  u2g_key				swnflag.word
//#define  		swnflag.bit.b15
//#define  		swnflag.bit.b14
//#define  		swnflag.bit.b13
//#define  		swnflag.bit.b12
//#define  		swnflag.bit.b11
#define  Fg_osikiri_bouhan			swnflag.bit.b10
#define  Fg_osikiri_blind_close	swnflag.bit.b9
#define  Fg_osikiri_blind_open		swnflag.bit.b8
#define  Fg_key_bouhan			swnflag.bit.b7
#define  Fg_key_blind_close	swnflag.bit.b6
#define  Fg_key_blind_open		swnflag.bit.b5
#define  Fg_osikiri_close		swnflag.WORD_FIELD.b4
#define  Fg_osikiri_open		swnflag.WORD_FIELD.b3
#define  Fg_key_stop			swnflag.WORD_FIELD.b2
#define  Fg_key_close			swnflag.WORD_FIELD.b1
#define  Fg_key_open			swnflag.WORD_FIELD.b0

extern TYPE_BYTE		outbuffer_;					/* output buffer */
#define  outbuffer		outbuffer_.byte
#define  Fg_f_dis_pwm		outbuffer_.bit.b7
#define  f_break_out	outbuffer_.bit.b6
#define  Fg_ver_keep	outbuffer_.bit.b5
#define  Fg_pump_out		outbuffer_.bit.b4
#define  Fg_ccw			outbuffer_.bit.b3
#define  Fg_cw				outbuffer_.bit.b2
#define  Fg_sol_out		outbuffer_.bit.b1
#define  Fg_pwm_out		outbuffer_.bit.b0

extern TYPE_BYTE		ftimer1s_;						/* 1s flag_field */
//#define  timer_1s_f		ftimer1s_.byte
//#define  	ftimer1s_.bit.b7
//#define  	ftimer1s_.bit.b6
//#define  timer_waite	ftimer1s_.bit.b5		
//#define  timer_over		ftimer1s_.bit.b4
//#define  		ftimer1s_.bit.b3
#define  timer_break	ftimer1s_.bit.b2
#define  timer_1s2		ftimer1s_.bit.b1
#define  timer_1s		ftimer1s_.bit.b0

extern TYPE_BYTE		ftimer100ms_;					/* 100ms flag_field */
#define  Fg_timer_100ms_f	ftimer100ms_.byte
#define  Fg_lock_led_100	ftimer100ms_.bit.b7
#define  Fg_lock_timer100	ftimer100ms_.bit.b6
#define  Fg_f_lock_100ms	ftimer100ms_.bit.b5
#define  Fg_lock_3sec		ftimer100ms_.bit.b4
#define  Fg_f_chng_mode_t	ftimer100ms_.bit.b3
#define  Fg_timer_thermal	ftimer100ms_.bit.b2
#define  Fg_timer_over		ftimer100ms_.bit.b1
#define	 Fg_ f_soft_100ms	ftimer100ms_.bit.b0

extern TYPE_BYTE		ftimer10ms_;						/* 10ms flag_field */
#define  timer_10ms_f	ftimer10ms_.byte
//#define  	ftimer10ms_.bit.b7
//#define  	ftimer10ms_.bit.b6
#define  f_10ms_lock	ftimer10ms_.bit.b5
#define  timer10ms_3	ftimer10ms_.bit.b4
#define  pre_ope_t		ftimer10ms_.bit.b3
#define  f_ha_10ms		ftimer10ms_.bit.b2	
#define  timer10ms_2	ftimer10ms_.bit.b1		
#define  timer10ms_1	ftimer10ms_.bit.b0		

extern TYPE_BYTE		selectsw_;				/* 4bit select sw  */
#define  modeselsw		selectsw_.byte
#define  selsw7			selectsw_.bit.b7
#define  selsw6			selectsw_.bit.b6
#define  selsw5			selectsw_.bit.b5
#define  selsw4			selectsw_.bit.b4
#define  selsw3			selectsw_.bit.b3
#define  selsw2			selectsw_.bit.b2
#define  selsw1			selectsw_.bit.b1
#define  selsw0			selectsw_.bit.b0

extern TYPE_BYTE		eeprm_buffer_;
#define eeprm_buffer_sent	eeprm_buffer_.byte
#define eeprm_buffer_sent7	eeprm_buffer_.bit.b7
#define eeprm_buffer_sent6	eeprm_buffer_.bit.b6
#define eeprm_buffer_sent5	eeprm_buffer_.bit.b5
#define eeprm_buffer_sent4	eeprm_buffer_.bit.b4
#define eeprm_buffer_sent3	eeprm_buffer_.bit.b3
#define eeprm_buffer_sent0	eeprm_buffer_.bit.b0

extern  TYPE_WORD		size_ram_ab_;
#define  u2g_size_ram_ab		size_ram_ab_.word
#define  u1g_size_ram_a			size_ram_ab_.byte[0]
#define  u1g_size_ram_b			size_ram_ab_.byte[1]

extern  TYPE_WORD		size_ram2_ab_;
#define  u2g_size_ram2_ab		size_ram2_ab_.word
#define  u1g_size_ram2_a		size_ram2_ab_.byte[0]
#define  u1g_size_ram2_b		size_ram2_ab_.byte[1]

extern  TYPE_WORD		temp_now_;
#define u2g_temp_now			temp_now_.word
#define u1g_temp_now_upper		temp_now_.byte[0]
#define u1g_temp_now_lower		temp_now_.byte[1]

extern  TYPE_WORD		num_now_;
#define u2g_num_now				num_now_.word
#define u1g_num_now1			num_now_.byte[0]
#define u1g_num_now0			num_now_.byte[1]

extern  TYPE_LONG		num_move_;
//extern  TYPE_WORD		_num_move_;
#define u2g_num_move			num_move_.word
#define u1g_num_move1			num_move_.byte[0]
#define u1g_num_move0			num_move_.byte[1]
#define b_check_num				num_move_.bit.b0


extern TYPE_BYTE	flag_NK;						/* multi_purpose frag */
#define  f_HS_signal	flag_NK.bit.b6		
#define  Fg_f_no_clutch	flag_NK.bit.b5		
#define  Fg_f_finish_soft_start	flag_NK.bit.b4	
#define  Fg_f_reset_able	flag_NK.bit.b3	
#define  Fg_f_no_clutch_before	flag_NK.bit.b2	
#define  Fg_f_no_learn_data	flag_NK.bit.b1	
//#define  	flag_NK.bit.b0		

extern TYPE_BYTE	flag_NK_signal;						/* multi_purpose frag */
//#define  Fg_f_saikou_kirikae	flag_NK_signal.bit.b7		
//#define  Fg_f_timer_200msec_input	flag_NK_signal.bit.b6		/*200msec経過信号フラグ*/
#define  f_sw_clutch	flag_NK_signal.bit.b5	
#define  Fg_f_pulse_blind_finish	flag_NK_signal.bit.b4		
#define  u1g_f_rangeout_kagen	flag_NK_signal.bit.b3	
#define  u1g_f_complete_lock	flag_NK_signal.bit.b2	
#define  u1g_f_suspend_lock	flag_NK_signal.bit.b1		
#define  u1g_f_stop_shortclose	flag_NK_signal.bit.b0	

extern TYPE_BYTE	flag_learn_open;					/* learn_open frag */
#define  u1g_f_open_learn		flag_learn_open.byte
#define  u1g_f_kagen_set		flag_learn_open.bit.b7	
#define  u1g_f_open_learn_comp	flag_learn_open.bit.b6	
#define  u1g_f_open_spot_learn	flag_learn_open.bit.b5	
#define  u1g_f_open_small_size	flag_learn_open.bit.b4	
#define  u1g_f_open_large_size	flag_learn_open.bit.b3	
#define  u1g_f_open_learn_error	flag_learn_open.bit.b2	
#define  u1g_f_close_learn_comp	flag_learn_open.bit.b1	

extern u1 u1g_Fg_soft_lock_out_duty;		
extern u1 	u1g_f_stop_shortopen;				


extern	TYPE_WORD u2g_size_ram_H_size;

extern u2	u2g_max_const_huka;			
extern u2	u2g_open_std_max_huka;			
extern u2	u2g_open_std_osikomi_huka;	
extern u2	u2g_osikomi_const_huka;			
extern u2	u2g_osikomi_const_huka_540rpm;

extern u2 u2g_standard_plus_length;	

extern u1 u1g_timer_f_ad;

extern u1 u1g_fg_charge_pump_enable;
extern u1 u1g_fg_next_main_go;

extern u2 u2g_count_tanrak_break_timer;
extern u2 u2g_soft_clear_counter;

extern u1 u1g_speed_up_slow_down;

extern u1 u1g_timer_3sw_100msec;

//extern u2 u2g_count_tanrak_break_timer; 
extern u1 u1g_count_90_sec_timer_0_100; 
extern u2 u2g_count_90_sec_timer_100_90000;
//extern u2 u2g_soft_clear_counter;

extern u1 u1g_fg_flash_initial;

extern u2 u2g_flash_write_data[FLASH_DATA_SIZE];

extern u1 u1g_fg_wait_format_complete;
extern u1 u1g_fg_wait_write_complete;

extern TYPE_WORD u2g_fg_control_structure;
#define  Fg_request_flash_write		u2g_fg_control_structure.bit.b5
#define  Fg_request_flash_read		u2g_fg_control_structure.bit.b4
#define  Fg_request_flash_reclaim	u2g_fg_control_structure.bit.b3
#define  Fg_request_flash_erase		u2g_fg_control_structure.bit.b2
#define  Fg_request_flash_format	u2g_fg_control_structure.bit.b1
#define  Fg_request_flash_init		u2g_fg_control_structure.bit.b0

extern s4 s4g_d_mv_loss_number;

extern u1 u1g_f_reset_after_write;
extern u2 u2g_c_main;

extern u1 u1g_fg_set_h_size_end;
extern u1 u1g_c_noservice;
extern u1 u1g_f_active_format;

extern u1 u1g_fg_read_retry;		

extern u2 u2g_raw_data[NUM_CAPTURE_DATA];
extern u2 u2g_check_temp_ad_data[NUM_AD_CHECK_DATA];
extern u2 u2g_check_ver_ad_data[NUM_AD_CHECK_DATA];

extern s1 s1g_temp_v;

extern u2 u2g_result_trqadjust;					
extern u1 u1g_f_trqajst_to_mainloop;			
extern u1 u1g_f_trqajststep_kidou;				
extern u2 u2g_timeover_trqajt;
extern u1 u1g_f_step_trq_ajt;
extern u1 u1g_f_ene_trqajst;
extern u1 u1g_f_disable_trqadjust;

extern u2 u2g_timelimit_trqajt;

extern u2 u2g_ajst_max_huka;
extern u2 u2g_ajst_open_max_huka;
extern u2 u2g_ajst_osikomi_const_huka;
extern u2 u2g_ajst_open_std_osikomi_huka;

extern u1 u1g_key_3sw_trqajst_reset;
extern u1 u1g_cnt_trqajst_reset;

extern u1 u1g_f_timeover_anjo_test;

extern u1 u1g_section_kahuka_occured;				
extern u1 u1g_huka_ad_value;					

extern u1 u1g_temp_previous_mode;					
extern u1 u1g_temp_signal;							
extern u1 u1g_temp_free_data;						


//extern TYPE_ERROR_1 xn_error_set1;						// 1回前
//extern TYPE_ERROR_1 xn_error_set0;						// 今回（0回前）

//extern TYPE_FLASH_LEARN_BODY xng_learned_huka_data;			// 負荷学習値フラッシュデータ
//extern TYPE_FLASH_ERROR_BODY_1 xng_error_data;				// 直近２個の詳細異常履歴データ
//extern TYPE_FLASH_ERROR_BODY_2 xng_error_20_data;			// 過去20個の異常履歴データ
//extern TYPE_FLASH_HSIZE_BODY xng_Hsize_series;				// Hサイズフラッシュデータ
//extern TYPE_FLASH_FACT_BODY xng_record_fact;				/* 検査工程用バッファ */

//#define U1_FLASH_LEARN_DATASIZE		sizeof(xng_learned_huka_data)		// 学習データbyteサイズ
//#define U1_FLASH_ERROR_DATASIZE		sizeof(xng_error_data)			// 異常履歴データbyteサイズ
//#define U1_FLASH_ERROR_20_DATASIZE	sizeof(xng_error_20_data)	
//#define U1_FLASH_HSIZE_DATASIZE		sizeof(xng_Hsize_series)		// Hサイズデータbyteサイズ
//#define U1_FLASH_FACT_DATASIZE		sizeof(xng_record_fact)			// Hサイズデータbyteサイズ

#define u1g_flash_type_error		xng_flash_error_data.xn_error_data._xn_error_set0.u1_kind_of_error			
#define u1g_flash_previous_mode		xng_flash_error_data.xn_error_data._xn_error_set0.u1_previous_mode			
#define u1g_flash_signal		xng_flash_error_data.xn_error_data._xn_error_set0.u1_signal					
#define u1g_flash_free_data		xng_flash_error_data.xn_error_data._xn_error_set0.u1_free					
#define u2g_flash_num_times		xng_flash_error_data.xn_error_data._xn_error_set0.u2_number_of_times		

extern TYPE_FLASH_LEARN_UNIT xng_flash_learned_hukadata;		
#define u1g_flash_learndata_top		xng_flash_learned_hukadata.byte[0]

#define u1g_flash_close_huka15		xng_flash_learned_hukadata.xn_learned_huka_data.u1_close_huka[15]
#define u1g_flash_close_huka14		xng_flash_learned_hukadata.xn_learned_huka_data.u1_close_huka[14]
#define u1g_flash_close_huka13		xng_flash_learned_hukadata.xn_learned_huka_data.u1_close_huka[13]
#define u1g_flash_close_huka12		xng_flash_learned_hukadata.xn_learned_huka_data.u1_close_huka[12]
#define u1g_flash_close_huka11		xng_flash_learned_hukadata.xn_learned_huka_data.u1_close_huka[11]
#define u1g_flash_close_huka10		xng_flash_learned_hukadata.xn_learned_huka_data.u1_close_huka[10]
#define u1g_flash_close_huka9		xng_flash_learned_hukadata.xn_learned_huka_data.u1_close_huka[9]
#define u1g_flash_close_huka8		xng_flash_learned_hukadata.xn_learned_huka_data.u1_close_huka[8]
#define u1g_flash_close_huka7		xng_flash_learned_hukadata.xn_learned_huka_data.u1_close_huka[7]
#define u1g_flash_close_huka6		xng_flash_learned_hukadata.xn_learned_huka_data.u1_close_huka[6]
#define u1g_flash_close_huka5		xng_flash_learned_hukadata.xn_learned_huka_data.u1_close_huka[5]
#define u1g_flash_close_huka4		xng_flash_learned_hukadata.xn_learned_huka_data.u1_close_huka[4]
#define u1g_flash_close_huka3		xng_flash_learned_hukadata.xn_learned_huka_data.u1_close_huka[3]
#define u1g_flash_close_huka2		xng_flash_learned_hukadata.xn_learned_huka_data.u1_close_huka[2]
#define u1g_flash_close_huka1		xng_flash_learned_hukadata.xn_learned_huka_data.u1_close_huka[1]
#define u1g_flash_close_huka0		xng_flash_learned_hukadata.xn_learned_huka_data.u1_close_huka[0]
#define u1g_flash_learn_open_fg		xng_flash_learned_hukadata.xn_learned_huka_data.u1_open_huka[1]
#define u1g_flash_open_allarea		xng_flash_learned_hukadata.xn_learned_huka_data.u1_open_huka[0]
#define u1g_flash_upper_ref		xng_flash_learned_hukadata.xn_learned_huka_data.u1_jogen_sansyo
//#define u1g_flash_max_open_pulse	xng_flash_learned_hukadata.xn_learned_huka_data.u1_max_open_pulse
#define u1g_flash_checksum_huka		xng_flash_learned_hukadata.xn_learned_huka_data.u1_huka_check_sum


extern TYPE_FLASH_ERROR_UNIT xng_flash_error_data;				
#define u1g_flash_errordata_top		xng_flash_error_data.byte[0]

#define xn_flash_error_set1		xng_flash_error_data.xn_error_data._xn_error_set1
#define xn_flash_error_set0		xng_flash_error_data.xn_error_data._xn_error_set0

#define u2g_flash_num_openclose		xng_flash_error_data.xn_error_data.u2_number_openclose
#define u2g_flash_num_move		xng_flash_error_data.xn_error_data.u2_number_move
#define u2g_flash_num_sw_open		xng_flash_error_data.xn_error_data.u2_number_sw_open
#define u2g_flash_num_sw_close		xng_flash_error_data.xn_error_data.u2_number_sw_close

#define u1g_flash_type_error_20		xng_flash_error_20_data.xn_error_20_data.err_now.no_err		
#define u1g_flash_free_data_20		xng_flash_error_20_data.xn_error_20_data.err_now.free_area		
#define u2g_flash_num_times_20		xng_flash_error_20_data.xn_error_20_data.err_now.num_move		

extern TYPE_FLASH_ERROR_2_UNIT xng_flash_error_20_data;				
#define u1g_flash_errordata20_top	xng_flash_error_20_data.byte[0]

#define xn_flash_error_20_set19		xng_flash_error_20_data.xn_error_20_data.err_prev_19
#define xn_flash_error_20_set18		xng_flash_error_20_data.xn_error_20_data.err_prev_18
#define xn_flash_error_20_set17		xng_flash_error_20_data.xn_error_20_data.err_prev_17
#define xn_flash_error_20_set16		xng_flash_error_20_data.xn_error_20_data.err_prev_16
#define xn_flash_error_20_set15		xng_flash_error_20_data.xn_error_20_data.err_prev_15
#define xn_flash_error_20_set14		xng_flash_error_20_data.xn_error_20_data.err_prev_14
#define xn_flash_error_20_set13		xng_flash_error_20_data.xn_error_20_data.err_prev_13
#define xn_flash_error_20_set12		xng_flash_error_20_data.xn_error_20_data.err_prev_12
#define xn_flash_error_20_set11		xng_flash_error_20_data.xn_error_20_data.err_prev_11
#define xn_flash_error_20_set10		xng_flash_error_20_data.xn_error_20_data.err_prev_10
#define xn_flash_error_20_set9		xng_flash_error_20_data.xn_error_20_data.err_prev_9
#define xn_flash_error_20_set8		xng_flash_error_20_data.xn_error_20_data.err_prev_8
#define xn_flash_error_20_set7		xng_flash_error_20_data.xn_error_20_data.err_prev_7
#define xn_flash_error_20_set6		xng_flash_error_20_data.xn_error_20_data.err_prev_6
#define xn_flash_error_20_set5		xng_flash_error_20_data.xn_error_20_data.err_prev_5
#define xn_flash_error_20_set4		xng_flash_error_20_data.xn_error_20_data.err_prev_4
#define xn_flash_error_20_set3		xng_flash_error_20_data.xn_error_20_data.err_prev_3
#define xn_flash_error_20_set2		xng_flash_error_20_data.xn_error_20_data.err_prev_2
#define xn_flash_error_20_set1		xng_flash_error_20_data.xn_error_20_data.err_prev_1
#define xn_flash_error_20_set0		xng_flash_error_20_data.xn_error_20_data.err_now


extern TYPE_FLASH_HSIZE_UNIT xng_flash_Hsize_series;			
#define u1g_flash_hsizedata_top		xng_flash_Hsize_series.byte[0]

#define u2g_flash_hsize_all			xng_flash_Hsize_series.xn_Hsize_series.u2_size_data
#define u1g_flash_num_section			xng_flash_Hsize_series.xn_Hsize_series.u1_ryoiki
#define u2g_flash_max_open_pulse		xng_flash_Hsize_series.xn_Hsize_series.u2_max_open_pulse
#define u1g_flash_checksum_hsize		xng_flash_Hsize_series.xn_Hsize_series.u1_check_sum

extern TYPE_FLASH_FACT_UNIT xng_flash_fact_series;			
#define u1g_flash_factdata_top			xng_flash_fact_series.byte[0]

#define u1g_flash_finish			xng_flash_fact_series.xn_record_fact.u1_finish
#define u1g_flash_adjust_trq			xng_flash_fact_series.xn_record_fact.u1_max_torque
#define u1g_flash_soft_ver			xng_flash_fact_series.xn_record_fact.u2_soft_ver

extern u1 u1g_flash_write_status;

extern u1 u1g_2ope_3ope_signal;

extern u1 u1g_Fg_previous_kahuka_upper;	
extern s2 s2g_previous_kahuka_position;	

//#endif

extern u1 u1g_limit_ad;

extern u2 u2l_threshold_limittime;
extern u2 u2l_timemoving_lockout;
extern u1 u1g_f_move_sol;
extern u1 u1g_f_limit_6min_lock;
extern u1 u1g_f_limit_5times_lock;
extern u1 u1g_f_delay_lock;
extern u1 u1g_f_end_shortbreak;
extern u1 u1g_f_start_shortbreak;
extern u1 u1g_f_start_lock_output;
extern u1 u1g_f_sw_off_stop;
extern u1 u1g_f_50mm_range_out;
extern u1 u1g_f_lock_timeout_restart;
extern u1 u1g_f_solenoid_mode;			
extern u1 u1g_f_rangein_kagen_kitei;	


extern u1 u1g_f_learn_open_max_huka;	
extern u1 u1g_f_learn_close_all_huka;	

extern u1 Fg_uart_fact_finish_trq_test;
extern u1 Fg_uart_fact_finish_elec_test;
extern u1 Fg_uart_fact_error;
extern u1 Fg_uart_fact_check_stop;
#endif

