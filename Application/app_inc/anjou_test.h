/*************************************************************/
/*  ����H���e�X�g�̒�` */
/*************************************************************/
#ifndef	__ANJOU_TEST_H__
#define	__ANJOU_TEST_H__


/*--------------------------------------------------------------------------*/
/*		�֐��錾										   				    */
/*--------------------------------------------------------------------------*/
extern void anjou_test_signal(void);
extern void anjou_test_initial(u1 u1a_flash_finish);
extern u1 check_torque_test_exec(void);
extern void cansel_torque_tester_mode(void);
extern u1 check_denki_test_exec(void);
/* extern void check_hide_ope_key(void); */


/*--------------------------------------------------------------------------*/
/*		�萔��`															*/
/*--------------------------------------------------------------------------*/
#define FACT_INIT_TORQUE_MODE			(u1)0			/* �g���N�e�X�^�[���[�h�J�n�\���(�H���������{�O) */
#define FACT_DENKI_MODE					(u1)1			/* �d�C�e�X�^�[���[�h�J�n��� */
#define FACT_TORQUE_MODE				(u1)2			/* �g���N�e�X�^�[���[�h�J�n�\���(�H���������{��) */

#define U1G_FACT_TRQ_STOP				(u1)0			/* �g���N�e�X�^�[���[�h�����{ */
#define U1G_FACT_TRQ_START_ACCEPT		(u1)1			/* �g���N�e�X�^�[���[�h�J�n��t�� */
#define U1G_FACT_TRQ_EXEC				(u1)2			/* �g���N�e�X�^�[���[�h���{�� */

#define U1G_FACT_DENKI_STOP				(u1)0			/* �d�C�e�X�^�[���[�h�����{ */
#define U1G_FACT_DENKI_EXEC				(u1)1			/* �d�C�e�X�^�[���[�h���{�� */

#define U1L_TRQ_AJST_CHECKING			(u1)0			/* �g���N�������蒆 */
#define U1L_TRQ_AJST_OK					(u1)1			/* �g���N����OK���� */
#define U1L_TRQ_AJST_UP					(u1)2			/* �g���N����UP���� */
#define U1L_TRQ_AJST_DOWN				(u1)3			/* �g���N����DOWN���� */
#define U1L_TRQ_AJST_NG					(u1)4			/* �g���N����NG���� */

/* �������W���[���ւ̃u�U�[�w�� */
#define U1G_ORDER_NO_BUZZER				(u1)0			/* �u�U�[�w�ߖ��� */
#define U1G_ORDER_BUZZER				(u1)1			/* �u�U�[��w�� */

#define	TIME_TESTER_SHORT_MS			500				/* �g���N�e�X�^�[���[�h���̒Z���u���[�LON���� */

#define U2L_RPM_MIN_PULSE_INPUT			(u2)146			/* 1rpm(4.5-3.5RPM)�ł̃p���X���͔���l */
#define U2L_RPM_MAX_PULSE_INPUT			(u2)1169		/* 8rpm(4.5+3.5RPM)�ł̃p���X���͔���l */


/*--------------------------------------------------------------------------*/
/*		���[�J���^��`														*/
/*--------------------------------------------------------------------------*/
typedef enum {
	TRQ_TEST_POWER_ON,				/* �d��ON��̓d���d������҂��J�n */
	TRQ_TEST_100V_WAIT,				/* �d���d��100V����҂� */
	TRQ_TEST_VER_DOWN_WAIT,			/* �d���d���~���҂� */
	TRQ_TEST_PULSE_IN_WAIT,			/* �g���N�e�X�^�[���[�h�ڍs����(�p���X���͑҂�) */
	TRQ_TEST_VER_UP_WAIT,			/* �g���N�e�X�^�[���[�h�ڍs����(�����҂�)*/
	TRQ_TEST_START_FAIL,			/* �g���N�e�X�^�[���[�h�J�n���s*/
	TRQ_TEST_START,					/* �g���N�e�X�^�[���[�h�J�n */
	TRQ_TEST_MODULE_CONNECT,		/* ���W���[���ƊJ�@�̐ڑ��m�F�҂� */
	TRQ_TEST_OPEN_KAHUKA_WAIT,		/* �J���� �ߕ��׌��m�҂� */
	TRQ_TEST_OPEN_TRQ_ADJUST,		/* �ő�g���N��������(�J��) */
	TRQ_TEST_CLOSE_KAHUKA_WAIT,		/* ���� �ߕ��׌��m�҂� */
	TRQ_TEST_CLOSE_TRQ_ADJUST,		/* �ő�g���N��������(��) */
	TRQ_TEST_REV_TRQ_WAIT			/* �t�]�g���N�m�F�҂� */
} trq_test_step;	/* �g���N�e�X�^�[���[�h��� */

typedef enum {
	DENKI_TEST_START,				/* �d�C�e�X�^�[���[�h�J�n */
	DENKI_TEST_100V_WAIT,			/* �d��ON��̓d���d������҂� */
	DENKI_TEST_POWER_CHECK_WAIT,	/* �ҋ@�d�͊m�F�҂� */
	DENKI_TEST_OPEN_VIB_CHECK,		/* �J����(�U���m�F)�I���҂� */
	DENKI_TEST_OPEN_STOP_WAIT,		/* �J�����A��~�I���҂� */
	DENKI_TEST_CLOSE_VIB_CHECK,		/* ����(�U���m�F)�I���҂� */
	DENKI_TEST_CLOSE_STOP_WAIT,		/* �����A��~�I���҂� */
	DENKI_TEST_ENCODER_CHECK,		/* �J����(�G���R�[�_�m�F)�I���҂� */
	DENKI_TEST_LEARN_STOP,			/* �J�����AROM���w�K�m�F�O��~�҂� */
	DENKI_TEST_LEARN_CHECK,			/* ROM���w�K�m�F */
	DENKI_TEST_SIGNAL_WAIT,			/* �M����M�҂� */
	DENKI_TEST_SIGNAL_ANS_WAIT		/* �J����(�M����M����)�I���҂� */
} denki_test_step;	/* �d�C�e�X�^�[���[�h��� */

typedef enum {
	TEST_DOUKI_START_CHECK,			/* ���������J�n�m�F */
	TEST_DOUKI_COMP_WAIT			/* �������������҂� */
} test_douki_step;	/* �e�X�^�[���Ƃ̓����҂���� */

typedef enum {
	TRQ_ADJUST_VER_DOWN_CHECK,		/* �~���m�F */
	TRQ_ADJUST_RESULT_CHECK			/* �g���N�������ʊm�F */
} trq_adjust_step;	/* �e�X�^�[���Ƃ̓����҂���� */

#if 0	/* �Г��pSW���씻�菈���R�����g�A�E�g */
typedef enum {
	KOUTEI_CHECK_SW_IN_WAIT,		/* SW���͑҂� */
	KOUTEI_CHECK_SW_OFF_WAIT		/* SW����OFF�҂� */
} koutei_write_step;	/* �H�����[�h����/���b�NSW����m�F��� */

typedef enum {
	VER_CHECK_STOP_IN_WAIT,			/* ��SW���񐔓��͑҂� */
	VER_CHECK_VER_OUTPUT			/* �\�t�g�o�[�W�������� */
} ver_check_step;	/* �\�t�g�o�[�W�����m�F��� */
#endif	/* �Г��pSW���씻�菈���R�����g�A�E�g */

typedef enum {
	TEST_MODE_STOP_IN_WAIT,			/* ��SW���񐔓��͑҂� */
	TEST_MODE_CHANGE				/* �e�X�^�[���[�h�ύX */
} test_mode_step;	/* �e�X�^�[���[�h�ύX����m�F��� */


#endif	/* __ANJOU_TEST_H__ */

