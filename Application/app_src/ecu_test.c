#include "Sys.h"
#include "Gpio.h"
#include "Timer.h"
#include "functions.h"
#include "variables.h"
#include "constants.h"
#include "ecu_test.h"
#include "anjou_test.h"
#include "tst_break.h"

/*************************************************************/
/* Definition of RAM area */
#define	ECU_PORT_NUM 			2			
#define U2L_TIME_TEST_OK_MIN	(u2)23		
#define U2L_TIME_TEST_OK_MAX	(u2)1111	

TYPE_BYTE	portflag = {0};			
#define  Fg_ecu_port_set		portflag.bit.b7
#define  Fg_pre_port_ecu_test2	portflag.bit.b3
#define  Fg_pre_port_ecu_test1	portflag.bit.b2
#define  Fg_port_ecu_test2		portflag.bit.b1
#define  Fg_port_ecu_test1		portflag.bit.b0

u1 u1l_port_jun = 0;
u1 u1l_last_port[ECU_PORT_NUM] = {0};	
u1 u1l_c_port_off[ECU_PORT_NUM] = {0};	
u1 u1l_c_port_on[ECU_PORT_NUM] = {0};	
u2 u2l_ecu_test1_on_cnt = 0;
u2 u2l_ecu_test2_on_cnt = 0;

ecu_test_id ecu_test_state = ECU_NO_TEST;

static void ecu_setup(void);
static void port_in_count(void);
static void port_off_count(void);
static void port_input_check(void);
static void ecu_test_check(void);

void ecu_test_main(void)
{
	ecu_setup();
	
	if( (u1g_current_mode < 10) && (u1g_flash_finish == FACT_INIT_TORQUE_MODE) )
	{
		port_input_check();

		ecu_test_check();

		switch(ecu_test_state)
		{
			case ECU_TST_BREAK_TEST:
				u2g_t_break_duty = D_BREAK_MAX_LEVEL;
				break;
			case ECU_TST_BREAK_STOP:
				t_flag_all_clear();
				ecu_test_state = ECU_TEST_IDLE;
				break;
			case ECU_SOLENOID_TEST:
				Fg_sol_out = 1;
				break;
			case ECU_SOLENOID_STOP:
				Fg_sol_out = 0;
				ecu_test_state = ECU_TEST_IDLE;
				break;
			default:
				ecu_test_state = ECU_TEST_IDLE;
				break;
		}

		Fg_pre_port_ecu_test1 = Fg_port_ecu_test1;
		Fg_pre_port_ecu_test2 = Fg_port_ecu_test2;
	}else{
		ecu_test_state = ECU_NO_TEST;
	}
	
	return;
}


static void ecu_setup(void)
{
	if( (u1g_current_mode < 10) && (u1g_flash_finish == FACT_INIT_TORQUE_MODE) )
	{
		if(Fg_ecu_port_set == 0)
		{
//		    P0 = _00_Pn0_OUTPUT_0;
//		    PU0 = _02_PUn1_PULLUP_ON;
//		    PU4 = _01_PUn0_PULLUP_ON | _02_PUn1_PULLUP_ON;
//		    PM0 = _00_PMn0_MODE_OUTPUT | _02_PMn1_MODE_INPUT | _FC_PM0_DEFAULT;
//		    PM4 = _01_PMn0_NOT_USE | _02_PMn1_MODE_INPUT | _FC_PM4_DEFAULT;
		}
		Fg_ecu_port_set = 1;
	}
	else if(Fg_ecu_port_set == 1)
	{
//	    P0 = _00_Pn0_OUTPUT_0 | _00_Pn1_OUTPUT_0;
//	    P4 = _00_Pn1_OUTPUT_0;
//	    PM0 = _00_PMn0_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT | _FC_PM0_DEFAULT;
//		PM4 = _01_PMn0_NOT_USE | _00_PMn1_MODE_OUTPUT | _FC_PM4_DEFAULT;
		Fg_ecu_port_set = 0;
	}
	else{}
	
	return;
}

static void port_in_count(void)
{
	u1l_c_port_off[u1l_port_jun] = 0x00;
	if ( u1l_last_port[u1l_port_jun] == 0x01 ){
		if(u1l_c_port_on[u1l_port_jun] < 0xff){
			u1l_c_port_on[u1l_port_jun]++;
		}
		else{
		}
			
		if( u1l_c_port_on[u1l_port_jun] >= ON_CHECK){

			switch(u1l_port_jun){
			case	0x00:	
				Fg_port_ecu_test1 = 1;
				u2l_ecu_test1_on_cnt++;
				break;
			case	0x01:	
				Fg_port_ecu_test2 = 1;
				u2l_ecu_test2_on_cnt++;
				break;
			default:
				u1l_port_jun = 0x00;
				break;
			}
		} else{
		}
	}
	else{
		u1l_last_port[u1l_port_jun] = 0x01;
	}
	return;
}

static void port_off_count(void)
{
	if(u1l_last_port[u1l_port_jun] == 0x00 ){
		u1l_c_port_on[u1l_port_jun] = 0x00;
		u1l_c_port_off[u1l_port_jun]++;
		if( u1l_c_port_off[u1l_port_jun] >= OFF_CHECK ){
			u1l_c_port_off[u1l_port_jun] = 0x00;
			switch(u1l_port_jun){
			case	0x00:		
				Fg_port_ecu_test1 = 0;
				u2l_ecu_test1_on_cnt = 0;
				break;
			case	0x01:	
				Fg_port_ecu_test2 = 0;
				u2l_ecu_test2_on_cnt = 0;
				break;
			default:
				break;
			}
		} else{
		}
	} else{
		u1l_last_port[u1l_port_jun] = 0x00;
	}
	return;
}

static void port_input_check(void)
{
	u1 u1a_port[ECU_PORT_NUM] = {0};			

	u1a_port[0x00] = P_ECU_TEST1;			
	u1a_port[0x01] = P_ECU_TEST2;			
	
	for( u1l_port_jun = 0; u1l_port_jun < ECU_PORT_NUM; u1l_port_jun++ ){
		if( u1a_port[u1l_port_jun] == 0x00 ){
			port_in_count();
		}
		else{
			port_off_count();
		}
	}
	return;
}

static void ecu_test_check(void)
{
	if( (U2L_TIME_TEST_OK_MIN <= u2l_ecu_test2_on_cnt) && (u2l_ecu_test2_on_cnt <= U2L_TIME_TEST_OK_MAX))
	{
		if( (Fg_port_ecu_test1 == 1) && (Fg_pre_port_ecu_test1 == 0) )
		{
			cansel_torque_tester_mode();
			ecu_test_state = ECU_TST_BREAK_TEST;
			R_TAU0_Channel6_Start();
		}
		else{}
	}
	else{}
	
	if( (U2L_TIME_TEST_OK_MIN <= u2l_ecu_test1_on_cnt) && (u2l_ecu_test1_on_cnt <= U2L_TIME_TEST_OK_MAX))
	{
		if( (Fg_port_ecu_test2 == 1) && (Fg_pre_port_ecu_test2 == 0) )
		{
			ecu_test_state = ECU_SOLENOID_TEST;
		}
		else{}
	}
	else{}

	if( (Fg_port_ecu_test1 == 0) || (Fg_port_ecu_test2 == 0) )
	{
		switch(ecu_test_state){
		case ECU_TST_BREAK_TEST:	
			ecu_test_state = ECU_TST_BREAK_STOP;
			break;
		case ECU_SOLENOID_TEST:		
			ecu_test_state = ECU_SOLENOID_STOP;
			break;
		default:
			break;
		}
	}
	else{}

	return;
}

ecu_test_id get_ecu_test_state(void)
{
	return ecu_test_state;
}
