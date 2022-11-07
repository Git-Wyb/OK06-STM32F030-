#ifndef	__FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "Sys.h"

/* 	in startup.c */
void initial(void);
void initial2(void);
void initial_huka(void);
void startup(void);
void Int_dummy(void);
void Int_n_dummy(void);
void f_vog_trc_clear(void);
/* void	abort(void); */
void main_4_5ms_counter_timer(void);	/* 4.05 */

/* 	in main.c */
void main_loop(void);
void check_flash_task(void);
void output_main(void);
void error_ope_main(void);
void check_open_learn_error(void);
void ret_set(void);
void set_ope_state_f(void);
void ad_operate_main(void);
void check_full_close(void);
void check_kamen_total(void);
void check_count_reset(void);
void check_jougen_count_clear(void);
void h_size_m_ck(void);
void data_ram_set(void);
void mode_select(void);
void reset_learn_data_no_kamen(void);
void check_check_sum(void);
void check_size_check_sum(void);
void const_huka_hosei(void);
void process_key_3sw(void);
void check_pulse_event(void);
void mode_change_to_freeze_mode(void);
void clear_flag_emergency_open_ijou(void);
/* void a_vog_error_status_store(u1,u1,u1); */
void set_20_rireki_data(void);
/* 	in DATAMONITOR_NK02.c */

void dataMonitor(void);


/* 	in adjust_mode.c */
void adjust_mode(void);

/* 	in adjust_sw_kinsetu.c */
void adjust_sw_kinsetu(void);

/* 	in select_signal.c */
void select_signal(void);
void clear_all_event_flags(void);

/* 	in select_mode.c */
u1 select_mode(void);

/* 	in call_mode_process.c */
void call_mode_process(void);
void open_kei_set(void);
void close_kei_set(void);
void set_close_huka(void);

void current_mode_0_9(void);
void current_mode_10_19(void);
void current_mode_20_99(void);
void current_mode_20_39(void);
void current_mode_40_59(void);
void current_mode_60_79(void);
void current_mode_80_99(void);
void current_mode_100_109(void);
void current_mode_110_119(void);
void current_mode_120_159(void);
void current_mode_160_169(void);
void current_mode_170_179(void);
void current_mode_180_189(void);
void current_mode_190_255(void);

void check_open_learn_huka(void);		/* 170420ni */


void process_stop(void);
void process_open_u(void);
void process_close_u(void);
void process_open_l(void);
void process_close_l(void);
void process_osikiri_open(void);
void process_osikiri_close(void);

void check_sol_time(void);
void check_close_under_kagenSW(void);
void check_close_under_kagenSW_bouhan(void);

/* 	in mode_process.c */
void mode_stop(void);
void mode_open_u(void);
void mode_open_l(void);
void mode_close_u(void);
void mode_close_l(void);
void mode_saikou_open_u(void);
void mode_saikou_open_l(void);
void mode_saikou_close_u(void);
void mode_saikou_close_l(void);
void mode_osikiri_open(void);
void mode_osikiri_close(void);
u1 select_step_stop(void);
u1 select_step_open(void);
u1 select_step_close(void);
u1 select_step_osikiri_open(void);
u1 select_step_osikiri_close(void);


/* 	in motion_command.c */
u2 motion_break(void);
u1 motion_stop(void);
u1 motion_open_startup(void);
u1 motion_soft_open(void);
u1 motion_open(void);
u1 motion_close_startup(void);
u1 motion_soft_close(void);
u1 motion_close(void);
/* 	void motion_saikou_open(void); */
/* 	void motion_saikou_close(void); */
/* 	void motion_osikiri_open(void); */
/* 	void motion_osikiri_close(void); */

void wait_motion_start(void);
u1 wait_motion_check(void);
void open_end_port_set(void);
void close_end_port_set(void);
void break_port_set(void);
void stop_port_set(void);
void open_startup_port_set(void);
void soft_open_port_set(void);
void open_port_set(void);
void close_startup_port_set(void);
void soft_close_port_set(void);
void close_port_set(void);


/* 	in encoder.c */
void int_input_encoder(void);
void  encoder(void);
void pulse_in_operation(void);
void set_d_pwm (void);
void move_break_ope(void);
void push_pull_ope(void);
void state_output_ope(void);
void kagen_reset(void);
void ope_key_stop(void);
void sw_in_end(void);
void pulse_interval_check(void);

void move_break_d_set(void);

/* 	in key_input.c */

void sw_input_check(void);
void check_sw_state_timeout(void);
void check_answer(void);
void check_sw_huka_reset(void);
void check_sw_startup(void);
void key_f_set(void);
void osikiri_reset(void);
void soft_reset_main(void);
u1 learn_fullclose_position(void);
void calcu_mode_change_pulse(void);
void key_flag_reset(void);
void check_sw_multi_input(void);
void check_sw_stop_3times(void);
void set_kagen_main(void);
void stop_set_kagen(void);
void step_0_ope(void);
void step_1_ope(void);
void step_2_ope(void);
void step_3_ope(void);
void data_input_bit1(void);
void data_input_bit0(void);
void return_input_data(void);
void osikiri_timer(void);
void a_vog_check_position_setting(void);	/* 4.05 */

/* 	in overload.c */
void check_huka(void);
void kahuka_close_ope(void);
void huka_count_jump(void);
void thermal_check(void);
void reset_learn_data(void);
void make_learn_new_data(void);
void seprate_block(void);
void after_learn_k(void);
void sikiiti_hosei(void);
void curr_lev_de(void);
void huka_lev_ver(void);
void hosei_main(void);
void learn_get_data(void);
void learn_data_make(void);
void set_error_open_learn_data(void);
void plus_a_cal(void);
void plus_a_cal_open(void);
void make_std_learn(void);
void ope_turnover(void);
void end_learn_ope(void);
void open_block_ope(void);
void open_block_no_learn_ope(void);
void close_block_ope(void);
void bad_data_del(u2 u2_pre_valu,u2 u2_now_val);
void learn_data_set(void);
void fst_full_close(void);
void calculate_error(void);
void make_section(void);
void calcu_std_huka(void);
void hosei_main_kamen(void);
void adjust_std_huka_1857to1000(void);
void check_ad_error_stop(void);
void select_learn_max_data(void);
u1 get_max_close_learn_data(void);

/* void set_write_data(void); */
void first_data_check(void);
void make_check_sum(void);
void make_size_check_sum(void);


u2 read_ad_data(u1);				/* AD変換結果レジスタの読出し */
void select_ad_class(u1);				/* AD変換ポート指定 */

void rest_startup(void);				/* マイコンリセットの実行 */
void set_pwm_limit_filter(void);		/* PWM設定最大値マスク */
void reset_watch_dog_timer(void);		/* WDTリセット */

void LED_blink(u1 *port, s2 num);		/* LED出力状態切り替え */
void LED_output(void);					/* LED出力メイン */
/* void set_LED(char red_or_green_or_both); */
/* void start_LED_blink(char red_or_green_or_both, u1 times, u1 interval); */
void timer_LED_blink(void);				/* LED点滅指示 */

void ready_write_data(void);			/* フラッシュへの書込みデータ準備 */
void rest_ready_write_data(void);		/* フラッシュへのリセットデータの準備 */

/* 170217nivoid write_data_number_check(void);		学習値・異常履歴連続書込み状態判定 */

void ad_start_set(u1 u1_ad_num);		/*AD変換ポート設定*/

u2 capture_ad_start(u1 u1_num,u1 u1_usedata_num);	/*変換データ取得*/
u1 adopt_data_num_set(u1 num_adopt);	/*生値格納場所設定*/
s2 absolute_calculate( s2 s2_num_cal1,s2 s2_num_cal2 );	/*2数の差の絶対値を返す*/
extern u1 u1a_fg_current_pulse_over_flow;

void a_vog_error_status_store(u1 u1_mode,u1 u1_sig,u1 u1_error_state);

void process_shortbreak(void);
void process_stop_lock(void);
void mode_shortbreak(void);
void mode_wait_lock(void);
u1 motion_shortbreak(void);

void a_vog_lock_mode_main(void);

void sol_ope_main(void);
void check_sol_short_error(void);
void solenoid_short(void);

#endif	/* __FUNCTIONS_H__ */

 
 
