#define DATF_LIGHT_VERSION
#include <string.h>
#include "Sys.h"
#include <stdlib.h>
#include "variables.h"
#include "functions.h"
#include "access_flash.h"
#include "constants.h"
#include "anjou_test.h"
#include "trq_adjust_trqchange.h"


u2 u2g_ajst_max_huka = 0;			
u2 u2g_ajst_open_max_huka = 0;		
u2 u2g_ajst_osikomi_const_huka = 0;	
u2 u2g_ajst_open_std_osikomi_huka = 0;

void a_vog_trqajst_trqinitial(void)
{
	switch( u2g_kahuka_mirror[TRQ_LEVEL_HIGH_SPEED] ){
		case U2_TRQ_AJST_HIGH_SPEED_105:
//			/* 105% */
			u2g_ajst_max_huka = U2_TRQ_AJST_HIGH_SPEED_105;
			u2g_ajst_open_max_huka = U2_TRQ_AJST_HIGH_SPEED_105;
			u2g_ajst_osikomi_const_huka = U2_TRQ_AJST_HIGH_SPEED_105;
			u2g_ajst_open_std_osikomi_huka =U2_TRQ_AJST_HIGH_SPEED_105;
			break;
		case U2_TRQ_AJST_HIGH_SPEED_95:
//			/* 95% */
			u2g_ajst_max_huka = U2_TRQ_AJST_HIGH_SPEED_95;
			u2g_ajst_open_max_huka = U2_TRQ_AJST_HIGH_SPEED_95;
			u2g_ajst_osikomi_const_huka = U2_TRQ_AJST_HIGH_SPEED_95;
			u2g_ajst_open_std_osikomi_huka =U2_TRQ_AJST_HIGH_SPEED_95;
			break;
		default:
//			/* 100% */
			u2g_ajst_max_huka = U2_TRQ_AJST_HIGH_SPEED_100;
			u2g_ajst_open_max_huka = U2_TRQ_AJST_HIGH_SPEED_100;
			u2g_ajst_osikomi_const_huka = U2_TRQ_AJST_HIGH_SPEED_100;
			u2g_ajst_open_std_osikomi_huka =U2_TRQ_AJST_HIGH_SPEED_100;	
			break;
	}

	u2g_max_const_huka = u2g_ajst_max_huka;							
	u2g_std_max_huka = u2g_ajst_max_huka;
	u2g_open_std_max_huka = u2g_ajst_open_max_huka;					
	u2g_osikomi_const_huka = u2g_ajst_osikomi_const_huka;		
	u2g_open_std_osikomi_huka = u2g_ajst_open_std_osikomi_huka;	
}

void a_vog_trqajst_dataset(u1 u1a_trq_input)
{
	switch(u1a_trq_input){

		case U1L_TRQ_AJST_UP:
			if(U2_TRQ_AJST_HIGH_SPEED_95 == u1g_flash_adjust_trq){
				u1g_flash_adjust_trq = (u1)U2_TRQ_AJST_HIGH_SPEED_100;
				u2g_kahuka_mirror[TRQ_LEVEL_HIGH_SPEED] = U2_TRQ_AJST_HIGH_SPEED_100;
			} else {
				u1g_flash_adjust_trq = (u1)U2_TRQ_AJST_HIGH_SPEED_105;
				u2g_kahuka_mirror[TRQ_LEVEL_HIGH_SPEED] = U2_TRQ_AJST_HIGH_SPEED_105;
			}
			break;
		case U1L_TRQ_AJST_DOWN:
			if(U2_TRQ_AJST_HIGH_SPEED_105 == u1g_flash_adjust_trq){
				u1g_flash_adjust_trq = (u1)U2_TRQ_AJST_HIGH_SPEED_100;
				u2g_kahuka_mirror[TRQ_LEVEL_HIGH_SPEED] = U2_TRQ_AJST_HIGH_SPEED_100;
			} else {
				u1g_flash_adjust_trq = (u1)U2_TRQ_AJST_HIGH_SPEED_95;
				u2g_kahuka_mirror[TRQ_LEVEL_HIGH_SPEED] = U2_TRQ_AJST_HIGH_SPEED_95;
			}
			break;
		default:
			break;
	}
	a_vog_trqajst_trqinitial();
	u1g_flash_write_status = U1_FACT_WRITE;
}
