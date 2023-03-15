#include "stm32f7xx.h"
#include "spi.h"

#define GPIOA_EN		(1U<<0)
#define PIN_CS			(1U<<8)

#define APB2_SPI1EN		(1U<<12)
#define CR1_CPHA		(1U<<0)
#define CR1_CPOL		(1U<<1)
#define CR1_RXONLY		(1U<<10)
#define CR1_LSBFIRST	(1U<<7)
#define CR1_MSTR		(1U<<2)
#define CR1_SPE			(1U<<6)
#define CR2_FRXTH		(1U<<12)
#define SR_TXE			(1U<<1)
#define SR_BSY			(1U<<7)
#define SR_RXNE			(1U<<0)

static void spi1_gpio_init(void);

void spi1_config(void) {
	spi1_gpio_init();

	// Enable clock access for SPI Module
	RCC->APB2ENR |= APB2_SPI1EN;

	// Configure baud rate to fcplk / 4
	SPI1->CR1 |= (1U<<3);
	SPI1->CR1 &= ~(1U<<4);
	SPI1->CR1 &= ~(1U<<5);

	// Set CPOL and CPHA to 1 -> SCK is high in idle stage, data is captured on rising edge
	SPI1->CR1 |= CR1_CPHA;
	SPI1->CR1 |= CR1_CPOL;

	// Select Full-Duplex mode
	SPI1->CR1 &= ~CR1_RXONLY;

	// Select MSB first data format
	SPI1->CR1 &= ~CR1_LSBFIRST;

	// Set Master mode
	SPI1->CR1 |= CR1_MSTR;

	// Set data length to be 8-bit
	SPI1->CR2 |= (1U<<8);
	SPI1->CR2 |= (1U<<9);
	SPI1->CR2 |= (1U<<10);
	SPI1->CR2 &= ~(1U<<11);

	// Generate interrupt flag when FIFO is 8-bit full
	SPI1->CR2 |= CR2_FRXTH;

	// TODO: Enable DMA transfer

	// Enable SPI Module
	SPI1->CR1 |= CR1_SPE;
}

void spi1_transmit(uint8_t* data, uint32_t bytesCnt) {
	uint32_t i = 0;
	uint32_t temp;

	while (i < bytesCnt) {
		// Wait until TXE is set (transmit FIFO is empty)
		while (!(SPI1->SR & SR_TXE)) {

		}

		SPI1->DR = data[i];
		i++;
	}

	// Wait until everything is transmitted
	while (!(SPI1->SR & SR_TXE) || SPI1->SR & SR_BSY) {

	}

	// Clear DR and OVR flag
	temp = SPI1->DR;
	temp = SPI1->SR;
}

void spi1_receive(uint8_t* data, uint32_t bytesCnt) {
	uint32_t i = 0;

	while (i < bytesCnt) {
		// Send dummy data
		SPI1->DR = 0;

		// Wait until data comes into receive FIFO
		while (!(SPI1->SR & SR_RXNE)) {

		}

		*data++ = SPI1->DR;
		i++;
	}
}

void cs_enable(uint8_t pinNumber) {
	if (pinNumber < 31) {
		GPIOA->ODR &= ~(1U<<pinNumber);
	}
}

void cs_disable(uint8_t pinNumber) {
	if (pinNumber < 31) {
		GPIOA->ODR |= (1U<<pinNumber);
	}
}

// Using AF05
// MOSI -> PA7
// MISO -> PA6
// SCK -> PA5
// CS -> PA 8
static void spi1_gpio_init(void) {
	// Enable clock access for GPIOA
	RCC->AHB1ENR |= GPIOA_EN;

	// Configure PA5, PA6, PA7 to AF Mode
	GPIOA->MODER &= ~(1U<<10);
	GPIOA->MODER |= (1U<<11);

	GPIOA->MODER &= ~(1U<<12);
	GPIOA->MODER |= (1U<<13);

	GPIOA->MODER &= ~(1U<<14);
	GPIOA->MODER |= (1U<<15);

	// Set AF05 to PA5, PA6 and PA7
	GPIOA->AFR[0] |= (1U<<20);
	GPIOA->AFR[0] &= ~(1U<<21);
	GPIOA->AFR[0] |= (1U<<22);
	GPIOA->AFR[0] &= ~(1U<<23);

	GPIOA->AFR[0] |= (1U<<24);
	GPIOA->AFR[0] &= ~(1U<<25);
	GPIOA->AFR[0] |= (1U<<26);
	GPIOA->AFR[0] &= ~(1U<<27);

	GPIOA->AFR[0] |= (1U<<28);
	GPIOA->AFR[0] &= ~(1U<<29);
	GPIOA->AFR[0] |= (1U<<30);
	GPIOA->AFR[0] &= ~(1U<<31);

	// Set PA 8 as output
	GPIOA->MODER |= (1U<<16);
	GPIOA->MODER &= ~(1U<<17);

	// Set PA 8 to be high (CS disabled)
	GPIOA->ODR |= PIN_CS;
}
