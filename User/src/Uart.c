#include "Uart.h"

volatile uint8_t * gp_uart0_tx_address = 0;        /* uart0 transmit buffer address */
volatile uint16_t  g_uart0_tx_count = 0;           /* uart0 transmit data number */
volatile uint8_t * gp_uart0_rx_address = 0;        /* uart0 receive buffer address */
volatile uint16_t  g_uart0_rx_count = 0;;           /* uart0 receive data number */
volatile uint16_t  g_uart0_rx_length = 0;
u1 Rx_Buff[10] = {0};
u1 Tx_Buff[10] = {1,2,3,4,5};

//PA9 -> USART1_TX; PA10 -> USART1_RX
void Init_Uart1(u4 BaudRate)
{
    GPIO_InitTypeDef    GPIO_InitStructure;
    NVIC_InitTypeDef    NVIC_InitStruct;
    USART_InitTypeDef   USART1_InitStruct;
  
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART1_InitStruct.USART_BaudRate = BaudRate;
    USART1_InitStruct.USART_WordLength = USART_WordLength_9b;   //8bit data,1bit Parity
    USART1_InitStruct.USART_StopBits = USART_StopBits_1;
    USART1_InitStruct.USART_Parity = USART_Parity_Odd;
    USART1_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART1_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART1,&USART1_InitStruct);
    
    NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
    
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//USART1->CR1 |= 0x20;| USART_IT_TXE | USART_IT_TC
    USART_ClearFlag(USART1,USART_IT_TC | USART_IT_ORE);

    USART_Cmd(USART1,ENABLE);
}
//USART_ClearFlag
void USART1_IRQHandler(void)
{
    volatile uint8_t rx_data;
//    if((USART1->ISR & USART_ISR_TXE) == USART_ISR_TXE)  //发送数据寄存器为空
//    {
//        if (g_uart0_tx_count > 0U)
//        {
//            USART1->TDR = *gp_uart0_tx_address;
//            gp_uart0_tx_address++;
//            g_uart0_tx_count--;
//        }
//    }

    if((USART1->ISR & USART_ISR_RXNE) == USART_ISR_RXNE)
    {
        rx_data = (u1)(USART1->RDR);/* Receive data, clear flag */
        USART_ClearITPendingBit(USART1,USART_IT_ORE);
        if (g_uart0_rx_length > g_uart0_rx_count)
        {
            *gp_uart0_rx_address = rx_data;
            gp_uart0_rx_address++;
            g_uart0_rx_count++;

            if (g_uart0_rx_length == g_uart0_rx_count)
            {
                i_serial_uart_rx_end();
            }
        }   
    }
    if((USART1->ISR & USART_ISR_TC) == USART_ISR_TC)
    {
        USART1->ICR |= USART_ICR_TCCF; /* Clear transfer complete flag */
        USART_ITConfig(USART1,USART_IT_TC,DISABLE);
        i_serial_uart_tx_end();
    }
}



//void i_serial_uart_tx_end(void)
//{
//    USART_ITConfig(USART1,USART_IT_TC,DISABLE);
//}

//void i_serial_uart_rx_end(void)
//{
//    R_UART0_Receive(Rx_Buff,7);
//    R_UART0_Send(Rx_Buff,7);
//}

void R_UART0_Receive(uint8_t * const rx_buf, uint16_t rx_num)
{
    g_uart0_rx_count = 0U;
    g_uart0_rx_length = rx_num;
    gp_uart0_rx_address = rx_buf;
}

void R_UART0_Send(uint8_t * const tx_buf, uint16_t tx_num)
{
    u1 i = 0;
    //gp_uart0_tx_address = tx_buf;
    //g_uart0_tx_count = tx_num;
    for(i=0; i<tx_num; i++)
    {
        //USART1->TDR = *gp_uart0_tx_address;
        while((USART1->ISR & USART_ISR_TXE) != USART_ISR_TXE)
        {
            ;
        }
        USART1->TDR = tx_buf[i];
        //gp_uart0_tx_address++;
        //g_uart0_tx_count--;
    }
    USART_ITConfig(USART1,USART_IT_TC,ENABLE);
}
