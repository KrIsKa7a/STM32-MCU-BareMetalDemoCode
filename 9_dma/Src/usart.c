#include "stm32f7xx.h"
#include "usart.h"

#define GPIOB_EN			(1U<<1)

#define USART3_EN			(1U<<18)
#define USART_UE			(1U<<0)
#define USART_TE			(1U<<3)
#define USART_TXE			(1U<<7)
#define USART_DMAT			(1U<<7)

#define APB1_CLK			16000000
#define USART3_BAUDRATE		115200

#define DMA1_EN				(1U<<21)
#define DMA_STRx_EN			(1U<<0)
#define DMA_CH4_SEL			(1U<<27)
#define DMA_MINC			(1U<<10)
#define DMA_MEM_TO_PERIPH	(1U<<6)
#define DMA_TCIE			(1U<<4)
#define DMA_DMDIS			(1U<<2)

static void usart_set_baudrate(USART_TypeDef* USARTx, uint32_t periphClk, uint32_t baudRate);
static uint16_t compute_baudrate(uint32_t periphClk, uint32_t baudRate);

int __io_putchar(char ch) {
	usart3_write(ch);

	return ch;
}

void usart3_tx_init() {
	RCC->AHB1ENR |= GPIOB_EN;

	GPIOB->MODER &= ~(1U<<20);
	GPIOB->MODER |= (1U<<21);

	GPIOB->AFR[1] |= (1U<<8);
	GPIOB->AFR[1] |= (1U<<9);
	GPIOB->AFR[1] |= (1U<<10);
	GPIOB->AFR[1] &= ~(1U<<11);

	RCC->APB1ENR |= USART3_EN;

	usart_set_baudrate(USART3, APB1_CLK, USART3_BAUDRATE);

	USART3->CR1 |= USART_TE;
	USART3->CR1 |= USART_UE;
}

void usart3_write(int ch) {
	while (!(USART3->ISR & USART_TXE)) {

	}

	USART3->TDR = (ch & 0xff);
}

void dma1_stream3_ch4_init(uint32_t src, uint32_t dest, uint32_t len) {
	// Enable DMA1 clock
	RCC->AHB1ENR |= DMA1_EN;

	// Disable DMA1 Stream 3
	DMA1_Stream3->CR &= ~DMA_STRx_EN;

	// Wait until DMA1 Stream 3 is disabled
	while (DMA1_Stream3->CR & DMA_STRx_EN) {

	}

	// Clear all interrupt flags for DMA1 Stream 3
	DMA1->LIFCR |= (1U<<22);
	DMA1->LIFCR |= (1U<<24);
	DMA1->LIFCR |= (1U<<25);
	DMA1->LIFCR |= (1U<<26);
	DMA1->LIFCR |= (1U<<27);

	// Set the destination buffer
	DMA1_Stream3->PAR = dest;

	// Set the source buffer
	DMA1_Stream3->M0AR = src;

	// Set length
	DMA1_Stream3->NDTR = len;

	// Select Stream 3 CH4
	DMA1_Stream3->CR |= DMA_CH4_SEL;

	// Enable memory increment
	DMA1_Stream3->CR |= DMA_MINC;

	// Configure transfer direction
	DMA1_Stream3->CR |= DMA_MEM_TO_PERIPH;

	// Enable complete transfer interrupt
	DMA1_Stream3->CR |= DMA_TCIE;

	// Enable direct mode and disable FIFO
	DMA1_Stream3->FCR &= ~DMA_DMDIS;

	// Enable back DMA1 Stream 3
	DMA1_Stream3->CR |= DMA_STRx_EN;

	// Enable USART3 Transmitter DMA
	USART3->CR3 |= USART_DMAT;

	// DMA1 Stream 3 Interrupt register
	NVIC_EnableIRQ(DMA1_Stream3_IRQn);
}

static void usart_set_baudrate(USART_TypeDef* USARTx, uint32_t periphClk, uint32_t baudRate) {
	USARTx->BRR = compute_baudrate(periphClk, baudRate);
}

static uint16_t compute_baudrate(uint32_t periphClk, uint32_t baudRate) {
	return (periphClk + (baudRate / 2U)) / baudRate;
}
