#define DATF_LIGHT_VERSION
#include <string.h>
#include "Sys.h"
#include <stdlib.h>
#include "variables.h"
#include "functions.h"
#include "storage.h"
#include "access_flash.h"
#include "a_data_exchange.h"
#include "comm_uart.h"
#include "storage.h"
#include "def_local.h"
#include "anjou_test.h"
#include "version.h"

static void data_read_flashmemory_h_size(void);
static void SW_input_cancel(void);

void write_data_number_check(void)
{
	if(u1g_flash_write_status != U1_NO_USE){
		u2g_flash_num_openclose = u2g_num_now;
		u2g_flash_num_move = u2g_num_move;
	}
	else{}
	
	switch( u1g_flash_write_status ){
		case U1_ALL_WRITE:				

			store_storage_data(STORAGE_STUDY_LOAD, (u1 *) &u1g_flash_learndata_top);	
			store_storage_data(STORAGE_RECORD_ERR1, (u1 *) &u1g_flash_errordata_top);
			store_storage_data(STORAGE_RECORD_ERR2, (u1 *) &u1g_flash_errordata20_top);	
			store_storage_data(STORAGE_STUDY_BASE, (u1 *) &u1g_flash_hsizedata_top);

			u1g_flash_write_status = 0;
				
			break;
		case U1_E_SIZE_WRITE:			
			
			store_storage_data(STORAGE_RECORD_ERR1, (u1 *) &u1g_flash_errordata_top);	
			store_storage_data(STORAGE_RECORD_ERR2, (u1 *) &u1g_flash_errordata20_top);	
			store_storage_data(STORAGE_STUDY_BASE, (u1 *) &u1g_flash_hsizedata_top);	
			
			u1g_flash_write_status = 0;
				
			break;
		case U1_E_H_WRITE:			
		
			u1g_flash_write_status = 0;

			break;
		case U1_SIZE_H_WRITE:			
			
			store_storage_data(STORAGE_RECORD_ERR1, (u1 *) &u1g_flash_errordata_top);
			store_storage_data(STORAGE_RECORD_ERR2, (u1 *) &u1g_flash_errordata20_top);

			/* store_storage_data(STORAGE_STUDY_BASE, (u1 *) &u1g_flash_hsizedata_top);*/
			u1g_flash_write_status = 0;

			break;
		case U1_HUKA_WRITE:
			store_storage_data(STORAGE_STUDY_LOAD, (u1 *) &u1g_flash_learndata_top);	

			u1g_flash_write_status = 0;
				
			break;
				
		case U1_ERROR_1_WRITE:

			store_storage_data(STORAGE_RECORD_ERR1, (u1 *) &u1g_flash_errordata_top);
				
			u1g_flash_write_status = 0;
			break;
		case U1_SIZE_HUKA_WRITE:
		
			store_storage_data(STORAGE_STUDY_LOAD, (u1 *) &u1g_flash_learndata_top);	
			store_storage_data(STORAGE_STUDY_BASE, (u1 *) &u1g_flash_hsizedata_top);	

			u1g_flash_write_status = 0;	
			break;
		case U1_FACT_WRITE:
			store_storage_data(STORAGE_FACTORY, (u1 *) &u1g_flash_factdata_top);	

			u1g_flash_write_status = 0;
			break;
		default:
			
			u1g_flash_write_status = 0;
			break;
	}
}


void check_flash_task(void)
{
//	u1 u1a_result;
	
	write_data_number_check();	
	
	
	if(u1g_fg_data_read == 0){
		
		data_read_flashmemory_h_size();
		anjou_test_initial(u1g_flash_finish);
		
//test		if(u1g_flash_soft_ver != version){
//			u1g_flash_soft_ver = version;
//			u1g_flash_write_status = U1_FACT_WRITE;
//		}
		
		
		u1g_fg_data_read = 1;	
	}
	else{}
	
	if( u1g_f_reset_after_write == 1){
	
		SW_input_cancel();
//test		u1a_result = check_storage_cmd_idle();
//		if( u1a_result == TRUE){
			rest_startup();	
//		}
//		else{}
	}
	else{}
}



void ready_write_data(void)
{
	if( u2g_huka_jougen >= LEARN_CLOSE_MIN ){
		
		u1g_flash_upper_ref = (u1)u2g_huka_jougen;				
	}
	else{
		u1g_flash_upper_ref = (u1)u2g_max_const_huka;			
	}
	if( u1g_f_learn_open_max_huka == 1){
		if( u2g_learn_buffer >= LEARN_OPEN_MIN){
			u1g_flash_open_allarea = (u1)u2g_learn_buffer;
		}
		else{
			u1g_flash_open_allarea = (u1)u2g_max_const_huka;
		}
	}
	else{
		u1g_flash_open_allarea = (u1)u2g_max_const_huka;
	}

	u1g_flash_learn_open_fg = u1g_f_open_learn;
	
	
	u1g_flash_close_huka0 = (u1)(u2g_over_lev_b[0][4]);
	u1g_flash_close_huka1 = (u1)(u2g_over_lev_b[1][4]);
	u1g_flash_close_huka2 = (u1)(u2g_over_lev_b[2][4]);
	u1g_flash_close_huka3 = (u1)(u2g_over_lev_b[3][4]);
	u1g_flash_close_huka4 = (u1)(u2g_over_lev_b[4][4]);
	u1g_flash_close_huka5 = (u1)(u2g_over_lev_b[5][4]);
	u1g_flash_close_huka6 = (u1)(u2g_over_lev_b[6][4]);
	u1g_flash_close_huka7 = (u1)(u2g_over_lev_b[7][4]);
	u1g_flash_close_huka8 = (u1)(u2g_over_lev_b[8][4]);
	u1g_flash_close_huka9 = (u1)(u2g_over_lev_b[9][4]);
	u1g_flash_close_huka10 = (u1)(u2g_over_lev_b[10][4]);
	u1g_flash_close_huka11 = (u1)(u2g_over_lev_b[11][4]);
	u1g_flash_close_huka12 = (u1)(u2g_over_lev_b[12][4]);
	u1g_flash_close_huka13 = (u1)(u2g_over_lev_b[13][4]);
	u1g_flash_close_huka14 = (u1)(u2g_over_lev_b[14][4]);
	u1g_flash_close_huka15 = (u1)(u2g_over_lev_b[15][4]);

	
	u1g_flash_num_section = u1g_num_section;
	u2g_flash_hsize_all = (u2)s2g_size_ram[0];
	u2g_flash_max_open_pulse = (u2)0;		
	
	make_check_sum();
	u1g_flash_checksum_huka = u1g_check_sum_learn;
		
	make_size_check_sum();
	u1g_flash_checksum_hsize = u1g_check_sum_size;
	
	if( ( u1g_previous_mode == 108 ) && ( u1g_current_mode == 100 )){
		u1g_cnt_e2prom_write++;
	}
	else{}
}


void rest_ready_write_data(void)
{
	u1 u1a_i = 0;
	
	for( u1a_i = 0;u1a_i <= CHECK_SUM_HUKA; u1a_i++ ){
		*(&u1g_flash_learndata_top + u1a_i) = U1_NON_VALUE;
	}
	
	for( u1a_i = 0;u1a_i <= CHECK_SUM_SIZE; u1a_i++ ){
		*(&u1g_flash_hsizedata_top + u1a_i) = U1_NON_VALUE;
	}
	u1g_current_mode = 0;
}


void make_check_sum(void)
{
	u1 u1a_i;
	u1g_check_sum_learn = 0;
	for(u1a_i = 0; u1a_i < CHECK_SUM_HUKA; u1a_i++){
		u1g_check_sum_learn = u1g_check_sum_learn + (u1)(*(&u1g_flash_learndata_top + u1a_i));
	}
}


void make_size_check_sum(void)
{
	u1g_check_sum_size = ((u1)0);

	u1g_check_sum_size = u1g_check_sum_size + u1g_flash_num_section;
	
	u1g_check_sum_size = u1g_check_sum_size + a_u1g_data_exchange0_word_to_byte(u2g_flash_hsize_all);
	u1g_check_sum_size = u1g_check_sum_size + a_u1g_data_exchange1_word_to_byte(u2g_flash_hsize_all);
	

}


static void data_read_flashmemory_h_size(void)
{
	get_storage_data(STORAGE_STUDY_BASE, (u1 *) &u1g_flash_hsizedata_top);
	get_storage_data(STORAGE_STUDY_LOAD, (u1 *) &u1g_flash_learndata_top);
	get_storage_data(STORAGE_RECORD_ERR1, (u1 *) &u1g_flash_errordata_top);
	get_storage_data(STORAGE_RECORD_ERR2, (u1 *) &u1g_flash_errordata20_top);
	get_storage_data(STORAGE_FACTORY, (u1 *) &u1g_flash_factdata_top);
}


static void SW_input_cancel(void){
	
	Fg_key_stop = 1;
	
	u1g_c_sw_on[0] = 0;
	u1g_c_sw_on[1] = 0;
	u1g_c_sw_on[2] = 0;
}



void reset_flash_learndata(void)
{
	u1 u1a_i = 0;
	
	for( u1a_i = 0;u1a_i < CHECK_SUM_HUKA; u1a_i++ ){
		*(&u1g_flash_learndata_top + u1a_i) = U1_NON_VALUE;
	}
	
	for( u1a_i = 0;u1a_i < CHECK_SUM_SIZE; u1a_i++ ){
		*(&u1g_flash_hsizedata_top + u1a_i) = U1_NON_VALUE;
	}

	
	make_check_sum();
	u1g_flash_checksum_huka = u1g_check_sum_learn;
		
	make_size_check_sum();
	u1g_flash_checksum_hsize = u1g_check_sum_size;
}


bool check_flash_learndata(void)
{
	u1 u1a_i = 0;
	bool find_learndata = FALSE;

	data_read_flashmemory_h_size();
	
	for( u1a_i = 0;u1a_i < CHECK_SUM_HUKA; u1a_i++ ){
		if( *(&u1g_flash_learndata_top + u1a_i) != U1_NON_VALUE ){
			find_learndata = TRUE;
		}
	}
	
	for( u1a_i = 0;u1a_i  < CHECK_SUM_SIZE; u1a_i++ ){
		if( *(&u1g_flash_hsizedata_top + u1a_i) != U1_NON_VALUE ){
			find_learndata = TRUE;	
		}
	}
	return find_learndata;
}

