#include "usart.h"
#include "stdio.h"
#include "stdint.h"

#define GPIOA_EN    	(1U<<0)
#define USART2_EN   	(1U<<17)

#define CR1_UE		(1U<<0)
#define CR1_TE		(1U<<3)
#define ISR_TXE		(1U<<7)

#define APB1_CLK    	54000000

#define USART_BAUDRATE  115200

static uint16_t compute_baudrate(uint32_t periphClk, uint32_t baudRate);
static void usart_set_baudrate(USART_TypeDef* USARTx, uint32_t periphClk, uint32_t baudRate);

int __io_putchar(int ch) {
	usart2_write(ch);
	return ch;
}

void usart2_tx_init(void) {
	// Enable clock access for GPIOA
	RCC->AHB1ENR |= GPIOA_EN;

	// Set PA2 as alternate function mode
	GPIOA->MODER &= ~(1U<<4);
	GPIOA->MODER |= (1U<<5);

	// Set the type of the alternate function
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);

	// Enable clock access for USART2
	RCC->APB1ENR |= USART2_EN;

	// Configure Baudrate
	usart_set_baudrate(USART2, APB1_CLK, USART_BAUDRATE);

	// Configure transfer direction
	USART2->CR1 = CR1_TE;
	USART2->CR1 |= CR1_UE;
}

void usart2_write(int ch) {
	// Waiting for the data to be fully transmitted to the shift register
	while (!(USART2->ISR & ISR_TXE)) {

	}

	// Conversion to 8-bit using 0xFF
	USART2->TDR = (ch & 0xFF);
}

static void usart_set_baudrate(USART_TypeDef* USARTx, uint32_t periphClk, uint32_t baudRate) {
	USARTx->BRR = compute_baudrate(periphClk, baudRate);
}

static uint16_t compute_baudrate(uint32_t periphClk, uint32_t baudRate) {
	return (periphClk + (baudRate / 2U)) / baudRate;
}
