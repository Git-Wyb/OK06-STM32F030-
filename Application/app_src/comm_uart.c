#include "comm_uart.h"
#include "def_local.h"
#include "comm_uart_local.h"
#include "Uart.h"
#include "Gpio.h"
#include "variables.h"
#include "storage.h"
#include "a_data_exchange.h"
#include "functions.h"
#include "anjou_test.h"
#include "input_encoder.h"
#include <string.h>

const u1 c_uart_mode[N_CURRENT_MODE] = {	
	UART_VALUE_MODE_BEGEN,		UART_VALUE_MODE_BEGEN,		UART_VALUE_MODE_BEGEN,		UART_VALUE_MODE_BEGEN,		UART_VALUE_MODE_BEGEN,		/* 0бл4 */
	UART_VALUE_MODE_BEGEN,		UART_VALUE_MODE_BEGEN,		UART_VALUE_MODE_BEGEN,		UART_VALUE_MODE_BEGEN,		UART_VALUE_MODE_BEGEN,		/* 5бл9 */
	UART_VALUE_MODE_BEGEN,		UART_VALUE_MODE_BEGEN,		UART_VALUE_MODE_BEGEN,		UART_VALUE_MODE_BEGEN,		UART_VALUE_UNEXPECT,		/* 10бл14 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 15бл19 */
	UART_VALUE_MODE_BEGEN,		UART_VALUE_MODE_BEGEN,		UART_VALUE_MODE_BEGEN,		UART_VALUE_MODE_BEGEN,		UART_VALUE_MODE_BEGEN,		/* 20бл24 */
	UART_VALUE_MODE_BEGEN,		UART_VALUE_MODE_BEGEN,		UART_VALUE_MODE_BEGEN,		UART_VALUE_MODE_BEGEN,		UART_VALUE_UNEXPECT,		/* 25бл29 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 30бл34 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 35бл39 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 40бл44 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 45бл49 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 50бл54 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 55бл59 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 60бл64 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 65бл69 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 70бл74 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 75бл79 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 80бл84 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 85бл89 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 90бл94 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 95бл99 */
	UART_VALUE_MODE_NORMAL,		UART_VALUE_MODE_NORMAL,		UART_VALUE_MODE_NORMAL,		UART_VALUE_MODE_NORMAL,		UART_VALUE_MODE_NORMAL,		/* 100бл104 */
	UART_VALUE_MODE_NORMAL,		UART_VALUE_MODE_NORMAL,		UART_VALUE_MODE_NORMAL,		UART_VALUE_MODE_NORMAL,		UART_VALUE_MODE_NORMAL,		/* 105бл109 */
	UART_VALUE_MODE_NORMAL,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_MODE_NORMAL,		UART_VALUE_MODE_NORMAL,		/* 110бл114 */
	UART_VALUE_UNEXPECT,		UART_VALUE_MODE_NORMAL,		UART_VALUE_MODE_NORMAL,		UART_VALUE_MODE_NORMAL,		UART_VALUE_MODE_NORMAL,		/* 115бл119 */
	UART_VALUE_MODE_NORMAL,		UART_VALUE_MODE_NORMAL,		UART_VALUE_MODE_NORMAL,		UART_VALUE_MODE_NORMAL,		UART_VALUE_UNEXPECT,		/* 120бл124 */
	UART_VALUE_MODE_NORMAL,		UART_VALUE_MODE_NORMAL,		UART_VALUE_MODE_NORMAL,		UART_VALUE_MODE_NORMAL,		UART_VALUE_MODE_NORMAL,		/* 125бл129 */
	UART_VALUE_MODE_NORMAL,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 130бл134 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 135бл139 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 140бл144 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 145бл149 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 150бл154 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 155бл159 */
	UART_VALUE_MODE_RECOVER,	UART_VALUE_MODE_RECOVER,	UART_VALUE_MODE_RECOVER,	UART_VALUE_MODE_RECOVER,	UART_VALUE_MODE_RECOVER,	/* 160бл164 */
	UART_VALUE_MODE_RECOVER,	UART_VALUE_MODE_RECOVER,	UART_VALUE_MODE_RECOVER,	UART_VALUE_MODE_RECOVER,	UART_VALUE_MODE_RECOVER,	/* 165бл169 */
	UART_VALUE_MODE_RECOVER,	UART_VALUE_MODE_RECOVER,	UART_VALUE_MODE_RECOVER,	UART_VALUE_MODE_RECOVER,	UART_VALUE_MODE_RECOVER,	/* 170бл174 */
	UART_VALUE_UNEXPECT,		UART_VALUE_MODE_RECOVER,	UART_VALUE_MODE_RECOVER,	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 175бл179 */
	UART_VALUE_MODE_RECOVER,	UART_VALUE_MODE_RECOVER,	UART_VALUE_MODE_RECOVER,	UART_VALUE_MODE_RECOVER,	UART_VALUE_MODE_RECOVER,	/* 180бл184 */
	UART_VALUE_MODE_RECOVER,	UART_VALUE_MODE_RECOVER,	UART_VALUE_MODE_RECOVER,	UART_VALUE_MODE_RECOVER,	UART_VALUE_MODE_RECOVER,	/* 185бл189 */
	UART_VALUE_MODE_RECOVER,	UART_VALUE_MODE_RECOVER,	UART_VALUE_MODE_RECOVER,	UART_VALUE_MODE_RECOVER,	UART_VALUE_MODE_RECOVER,	/* 190бл194 */
	UART_VALUE_UNEXPECT,		UART_VALUE_MODE_RECOVER,	UART_VALUE_MODE_RECOVER,	UART_VALUE_MODE_RECOVER,	UART_VALUE_UNEXPECT			/* 195бл199 */
};

const u1 c_uart_state[N_CURRENT_MODE] = {	
	UART_VALUE_STATE_STOP_MID,	UART_VALUE_STATE_OPENING,	UART_VALUE_STATE_OPENING,	UART_VALUE_STATE_CLOSING,	UART_VALUE_STATE_OPENING,	/* 0бл4 */
	UART_VALUE_STATE_OPENING,	UART_VALUE_NO_CHANGE,		UART_VALUE_NO_CHANGE,		UART_VALUE_NO_CHANGE,		UART_VALUE_NO_CHANGE,		/* 5бл9 */
	UART_VALUE_STATE_UPPER,		UART_VALUE_STATE_CLOSING,	UART_VALUE_STATE_OPENING,	UART_VALUE_STATE_OPENING,	UART_VALUE_UNEXPECT,		/* 10бл14 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 15бл19 */
	UART_VALUE_STATE_STOP_MID,	UART_VALUE_STATE_STOP_MID,	UART_VALUE_STATE_OPENING,	UART_VALUE_STATE_CLOSING,	UART_VALUE_STATE_OPENING,	/* 20бл24 */
	UART_VALUE_STATE_CLOSING,	UART_VALUE_STATE_OPENING,	UART_VALUE_STATE_CLOSING,	UART_VALUE_STATE_OPENING,	UART_VALUE_UNEXPECT,		/* 25бл29 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 30бл34 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 35бл39 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 40бл44 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 45бл49 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 50бл54 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 55бл59 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 60бл64 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 65бл69 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 70бл74 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 75бл79 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 80бл84 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 85бл89 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 90бл94 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 95бл99 */
	UART_VALUE_STATE_LOWER,		UART_VALUE_STATE_STOP_MID,	UART_VALUE_STATE_UPPER,		UART_VALUE_STATE_OPENING,	UART_VALUE_STATE_OPENING,	/* 100бл104 */
	UART_VALUE_STATE_LOWER,		UART_VALUE_STATE_CLOSING,	UART_VALUE_STATE_OPENING,	UART_VALUE_STATE_CLOSING,	UART_VALUE_STATE_LOWER,		/* 105бл109 */
	UART_VALUE_STATE_LOWER,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_STATE_OPENING,	UART_VALUE_STATE_CLOSING,	/* 110бл114 */
	UART_VALUE_UNEXPECT,		UART_VALUE_STATE_OPENING,	UART_VALUE_STATE_OPENING,	UART_VALUE_STATE_OPENING,	UART_VALUE_STATE_CLOSING,	/* 115бл119 */
	UART_VALUE_STATE_OPENING,	UART_VALUE_STATE_LOWER,		UART_VALUE_STATE_LOWER,		UART_VALUE_STATE_STOP_MID,	UART_VALUE_UNEXPECT,		/* 120бл124 */
	UART_VALUE_STATE_OPENING,	UART_VALUE_STATE_OPENING,	UART_VALUE_STATE_STOP_MID,	UART_VALUE_NO_CHANGE,		UART_VALUE_STATE_STOP_MID,	/* 125бл129 */
	UART_VALUE_NO_CHANGE,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 130бл134 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 135бл139 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 140бл144 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 145бл149 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 150бл154 */
	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 155бл159 */
	UART_VALUE_STATE_STOP_MID,	UART_VALUE_STATE_OPENING,	UART_VALUE_STATE_CLOSING,	UART_VALUE_STATE_STOP_MID,	UART_VALUE_STATE_STOP_MID,	/* 160бл164 */
	UART_VALUE_STATE_STOP_MID,	UART_VALUE_STATE_OPENING,	UART_VALUE_STATE_OPENING,	UART_VALUE_STATE_CLOSING,	UART_VALUE_STATE_STOP_MID,	/* 165бл169 */
	UART_VALUE_STATE_STOP_MID,	UART_VALUE_STATE_STOP_MID,	UART_VALUE_STATE_STOP_MID,	UART_VALUE_STATE_OPENING,	UART_VALUE_STATE_CLOSING,	/* 170бл174 */
	UART_VALUE_UNEXPECT,		UART_VALUE_STATE_OPENING,	UART_VALUE_STATE_OPENING,	UART_VALUE_UNEXPECT,		UART_VALUE_UNEXPECT,		/* 175бл179 */
	UART_VALUE_STATE_LOWER,		UART_VALUE_STATE_OPENING,	UART_VALUE_STATE_CLOSING,	UART_VALUE_STATE_LOWER,		UART_VALUE_STATE_LOWER,		/* 180бл184 */
	UART_VALUE_STATE_OPENING,	UART_VALUE_STATE_STOP_MID,	UART_VALUE_STATE_OPENING,	UART_VALUE_STATE_CLOSING,	UART_VALUE_STATE_LOWER,		/* 185бл189 */
	UART_VALUE_STATE_LOWER,		UART_VALUE_STATE_STOP_MID,	UART_VALUE_STATE_STOP_MID,	UART_VALUE_STATE_OPENING,	UART_VALUE_STATE_OPENING,	/* 190бл194 */
	UART_VALUE_STATE_OPENING,	UART_VALUE_STATE_OPENING,	UART_VALUE_STATE_OPENING,	UART_VALUE_STATE_OPENING,	UART_VALUE_NO_CHANGE		/* 195бл199 */
};

const u1 c_uart_err[N_ERR] = {	
	UART_VALUE_ERROR_NONE,			
	UART_VALUE_ERROR_OVERLOAD,		
	UART_VALUE_ERROR_SENS_ELEC,		
	UART_VALUE_ERROR_NONE,			
	UART_VALUE_ERROR_HIGH_SPEED,	
	UART_VALUE_ERROR_NONE,			
	UART_VALUE_ERROR_THERMAL,		
	UART_VALUE_ERROR_NONE,			
	UART_VALUE_ERROR_NONE,			
	UART_VALUE_ERROR_NONE,			
	UART_VALUE_ERROR_TIMER,	
	UART_VALUE_ERROR_ENCODER,
	UART_VALUE_ERROR_SOFT_ROCK,
	UART_VALUE_ERROR_NONE,	
	UART_VALUE_ERROR_SOLENOID,	
	UART_VALUE_ERROR_NONE,		
	UART_VALUE_ERROR_FET,	
	UART_VALUE_ERROR_POWER,		
	UART_VALUE_ERROR_TEMP		
};

STATIC bool act_shutter = 0;					
STATIC u1 u1l_uart_txbuf[N_UART_BYTE_TX] = {0};	
STATIC u1 u1l_uart_txans[N_UART_BYTE_TX_ANS] = {0};
STATIC u1 u1l_uart_rxbuf[N_UART_BYTE_RX] = {0};		
STATIC u1 u1l_uart_rxans[N_UART_BYTE_RX_ANS] = {0};
STATIC u1 u1l_uart_value_mode = 0;		
STATIC u1 u1l_uart_value_state = 0;		
STATIC u1 u1l_uart_value_error = 0;		
STATIC u1 u1l_uart_value_mode_pre = 0;	
STATIC u1 u1l_uart_value_state_pre = 0;	
STATIC u1 u1l_uart_value_error_pre = 0;		
STATIC uart_ph uart_phase = UART_PH_RESET_ON;	
STATIC u1 u1l_cnt_t4_5ms_uart = 0;				
STATIC u1 u1l_cnt_uart_retry = 0;				
STATIC uart_ev ev_uart = {0};					
STATIC bool uart_key_in = 0;					
STATIC bool uart_key_detect = 0;				
STATIC bool uart_err_rcv = 0;					
STATIC u2 u2l_cnt_t4_5ms_after_error = 0;			
STATIC uart_error_tx uart_err = UART_ERR_NONE;	
STATIC TYPE_FLASH_ERROR_BODY_1 uart_record_err1 = {0};
STATIC TYPE_FLASH_ERROR_BODY_2 uart_record_err2 = {0};
STATIC TYPE_FLASH_HSIZE_BODY uart_record_base = {0};
STATIC TYPE_FLASH_FACT_BODY uart_record_fact = {0};
STATIC u1 u1l_uart_state_pre = 0;				

STATIC bool flg_uart_fact_trq_test = 0;			
STATIC bool flg_uart_fact_elec_test = 0;	
STATIC u2 u2l_cnt_uart_fact = 0;			

STATIC void check_update_trns(u1 mode);
STATIC void check_shutter_move(u1 mode);
STATIC void uart_value_change(void);
STATIC void check_error(void);
STATIC void uart_set_trans(u1 *value_now, u1 *value_pre);
STATIC void uart_check_key(void);
STATIC void reserve_uart_trns(void);
STATIC void check_error_change(u1 mode);
STATIC void update_error_trns(u1 mode);
STATIC uart_ph check_uart_retry(uart_ph ph_retry);
STATIC bool check_uart_rx(void);
STATIC void check_err_record(void);
STATIC void set_err_record(u1 no_array, u1 no_err, u2 num_move, u1 *err_num);
STATIC void uart_update_tx_buf(void);
STATIC void uart_tx_start(void);
STATIC void uart_tx_end(void);
STATIC uart_ph uart_tx_ans_wait(uart_ph ph_now, uart_ph ph_next, uart_ph ph_retry);
STATIC uart_ph uart_tx_ans_check(u1 req_ans, uart_ph ph_retry, uart_ph ph_next, bool buzz_off);
STATIC void uart_clear_tx_ans(void);
STATIC void uart_clear_rx_buf(void);
STATIC void comm_uart_fact(void);
STATIC void uart_fact_wait_trans_end(uart_ph next_phase);
STATIC void uart_fact_wait_connect(uart_ph next_phase, u1 check_key, u1 check_no_key1, u1 check_no_key2);
STATIC void uart_fact_set_tx(u1 value_id, u1 value_signal);

void comm_uart(void)
{
	if (uart_phase < UART_START_FACT_PHASE) {
		check_update_trns(u1g_current_mode);
		check_shutter_move(u1g_current_mode);
	}
	switch (uart_phase) {
	case UART_PH_RESET_ON:
		if ((++u1l_cnt_t4_5ms_uart) >= T4_5MS_RESET_MODULE) {
			u1l_cnt_t4_5ms_uart = 0u;
			P_EM_RESET_N_1;
			uart_phase = UART_PH_WAIT_START;
		}
		break;
	case UART_PH_WAIT_START:
		if ((++u1l_cnt_t4_5ms_uart) >= T4_5MS_WAIT_START_UART) {
			u1l_cnt_t4_5ms_uart = 0u;
			uart_phase = UART_PH_INITIAL;
		}
		break;
	case UART_PH_INITIAL:
		R_UART0_Receive(u1l_uart_rxbuf, N_UART_BYTE_RX);
		uart_phase = UART_PH_IDLE;
		break;
	case UART_PH_IDLE:
		if (ev_uart.rx == TRUE) {
			ev_uart.rx = FALSE;
			uart_phase = UART_PH_RX_ANS;
		} else if (ev_uart.tx == TRUE) {
			uart_phase = UART_PH_TX_START;
		} else if (u1g_uart_buzzer_order == U1G_ORDER_BUZZER) {
			uart_phase = UART_PH_TX_BUZZER_START;
		} else if (flg_uart_fact_trq_test == 1) {
			uart_phase = UART_PH_FACT_REQ_OPEN;
		} else if (flg_uart_fact_elec_test == 1) {
			u1l_cnt_t4_5ms_uart = 0u;
			u1l_cnt_uart_retry = 0u;
			uart_phase = UART_PH_FACT_REQ_MDL;
		} else {
		}
		break;
	case UART_PH_TX_START:
		uart_tx_start();
		uart_phase = UART_PH_TX;
		break;
	case UART_PH_TX:
		if (ev_uart.tx_end == TRUE) {
			uart_tx_end();
			uart_phase = UART_PH_TX_ANS_WAIT;
		}
		break;
	case UART_PH_TX_ANS_WAIT:
		uart_phase = uart_tx_ans_wait(UART_PH_TX_ANS_WAIT, UART_PH_TX_ANS, UART_PH_TX_START);
		break;
	case UART_PH_TX_ANS:
		uart_phase = uart_tx_ans_check(UART_VALUE_ANS_TX_ACK, UART_PH_TX_START, UART_PH_INITIAL, FALSE);
		break;
	case UART_PH_RX_ANS:
		check_err_record();
		ev_uart.rx_end = FALSE;	
		R_UART0_Send(u1l_uart_rxans, u1l_uart_rxans[UART_RXANS_L_DATA]);
		uart_phase = UART_PH_RX_ANS_END;
		break;
	case UART_PH_RX_ANS_END:
		if (ev_uart.rx_end == TRUE) {
			ev_uart.rx_end = FALSE;
			uart_phase = UART_PH_INITIAL;
		}
		break;
	case UART_PH_TX_BUZZER_START:
		uart_fact_set_tx(UART_VALUE_TX_FACT_WIRELESS_ID, 0u);
		uart_phase = UART_PH_TX_BUZZER;
		break;
	case UART_PH_TX_BUZZER:
		if (ev_uart.tx_end == TRUE) {
			uart_tx_end();
			uart_phase = UART_PH_TX_BUZZER_ANS_WAIT;
		}
		break;
	case UART_PH_TX_BUZZER_ANS_WAIT:
		uart_phase = uart_tx_ans_wait(UART_PH_TX_BUZZER_ANS_WAIT, UART_PH_TX_BUZZER_ANS, UART_PH_TX_BUZZER_START);
		break;
	case UART_PH_TX_BUZZER_ANS:
		uart_phase = uart_tx_ans_check(UART_VALUE_ANS_TX_NACK, UART_PH_TX_BUZZER_START, UART_PH_INITIAL, TRUE);
		break;
	default:
		comm_uart_fact();
		break;
	}
}

STATIC void check_update_trns(u1 mode)
{
	uart_check_key();
	if (uart_err == UART_ERR_NONE) {
		uart_value_change();
		uart_set_trans(&u1l_uart_value_mode, &u1l_uart_value_mode_pre);
		uart_set_trans(&u1l_uart_value_error, &u1l_uart_value_error_pre);
		uart_set_trans(&u1l_uart_value_state, &u1l_uart_value_state_pre);
		if (uart_key_in == TRUE) {
			reserve_uart_trns();
		}
		if (((u1l_uart_state_pre == UART_STATE_ROCK_CLOSE_ON) || (u1l_uart_state_pre == UART_STATE_ROCK_CLOSE_OFF))
			&& ((mode == UART_STATE_ROCK_CANCEL) || (mode == UART_STATE_ROCK_OVERLOAD))) {
			reserve_uart_trns();
		}
		uart_key_in = FALSE;
		if (u1l_uart_value_error != UART_VALUE_ERROR_NONE) {
			uart_err = UART_ERR_WAIT_KEY;
		}
	} else {
		check_error_change(mode);
	}
	u1l_uart_state_pre = mode;
}

STATIC void check_shutter_move(u1 mode)
{
	if ((c_uart_state[mode] == UART_VALUE_STATE_UPPER) || (c_uart_state[mode] == UART_VALUE_STATE_LOWER) || (c_uart_state[mode] == UART_VALUE_STATE_STOP_MID)) {
		act_shutter = FALSE;
	} else if ((c_uart_state[mode] == UART_VALUE_STATE_OPENING) || (c_uart_state[mode] == UART_VALUE_STATE_CLOSING)) {
		act_shutter = TRUE;
	} else {
	}
}

STATIC void uart_value_change(void)
{
	u1l_uart_value_mode = c_uart_mode[u1g_current_mode];
	check_error();
	if (c_uart_state[u1g_current_mode] != UART_VALUE_NO_CHANGE) {
		u1l_uart_value_state = c_uart_state[u1g_current_mode];
	}
}

STATIC void check_error(void)
{
	u1 err = 0;
	
	err = c_uart_err[req_uart_err.u1_uart_err_mode];
	if ((err == UART_VALUE_ERROR_NONE) && (uart_err == UART_ERR_WAIT_KEY)) {
		u1l_uart_value_error = u1l_uart_value_error_pre;
	} else {
		u1l_uart_value_error = err;
	}
}

STATIC void uart_set_trans(u1 *value_now, u1 *value_pre)
{
	if ((*value_now == UART_VALUE_UNEXPECT) || (*value_now == *value_pre)) {
		*value_now = *value_pre;
	} else {
		*value_pre = *value_now;
		reserve_uart_trns();
	}
}

STATIC void uart_check_key(void)
{
	static u1 cnt_no_trns = 0;
	static u1 key_in_pre = 0;
	
	if ((!key_in_pre) && (u1g_f_any_key_input == 1)) {
		uart_key_detect = TRUE;
	}
	if (uart_key_detect == TRUE) {
		if (!ev_uart.tx) {
			if ((++cnt_no_trns) >= CNT_UART_TRNS_FOR_A_KEY) {
				uart_key_detect = FALSE;
				uart_key_in = TRUE;
				cnt_no_trns = 0u;
			}
		} else {
			if (uart_err != UART_ERR_WAIT_KEY) {
				uart_key_detect = FALSE;
			}
			cnt_no_trns = 0u;
		}
	}
	key_in_pre = u1g_f_any_key_input;
}

STATIC void reserve_uart_trns(void)
{
	u1l_cnt_uart_retry = 0u;
	ev_uart.tx = TRUE;
	uart_update_tx_buf();
}

STATIC void uart_update_tx_buf(void)
{
	u1l_uart_txbuf[UART_TX_START] = UART_VALUE_START;
	u1l_uart_txbuf[UART_TX_L_DATA] = UART_VALUE_TX_L_DATA;
	u1l_uart_txbuf[UART_TX_SIGNAL_ID] = UART_VALUE_SIGNAL_ID;
	u1l_uart_txbuf[UART_TX_STATE_ID] = UART_VALUE_TX_STATE_ID;
	u1l_uart_txbuf[UART_TX_STATE] = (u1l_uart_value_mode | u1l_uart_value_state);
	u1l_uart_txbuf[UART_TX_ERROR] = u1l_uart_value_error;
	u1l_uart_txbuf[UART_TX_RESERVE] = UART_VALUE_RESERVE;
}

STATIC void check_error_change(u1 mode)
{
	switch (uart_err) {
	case UART_ERR_WAIT_KEY:
		if (uart_key_detect == TRUE) {
			uart_key_detect = FALSE;
			uart_err = UART_ERR_CNT_AFTER_ERR;
			u2l_cnt_t4_5ms_after_error = 0u;
		} else {
			update_error_trns(mode);
		}
		break;
	case UART_ERR_CNT_AFTER_ERR:
		if ((++u2l_cnt_t4_5ms_after_error) >= T4_5MS_AFTER_ERROR) {
			uart_err = UART_ERR_NONE;
		} 
		break;
	default:
		break;
	}
}


STATIC void update_error_trns(u1 mode)
{
	uart_value_change();
	uart_set_trans(&u1l_uart_value_mode, &u1l_uart_value_mode_pre);
	uart_set_trans(&u1l_uart_value_state, &u1l_uart_value_state_pre);
	uart_set_trans(&u1l_uart_value_error, &u1l_uart_value_error_pre);
	if (((u1l_uart_state_pre == UART_STATE_ROCK_CLOSE_ON) || (u1l_uart_state_pre == UART_STATE_ROCK_CLOSE_OFF))
		&& ((mode == UART_STATE_ROCK_CANCEL) || (mode == UART_STATE_ROCK_OVERLOAD))) {
		reserve_uart_trns();
	}
}

STATIC void uart_tx_start(void)
{
	ev_uart.tx = FALSE;
	ev_uart.tx_end = FALSE;
	R_UART0_Send(u1l_uart_txbuf, N_UART_BYTE_TX);
	uart_err_rcv = FALSE;
}

STATIC void uart_tx_end(void)
{
	u1l_cnt_t4_5ms_uart = 0u;
	ev_uart.tx_end = FALSE;
	ev_uart.ans_rcv = FALSE;	
}

STATIC uart_ph uart_tx_ans_wait(uart_ph ph_now, uart_ph ph_next, uart_ph ph_retry)
{
	uart_ph ph_ret = UART_PH_IDLE;
	
	if ((++u1l_cnt_t4_5ms_uart) >= T4_5MS_LIMIT_WAIT_ANS) {
		ph_ret = check_uart_retry(ph_retry);
	} else if (ev_uart.ans_rcv == TRUE) {
		ev_uart.ans_rcv = FALSE;
		ph_ret = ph_next;
	} else {
		ph_ret = ph_now;
	}
	return  ph_ret;
}

STATIC uart_ph uart_tx_ans_check(u1 req_ans, uart_ph ph_retry, uart_ph ph_next, bool buzz_off)
{
	uart_ph ph_ret = UART_PH_IDLE;
	
	if (u1l_uart_txans[UART_TXANS_SIGNAL_ID] == req_ans) {
		if (buzz_off == TRUE) {
			u1g_uart_buzzer_order = U1G_ORDER_NO_BUZZER;
		}
		u1l_cnt_uart_retry = 0u;
		ph_ret = ph_next;
	} else {
		ph_ret = check_uart_retry(ph_retry);
	}
	uart_clear_tx_ans();
	return  ph_ret;
}

STATIC void uart_clear_tx_ans(void)
{
	u1l_uart_txans[UART_TX_START] = 0u;
	u1l_uart_txans[UART_TX_L_DATA] = 0u;
	u1l_uart_txans[UART_TX_SIGNAL_ID] = 0u;
}

STATIC void uart_clear_rx_buf(void)
{
	u1l_uart_rxbuf[UART_TX_START] = 0u;
	u1l_uart_rxbuf[UART_TX_L_DATA] = 0u;
	u1l_uart_rxbuf[UART_TX_SIGNAL_ID] = 0u;
	u1l_uart_rxbuf[UART_RX_ERROR_ID] = 0u;
	u1l_uart_rxbuf[UART_RX_SW] = 0u;
	u1l_uart_rxbuf[UART_RX_ERROR_1] = 0u;
	u1l_uart_rxbuf[UART_RX_ERROR_2] = 0u;
}

STATIC uart_ph check_uart_retry(uart_ph ph_retry)
{
	uart_ph ret_ph = UART_PH_IDLE;
	
	if ((++u1l_cnt_uart_retry) <= UART_LIMIT_RETRY_TX) {
		ret_ph = ph_retry;
	} else {
		u1l_cnt_uart_retry = 0u;
		if (ph_retry == UART_PH_TX_BUZZER_START) {
			u1g_uart_buzzer_order = U1G_ORDER_NO_BUZZER;
		}
		if (ph_retry == UART_PH_FACT_REQ_MDL) {
			Fg_uart_fact_error = TRUE;
			ret_ph = UART_PH_FACT_ERROR;
		} else {
			ret_ph = UART_PH_INITIAL;
		}
	}
	u1l_cnt_t4_5ms_uart = 0u;
	return ret_ph;
}

void i_serial_uart_rx_end(void)
{
    if(flag_test_enable == 1) uart_recv_del();//test
    else
    {
        if (!uart_err_rcv) {
            if ((uart_phase == UART_PH_TX) || (uart_phase == UART_PH_TX_ANS_WAIT) 
                || (uart_phase == UART_PH_TX_BUZZER) || (uart_phase == UART_PH_TX_BUZZER_ANS_WAIT)) {
                if ((u1l_uart_txans[UART_RX_START] == UART_VALUE_START) && (u1l_uart_txans[UART_TXANS_L_DATA] == UART_VALUE_ANS_TX_L_DATA)) {
                    ev_uart.ans_rcv = TRUE;
                }
            } else if ((uart_phase == UART_PH_FACT_REQ_MDL_END) || (uart_phase == UART_PH_FACT_ANS_WAIT) || (uart_phase == UART_PH_FACT_ANS) || (uart_phase == UART_PH_FACT_WAIT_MODEL)) {
                R_UART0_Receive(u1l_uart_txans, N_UART_BYTE_TX_ANS);
                if ((u1l_uart_txans[UART_RX_START] == UART_VALUE_START) && (u1l_uart_txans[UART_TXANS_L_DATA] == UART_VALUE_ANS_TX_L_DATA)) {
                    ev_uart.ans_rcv = TRUE;
                }
            } else  if (uart_phase == UART_PH_IDLE) {
                if (check_uart_rx() == TRUE) {
                    ev_uart.rx = TRUE;
                }
                if(timeout_test_enter > 0 && u1g_current_mode < 100) uart_rx_test_check();//test
                R_UART0_Receive(u1l_uart_rxbuf, N_UART_BYTE_RX);
            } else {
            }
        } else {
            uart_err_rcv = FALSE;
        }
        uart_clear_rx_buf();
    }
}

STATIC bool check_uart_rx(void)
{
	bool ret = TRUE;
	
	if (u1l_uart_rxbuf[UART_RX_START] != UART_VALUE_START) {
		ret = FALSE;
	}
	if (u1l_uart_rxbuf[UART_TXANS_L_DATA] != UART_VALUE_RX_L_DATA) {
		ret = FALSE;
	}
	if (u1l_uart_rxbuf[UART_RX_SIGNAL_ID] != UART_VALUE_SIGNAL_ID) {
		ret = FALSE;
	}
	if (u1l_uart_rxbuf[UART_RX_ERROR_ID] != UART_VALUE_RX_HISTRY_ID) {
		ret = FALSE;
	}
	if (u1l_uart_rxbuf[UART_RX_SW] != UART_VALUE_RX_HISTRY_SW) {
		ret = FALSE;
	}
	if (u1l_uart_rxbuf[UART_RX_ERROR_1] != UART_VALUE_RX_HISTRY_ERR1) {
		ret = FALSE;
	}
	if (u1l_uart_rxbuf[UART_RX_ERROR_2] != UART_VALUE_RX_HISTRY_ERR2) {
		ret = FALSE;
	}
	if (act_shutter == TRUE) {
		ret = FALSE;
	}
	return ret;
}

STATIC void check_err_record(void)
{
	u1 err_num = 0;
	
	get_storage_data(STORAGE_RECORD_ERR1, (u1 *) &uart_record_err1);
	get_storage_data(STORAGE_RECORD_ERR2, (u1 *) &uart_record_err2);
	get_storage_data(STORAGE_STUDY_BASE, (u1 *) &uart_record_base);
	get_storage_data(STORAGE_FACTORY, (u1 *) &uart_record_fact);
	
	u1l_uart_rxans[UART_RXANS_START] = UART_VALUE_START;
	u1l_uart_rxans[UART_RXANS_SIGNAL_ID] = UART_VALUE_SIGNAL_ID;
	u1l_uart_rxans[UART_RXANS_ERROR_ID] = UART_VALUE_ANS_RX_ERR_ID;
	u1l_uart_rxans[UART_RXANS_NUM_OPEN_CLOSE1] = (u1) uart_record_err1.u2_number_openclose;
	u1l_uart_rxans[UART_RXANS_NUM_OPEN_CLOSE2] = (u1) (uart_record_err1.u2_number_openclose >> UART_SHIFTDOWN_1BYTE);
	u1l_uart_rxans[UART_RXANS_NUM_MOVE1] = (u1) uart_record_err1.u2_number_move;
	u1l_uart_rxans[UART_RXANS_NUM_MOVE2] = (u1) (uart_record_err1.u2_number_move >> UART_SHIFTDOWN_1BYTE);
	u1l_uart_rxans[UART_RXANS_OVERLOAD] = (u1) (a_u2g_close_AD_exchange_to_Nm(get_max_close_learn_data()) / KETA_10);	/* 1/10N?mд╦ЙфУQ */
	u1l_uart_rxans[UART_RXANS_SIZE_H1] = (u1) a_u2g_pulse_exchange_to_rotation(uart_record_base.u2_size_data);
    u1l_uart_rxans[UART_RXANS_SIZE_H2] = (u1) (a_u2g_pulse_exchange_to_rotation(uart_record_base.u2_size_data) >> UART_SHIFTDOWN_1BYTE);
	
	set_err_record(UART_RXANS_ERR_RECORD_1, uart_record_err2.err_now.no_err, uart_record_err2.err_now.num_move, &err_num);
	set_err_record(UART_RXANS_ERR_RECORD_2, uart_record_err2.err_prev_1.no_err, uart_record_err2.err_prev_1.num_move, &err_num);
	set_err_record(UART_RXANS_ERR_RECORD_3, uart_record_err2.err_prev_2.no_err, uart_record_err2.err_prev_2.num_move, &err_num);
	set_err_record(UART_RXANS_ERR_RECORD_4, uart_record_err2.err_prev_3.no_err, uart_record_err2.err_prev_3.num_move, &err_num);
	set_err_record(UART_RXANS_ERR_RECORD_5, uart_record_err2.err_prev_4.no_err, uart_record_err2.err_prev_4.num_move, &err_num);
	set_err_record(UART_RXANS_ERR_RECORD_6, uart_record_err2.err_prev_5.no_err, uart_record_err2.err_prev_5.num_move, &err_num);
	set_err_record(UART_RXANS_ERR_RECORD_7, uart_record_err2.err_prev_6.no_err, uart_record_err2.err_prev_6.num_move, &err_num);
	set_err_record(UART_RXANS_ERR_RECORD_8, uart_record_err2.err_prev_7.no_err, uart_record_err2.err_prev_7.num_move, &err_num);
	set_err_record(UART_RXANS_ERR_RECORD_9, uart_record_err2.err_prev_8.no_err, uart_record_err2.err_prev_8.num_move, &err_num);
	set_err_record(UART_RXANS_ERR_RECORD_10, uart_record_err2.err_prev_9.no_err, uart_record_err2.err_prev_9.num_move, &err_num);
	u1l_uart_rxans[UART_RXANS_L_DATA] = UART_VALUE_ANS_RX_L_DATA + err_num;
}

STATIC void set_err_record(u1 no_array, u1 no_err, u2 num_move, u1 *err_num)
{
	u1l_uart_rxans[no_array] = no_err;
	u1l_uart_rxans[no_array + 1] = (u1) num_move;
	u1l_uart_rxans[no_array + 2] = (u1) (num_move >> UART_SHIFTDOWN_1BYTE);
	if (no_err != 0u) {
		*err_num += UART_VALUE_ANS_RX_ERR_DATA;
	}
}

void i_serial_uart_tx_end(void)
{
	if ((uart_phase == UART_PH_TX) || (uart_phase == UART_PH_TX_START) 
		|| (uart_phase == UART_PH_FACT_REQ_MDL) || (uart_phase == UART_PH_FACT_REQ_MDL_END)
	    || (uart_phase == UART_PH_TX_BUZZER) || (uart_phase == UART_PH_TX_BUZZER_START)) {
		ev_uart.tx_end = TRUE;
		R_UART0_Receive(u1l_uart_txans, N_UART_BYTE_TX_ANS);
	} else if ((uart_phase == UART_PH_FACT_REQ_OPEN) || (uart_phase == UART_PH_FACT_REQ_OPEN_END)
				|| (uart_phase == UART_PH_FACT_REQ_STOP) || (uart_phase == UART_PH_FACT_REQ_STOP_END)
				|| (uart_phase == UART_PH_FACT_REQ_CLOSE) || (uart_phase == UART_PH_FACT_REQ_CLOSE_END)
			    || (uart_phase == UART_PH_FACT_REQ_OPEN_AFTER_RESET) || (uart_phase == UART_PH_FACT_REQ_OPEN_END_AFTER_RESET)) { 
		ev_uart.tx_end = TRUE;
	} else {
		ev_uart.rx_end = TRUE;
	}
}

void i_serial_uart_rx_error(u1 err)
{
	if (err & UART_ERR_PARITY) {
		uart_err_rcv = TRUE;
	}
}

void i_serial_uart_rx_over_run(void)
{
}

void uart_fact_trq_test(void)
{
	flg_uart_fact_trq_test = TRUE;
}

void uart_fact_elec_test(void)
{
	flg_uart_fact_elec_test = TRUE;
}

STATIC void comm_uart_fact(void)
{
	static bool fact_hang_up = FALSE;	
	
	if (fact_hang_up == TRUE) {
		uart_phase = UART_PH_FACT_ERROR;
	}
	if ((uart_phase == UART_PH_FACT_WAIT_ANS_OPEN) || (uart_phase == UART_PH_FACT_WAIT_ANS_STOP)
	    || (uart_phase == UART_PH_FACT_WAIT_ANS_CLOSE) || (uart_phase == UART_PH_FACT_REQ_RESET)
	    || (uart_phase == UART_PH_FACT_INTERVAL_AFTER_RESET) || (uart_phase == UART_PH_FACT_CHECK_RESET)
	    || (uart_phase == UART_PH_FACT_RESET_OK) || (uart_phase == UART_PH_FACT_ANS_WAIT)
	    || (uart_phase == UART_PH_FACT_ANS) || (uart_phase == UART_PH_FACT_WAIT_MODEL)
	    || (uart_phase == UART_PH_FACT_FINISH) || (uart_phase == UART_PH_FACT_ERROR)) {
		if (u1g_uart_buzzer_order == U1G_ORDER_BUZZER) {
			uart_phase = UART_PH_TX_BUZZER_START;
			fact_hang_up = TRUE;
		}
	}
	switch (uart_phase) {
	case UART_PH_FACT_REQ_OPEN:
		uart_fact_set_tx(UART_VALUE_TX_FACT_CONNECT_ID, UART_VALUE_FACT_SW_OPEN);
		uart_phase = UART_PH_FACT_REQ_OPEN_END;
		break;
	case UART_PH_FACT_REQ_OPEN_END:
		uart_fact_wait_trans_end(UART_PH_FACT_WAIT_ANS_OPEN);
		break;
	case UART_PH_FACT_WAIT_ANS_OPEN:
		uart_fact_wait_connect(UART_PH_FACT_REQ_STOP, Fg_keyin_open, Fg_keyin_stop, Fg_keyin_close);
		break;
	case UART_PH_FACT_REQ_STOP:
		Fg_uart_fact_check_stop = TRUE;
		u2l_cnt_uart_fact = 0u;
		uart_fact_set_tx(UART_VALUE_TX_FACT_CONNECT_ID, UART_VALUE_FACT_SW_STOP);
		uart_phase = UART_PH_FACT_REQ_STOP_END;
		break;
	case UART_PH_FACT_REQ_STOP_END:
		uart_fact_wait_trans_end(UART_PH_FACT_WAIT_ANS_STOP);
		break;
	case UART_PH_FACT_WAIT_ANS_STOP:
		uart_fact_wait_connect(UART_PH_FACT_REQ_CLOSE, Fg_keyin_stop, Fg_keyin_open, Fg_keyin_close);
		break;
	case UART_PH_FACT_REQ_CLOSE:
		Fg_uart_fact_check_stop = FALSE;
		u2l_cnt_uart_fact = 0u;
		uart_fact_set_tx(UART_VALUE_TX_FACT_CONNECT_ID, UART_VALUE_FACT_SW_CLOSE);
		uart_phase = UART_PH_FACT_REQ_CLOSE_END;
		break;
	case UART_PH_FACT_REQ_CLOSE_END:
		uart_fact_wait_trans_end(UART_PH_FACT_WAIT_ANS_CLOSE);
		break;
	case UART_PH_FACT_WAIT_ANS_CLOSE:
		uart_fact_wait_connect(UART_PH_FACT_REQ_RESET, Fg_keyin_close, Fg_keyin_open, Fg_keyin_stop);
		break;
	case UART_PH_FACT_REQ_RESET:
		u2l_cnt_uart_fact = 0u;
		P_EM_RESET_N_0;
		uart_phase = UART_PH_FACT_INTERVAL_AFTER_RESET;
		break;
	case UART_PH_FACT_INTERVAL_AFTER_RESET:
		if ((++u2l_cnt_uart_fact) >= T4_5MS_FACT_INTERVAL_AFTER_RESET) {
			u2l_cnt_uart_fact = 0u;
			uart_phase = UART_PH_FACT_REQ_OPEN_AFTER_RESET;
		}
		break;
	case UART_PH_FACT_REQ_OPEN_AFTER_RESET:
		uart_fact_set_tx(UART_VALUE_TX_FACT_CONNECT_ID, UART_VALUE_FACT_SW_OPEN);
		uart_phase = UART_PH_FACT_REQ_OPEN_END_AFTER_RESET;
		break;
	case UART_PH_FACT_REQ_OPEN_END_AFTER_RESET:
		uart_fact_wait_trans_end(UART_PH_FACT_CHECK_RESET);
		break;
	case UART_PH_FACT_CHECK_RESET:
		if ((++u2l_cnt_uart_fact) >= T4_5MS_FACT_CHECK_RESET) {
			u2l_cnt_uart_fact = 0u;
			uart_phase = UART_PH_FACT_RESET_OK;
		}
		if (Fg_keyin_open == 1) {
			Fg_uart_fact_error = TRUE;
		}
		break;
	case UART_PH_FACT_RESET_OK:
		P_EM_RESET_N_0;
		Fg_uart_fact_finish_trq_test = TRUE;
		break;
	case UART_PH_FACT_REQ_MDL:
		uart_fact_set_tx(UART_VALUE_TX_FACT_WIRELESS_ID, 0u);
		uart_phase = UART_PH_FACT_REQ_MDL_END;
		break;
	case UART_PH_FACT_REQ_MDL_END:
		if (ev_uart.tx_end == TRUE) {
			ev_uart.tx_end = FALSE;
			ev_uart.ans_rcv = FALSE;	/* епеъеведе┘еєе╚гие╒езй`еые╗й`е╒гй */
			uart_phase = UART_PH_FACT_ANS_WAIT;
		}
		break;
	case UART_PH_FACT_ANS_WAIT:
		uart_phase = uart_tx_ans_wait(UART_PH_FACT_ANS_WAIT, UART_PH_FACT_ANS, UART_PH_FACT_REQ_MDL);
		break;
	case UART_PH_FACT_ANS:
		uart_phase = uart_tx_ans_check(UART_VALUE_ANS_TX_ACK, UART_PH_FACT_REQ_MDL, UART_PH_FACT_WAIT_MODEL, FALSE);
		break;
	case UART_PH_FACT_WAIT_MODEL:
		if (ev_uart.ans_rcv == TRUE) {
			ev_uart.ans_rcv = FALSE;
			if (u1l_uart_txans[UART_TXANS_SIGNAL_ID] == UART_VALUE_ANS_TX_SW_CLOSE) {
				uart_phase = UART_PH_FACT_FINISH;
			}
		}
		break;
	case UART_PH_FACT_FINISH:
		Fg_uart_fact_finish_elec_test = TRUE;
		break;
	case UART_PH_FACT_ERROR:
		break;
	default:
		break;
	}
}

STATIC void uart_fact_wait_trans_end(uart_ph next_phase)
{
	if (ev_uart.tx_end == TRUE) {
		ev_uart.tx_end = FALSE;
		uart_phase = next_phase;
	}
}

STATIC void uart_fact_wait_connect(uart_ph next_phase, u1 check_key, u1 check_no_key1, u1 check_no_key2)
{
	static bool connect_on = FALSE;
	
	if (!connect_on) {
		if (check_key && (!check_no_key1) && (!check_no_key2)) {
			connect_on = TRUE;
			u2l_cnt_uart_fact = 0u;
		}
		if ((++u2l_cnt_uart_fact) >= T4_5MS_FACT_CHECK_CONNECT) {
			Fg_uart_fact_error = TRUE;
			Fg_uart_fact_check_stop = FALSE;
			u2l_cnt_uart_fact = T4_5MS_FACT_CHECK_CONNECT;
		}
	} else {
		if (!check_key) {
			connect_on = FALSE;
			uart_phase = next_phase;
		}
		if ((++u2l_cnt_uart_fact) >= T4_5MS_FACT_CHECK_CONNECT_OFF) {
			Fg_uart_fact_error = TRUE;
			Fg_uart_fact_check_stop = FALSE;
			u2l_cnt_uart_fact = T4_5MS_FACT_CHECK_CONNECT_OFF;
		}
	}
}

STATIC void uart_fact_set_tx(u1 value_id, u1 value_signal)
{
	u1l_uart_txbuf[UART_TX_START] = UART_VALUE_START;
	u1l_uart_txbuf[UART_TX_L_DATA] = UART_VALUE_TX_L_DATA;
	u1l_uart_txbuf[UART_TX_SIGNAL_ID] = UART_VALUE_SIGNAL_ID;
	u1l_uart_txbuf[UART_TX_STATE_ID] = value_id;
	u1l_uart_txbuf[UART_TX_STATE] = value_signal;
	u1l_uart_txbuf[UART_TX_ERROR] = 0u;
	u1l_uart_txbuf[UART_TX_RESERVE] = 0u;
	
	uart_tx_start();
}

/*Function description: Production test program*/
static u1 time_count = 0;
static u2 encoder_speed = 0;
static u1 average_step = 0;
static u2 get_speed_buff[7] = {0};
u1 uart_test_step = UART_TEST_RESET_ON;

#if TEST_MODE==0
void uart_production_test(void)
{
	switch(uart_test_step)
	{
		case UART_TEST_RESET_ON:
			uart_send_buf[0] = 0x22;
			uart_send_buf[1] = 0x08;
			uart_send_buf[2] = 0x09;
			uart_send_buf[3] = 0x09;
			uart_send_buf[4] = 0x00;
			uart_send_buf[5] = 0x00;
			uart_send_buf[6] = 0x00;
			uart_send_buf[7] = 0xBB;
			time_count++;
			if(time_count>200)
			{
				R_UART0_Receive(uart_recv_buf,7);
				time_count = 0;
				R_UART0_Send(uart_send_buf,8);
				uart_test_step = UART_TEST_IDLE;
				flag_test_encoder = 0;
				flag_test_rotate = 0;
			}
			break;
		case UART_TEST_CURR:
			time_count++;
			if(time_count>50)
			{
				time_count = 0;
				uart_send_buf[2] = UART_TEST_CURR;
				uart_send_buf[3] = 0;
				uart_send_buf[4] = uart_test_curr_value & 0xff;
				uart_send_buf[5] = 0;
				uart_send_buf[6] = 0; 
				uart_send_buf[7] = 0xBB;
				
				R_UART0_Send(uart_send_buf,8);
				if(flag_test_encoder == 1) uart_test_step = UART_TEST_ENCODER_SPEED_SEND;
				else uart_test_step = UART_TEST_IDLE;
			}
			break;
		case UART_TEST_TEMP:
			uart_send_buf[2] = UART_TEST_TEMP;
			uart_send_buf[3] = (uart_test_temp_value >> 8) & 0xff;
			uart_send_buf[4] = (uart_test_temp_value & 0xff);
			uart_send_buf[5] = 0;
			uart_send_buf[6] = 0;
			uart_send_buf[7] = 0xBB;
			R_UART0_Send(uart_send_buf,8);
			if(flag_test_encoder == 1) uart_test_step = UART_TEST_ENCODER_SPEED_SEND;
			else uart_test_step = UART_TEST_IDLE;
			break;
		case UART_TEST_VER:
			P_VER_POWER_1;
			time_count++;
			if(time_count>100)
			{
				time_count = 0;
				uart_send_buf[2] = UART_TEST_VER;
				uart_send_buf[3] = (uart_test_ver_value >> 8) & 0xff;
				uart_send_buf[4] = (uart_test_ver_value & 0xff);
				uart_send_buf[5] = 0;
				uart_send_buf[6] = 0;
				uart_send_buf[7] = 0xBB;
				R_UART0_Send(uart_send_buf,8);
				P_VER_POWER_0;
				if(flag_test_encoder == 1) uart_test_step = UART_TEST_ENCODER_SPEED_SEND;
				else uart_test_step = UART_TEST_IDLE;
			}
			break;
		case UART_TEST_OPEN:
			if(flag_test_rotate == 0)
			{
				flag_test_encoder = 1;
				uart_send_buf[2] = UART_TEST_OPEN;
				uart_send_buf[3] = 0;
				uart_send_buf[4] = 0;
				uart_send_buf[5] = 0;
				uart_send_buf[6] = 0;
				uart_send_buf[7] = 0xBB;
				R_UART0_Send(uart_send_buf,8);
				uart_test_step = UART_TEST_ENCODER_SPEED_SEND;
			}
			break;
		case UART_TEST_CLOSE:
		
			break;
		case UART_TEST_ENCODER_SPEED_SEND:
			average_speed();
			if(time_run_cnt == TEST_OPEN_TIME)
			{
				if(s2_encoder_cnt > 0) s2_encoder_cnt |= 0x8000;
				else s2_encoder_cnt = -s2_encoder_cnt; 
				uart_send_buf[2] = UART_TEST_OPEN;
				//uart_send_buf[3] = 0;
				//uart_send_buf[4] = uart_test_curr_value & 0xff;
				//uart_send_buf[5] = (uart_test_ver_value >> 8) & 0xff;
				//uart_send_buf[6] = (uart_test_ver_value & 0xff);
				//uart_send_buf[7] = (uart_test_temp_value >> 8) & 0xff;
				//uart_send_buf[8] = (uart_test_temp_value & 0xff);
				uart_send_buf[3] = (s2_encoder_cnt >> 8) & 0xff;
				uart_send_buf[4] = (s2_encoder_cnt & 0xff);
				uart_send_buf[5] = (encoder_speed >> 8) & 0xff;
				uart_send_buf[6] = (encoder_speed & 0xff);
				uart_send_buf[7] = 0xBB;
				R_UART0_Send(uart_send_buf,8);
				time_run_cnt = 0;
				flag_test_encoder = 0;
				s2_encoder_cnt = 0;
				uart_test_step = UART_TEST_IDLE;
			}
			break;
		case UART_TEST_ROTATE:
			if(flag_test_encoder == 0)
			{
				flag_test_rotate = 1;
				uart_send_buf[2] = UART_TEST_ROTATE;
				uart_send_buf[3] = 0x10;
				uart_send_buf[4] = 0;
				uart_send_buf[5] = 0;
				uart_send_buf[6] = 0;
				uart_send_buf[7] = 0xBB;
				R_UART0_Send(uart_send_buf,8);
				uart_test_step = UART_TEST_IDLE;
			}
			else uart_test_step = UART_TEST_ENCODER_SPEED_SEND;
			break;
		case UART_TEST_EXIT:
			if(flag_test_encoder==0 && flag_test_rotate==0)
			{
				flag_test_enable = 0;
				uart_send_buf[0] = 0x22;
				uart_send_buf[1] = 0x08;
				uart_send_buf[2] = 0x0A;
				uart_send_buf[3] = 0x0A;
				uart_send_buf[4] = 0x00;
				uart_send_buf[5] = 0x00;
				uart_send_buf[6] = 0x00;
				uart_send_buf[7] = 0xBB;
				R_UART0_Send(uart_send_buf,8);
				
				R_UART0_Receive(u1l_uart_rxbuf, N_UART_BYTE_RX);
				time_count = 0;
				time_run_cnt = 0;
				s2_encoder_cnt = 0;
				flag_test_once_stop = 0;
				uart_test_step = UART_TEST_RESET_ON;
			}
			else if(flag_test_encoder == 1) uart_test_step = UART_TEST_ENCODER_SPEED_SEND;
			else uart_test_step = UART_TEST_IDLE;
			break;
		default:
			time_count = 0;
		break; 
	}
}
#endif

void uart_recv_del(void)
{
	u1 recvdata_datect = 1;
	
	if(uart_recv_buf[0] != 0x11) recvdata_datect = 0;
	else if(uart_recv_buf[1] != 0x12) recvdata_datect = 0;
	else if(uart_recv_buf[2] != 0x07) recvdata_datect = 0;
	else if(uart_recv_buf[4] != 0x00) recvdata_datect = 0;
	else if(uart_recv_buf[5] != 0x00) recvdata_datect = 0;
	else if(uart_recv_buf[6] != 0xAA) recvdata_datect = 0;
	
	if(recvdata_datect != 0)
	{
		uart_test_step = uart_recv_buf[3];
		time_count = 0;
	}
	for(recvdata_datect=0;recvdata_datect<7;recvdata_datect++)
	{
		uart_recv_buf[recvdata_datect] = 0;		
	}
	R_UART0_Receive(uart_recv_buf, 7);
}

void average_speed(void)
{
	u1 i=0,j=0;
	u2 u2_temp = 0;
	
	switch(average_step)
	{
		case 0:
			if(2000<time_run_cnt && time_run_cnt<3000)
			{
				get_speed_buff[0] = u2g_d_rpm_current;
				average_step = 1;
			}
			break;
		case 1:
			if(3000<time_run_cnt && time_run_cnt<4000)
			{
				get_speed_buff[1] = u2g_d_rpm_current;
				average_step = 2;
			}
			break;
		case 2:
			if(4000<time_run_cnt && time_run_cnt<5000)
			{
				get_speed_buff[2] = u2g_d_rpm_current;
				average_step = 3;
			}
			break;
		case 3:
			if(5000<time_run_cnt && time_run_cnt<6000)
			{
				get_speed_buff[3] = u2g_d_rpm_current;
				average_step = 4;
			}
			break;
		case 4:
			if(6000<time_run_cnt && time_run_cnt<7000)
			{
				get_speed_buff[4] = u2g_d_rpm_current;
				average_step = 5;
			}
			break;
		case 5:
			if(7000<time_run_cnt && time_run_cnt<8000)
			{
				get_speed_buff[5] = u2g_d_rpm_current;
				average_step = 6;
			}
			break;
		case 6:
			if(8000<time_run_cnt && time_run_cnt<9000)
			{
				get_speed_buff[6] = u2g_d_rpm_current;
				//encoder_speed = encoder_speed / 6;
				for(i=0; i<6; i++)
				{
					for(j=6; j>i; j--)
					{
						if(get_speed_buff[j-1] > get_speed_buff[j])
						{
							u2_temp = get_speed_buff[j];
							get_speed_buff[j] = get_speed_buff[j-1];
							get_speed_buff[j-1] = u2_temp;
						}
					}
				}
				encoder_speed = get_speed_buff[3];
				average_step = 0;
			}
			break;
		default:
			break;
	}

}

s2 get_cnt = 0;
void uart_rx_test_check(void)
{
	u1 recvdata_datect = 1;
	if(u1l_uart_rxbuf[0] != 0x11) recvdata_datect = 0;
	else if(u1l_uart_rxbuf[1] != 0x12) recvdata_datect = 0;
	else if(u1l_uart_rxbuf[2] != 0x07) recvdata_datect = 0;
	else if(u1l_uart_rxbuf[4] != 0x00) recvdata_datect = 0;
	else if(u1l_uart_rxbuf[5] != 0x00) recvdata_datect = 0;
	else if(u1l_uart_rxbuf[6] != 0xAA) recvdata_datect = 0;
	
	if(recvdata_datect != 0)
	{
		if(u1l_uart_rxbuf[3] == 0x09)
		{
			flag_test_enable = 1;
			flag_test_once_stop = 1;
		}
		
		R_UART0_Receive(u1l_uart_rxbuf,7);
		uart_send_buf[0] = 0x22;
		uart_send_buf[1] = 0x08;
		switch(u1l_uart_rxbuf[3])
		{
			case UART_TEST_CURR:
				uart_send_buf[2] = UART_TEST_CURR;
				uart_send_buf[3] = 0;
				uart_send_buf[4] = uart_test_curr_value & 0xff;
				uart_send_buf[5] = 0;
				uart_send_buf[6] = 0; 
				uart_send_buf[7] = 0xBB;
				R_UART0_Send(uart_send_buf,8);
				break;
			case UART_TEST_TEMP:
				uart_send_buf[2] = UART_TEST_TEMP;
				uart_send_buf[3] = (uart_test_temp_value >> 8) & 0xff;
				uart_send_buf[4] = (uart_test_temp_value & 0xff);
				uart_send_buf[5] = 0;
				uart_send_buf[6] = 0;
				uart_send_buf[7] = 0xBB;
				R_UART0_Send(uart_send_buf,8);
				break;
			case UART_TEST_VER:
				//P_VER_POWER = 1;
				uart_send_buf[2] = UART_TEST_VER;
				uart_send_buf[3] = (uart_test_ver_value >> 8) & 0xff;
				uart_send_buf[4] = (uart_test_ver_value & 0xff);
				uart_send_buf[5] = 0;
				uart_send_buf[6] = 0;
				uart_send_buf[7] = 0xBB;
				R_UART0_Send(uart_send_buf,8);
				//P_VER_POWER = 0;
				break;
			case UART_TEST_OPEN:
				get_cnt = s2_encoder_cnt; 
				if(get_cnt > 0) get_cnt |= 0x8000;
				else get_cnt = -get_cnt;
				encoder_speed = u2g_d_rpm_current;
				uart_send_buf[2] = UART_TEST_OPEN;
				uart_send_buf[3] = (get_cnt >> 8) & 0xff;
				uart_send_buf[4] = (get_cnt & 0xff);
				uart_send_buf[5] = (encoder_speed >> 8) & 0xff;
				uart_send_buf[6] = (encoder_speed & 0xff);
				uart_send_buf[7] = 0xBB;
				R_UART0_Send(uart_send_buf,8);
				break;
			default:
			break;
		}
	}
}



/**************************************************************************************/
#if TEST_MODE==1
u1 str[24] = {0};
s2 temp_now = 0;
u4 ver_now = 0;
u1 len = 0;
 
void uart_production_test(void)
{
	u1 i = 0;
	switch(uart_test_step)
	{
		case UART_TEST_RESET_ON:
			uart_send_buf[0] = 0x22;
			uart_send_buf[1] = 0x08;
			uart_send_buf[2] = 0x09;
			uart_send_buf[3] = 0x09;
			uart_send_buf[4] = 0x00;
			uart_send_buf[5] = 0x00;
			uart_send_buf[6] = 0x00;
			uart_send_buf[7] = 0xBB;
			time_count++;
			if(time_count>200)
			{
				R_UART0_Receive(uart_recv_buf,7);
				time_count = 0;
				for(i=0;i<24;i++) str[i] = 0;
				sprintf(str,"\nEnter Test Mode OK...");
				R_UART0_Send(str,strlen(str));
				uart_test_step = UART_TEST_IDLE;
				flag_test_encoder = 0;
				flag_test_rotate = 0;
			}
			break;
		case UART_TEST_CURR:
			time_count++;
			if(time_count>50)
			{
				time_count = 0;
				uart_send_buf[2] = UART_TEST_CURR;
				uart_send_buf[3] = 0;
				uart_send_buf[4] = uart_test_curr_value & 0xff;
				uart_send_buf[5] = 0;
				uart_send_buf[6] = 0; 
				uart_send_buf[7] = 0xBB;
				for(i=0;i<8;i++) str[i] = 0;
				sprintf(str,"\nI = %d",uart_test_curr_value);
				R_UART0_Send(str,strlen(str));
				if(flag_test_encoder == 1) uart_test_step = UART_TEST_ENCODER_SPEED_SEND;
				else uart_test_step = UART_TEST_IDLE;
			}
			break;
		case UART_TEST_TEMP:
			time_count++;
			if(time_count>50)
			{
				time_count = 0;
				uart_send_buf[2] = UART_TEST_TEMP;
				uart_send_buf[3] = (uart_test_temp_value >> 8) & 0xff;
				uart_send_buf[4] = (uart_test_temp_value & 0xff);
				uart_send_buf[5] = 0;
				uart_send_buf[6] = 0;
				uart_send_buf[7] = 0xBB;
				
				for(i=0;i<16;i++) str[i] = 0;
				temp_now = (s2)((s4)112 - (s4)((1281 * (s4)uart_test_temp_value) / 10000));
				sprintf(str,"\nT = %d",temp_now);
				R_UART0_Send(str,strlen(str));
				if(flag_test_encoder == 1) uart_test_step = UART_TEST_ENCODER_SPEED_SEND;
				else uart_test_step = UART_TEST_IDLE;
			}
			break;
		case UART_TEST_VER:
			P_VER_POWER = 1;
			time_count++;
			if(time_count>200)
			{
				time_count = 0;
				uart_send_buf[2] = UART_TEST_VER;
				uart_send_buf[3] = (uart_test_ver_value >> 8) & 0xff;
				uart_send_buf[4] = (uart_test_ver_value & 0xff);
				uart_send_buf[5] = 0;
				uart_send_buf[6] = 0;
				uart_send_buf[7] = 0xBB;
				
				ver_now = ((u4)1604 * (u4)uart_test_ver_value + (u4)17) / (u4)10000;
				for(i=0;i<16;i++) str[i] = 0;
				sprintf(str,"\nV = %d v",ver_now);
				R_UART0_Send(str,strlen(str));
				P_VER_POWER = 0;
				if(flag_test_encoder == 1) uart_test_step = UART_TEST_ENCODER_SPEED_SEND;
				else uart_test_step = UART_TEST_IDLE;
			}
			break;
		case UART_TEST_ENCODER_SPEED:
			if(flag_test_rotate == 0)
			{
				flag_test_encoder = 1;
				
				for(i=0;i<24;i++) str[i] = 0;
				sprintf(str,"\nEncoder Testing...");
				R_UART0_Send(str,strlen(str));
				uart_test_step = UART_TEST_ENCODER_SPEED_SEND;
			}
			break;
		case UART_TEST_ENCODER_SPEED_SEND:
			average_speed();
			if(time_run_cnt == TEST_OPEN_TIME)
			{
				if(s2_encoder_cnt > 0) s2_encoder_cnt |= 0x8000;
				else s2_encoder_cnt = -s2_encoder_cnt; 
				uart_send_buf[2] = UART_TEST_ENCODER_SPEED;
				//uart_send_buf[3] = 0;
				//uart_send_buf[4] = uart_test_curr_value & 0xff;
				//uart_send_buf[5] = (uart_test_ver_value >> 8) & 0xff;
				//uart_send_buf[6] = (uart_test_ver_value & 0xff);
				//uart_send_buf[7] = (uart_test_temp_value >> 8) & 0xff;
				//uart_send_buf[8] = (uart_test_temp_value & 0xff);
				uart_send_buf[3] = (s2_encoder_cnt >> 8) & 0xff;
				uart_send_buf[4] = (s2_encoder_cnt & 0xff);
				uart_send_buf[5] = (encoder_speed >> 8) & 0xff;
				uart_send_buf[6] = (encoder_speed & 0xff);
				uart_send_buf[7] = 0xBB;
				
				for(i=0;i<24;i++) str[i] = 0;
				sprintf(str,"\nE = %d;R = %d rpm",s2_encoder_cnt,encoder_speed);
				R_UART0_Send(str,strlen(str));
				time_run_cnt = 0;
				flag_test_encoder = 0;
				s2_encoder_cnt = 0;
				uart_test_step = UART_TEST_IDLE;
			}
			break;
		case UART_TEST_ROTATE:
			if(flag_test_encoder == 0)
			{
				flag_test_rotate = 1;
				uart_send_buf[2] = UART_TEST_ROTATE;
				uart_send_buf[3] = 0x10;
				uart_send_buf[4] = 0;
				uart_send_buf[5] = 0;
				uart_send_buf[6] = 0;
				uart_send_buf[7] = 0xBB;
				
				for(i=0;i<24;i++) str[i] = 0;
				sprintf(str,"\nRotate OK...",s2_encoder_cnt,encoder_speed);
				R_UART0_Send(str,strlen(str));
				uart_test_step = UART_TEST_IDLE;
			}
			else uart_test_step = UART_TEST_ENCODER_SPEED_SEND;
			break;
		case UART_TEST_EXIT:
			if(flag_test_encoder==0 && flag_test_rotate==0)
			{
				flag_test_enable = 0;
				uart_send_buf[0] = 0x22;
				uart_send_buf[1] = 0x08;
				uart_send_buf[2] = 0x0A;
				uart_send_buf[3] = 0x0A;
				uart_send_buf[4] = 0x00;
				uart_send_buf[5] = 0x00;
				uart_send_buf[6] = 0x00;
				uart_send_buf[7] = 0xBB;
				
				for(i=0;i<24;i++) str[i] = 0;
				sprintf(str,"\nExit Test Mode OK...");
				R_UART0_Send(str,strlen(str));
				R_UART0_Receive(u1l_uart_rxbuf, N_UART_BYTE_RX);
				time_count = 0;
				time_run_cnt = 0;
				s2_encoder_cnt = 0;
				flag_test_once_stop = 0;
				uart_test_step = UART_TEST_RESET_ON;
			}
			else if(flag_test_encoder == 1) uart_test_step = UART_TEST_ENCODER_SPEED_SEND;
			else uart_test_step = UART_TEST_IDLE;
			break;
		default:
			time_count = 0;
		break; 
	}
}
#endif
