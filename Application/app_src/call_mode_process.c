#include "Sys.h"
#include "variables.h"
#include "constants.h"
#include "functions.h"
//#include "serial_transmission.h"
#include "a_data_exchange.h"
#include "Gpio.h"
#define	TEST_SPEED_CHANGE

static void a_vol_check_fullclose_learncondition_100(void);
static void a_vol_check_stop_102(void);
static void a_vol_check_learn_condition_at_102(void);
static void a_vol_check_position_128(void);
static void a_vol_check_position_130(void);
/* static void a_vol_check_power_on_160(void); */
static void a_vol_check_stop_180_183(void);
/* static void a_vol_check_lock_error_110(void); */
static void a_vol_check_position_199(void);
static void process_short_open(void);
static void process_ready_open(void);


void call_mode_process(void)
{
	u1 u1a_i = 0, u1a_j = 0;

	u1g_threshold_huka = 0;		
	
	u1g_motor_speed = 0;		/* 1169rpm */
	
	if(u1g_different_mode == 1){
		s2g_cnt_plus_speed_down = 20000;
	}
	else{}
	
	u1g_f_solenoid_mode = 0;		

	if( (u1g_different_mode == 1) && ((u1g_previous_mode == 103) || (u1g_previous_mode == 107)) && (u2g_copy_max_learn_b[u1g_n_section] < u2g_max_learn_b) ){
		u2g_copy_max_learn_b[u1g_n_section] = u2g_max_learn_b;
	}
	else{}

	if(u1g_pre_mode != u1g_mode){
		u2g_max_learn_b = 0;
	}
	else{}

	if( (u1g_f_learn_close_all_huka == 0) && (u1g_different_mode == 1) && (u1g_previous_mode == 108) && (u1g_current_mode != 100) ){
		for( u1a_j = 0; u1a_j <= u1g_num_section; u1a_j++){
			for( u1a_i = 0; u1a_i <= 3; u1a_i++){
				u2g_over_lev_b[u1a_j][u1a_i] = 0;
			}
			u2g_over_lev_b[u1a_j][4] = u2g_huka_jougen;
		}
		u2g_cal_b = u2g_huka_jougen;
	}
	else{}

	if(u1g_current_mode < 10){				
		current_mode_0_9();
	}
	else{}
	
	if((u1g_current_mode >= 10) && (u1g_current_mode < 20)){
		current_mode_10_19();
	}
	else{}
	
	if((u1g_current_mode >= 20) && (u1g_current_mode < 100)){
		current_mode_20_99();
	}
	else{}
	
	if((u1g_current_mode >= 100) && (u1g_current_mode < 110)){
		current_mode_100_109();
	}
	else{}
	
	if((u1g_current_mode >= 110) && (u1g_current_mode < 120)){	
		current_mode_110_119();
	}
	else{}
	
	if((u1g_current_mode >= 120) && (u1g_current_mode < 160)){	
		current_mode_120_159();
	}
	else{}
	
	if((u1g_current_mode >= 160) && (u1g_current_mode < 170)){	
		current_mode_160_169();
	}
	else{}
	
	if((u1g_current_mode >= 170) && (u1g_current_mode < 180)){
		current_mode_170_179();
	}
	else{}
	
	if((u1g_current_mode >= 180) && (u1g_current_mode < 190)){	
		current_mode_180_189();
	}
	else{}
	
	if((u1g_current_mode >= 190) && (u1g_current_mode <= 255)){	
		current_mode_190_255();
	}
	else{}
	
	if(u1g_mode == U1G_STOP_MODE){
		
		s2g_cnt_plus_start = 0;

		if(u1g_pre_mode != u1g_mode){
			
			s2g_cnt_plus_start_for_stop = s2g_cnt_plus;
		}
		else{}
	}
	else{
	
		if(u1g_pre_mode != u1g_mode){
		
			s2g_cnt_plus_start = s2g_cnt_plus;
		}
		else{}
		
		s2g_cnt_plus_start_for_stop = 0;
	}
}



void open_kei_set(void)
{
	if( u1g_Fg_jougen_area == 1 ){	
		u2g_cal_b = u2g_learn_buffer;/* u2g_open_over_lev_b[u1g_n_section][4]; */
	}else{					
		u2g_cal_b = u2g_max_const_huka;	
	}
	hosei_main();
	plus_a_cal_open();
}

void close_kei_set(void)
{
	u2g_cal_b = u2g_over_lev_b[u1g_n_section][4];
	hosei_main();
	plus_a_cal();
}

void set_close_huka(void)
{
	u1 u1a_j = 0;
		for( u1a_j = 0;u1a_j <= MAX_SECTION;u1a_j++){
			
			if(Fg_f_no_learn_data == 1){
				/* u2g_kahuka_mirror[]*/
				u2g_over_lev_b[u1a_j][3] = u2g_std_max_huka;
				u2g_over_lev_b[u1a_j][4] = u2g_std_max_huka;
			}
			else{
			
				u2g_over_lev_b[u1a_j][3] = u2g_kahuka_mirror[u1a_j];
				u2g_over_lev_b[u1a_j][4] = u2g_kahuka_mirror[u1a_j];
			}
		}
}

void current_mode_0_9(void)
{
	switch(u1g_current_mode){
		case 0:		
		
			s2g_cnt_plus = 0;
			s2g_size_ram[0] = 0;
			s2g_size_ram[1] = 0;
			s2g_size_ram[2] = 0;
			
			if(u1g_current_mode != u1g_previous_mode){
				reset_learn_data();
			}
			
			process_stop();
			break;
			
		case 1:			
			process_open_u();
			u1g_threshold_huka = 2;	
			break;
			
		case 2:			
			process_osikiri_open();
			break;
			
		case 3:			
			process_osikiri_close();
			break;
			
		case 4:			
			process_open_u();
			u1g_threshold_huka = 2;	
 			break;
			
		case 5:			
			process_ready_open();
			u1g_threshold_huka = 2;	/*10Nm */
			break;
			
		case 6:		
		
			s2g_cnt_plus = 0;
			process_stop();
			break;
			
		case 7:		
			process_osikiri_open();
			break;
			
		case 8:		
			process_osikiri_close();
			break;
			
		case 9:		
			process_stop();
			break;
			
		default:	
			process_stop();
			break;
	}
}

void current_mode_10_19(void)
{
		switch(u1g_current_mode){
			case 10:	
				
				if(u1g_different_mode == 1){
					s2g_cnt_plus = 0;
				}
				else{}
				
				process_stop();
				break;
				
			case 11:	
				process_close_u();
				u1g_threshold_huka = 2;
#ifndef	NO_LEARN
				seprate_block();			
#endif
				break;
				
			case 12:	
				process_open_u();
				u1g_threshold_huka = 2;
 				break;
				
			case 13:	
				process_open_u();
				u1g_threshold_huka = 2;
				break;
				
			default:	
				process_stop();
				break;
		}
}



void current_mode_20_99(void)
{
	s2 s2a_j = 0;
		switch(u1g_current_mode){
			case 20:	
				process_stop();
				break;
				
			case 21:	
				process_stop();
				break;
				
			case 22:		
				process_open_u();
				u1g_threshold_huka = 2;
				break;
				
			case 23:	
				process_short_open();
				u1g_threshold_huka = 2;
				break;
				
			case 24:	
				process_open_u();
				u1g_threshold_huka = 2;	
				break;
				
			case 25:	
			
				if( u1g_previous_mode == 11 ){
					u2g_huka_jougen = u2g_over_lev_b[0][0];
										
					for( s2a_j = 0; s2a_j <= MAX_SECTION; s2a_j++){
						u2g_over_lev_b[s2a_j][4] = u2g_huka_jougen;
					}
					u2g_cal_b = u2g_huka_jougen;
				}
				else{}
					
				process_close_u();
				break;
				
			case 26:	
				process_osikiri_open();
				break;
				
			case 27:	
				process_osikiri_close();
				break;
				
			case 28:		
				process_ready_open();
				break;
				
///* 			case 29:	
//                break; */

			default:	
				process_stop();
				break;
		}
}

void current_mode_100_109(void)
{
		switch(u1g_current_mode){
			case 100:	
			
				a_vol_check_fullclose_learncondition_100();
				process_stop();

				break;
				
			case 101:	
				process_stop();
				break;
				
			case 102:	
				a_vol_check_stop_102();
				Fg_f_reset_able = 1;
				process_stop();
				break;
				
			case 103:		
				process_open_u();		
				if( u1g_f_learn_open_max_huka == 0 ){
					seprate_block();			
					select_learn_max_data();	
				}
				break;
				
			case 104:		
				process_ready_open();
				break;
				
			case 105:	
				u1g_shutter_state = SF_STOP;
				process_stop();
				break;
				
			case 106:		
				process_close_u();
				break;
				
			case 107:		
				process_open_u();
				if( u1g_f_learn_open_max_huka == 0 ){
					seprate_block();			
					select_learn_max_data();		
				}
				break;
				
			case 108:	
				process_close_u();
				seprate_block();			
				break;
				
			case 109:	
				Fg_f_reset_able = 0;
				if( u1g_previous_mode == 110 ){
					u1g_shutter_state = SF_STOP;	
				}
				else{}
				process_stop();
				break;
	
			default:	
				process_stop();
				break;
		}
}

void current_mode_110_119(void)
{
		switch(u1g_current_mode){						
			case 110:	
				/* a_vol_lock_error_110(); */
				process_shortbreak();
				break;
				
///* 			case 111:			
///* 				break; */
//				
///* 			case 112:			
///* 				break; */
				
			case 113:	
				process_osikiri_open();
				break;
				
			case 114:	
				process_osikiri_close();
				break;
				
///* 			case 115:		
///* 				break; */

			case 116:	
				process_open_u();
				u1g_threshold_huka = 2;	
				break;
				
			case 117:	
				process_open_u();
				break;
				
			case 118:	
				process_osikiri_open();
				break;
				
			case 119:	
				process_osikiri_close();
				break;
				
			default:		
				process_stop();
				break;
		}
}

void current_mode_120_159(void)
{
		switch(u1g_current_mode){	
			case 120:	
				process_open_u();
				break;
				
			case 121:		
				process_close_u();
				break;
				
			case 122:	
				process_stop_lock();
				break;
				
			case 123:	
				process_stop();
				
				break;
///* 			case 124:		
///* 				break; */

			case 125:	
				process_open_u();
				u1g_threshold_huka = 2;
				break;
				
			case 126:
				process_ready_open();
				break;
				
			case 127:
				process_stop();
				break;
			
			case 128:
				process_stop();
				a_vol_check_position_128();
				break;
				
			case 129:
				process_stop();
				break;
			case 130:	
				process_stop();
				a_vol_check_position_130();
				break;
				
			default:	
				process_stop();
				break;
		}
}

static void a_vol_check_fullclose_learncondition_100(void)
{
#ifndef	NO_LEARN

	if( u1g_previous_mode == 108  ){
		Fg_f_fin_both = 1;
		u1g_f_learn_close_all_huka = 1;
		u1g_f_close_learn_comp = 1;
		close_block_ope();
		learn_data_make();
		u2g_huka_jougen = u2g_learn_buffer_close;
		
		ready_write_data();
		
		/* if( ( u2g_over_lev_b[u1g_num_section][0] == u2g_over_lev_b[u1g_num_section][4])&&(u2g_over_lev_b[u1g_num_section][1] == u2g_over_lev_b[u1g_num_section][2])&&(u2g_over_lev_b[u1g_num_section][1] == 0 ) ){ */
		if( u1g_Fg_close_huka_learn == 0 ){
			u1g_flash_write_status = U1_HUKA_WRITE;
			u1g_cnt_e2prom_write = 0x00;
			u1g_Fg_close_huka_learn = 1;
		}
		else{}
	}
	else{
		u2g_max_learn_b = 0;
	}
#endif
	if( u1g_previous_mode == 108 ){
		if( u2g_num_now < (u2)0xffff )		
			{
				u2g_num_now++;
			}
		else
			{
				u2g_num_now = 0x0000;
			}
	}
	else{}

	if(u1g_previous_mode >= 160){
		set_close_huka();
	}
	else{}
	
	if( (u1g_cnt_e2prom_write >= U1_FLASHWRITE_TIMING) ){
		u1g_cnt_e2prom_write = 0x00;
		u1g_flash_write_status = U1_HUKA_WRITE;
	}
	else{}
}

static void a_vol_check_stop_102(void)
{

	if(u1g_different_mode == 1){
		
		/* s2g_cnt_plus_jougen = s2g_cnt_plus; */
		if( ( u1g_previous_mode != 118 ) && (u1g_previous_mode != 119) ){
			s2g_cnt_plus = 0;
		}
		
		
		if( u1g_previous_mode >= 160 ){
			s2g_lock_start_position = s2g_size_ram[0] - S2G_LOCK_ALLOW_AREA;
		}else{}
	}
	else{} 
	a_vol_check_learn_condition_at_102();
}

static void a_vol_check_learn_condition_at_102(void)
{
	if(u1g_previous_mode == 103){
		if( u2g_num_now < (u2)0xffff )		
			{
				u2g_num_now++;
			}
		else
			{
				u2g_num_now = 0x0000;
			}
	}
	else{
		u2g_max_learn_b = 0;
	}
	

	if( u1g_previous_mode >= 160 ){
		set_close_huka();
		s2g_cnt_plus = 0;
	}
	else{}
}

static void a_vol_check_position_128(void)
{
	u1g_previous_mode = 128;
	
	if(u1g_f_rangein_kagen_kitei == 1){	
		u1g_current_mode = 100;
	}else{								
		u1g_current_mode = 129;
	}
}


static void a_vol_check_position_130(void)
{

	if( (u1g_previous_mode == 100) && ( s2g_cnt_plus >= (s2)(s2g_size_ram[0] - S2G_LOCK_ALLOW_AREA) ) ){
	
		if( s2g_cnt_plus > (s2)s2g_size_ram[0] ){
			s2g_lock_start_position = (s2)s2g_size_ram[0];
		}else{
			s2g_lock_start_position = s2g_cnt_plus;
		}
		u1g_f_rangein_kagen_kitei = 1;
	}
	else{}

	if(u1g_f_rangein_kagen_kitei == 1){	
		u1g_current_mode = 109;
	}else{								
		u1g_current_mode = 101;
	}
	
	u1g_previous_mode = 130;
}

void current_mode_160_169(void)
{
	switch(u1g_current_mode){
		case 160:
			switch(u1g_previous_mode){
				case 110:
				case 164:
				case 184:
					u1g_shutter_state = SF_STOP;	
					break;
				default:
					break;
			}
			s2g_cnt_plus = 0;
			process_stop();
			break;
			
		case 161:	
			process_open_u();
			break;
			
		case 162:	
			process_close_u();
			break;
			
		case 163:	
			if( u1g_previous_mode == 164 ){
				u1g_shutter_state = SF_STOP;
			}
			else{}
			process_stop();
			break;
			
		case 164:	
			process_shortbreak();
			break;
			
		case 165:	
			process_stop();			
			break;
			
		case 166:		
			process_open_u();
			break;
			
		case 167:	
			process_osikiri_open();
			break;
			
		case 168:	
			process_osikiri_close();
			break;
			
		case 169:	
			process_close_u();
			break;
	
		default:	
			process_stop();
			break;
	}
}

///*
//static void a_vol_check_power_on_160(void)
//{
//	u1g_f_delay_lock = 1;	
//}
//*/
void current_mode_170_179(void)
{
	switch(u1g_current_mode){			
		case 170:	
			process_stop_lock();
			break;
			
		case 171:	
			process_stop();
			break;
			
		case 172:	
			process_stop();
			break;
			
		case 173:	
			process_open_u();
			u1g_threshold_huka = 2;	
			break;
			
		case 174:	
			process_short_open();
			u1g_threshold_huka = 2;	
			break;
///* 		case 175:	

///* 			break; */
		case 176:	
			process_ready_open();
			break;
		case 177:	
			process_ready_open();
			break;
///* 		case 178:	

///* 			break; */
///* 		case 179:		

///* 			break; */
		
		default:	
			process_stop();
			break;
	}
}

void current_mode_180_189(void)
{
	switch(u1g_current_mode){
		case 180:	
			a_vol_check_stop_180_183();
			process_stop();
			break;
			
		case 181:	
			process_open_u();
			break;
			
		case 182:	
			process_close_u();
			break;
			
		case 183:	
			a_vol_check_stop_180_183();
			if( u1g_previous_mode == 184 ){
				u1g_shutter_state = SF_STOP;
			}
			else{}
			process_stop();
			break;
			
		case 184:	
			process_shortbreak();			
			break;
			
		case 185:	
			process_open_u();			
			break;
			
		case 186:	
			process_stop();
			break;
			
		case 187:	
			process_osikiri_open();
			break;
			
		case 188:	
			process_osikiri_close();
			break;
			
		case 189:	
			process_close_u();
			break;
		default:	
			process_stop();
			break;
	}
}

static void a_vol_check_stop_180_183(void)
{
	if(u1g_different_mode == 1){
	
		if(  u1g_previous_mode == 165 ){	
			s2g_cnt_plus = s2g_size_ram[0] + 2;		
			s2g_lock_start_position = s2g_size_ram[0];
		}
		else{}
	}
	else{}
}

void current_mode_190_255(void)
{
	switch(u1g_current_mode){			
		case 190:	
			process_stop_lock();
			break;
			
		case 191:	
			process_stop();
			break;
			
		case 192:	
			process_stop();
			break;
			
		case 193:		
			process_open_u();
			u1g_threshold_huka = 2;
			break;
			
		case 194:	
			process_open_u();
			u1g_threshold_huka = 2;
			break;
		case 195:	
			process_open_u();
			break;
		case 196:	
			process_ready_open();
			break;
		case 197:	
			process_ready_open();
			break;
		case 198:	
			process_open_u();			
			break;
		case 199:	
			if( u1g_previous_mode == 184 ){
				u1g_shutter_state = SF_STOP;
			}
			else{}
			process_stop();
			a_vol_check_position_199();
			break;
		
		default:		
			process_stop();
			break;
	}
}

static void a_vol_check_position_199(void)
{
	u1g_previous_mode = 199;

	if(u1g_f_rangein_kagen_kitei == 1){	
		u1g_current_mode = 180;
	}else{								
		u1g_current_mode = 186;
	}
}


void process_stop(void)
{
	u2g_max_learn_b = 0;	
	
	u1g_mode = U1G_STOP_MODE;
	u1g_motor_speed = 0;	
	u1g_threshold_huka = 0;
	
	mode_stop();
}

void process_stop_lock(void)
{
	u2g_max_learn_b = 0;
	
	u1g_mode = U1G_STOP_MODE;	
	u1g_motor_speed = 0;
	u1g_threshold_huka = 0;	

	mode_wait_lock();
}

void process_shortbreak(void)
{
	u1g_mode = U1G_STOP_MODE;
	u1g_motor_speed = 0;
	u1g_threshold_huka = 0;
	
	mode_shortbreak();
}

void process_open_u(void)
{
	P_VER_POWER_1;				
	if(u1g_current_mode != u1g_previous_mode){
		open_kei_set();
	}
	else{}

	u1g_mode = U1G_OPEN_MODE;	
	u1g_motor_speed = 0;		
	u1g_threshold_huka = 0;		
	u1g_f_solenoid_mode = 1;

	mode_open_u();
}

static void process_short_open(void)
{
	process_open_u();			
	u1g_f_solenoid_mode = 0;	
}

static void process_ready_open(void)
{
	process_close_u();			
	u1g_f_solenoid_mode = 1;	
}

void process_close_u(void)
{
	P_VER_POWER_1;			
	if(u1g_current_mode != u1g_previous_mode){
		close_kei_set();
	}
	else{}

	u1g_mode = U1G_CLOSE_MODE;	
	u1g_motor_speed = 0;	
	u1g_threshold_huka = 0;

	mode_close_u();
}

void process_osikiri_open(void)
{
	P_VER_POWER_1;	

	u1g_mode = U1G_OSIKIRI_OPEN_MODE;
	u1g_motor_speed = 0;	
	u1g_threshold_huka = 2;	
	u1g_f_solenoid_mode = 1;

	mode_osikiri_open();
}

void process_osikiri_close(void)
{
	P_VER_POWER_1;			
	u1g_mode = U1G_OSIKIRI_CLOSE_MODE;
	u1g_motor_speed = 0;
	u1g_threshold_huka = 2;

	mode_osikiri_close();
}


void check_open_learn_huka(void){

	if(u1g_f_learn_open_max_huka == 0){	

		switch(u1g_current_mode){
			case 100:
			case 109:
				learn_data_set();
				break;
			case 102:
				switch(u1g_previous_mode){
					case 103:
					case 107:
						u1g_f_learn_open_max_huka = 1;		
						u1g_f_open_learn_comp = 1;
						learn_data_make();			
					
						u1g_flash_write_status = U1_SIZE_HUKA_WRITE;
						ready_write_data();
						break;
					default:
						learn_data_set();
					break;
				}
				break;
			default:
				break;
		}

		switch(u1g_current_mode){
			case 103:
			case 107:
				break;
			default:
				open_block_no_learn_ope();
				break;
		}
	}
	else{}
	
}

