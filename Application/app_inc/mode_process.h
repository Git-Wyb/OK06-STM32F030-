
#ifndef _MODE_PROCESS_H_
#define _MODE_PROCESS_H_



#define TIME_PRE_BREAK 100/* 100msec */
#define TIME_BREAK_STOP 2


#define TOTAL_TIMER 90

#define TIME_PRE_MOTION 200

#define TIME_SOFT_MOTION_MS 800
#define TIME_SOFT_MOTION_SEC 0

#define	SF_STOP			0
#define	SF_OPEN			1
#define	SF_CLOSE		2
#define	SF_SAIKOU_OP	3
#define	SF_SAIKOU_CL	4
#define	SF_PRE_OPEN		5
#define	SF_PRE_CLOSE	6
#define	SF_PRE_SAI_OP	7
#define	SF_PRE_SAI_CL	8
#define	SF_SOFT_OPEN	9
#define	SF_SOFT_CLOSE	10
#define	SF_SOFT_SAI_OP	11
#define	SF_SOFT_SAI_CL	12
#define	SF_BREAK		13




extern u1 u1g_step;
extern u1 u1g_shutter_state;

extern void mode_stop(void);
extern void mode_close(void);
extern void mode_open(void);
extern void mode_osikiri_open(void);
extern void mode_osikiri_close(void);
extern void calcu_std_huka(void);

extern u1 select_step_stop(void);
extern u1 select_step_open(void);
extern u1 select_step_close(void);
extern u1 select_step_osikiri_open(void);
extern u1 select_step_osikiri_close(void);

#endif