/***********************************************
* motion_command.h
************************************************/


#ifndef _MOTION_COMMAND_H
#define _MOTIOM_COMMAND_H

#include "typedefine.h"

#define	TIME_MOTION_END 10  /* msec */

/***** 動作の時間で使用する関数 *****/
u1 wait_motion_check(void);
void wait_motion_start(void);

/***** 開動作で使用する関数 *****/
u1 motion_open_startup(void);
u1 motion_soft_open(void);
u1 motion_open(void);
/* ポートの設定 */
void open_startup_port_set(void);
void soft_open_port_set(void);
void open_port_set(void);

/****** 閉動作で使用する関数 ******/
u1 motion_close_startup(void);
u1 motion_soft_close(void);
u1 motion_close(void);
/* ポートの設定 */
void close_startup_port_set(void);
void soft_close_port_set(void);
void close_port_set(void);

/***** 短絡ブレーキで使用する関数 *****/
u2 motion_break(void);
/* ポートの設定 */
void break_port_set(void);
void open_end_port_set(void);
void close_end_port_set(void);

/***** 停止で使用する関数 *******/
u1 motion_stop(void);
/* ポートの設定 */
void stop_port_set(void);

/***** 押切開で使用する関数 *******/
void osikiri_open_startup_port_set(void);
void soft_osikiri_open_port_set(void);
void osikiri_open_port_set(void);

/***** 押切閉で使用する関数 *******/
void osikiri_close_startup_port_set(void);
void soft_osikiri_close_port_set(void);
void osikiri_close_port_set(void);

extern u1 u1g_fg_soft_start_f; /* ソフトスタート許可フラグ */
extern u1 u1g_fg_cw;
extern u1 u1g_fg_ccw;
extern u1 u1g_fg_pwm_break_out;
extern u1 u1g_fg_pump_out;
extern u1 u1g_step_motion; /* 関数内で処理を変化させる */


extern u1 u1g_fg_finish_soft_start; /* ソフトスタート終了フラグ */

#endif