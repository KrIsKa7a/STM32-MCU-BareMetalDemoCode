#ifndef USART_H_
#define USART_H_

#define USART_SR_RXNE	(1U<<5)
#define USART_SR_TXE	(1U<<7)

void usart3_rx_tx_init(void);
char usart3_read_data(void);
void usart3_write(int);

#endif
