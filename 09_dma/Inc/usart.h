#ifndef USART_H_
#define USART_H_

#include "stdint.h"

#define DMA_TCIF3	(1U<<27)
#define DMA_CTCIF3 	(1U<<27)

void usart3_tx_init();
void usart3_write(int ch);

void dma1_stream3_ch4_init(uint32_t src, uint32_t dest, uint32_t len);

#endif /* USART_H_ */
