#ifndef __COMM_UART_H__
#define __COMM_UART_H__

#include "stm32f0xx.h"
#include "Sys.h"

#define UART_ERR_FRAMING	0x04u
#define UART_ERR_PARITY		0x02u
#define UART_ERR_OVERRUN	0x01u

void comm_uart(void);
void i_serial_uart_rx_end(void);
void i_serial_uart_tx_end(void);
void i_serial_uart_rx_error(u1);
void i_serial_uart_rx_over_run(void);

void uart_fact_trq_test(void);	
void uart_fact_elec_test(void);		

#endif
