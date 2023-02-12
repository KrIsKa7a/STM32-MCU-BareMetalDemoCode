#include "stdint.h"
#include "stdio.h"

#include "usart.h"

#include "stm32f7xx.h"

#define GPIOA_EN 		(1U<<0)
#define USART2_EN		(1U<<17)

#define CR1_UE			(1U<<0)
#define CR1_TE			(1U<<3)
#define CR1_RE			(1U<<2)

#define ISR_TXE			(1U<<7)
#define ISR_RXNE		(1U<<5)

#define APB1_CLK		54000000
#define USART_BAUDRATE  115200

static void usartX_set_baudrate(USART_TypeDef* usartX, uint32_t periphClk, uint32_t baudRate);
static uint16_t compute_baudrate(uint32_t periphClk, uint32_t baudRate);

int __io_putchar(int ch) {
	usart2_write(ch);
	return ch;
}

void usart2_rx_tx_init(void) {
	// Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOA_EN;

	// Set PA2 and PA3 to AF07
	GPIOA->MODER &= ~(1U<<4);
	GPIOA->MODER |= (1U<<5);
	GPIOA->MODER &= ~(1U<<6);
	GPIOA->MODER |= (1U<<7);

	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);
	GPIOA->AFR[0] |= (1U<<12);
	GPIOA->AFR[0] |= (1U<<13);
	GPIOA->AFR[0] |= (1U<<14);
	GPIOA->AFR[0] &= ~(1U<<15);

	// Enable clock access to USART2 module
	RCC->APB1ENR |= USART2_EN;

	// Configure USART2 parameters
	usartX_set_baudrate(USART2, APB1_CLK, USART_BAUDRATE);

	USART2->CR1 = (CR1_RE | CR1_TE);
	USART2->CR1 |= CR1_UE;
}

char usart2_read(void) {
	while (!(USART2->ISR & ISR_RXNE)) {

	}

	return USART2->RDR;
}

void usart2_write(int ch) {
	while (!(USART2->ISR & ISR_TXE)) {

	}

	USART2->TDR = (ch & 0xFF);
}

static void usartX_set_baudrate(USART_TypeDef* usartX, uint32_t periphClk, uint32_t baudRate) {
	usartX->BRR = compute_baudrate(periphClk, baudRate);
}

static uint16_t compute_baudrate(uint32_t periphClk, uint32_t baudRate) {
	return (periphClk + (baudRate / 2U)) / baudRate;
}
