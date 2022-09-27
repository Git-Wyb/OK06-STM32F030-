/*************************************************************/
/*  flash_data_read ���� */
/*  ����M�̏��� */
/*************************************************************/

#ifndef __FLASH_DATA_READ__
#define __FLASH_DATA_READ__

/**************************************************************************************************/
/* �萔��` */
/*==========================================================*/
/** �v���g�R���ɂ��킹���萔 ****/
#define	DATA_LENGTH_HEAD_SIZE	13	/* ACK_NACK�̑��M�f�[�^�� */
#define	DATA_LENGTH_ACK_NACK_SIZE	11	/* ACK_NACK�̑��M�f�[�^�� */

/**************************************************************************************************/
/* �֐� */
/*==========================================================*/
void check_ijou_rireki_read(void);


/****�@�X�^�[�g�e�L�X�g�@0x0f5A �Œ�l �@1byte , 2byte ��
*/
/**************************************************************************************************/
/* �ϐ���` */
/*==========================================================*/
extern u1 u1g_save_all_data;
extern u1 u1g_Fg_ijou_read_enable;
extern u1 u1g_all_read_counter;

void make_send_ijou_data(u1);
void phase_sw_signal_send(void);
void phase_device_search(void);
void phase_ijou_data_send_main(void);
void make_device_search_data(void);
void stop_ijou_read(void);
void check_ijou_end_data(u1);
void check_yomidashi_out(void);
void make_send_Ack_Nack_data(void);


extern u1 u1g_send_Ack_Nack_data[11];
extern u1 u1g_send_ijou_data[61];	/* 48+13 */
extern u1 u1g_sf_ijou_read_phase;
extern u1 u1g_Fg_ijou_rireki_PC_send_enable;
extern u1 u1g_Fg_fuka_ijou_hsize;
extern u1 fg_next_data_can_send;


#endif

