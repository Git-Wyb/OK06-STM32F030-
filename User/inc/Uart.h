#ifndef __UART_H__
#define __UART_H__

#include "stm32f0xx.h"
#include "Sys.h"


//extern u1 Rx_Buff[10];
//extern u1 Tx_Buff[10];

void i_serial_uart_tx_end(void);
void i_serial_uart_rx_end(void);
void R_UART0_Send(uint8_t * const tx_buf, uint16_t tx_num);
void R_UART0_Receive(uint8_t * const rx_buf, uint16_t rx_num);
void Init_Uart1(u4 BaudRate);

#endif
