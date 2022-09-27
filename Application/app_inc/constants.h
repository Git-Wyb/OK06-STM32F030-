#ifndef	__CONSTANTS_H__
#define	__CONSTANTS_H__

#include "comm_uart.h"

#define REV_SHORT_PULSE		18

#define	SF_STOP			0
#define	SF_OPEN			1
#define	SF_CLOSE		2
#define	SF_SAIKOU_OP		3
#define	SF_SAIKOU_CL		4
#define	SF_PRE_OPEN		5
#define	SF_PRE_CLOSE		6
#define	SF_PRE_SAI_OP		7
#define	SF_PRE_SAI_CL		8
#define	SF_SOFT_OPEN		9
#define	SF_SOFT_CLOSE		10
#define	SF_SOFT_SAI_OP		11
#define	SF_SOFT_SAI_CL		12
#define	SF_BREAK		13

//in motion_commands.c
#define	TIME_MOTION_END		10	//ms
#define	TIME_BREAK_STOP		2	//s
#define	TIME_ANJOU_BREAK_STOP	5	//s
#define	TOTAL_TIMER		90	//s
#define	TIME_PRE_BREAK		100	//ms
#define	TIME_SOFT_MOTION_SEC	0	//s
#define	TIME_SOFT_MOTION_MS	800	//ms
#define	TIME_PRE_MOTION		200	//ms

//	in system_timer
#define	TIME_2sec		TIME_BREAK_STOP	//5
#define	TIME_3sec		0x03	//4.05
#define	TIME_5sec		0x05	//5
#define	TIME_10sec		0x0a	//4.05
#define	TIME_90sec		TOTAL_TIMER	//90

#define	TIME_200msec_ms		550
#define	TIME_200msec_sec	0

#define	PULSE_100mm		200	
				
#define	PULSE_CLEAR_RESET_FLAG	30

//	for overload.c (bad_data_del())
#define	NOISE_FILTER_ADD	8
#define	NOISE_FILTER_MIN	3
#define	NOISE_SET_MIN		2

#define	DELAY_KAGEN_SW	25
							
#define	MARGIN_KAGEN_SW	4
						
#define	PULSE_BISHOU_KAKOU		25	
#define	LIMIT_SW_ON	0
#define	LIMIT_SW_OFF	1

#define	ON_CHECK  			0x04					
#define	OFF_CHECK 			0x03				
#define	WAIT_SAIKOU			0x03					
	
												

#define	CURR				9						
#define	VER				10						
#define	TEMP				11						

#define	TEMP_MAX_HOSEI	40					
#define	VER_MAX_HOSEI	20				

#define	D_PWM_MAX_NORMAL		0x2A84	//99.6%
#define	D_PWM_MAX_SOFT_LOCK		0x2A84	//99.6%
#define D_PWM_DUTY_100			108	//0x555F (100%)
#define	D_PWM_MIN			0	
#define MAX_CHANGE			130
#define MIN_CHANGE			((s2)(-130))	
#define CLOSE_MAX_CHANGE		28
#define CLOSE_MIN_CHANGE		((s2)(-28))

#define	KP				((s4)96)//96//96		
#define	KI				((s4)25)//25//25//24		

#define UNIT1_UNIT2_DATA_PLS_25		25
#define UNIT1_UNIT2_DATA_MINUS_100	((s4)(-100))
#define UNIT1_UNIT2_DATA_MINUS_1000	((s4)(-1000))

#define	PULSE_LENGTH_1388RPM		1388
#define PULSE_LENGTH_1110RPM		1110
#define PULSE_LENGTH_1169RPM		1169		
#define PULSE_LENGTH_1666RPM		1666

#define	STAND_PLUS_LENGTH		PULSE_LENGTH_1169RPM		
#define	MAINT_PLUS_LENGTH		0x3f1f				//(DIPSW) 1392.4rpm
#define	TOO_S_PLS_LEN			0x0015				/* 800rpm*/
#define	L_PLUS				300				/*0.025% 20*/



#define	length_break		0x4374					/*35rpm*/
#define	cnst_break_on		0x1e					
#define	b_d_updowm		0x4194					/*36rpm*/
#define	off_break		0x48a5					/*l 32.5rpm*/
#define	cnst_break_off		0x03				
#define	off_pwm			0x456f					/*pwm33rpm*/
#define	cnst_off_pwm		0x14					/*pwm*/
#define	b_cycle			0x03					/*20ms*/
/*
	ÌÞÚ°·—Í(-1.5Nm)‚É‚Ä40rpm‚­‚ç‚¢
*/

#define	TOO_L_PLS_LEN		0x1bc					/*444ms*/
#define	U2L_JOUGEN_KITEI_AREA		155				
#define MAX_TRQ_H_HABA  	155					
#define MINUS_HABA		(-30)					
#define NORMAL_HABA		50					
#define S2L_P_THRESHOLD_50MM	((s2)117)			
#define S2L_THRESHOLD_TEIDEN_LOCKOUTPUT ((s2)25)		
#define S2L_THRESHOLD_LOCKOUTPUT	((s2)S2L_THRESHOLD_TEIDEN_LOCKOUTPUT + 12)	
#define S2G_LOCK_ALLOW_AREA			((s2)117)		

#define	no_posi_p		0x1d3				
#define ONE_SEC_P		390

#define	THERMAL_A		4				
#define	THERMAL_D_PWM		1361

#define FLASH_DATA_SIZE  (u1)(U1_DATA_LEARN_NUM + U1_DATA_HSIZE_NUM) 

#define	OPEN_DATA			16				
#define	ADD_OPEN_LEARN_FG		17				
#define	HUKA_UPPER			18				
#define SIZE_RAM			19				
#define	SECTION_DATA			20				
#define	MAX_OPEN_PULSE			21				
#define	TRQ_LEVEL_HIGH_SPEED		22			
#define FACT_FINISH			23				

#define	CHECK_SUM_HUKA		(u1)(U1_DATA_LEARN_NUM - 1)					
#define	CHECK_SUM_SIZE		(u1)(U1_DATA_HSIZE_NUM - 1)					


#define TIME_OVER 			4000

#define	MAX_SECTION			0x0f				

#define	max_learn		0x00				

#define U1G_STOP_MODE			(u1)0
#define U1G_OPEN_MODE			(u1)1
#define U1G_CLOSE_MODE			(u1)2
#define U1G_OSIKIRI_OPEN_MODE		(u1)3
#define U1G_OSIKIRI_CLOSE_MODE		(u1)4
#define U1G_LOCK_MODE			(u1)5



/* y = 0.1604x + 0.0017 */
#define	POWER_VER_1JI			1604			
#define	POWER_VER_CONST			17				


/* y = -0.2768x + 245.38 */
#define	TEMP_VERY_COLD_1JI		2768			
#define	TEMP_VERY_COLD_CONST	245				


/* y = -0.1281x + 112.34 */
#define	TEMP_NORMAL_1JI			1281			
#define	TEMP_NORMAL_CONST		112				

#define	S2G_STANDARD_TEMP		(s2)23			



//y = 0x^2 + 0.1862x + 3.6789
//  = 0x^2 + 3051/16384x + 3.6789

#define	MARGIN_CLOSE_2JI		0				
#define	MARGIN_CLOSE_1JI		19306//19139//3051//6101//3051	
#define	MARGIN_CLOSE_CONST		113170//111850//8//16//4		
#define TRQ_AD_0_3Nm			10					
#define TRQ_AD_OPEN_MAX_0_3Nm	10	//9‚É15%


//y = 0x^2 + 0.3034x + 8.5438
//  = 0x^2 + 4971/16384x + 8.5438

#define	MARGIN_OPEN_2JI		0					
#define	MARGIN_OPEN_1JI		15323//15252//1546//4971			
#define	MARGIN_OPEN_CONST	3475//5800//7746//18//36//9			
#define KETA_10000		10000
#define TRQ_AD_1_9Nm		92		/*OK04:1.9Nm*/
#define TRQ_AD_0_5Nm		25		
#define TRQ_AD_CLOSE_1_7Nm	80		
#define TRQ_AD_0_8Nm		36		
#define TRQ_AD_1_0Nm		44		
#define TRQ_AD_1_2Nm		53		
#define TRQ_AD_CLOSE_1_45Nm	66	
#define TRQ_REL_NM_NO_SIZE_RAM	37	
#define TRQ_REL_NM_SET_SIZE_RAM	62



#define	LEARN_CLOSE_MIN			18//14 RK02:14 -> OK04:18
#define	LEARN_OPEN_MIN			24//18 RK02:18 -> OK04:24
#define	KAMEN_LEARN_CLOSE_MIN		20


//1857rpm
// T(1000rpm) = 0.7502*T(1857rpm) - 1.7636
//0.7502 = 7502/10000 = 12291/16384
#define	MOTOR_AD_1857to1000_1JI		12291
#define	MOTOR_AD_1857to1000_CONST	1

#define	C_SHORT_CLOSE			18					
#define	c_short_wait_off		0x14				
#define	c_short_ly_end			0x14				
#define	HAND_ERROR			0xfd				
#define	CONST_MOVE			146					/*133=2000ms/15ms*/
#define	STOP_ERROR_PULSE	467				

#define	PRE_POSI			0x16DB	

#define	P_DIRECTION			0x01

#define	KAGEN_HANI			25		
#define	HIGHT_SPEED_P			1710				
#define	KARIKAGEN_MINUS			0	

#define	ABNORMAL_PLUS_LENGTH		2000		
										
#define	BOUSOU_PULSE_COUNT		200		
#define	BOUSOU_LONG_NOISE_PENA		5	



#define TIME_10sec_sw_input		10000
#define	TIME_8sec_sw_input		8000		/* 4.05 */
#define	TIME_5sec_sw_input		5000
#define	TIME_3sec_sw_input		3000
#define	TIME_2sec_sw_input		2000
#define	TIME_1sec_sw_input		1000
#define	TIME_500ms_sw_input		500
#define TIME_LED_OUTPUT_ms		250
#define PULSE_MAX_SIZE			5849		
#define HUKA_JOUGEN_BORDER_SIZE	2127		
#define	TIME_CHECK_SW_HUKA_RESET	30		
#define	TIME_CHECK_SW_STARTUP		50		


#define	PULSE_POSITION_TEIDEN_HUKKI_OPEN	(PULSE_BOUHAN_START + PULSE_BOUHAN_MARGIN)


#define	PULSE_UPPER_JOUGEN  (s2)(-30)


#define	PULSE_KAHUKA_CLOSE	200

#define CH_NUM 3 
#define BF_NUM 4 

#define JUST_SW_ALL 0xe0
#define P_OPEN_KEY	0x80
#define P_CLOSE_KEY	0x40
#define P_STOP_KEY	0x20
#define P_KEY_NO_IN	0x00

#define TH_S_START_ADD_1	20
#define TH_S_START_ADD_2	1
#define TH_N_SPEED_ADD_1	28
#define TH_N_SPEED_ADD_2	1


#define BOTH_OPEN_CLOSE		((u1)0x05)		//0000 0101

#define CNT_OPEN_CLOSE		((u1)0)		
#define CNT_MOVE		((u1)1)		
#define THRESHOLD_MAX		((u1)2)		
#define R_TO_FULL		((u1)3)	
#define NUM_ERROR_MODE		((u1)4)	
#define CNT_OCCUR_1		((u1)5)	

#define WAIT_TIME_MAIN		((u1)45)

#define NUM_ADOPT_DATA		(u1)4
#define NUM_CAPTURE_DATA	(u1)7
#define NUM_AD_CHECK_DATA	(u1)5
#define LIMIT_TIME_1BYTE	(u1)30
#define LIMIT_TIME_8BYTE	(u1)7

#define VALUE_LIMIT_FROM_0	10	
#define LIMIT_FROM_0		10	

#define S2_RANGE_ERR_LIMITSW	((s2)2)

#define U1_FLASHWRITE_TIMING	6	

#define CONST_READ_DATA_TIME  8  

#define YOMIDASHI_TIME_LIMIT  300	

#define U1_NON_VALUE				((u1)0xff)		


#define U1_NO_USE		((u1)0)				
#define U1_ALL_WRITE		((u1)1)				
#define U1_E_SIZE_WRITE		((u1)2)				
#define U1_E_H_WRITE		((u1)3)			
#define U1_SIZE_H_WRITE		((u1)4)				
#define U1_HUKA_WRITE		((u1)5)			
#define U1_ERROR_1_WRITE	((u1)6)			
#define U1_SIZE_HUKA_WRITE	((u1)7)			
#define U1_FACT_WRITE		((u1)8)				

typedef enum {
	ERR_NONE,					
	ERR_CLOSE_OVERLOAD,			
	ERR_SENS_ELEC,				
	ERR_POWER_ON,			
	ERR_HIGH_SPEED,			
	ERR_HAND_MOVE,			
	ERR_THERMAL,			
	ERR_SOFT_RESET,			
	ERR_POWER,				
	ERR_OPEN_OVERLOAD,		
	ERR_TIME_OVER,			
	ERR_ENCODER,			
	ERR_SOFT_ROCK_OUT,		
	ERR_H_SIZE_SET,		
	ERR_SOL_SHORT,	
	ERR_CLUTCH,			
	ERR_FET,		
	ERR_POWER_PORT,		
	ERR_TEMP_PORT		
} error_mode_no;


#define POWER_85V	530	/*522*/
#define POWER_115V	717	/*666*/


#define MAIN_10SEC	0x8ac			/* 4.05 */

#define U1L_VALUE_FFFF			((u1)0xffU)					
#define U2L_VALUE_FFFF			((u2)0xffffU)			
#define U4L_VALUE_FFFF			((u4)0xffffffffU)		

	
#endif	/* __CONSTANTS_H__ */
