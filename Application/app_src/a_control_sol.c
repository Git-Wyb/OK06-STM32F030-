/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "Gpio.h"
#include "variables.h"
#include "def_local.h"
#include "functions.h"
#include "ecu_test.h"
#include "anjou_test.h"

static u1 u1l_step_sol_out = 0;						
static u1 u1l_f_sol_short = FALSE;				

#define U2L_READY_VER_KEEP_OUT	((u2)64)			
#define U2L_START_SOLOUT		((u2)10)			
#define U2L_END_SOLOUT			((u2)667)		


static void sol_out_process(void);


typedef enum {
	SOL_OUT_START,				
	SOL_OUT_VER_KEEP_WAIT,		
	SOL_OUT_ON_WAIT,	
	SOL_OUT_OFF_WAIT,
	SOL_OUT_END			
} sol_out_step;	



void sol_ope_main(void)
{
	ecu_test_id ecu_test_state = get_ecu_test_state();
	
	
	if( u1g_f_solenoid_mode == 1 )
	{
		
		sol_out_process();
	}
	else if( (ecu_test_state != ECU_SOLENOID_TEST) && (ecu_test_state != ECU_SOLENOID_STOP) )
	{
		
		Fg_sol_out = 0;
		Fg_ver_keep = 0;
		u1l_step_sol_out = SOL_OUT_START;	
	}
	else{}
	
}


static void sol_out_process(void)
{
	static u2 u2a_c_timer_sol = 0;		
	u1 u1a_torque_test_state = 0;		
	u1 u1a_denki_test_state = 0;		

	switch( u1l_step_sol_out ){
	case SOL_OUT_START:			
		u2a_c_timer_sol = 0;
		u1l_step_sol_out++;
		break;
	case SOL_OUT_VER_KEEP_WAIT:		
		u2a_c_timer_sol++;
		if( u2a_c_timer_sol >= U2L_READY_VER_KEEP_OUT ){
			u2a_c_timer_sol = 0;
			u1l_step_sol_out++;
		} else{}
		break;
	case SOL_OUT_ON_WAIT:			
		Fg_ver_keep = 1;			
		u2a_c_timer_sol++;
		if( u2a_c_timer_sol >= U2L_START_SOLOUT ){
			u2a_c_timer_sol = 0;
			u1l_step_sol_out++;
		} else{}
		break;
	case SOL_OUT_OFF_WAIT:		
		Fg_ver_keep = 1;	
		Fg_sol_out = 1;			
		
		u1a_torque_test_state = check_torque_test_exec();
		u1a_denki_test_state = check_denki_test_exec();

		
		if( (u1g_mode != U1G_OSIKIRI_OPEN_MODE) ||	
			(u1a_torque_test_state == U1G_FACT_TRQ_EXEC) || (u1a_denki_test_state == U1G_FACT_DENKI_EXEC) )
		{
			u2a_c_timer_sol++;
			if( u2a_c_timer_sol >= U2L_END_SOLOUT ){
				u2a_c_timer_sol = 0;
				u1g_f_move_sol = 1;
				u1l_step_sol_out++;
			}else{}
		}else{}
		break;
	case SOL_OUT_END:			
		Fg_ver_keep = 0;		
		Fg_sol_out = 0;			
		break;
	default:
		u1l_step_sol_out = SOL_OUT_START;
		u2a_c_timer_sol = 0;
		break;
	}
}


void check_sol_short_error(void)
{
	
	if( u1l_f_sol_short == TRUE ){
		u1g_error_mode = ERR_SOL_SHORT;		
		a_vog_error_status_store(u1g_current_mode,u1g_signal,u1g_current_mode);
		u1l_f_sol_short = FALSE;
	}
	else{}
}


void solenoid_short(void)
{
#ifdef OK04
	
	if( (get_ecu_test_state() != ECU_SOLENOID_TEST) && (P_SOLENOID == 1) ){
		
		P_SOLENOID = 0;			
		P_VER_KEEP = 1;			
		u1l_step_sol_out = SOL_OUT_END;		

		u1l_f_sol_short = TRUE;
	}
	else{}
#endif
}
