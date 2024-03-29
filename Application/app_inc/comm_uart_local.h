#ifndef _COMM_UART_LOCAL_INCLUDED
#define _COMM_UART_LOCAL_INCLUDED

#define N_UART_BYTE_TX		7u	
#define N_UART_BYTE_TX_ANS	3u

#define N_UART_BYTE_RX		7u
#define N_UART_BYTE_RX_ANS	41u

/* Tx: ���^�����λ�� */
#define UART_TX_START		0u
#define	UART_TX_L_DATA		1u
#define	UART_TX_SIGNAL_ID	2u
#define	UART_TX_STATE_ID	3u
#define	UART_TX_STATE		4u	
#define	UART_TX_ERROR		5u
#define UART_TX_RESERVE		6u	

#define UART_VALUE_START			0x02u	
#define UART_VALUE_SIGNAL_ID		0x11u	

#define UART_VALUE_TX_L_DATA			0x07u	
#define UART_VALUE_TX_STATE_ID			0x92u	
#define UART_VALUE_TX_FACT_WIRELESS_ID	0x91u	
#define UART_VALUE_TX_FACT_CONNECT_ID	0x93u

#define UART_VALUE_MODE_NORMAL_RK	0x30u	
#define UART_VALUE_MODE_NORMAL_NK	0x40u
#define UART_VALUE_MODE_BEGEN_RK	0x50u
#define UART_VALUE_MODE_BEGEN_NK	0x60u
#define UART_VALUE_MODE_RECOVER_RK	0x70u
#define UART_VALUE_MODE_RECOVER_NK	0x80u

#define UART_VALUE_MODE_NORMAL		UART_VALUE_MODE_NORMAL_RK	
#define UART_VALUE_MODE_BEGEN		UART_VALUE_MODE_BEGEN_RK	
#define UART_VALUE_MODE_RECOVER		UART_VALUE_MODE_RECOVER_RK	

#define UART_VALUE_STATE_UPPER		0x01u	
#define UART_VALUE_STATE_LOWER		0x02u	
#define UART_VALUE_STATE_OPENING	0x03u	
#define UART_VALUE_STATE_CLOSING	0x04u	
#define UART_VALUE_STATE_STOP_MID	0x05u
#define UART_VALUE_STATE_DAYLIGHT	0x06u	

#define UART_VALUE_ERROR_NONE		0x00u	
#define UART_VALUE_ERROR_OVERLOAD	0x04u	
#define UART_VALUE_ERROR_TIMER		0x06u
#define UART_VALUE_ERROR_THERMAL	0x45u
#define UART_VALUE_ERROR_SENS_ELEC	0x46u
#define UART_VALUE_ERROR_SOFT_ROCK	0x47u
#define UART_VALUE_ERROR_SOLENOID	0x48u
#define UART_VALUE_ERROR_HIGH_SPEED	0x49u
#define UART_VALUE_ERROR_ENCODER	0x4au
#define UART_VALUE_ERROR_FET		0x4bu
#define UART_VALUE_ERROR_POWER		0x4cu
#define UART_VALUE_ERROR_TEMP		0x4du

#define UART_VALUE_RESERVE			0x00u
#define UART_VALUE_NO_CHANGE		0xfeu
#define UART_VALUE_UNEXPECT			0xffu

#define UART_VALUE_FACT_SW_OPEN		0x01u
#define UART_VALUE_FACT_SW_STOP		0x02u
#define UART_VALUE_FACT_SW_CLOSE	0x04u
#define UART_VALUE_FACT_BUZZ_1		0xfau
#define UART_VALUE_FACT_BUZZ_2		0xfbu
#define UART_VALUE_FACT_BUZZ_3		0xfcu

#define UART_TXANS_START		0u
#define	UART_TXANS_L_DATA		1u
#define	UART_TXANS_SIGNAL_ID	2u

#define UART_VALUE_ANS_TX_START		0x02u
#define UART_VALUE_ANS_TX_L_DATA	0x03u
#define UART_VALUE_ANS_TX_ACK		0x00u
#define UART_VALUE_ANS_TX_NACK		0x01u
#define UART_VALUE_ANS_TX_SW_OPEN	0xa1u
#define UART_VALUE_ANS_TX_SW_STOP	0xa2u
#define UART_VALUE_ANS_TX_SW_CLOSE	0xa4u

#define UART_LIMIT_RETRY_TX			1u

#define UART_RX_START		0u	
#define	UART_RX_L_DATA		1u	
#define	UART_RX_SIGNAL_ID	2u	
#define	UART_RX_ERROR_ID	3u
#define	UART_RX_SW			4u
#define	UART_RX_ERROR_1		5u
#define	UART_RX_ERROR_2		6u

#define UART_VALUE_RX_L_DATA		0x07u	
#define UART_VALUE_RX_HISTRY_ID		0x98u
#define UART_VALUE_RX_HISTRY_SW		0x09u
#define UART_VALUE_RX_HISTRY_ERR1	0x52u
#define UART_VALUE_RX_HISTRY_ERR2	0x46u

#define UART_RXANS_START			0u	
#define	UART_RXANS_L_DATA			1u
#define	UART_RXANS_SIGNAL_ID		2u
#define	UART_RXANS_ERROR_ID			3u
#define	UART_RXANS_NUM_OPEN_CLOSE1	4u
#define	UART_RXANS_NUM_OPEN_CLOSE2	5u
#define	UART_RXANS_NUM_MOVE1		6u
#define	UART_RXANS_NUM_MOVE2		7u
#define	UART_RXANS_OVERLOAD			8u
#define	UART_RXANS_SIZE_H1			9u
#define	UART_RXANS_SIZE_H2			10u
#define	UART_RXANS_ERR_RECORD_1		11u
#define	UART_RXANS_ERR_RECORD_2		14u
#define	UART_RXANS_ERR_RECORD_3		17u
#define	UART_RXANS_ERR_RECORD_4		20u
#define	UART_RXANS_ERR_RECORD_5		23u
#define	UART_RXANS_ERR_RECORD_6		26u
#define	UART_RXANS_ERR_RECORD_7		29u
#define	UART_RXANS_ERR_RECORD_8		32u	
#define	UART_RXANS_ERR_RECORD_9		35u
#define	UART_RXANS_ERR_RECORD_10	38u

#define UAER_RXANS_SIZE_RECORD		3	

#define UART_SHIFTDOWN_1BYTE		8

#define UART_VALUE_ANS_RX_L_DATA	0x0bu	
#define UART_VALUE_ANS_RX_ERR_DATA	0x03u
#define UART_VALUE_ANS_RX_ERR_ID	0x98u

#define N_CURRENT_MODE			200u
#define N_ERR					19u	
#define CNT_UART_TRNS_FOR_A_KEY	5u	
#define UART_STATE_ROCK_CLOSE_ON	169
#define UART_STATE_ROCK_CLOSE_OFF	170
#define UART_STATE_ROCK_CANCEL		171
#define UART_STATE_ROCK_OVERLOAD	172

#define T4_5MS_LIMIT_WAIT_ANS				45u
#define T4_5MS_AFTER_ERROR					332u
#define T4_5MS_FACT_INTERVAL				45u
#define T4_5MS_FACT_CHECK_CONNECT			111u
#define T4_5MS_FACT_CHECK_CONNECT_OFF		355u
#define T4_5MS_FACT_INTERVAL_AFTER_RESET	111u
#define T4_5MS_FACT_CHECK_RESET				56u
#define T4_5MS_RESET_MODULE					223u
#define T4_5MS_WAIT_START_UART				223u

typedef enum {
	UART_ERR_NONE,			
	UART_ERR_WAIT_KEY,	
	UART_ERR_CNT_AFTER_ERR	
} uart_error_tx;	

typedef enum {
	UART_NO_ERR_UNEXPECT1,	
	UART_NO_ERR_OVERLOAD_DOWN,
	UART_NO_ERR_SENS_ELEC,	
	UART_NO_ERR_POWER_ON,	
	UART_NO_ERR_HIGH_SPEED,		
	UART_NO_ERR_CNT_PLS,	
	UART_NO_ERR_THERMAL,	
	UART_NO_ERR_SOFT_RISET,	
	UART_NO_ERR_VOLT_POWER,	
	UART_NO_ERR_OVERLOAD_UP,
	UART_NO_ERR_TIMER,		
	UART_NO_ERR_ENCODER,	
	UART_NO_ERR_SOFT_ROCK,	
	UART_NO_ERR_H_SIZE,		
	UART_NO_ERR_SOLENOID,	
	UART_NO_ERR_KULUTCH_REL,
	UART_NO_ERR_UNEXPECT2,	
	UART_NO_ERROR_OUT_CTRL	
} uart_error_no;

#define N_UART_ERR_NO_STORAGE	18	

typedef enum {
	UART_PH_RESET_ON,				
	UART_PH_WAIT_START,				
	UART_PH_INITIAL,				
	UART_PH_IDLE,					
	UART_PH_TX_START,			
	UART_PH_TX,					
	UART_PH_TX_ANS_WAIT,			
	UART_PH_TX_ANS,					
	UART_PH_RX_ANS,					
	UART_PH_RX_ANS_END,				
	UART_PH_TX_BUZZER_START,		
	UART_PH_TX_BUZZER,				
	UART_PH_TX_BUZZER_ANS_WAIT,		
	UART_PH_TX_BUZZER_ANS,				
	
	UART_PH_FACT_REQ_OPEN,				
	UART_PH_FACT_REQ_OPEN_END,		
	UART_PH_FACT_WAIT_ANS_OPEN,			
	UART_PH_FACT_REQ_STOP,				
	UART_PH_FACT_REQ_STOP_END,			
	UART_PH_FACT_WAIT_ANS_STOP,			
	UART_PH_FACT_REQ_CLOSE,				
	UART_PH_FACT_REQ_CLOSE_END,		
	UART_PH_FACT_WAIT_ANS_CLOSE,		
	UART_PH_FACT_REQ_RESET,				
	UART_PH_FACT_INTERVAL_AFTER_RESET,	
	UART_PH_FACT_REQ_OPEN_AFTER_RESET,
	UART_PH_FACT_REQ_OPEN_END_AFTER_RESET,	
	UART_PH_FACT_CHECK_RESET,		
	UART_PH_FACT_RESET_OK,				
	UART_PH_FACT_REQ_MDL,				
	UART_PH_FACT_REQ_MDL_END,	
	UART_PH_FACT_ANS_WAIT,		
	UART_PH_FACT_ANS,			
	UART_PH_FACT_WAIT_MODEL,	
	UART_PH_FACT_FINISH,		
	UART_PH_FACT_ERROR			
} uart_ph;

#define	UART_START_FACT_PHASE	UART_PH_FACT_REQ_OPEN

typedef struct {
	bool tx;	
	bool tx_end;	
	bool ans_rcv;	
	bool rx;		
	bool rx_end;	
} uart_ev;

/* The following is the production test software program */
/* 2021.02.02 */
typedef enum{
	UART_TEST_RESET_ON,
	UART_TEST_CURR,
	UART_TEST_VER,
	UART_TEST_TEMP,
	UART_TEST_OPEN,
	UART_TEST_ROTATE,
	UART_TEST_CLOSE,
	UART_TEST_ENCODER_SPEED_SEND,	
	UART_TEST_EXIT = 10,
	UART_TEST_IDLE
}uart_test_enum;

#define TEST_MODE 0

#endif
