#include "stm32f0xx.h"
#include "Sys.h"
#include "Gpio.h"
#include "Adc.h"
#include "Timer.h"
#include "Uart.h"
#include "M24C16.h"

#include "def_local.h"
#include "variables.h"
#include "functions.h"
#include "trq_adjust_trqchange.h"
#include "flash_data_read.h"
#include "a_data_exchange.h"
#include "comm_uart.h"
#include "comm_uart_local.h"
#include "anjou_test.h"
#include "tst_break.h"
#include "storage.h"
#include "ecu_test.h"
#include "input_encoder.h"

#define S2L_P_END_PRECLOSE		((s2)18)
#define S2L_P_END_REVOPEN		((s2)18)

static void a_vol_clear_upper_limit(void);
static void a_vol_reset_upper_limit(void);
static void check_error_clear(void);
static void check_uart_error(void);
static void check_unknown_posi_error(void);
static void a_vol_clear_reset_command(void);
static void a_vol_motor_huka_setting(void);
static void check_break_enable_time(void);
static void check_break_stop(void);
static void check_power_on_rireki(void);
static void close_huka_data_set(void);
static void open_huka_data_set(void);
static void soft_lock_signal(void);
void variable_setup(void);
static void main_loop(void);

u1 w_buff[90] = {11,1,2,3,4,5,6,7,8,9,10};
u1 r_buff[90] = {0};
u1 datat = 55;
u1 readata = 0;
int main(void)
{
    Init_IWDG();
    Init_Gpio();
    Init_Delay();
    R_WDT_Restart();
    storage_init();
    R_WDT_Restart();
    Init_Adc();
    Init_Timer6();
    Init_Timer16();
    Init_Timer17();
    Init_Timer15();
    Init_Uart1(9600);
    R_WDT_Restart();
    variable_setup();
//    delay_ms(100);
//    P_PWM_OUT_1;
//    M24C16_Read(0,r_buff,1);
//    P_PWM_OUT_0;
//    R_UART0_Receive(w_buff,7);
//    delay_ms(100);
//    P_EM_RESET_N_1;
//    R_TAU0_Channel4_Start();
//    P_RELAY_3_0;
//	P_RELAY_2_1;
//    P_RELAY_1_1;
//    P_PWM_OUT_1;
//    while(1)
//    {
//        delay_us(5);
//        P_PWM_OUT_1;
//        delay_us(2);
//        P_PWM_OUT_0;
//    }
//    MCO_ClockOutPut_PA8();
//    R_ADC_Start();
//    RCC->CFGR &= ~0x0f000000;
//    RCC->CFGR |= RCC_CFGR_MCO_HSE;
    while(1)
    {
        main_loop();
//        Key_Sw_Dete();
//        adc_test();
    }
}

void HardFault_Handler(void)
{
    while(1);
}

/************************************************
 *	メイン処理
 *-----------------------------------------------
 *	引数
 *		無し
 *	戻り値
 *		無し
 *	処理内容
 *  	一定周期毎に実行するメイン処理
 *	呼出タイミング
 *		4.5ms毎
 ************************************************/
void main_loop(void)
{
 /********   WDT operate     *************************************/
	R_WDT_Restart();

//Issues commands such as initialization processing, write processing, and read processing at any time.

	check_flash_task();

	ret_set();
	
/********  motor setting   ********************************/

	u2g_standard_plus_length = STAND_PLUS_LENGTH;

	a_vol_motor_huka_setting();
	
/********   A/D convert     *************************************/

	ad_operate_main(); 
	
/********   key input     ***************************************/
	sw_input_check();

	key_f_set();				

	check_error_clear();		//Clear confirmation of UART communication error

	check_break_stop();
	check_ad_error_stop();

	if(u1g_mode != U1G_STOP_MODE){
		check_huka();			
	}
	else{
		u1g_c_kahuka = 0;
	}

	check_count_reset();		
	
	pulse_interval_check();	

	check_kamen_total();
//	ecu_test_main();	

	process_key_3sw();
	
	soft_lock_signal();
	anjou_test_signal();
	select_signal();

	if(u1g_signal != 255){
		u1g_current_mode = select_mode();
	}
	else{}
	
	if(u1g_current_mode == 255){
		u1g_current_mode = u1g_previous_mode;
		if((u1g_error_mode == ERR_HAND_MOVE) || (u1g_error_mode == ERR_POWER)){

		}
		else{
			u1g_error_mode = ERR_NONE;
		}
	}
	else if(u1g_current_mode == 254){
		rest_startup();
	}
	else{}
	


	if(u1g_current_mode == u1g_previous_mode){
		u1g_different_mode = 0;
	}
	else{
		u1g_different_mode = 1;

		Fg_f_finish_soft_start = 0;
	}

	check_open_learn_huka();
	
	call_mode_process();
	
	set_ope_state_f();
	
	comm_uart();
	
	storage_memory_handler();
	
/********   error check *****************************************/
	error_ope_main();
	
	a_vog_lock_mode_main();
	
	check_pulse_event();
	
	sol_ope_main();	

	u1g_copy_section = u1g_n_section;
	
	make_section();
	
	output_main();
	
	u1g_previous_mode = u1g_current_mode;
	u1g_pre_mode = u1g_mode;
	u1g_previous_motor_speed = u1g_motor_speed;

	a_vol_clear_reset_command();
}

void output_main(void){
/*===    pwm    ==========*/
	if( (Fg_pwm_out == 1)&&(Fg_f_dis_pwm == 0) )
		{
			set_d_pwm();							
			set_pwm_limit_filter();					
			if(u1g_Fg_pwm_start_pass_code == 0){
				R_TAU0_Channel4_Start();
				u1g_Fg_pwm_start_pass_code = 1;
			}	
			
			if( ( u1g_mode == U1G_CLOSE_MODE) || ( u1g_mode == U1G_OSIKIRI_CLOSE_MODE) ){
				check_break_enable_time();
			}
			else if( ( u1g_mode == U1G_OPEN_MODE) || ( u1g_mode == U1G_OSIKIRI_OPEN_MODE) ){
				check_break_enable_time();
			}
			else{
				u1g_t_break_step = 0;	
			}
		}
	else
		{
			R_TAU0_Channel4_Stop();
			P_PWM_OUT_0;							

			u1g_Fg_pwm_start_pass_code = 0;
			Fg_pwm_out = 0;						
			u2g_d_pwm = D_PWM_MIN;					
			u2g_d_mv = 0;	
			u1g_c_no_plus = 0;	

		}
/*======  break     ========*/
	if(get_ecu_test_state() != ECU_TST_BREAK_TEST){
		if(u1g_Fg_break_enable_time != 0){
			check_t_break_main();
		}
		else{
			t_flag_all_clear();
		}

		if( u1g_mode == U1G_STOP_MODE ){
			
			R_TAU0_Channel6_Stop();		

			u1g_Fg_break_start_pass_code = 0;
			u1g_Fg_break_enable_counter = 0;
			u1g_Fg_break_enable_time = 0;
		}
	}
	else{}

//#ifdef OK04	/* OK04でソレノイド動作の対応を行なう */
///*======  sol       ========*/
//	if( Fg_sol_out == 1)
//		{
//			P_SOLENOID_1;
//		}
//	else
//		{
//			P_SOLENOID_0;
//		}

///*======  Fg_ver_keep ========*/
//	if( Fg_ver_keep == 1)	/* 電圧安定ポートは反転して設定 */
//		{
//			P_VER_KEEP_0;
//		}
//	else
//		{
//			P_VER_KEEP_1;
//		}
//#endif

	if( u1g_f_release_elec == 1 ){
		
		u1g_fg_charge_pump_enable = 0;	
		P_RELAY_1_0;			
		P_RELAY_2_1;
		P_RELAY_3_1;
	}
	else{
		
/*======  Fg_cw       ========*/
		if( Fg_cw == 1)    
			{
				P_RELAY_2_0;
				P_RELAY_3_1;
			}
		else
			{
				P_RELAY_3_0;
			}
/*======  Fg_ccw      ========*/
		if( Fg_ccw == 1)  //CLOSE
			{
				P_RELAY_3_0;
				P_RELAY_2_1;
			}
		else
			{
				P_RELAY_2_0;
			}
/*======  Fg_pump_out     =======*/
		if( Fg_pump_out == 1 ){
			u1g_fg_charge_pump_enable = 1;

		}
		else{
			u1g_fg_charge_pump_enable = 0;			
			P_RELAY_1_0;
		}
	}

}


void ret_set(void)
{
	if( Fg_f_fset_hukachi == 0 )	
		{
			Fg_f_fset_hukachi = 1;
			data_ram_set();			

			u1g_fg_power_on = 1;
		}
	else{
	}
}



void data_ram_set(void){
	u1 u1l_j = 0;

	for( u1l_j = 0;u1l_j < CHECK_SUM_HUKA;u1l_j++ ){
		u2g_kahuka_mirror[u1l_j] = (u2)(*(&u1g_flash_learndata_top + u1l_j));
	}

//	/*開学習最大値を使って巻き閉める	上で読み出し済み				*/
//	/*u2g_kahuka_mirror[ADD_OPEN_LEARN_FG] = (u2)u1g_flash_learn_open_fg;			*/
//	/*u2g_kahuka_mirror[OPEN_DATA] = (u2)u1g_flash_open_allarea;			*//* 開学習値 */
//	/*u2g_kahuka_mirror[HUKA_UPPER] = (u2)u1g_flash_upper_ref;				*/
//	
	u2g_kahuka_mirror[SIZE_RAM] = u2g_flash_hsize_all;
	u2g_kahuka_mirror[SECTION_DATA] = (u2)u1g_flash_num_section;
	u2g_kahuka_mirror[TRQ_LEVEL_HIGH_SPEED] = (u2)u1g_flash_adjust_trq;
	u2g_kahuka_mirror[MAX_OPEN_PULSE] = u2g_flash_max_open_pulse;
	u2g_kahuka_mirror[FACT_FINISH] = (u2)u1g_flash_finish;
	a_vog_trqajst_trqinitial();
	
	check_check_sum();	
	check_size_check_sum();

	Fg_f_no_position = 1;
	
	u1g_num_section = (u1)u2g_kahuka_mirror[SECTION_DATA];
	h_size_m_ck();	
	
	u1g_num_section_kagen = (u1)((u2)s2g_size_ram[0] / (u2)(ONE_SEC_P));
	if( u1g_num_section_kagen >= MAX_SECTION )
		{
			u1g_num_section_kagen = MAX_SECTION;
		}
		
	else{}
	
	u2g_huka_jougen = u2g_kahuka_mirror[HUKA_UPPER];

	close_huka_data_set();
	open_huka_data_set();
	
	u2g_num_now = u2g_flash_num_openclose;		
	u2g_num_move = u2g_flash_num_move;		
}
void h_size_m_ck(void){
//	u1 k;
	s2g_size_ram[0] = (s2)u2g_kahuka_mirror[SIZE_RAM];	

	if(u1g_num_section <= MAX_SECTION)
		{
			if( (s2g_size_ram[0] != 0x0000)&&(s2g_size_ram[0] <= PULSE_MAX_SIZE) )
				{
					u1g_current_mode = 163;
					u1g_previous_mode = 163;
					s2g_cnt_plus = 0;
					u1g_Fg_close_huka_learn = 1;
				}
			else
				{
					s2g_size_ram[0] = 0x00;
					s2g_size_ram[1] = 0x00;
					s2g_size_ram[2] = 0x00;
#ifdef	START_NOMAL_MODE
					u1g_current_mode = 101;
					u1g_previous_mode = 101;
#else
					u1g_current_mode = 0;
					u1g_previous_mode = 0;
#endif
				}
		}
	else
		{
			s2g_size_ram[0] = 0x00;
			s2g_size_ram[1] = 0x00;
			s2g_size_ram[2] = 0x00;
#ifdef	START_NOMAL_MODE
			u1g_current_mode = 101;
			u1g_previous_mode = 101;
#else
			u1g_current_mode = 0;
			u1g_previous_mode = 0;
#endif
		}
}

void check_check_sum(void)
{
	s2 s2a_i = 0;
	u1 u1a_check_sum;

	u1a_check_sum = 0;
	for(s2a_i = 0; s2a_i < CHECK_SUM_HUKA; s2a_i++){
		u1a_check_sum = u1a_check_sum + (u1)(*(&u1g_flash_learndata_top + s2a_i));
	}
	
	if(u1a_check_sum != u1g_flash_checksum_huka){
		Fg_f_no_learn_data = 1;
		
		for( s2a_i = 0;s2a_i <= MAX_SECTION;s2a_i++ ){
			u2g_kahuka_mirror[s2a_i] = u2g_std_max_huka;
		}
		
		u2g_kahuka_mirror[OPEN_DATA] = u2g_open_std_max_huka;

		u2g_kahuka_mirror[HUKA_UPPER] = u2g_std_max_huka;
	}
	else{}
}


void check_size_check_sum(void)
{
	u1 u1a_check_sum_size = 0;

	u1a_check_sum_size = ((u1)0);
	
	u1a_check_sum_size = u1a_check_sum_size + u1g_flash_num_section;

	u1a_check_sum_size = u1a_check_sum_size + a_u1g_data_exchange0_word_to_byte(u2g_flash_hsize_all);
	u1a_check_sum_size = u1a_check_sum_size + a_u1g_data_exchange1_word_to_byte(u2g_flash_hsize_all);
		
	if(u1a_check_sum_size != u1g_flash_checksum_hsize){

		u1g_flash_num_section = (u1)0xf0;
	}
	else{}


}

void const_huka_hosei(void)
{
	if( u1g_temp_b_f_p_hugo == 0 )
		{
			u2g_max_const_huka = (u2)(u2g_max_const_huka + u2g_max_const_huka_hosei);
			u2g_open_std_max_huka = (u2)(u2g_open_std_max_huka + u2g_open_std_max_huka_hosei);
			u2g_osikomi_const_huka = (u2)(u2g_osikomi_const_huka + u2g_osikomi_const_huka_hosei);
			u2g_open_std_osikomi_huka = (u2)(u2g_open_std_osikomi_huka + u2g_open_std_osikomi_huka_hosei);
		}
	else
		{
			u2g_max_const_huka = (u2)(u2g_max_const_huka - u2g_max_const_huka_hosei);
			u2g_open_std_max_huka = (u2)(u2g_open_std_max_huka - u2g_open_std_max_huka_hosei);
			u2g_osikomi_const_huka = (u2)(u2g_osikomi_const_huka - u2g_osikomi_const_huka_hosei);
			u2g_open_std_osikomi_huka = (u2)(u2g_open_std_osikomi_huka - u2g_open_std_osikomi_huka_hosei);
		}
}

/*---------------------------------------------------------------------------------------*/
void check_count_reset(void){
	
	if(u1g_kahuka_input == 1){
		switch(u1g_current_mode){
			case 1:	
			case 2:	
			case 4:	
				s2g_cnt_plus = 0;
				break;
			case 12:
			case 13:
			case 22:
			case 23:
			case 24:
				a_vol_clear_upper_limit();
				break;
			case 103:
			case 107:
			case 116:
			case 117:
			case 118:
			case 119:
			case 120:
			case 125:
			case 161:
			case 166:
			case 173:
			case 174:
			case 181:
			case 185:
			case 193:
			case 194:
			case 195:
			case 198:

				a_vol_reset_upper_limit();
				break;
			default:
				break;
		}		
	}
	else{}
	check_jougen_count_clear();
}

static void a_vol_clear_upper_limit(void)
{
	if(s2g_cnt_plus < (s2)MAX_TRQ_H_HABA){

		s2g_cnt_plus = 0;
		u1g_full_open_input = 1;
	}
	else{}
}

static void a_vol_reset_upper_limit(void)
{
	if( u1g_f_learn_open_max_huka == 0 ){
		switch(u1g_current_mode){
			case 103:
			case 107:
				if(s2g_size_ram[0] > s2g_cnt_plus){
					if(s2g_cnt_plus > NORMAL_HABA){
						u1g_f_open_small_size = 1;
					}else if(s2g_cnt_plus < ((-1) * NORMAL_HABA)){
						u1g_f_open_large_size = 1;
					}
					else{}
					
					
					if((PULSE_MAX_SIZE - s2g_size_ram[0]) > ((-1) * s2g_cnt_plus)){
						s2g_size_ram[0] = s2g_size_ram[0] - s2g_cnt_plus;		
						s2g_lock_start_position = s2g_size_ram[0];
					}
					else{}
					u1g_num_section = (u1)( (u2)s2g_size_ram[0] / (u2)(ONE_SEC_P) );
					u1g_full_open_input = 1;
				}
				else{}
				break;
			default:
				break;
		}
	}
	else{}
	
	if(s2g_cnt_plus <= (s2)U2L_JOUGEN_KITEI_AREA ){
		if( u1g_f_learn_open_max_huka == 1 ){
			s2g_cnt_plus = 0;
		}
		u1g_full_open_input = 1;
	}
	else{}
}


void a_vog_error_status_store(u1 u1_mode,u1 u1_sig,u1 u1_error_state)
{
	u1g_temp_previous_mode	= u1_mode;			
	u1g_temp_signal = 	u1_sig;			
	u1g_temp_free_data = u1_error_state;	
}

void check_kamen_total(void)
{
	switch( u1g_current_mode ){
	case 106:
	case 108:
	case 121:
	case 122:
	case 162:
	case 182:
	case 189:
	case 190:

		if( s2g_cnt_plus >= s2g_size_ram[0] ){
			u1g_kamen_total_input = 1;
		}
		else{
			u1g_kamen_total_input = 0;
		}
		break;
	default:
		break;
	}
}

void process_key_3sw(void)
{
	if(u1g_key_3sw == 1){
		u1g_key_3sw = 0;
		switch( u1g_current_mode ){
			case 20:
			case 100:
			case 101:
			case 105:
			case 129:
			
				learn_fullclose_position();
				break;
			default:
			break;
		}
	}
	else{}
	
	
	if(u1g_key_3sw_jougen == 1){
		u1g_key_3sw_jougen = 0;
        
		if(Fg_f_reset_able == 1){
			soft_reset_main();
		} 
		else{
		}
		u1g_key_3sw_jougen = 0;
	}
	else{
		u1g_key_3sw_jougen = 0;
	}
	
}

void set_ope_state_f(void)
{
	switch(u1g_shutter_state){
		case SF_PRE_OPEN:
		case SF_PRE_CLOSE:
		case SF_PRE_SAI_OP:
		case SF_PRE_SAI_CL:
			u1g_ope_state_f = 0;
		break;
			
		case SF_OPEN:
		case SF_CLOSE:
		case SF_SAIKOU_OP:
		case SF_SAIKOU_CL:
		case SF_SOFT_OPEN:
		case SF_SOFT_CLOSE:
		case SF_SOFT_SAI_OP:
		case SF_SOFT_SAI_CL:
			u1g_ope_state_f = 1;
		break;
			
		case SF_BREAK:
			u1g_ope_state_f = 2;
		break;
			
		case SF_STOP:
			u1g_ope_state_f = 3;
		break;
		
		default:
			u1g_ope_state_f = 3;
		break;
	}
}


void error_ope_main(void){
	
	check_power_on_rireki();

	check_sol_short_error();

	check_uart_error();

	check_unknown_posi_error();

	check_open_learn_error();
	
	u2g_flash_num_openclose = u2g_num_now;	
	u2g_flash_num_move = u2g_num_move;		

	if( u1g_error_mode != ERR_NONE ){
		switch	( u1g_error_mode ){
			case	ERR_CLOSE_OVERLOAD:		
			case	ERR_SENS_ELEC:		
			case 	ERR_HIGH_SPEED:		
			case	ERR_HAND_MOVE:	
			case	ERR_THERMAL:	
			case	ERR_SOFT_RESET:		
			case 	ERR_POWER:			
			case	ERR_OPEN_OVERLOAD:	
			case	ERR_TIME_OVER:		
			case	ERR_ENCODER:		
			case	ERR_SOFT_ROCK_OUT:	
			case	ERR_H_SIZE_SET:		
			case	ERR_SOL_SHORT:		
			case	ERR_CLUTCH:			
			case	ERR_FET:			
			case	ERR_POWER_PORT:		
			case	ERR_TEMP_PORT:		
			
				calculate_error();	
				
				xn_flash_error_set1 = xn_flash_error_set0;
				u1g_flash_type_error = u1g_error_mode;				
				u1g_flash_previous_mode = u1g_temp_previous_mode;	
				u1g_flash_signal = u1g_temp_signal;			
				u1g_flash_free_data = u1g_temp_free_data;	
				u2g_flash_num_times = u2g_num_move;			

			case	ERR_POWER_ON:	
			
				set_20_rireki_data();
				
				if( (u1g_error_mode == ERR_POWER_PORT) && (u1g_Fg_temp_ad_error) ){
					u1g_error_mode = ERR_TEMP_PORT;		
					calculate_error();				
					
					xn_flash_error_set1 = xn_flash_error_set0;
					u1g_flash_type_error = u1g_error_mode;			
					u1g_flash_previous_mode = u1g_temp_previous_mode;	
					u1g_flash_signal = u1g_temp_signal;			
					u1g_flash_free_data = u1g_temp_free_data;	
					u2g_flash_num_times = u2g_num_move;			

					set_20_rireki_data();
				}
				else{}
			
				u1g_error_mode = ERR_NONE;
			
				u1g_flash_write_status = U1_SIZE_H_WRITE;

				break;
			default:
				u1g_error_mode = ERR_NONE;
				break;
		}
	
	}
	else{}
}

void check_open_learn_error(void){

	switch	( u1g_error_mode ){
		case	ERR_POWER_ON:		
		case 	ERR_HIGH_SPEED:	
		case	ERR_THERMAL:	
		case	ERR_TIME_OVER:	
		case	ERR_ENCODER:	
		case	ERR_FET:		

			if( (u1g_f_learn_open_max_huka == 0) && (u1g_current_mode >= 100) )
            {
				u1g_f_learn_open_max_huka = 1;	
				u1g_f_open_learn_comp = 1;
				set_error_open_learn_data();

				u1g_flash_write_status = U1_SIZE_HUKA_WRITE;
				ready_write_data();
			}
			else{}
				
			break;
		default:
			break;
	}
	
	return;
}

static void check_error_clear(void){

	static u2 u2a_clear_count = 0;	

	if( (req_uart_err.u1_uart_err_mode != ERR_NONE) && ( u1g_f_any_key_input == TRUE ) ){
		req_uart_err.u1_f_err_clear_wait = 1;
	}
	else{}

	if( req_uart_err.u1_f_err_clear_wait == 1 ){
		if( u2a_clear_count >= T4_5MS_AFTER_ERROR ){
			req_uart_err.u1_uart_err_mode = ERR_NONE;
			req_uart_err.u1_f_err_clear_wait = 0;	
		} else {
			u2a_clear_count++;
		}			
	} else {
		u2a_clear_count = 0;
	}
	
	return;
}

static void check_uart_error(void){

	switch	( u1g_error_mode ){
		case	ERR_CLOSE_OVERLOAD:	
		case	ERR_SENS_ELEC:		
		case 	ERR_HIGH_SPEED:		
		case	ERR_THERMAL:	
		case	ERR_TIME_OVER:	
		case	ERR_ENCODER:		
		case	ERR_SOFT_ROCK_OUT:	
		case	ERR_SOL_SHORT:	
		case	ERR_FET:		
		case	ERR_POWER_PORT:	
		case	ERR_TEMP_PORT:	

			req_uart_err.u1_uart_err_mode = u1g_error_mode;
			req_uart_err.u1_f_err_clear_wait = 0;
			break;
		default:
			break;
	}

	return;
}

static void check_unknown_posi_error(void)
{
	switch	(u1g_error_mode){
		case	ERR_THERMAL:		
		case	ERR_TIME_OVER:		
		case	ERR_ENCODER:	
		case	ERR_FET:			
			s2g_cnt_plus = 0;
			s2g_unknown_cnt_plus = 0;
			break;
		default:
			break;
	}

	return;
}

void check_pulse_event(void)
{
	static s2 s2a_pre_cnt_plus = 0;
	s2 s2a_temp_cnt_plus = 0;
	u1 u1a_f_open_pulse = 0;

	if( (u1g_f_input_pulse == 1) || (u1g_different_mode == 1)){
		if(u1g_f_input_pulse == 1){
			u1g_f_input_pulse = 0;
			pulse_in_operation();

			if(s2a_pre_cnt_plus > s2g_cnt_plus){
				u1a_f_open_pulse = 1;
			}
			else{}

			s2a_pre_cnt_plus = s2g_cnt_plus;
		}
		else{}

		if(s2g_cnt_plus > U2L_JOUGEN_KITEI_AREA){
			u1g_jougen_kitei_area_input = 1;
		}
		else{}
		
		if(s2g_cnt_plus >= (ONE_SEC_P + 1)){
			if(u1g_current_mode == 11){
				u1g_timer_5sec_input = 1;
			}
			else{}
		}
		else{}

		switch( u1g_current_mode ){
		case 5:
		case 28:
		case 104:
		case 126:
		case 176:
		case 177:
		case 196:
		case 197:
			if((s2g_cnt_plus - s2g_cnt_plus_start) >= S2L_P_END_PRECLOSE ){
				u1g_f_stop_shortclose = 1;
			}
			else{}
			break;
		default:
			break;
		}

		switch( u1g_current_mode ){
		case 23:
		case 174:
			if(( s2g_cnt_plus_start - s2g_cnt_plus) >= S2L_P_END_REVOPEN ){
				u1g_f_stop_shortopen = 1;
			}
			else{}
			break;
		default:
			break;
		}
	
		if ( (100 <= u1g_current_mode) && (u1g_current_mode <= 130) ){	

			if( s2g_cnt_plus < (s2g_size_ram[0] - S2L_P_THRESHOLD_50MM) ){
				u1g_f_50mm_range_out = 1;
			}else{
				u1g_f_50mm_range_out = 0;
			}
		}else{
			u1g_f_50mm_range_out = 0;
		}

		switch( u1g_current_mode ){
		case 128:
		case 130:
			if( s2g_cnt_plus < (s2)(s2g_lock_start_position - KAGEN_HANI) ){
				u1g_f_rangeout_kagen = 1;
			}
			else{}
			break;
		case 180:
		case 199:
			if( s2g_cnt_plus < (s2)(s2g_size_ram[0] - KAGEN_HANI) ){
				u1g_f_rangeout_kagen = 1;
			}
			else{}
			break;
		default:
			break;
		}

		if( u1g_current_mode < 160){	
			if( s2g_cnt_plus >= (s2)(s2g_lock_start_position - KAGEN_HANI) ){
				u1g_f_rangein_kagen_kitei = 1;
			}else{
				u1g_f_rangein_kagen_kitei = 0;
			}
		}else{					
			if( s2g_cnt_plus >= (s2)(s2g_size_ram[0] - KAGEN_HANI) ){
				u1g_f_rangein_kagen_kitei = 1;
			}else{
				u1g_f_rangein_kagen_kitei = 0;
			}
		}

		switch( u1g_current_mode ){
		case 121:
		case 122:
		case 169:
		case 170:
		case 189:
		case 190:
			if( s2g_cnt_plus >= (s2)s2g_lock_start_position ) {
				u1g_f_complete_lock = 1;
			}
			break;
		default:
			break;
		}

		switch( u1g_current_mode ){
		case 109:
		case 110:
			if( (s2g_cnt_plus <= (s2)(s2g_lock_start_position - S2L_THRESHOLD_LOCKOUTPUT)) && (u1a_f_open_pulse == 1) ){
				u1g_f_start_lock_output = 1;
			}
			else{}
			break;
		case 163:
		case 164:
			if( (s2g_cnt_plus <= (s2)(0 - S2L_THRESHOLD_TEIDEN_LOCKOUTPUT )) && (u1a_f_open_pulse == 1) ){
				u1g_f_start_lock_output = 1;
			}
			else{}
			break;
		case 183:
		case 184:
			if( (s2g_cnt_plus <= (s2)(s2g_lock_start_position - S2L_THRESHOLD_TEIDEN_LOCKOUTPUT)) && (u1a_f_open_pulse == 1) ){
				u1g_f_start_lock_output = 1;
			}
			else{}
			break;
		default:
			break;
		}
	}
	else{}

	u1g_Fg_copy_jougen_area = u1g_Fg_jougen_area;
	if((u1g_current_mode >= 160) && (u1g_current_mode < 180)){	
		s2a_temp_cnt_plus = s2g_unknown_cnt_plus + s2g_size_ram[0];	
	}else{
		s2a_temp_cnt_plus = s2g_cnt_plus;
	}

	if((u1g_current_mode >= 100) && (s2a_temp_cnt_plus <= U2L_JOUGEN_KITEI_AREA )){
		u1g_Fg_jougen_area = 1;
	} else {
		u1g_Fg_jougen_area = 0;
	}
}

void set_pwm_limit_filter(void){
	
	u2 u2a_d_pwm_max_limit = 0;
	
	if( u2g_d_pwm > 0 ){ 
		if( u1g_Fg_soft_lock_out_duty == 0){
			u2a_d_pwm_max_limit = D_PWM_MAX_NORMAL;
		}
		else{
			u2a_d_pwm_max_limit = D_PWM_MAX_SOFT_LOCK;	
		}
		
		if( u2g_d_pwm > (u2)u2a_d_pwm_max_limit){
			u2g_d_pwm = u2a_d_pwm_max_limit;
		}
		else{}
	}			
	else{
		u2g_d_pwm = D_PWM_MIN;				
	}
}	


void check_jougen_count_clear(void){
	
	switch( u1g_current_mode ){
		case 20:
		case 21:
		case 100:
		case 101:
		case 102:
		case 122:
		case 129:
		case 160:
		case 165:
		case 170:

			u1g_Fg_previous_kahuka_upper = 0;
		break;
		default:
		break;
	}
}
static void a_vol_clear_reset_command(void)
{	
	if(Fg_f_reset_able == 1){		

		if((u1g_mode >= U1G_OPEN_MODE) && (u1g_mode <= U1G_OSIKIRI_CLOSE_MODE)){
			if(s2g_cnt_plus <= (s2g_cnt_plus_start - (s1)PULSE_CLEAR_RESET_FLAG) ){
				Fg_f_reset_able = 0;
			}
			else{}
			
			if(s2g_cnt_plus >= (s2g_cnt_plus_start + (s1)PULSE_CLEAR_RESET_FLAG) ){
				Fg_f_reset_able = 0;
			}
			else{}
		}
		else if(u1g_mode == U1G_STOP_MODE){
			if(s2g_cnt_plus <= (s2g_cnt_plus_start_for_stop - (s2)HAND_ERROR) ){
				Fg_f_reset_able = 0;
			}
			else{}
			
			if(s2g_cnt_plus >= (s2g_cnt_plus_start_for_stop + (s2)HAND_ERROR) ){
				Fg_f_reset_able = 0;
			}
			else{}
		}
		else{}
	}
	else{}
	
}

static void a_vol_motor_huka_setting(void)
{
	u2g_max_const_huka = u2g_ajst_max_huka;			
	u2g_open_std_max_huka = u2g_ajst_open_max_huka;			
	u2g_osikomi_const_huka = u2g_ajst_osikomi_const_huka;	
	u2g_open_std_osikomi_huka = u2g_ajst_open_std_osikomi_huka;	
//	/* const_huka_hosei(); 補正はAD変換時に行う */
}

static void check_break_enable_time(void)
{
	if(u1g_Fg_break_enable_counter > 10){ //4.5ms * 11 = 50ms
		
		u1g_Fg_break_enable_time  = 1;
		u1g_Fg_break_enable_counter = 0;
	}
	
	u1g_Fg_break_enable_counter ++;
}

static void check_break_stop(void)
{
	if(u1g_Fg_break_over_stop == 1)
    {
		Fg_osikiri_open = 0;
		Fg_osikiri_close = 0;
		u1g_key_3sw = 0;
		Fg_key_open = 0;
		Fg_key_close = 0;
		Fg_key_stop = 1;
	}
}
	
static void check_power_on_rireki(void)
{
	if( u1g_Fg_power_on == 1){	
		
		if( ( ( u1g_flash_type_error_20 == ERR_POWER_ON) && ( u2g_flash_num_times_20 != u2g_num_move ) ) ||
			( u1g_flash_type_error_20 != ERR_POWER_ON ) )
        {
			//if( u1g_Fg_error_mode_3_write_check == 1 ){
		
				if( u2g_ad_now[(VER - CURR)] >= POWER_85V ){	//85V
					u1g_error_mode = ERR_POWER_ON;	
					a_vog_error_status_store(u1g_current_mode,u1g_signal,u1g_current_mode);
					u1g_Fg_error_mode_3_write_check = 0;
					u1g_Fg_power_on = 0;
			
				}
				else{}
			//}
		}
		else{
			u1g_Fg_power_on = 0;
		}
	}
	else{}
}

void set_20_rireki_data(void)
{
	xn_flash_error_20_set19 = xn_flash_error_20_set18;
	xn_flash_error_20_set18 = xn_flash_error_20_set17;
	xn_flash_error_20_set17 = xn_flash_error_20_set16;
	xn_flash_error_20_set16 = xn_flash_error_20_set15;
	xn_flash_error_20_set15 = xn_flash_error_20_set14;
	xn_flash_error_20_set14 = xn_flash_error_20_set13;
	xn_flash_error_20_set13 = xn_flash_error_20_set12;
	xn_flash_error_20_set12 = xn_flash_error_20_set11;
	xn_flash_error_20_set11 = xn_flash_error_20_set10;
	xn_flash_error_20_set10 = xn_flash_error_20_set9;
	xn_flash_error_20_set9 = xn_flash_error_20_set8;
	xn_flash_error_20_set8 = xn_flash_error_20_set7;
	xn_flash_error_20_set7 = xn_flash_error_20_set6;
	xn_flash_error_20_set6 = xn_flash_error_20_set5;
	xn_flash_error_20_set5 = xn_flash_error_20_set4;
	xn_flash_error_20_set4 = xn_flash_error_20_set3;
	xn_flash_error_20_set3 = xn_flash_error_20_set2;
	xn_flash_error_20_set2 = xn_flash_error_20_set1;
	xn_flash_error_20_set1 = xn_flash_error_20_set0;
	
	u1g_flash_type_error_20 = u1g_error_mode;		
	u1g_flash_free_data_20 = u1g_temp_free_data;	
	u2g_flash_num_times_20 = u2g_num_move;			
}

static void open_huka_data_set(void){
	
	u1 u1l_j = 0;
	u1 u1a_fg_end_learn_open = 0;
	u2 u2a_learn_open_max_huka = 0;
	
	if(u1g_flash_learn_open_fg == U1_NON_VALUE){
		u1g_f_open_learn = 0x00;
	}else{
		u1g_f_open_learn = u1g_flash_learn_open_fg;
	}

	if( u1g_num_section <= MAX_SECTION ){
		if( u1g_f_open_learn_comp == 0 ){
			u1a_fg_end_learn_open = 0;		
		}
		else{
			u1a_fg_end_learn_open = 1;
		}
	}
	else{
		u1a_fg_end_learn_open = 0;
	}
	
	
	if( u1a_fg_end_learn_open != 1 ){
		u1g_f_learn_open_max_huka = 0;	
		u1g_num_section = 0;
	
		for( u1l_j = 0;u1l_j <= MAX_SECTION;u1l_j++){
			u2g_open_over_lev_b[u1l_j][4] = u2g_open_std_max_huka;
		}
		u2g_jougen_open_over_lev_b = u2g_open_std_max_huka;
		u2g_learn_buffer = u2g_max_const_huka;
	}
	else{	
		u1g_f_learn_open_max_huka = 1;	
		if(u2g_kahuka_mirror[ADD_OPEN_LEARN_FG] == 1){	
			u2a_learn_open_max_huka = u2g_open_std_max_huka;
		}
		else{
			u2a_learn_open_max_huka = u2g_kahuka_mirror[OPEN_DATA];
		}
		
		for( u1l_j = 0;u1l_j <= MAX_SECTION;u1l_j++){
			u2g_open_over_lev_b[u1l_j][0] = u2a_learn_open_max_huka;
			u2g_open_over_lev_b[u1l_j][4] = u2a_learn_open_max_huka;
		}
		u2g_jougen_open_over_lev_b = u2a_learn_open_max_huka;	
		u2g_keep_jougen_open_over_lev_b = u2a_learn_open_max_huka;

		u2g_cal_b = u2a_learn_open_max_huka;
		plus_a_cal_open();
		u2g_learn_buffer = u2a_learn_open_max_huka;
	}
	
	
}

static void close_huka_data_set(void){
	
	u1 u1l_j = 0;

	if(u1g_flash_learn_open_fg == U1_NON_VALUE){
		u1g_f_open_learn = 0x00;
	}else{
		u1g_f_open_learn = u1g_flash_learn_open_fg;
	}
	
	if( (u1g_num_section != 0)&&(u1g_num_section <= MAX_SECTION) )
    {
        Fg_f_end_learn = 1;	
    }
	else{}
	if( Fg_f_end_learn != 1 ){
		u1g_num_section = 0;
	
		for( u1l_j = 0;u1l_j <= MAX_SECTION;u1l_j++){
			u2g_over_lev_b[u1l_j][4] = u2g_std_max_huka;
		}
	}
	else{
		u2g_learn_buffer_close = 0;
		for( u1l_j = 0;u1l_j <= u1g_num_section;u1l_j++){
			if(u2g_learn_buffer_close < u2g_kahuka_mirror[u1l_j]){
				u2g_learn_buffer_close = u2g_kahuka_mirror[u1l_j];
			}
			else{}
		}

		for( u1l_j = 0;u1l_j <= MAX_SECTION;u1l_j++){
			u2g_over_lev_b[u1l_j][4] = u2g_learn_buffer_close;
		}

		if( u1g_num_section != (u1)((u2)(s2g_size_ram[0] - s2g_size_ram[2]) / (u2)(ONE_SEC_P)))
        {
			rest_ready_write_data();
//			u1g_flash_adjust_trq = U1_NON_VALUE;
			u1g_flash_write_status = U1_SIZE_H_WRITE;
			u1g_f_reset_after_write = 1;
			return;
		}
		else{}
		make_std_learn();
		u1g_f_learn_close_all_huka = u1g_f_close_learn_comp;
	}
}
static void soft_lock_signal(void)
{
	switch( u1g_current_mode )
    {
		case 121:
		case 169:
		case 189:
			u1g_kahuka_input = 0;
			break;
		default:
		break;
	}
}
