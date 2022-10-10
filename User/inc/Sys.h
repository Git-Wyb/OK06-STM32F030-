#ifndef __SYS_H__
#define __SYS_H__

#include "stm32f0xx.h"

typedef signed char s1;
typedef unsigned char u1;
typedef signed short int s2;
typedef unsigned short int u2;
typedef signed int s4;
typedef unsigned int u4;
typedef float f4;

/*=======  T1  FIELD =======*/
typedef union {
	u1 	byte;
/* 	T1_FIELD 	bit; */
	struct {
	u1 b4:1;
	u1 b3:1;
	u1 b2:2;
	u1 b1:2;
	u1 b0:2;
	} T1_FIELD;
} TYPE_T1;

/*=======  T2  FIELD =======*/
typedef union {
	u1 	byte;
	struct {
	u1 b4:2;
	u1 b3:1;
	u1 b2:3;
	u1 b1:1;
	u1 b0:1;
	} T2_FIELD;
} TYPE_T2;

/*=======  T34 FIELD =======*/
typedef union {
	u1 	byte;
	struct {
	u1 b3:1;
	u1 b2:3;
	u1 b1:1;
	u1 b0:3;
	} T_FIELD;
} TYPE_T34;

/*=======  AD FIELD =======*/
typedef union {
	u1 	byte;
	struct {
	u1 b3:1;
	u1 b2:2;
	u1 b1:1;
	u1 b0:4;
	} AD_FIELD;
} TYPE_AD;

/*=======  AD2 FIELD =======*/
typedef union {
	u1 	byte;
	struct {
	u1 b4:2;
	u1 b3:1;
	u1 b2:1;
	u1 b1:3;
	u1 b0:1;
	} AD2_FIELD;
} TYPE_AD2;

/*=======  BYTE IO ========*/
typedef union {
	u1 	byte;
	struct {
	u1 b7:1;
	u1 b6:1;
	u1 b5:1;
	u1 b4:1;
	u1 b3:1;
	u1 b2:1;
	u1 b1:1;
	u1 b0:1;
	}	BYTE_FIELD;
} TYPE_BYTE;

/*======= WORD IO ========*/
typedef union {
	u2	word;
	u1	byte[2];
	struct {
	u2 b15:1;
	u2 b14:1;
	u2 b13:1;
	u2 b12:1;
	u2 b11:1;
	u2 b10:1;
	u2 b9:1;
	u2 b8:1;
	u2 b7:1;
	u2 b6:1;
	u2 b5:1;
	u2 b4:1;
	u2 b3:1;
	u2 b2:1;
	u2 b1:1;
	u2 b0:1;
	} WORD_FIELD;
} TYPE_WORD;

/*=======  AD FIELD =======*/
typedef union {
	u1 	byte;
	struct {
	u1 b3:2;
	u1 b2:2;
	u1 b1:2;
	u1 b0:2;
	} BIT2_FIELD;
} TYPE_BIT2;

/*=======  NIBLE FIELD =======*/
typedef union {
	u1 	byte;
	struct {
	u1 b1:4;
	u1 b0:4;
	} NIBLE_FIELD;
} TYPE_NIBLE;

/*=======  LONG FIELD =======*/
typedef union {
	u2	word;
	u1	byte[2];
	struct {
	u2 b3:4;
	u2 b2:4;
	u2 b1:6;
	u2 b0:2;
	} WORD4_FIELD;
} TYPE_LONG;


typedef struct {								/*  異常履歴データ構成1 */
	u1 u1_kind_of_error;							/*  異常の種類 */
	u1 u1_previous_mode;							/*  前回の動作モード */
	u1 u1_signal;									/*  異常発生時のシグナル */
	u1 u1_free;										/*  異常毎のデータ */
	u2 u2_number_of_times;							/*  異常発生動作回数 */
}	TYPE_ERROR_1;

typedef struct {
	u1 u1_close_huka[16];							/*  閉方向負荷学習値 */
	u1 u1_open_huka[2];							/*  開方向:最大、上端 */
	u1 u1_jogen_sansyo;							/*  上限参照値 */
	u1 u1_huka_check_sum;							/*  チェックサム */
}	TYPE_FLASH_LEARN_BODY;

typedef struct {								/*  異常履歴データ */
	u2 u2_number_openclose;							/*  開閉回数 */
	u2 u2_number_move;							/*  動作回数 */

	u2 u2_number_sw_open;							/*  開SW押し回数 */
	u2 u2_number_sw_close;							/*  閉SW押し回数 */

	TYPE_ERROR_1 _xn_error_set0;						/*  今回 */
	TYPE_ERROR_1 _xn_error_set1;						/*  1回前 */

}	TYPE_FLASH_ERROR_BODY_1;

typedef struct {
	u1 no_err;			/* 異常の種類 */
	u1 free_area;			/* free */
	u2 num_move;			/* 動作回数 */
}	TYPE_ERROR_2;			/* 異常履歴データ構成2 */

typedef struct {
	TYPE_ERROR_2 err_now;		/* 直前に発生した異常 */
	TYPE_ERROR_2 err_prev_1;	/* 1回前に発生した異常 */
	TYPE_ERROR_2 err_prev_2;	/* 2回前に発生した異常 */
	TYPE_ERROR_2 err_prev_3;	/* 3回前に発生した異常 */
	TYPE_ERROR_2 err_prev_4;	/* 4回前に発生した異常 */
	TYPE_ERROR_2 err_prev_5;	/* 5回前に発生した異常 */
	TYPE_ERROR_2 err_prev_6;	/* 6回前に発生した異常 */
	TYPE_ERROR_2 err_prev_7;	/* 7回前に発生した異常 */
	TYPE_ERROR_2 err_prev_8;	/* 8回前に発生した異常 */
	TYPE_ERROR_2 err_prev_9;	/* 9回前に発生した異常 */
	TYPE_ERROR_2 err_prev_10;	/* 10回前に発生した異常 */
	TYPE_ERROR_2 err_prev_11;	/* 11回前に発生した異常 */
	TYPE_ERROR_2 err_prev_12;	/* 12回前に発生した異常 */
	TYPE_ERROR_2 err_prev_13;	/* 13回前に発生した異常 */
	TYPE_ERROR_2 err_prev_14;	/* 14回前に発生した異常 */
	TYPE_ERROR_2 err_prev_15;	/* 15回前に発生した異常 */
	TYPE_ERROR_2 err_prev_16;	/* 16回前に発生した異常 */
	TYPE_ERROR_2 err_prev_17;	/* 17回前に発生した異常 */
	TYPE_ERROR_2 err_prev_18;	/* 18回前に発生した異常 */
	TYPE_ERROR_2 err_prev_19;	/* 19回前に発生した異常 */
} TYPE_FLASH_ERROR_BODY_2;	/* 異常履歴2 */

typedef struct {									/*  Hサイズフラッシュデータ */
	u2 u2_size_data;								/*  Hサイズ */
	u2 u2_max_open_pulse;								/*  学習最大値位置 */
	u1 u1_ryoiki;									/*  領域数 */
	u1 u1_check_sum;								/*  チェックサム */

}	TYPE_FLASH_HSIZE_BODY;

typedef struct {
	u1 u1_finish;		/* 工程完了 */
	u1 u1_max_torque;	/* 最大トルク設定値 */
	u2 u2_soft_ver;		/* ソフトバージョン */
} TYPE_FLASH_FACT_BODY;		/* 検査履歴 */

typedef struct {
	u1 u1_uart_err_mode;	/* UART通信用 異常内容 */
	u1 u1_f_err_clear_wait;	/* 異常解除待ちフラグ */
} TYPE_REQ_UART_ERR;		/* 通信用異常継続状態 */

/* U1_DATA_LEARN_NUM,U1_DATA_ERROR_NUM,U1_DATA_HSIZE_NUM を変更する場合は
　 p_flash_config.h #define U2G_FARG_USER_DATA　のデータサイズを変更する！    */

#define U1_DATA_LEARN_NUM		(u1)(20)
#define U1_DATA_ERROR_NUM		(u1)(20)
#define U1_DATA_ERROR_20_NUM		(u1)(80)
#define U1_DATA_HSIZE_NUM		(u1)(6)
#define U1_DATA_FACT_NUM		(u1)(4)

typedef union {					/*  負荷学習フラッシュデータ */

	u1 byte[U1_DATA_LEARN_NUM];				/*  byteアクセス用 */
	TYPE_FLASH_LEARN_BODY xn_learned_huka_data;

}	TYPE_FLASH_LEARN_UNIT;

typedef union {								/*  異常履歴フラッシュデータ */

	u1 byte[U1_DATA_ERROR_NUM];					/*  byteアクセス用 */
	TYPE_FLASH_ERROR_BODY_1 xn_error_data;

}	TYPE_FLASH_ERROR_UNIT;

typedef union {								/*  異常履歴フラッシュデータ */

	u1 byte[U1_DATA_ERROR_20_NUM];					/*  byteアクセス用 */
	TYPE_FLASH_ERROR_BODY_2 xn_error_20_data;

}	TYPE_FLASH_ERROR_2_UNIT;


typedef union {							/*  Hサイズフラッシュデータ */

	u1 byte[U1_DATA_HSIZE_NUM];					/*  byteアクセス用 */
	TYPE_FLASH_HSIZE_BODY xn_Hsize_series;

}	TYPE_FLASH_HSIZE_UNIT;

typedef union {							/*  検査履歴フラッシュデータ */

	u1 byte[U1_DATA_FACT_NUM];					/*  byteアクセス用 */
	TYPE_FLASH_FACT_BODY xn_record_fact;

}	TYPE_FLASH_FACT_UNIT;

typedef union{
    u1 Flag;
    struct
    {
        u1 b0 : 1;
        u1 b1 : 1;
        u1 b2 : 1;
        u1 b3 : 1;
        u1 b4 : 1;
        u1 b5 : 1;
        u1 b6 : 1;
        u1 b7 : 1;
    };
}BaseFlagStruct;

extern BaseFlagStruct Un_Flag0;
#define flag_CaptureStart   Un_Flag0.b0
#define flag_key_scan       Un_Flag0.b1
#define flag_sw_sta         Un_Flag0.b2
#define flag_tim17_en       Un_Flag0.b3
#define flag_tim16_en       Un_Flag0.b4

void Init_IWDG(void);
void delay_ms(u2 nms);
void delay_us(u4 nus);
void Init_Delay(void);
void IWDG_Clear(void);
void R_WDT_Restart(void);
u1 Key_Scan(void);
void Key_Sw_Dete(void);

#endif

