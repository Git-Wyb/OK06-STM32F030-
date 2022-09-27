#include "Sys.h"

#include "variables.h"
#include "constants.h"
#include "functions.h"
//#include "serial_transmission.h"
#include "trq_adjust_trqchange.h"
#include "Gpio.h"

void variable_setup(void)
{
	u1g_fg_charge_pump_enable = 0;
	/* 0 until motor operation */
	u1g_shutter_state = 0;
	u1g_step = 0;
	u2g_c_interval_plus = 0;
	P_RELAY_1_0;
	P_RELAY_2_0;
	P_RELAY_3_0;
	//P_SOLENOID = 0;
	u1g_Fg_power_on = 1;
	//R_INTC8_Start();
	u2g_key = 0;
/* 170407mino	u1g_fg_flash_initial = 1; */
	u1g_f_ok_set_on_shortbreak = 1;	
    
    initial_huka();
}

void initial_huka(void)
{
	learn_data_set();	
	u2g_max_const_huka = U2_TRQ_AJST_HIGH_SPEED_100;	/* 4.05 */
	u2g_open_std_max_huka = U2_TRQ_AJST_HIGH_SPEED_100;	/* 4.05 */
	u2g_max_huka = u2g_max_const_huka;
	u2g_std_huka = u2g_max_const_huka;
	u2g_nor_huka = u2g_max_const_huka;
	u2g_std_learn = u2g_max_const_huka;
	u2g_open_std_learn = u2g_max_const_huka;
	u2g_std_max_huka = u2g_max_const_huka;
	u2g_learn_max_huka = u2g_max_const_huka;
	
	u2g_osikomi_const_huka  = U2_TRQ_AJST_HIGH_SPEED_100;		/* 4.05 */
	u2g_open_std_osikomi_huka  = U2_TRQ_AJST_HIGH_SPEED_100;	/* 4.05 */
}
void rest_startup(void)
{
	while(1)
	{
		;						/*  infinite loop; */
	}
}


