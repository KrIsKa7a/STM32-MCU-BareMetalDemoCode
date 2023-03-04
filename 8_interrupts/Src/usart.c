#include "stdint.h"
#include "stm32f7xx.h"
#include "usart.h"

#define GPIOB_EN		(1U<<1)
#define USART3_EN		(1U<<18)

#define USART_CR_UE		(1U<<0)
#define USART_CR_RE		(1U<<2)
#define USART_CR_TE		(1U<<3)
#define USART_CR_RXNEIE	(1U<<5)

#define APB1_CLK		54000000
#define USART3_BR		115200

static void usart_set_baudrate(USART_TypeDef*, uint32_t, uint32_t);
static uint16_t compute_baudrate(uint32_t, uint32_t);

void usart3_rx_tx_init(void) {
	// Enable clock access for GPIOB
	RCC->AHB1ENR |= GPIOB_EN;

	// Set PB10 to AF mode
	GPIOB->MODER &= ~(1U<<20);
	GPIOB->MODER |= (1U<<21);

	// Set PB11 to AF mode
	GPIOB->MODER &= ~(1U<<22);
	GPIOB->MODER |= (1U<<23);

	// Set AF type to AF07
	GPIOB->AFR[1] |= (1U<<8);
	GPIOB->AFR[1] |= (1U<<9);
	GPIOB->AFR[1] |= (1U<<10);
	GPIOB->AFR[1] &= ~(1U<<11);

	GPIOB->AFR[1] |= (1U<<12);
	GPIOB->AFR[1] |= (1U<<13);
	GPIOB->AFR[1] |= (1U<<14);
	GPIOB->AFR[1] &= ~(1U<<15);

	// Enable clock access for USART3 module
	RCC->APB1ENR |= USART3_EN;

	// Set baudrate
	usart_set_baudrate(USART3, APB1_CLK, USART3_BR);

	// Enable interrupts
	USART3->CR1 |= USART_CR_RXNEIE;

	// Register USART interrupts in NVIC
	NVIC_EnableIRQ(USART3_IRQn);

	// Configure transfer direction in USART CR
	USART3->CR1 |= (USART_CR_RE | USART_CR_TE);
	USART3->CR1 |= USART_CR_UE;
}

char usart3_read(void) {
	while (!(USART3->ISR & USART_SR_RXNE)) {

	}

	return USART3->RDR;
}

void usart3_write(int ch) {
	while (!(USART3->ISR & USART_SR_TXE)) {

	}

	USART3->TDR = (ch & 0xFF);
}

static void usart_set_baudrate(USART_TypeDef* USARTx, uint32_t periphClk, uint32_t baudRate) {
	USARTx->BRR = compute_baudrate(periphClk, baudRate);
}

static uint16_t compute_baudrate(uint32_t periphClk, uint32_t baudRate) {
	return ((periphClk + (baudRate / 2U)) / baudRate);
}
