#include "Sys.h"
#include "def_local.h"
#include "comm_uart.h"
#include "variables.h"
#include <string.h>
#include "access_flash.h"
#include "a_data_exchange.h"
#include "flash_data_read.h"
#include "functions.h"
#include "trq_adjust_trqchange.h"
#include "anjou_test.h"
#include "Timer.h"
/**************************************************************************************************/

static u1 u1l_fact_finish = 0;					
static u1 u1l_step_torque_test = 0;				
//static s2 s2l_cnt_p_trq_test = 0;			
static u1 u1l_step_denki_test = 0;				
static u2 u2l_total_timer_counter = 0;			

#if 0	
static u1 u1l_fact_write = 0;		
static u1 u1l_step_koutei_ope = 0;	

static u2 u2l_timer_counter = 0;		
static u1 u1l_step_ver_output = 0;	
#endif
static u1 u1l_step_test_change = 0;		
static u1 u1l_stop_count = 0;			

/* Definition of RAM area */
#define S2L_TEST_START_PULSE			((s2)(-100))
#define U1L_FREEZE_STATE				(u1)0xff	

#define U1L_TOTAL_TIMER_TRQ_MODE_SEC	(u1)180		
#define U2L_TIME_PULSE_INPUT			(u2)2333	
#define U2L_TIME_START_VER_DOWN			(u2)3600	
#define U2L_TIME_VER_UP					(u2)2456	
#define U2L_TIME_VER_DOWN_STABLE		(u2)111		
#define U2L_TIME_VER_UP_STABLE			(u2)177		
#define U2L_TIME_TRQ_OK_MIN				(u2)111		
#define U2L_TIME_TRQ_OK_MAX				(u2)800		
#define U2L_TIME_TRQ_UP_MAX				(u2)1467	
#define U2L_TIME_TRQ_DOWN_MAX			(u2)2667	
#define U2L_TIME_RELEASE_ELEC_START		(u2)222		

#define U1L_WAIT_DOUKI_CHECKING			(u1)0		
#define U1L_WAIT_DOUKI_OK				(u1)1	
#define U1L_WAIT_DOUKI_NG				(u1)2	

/* 電気テスターモード用 */
#define U1L_TOTAL_TIMER_DENKI_MODE_SEC	(u1)90		
#define U2L_TIME_WAIT_POWER_CHECK		(u2)444		
#define U2L_TIME_VIBRATION_CHECK		(u2)2333	
#define U2L_TIME_STOP_KEEP				(u2)444		
#define U2L_TIME_ENCODER_CHECK			(u2)888		
#define U2L_TIME_TESTER_RESPONSE		(u2)666		
#define U2L_TIME_DIR_CHECK_WAIT			(u2)444		
#define U2L_TIME_WIRELESS_TIMEOUT		(u2)2222	

#if 0	
#define U2L_TIME_KOUTEI_KYOKA			(u2)2222	
#define U1L_OPE_KOUTEI_KYOKA			(u1)1		
#define U1L_OPE_KOUTEI_LOCK				(u1)2		
#define U1L_SW_OPE_NUM					(u1)3		
#endif

#define POWER_103V_MAX					700			
#define POWER_97V_MIN					542			
#define POWER_78V_MAX					532			
#define POWER_72V_MIN					397			

#if 0	
#define U2L_TIME_VERSION_CHECK			(u2)2222	
#define U1L_VERSION_BUZZER_COUNT		(u1)1		
#define U2L_TIME_BUZZER_INTERVAL		(u2)177		
#endif	
#define U1L_COMP_STOP_COUNT				(u1)3		

static void ready_torque_tester_mode(void);
static void torque_tester_mode(void);
static void torque_tester_release_elec(void);
static void trq_test_100v_wait(void);
static void trq_test_ver_down_wait(void);
static void trq_test_pulse_in_wait(void);
static void trq_test_ver_up_wait(void);
static void trq_test_start(void);
static void trq_test_module_connect(void);
static void trq_test_open_kahuka_wait(void);
static void trq_test_open_trq_adjust(void);
static void trq_test_close_kahuka_wait(void);
static void trq_test_close_trq_adjust(void);
static void trq_test_rev_trq_wait(void);
static u1 wait_tester_douki(void);
static u1 check_torque_adjust(void);


static void denki_tester_mode(void);
static void denki_test_start(void);
static void denki_test_100v_wait(void);
static void denki_test_power_check_wait(void);
static void denki_test_open_vib_check(void);
static void denki_test_open_stop_wait(void);
static void denki_test_close_vib_check(void);
static void denki_test_close_stop_wait(void);
static void denki_test_encoder_check(void);
static void denki_test_learn_stop(void);
static void denki_test_learn_check(void);
static void denki_test_signal_wait(void);
static void denki_test_signal_ans_wait(void);

#if 0	
static void check_koutei_write(void);
static void check_koutei_sw_input(void);
static void check_version_output(void);
static void check_version_stop_in_wait(void);
static void check_version_ver_output(void);
#endif	
static void check_test_mode_change(void);
static void check_test_mode_stop_in_wait(void);
static void change_tester_mode(void);


void anjou_test_signal(void)
{
	if(u2l_total_timer_counter < U2L_VALUE_FFFF){
		u2l_total_timer_counter++;
	}
	else{}

	switch(u1l_fact_finish){
		case FACT_INIT_TORQUE_MODE:	
		case FACT_TORQUE_MODE:		
			if( u1l_step_torque_test <= TRQ_TEST_START_FAIL ){
				ready_torque_tester_mode();
			} else {
				torque_tester_mode();
			}
			
			torque_tester_release_elec();
			break;
		case FACT_DENKI_MODE:	
			denki_tester_mode();
			break;
		default:
			
			break;
	}
}


void anjou_test_initial(u1 u1a_flash_finish)
{
	u1l_fact_finish = u1a_flash_finish;
	u1l_step_torque_test = TRQ_TEST_POWER_ON;
	u1l_step_denki_test = DENKI_TEST_START;
	u2l_total_timer_counter = 0;
	u1g_uart_buzzer_order = U1G_ORDER_NO_BUZZER;
	u1g_f_release_elec = FALSE;
}

u1 check_torque_test_exec(void)
{
	u1 u1a_torque_test_state = 0;

	
	switch(u1l_fact_finish){
		case FACT_INIT_TORQUE_MODE:
		case FACT_TORQUE_MODE:	
			if( u1l_step_torque_test < TRQ_TEST_START_FAIL ){
				u1a_torque_test_state = U1G_FACT_TRQ_START_ACCEPT;
			} else if( (u1l_step_torque_test == TRQ_TEST_START_FAIL) || (u1l_step_torque_test == U1L_FREEZE_STATE) ){
				u1a_torque_test_state = U1G_FACT_TRQ_STOP;
			} else {
				u1a_torque_test_state = U1G_FACT_TRQ_EXEC;
			}
			break;
		default:
			u1a_torque_test_state = U1G_FACT_TRQ_STOP;
			break;
	}
	return u1a_torque_test_state;
}

void cansel_torque_tester_mode(void)
{
	u1l_step_torque_test = TRQ_TEST_START_FAIL;
	return;
}

static void ready_torque_tester_mode(void)
{
	
	if( u1g_f_any_key_input || (100 <= u1g_current_mode) ){
		cansel_torque_tester_mode();
	}
	else{}
	
	switch(u1l_step_torque_test){

		case TRQ_TEST_POWER_ON:			
			u2l_total_timer_counter = 0;
			u1g_f_ok_set_on_shortbreak = FALSE;		
			u1l_step_torque_test++;
			break;
		case TRQ_TEST_100V_WAIT:	
			trq_test_100v_wait();
			break;
		case TRQ_TEST_VER_DOWN_WAIT:
			trq_test_ver_down_wait();
			break;
		case TRQ_TEST_PULSE_IN_WAIT:
			trq_test_pulse_in_wait();
			break;
		case TRQ_TEST_VER_UP_WAIT:	
			trq_test_ver_up_wait();
			break;
		case TRQ_TEST_START_FAIL:	
			u1g_f_ok_set_on_shortbreak = TRUE;		
			break;
		default:
			u1g_f_ok_set_on_shortbreak = TRUE;		
			break;
	}
}

static void torque_tester_mode(void)
{
	check_test_mode_change();

	if(u1g_current_mode == 9){
		return;
	}
	else{}

	if(u2g_systimer_1sec_timer_for_anjou >= U1L_TOTAL_TIMER_TRQ_MODE_SEC)
	{
		u1l_step_torque_test = U1L_FREEZE_STATE;
	}
	else{}
	
	switch(u1l_step_torque_test){
		case TRQ_TEST_START:				
			trq_test_start();
			break;
		case TRQ_TEST_MODULE_CONNECT:	
			trq_test_module_connect();
			break;
		case TRQ_TEST_OPEN_KAHUKA_WAIT:		
			trq_test_open_kahuka_wait();
			break;
		case TRQ_TEST_OPEN_TRQ_ADJUST:		
			trq_test_open_trq_adjust();
			break;
		case TRQ_TEST_CLOSE_KAHUKA_WAIT:	
			trq_test_close_kahuka_wait();		
			break;
		case TRQ_TEST_CLOSE_TRQ_ADJUST:	
			trq_test_close_trq_adjust();
			break;
		case TRQ_TEST_REV_TRQ_WAIT:		
			trq_test_rev_trq_wait();
			break;
		default:		
			u1g_current_mode = 9;
			break;
	}
}

/********************************************************/
static void torque_tester_release_elec(void)
{
	static u2 u2l_release_timer_counter = 0;	

	switch(u1l_step_torque_test){
		case TRQ_TEST_VER_DOWN_WAIT:		
		case TRQ_TEST_PULSE_IN_WAIT:	
		case TRQ_TEST_VER_UP_WAIT:		
		
			u1g_f_release_elec = TRUE;
			break;
		case TRQ_TEST_POWER_ON:			
		case TRQ_TEST_100V_WAIT:		
		case TRQ_TEST_START:			
		case TRQ_TEST_MODULE_CONNECT:	
		case TRQ_TEST_OPEN_KAHUKA_WAIT:	
		case TRQ_TEST_CLOSE_KAHUKA_WAIT:
			
			u1g_f_release_elec = FALSE;
			u2l_release_timer_counter = 0;
			break;
		case TRQ_TEST_OPEN_TRQ_ADJUST:		
		case TRQ_TEST_CLOSE_TRQ_ADJUST:	
			
			if(u2l_release_timer_counter >= U2L_TIME_RELEASE_ELEC_START){
				
				u1g_f_release_elec = TRUE;
			}
			else{
				u2l_release_timer_counter++;
				u1g_f_release_elec = FALSE;
			}
			break;
		case TRQ_TEST_REV_TRQ_WAIT:			
			
			u1g_f_release_elec = TRUE;
			break;
		case TRQ_TEST_START_FAIL:		
		case U1L_FREEZE_STATE:			
		default:
			
			u1g_f_release_elec = FALSE;
			break;
	}
}

static void trq_test_100v_wait(void)
{
	if( (POWER_97V_MIN <= u2g_ad_now[(VER - CURR)]) && (u2g_ad_now[(VER - CURR)] < POWER_103V_MAX) ) {		
		if(u2l_total_timer_counter >= U2L_TIME_VER_UP_STABLE){
			u2l_total_timer_counter = 0;
			u1l_step_torque_test++;
		}
		else{}
	}else{
		u2l_total_timer_counter = 0;
	}
}


static void trq_test_ver_down_wait(void)
{
	static u2 u2l_timeout_counter = 0;					
	
	if( (POWER_72V_MIN <= u2g_ad_now[(VER - CURR)]) && (u2g_ad_now[(VER - CURR)] < POWER_78V_MAX) ){		
		if(u2l_total_timer_counter >= U2L_TIME_VER_DOWN_STABLE){
			
			s2g_cnt_p_trq_test = 0;
				
			u2l_total_timer_counter = 0;
			u1l_step_torque_test++;
		}
		else{}
	}else{
		u2l_total_timer_counter = 0;
	}

	
	if(u2l_timeout_counter >= U2L_TIME_START_VER_DOWN){
		u1l_step_torque_test = TRQ_TEST_START_FAIL;
	}else{
		u2l_timeout_counter++;
	}
}


static void trq_test_pulse_in_wait(void)
{
	if( (POWER_72V_MIN <= u2g_ad_now[(VER - CURR)]) && (u2g_ad_now[(VER - CURR)] < POWER_78V_MAX) ){		
		
		if(s2g_cnt_p_trq_test <= S2L_TEST_START_PULSE){
			u2l_total_timer_counter = 0;
			u1l_step_torque_test++;
		}
		else{}
	} else {
		s2g_cnt_p_trq_test = 0;
	}

	
	if(u2l_total_timer_counter >= U2L_TIME_PULSE_INPUT){
		u1l_step_torque_test = TRQ_TEST_START_FAIL;
	}
	else{}
}


static void trq_test_ver_up_wait(void)
{
	static u2 u2l_timeout_counter = 0;					
	
	if( (POWER_97V_MIN <= u2g_ad_now[(VER - CURR)]) && (u2g_ad_now[(VER - CURR)] < POWER_103V_MAX) ) {	
		if( (u2l_total_timer_counter >= U2L_TIME_VER_UP_STABLE) && (u1g_current_mode == 0) ){

			u1l_step_torque_test = TRQ_TEST_START;
		}
		else{}
	}else{
		u2l_total_timer_counter = 0;
	}

	if(u2l_timeout_counter >= U2L_TIME_VER_UP){
		u1l_step_torque_test = TRQ_TEST_START_FAIL;
	}else{
		u2l_timeout_counter++;
	}
}



static void trq_test_start(void)
{
	u1g_current_mode = 7;
	
	reset_flash_learndata();
	u1g_flash_write_status = U1_SIZE_HUKA_WRITE;

	
	u2g_systimer_1ms_timer_for_anjou = U1L_ZERO;
	u2g_systimer_1sec_timer_for_anjou = U1L_ZERO;
	u2l_total_timer_counter = 0;

	uart_fact_trq_test();

	u1g_f_ok_set_on_shortbreak = TRUE;	
	
	u1l_step_torque_test++;
}


static void trq_test_module_connect(void)
{
	if( Fg_uart_fact_finish_trq_test == TRUE ){
		u2l_total_timer_counter = 0;
		
		u1l_step_torque_test++;
	}
	else{}

	if( Fg_uart_fact_error == TRUE ){
		u1l_step_torque_test = U1L_FREEZE_STATE;
	}
	else{}
}


static void trq_test_open_kahuka_wait(void)
{
	bool find_learndata = FALSE;
	
	if( (u1g_kahuka_input == 1) && (Fg_pwm_out == 1) ){
	
		
		
		find_learndata = check_flash_learndata();		
	
		
		if(find_learndata == TRUE){
			
			u1l_step_torque_test = U1L_FREEZE_STATE;
		}else{
			u2l_total_timer_counter = 0;
			
			u1l_step_torque_test++;
		}			
	}
	else{}
}


static void trq_test_open_trq_adjust(void)
{
	u1 u1a_result_trq_ajst = 0;

	u1a_result_trq_ajst = check_torque_adjust();
	
	switch(u1a_result_trq_ajst){

		case U1L_TRQ_AJST_OK:	
			
			u1g_current_mode = 8;

			u1l_step_torque_test++;
			break;
		case U1L_TRQ_AJST_UP:		
		case U1L_TRQ_AJST_DOWN:		
			
			u1g_current_mode = 7;

			u2l_total_timer_counter = 0;
			u1l_step_torque_test = TRQ_TEST_OPEN_KAHUKA_WAIT;	
			break;
		case U1L_TRQ_AJST_NG:	
			
			u1l_step_torque_test = U1L_FREEZE_STATE;
			break;
		default:				
			break;
	}
}

static void trq_test_close_kahuka_wait(void)
{
	if( (u1g_kahuka_input == 1) && (Fg_pwm_out == 1) ){
		
		u2l_total_timer_counter = 0;

		u1l_step_torque_test++;
	}
	else{}
}


static void trq_test_close_trq_adjust(void)
{
	u1 u1a_result_trq_ajst = 0;

	u1a_result_trq_ajst = check_torque_adjust();
	
	switch(u1a_result_trq_ajst){

		case U1L_TRQ_AJST_OK:	
			u1g_current_mode = 6;

			u2l_total_timer_counter = 0;
			u1l_step_torque_test++;
			break;
		case U1L_TRQ_AJST_UP:	
		case U1L_TRQ_AJST_DOWN:	
			
			u1g_current_mode = 7;

			u2l_total_timer_counter = 0;
			u1l_step_torque_test = TRQ_TEST_OPEN_KAHUKA_WAIT;	
			break;
		case U1L_TRQ_AJST_NG:	
		
			u1l_step_torque_test = U1L_FREEZE_STATE;
			break;
		default:				
			break;
	}
}

static void trq_test_rev_trq_wait(void)
{
	u1 u1a_result_douki = 0;

	u1a_result_douki = wait_tester_douki();
	
	switch(u1a_result_douki){
		case U1L_WAIT_DOUKI_OK:	
			
			u1g_flash_finish = FACT_DENKI_MODE;	
			u1g_flash_write_status = U1_FACT_WRITE;

		
			u1l_step_torque_test = U1L_FREEZE_STATE;
			break;
		case U1L_WAIT_DOUKI_NG:		
		
			u1l_step_torque_test = U1L_FREEZE_STATE;
			break;
		default:				
			break;
	}
}


static u1 wait_tester_douki(void)
{
	static u1 u1l_step_test_douki = TEST_DOUKI_START_CHECK;			
	static u2 u2l_low_ver_counter = 0;								
	u1 u1a_check_wait_comp = U1L_WAIT_DOUKI_CHECKING;

	switch(u1l_step_test_douki){
	
		case TEST_DOUKI_START_CHECK:		
			if( (POWER_72V_MIN <= u2g_ad_now[(VER - CURR)]) && (u2g_ad_now[(VER - CURR)] < POWER_78V_MAX) ){		/* 電源電圧が75V±3V */
				u2l_low_ver_counter++;
				
				u1l_step_test_douki++;
			}else{
				u2l_low_ver_counter = 0;
			}
			
			break;
		default:	
			if( (POWER_97V_MIN <= u2g_ad_now[(VER - CURR)]) && (u2g_ad_now[(VER - CURR)] < POWER_103V_MAX) ) {		/* 電源電圧が100V±3V */
				if(u2l_low_ver_counter < U2L_TIME_TRQ_OK_MIN){			
				
				}
				else if(u2l_low_ver_counter < U2L_TIME_TRQ_OK_MAX){		
					
					u1a_check_wait_comp = U1L_WAIT_DOUKI_OK;
				}
				else{													
				
					u1a_check_wait_comp = U1L_WAIT_DOUKI_NG;
				}
				u1l_step_test_douki = TEST_DOUKI_START_CHECK;			
				u2l_low_ver_counter = 0;
			}else if( (POWER_72V_MIN <= u2g_ad_now[(VER - CURR)]) && (u2g_ad_now[(VER - CURR)] < POWER_78V_MAX) ){		/* 電源電圧が75V±3V */
				if(u2l_low_ver_counter < U2L_VALUE_FFFF){
					u2l_low_ver_counter++;
				}
				else{}
			}else{
			
			}
			break;
	}
	return u1a_check_wait_comp;
}



static u1 check_torque_adjust(void)
{
	static u1 u1l_step_torque_douki = TRQ_ADJUST_VER_DOWN_CHECK;	
	static u2 u2l_low_ver_counter = 0;							
	u1 u1a_check_result = U1L_TRQ_AJST_CHECKING;

	switch(u1l_step_torque_douki){
	
		case TRQ_ADJUST_VER_DOWN_CHECK:	
			
			if( (POWER_72V_MIN <= u2g_ad_now[(VER - CURR)]) && (u2g_ad_now[(VER - CURR)] < POWER_78V_MAX) ){		/* 電源電圧が75V±3V */
				u2l_low_ver_counter++;
			
				u1l_step_torque_douki++;
			}else{
				u2l_low_ver_counter = 0;
			}
		
			break;
		default:		
			if( (POWER_97V_MIN <= u2g_ad_now[(VER - CURR)]) && (u2g_ad_now[(VER - CURR)] < POWER_103V_MAX) ) {		/* 電源電圧が100V±3V */
				if(u2l_low_ver_counter < U2L_TIME_TRQ_OK_MIN){			
				
				}
				else if(u2l_low_ver_counter < U2L_TIME_TRQ_OK_MAX){	
				
					u1a_check_result = U1L_TRQ_AJST_OK;
				}
				else if(u2l_low_ver_counter < U2L_TIME_TRQ_UP_MAX){		
				
					u1a_check_result = U1L_TRQ_AJST_UP;
					a_vog_trqajst_dataset(U1L_TRQ_AJST_UP);
				}
				else if(u2l_low_ver_counter < U2L_TIME_TRQ_DOWN_MAX){
				
					u1a_check_result = U1L_TRQ_AJST_DOWN;
					a_vog_trqajst_dataset(U1L_TRQ_AJST_DOWN);
				}
				else{												
				
					u1a_check_result = U1L_TRQ_AJST_NG;
				}
				u1l_step_torque_douki = TRQ_ADJUST_VER_DOWN_CHECK;		
				u2l_low_ver_counter = 0;
			}else if( (POWER_72V_MIN <= u2g_ad_now[(VER - CURR)]) && (u2g_ad_now[(VER - CURR)] < POWER_78V_MAX) ){		/* 電源電圧が75V±3V */
				if(u2l_low_ver_counter < U2L_VALUE_FFFF){
					u2l_low_ver_counter++;
				}
				else{}
			}else{
			
			}
			
			break;
	}
	return u1a_check_result;
}



u1 check_denki_test_exec(void)
{
	u1 u1a_denki_test_state = 0;

	switch(u1l_fact_finish){
		case FACT_DENKI_MODE:	
			if( u1l_step_denki_test == U1L_FREEZE_STATE ){
				u1a_denki_test_state = U1G_FACT_DENKI_STOP;
			} else {
				u1a_denki_test_state = U1G_FACT_DENKI_EXEC;
			}
			break;
		default:
			u1a_denki_test_state = U1G_FACT_DENKI_STOP;
			break;
	}
	return u1a_denki_test_state;
}

static void denki_tester_mode(void)
{
	
	check_test_mode_change();

	
	if(u1g_current_mode == 9){
		return;
	}
	else{}


	if(u2g_systimer_1sec_timer_for_anjou >= U1L_TOTAL_TIMER_DENKI_MODE_SEC)
	{
		u1l_step_denki_test = U1L_FREEZE_STATE;
	}
	else{}
	
	switch(u1l_step_denki_test){
		case DENKI_TEST_START:			
			denki_test_start();
			break;
		case DENKI_TEST_100V_WAIT:		
			denki_test_100v_wait();
			break;
		case DENKI_TEST_POWER_CHECK_WAIT:
			denki_test_power_check_wait();
			break;
		case DENKI_TEST_OPEN_VIB_CHECK:	
			denki_test_open_vib_check();
			break;
		case DENKI_TEST_OPEN_STOP_WAIT:		
			denki_test_open_stop_wait();
			break;
		case DENKI_TEST_CLOSE_VIB_CHECK:	
			denki_test_close_vib_check();
			break;
		case DENKI_TEST_CLOSE_STOP_WAIT:	
			denki_test_close_stop_wait();
			break;
		case DENKI_TEST_ENCODER_CHECK:	
			denki_test_encoder_check();
			break;
		case DENKI_TEST_LEARN_STOP:		
			denki_test_learn_stop();
			break;
		case DENKI_TEST_LEARN_CHECK:
			denki_test_learn_check();
			break;
		case DENKI_TEST_SIGNAL_WAIT:	
			denki_test_signal_wait();
			break;
		case DENKI_TEST_SIGNAL_ANS_WAIT:
			denki_test_signal_ans_wait();
			break;
		default:	
			u1g_current_mode = 9;
			break;
	}
}


static void denki_test_start(void)
{
	u2g_systimer_1ms_timer_for_anjou = U1L_ZERO;
	u2g_systimer_1sec_timer_for_anjou = U1L_ZERO;
	u1g_f_ok_set_on_shortbreak = FALSE;			

	if ( u1g_current_mode == 0 ){
		
		u2l_total_timer_counter = 0;
		u1l_step_denki_test++;
	}
	else{}
}


static void denki_test_100v_wait(void)
{
	if(u2l_total_timer_counter >= U2L_TIME_VER_UP_STABLE){
		u2l_total_timer_counter = 0;

		u1l_step_denki_test++;
	}
	else{}
}


static void denki_test_power_check_wait(void)
{
	if(u2l_total_timer_counter >= U2L_TIME_WAIT_POWER_CHECK){
		u1g_f_ok_set_on_shortbreak = TRUE;		
		
		u1g_current_mode = 7;
		u2l_total_timer_counter = 0;

		u1l_step_denki_test++;
	}
	else{}
}


static void denki_test_open_vib_check(void)
{
	if(u2l_total_timer_counter >= U2L_TIME_VIBRATION_CHECK){
		
		u1g_current_mode = 6;
		u2l_total_timer_counter = 0;

		u1l_step_denki_test++;
	}
	else{}

	
	if( (u1g_kahuka_input == 1) && (Fg_pwm_out == 1) ){
		u1l_step_denki_test = U1L_FREEZE_STATE;			
	}
	else{}
}


static void denki_test_open_stop_wait(void)
{
	if(u2l_total_timer_counter >= U2L_TIME_STOP_KEEP){
		
		u1g_current_mode = 8;
		u2l_total_timer_counter = 0;

		u1l_step_denki_test++;
	}
	else{}
}

static void denki_test_close_vib_check(void)
{
	if(u2l_total_timer_counter >= U2L_TIME_VIBRATION_CHECK){
		
		u1g_current_mode = 6;
		u2l_total_timer_counter = 0;

		u1l_step_denki_test++;
	}
	else{}
		
	
	if( (u1g_kahuka_input == 1) && (Fg_pwm_out == 1) ){
		u1l_step_denki_test = U1L_FREEZE_STATE;			
	}
	else{}
}


static void denki_test_close_stop_wait(void)
{
	if(u2l_total_timer_counter >= U2L_TIME_STOP_KEEP){
	
		u1g_current_mode = 7;
		u2l_total_timer_counter = 0;

		u1l_step_denki_test++;
	}
	else{}
}


static void denki_test_encoder_check(void)
{
	if(u2l_total_timer_counter >= U2L_TIME_ENCODER_CHECK){
	
		u1g_current_mode = 6;
		u2l_total_timer_counter = 0;

		u1l_step_denki_test++;
	}
	else{}

	if( (u1g_kahuka_input == 1) && (Fg_pwm_out == 1) ){
		u1l_step_denki_test = U1L_FREEZE_STATE;		
	}
	else{}
}


static void denki_test_learn_stop(void)
{
	if(u2l_total_timer_counter >= U2L_TIME_DIR_CHECK_WAIT){	
		u1l_step_denki_test++;
	}
	else{}
}

static void denki_test_learn_check(void)
{
	bool find_learndata = FALSE;

	find_learndata = check_flash_learndata();		

	u2l_total_timer_counter = 0;

	if(find_learndata == TRUE){
		
		u1l_step_denki_test = U1L_FREEZE_STATE;
	}
	else{
		
		u1l_step_denki_test = DENKI_TEST_SIGNAL_WAIT;
		
		uart_fact_elec_test();
	}
}

static void denki_test_signal_wait(void)
{
	if( Fg_uart_fact_finish_elec_test == TRUE ){
		
		u1g_flash_finish = FACT_TORQUE_MODE;	
		u1g_flash_write_status = U1_FACT_WRITE;

		u1g_current_mode = 8;
		u2l_total_timer_counter = 0;

		u1l_step_denki_test++;
	}
	else if(u2l_total_timer_counter >= U2L_TIME_WIRELESS_TIMEOUT){
		
		u1l_step_denki_test = U1L_FREEZE_STATE;
	}
	else{}
}

static void denki_test_signal_ans_wait(void)
{
	if(u2l_total_timer_counter >= U2L_TIME_TESTER_RESPONSE){
		
		u1l_step_denki_test = U1L_FREEZE_STATE;
	}
	else{}

	if( (u1g_kahuka_input == 1) && (Fg_pwm_out == 1) ){
		u1l_step_denki_test = U1L_FREEZE_STATE;		
	}
	else{}
}

#if 0	

void check_hide_ope_key(void)
{
	check_koutei_write();
	check_version_output();
	
	return;
}

static void check_koutei_write(void)
{
	static u2 u2l_kyoka_timer_counter = 0;	

	if( u1g_mode == U1G_STOP_MODE ){
		u1l_fact_write = 0;
	}else{}
	
	if(u2l_kyoka_timer_counter >= U2L_TIME_KOUTEI_KYOKA){
	
	}else{
		if(u1g_current_mode < 10){	
		
			check_koutei_sw_input();
		}
		else{}

		u2l_kyoka_timer_counter++;
	}

	if( (u1l_fact_write == 1) && (u1g_total_timer_input) ){
		if(u1l_step_koutei_ope == U1L_OPE_KOUTEI_KYOKA){
			u1g_flash_finish = 0;	
		}else if(u1l_step_koutei_ope == U1L_OPE_KOUTEI_KYOKA){
			u1g_flash_finish = 2;	
		}
		else{}
		u1g_flash_write_status = U1_FACT_WRITE;
		u1l_step_koutei_ope = 0;	

		u1g_uart_buzzer_order = U1G_ORDER_BUZZER;
	}
	else{}
	
	return;
}

static void check_koutei_sw_input(void)
{
	static u1 u1l_step_koutei_write = 0;			
	static u1 u1l_sw_input_buf[U1L_SW_OPE_NUM] = {255, 255, 255};
	u1 u1a_sw_value = 0;								
	u1 u1a_i = 0;
	bool sw_input = FALSE;							

	switch(u1l_step_koutei_write){
		case KOUTEI_CHECK_SW_IN_WAIT:	
			if(Fg_key_open){
				sw_input = TRUE;
				u1a_sw_value = SF_OPEN;
			}else if(Fg_key_close){
				sw_input = TRUE;
				u1a_sw_value = SF_CLOSE;
			}else if(Fg_key_stop){
				sw_input = TRUE;
				u1a_sw_value = SF_STOP;
				u1l_step_koutei_write = KOUTEI_CHECK_SW_OFF_WAIT;	
			}
			else{}
		
			if(sw_input){
				u1l_sw_input_buf[2] = u1l_sw_input_buf[1];
				u1l_sw_input_buf[1] = u1l_sw_input_buf[0];
				u1l_sw_input_buf[0] = u1a_sw_value;
			}
			else{}
		
			break;
		case KOUTEI_CHECK_SW_OFF_WAIT:	
			if(Fg_keyoff_f){
				u1l_step_koutei_write = KOUTEI_CHECK_SW_IN_WAIT;
			}
			else{}
			
			break;
		default:	
			break;
	}
	
	if(u1l_sw_input_buf[0] == SF_OPEN){
		if( (u1l_sw_input_buf[1] == SF_STOP) && (u1l_sw_input_buf[2] == SF_CLOSE) ){
			u1l_step_koutei_ope = U1L_OPE_KOUTEI_KYOKA;		
		}else if( (u1l_sw_input_buf[1] == SF_CLOSE) && (u1l_sw_input_buf[2] == SF_STOP) ){
			u1l_step_koutei_ope = U1L_OPE_KOUTEI_LOCK;	
		}
		else{}
	}
	else{}

	if( (u1l_step_koutei_ope != 0) && (u1l_fact_write == 0) ){
	
		u1g_uart_buzzer_order = U1G_ORDER_BUZZER;
		u1l_fact_write = 1;				
	

		for(u1a_i = 0; u1a_i < U1L_SW_OPE_NUM; u1a_i++){
			u1l_sw_input_buf[u1a_i] = 255;
		}
		u1l_step_koutei_write = 255;	
	}
	else{}
	
	return;
}


static void check_version_output(void)
{
	static u2 u2l_version_timer_counter = 0;	


	if(u2l_version_timer_counter >= U2L_TIME_VERSION_CHECK){
	
	}else{
		switch(u1l_step_ver_output){
			case VER_CHECK_STOP_IN_WAIT:	
				check_version_stop_in_wait();
				break;
			case VER_CHECK_VER_OUTPUT:	
				check_version_ver_output();
				break;
			default:
				u1l_step_ver_output = 255;
				break;
		}
		
		u2l_version_timer_counter++;
	}
	
	return;
}


static void check_version_stop_in_wait(void)
{
	static u1 u1l_pre_stop_off = 0;			

	if(Fg_osikiri_open || Fg_osikiri_close || u1g_key_3sw){
		u1l_stop_count = 0;
	}else if(Fg_key_stop){
		if(u1l_pre_stop_off){
			u1l_stop_count++;
			u2l_timer_counter = 0;
		}
		else{}
		u1l_pre_stop_off = 0;
	}else if(u1g_f_any_key_input){
		u1l_stop_count = 0;
		u1l_pre_stop_off = 1;
	}else{
		u1l_pre_stop_off = 1;
	}

	if (u1l_stop_count >= U1L_COMP_STOP_COUNT){
		u2l_timer_counter = U2L_TIME_BUZZER_INTERVAL;
		u1l_step_ver_output++;
	}
	else{}
}


static void check_version_ver_output(void)
{
	static u1 u1l_buzzer_count = 0;				

	if(u2l_timer_counter >= U2L_TIME_BUZZER_INTERVAL){	
		if(u1g_uart_buzzer_order == 0){	
			u1g_uart_buzzer_order = U1G_ORDER_BUZZER;
			u1l_buzzer_count++;
			u2l_timer_counter = 0;
		}
		else{}
	}else{
		u2l_timer_counter++;
	}

	if(u1l_buzzer_count >= U1L_VERSION_BUZZER_COUNT) {
		u1l_stop_count = 0;
		u1l_step_ver_output = VER_CHECK_STOP_IN_WAIT;
	}else{}
}
#endif


static void check_test_mode_change(void)
{
	switch(u1l_step_test_change){
		case TEST_MODE_STOP_IN_WAIT:	
			check_test_mode_stop_in_wait();
			break;
		case TEST_MODE_CHANGE:				
			change_tester_mode();
			break;
		default:
			u1l_step_test_change = U1L_FREEZE_STATE;
			break;
	}
	return;
}


static void check_test_mode_stop_in_wait(void)
{
	static u1 u1l_pre_stop_off = FALSE;				

	
	if((Fg_osikiri_open == 1) || (Fg_osikiri_close == 1) || (u1g_key_3sw == 1)){
		u1l_stop_count = 0;
	}else if(Fg_key_stop == 1){
		if(u1l_pre_stop_off == TRUE){
			u1l_stop_count++;
		}
		else{}
		u1l_pre_stop_off = FALSE;
	}else if(u1g_f_any_key_input == 1){
		u1l_stop_count = 0;
		u1l_pre_stop_off = TRUE;
	}else{
		u1l_pre_stop_off = TRUE;
	}

	
	if (u1l_stop_count >= U1L_COMP_STOP_COUNT){
		u1l_step_test_change++;
	}
	else{}
}


static void change_tester_mode(void)
{
	
	u1g_uart_buzzer_order = U1G_ORDER_BUZZER;

	
	if(u1g_flash_finish == FACT_DENKI_MODE){
		u1g_flash_finish = FACT_TORQUE_MODE;	
	} else {
		u1g_flash_finish = FACT_DENKI_MODE;		
	}
	u1g_flash_write_status = U1_FACT_WRITE;
	u1l_step_test_change = U1L_FREEZE_STATE;
}

