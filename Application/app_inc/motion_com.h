/***********************************************
* motion_command.h
************************************************/


#ifndef _MOTION_COMMAND_H
#define _MOTIOM_COMMAND_H

#include "typedefine.h"

#define	TIME_MOTION_END 10  /* msec */

/***** ����̎��ԂŎg�p����֐� *****/
u1 wait_motion_check(void);
void wait_motion_start(void);

/***** �J����Ŏg�p����֐� *****/
u1 motion_open_startup(void);
u1 motion_soft_open(void);
u1 motion_open(void);
/* �|�[�g�̐ݒ� */
void open_startup_port_set(void);
void soft_open_port_set(void);
void open_port_set(void);

/****** ����Ŏg�p����֐� ******/
u1 motion_close_startup(void);
u1 motion_soft_close(void);
u1 motion_close(void);
/* �|�[�g�̐ݒ� */
void close_startup_port_set(void);
void soft_close_port_set(void);
void close_port_set(void);

/***** �Z���u���[�L�Ŏg�p����֐� *****/
u2 motion_break(void);
/* �|�[�g�̐ݒ� */
void break_port_set(void);
void open_end_port_set(void);
void close_end_port_set(void);

/***** ��~�Ŏg�p����֐� *******/
u1 motion_stop(void);
/* �|�[�g�̐ݒ� */
void stop_port_set(void);

/***** ���؊J�Ŏg�p����֐� *******/
void osikiri_open_startup_port_set(void);
void soft_osikiri_open_port_set(void);
void osikiri_open_port_set(void);

/***** ���ؕŎg�p����֐� *******/
void osikiri_close_startup_port_set(void);
void soft_osikiri_close_port_set(void);
void osikiri_close_port_set(void);

extern u1 u1g_fg_soft_start_f; /* �\�t�g�X�^�[�g���t���O */
extern u1 u1g_fg_cw;
extern u1 u1g_fg_ccw;
extern u1 u1g_fg_pwm_break_out;
extern u1 u1g_fg_pump_out;
extern u1 u1g_step_motion; /* �֐����ŏ�����ω������� */


extern u1 u1g_fg_finish_soft_start; /* �\�t�g�X�^�[�g�I���t���O */

#endif