#include "Timer.h"
#include "Adc.h"
#include "Gpio.h"
#include "Sys.h"
#include "variables.h"
#include "constants.h"
#include "functions.h"
#include "anjou_test.h"
#include "input_encoder.h"
#include "a_data_exchange.h"
#include "ecu_test.h"


static void cul_bad_data_del(void);
static void ad_correct(void);
static void ad_hosei(void);
static void bousou_check(void);
static void hosei_culc_temp(void);
static void hosei_culc_ver(void);
static void ad_data_full_buffer(void);
static void ad_port_select(void);
static void watch_temp_value(void);
static void check_temp_error(void);
static void watch_ver_value(void);
static void check_ver_error(void);
static void sort_check_ad_data(u2 *u2a_raw_ad_data);

u1 u1g_ad_num_VER_1sec = 0;
u1 u1l_temp_init_num = 0;
u1 u1l_ver_init_num = 0;
u2 u2l_ver_err_cnt_time = 0;
u1 u1l_f_temp_error_stop = 0;	
u1 u1l_f_ver_error_stop = 0;

#define U1L_KAHUKA_COUNT		(u1)3
#define U1L_FET_CURR_OVER		(u1)0xa5//			//165 300mA
#define U1L_AD_VER_TIME			(u1)0xdf
#define U1L_AD_VER_POWER_ON_TIME	(u1)0xd3

#define	S2L_HOSEI_TEMP_MIN			(s2)(-22)
#define	S2L_HOSEI_TEMP_MAX			(s2)78
#define	HOSEI_HOT_1JI				8
#define	HOSEI_COLD_1JI				4
#define	HOSEI_COLD_CONST				1
#define U1L_TEMP_HOSEI_MAX			(u1)41

#define	U2L_TEMP_CONVERT_BORDER		(u2)912
#define	U2L_TEMP_OPEN_AD			(u2)20
#define	U2L_TEMP_SHORT_AD			(u2)1002
#define	U2L_VER_OPEN_AD				(u2)20
#define	U2L_VER_SHORT_AD			(u2)1002
#define	U2L_VER_ERROR_CHECK_TIME	(u2)0x458

#define FET_ERR_D_PWM				27	
#define FET_ERR_CNT_BREAKDOWN		67

void check_huka(void)
{
	if(u1g_threshold_huka == 1)
    {
		u2g_std_huka = u2g_max_const_huka;
		u2g_max_huka = u2g_max_const_huka;
		u2g_nor_huka = u2g_max_const_huka;
		u2g_learn_max_huka = u2g_max_const_huka;
	}
	else if(u1g_threshold_huka == 2)
    {
		u2g_std_huka = u2g_osikomi_const_huka;
		u2g_max_huka = u2g_osikomi_const_huka;
		u2g_nor_huka = u2g_osikomi_const_huka;
		u2g_learn_max_huka = u2g_osikomi_const_huka;
	}
	else{
#ifdef	NO_LEARN
		u2g_std_huka = u2g_max_const_huka;
		u2g_max_huka = u2g_max_const_huka;
		u2g_nor_huka = u2g_max_const_huka;
		u2g_learn_max_huka = u2g_max_const_huka;
#else
		if(u1g_mode == U1G_CLOSE_MODE){
			u2g_learn_max_huka = u2g_max_const_huka;
		}
		else if(u1g_mode == U1G_OPEN_MODE){
			u2g_learn_max_huka = u2g_open_std_max_huka;
		}
		else{
			u2g_learn_max_huka = u2g_osikomi_const_huka;
		}
		after_learn_k();
		
		sikiiti_hosei();
#endif
		if(u1g_mode == U1G_OPEN_MODE){
			u2g_max_huka = u2g_open_std_max_huka;
		}
		else if(u1g_mode == U1G_CLOSE_MODE){
			u2g_max_huka = u2g_max_const_huka;
		}
		else{}
		
	}

	if ( Fg_f_curr_ad_end == 1 )
		{
			Fg_f_curr_ad_end = 0;

			u1g_thermal_count = 0x0f;
			thermal_check();

			if( u2g_ad_now[(CURR - CURR)] > (u2g_osikomi_const_huka) )
				{
					huka_count_jump();
				}
			else if ( u2g_ad_now[(CURR - CURR)] > u2g_max_huka )
				{
					huka_count_jump();
				}
			else if ( u2g_ad_now[(CURR - CURR)] > u2g_nor_huka )
				{
////					if( Fg_f_no_position != 1 )
////						{
							huka_count_jump();
////						}
				}
			else
				{
					u1g_c_kahuka = 0x00;
				}
		}
	else
		{
		}
}

void huka_count_jump(void)
{
	u1g_c_kahuka++;
	if( u1g_c_kahuka >= U1L_KAHUKA_COUNT )
		{
			Fg_key_stop_only = 0;
			u1g_key_open_only = 0;
			u1g_key_close_only = 0;
			Fg_osikiri_open = 0;
			Fg_osikiri_close = 0;

			u1g_kahuka_input = 1;

			u1g_section_kahuka_occured = u1g_n_section;
			u1g_huka_ad_value = (u1)u2g_ad_now[(CURR - CURR)]/4;
		}
	else{
		u1g_kahuka_input = 0;
	}
}


void thermal_check(void)
{
	if( Fg_timer_thermal == 1)	
		{
			Fg_timer_thermal = 0;
			if( (u2g_ad_now[(CURR - CURR)] <= THERMAL_A)&&	
				(u2g_d_pwm >= THERMAL_D_PWM) )		
				{
					if( Fg_f_last_stateth == 1 )
						{
							if(u1g_cnt_thermal < U1L_VALUE_FFFF){
								u1g_cnt_thermal++;
							}
							else{}
							
							if( u1g_cnt_thermal >= u1g_thermal_count )
								{
									u1g_thermal_input = 1;

									ope_key_stop();
									Fg_key_stop_only = 0;
									u1g_key_open_only = 0;
									u1g_key_close_only = 0;
									u1g_ope_state_f = 3;
									kagen_reset();	
								}
							else{}
						}
					else
						{
							Fg_f_last_stateth = 1;
						}
				}
			else
				{
					if(Fg_f_last_stateth == 1)
						{
							Fg_f_last_stateth = 0;
						}
					else
						{
							u1g_cnt_thermal =0x00;
						}
				}
		}
	else{}
}

void reset_learn_data(void){
	u1 u1a_i = 0;
	u1 u1a_j = 0;
	
	u1g_copy_section = 0;
	u1g_n_section = 0;
	for( u1a_j = 0;u1a_j <= MAX_SECTION;u1a_j++){
		for( u1a_i = 0;u1a_i <= 4;u1a_i++ ){
			u2g_over_lev_b[u1a_j][u1a_i] = 0x00;
			u2g_open_over_lev_b[u1a_j][u1a_i] = 0x00;
		}
		u2g_over_lev_b[u1a_j][4] = u2g_std_max_huka;
		u2g_open_over_lev_b[u1a_j][4] = u2g_open_std_max_huka;
		u2g_jougen_open_over_lev_b = u2g_open_std_max_huka;
		u2g_copy_max_learn_b[u1a_j] = 0;
	}
	u1g_f_learn_open_max_huka = 0;
	u1g_f_learn_close_all_huka = 0;
	u1g_f_open_learn = 0;
	u1g_flash_learn_open_fg = 0;
}

void seprate_block(void){
	if( u1g_mode == U1G_OPEN_MODE )
		{
			open_block_ope();
		}
	else if( u1g_mode == U1G_CLOSE_MODE )
		{
			close_block_ope();
		}
	else{}
}

void after_learn_k(void){
	if( u1g_mode == U1G_OPEN_MODE )
		{
			if( (u1g_Fg_jougen_area > u1g_Fg_copy_jougen_area) || (u1g_different_mode == 1) || (Fg_f_finish_soft_start == 1) )
				{
					if( u1g_Fg_jougen_area == 1 ){	
						u2g_cal_b = u2g_learn_buffer;/* u2g_open_over_lev_b[u1g_n_section][4]; */
					}else{					
						u2g_cal_b = u2g_max_const_huka;
					}
					hosei_main();
					plus_a_cal_open();
					Fg_f_finish_soft_start = 0;
				}
			else{}
		}
	else	
		{

			if( (u1g_copy_section != u1g_n_section) || (u1g_different_mode == 1) || (Fg_f_finish_soft_start == 1) )
				{
					u2g_cal_b = u2g_over_lev_b[u1g_n_section][4];
					hosei_main();
					plus_a_cal();
					Fg_f_finish_soft_start = 0;
				}
			else{}
		}

	switch	( u1g_mode )
		{
			case	0x02:
				if(u2g_kei > (u2)((u2)(U2L_VALUE_FFFF) - u2g_cal_b)){
					u2g_std_huka = U2L_VALUE_FFFF;
				}
				else{
					u2g_std_huka = u2g_cal_b + u2g_kei;
				}
				if( u2g_std_learn <= 6 )
					{
						u2g_std_learn = u2g_std_max_huka;
					}
				else{}
				u2g_max_huka = u2g_std_learn;
			break;
			case	0x01:
				if(u2g_kei > ((u2)(U2L_VALUE_FFFF) - u2g_cal_b)){
					u2g_std_huka = U2L_VALUE_FFFF;
				}
				else{
					u2g_std_huka = u2g_cal_b + u2g_kei;
				}
				if( u2g_open_std_learn <= 6 )
					{
						u2g_open_std_learn = u2g_open_std_learn + 56;
					}
				else{}
				u2g_max_huka = u2g_open_std_learn;					
			break;
			default:
			break;
		}
}

void sikiiti_hosei(void){
	u2g_nor_huka = u2g_std_huka;
	if( u1g_mode == U1G_CLOSE_MODE )
		{
			if( u2g_max_huka >= u2g_std_max_huka )		
				{
					u2g_max_huka = u2g_std_max_huka;
				}
			else{}
		}
	else{}
	if( u2g_max_huka >= u2g_max_const_huka )			
		{
			u2g_max_huka = u2g_max_const_huka;
		}
	else{}

	if( ( u1g_num_section != 0x00 ) &&	
		( ((u1g_mode == U1G_CLOSE_MODE) && ( u1g_n_section > u1g_num_section ))	
		  || ((u1g_mode ==  U1G_OPEN_MODE) && (u1g_n_section > u1g_num_section_kagen)) ))	
		{
			u2g_max_huka = u2g_max_const_huka;			
			u2g_nor_huka = u2g_max_const_huka;
			
		}
	else{}
	if( (u1g_mode == U1G_OSIKIRI_OPEN_MODE) || (u1g_mode == U1G_OSIKIRI_CLOSE_MODE) )	
		{
			u2g_max_huka = u2g_max_const_huka;	
			u2g_nor_huka = u2g_max_const_huka;
		}
	else{}
}


void curr_lev_de(void)
{
	if(u1g_ad_ref[0] == 1)			
		{
			u1g_ad_ref[0] = 0;

			bousou_check();

			if( (u1g_mode == U1G_CLOSE_MODE)||(u1g_mode == U1G_OPEN_MODE)||
				(u1g_mode == U1G_OSIKIRI_CLOSE_MODE))
				{
					if( (u1g_ope_state_f == 1))
						{
							learn_get_data();
						}
					else{}
				}
			else
				{
				}
		}
	else{}
}


void huka_lev_ver(void){
	u2 u2a_hosei_value = 0;

	hosei_culc_ver();

	Fg_b_f_p_hugo = 0;

	if( Fg_f_ver_under == 1 ){	
		u1g_b_p_hosei = (u1)u1g_b_ver_hosei;
		Fg_b_f_p_hugo = 1;
	}
	else{							
		u1g_b_p_hosei = (u1)u1g_b_ver_hosei;
	}
	
	if(u1g_b_p_hosei >= 40){
		u1g_b_p_hosei = 40;
	}
	else{}

	u2a_hosei_value = (u1g_b_p_hosei * u2g_ad_now[(CURR - CURR)]) / 0x64;	
	if( Fg_b_f_p_hugo == 0 )
		{
			u2g_ad_now[(CURR - CURR)] = u2g_ad_now[(CURR - CURR)] + u2a_hosei_value;
		}
	else
		{
			if(u2g_ad_now[(CURR - CURR)] > u2a_hosei_value){	
				u2g_ad_now[(CURR - CURR)] = u2g_ad_now[(CURR - CURR)] - u2a_hosei_value;
			}else{
				u2g_ad_now[(CURR - CURR)] = (u2)U1L_ZERO;
			}
		}
}

void hosei_main(void){
	if( u1g_mode == U1G_OPEN_MODE){
		if( u2g_cal_b >= u2g_open_std_max_huka )
			{
				u2g_cal_b = u2g_open_std_max_huka;
			}
		else{}
	}
	else if( u1g_mode == U1G_CLOSE_MODE){
		if( u2g_cal_b >= u2g_max_const_huka )	
			{
				u2g_cal_b = u2g_max_const_huka;
			}
		else{}
	}
	else{}

///*
//	if( Fg_f_p_hugo == 0 )
//		{
//			u2g_cal_b = (u2)(u2g_cal_b + ((u1g_p_hosei * u2g_cal_b) / 0x64));
//		}
//	else
//		{
//			u2g_cal_b = (u2)(u2g_cal_b - ((u1g_p_hosei * u2g_cal_b) / 0x64));
//		}
//	u2g_cal_b = a_vog_cold_temp_hosei(u2g_cal_b);
//*/	
	
	if( u1g_mode == U1G_OPEN_MODE){
		if(u2g_cal_b < LEARN_OPEN_MIN){
			u2g_cal_b = LEARN_OPEN_MIN;
		}
		else{}
	}
	else if( u1g_mode == U1G_CLOSE_MODE){
		if(u2g_cal_b < LEARN_CLOSE_MIN){
			u2g_cal_b = LEARN_CLOSE_MIN;
		}
		else{}
	}
	else{}

}

void learn_get_data(void)
	{
		switch	(Fg_c_learn)
			{
				case	0x00:
					u2g_max_learn_b = u2g_ad_now[(CURR - CURR)];
					Fg_c_learn = 0x01;
				break;
				default:
					if(u2g_max_learn_b < u2g_ad_now[(CURR - CURR)])
						{
							if( (u2g_ad_now[(CURR - CURR)] <= (u2g_max_learn_b * 2))||
								(u2g_max_learn_b == 0 ) )
								{
									if( (u1g_mode == U1G_OPEN_MODE) && (s2g_cnt_plus <= U2L_JOUGEN_KITEI_AREA) ){
									}
									else{
										u2g_max_learn_b = u2g_ad_now[(CURR - CURR)];
									}
								}
							else if( u2g_ad_now[(CURR - CURR)] <= LEARN_CLOSE_MIN )	
								{
									if( u1g_mode == U1G_CLOSE_MODE )						
										{
											u2g_max_learn_b = LEARN_CLOSE_MIN;	
										}
									else
										{
											u2g_max_learn_b = u2g_ad_now[(CURR - CURR)];
										}
								}
							else
								{
								}
						}
					else{}
				break;
			}
			
			if(u1g_mode == U1G_CLOSE_MODE){
				if(u2g_max_learn_b < LEARN_CLOSE_MIN){
					u2g_max_learn_b = LEARN_CLOSE_MIN;
				}
				else{}
			}
			
			else if(u1g_mode == U1G_OPEN_MODE){
				if(u2g_max_learn_b < LEARN_OPEN_MIN){
					u2g_max_learn_b = LEARN_OPEN_MIN;
				}
				else{}
			}
			else{}
				
			
		if( u2g_max_learn_b >= u2g_learn_max_huka )
			{
				u2g_max_learn_b = u2g_learn_max_huka;
			}
		else{}
}

void learn_data_make(void)
{
	u1 u1a_k = 0;
	u1 u1a_l = 0;
	
	switch	( u1g_mode )
		{
			case	0x02:
				make_std_learn();
			break;
			case	0x01:
				u2g_learn_buffer = 0x00;

				for( u1a_k = 0;u1a_k <= u1g_num_section;u1a_k++ )
				{
					for(u1a_l = 0; u1a_l < 4; u1a_l++){
						if( u2g_open_over_lev_b[u1a_k][u1a_l] >= u2g_learn_buffer )
							{
								u2g_learn_buffer = u2g_open_over_lev_b[u1a_k][u1a_l];
							}
						else{}
					}

					if( u2g_open_over_lev_b[u1a_k][0] == 0 ){
						u1g_f_open_spot_learn = 1;
					}
				}

				if( (u1g_Fg_jougen_area == 0) || (u2g_learn_buffer == 0 ) )	
					{
						u2g_learn_buffer = u2g_max_const_huka;		
					}
				else if( u2g_learn_buffer < LEARN_OPEN_MIN )		
					{
						u2g_learn_buffer = LEARN_OPEN_MIN;		
					}
				else{}

				u2g_cal_b = u2g_learn_buffer;
				plus_a_cal_open();
				if(u2g_kei > (u2)((u2)(U2L_VALUE_FFFF) - u2g_learn_buffer)){
					u2g_open_std_learn = U2L_VALUE_FFFF;
				}
				else{
					u2g_open_std_learn = u2g_learn_buffer + u2g_kei;
				}
				
			
			break;
			default:
			break;
		}
}

void set_error_open_learn_data(void)
{
	u2g_learn_buffer = u2g_max_const_huka;
	u1g_f_open_learn_error = 1;	

	u2g_cal_b = u2g_learn_buffer;
	plus_a_cal_open();
	if(u2g_kei > (u2)((u2)(U2L_VALUE_FFFF) - u2g_learn_buffer)){
		u2g_open_std_learn = U2L_VALUE_FFFF;
	}
	else{
		u2g_open_std_learn = u2g_learn_buffer + u2g_kei;
	}
}

void plus_a_cal(void)
{
	u4 u4a_cal_temp = 0;
	u2 u2a_cal_margin_1ji = 0;
	u2 u2a_temp_hosei_huka = 0;	
	u2 u2a_sikiiti_jougen = 0;	
	u2 u2a_org_learn_Nm = 0;	
	
	u2g_cal_b = u2g_cal_b + ((u2g_cal_b * (u2)u1g_temp_hosei) / KETA_100);
	
	if(u1g_current_mode == 25){
		u2a_temp_hosei_huka = u2g_huka_jougen + ((u2g_huka_jougen * (u2)u1g_temp_hosei) / KETA_100);	
		u2a_org_learn_Nm = a_u2g_close_AD_exchange_to_Nm((u1)u2a_temp_hosei_huka);	
		u2a_sikiiti_jougen = a_u2g_close_Nm_exchange_to_AD(u2a_org_learn_Nm + TRQ_REL_NM_NO_SIZE_RAM);
		
		u2g_cal_b = u2a_temp_hosei_huka;
		if( u2a_sikiiti_jougen >= TRQ_AD_1_2Nm ){			
			u2g_kei = u2a_sikiiti_jougen - u2g_cal_b;
		}else{								
			u2g_kei = TRQ_AD_1_2Nm - u2g_cal_b;
		}
	}
	else if (u1g_f_learn_close_all_huka == 0){
		u2a_temp_hosei_huka = u2g_huka_jougen + ((u2g_huka_jougen * (u2)u1g_temp_hosei) / KETA_100);

		u2a_org_learn_Nm = a_u2g_close_AD_exchange_to_Nm((u1)u2a_temp_hosei_huka);
		u2a_sikiiti_jougen = a_u2g_close_Nm_exchange_to_AD(u2a_org_learn_Nm + TRQ_REL_NM_SET_SIZE_RAM);

		u2g_cal_b = u2a_temp_hosei_huka;
		if(s2g_size_ram[0] < HUKA_JOUGEN_BORDER_SIZE){
			if( u2a_sikiiti_jougen >= TRQ_AD_1_2Nm ){	
				u2g_kei = u2a_sikiiti_jougen - u2g_cal_b;
			}else{									
				u2g_kei = TRQ_AD_1_2Nm - u2g_cal_b;	
			}
		}else{
			if( u2a_sikiiti_jougen >= TRQ_AD_CLOSE_1_45Nm ){	
				u2g_kei = u2a_sikiiti_jougen - u2g_cal_b;	
			}else{											
				u2g_kei = TRQ_AD_CLOSE_1_45Nm - u2g_cal_b;	
			}
		}
	}
	else if( u2g_cal_b >= TRQ_AD_CLOSE_1_7Nm )
		{
			u2g_cal_b = TRQ_AD_CLOSE_1_7Nm;
			if(u2g_max_const_huka > u2g_cal_b){	
				u2g_kei = u2g_max_const_huka - u2g_cal_b;
			}else{
				u2g_kei = U1L_ZERO;
			}
		}
	else if( u2g_cal_b < TRQ_AD_0_5Nm ){
		u2g_kei = TRQ_AD_0_3Nm;	
	}
	else{
//		//u2g_kei = (u2)(((MARGIN_CLOSE_1JI * (u4)u2g_cal_b) / 16384 ) + MARGIN_CLOSE_CONST);
		u4a_cal_temp = MARGIN_CLOSE_1JI * (u4)u2g_cal_b;
		
		if(u4a_cal_temp > MARGIN_CLOSE_CONST){
			u2a_cal_margin_1ji = (u2)((u4a_cal_temp - MARGIN_CLOSE_CONST) / KETA_10000);
		}else{
			u2a_cal_margin_1ji = (u2)U1L_ZERO;
		}
		
		if(u2a_cal_margin_1ji > u2g_cal_b){
			u2g_kei = u2a_cal_margin_1ji - u2g_cal_b;
		}else{
			u2g_kei = (u2)U1L_ZERO;
		}
	}
}

void plus_a_cal_open(void)
{
	u4 u4a_cal_temp = 0;
	u2 u2a_cal_margin_1ji = 0;

	u2g_cal_b = u2g_cal_b + ((u2g_cal_b * (u2)u1g_temp_hosei) / KETA_100);
	
	if( u2g_cal_b >= TRQ_AD_1_9Nm )	
		{
			u2g_cal_b = TRQ_AD_1_9Nm;
			if(u2g_ajst_open_max_huka > u2g_cal_b){
				u2g_kei = u2g_ajst_open_max_huka - u2g_cal_b; 
			}else{
				u2g_kei = (u2)U1L_ZERO;
			}
		}
	else if( u2g_cal_b < TRQ_AD_0_5Nm ){
		u2g_kei = TRQ_AD_OPEN_MAX_0_3Nm;
	}
	else{
		u4a_cal_temp = MARGIN_OPEN_1JI * (u4)u2g_cal_b;
		u2a_cal_margin_1ji = (u2)((u4a_cal_temp + MARGIN_OPEN_CONST) / KETA_10000);
		
		if(u2a_cal_margin_1ji > u2g_cal_b){
			u2g_kei = u2a_cal_margin_1ji - u2g_cal_b;
		}else{
			u2g_kei = (u2)U1L_ZERO;
		}
	}
}

void make_std_learn(void){
	u1 u1a_k = 0;

	u2g_learn_buffer_close = 0x00;
	for( u1a_k = 0;u1a_k <= u1g_num_section ;u1a_k++ )
		{
			if( u2g_over_lev_b[u1a_k][4] >= u2g_learn_buffer_close )
				{
					u2g_learn_buffer_close = (u1)u2g_over_lev_b[u1a_k][4];
				}
			else{}
		}
	u2g_cal_b = (u1)u2g_learn_buffer_close;
	plus_a_cal();
	u2g_std_learn = (u2)(u2g_learn_buffer_close + u2g_kei + max_learn);
}


void open_block_ope(void){
	
	u2 u2a_max_learn_data = 0;
	if( (u1g_n_section < u1g_copy_section) || (u1g_Fg_jougen_area > u1g_Fg_copy_jougen_area) )
		{
			for( u1g_n_lev = 0;u1g_n_lev <= 3;u1g_n_lev++ )
				{
					u2g_open_over_lev_b[u1g_copy_section][(4-u1g_n_lev)] = u2g_open_over_lev_b[u1g_copy_section][(3-u1g_n_lev)];
				}
				
			if( u2g_max_learn_b <= LEARN_OPEN_MIN )
				{
					u2g_max_learn_b = LEARN_OPEN_MIN;
				}
			else{}

			if(u2g_max_learn_b > u2g_copy_max_learn_b[u1g_copy_section]){
				u2a_max_learn_data = u2g_max_learn_b;
			}else{
				u2a_max_learn_data = u2g_copy_max_learn_b[u1g_copy_section];
			}

			if(u2a_max_learn_data > u2g_open_over_lev_b[u1g_copy_section][0]){
				u2g_open_over_lev_b[u1g_copy_section][0] = u2a_max_learn_data;
			}
			else{}
			
			u2g_max_learn_b = 0x00;
			u2g_copy_max_learn_b[u1g_copy_section] = 0x00;
			Fg_c_learn = 0;
			
			if( u1g_c_kahuka >= 0x02 ){
				if( u2g_open_over_lev_b[0][0] >= (u2g_open_over_lev_b[1][0] + 20) ){
					u2g_open_over_lev_b[0][0] = u2g_open_over_lev_b[1][0];
				}
				else{}
			}
			else{}
			
			if( u2g_open_over_lev_b[u1g_copy_section][3] >= u2g_open_over_lev_b[u1g_copy_section][2] ){
				
				u2g_open_over_lev_b[u1g_copy_section][4] = u2g_open_over_lev_b[u1g_copy_section][3];
			}
			else{
				u2g_open_over_lev_b[u1g_copy_section][4] = u2g_open_over_lev_b[u1g_copy_section][2];
			}
			
				
			for( u1g_n_lev = 0; u1g_n_lev <= 1;u1g_n_lev++ ){
				if( u2g_open_over_lev_b[u1g_copy_section][4] <= u2g_open_over_lev_b[u1g_copy_section][(1-u1g_n_lev)]){
					
					u2g_open_over_lev_b[u1g_copy_section][4] = u2g_open_over_lev_b[u1g_copy_section][(1-u1g_n_lev)];
				}
				else{}
			}
			
		}
	else{}
}

void open_block_no_learn_ope(void){
	
	u2 u2a_max_learn_data = 0;

	if( (u1g_f_kagen_set == 1) && ((u1g_n_section < u1g_copy_section) || (u1g_Fg_jougen_area > u1g_Fg_copy_jougen_area)) )
		{
			for( u1g_n_lev = 0;u1g_n_lev <= 3;u1g_n_lev++ )
				{
					u2g_open_over_lev_b[u1g_copy_section][(4-u1g_n_lev)] = u2g_open_over_lev_b[u1g_copy_section][(3-u1g_n_lev)];
				}
				
			if(0 <  u2g_copy_max_learn_b[u1g_copy_section]){
				u2a_max_learn_data = u2g_copy_max_learn_b[u1g_copy_section];
			}else{
				u2a_max_learn_data = 0;
			}
			
			if(u2a_max_learn_data > u2g_open_over_lev_b[u1g_copy_section][0]){
				u2g_open_over_lev_b[u1g_copy_section][0] = u2a_max_learn_data;
			}
			else{}
						
			u2g_max_learn_b = 0x00;
			u2g_copy_max_learn_b[u1g_copy_section] = 0x00;
			Fg_c_learn = 0;

			if( u2g_open_over_lev_b[u1g_copy_section][3] >= u2g_open_over_lev_b[u1g_copy_section][2] ){
				
				u2g_open_over_lev_b[u1g_copy_section][4] = u2g_open_over_lev_b[u1g_copy_section][3];
			}
			else{
				u2g_open_over_lev_b[u1g_copy_section][4] = u2g_open_over_lev_b[u1g_copy_section][2];
			}
				
			for( u1g_n_lev = 0; u1g_n_lev <= 1;u1g_n_lev++ ){
				if( u2g_open_over_lev_b[u1g_copy_section][4] <= u2g_open_over_lev_b[u1g_copy_section][(1-u1g_n_lev)]){
					
					u2g_open_over_lev_b[u1g_copy_section][4] = u2g_open_over_lev_b[u1g_copy_section][(1-u1g_n_lev)];
				}
				else{}
			}
		}
	else{}
}


void close_block_ope(void){
	if(( u1g_n_section > u1g_copy_section) || 
		(Fg_f_fin_both == 1) )
		{
			Fg_f_fin_both = 0;
			for( u1g_n_lev = 0;u1g_n_lev <= 3;u1g_n_lev++ )
				{
					u2g_over_lev_b[u1g_copy_section][(4-u1g_n_lev)] = u2g_over_lev_b[u1g_copy_section][(3-u1g_n_lev)];
				}
			if( u2g_max_learn_b <= LEARN_CLOSE_MIN )
				{
					u2g_max_learn_b = LEARN_CLOSE_MIN;
				}
			else{}
			if( (u2g_max_learn_b >= (u2g_over_lev_b[u1g_copy_section][0] + 80))&&
				(u2g_over_lev_b[u1g_copy_section][0] != 0x00) )
				{
					u2g_max_learn_b = u2g_over_lev_b[u1g_copy_section][0] + 8;
				}
			else{}
			u2g_over_lev_b[u1g_copy_section][0] = u2g_max_learn_b;
			u2g_max_learn_b = 0x00;
			Fg_c_learn = 0;
			if( u2g_over_lev_b[u1g_copy_section][3] >= u2g_over_lev_b[u1g_copy_section][2] )
				{
					u2g_over_lev_b[u1g_copy_section][4] = u2g_over_lev_b[u1g_copy_section][3];
				}
			else
				{
					u2g_over_lev_b[u1g_copy_section][4] = u2g_over_lev_b[u1g_copy_section][2];
				}
			for( u1g_n_lev = 0; u1g_n_lev <= 1;u1g_n_lev++ )
				{
					if( u2g_over_lev_b[u1g_copy_section][4] <= u2g_over_lev_b[u1g_copy_section][(1-u1g_n_lev)])
						{
							u2g_over_lev_b[u1g_copy_section][4] = u2g_over_lev_b[u1g_copy_section][(1-u1g_n_lev)];
						}
					else{}
				}
			
#if 0
			if(u1g_copy_section == 0){
				u2g_huka_jougen = u2g_over_lev_b[0][4];
			}
#endif
		}
	else{}
}

void ad_operate_main(void){
	ad_port_select();
	ad_correct();	
   	curr_lev_de();	
	watch_temp_value();	
	watch_ver_value();
}

static void ad_correct(void)
{
	u1 u1a_num_now = 0,u1a_i = 0;
	u2 u2a_pre_value = 0;
	u4 u4a_temp = 0;
	
	u4a_temp = 0;
	u1a_num_now = 0;
	u2a_pre_value = 0;

	ad_start_set(u1g_ad_num);
	u1g_ad_num_temp = (u1)(u1g_ad_num - CURR);
//    if(u1g_ad_num == CURR) u2g_now_data = 5;
	u2g_now_data = capture_ad_start(NUM_CAPTURE_DATA,(u1)(NUM_ADOPT_DATA - 1));
	switch( u1g_ad_num ){
		case CURR:
			u2a_pre_value = u2g_raw_q[u1g_ad_num_temp][u1g_curr_num];
			u1g_curr_num = adopt_data_num_set(u1g_curr_num);
			u1a_num_now = u1g_curr_num;
			break;
		case VER:
			u2a_pre_value = u2g_raw_q[u1g_ad_num_temp][u1g_ver_num];
			u1g_ver_num = adopt_data_num_set(u1g_ver_num);
			u1a_num_now = u1g_ver_num;
			break;
		case TEMP:
			u2a_pre_value = u2g_raw_q[u1g_ad_num_temp][u1g_temp_num];
			u1g_temp_num = adopt_data_num_set(u1g_temp_num);
			u1a_num_now = u1g_temp_num;
			break;
		default: 
			u1g_ad_num = CURR;

			rest_startup();	
			break;
	}
	if( u1g_f_limit_average == 0 ){
		bad_data_del(u2a_pre_value,u2g_now_data);	
	}
	else{}

	u2g_raw_q[u1g_ad_num_temp][u1a_num_now] = u2g_now_data;


	for( u1a_i = 0;u1a_i <= 3;u1a_i++ ){
		u4a_temp = u4a_temp + (u4)u2g_raw_q[u1g_ad_num_temp][u1a_i];
	}
	u2g_ad_now[u1g_ad_num_temp] = (u2)(u4a_temp / 4);

	u1g_ad_ref[u1g_ad_num_temp] = 1;
	if( u1g_ad_num == CURR ){
		Fg_f_curr_ad_end = 1;					
		ad_hosei();
	}
	else if( u1g_ad_num == TEMP ){
		hosei_culc_temp();
	}
	else{}
	
	ad_data_full_buffer();
}

static void ad_hosei(void)
{
	huka_lev_ver();							
	//hosei_culc_temp();			
}

static void bousou_check(void)
{
	if( (Fg_f_dis_pwm == 1) ||		
		(u2g_d_pwm <= FET_ERR_D_PWM) )	
		{
			if( u2g_ad_now[(CURR - CURR)] >= U1L_FET_CURR_OVER )
				{
					if(u1g_cnt_breakdown < U1L_VALUE_FFFF){
						u1g_cnt_breakdown++;
					}
					else{}

					if( u1g_cnt_breakdown >= FET_ERR_CNT_BREAKDOWN )
						{
							u1g_cnt_breakdown = (u1)0x00;
							ope_key_stop();
							Fg_key_stop_only = 0;
							u1g_key_open_only = (u1)0;
							u1g_key_close_only = (u1)0;
							u1g_bousou_input = (u1)1;
							u1g_huka_ad_value = (u1)u2g_ad_now[(CURR - CURR)]/4;							
						}
					else{}
				}
			else
				{
					u1g_cnt_breakdown = 0x00;
				}
		}
	else
		{
			u1g_cnt_breakdown = 0x00;
		}

	if(u1g_count_abnormal_speed_pulse >= BOUSOU_PULSE_COUNT){
		ope_key_stop();
		Fg_key_stop_only = 0;
		u1g_key_open_only = (u1)0;
		u1g_key_close_only = (u1)0;
		u1g_Fg_break_over_stop = 1;
		u1g_count_abnormal_speed_pulse = (u1)0;
	}
	else{}
	
	if(u1g_mode == U1G_STOP_MODE){
		u1g_bousou_input = (u1)0;
		u1g_count_abnormal_speed_pulse = (u1)0;
	}
	else{}
		
}

static void cul_bad_data_del(void)
{
	if( u2g_ad_buffer0_temp > (u2g_ad_buffer_temp * 5/4) ){
		if(u2g_ad_buffer_temp > 5){
			u2g_now_data = (u2)(u2g_ad_buffer_temp*5/4);
		}
		else{
			u2g_now_data = (u2)(7);
		}
	}
	else if( u2g_ad_buffer0_temp < (u2g_ad_buffer_temp / 2) ){
		if(u2g_ad_buffer_temp >= NOISE_FILTER_ADD + NOISE_FILTER_MIN){
			u2g_now_data = (u2)(u2g_ad_buffer_temp - NOISE_FILTER_ADD);
		}
		else if(u2g_ad_buffer_temp < NOISE_FILTER_MIN){
			u2g_now_data = (u2)(u2g_ad_buffer_temp / 2);
		}
		else{
			u2g_now_data = (u2)(NOISE_SET_MIN);
		}
	}
	else{}
}


void bad_data_del(u2 u2_pre_valu,u2 u2_now_val)
{
	u2g_ad_buffer0_temp = u2_now_val;		
	u2g_ad_buffer_temp = u2_pre_valu;		
	
	if( u1g_ad_num == CURR ){
		if( u2_pre_valu == 0x00 ){
			Fg_f_ad_ok = 0;
			if( u2_now_val > LIMIT_FROM_0 ){
				u2_now_val = VALUE_LIMIT_FROM_0;
			}
			else{}
		}
		else{
			cul_bad_data_del();
		}
	}
	else{
		if( (u2_pre_valu > (u2_now_val * 2))||
			(u2_pre_valu < (u2_now_val / 2)) ){
			Fg_f_ad_ok = 1;
		}
		else{}
	}
}

void learn_data_set(void){
	u1 u1a_i = 0;
	u1 u1a_j = 0;

	for( u1a_j = 0;u1a_j <= MAX_SECTION;u1a_j++){
			for( u1a_i = 0;u1a_i <= 4;u1a_i++ ){
				
					u2g_over_lev_b[u1a_j][u1a_i] = 0x00;
					u2g_open_over_lev_b[u1a_j][u1a_i] = 0x00;
			}
			
			u2g_over_lev_b[u1a_j][4] = u2g_std_max_huka;
			u2g_open_over_lev_b[u1a_j][4] = u2g_open_std_max_huka;
			u2g_copy_max_learn_b[u1a_j] = 0x00;
	}
	u2g_open_std_learn = u2g_open_std_max_huka;

	for( u1a_j = 0;u1a_j <= MAX_SECTION;u1a_j++){
		u2g_over_lev_b[u1a_j][4] = u2g_huka_jougen;
	}

	u2g_learn_buffer = u2g_ajst_open_max_huka;//u2g_open_std_max_huka;
	u2g_learn_buffer_close = u2g_huka_jougen;
	u2g_max_learn_b = 0;
	u1g_f_learn_open_max_huka = 0;	
	u1g_f_learn_close_all_huka = 0;	
    
	u1g_f_open_learn_comp = 0;
	u1g_f_open_spot_learn = 0;
	u1g_f_open_small_size = 0;
	u1g_f_open_large_size = 0;
	u1g_f_open_learn_error = 0;
	u1g_f_close_learn_comp = 0;
}


void calculate_error(void)
{
////	u4 u4a_size_cal;
	u1 u1a_line_stop = 0;
	
	if(u2g_learn_buffer_close < LEARN_CLOSE_MIN){
		u2g_learn_buffer_close = LEARN_CLOSE_MIN;
	}
	else{}
	
	
	switch(u1g_lev_huka){
        
		default:
#if 0
//			// u1a_line_stop = 10T
//			// u1a_line_stop = 16072/16384 *x - 4
			u1a_line_stop = (u2)(((16072 * (u4)u2g_learn_buffer_close) / 16384) - 4);
#else
//			// u1a_line_stop = 10T
//			// u1a_line_stop = 14467/16384 *x - 1
			u1a_line_stop = (u1)((((u4)14467 * (u4)u2g_learn_buffer_close) / (u4)16384) - (u4)1);
#endif
			break;
	}
		
		
	if( u1a_line_stop >= 0x19 )
		{
			u1a_line_stop = 0x19;
		}
	else if(u1a_line_stop < 8){
		u1a_line_stop = 8;
	}
	else{}
		
}

void make_section(void){
	if( s2g_cnt_plus <= 0x0000)
		{
			u1g_n_section = 0x00;
		}
	else
		{
			u1g_n_section = (u1)((u2)s2g_cnt_plus / (u2)ONE_SEC_P );
		}
	if( u1g_n_section >= MAX_SECTION)
		{
			u1g_n_section = MAX_SECTION;
		}
	else{}
}


void calcu_std_huka(void)
{
	u1g_p_hosei = u1g_b_p_hosei;
	Fg_f_p_hugo = Fg_b_f_p_hugo;
	
////	make_section();
	if( u1g_mode == U1G_OPEN_MODE )
	{
		if(u1g_n_section != 0){
//			//u2g_cal_b = u2g_open_over_lev_b[u1g_n_section][4];
			u2g_cal_b = u2g_learn_buffer;
		}
		else{
			if( (u1g_current_mode >= 160) && (u1g_current_mode < 200) ){
//				//u2g_cal_b = u2g_open_over_lev_b[u1g_n_section][4];
				u2g_cal_b = u2g_learn_buffer;
			}
			else{
//				//u2g_cal_b = u2g_jougen_open_over_lev_b;
				u2g_cal_b = u2g_learn_buffer;
			}
		}
		hosei_main();
		plus_a_cal_open();
//		/*
//		if(!u1g_n_section){
//			if( (u1g_current_mode >= 160) && (u1g_current_mode < 200) ){
//			}
//			else if(u1g_motor_speed != 0){
//			}
//			else{
//				u2g_kei = (u2)(u2g_kei/4);
////				u2g_kei = (u2)(4);
//			}
//		}
//		else{}
//		*/
	}
	else
	{
		u2g_cal_b = u2g_over_lev_b[u1g_n_section][4];
		hosei_main();
		plus_a_cal();
	}
}

void adjust_std_huka_1857to1000(void)
{
	u2 u2a_motor_ad_1ji = 0;

		if(u2g_std_huka < 16){
			u2g_std_huka = 16;
		}
		else{}

		if(u2g_std_huka > u2g_max_const_huka){
			u2g_std_huka = u2g_max_const_huka;
		}
		else{}
		
	u2a_motor_ad_1ji = (u2)((MOTOR_AD_1857to1000_1JI * (u4)u2g_std_huka) / 16384);
	
		if(u2a_motor_ad_1ji > MOTOR_AD_1857to1000_CONST){
			u2g_std_huka = (u2)(u2a_motor_ad_1ji - MOTOR_AD_1857to1000_CONST);
		}else{
			u2g_std_huka = (u2)U1L_ZERO;
		}
}

void ad_start_set(u1 u1_ad_num)
{
	if( u1g_ope_state_f == 1 ){
		select_ad_class(CURR);
		u1g_ad_num = CURR;
		u1g_limittime = LIMIT_TIME_8BYTE;
	}
	else{

		switch( u1_ad_num ){
			case CURR:
				select_ad_class(VER);
				u1g_ad_num = VER;
				u1g_limittime = LIMIT_TIME_8BYTE;
				break;
			case VER:
				select_ad_class(TEMP);
				u1g_ad_num = TEMP;
				u1g_limittime = LIMIT_TIME_8BYTE;

				break;
			case TEMP:
				select_ad_class(CURR);
				u1g_ad_num = CURR;
				u1g_limittime = LIMIT_TIME_8BYTE;

				break;
			default:
				break;
		}
	}
}


u2 capture_ad_start(u1 u1_num,u1 u1_usedata_num)
{
	u1 u1a_i = 0,u1a_j = 0;
	u2 u2a_temp = 0;
	
    u1g_limit_ad = 0;
	R_ADC_Start();
	while( u1g_limit_ad < u1g_limittime ){
		;//__nop();
	}
	//R_ADC_Stop();
	u1g_limit_ad = 0;

	for( u1a_j = 0; u1a_j < (u1)(u1_num - 1) ; u1a_j++ ){
		for( u1a_i = (u1)(u1_num - 1); u1a_i > u1a_j; u1a_i-- ) {
			if( u2g_raw_data[u1a_i - 1] < u2g_raw_data[u1a_i] ){
				u2a_temp = u2g_raw_data[u1a_i];
				u2g_raw_data[u1a_i] = (0x3fff & u2g_raw_data[u1a_i - 1]);//mino
				u2g_raw_data[u1a_i - 1] = (0x3fff & u2a_temp);//mino
			}
			else{}
		}
	}

	return u2g_raw_data[u1_usedata_num];
}

u1 adopt_data_num_set(u1 num_adopt)
{
	num_adopt++;
	if( num_adopt >= 4 ){
		u1g_f_limit_average = 0;
		num_adopt = 0;
	}
	else{}
	return num_adopt;

}

s2 absolute_calculate( s2 s2_num_cal1,s2 s2_num_cal2 )
{
	s2 s2_value_abs = 0;
	
	if( s2_num_cal1  < s2_num_cal2 ){
		s2_value_abs = s2_num_cal2 - s2_num_cal1;
	}
	else{
		s2_value_abs = s2_num_cal1 - s2_num_cal2;
	}
	
	return s2_value_abs;
	
}

void select_learn_max_data(void){
	
	u1 u1l_index_i= 0;
	u2 u2l_instant_learn_buffer=0;

	if( (u1g_Fg_jougen_area > u1g_Fg_copy_jougen_area) || (u1g_different_mode == 1) || (Fg_f_finish_soft_start == 1) ){
	
		if(u1g_Fg_jougen_area == 1){
			
			for( u1l_index_i = 0;u1l_index_i <= u1g_num_section;u1l_index_i++ ){
					
				if( u2g_open_over_lev_b[u1l_index_i][4] >= u2l_instant_learn_buffer ){
					u2l_instant_learn_buffer = u2g_open_over_lev_b[u1l_index_i][4];
				}
				else{}
			}
			if( u2l_instant_learn_buffer == 0 ){						
				u2l_instant_learn_buffer = u2g_max_const_huka;			
			}else if( u2l_instant_learn_buffer < LEARN_OPEN_MIN ){		
				u2l_instant_learn_buffer = LEARN_OPEN_MIN;				
			}
			else{}
			u2g_open_over_lev_b[0][4] = u2l_instant_learn_buffer;
			
			u2g_cal_b = u2g_open_over_lev_b[0][4];	

			hosei_main();
			plus_a_cal_open();
		}
	}

}

static void hosei_culc_temp(void)
{
	u4 u4l_ad_temp_temp = 0;
	u2 u2a_diff_temp = 0;
	
#ifndef	NO_TEMP_HOSEI

	u4l_ad_temp_temp = u2g_ad_now[(TEMP - CURR)];
	
	if(u4l_ad_temp_temp < U2L_TEMP_CONVERT_BORDER){
		s2g_temp_now_signed = (s2)((s4)TEMP_NORMAL_CONST - (s4)( (TEMP_NORMAL_1JI*(s4)u4l_ad_temp_temp)/KETA_10000 ));	
	}
	else{	
		s2g_temp_now_signed = (s2)((s4)TEMP_VERY_COLD_CONST - (s4)( (TEMP_VERY_COLD_1JI*(s4)u4l_ad_temp_temp)/KETA_10000 ));	
	}

	if(u1g_Fg_temp_ad_error == 1){
		s2g_temp_now_signed = S2G_STANDARD_TEMP;
	}
	else{}

	if(s2g_temp_now_signed < S2L_HOSEI_TEMP_MIN){
		s2g_temp_now_signed = S2L_HOSEI_TEMP_MIN;
	}
	else{}
	
	if(s2g_temp_now_signed > S2L_HOSEI_TEMP_MAX){
		s2g_temp_now_signed = S2L_HOSEI_TEMP_MAX;
	}
	else{}

	if(s2g_temp_now_signed >= S2G_STANDARD_TEMP){
		u2a_diff_temp = (u2)(s2g_temp_now_signed - S2G_STANDARD_TEMP);
		u1g_temp_hosei = (u1)(u2a_diff_temp * HOSEI_HOT_1JI / KETA_10);
	}

	else{
		u2a_diff_temp = (u2)(S2G_STANDARD_TEMP - s2g_temp_now_signed);
		u1g_temp_hosei = (u1)((u2a_diff_temp * HOSEI_COLD_1JI / KETA_10) + HOSEI_COLD_CONST);
	}

	if(u1g_temp_hosei > U1L_TEMP_HOSEI_MAX){
		u1g_temp_hosei = U1L_TEMP_HOSEI_MAX;
	}
	else{}

#endif
}

static void hosei_culc_ver(void)
{
//	/*if(u1g_ad_ref[1] == 1){
	
		Fg_f_ver_under = 0;

		u4g_now_ver = ( ( (u4)POWER_VER_1JI * (u4)u2g_ad_now[(VER - CURR)]) + (u4)POWER_VER_CONST ) / (u4)KETA_10000;
	
		if( u4g_now_ver < (u4)100 ){
			Fg_f_ver_under = 1;
			u1g_b_ver_hosei = (u1)((u4)9*( (u4)100 - (u4g_now_ver) )/(u4)10);
		}
		else{
			u1g_b_ver_hosei = (u1)(9*( (u4g_now_ver) - 100 )/10);
		}
		if( u1g_b_ver_hosei >= VER_MAX_HOSEI ){
			u1g_b_ver_hosei = VER_MAX_HOSEI;
		}
		else{}
		
		if(u1g_Fg_ver_ad_error == 1){
			Fg_f_ver_under = 0;
			u1g_b_ver_hosei = VER_MAX_HOSEI;
		}
		else{}
		
		if((u4g_now_ver <= 85) || (u4g_now_ver >= 115) ){ 
			if( (( u1g_flash_type_error == 0x08) && ( u2g_flash_num_times != u2g_num_move )) ||
				( u1g_flash_type_error != 0x08 ) ){
					u1g_error_mode = ERR_POWER;
					a_vog_error_status_store(u1g_current_mode,u1g_signal,(u1)u4g_now_ver);
			}
		}
		else{}
//	/*}*/
}
static void ad_data_full_buffer(void)
{
	if( u1g_f_limit_average == 1 ){
		u1g_ad_ref[u1g_ad_num_temp] = 0;
	}
	else{}

}

static void ad_port_select(void)
{
	if(u1g_ad_num == 0){
		u1g_ad_num = TEMP;		
		u1g_f_limit_average = 1;	
	}
	else{}
	
	if( u1g_mode == U1G_STOP_MODE ){
		if( check_torque_test_exec() != U1G_FACT_TRQ_STOP ){

			P_VER_POWER_1;
			if(u1g_ad_num == VER){
//				/* u1g_ad_num = VER;
			}else{
				u1g_ad_num = CURR;
			}
		}
		else{
			u1g_ad_num = VER;
			if( u1g_ad_num_VER_1sec >= U1L_AD_VER_TIME){
				P_VER_POWER_1;
				u1g_ad_num_VER_1sec = 0;
				u1g_ad_num = CURR;
			}
			else if( u1g_ad_num_VER_1sec >= U1L_AD_VER_POWER_ON_TIME ){
				u1g_ad_num_VER_1sec++;	
				P_VER_POWER_1;
			}
			else{
				 u1g_ad_num_VER_1sec++;	
				 P_VER_POWER_0;
			}
		}
	}else{
		u1g_ad_num_VER_1sec = 0;
	}
}

static void watch_temp_value(void){

	u1 u1a_i = 0;

	if( u1g_ope_state_f == 1 ){
		u1l_temp_init_num = 0;
		for( u1a_i = 0; u1a_i < NUM_AD_CHECK_DATA; u1a_i++ )
			{
				u2g_check_temp_ad_data[u1a_i] = 0;
			}
	}
	else{}
	
	if(u1g_ad_ref[TEMP - CURR] == 1)
		{
			u1g_ad_ref[TEMP - CURR] = 0;

			for( u1a_i = 0; u1a_i < (NUM_AD_CHECK_DATA - 1); u1a_i++ )
				{
					u2g_check_temp_ad_data[u1a_i] = u2g_check_temp_ad_data[u1a_i + 1];
				}
			u2g_check_temp_ad_data[NUM_AD_CHECK_DATA - 1] = u2g_ad_now[(TEMP - CURR)];
			
			if(NUM_AD_CHECK_DATA > u1l_temp_init_num)
				{
					u1l_temp_init_num++;
				}
			else
				{
					check_temp_error();
				}
		}
	else{}
	
	return;
}

static void check_temp_error(void){

	u1 u1a_i = 0;
	u1 u1a_center_num = NUM_AD_CHECK_DATA / 2;
	u2 u2a_temp_ad_data[10];//NUM_AD_CHECK_DATA

	for( u1a_i = 0; u1a_i < NUM_AD_CHECK_DATA; u1a_i++ )
		{
			u2a_temp_ad_data[u1a_i] = u2g_check_temp_ad_data[u1a_i];
		}
	sort_check_ad_data(u2a_temp_ad_data);

	if(get_ecu_test_state() == ECU_NO_TEST){
		u1l_f_temp_error_stop = 0;
		
		if( (u2a_temp_ad_data[u1a_center_num] <= U2L_TEMP_OPEN_AD) ||
			(U2L_TEMP_SHORT_AD <= u2a_temp_ad_data[u1a_center_num]) ) {
			u1g_Fg_temp_ad_error = 1;
		}else{
			u1g_Fg_temp_ad_error = 0;
		}
	}else{
        
		if( (u2a_temp_ad_data[u1a_center_num] <= U2L_TEMP_OPEN_AD) ||
			(U2L_TEMP_SHORT_AD <= u2a_temp_ad_data[u1a_center_num]) )
			{
				if(u1g_Fg_ecu_temp_ad_error == 0){
					Fg_key_stop = 1;
				}
				else{}
				u1g_Fg_ecu_temp_ad_error = 1;
				u1l_f_temp_error_stop = 1;
			}
		else
			{
				if(u1g_Fg_ecu_temp_ad_error == 1){
					u1g_f_reset_after_write = 1;
				}
				else{}
				u1g_Fg_ecu_temp_ad_error = 0;
				u1l_f_temp_error_stop = 0;
			}
	}
	
	return;
}

static void watch_ver_value(void){

	u1 u1a_i = 0;

	if( u1g_ope_state_f == 1 ){	
		u1l_ver_init_num = 0;
		for( u1a_i = 0; u1a_i < NUM_AD_CHECK_DATA; u1a_i++ )
			{
				u2g_check_ver_ad_data[u1a_i] = 0;
			}
	}
	else{}

	if( (u2g_ad_now[(VER - CURR)] <= U2L_VER_OPEN_AD) &&
		(u2l_ver_err_cnt_time < U2L_MAX) )
		{
			u2l_ver_err_cnt_time++;
		}
	else
		{
			u2l_ver_err_cnt_time = 0;
		}
	
	if(u1g_ad_ref[VER - CURR] == 1)
		{
			u1g_ad_ref[VER - CURR] = 0;

			for( u1a_i = 0; u1a_i < NUM_AD_CHECK_DATA - 1; u1a_i++ )
				{
					u2g_check_ver_ad_data[u1a_i] = u2g_check_ver_ad_data[u1a_i + 1];
				}
			u2g_check_ver_ad_data[NUM_AD_CHECK_DATA - 1] = u2g_ad_now[(VER - CURR)];
			
			if(NUM_AD_CHECK_DATA > u1l_ver_init_num)
				{
					u1l_ver_init_num++;
				}
			else
				{
					check_ver_error();
				}
		}
	else{}
	
	return;
}

static void check_ver_error(void){

	u1 u1a_i = 0;
	u1 u1a_center_num = NUM_AD_CHECK_DATA / 2;
	u2 u2a_ver_ad_data[10];//NUM_AD_CHECK_DATA

	for( u1a_i = 0; u1a_i < NUM_AD_CHECK_DATA; u1a_i++ )
		{
			u2a_ver_ad_data[u1a_i] = u2g_check_ver_ad_data[u1a_i];
		}
	sort_check_ad_data(u2a_ver_ad_data);

	if(get_ecu_test_state() == ECU_NO_TEST){
		u1l_f_ver_error_stop = 0;
		
		if( (u2a_ver_ad_data[u1a_center_num] <= U2L_VER_OPEN_AD) ||
			(U2L_VER_SHORT_AD <= u2a_ver_ad_data[u1a_center_num]) ) {
			u1g_Fg_ver_ad_error = 1;
		}else{
			u1g_Fg_ver_ad_error = 0;
		}
	}else{

		if(u2a_ver_ad_data[u1a_center_num] <= U2L_VER_OPEN_AD)
			{
				if( (u1g_Fg_ecu_ver_ad_error == 0) && (u2l_ver_err_cnt_time >= U2L_VER_ERROR_CHECK_TIME) ){
					Fg_key_stop = 1;
					u1g_Fg_ecu_ver_ad_error = 1;
				}
				else{}
				u1l_f_ver_error_stop = 1;
			}

		else if(U2L_VER_SHORT_AD <= u2a_ver_ad_data[u1a_center_num])
			{
				if(u1g_Fg_ecu_ver_ad_error == 0){
					Fg_key_stop = 1;
				}
				else{}
				u1g_Fg_ecu_ver_ad_error = 1;
				u1l_f_ver_error_stop = 1;
			}
		else
			{
				if(u1g_Fg_ecu_ver_ad_error == 1){
					u1g_f_reset_after_write = 1;
				}
				else{}
				u1g_Fg_ecu_ver_ad_error = 0;
				u1l_f_ver_error_stop = 0;
			}
	}
	
	return;
}

static void sort_check_ad_data(u2 *u2a_raw_ad_data){

	u1 u1a_i = 0, u1a_j = 0;
	u2 u2a_temp = 0;

	for( u1a_j = 0; u1a_j < (NUM_AD_CHECK_DATA - 1) ; u1a_j++ ){
		for( u1a_i = NUM_AD_CHECK_DATA - 1; u1a_i > u1a_j; u1a_i-- ) {
			if( u2a_raw_ad_data[u1a_i - 1] < u2a_raw_ad_data[u1a_i] ){
				u2a_temp = u2a_raw_ad_data[u1a_i];
				u2a_raw_ad_data[u1a_i] = (0x3fff & u2a_raw_ad_data[u1a_i - 1]);
				u2a_raw_ad_data[u1a_i - 1] = (0x3fff & u2a_temp);
			}
			else{}
		}
	}
	
	return;
}

void check_ad_error_stop(void)
{
	if( (u1l_f_temp_error_stop) || (u1l_f_ver_error_stop) ){
		Fg_osikiri_open = 0;
		Fg_osikiri_close = 0;
		u1g_key_3sw = 0;
		Fg_key_open = 0;
		Fg_key_close = 0;
		Fg_key_stop = 0;
	}
}

u1 get_max_close_learn_data(void){
	u1 u1a_j = 0;
	u1 u1a_max_learn_data = 0;

	for( u1a_j = 0;u1a_j <= MAX_SECTION;u1a_j++ ){
		if(u1a_max_learn_data < (u2)(*(&u1g_flash_learndata_top + u1a_j))){
			u1a_max_learn_data = (u1)(*(&u1g_flash_learndata_top + u1a_j));			
		}
	}
	
	return u1a_max_learn_data;
}
