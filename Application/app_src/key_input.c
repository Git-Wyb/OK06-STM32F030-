#include "Sys.h"
#include "constants.h"
#include "variables.h"
#include "functions.h"
#include "a_data_exchange.h"
#include "Gpio.h"
#include "comm_uart.h"
#include "access_flash.h"
#include "anjou_test.h"

//#define	U1L_ZERO			((u1)0)
//#define	U1L_ONE				((u1)1)
//#define	U1L_TWO				((u1)2)
//#define	U2L_ZERO			((u2)0)
//#define	U2L_MAX				((u2)0xffffU)

#define	U1L_MASK_CLOSE		((u1)0x80)		
#define	U1L_MASK_STOP		((u1)0x02)		
#define	U1L_MASK_OPEN		((u1)0x01)		
#define	U1L_MASK_SAIKOU		((u1)0x10)		
#define	U1L_MASK_OKONOMI	((u1)0x80)		
#define	U1L_MASK_SETTING	((u1)0x40)		

#define	U1L_MASK_START_SW	((u1)0x02)		
#define	U1L_MASK_OBSTACLE_SW	((u1)0x04)		
#define	U1L_MASK_LOCK_SW	((u1)0x08)		

#define	U1L_3SW_ON			((u1)0xe0)
#define	U1L_BIT_SET			((u1)1)			

#define	TIME_CHECK_SW_RESET	((u1)30)		
#define	U2L_TIME_STOP_RESET	((u2)1000)		
#define U1L_NOT_SIGNAL		((u1)255)	

static void sw_off_count(void);
static void sw_all_off_ope(void);
static void check_sw_reset(void);
static void check_sw_stop_tr(void);
static void sw_in_count(void);
static void check_power_start_sw(void);
static void check_any_key_input(void);

//static u2 u2l_cnt_stop_reset;		
//static u1 u1l_key_reset_stop;		
//static u2 u2l_cnt_chng_mode;
//static u1 u1l_f_3swreset_enable;
//static u1 u1l_f_clear_enable;	
//static u2 u2l_cnt_open_sw;	
//static u2 u2l_cnt_stop_sw;	
//static u2 u2l_cnt_close_sw;	
//static u1 u1l_f_clear_dis;		
//static u1 u1l_f_3swreset_dis;	
u1 u1l_sw_jun = 0;			

static void sw_in_count(void)
{
	u1g_c_sw_off[u1l_sw_jun] = 0x00;					
	if ( u1g_last_sw[u1l_sw_jun] == 0x01 ){
	
		if(u1g_c_sw_on[u1l_sw_jun] < 0xff){
			u1g_c_sw_on[u1l_sw_jun]++;
		}
		else{
		}
			
		if( u1g_c_sw_on[u1l_sw_jun] >= ON_CHECK){
		
			switch(u1l_sw_jun){
			case	0x00:		
				Fg_keyin_open = 1;
				break;
			case	0x01:		
				Fg_keyin_close = 1;
				break;
			case	0x02:		
				Fg_keyin_stop = 1;
				break;
			default:
				u1g_keyin = 0x00;
				u1l_sw_jun = 0x00;
				break;
			}
		} else{
		}
	}
	else{
		u1g_last_sw[u1l_sw_jun] = 0x01;
	}
}

static void sw_off_count(void)
{
	if(u1g_last_sw[u1l_sw_jun] == 0x00 ){
		u1g_c_sw_on[u1l_sw_jun] = 0x00;
		u1g_c_sw_off[u1l_sw_jun]++;
		if( u1g_c_sw_off[u1l_sw_jun] >= OFF_CHECK ){
			u1g_c_sw_off[u1l_sw_jun] = 0x00;
			switch(u1l_sw_jun){
			case	0x00:	
				Fg_keyoff_open = 1;
				Fg_keyin_open = 0;
				u1g_key_open_only = 0;
				break;
			case	0x01:	
				Fg_keyoff_close = 1;
				Fg_keyin_close = 0;
				u1g_key_close_only = 0;
				break;
			case	0x02:
				Fg_keyoff_stop = 1;
				Fg_key_stop_only = 0;
				Fg_keyin_stop = 0;
				Fg_f_stop_sakiosi = 0;
				break;
			default:
		
				break;
			}
		} else{
		}
	} else{
		u1g_last_sw[u1l_sw_jun] = 0x00;
	}
}

static void sw_all_off_ope(void){
	if( u1g_keyoff == 0xe0 ){
		if( Fg_f_sw_cancel == 1 ){				

			if( u1g_keyin == 0 ){
				Fg_keyoff_f = 1;
				Fg_f_sw_cancel = 0;
			}	
			else{}
		} 
		else {
			Fg_keyoff_f = 1;
			Fg_f_sw_cancel = 0;
		}
	} 
	else{
		Fg_keyoff_f = 0;
		u1g_cnt_no_in = 0;
	}
}

void sw_input_check(void)
{
	u1g_sw[0x00] = P_OPEN_SW_Input();//(u1)(~P_OPEN_SW & 0x01);			
	u1g_sw[0x01] = P_CLOSE_SW_Input();//(u1)(~P_CLOSE_SW & 0x01);			
	u1g_sw[0x02] = P_STOP_SW_Input();//(u1)(~P_STOP_SW & 0x01);			
#if 0
	u1g_sw[0x00] = P_OPEN_SW & P_OPEN_SW_WIRED;	
	u1g_sw[0x01] = P_CLOSE_SW & P_CLOSE_SW_WIRED;
	u1g_sw[0x02] = P_STOP_SW & P_STOP_SW_WIRED;	
#endif

	for( u1l_sw_jun=0;u1l_sw_jun<=2;u1l_sw_jun++ ){
		if( u1g_sw[u1l_sw_jun] == 0x00 ){
			sw_in_count();
		}
		else{
			sw_off_count();
		}
	}
	sw_all_off_ope();
}

static void check_sw_reset(void){
	if( u1g_keyin == 0xe0 )						
		{
			Fg_key_stop_only = 0;
			u1g_key_open_only = 0;
			u1g_key_close_only = 0;
			u1g_keyoff = 0;
			Fg_f_sw_cancel = 1;					
			if( Fg_f_chng_mode_t == 1 )
				{
					Fg_f_chng_mode_t = 0;
					u2g_cnt_chng_mode++;
					if( u2g_cnt_chng_mode >= TIME_CHECK_SW_RESET )		/*3000ms */
						{
							u2g_cnt_chng_mode = 0;
							Fg_f_stop_sakiosi = 0;
							u1g_key_3sw = 1;
							u1g_key_3sw_jougen = 1;
						}
					else{}
				}
			else{}
		}
	else
		{
////			Fg_f_chng_mode_t = 0;
			u2g_cnt_chng_mode =0x00;
		}
}


static void check_sw_stop_tr(void)
{
	u1 u1a_num_input_sw = 0;
	
	u1a_num_input_sw = (u1)(Fg_keyin_open + Fg_keyin_close + Fg_keyin_stop);

	if( ( (Fg_key_stop_only != 1) && (u1a_num_input_sw >= 2) )
		|| (u1a_num_input_sw >= 3) ){	
			Fg_key_stop_only = 0;
			u2g_key = 0x00;
			Fg_key_stop = 1;
	}
	else{}
}

void key_f_set(void){
	if ( Fg_keyoff_f == 1)			
		{
			u1g_key_open_only = 0;
			u1g_key_close_only = 0;
			Fg_key_stop_only = 0;
			Fg_f_stop_sakiosi = 0;
			u2g_key = 0x00;						
			switch( u1g_keyin )
				{
				case	P_OPEN_KEY:					
					Fg_key_open = 1;
					Fg_keyoff_open = 0;
					Fg_keyoff_f = 0;
					u1g_key_open_only = 1;	
					if( u2g_flash_num_sw_open < 0xffff ){
						u2g_flash_num_sw_open++;
					}
				break;
				case	P_CLOSE_KEY:				
					Fg_key_close = 1;
					Fg_keyoff_close = 0;
					Fg_keyoff_f = 0;
					u1g_key_close_only	= 1;	
					if( u2g_flash_num_sw_close < 0xffff ){
						u2g_flash_num_sw_close++;
					}
				break;
				case	P_STOP_KEY:					
					Fg_key_stop = 1;
					Fg_keyoff_stop = 0;
					Fg_keyoff_f = 0;
					Fg_key_stop_only = 1;
					Fg_f_stop_sakiosi = 1;			
				break;
				case	P_KEY_NO_IN:				
				break;
				default:							
					Fg_key_stop = 1;				
					Fg_keyoff_f = 0;
					Fg_keyoff_open = 0;
					Fg_keyoff_close = 0;
					Fg_keyoff_stop = 0;
				break;
				}
			u1g_keyin = 0x00;
////			stop_only_in = 0;
		}
	else										
		{
			Fg_f_sw_cancel = 1;					

			if( Fg_keyoff_stop == 0 )			
				{
					if( Fg_key_stop_only == 1)			
						{
							Fg_f_sw_cancel = 0;
							Fg_osikiri_open = 0;
							Fg_osikiri_close = 0;
							if( u1g_keyin == 0xa0 )	
								{
									Fg_osikiri_open = 1;
									Fg_keyoff_open = 0;
								}
							else{}
							if( u1g_keyin == 0x60 )
								{
									Fg_osikiri_close = 1;
									Fg_keyoff_close = 0;
								}
							else{}
						}
					else{}
				}
			else
				{
				}
			if( Fg_f_stop_sakiosi == 1 )
				{
					check_sw_reset();				
#if 0
					check_sw_huka_reset();
					check_sw_startup();
					a_vog_trqajst_resetvalue();		
					Fg_f_chng_mode_t = 0;
#endif
				}
			else{}
			if ( Fg_osikiri_open == 1 )			
				{
					if( (Fg_key_stop_only == 0) || (Fg_keyoff_open == 1) )
						{
							osikiri_reset();
						}
					else{}
				}
			else if( Fg_osikiri_close == 1 )			
				{
					if( (Fg_key_stop_only == 0) || (Fg_keyoff_close == 1) )
						{
							osikiri_reset();
						}
					else{}
				}
			else{}
			
		}

	check_sw_stop_tr();
	
	if( Fg_f_stop_sakiosi == 0 )
	{
		osikiri_reset();
	}
	check_power_start_sw();
	check_any_key_input();
}

void osikiri_reset(void){
	
	if( ( Fg_osikiri_open == 1) || ( Fg_osikiri_close == 1 ) ){
		Fg_osikiri_open = 0;
		Fg_osikiri_close = 0;
		u1g_keyin = 0x00;
		Fg_key_stop = 1;
		u1g_keyoff = 0;
		Fg_f_sw_cancel = 1;		
	}
	if( (u1g_mode == U1G_OSIKIRI_OPEN_MODE) || ( u1g_mode == U1G_OSIKIRI_CLOSE_MODE) ){
		if( ( Fg_osikiri_open == 0 ) || ( Fg_osikiri_close == 0 ) ){
			
			if( (check_torque_test_exec() == U1G_FACT_TRQ_STOP) && (check_denki_test_exec() == U1G_FACT_DENKI_STOP) ){
				Fg_key_stop = 1;
			}
			else{}
		}
	}
}

void soft_reset_main(void)
{

	u1 u1a_up = 0;
	u1 u1a_down = 0;
	u2 u2a_size = 0;
	
	u1g_error_mode = ERR_SOFT_RESET;	
	u2a_size = (u2)(s2g_size_ram[0]);
	u1a_down = a_u1g_data_exchange0_word_to_byte(u2a_size);
	u1a_up = a_u1g_data_exchange1_word_to_byte(u2a_size);
	a_vog_error_status_store(u1g_current_mode,u1a_up,u1a_down);
	error_ope_main();

	rest_ready_write_data();

	u1g_cnt_e2prom_write = 0;

	u1g_flash_write_status = U1_ALL_WRITE;
	u1g_f_reset_after_write = 1;
}


u1 learn_fullclose_position(void)
{
	u1 u1a_down = 0,u1a_up = 0,u1a_ans = 0;
	s2 s2a_j = 0;
	u1a_ans = 0;
	if((s2g_cnt_plus >= (s2)ONE_SEC_P) && (s2g_cnt_plus <= (s2)PULSE_MAX_SIZE)){
		u1a_ans = 1;	
		if( u1g_current_mode == 20 ){
			for( s2a_j = 0; s2a_j <= MAX_SECTION; s2a_j++){
				u2g_over_lev_b[s2a_j][4] = u2g_huka_jougen;
			}
		}
		else{}
	
		u1g_previous_mode = u1g_current_mode;
		u1g_different_mode = 1;
	
		s2g_size_ram[0] = s2g_cnt_plus;			
		s2g_lock_start_position = s2g_size_ram[0];

		u1g_error_mode = ERR_H_SIZE_SET;
		u2g_flash_hsize_all = (u2)s2g_cnt_plus;	
		u1a_down = a_u1g_data_exchange0_word_to_byte(u2g_flash_hsize_all);
		u1a_up = a_u1g_data_exchange1_word_to_byte(u2g_flash_hsize_all);
		a_vog_error_status_store(u1g_current_mode,u1a_up,u1a_down);
		error_ope_main();

		u1g_num_section = (u1)( (u2)s2g_size_ram[0] / (u2)(ONE_SEC_P) );
	
		if( u1g_num_section >= MAX_SECTION ){
			u1g_num_section = MAX_SECTION;
		}
		else{}
		u1g_num_section_kagen = (u1)((u2)s2g_size_ram[0] / (u2)ONE_SEC_P);
		if( u1g_num_section_kagen >= MAX_SECTION ){
			u1g_num_section_kagen = MAX_SECTION;
		}
		else{}
		
		learn_data_set();
		u1g_f_kagen_set = 1;

		Fg_f_no_learn_data = 0;
		
		u1g_flash_finish = 2;	

		ready_write_data();
		u1g_cnt_e2prom_write = 0;
		u1g_Fg_close_huka_learn = 0;	
		u1g_flash_write_status = U1_ALL_WRITE;	
					
		u1g_current_mode = 109;
		u1g_previous_mode = 109;
	}
	else{}
	return u1a_ans;
}

static void check_power_start_sw(void)
{
	if( swnflag.word != 0 ){
		u1g_power_start = 1;
	}
}

static void check_any_key_input(void)
{
	if( (Fg_key_open == 1) || (Fg_key_close == 1) || (Fg_key_stop == 1) || (Fg_osikiri_open == 1) || (Fg_osikiri_close == 1) || (u1g_key_3sw == 1) ){
		u1g_f_any_key_input = TRUE;
	}else{
		u1g_f_any_key_input	= FALSE;
	}
}
