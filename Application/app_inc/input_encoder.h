/*************************************************************/
/* encoder入力処理 */
/*************************************************************/
/***********************************************************************/
/*                                                                     */
/*  FILE        :input encoder.h                                       */
/*  DATE        :Fri, Apr 04, 2008                                     */
/*  DESCRIPTION :define the macro for initialization of sections.      */
/*  CPU GROUP   :35C                                                   */
/*                                                                     */
/*  This file is generated by Renesas Project Generator (Ver.4.12).    */
/*                                                                     */
/***********************************************************************/

/***********************************************************/
/*  COMPILER for R8C/Tiny                                  */
/*                                                         */
/*  Copyright(c) 2004 Renesas Technology Corp.             */
/*  And Renesas Solutions Corp.,All Rights Reserved.       */
/*                                                         */
/*  input encoder .h                                       */
/*                                                         */
/*  clear for bss section                                  */
/*  transfer initialized data to data section              */
/*                                                         */
/*  note: Do not modify                                    */
/*                                                         */
/* $Date: 2007/06/14 01:49:49 $                            */
/* $Revision: 1.9.4.2.8.2 $                                */
/***********************************************************/ 

#ifndef _INPUT_ENCODER_H
#define _INPUT_ENCODER_H

#include "Sys.h"


/* #define H_HABA					0xa3		上限確認値許容幅 100mm（巻き径120mm）*/
#define TOO_S_PULSE_LENGTH		20	    /*異常短ﾊﾟﾙｽ 800rpm ???*/
#define TOO_L_PULSE_LENGTH		0x1bc  /*0x00c8  0x01bc		異常ﾊﾟﾙｽ長さ 444ms*/
/* #define BOUSOU_LONG_NOISE_PENA  5    		暴走検知中、長いノイズを受信したときのマイナス値 */

#define	TIME_25MSEC		0x0019			/* 25msec */
#define	TIME_21MSEC		0x0015			/* 21msec */
#define TIME_20MSEC		0x0014			/* 20msec */
#define TIME_19MSEC 		0x0013			/* 19msec */
#define TIME_17MSEC 		0x0011			/* 17msec */
#define TIME_16MSEC 		0x0010			/* 16msec */
#define TIME_15MSEC 		0x000F			/* 15msec */
#define TIME_14MSEC		0x000E			/* 12msec */
#define TIME_12MSEC 	   	0x000c			/* 12msec */
#define TIME_10MSEC 		0x000A			/* 10msec */

#define BIT_SHIFT_2 		2			/* 2bitシフト用 */
#define PW_TO_RPM 		7500000			/* palse_width to rpm  */
#define L_PULS			  100
#define KETA_10		 	   10
#define KETA_100 		  100
#define KETA_1000		 1000
#define HIGH_SPEED_PULSE 	15100			/* 20131   		これ以上早いパルスはＢ相を調べない 5131 */
#define DIRECTION_CLOSE		    0      		/* 閉方向のＢ相のあるべきレベル */
#define FASTER_SPEED		40000

#define U1_SPEED_BEST		0			/* 0:速度ぴったり */
#define U1_SPEED_UP		1			/* 1:遅いのでUP */
#define U1_SPEED_DOWN		2			/* 2:速いのでDOWN */

#define NORMAL_21MS_MORE_DUTY		50		/*109 ﾂ�ｳ蠢�ｶﾈ21msﾒﾔﾉﾏｵﾄﾈ�ﾆ�ｶｯｺ�DUTY */
#define NORMAL_28MS_MORE_DUTY		50		/*50 ﾂ�ｳ蠢�ｶﾈ28msﾒﾔﾉﾏｵﾄﾈ�ﾆ�ｶｯｺ�DUTY */
#define SOFT_START_20MS_LESS_DUTY	18		/*18 ﾂ�ｳ蠢�ｶﾈﾐ｡ﾓﾚ20msｵﾄﾈ�ﾆ�ｶｯﾖﾐDUTY */
#define SOFT_START_20MS_MORE_DUTY	12		/*105 ﾂ�ｳ蠢�ｶﾈ20msﾒﾔﾉﾏｵﾄﾈ�ﾆ�ｶｯﾖﾐDUTY */

/* extern u1 u1g_c_no_plus;					ﾃﾞｭｰﾃｨｰ追加ｲﾝﾀｰﾊﾞﾙｶｳﾝﾀ */
/* extern u2 u2g_c_interval_plus;				パルスが来ない時間をカウント */

/* extern u1 u1g_count_abnormal_speed_pulse; */
extern u1 u1g_count_moveing_B; 				/*動作中B相監視ｶｳﾝﾀ*/
extern u1 u1g_fg_final_state;
extern u1 u1g_fg_mid_state;
extern u1 u1g_fg_direction_pulse; 				/* パルスの方向 */

extern u1 u1g_c_move_consist;  				/* flashに動作回数を書く　パルスカウント */
extern u1 u1g_fg_move_consist;    				/* 上の変数が250パルスを超えたらフラグオン！ */
extern u4 u4g_plus_length;

extern u1 u1g_fg_input_encoder;
extern u4 u4g_d_rpm_before;

extern u2 u2g_d_rpm_current;
extern u1 u1g_cnt_change_mode;  		/*停＋開閉SW長押し時間 上限リセット*/
/* extern u1 u1g_c_check_out;						ﾁｪｯｸ用出力時間ｶｳﾝﾀ */

#endif


