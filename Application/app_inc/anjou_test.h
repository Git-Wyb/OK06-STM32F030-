/*************************************************************/
/*  安城工程テストの定義 */
/*************************************************************/
#ifndef	__ANJOU_TEST_H__
#define	__ANJOU_TEST_H__


/*--------------------------------------------------------------------------*/
/*		関数宣言										   				    */
/*--------------------------------------------------------------------------*/
extern void anjou_test_signal(void);
extern void anjou_test_initial(u1 u1a_flash_finish);
extern u1 check_torque_test_exec(void);
extern void cansel_torque_tester_mode(void);
extern u1 check_denki_test_exec(void);
/* extern void check_hide_ope_key(void); */


/*--------------------------------------------------------------------------*/
/*		定数定義															*/
/*--------------------------------------------------------------------------*/
#define FACT_INIT_TORQUE_MODE			(u1)0			/* トルクテスターモード開始可能状態(工程検査実施前) */
#define FACT_DENKI_MODE					(u1)1			/* 電気テスターモード開始状態 */
#define FACT_TORQUE_MODE				(u1)2			/* トルクテスターモード開始可能状態(工程検査実施後) */

#define U1G_FACT_TRQ_STOP				(u1)0			/* トルクテスターモード未実施 */
#define U1G_FACT_TRQ_START_ACCEPT		(u1)1			/* トルクテスターモード開始受付中 */
#define U1G_FACT_TRQ_EXEC				(u1)2			/* トルクテスターモード実施中 */

#define U1G_FACT_DENKI_STOP				(u1)0			/* 電気テスターモード未実施 */
#define U1G_FACT_DENKI_EXEC				(u1)1			/* 電気テスターモード実施中 */

#define U1L_TRQ_AJST_CHECKING			(u1)0			/* トルク調整判定中 */
#define U1L_TRQ_AJST_OK					(u1)1			/* トルク調整OK判定 */
#define U1L_TRQ_AJST_UP					(u1)2			/* トルク調整UP判定 */
#define U1L_TRQ_AJST_DOWN				(u1)3			/* トルク調整DOWN判定 */
#define U1L_TRQ_AJST_NG					(u1)4			/* トルク調整NG判定 */

/* 無線モジュールへのブザー指令 */
#define U1G_ORDER_NO_BUZZER				(u1)0			/* ブザー指令無し */
#define U1G_ORDER_BUZZER				(u1)1			/* ブザー鳴り指令 */

#define	TIME_TESTER_SHORT_MS			500				/* トルクテスターモード中の短絡ブレーキON時間 */

#define U2L_RPM_MIN_PULSE_INPUT			(u2)146			/* 1rpm(4.5-3.5RPM)でのパルス入力判定値 */
#define U2L_RPM_MAX_PULSE_INPUT			(u2)1169		/* 8rpm(4.5+3.5RPM)でのパルス入力判定値 */


/*--------------------------------------------------------------------------*/
/*		ローカル型定義														*/
/*--------------------------------------------------------------------------*/
typedef enum {
	TRQ_TEST_POWER_ON,				/* 電源ON後の電源電圧安定待ち開始 */
	TRQ_TEST_100V_WAIT,				/* 電源電圧100V安定待ち */
	TRQ_TEST_VER_DOWN_WAIT,			/* 電源電圧降圧待ち */
	TRQ_TEST_PULSE_IN_WAIT,			/* トルクテスターモード移行判定(パルス入力待ち) */
	TRQ_TEST_VER_UP_WAIT,			/* トルクテスターモード移行判定(昇圧待ち)*/
	TRQ_TEST_START_FAIL,			/* トルクテスターモード開始失敗*/
	TRQ_TEST_START,					/* トルクテスターモード開始 */
	TRQ_TEST_MODULE_CONNECT,		/* モジュールと開閉機の接続確認待ち */
	TRQ_TEST_OPEN_KAHUKA_WAIT,		/* 開動作 過負荷検知待ち */
	TRQ_TEST_OPEN_TRQ_ADJUST,		/* 最大トルク調整判定(開側) */
	TRQ_TEST_CLOSE_KAHUKA_WAIT,		/* 閉動作 過負荷検知待ち */
	TRQ_TEST_CLOSE_TRQ_ADJUST,		/* 最大トルク調整判定(閉側) */
	TRQ_TEST_REV_TRQ_WAIT			/* 逆転トルク確認待ち */
} trq_test_step;	/* トルクテスターモード状態 */

typedef enum {
	DENKI_TEST_START,				/* 電気テスターモード開始 */
	DENKI_TEST_100V_WAIT,			/* 電源ON後の電源電圧安定待ち */
	DENKI_TEST_POWER_CHECK_WAIT,	/* 待機電力確認待ち */
	DENKI_TEST_OPEN_VIB_CHECK,		/* 開動作(振動確認)終了待ち */
	DENKI_TEST_OPEN_STOP_WAIT,		/* 開動作後、停止終了待ち */
	DENKI_TEST_CLOSE_VIB_CHECK,		/* 閉動作(振動確認)終了待ち */
	DENKI_TEST_CLOSE_STOP_WAIT,		/* 閉動作後、停止終了待ち */
	DENKI_TEST_ENCODER_CHECK,		/* 開動作(エンコーダ確認)終了待ち */
	DENKI_TEST_LEARN_STOP,			/* 開動作後、ROM未学習確認前停止待ち */
	DENKI_TEST_LEARN_CHECK,			/* ROM未学習確認 */
	DENKI_TEST_SIGNAL_WAIT,			/* 信号受信待ち */
	DENKI_TEST_SIGNAL_ANS_WAIT		/* 開動作(信号受信応答)終了待ち */
} denki_test_step;	/* 電気テスターモード状態 */

typedef enum {
	TEST_DOUKI_START_CHECK,			/* 同期処理開始確認 */
	TEST_DOUKI_COMP_WAIT			/* 同期処理完了待ち */
} test_douki_step;	/* テスター側との同期待ち状態 */

typedef enum {
	TRQ_ADJUST_VER_DOWN_CHECK,		/* 降圧確認 */
	TRQ_ADJUST_RESULT_CHECK			/* トルク調整結果確認 */
} trq_adjust_step;	/* テスター側との同期待ち状態 */

#if 0	/* 社内用SW操作判定処理コメントアウト */
typedef enum {
	KOUTEI_CHECK_SW_IN_WAIT,		/* SW入力待ち */
	KOUTEI_CHECK_SW_OFF_WAIT		/* SW入力OFF待ち */
} koutei_write_step;	/* 工程モード許可/ロックSW操作確認状態 */

typedef enum {
	VER_CHECK_STOP_IN_WAIT,			/* 停SW一定回数入力待ち */
	VER_CHECK_VER_OUTPUT			/* ソフトバージョン応答 */
} ver_check_step;	/* ソフトバージョン確認状態 */
#endif	/* 社内用SW操作判定処理コメントアウト */

typedef enum {
	TEST_MODE_STOP_IN_WAIT,			/* 停SW一定回数入力待ち */
	TEST_MODE_CHANGE				/* テスターモード変更 */
} test_mode_step;	/* テスターモード変更操作確認状態 */


#endif	/* __ANJOU_TEST_H__ */

