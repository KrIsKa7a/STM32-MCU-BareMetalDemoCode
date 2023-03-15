#include "stm32f7xx.h"
#include "i2c.h"

#define GPIOB_EN			(1U<<1)
#define GPIOx_PIN6			(1U<<6)
#define GPIOx_PIN7			(1U<<7)

#define I2C1_EN				(1U<<21)
#define I2Cx_CR1_PE			(1U<<0)
#define I2Cx_CR1_ANFOFF		(1U<<12)
#define I2Cx_CR2_ADD10		(1U<<11)
#define I2Cx_CR2_RD_WRN		(1U<<10)
#define I2Cx_CR2_START		(1U<<13)
#define I2Cx_CR2_AUTOEND	(1U<<25)
#define I2Cx_ISR_ADDR		(1U<<3)
#define I2Cx_ISR_TXIS		(1U<<1)
#define I2Cx_ISR_TC			(1U<<6)
#define I2Cx_ICR_ADDRCF		(1U<<3)
#define I2Cx_ISR_RXNE		(1U<<2)
#define I2Cx_CR2_STOP		(1U<<14)

static void GPIOB_set_AF4_pin_6_7(void);
static void I2C1_set_timings_sm_100kHz(void);

// SCL -> PB6
// SDA -> PB7
void I2C1_init(void) {
	// Enable clock access for GPIOB
	RCC->AHB1ENR |= GPIOB_EN;

	// Set MODE for PB6 and PB7 to AF
	GPIOB->MODER &= ~(1U<<12);
	GPIOB->MODER |= (1U<<13);

	GPIOB->MODER &= ~(1U<<14);
	GPIOB->MODER |= (1U<<15);

	// Set PB6 and PB7 output type to Open-Drain
	GPIOB->OTYPER |= GPIOx_PIN6;
	GPIOB->OTYPER |= GPIOx_PIN7;

	// Enable pull-up resistors for PB6 and PB7
	GPIOB->PUPDR |= (1U<<12);
	GPIOB->PUPDR &= ~(1U<<13);

	GPIOB->PUPDR |= (1U<<14);
	GPIOB->PUPDR &= ~(1U<<15);

	// Set the AF type in AFR to AF4
	GPIOB_set_AF4_pin_6_7();

	// Enable clock access for I2C1
	RCC->APB1ENR |= I2C1_EN;

	// Enter reset mode
	I2C1->CR1 &= ~I2Cx_CR1_PE;

	// Wait for software reset to be performed
	while (I2C1->CR1 & I2Cx_CR1_PE) {

	}

	// Configure analog filter
	I2C1->CR1 &= ~I2Cx_CR1_ANFOFF;

	// Set peripheral clock frequency to 16 MHz and Standard Mode 100 kHz
	I2C1_set_timings_sm_100kHz();

	// Enable I2C1 module
	I2C1->CR1 |= I2Cx_CR1_PE;
}

void I2C1_burst_read(char sAddr, char mAddr, int len, char* data) {
	// Set the master to operate in 7-bit addressing mode
	I2C1->CR2 &= ~I2Cx_CR2_ADD10;

	// Set number of bytes to be written = 1
	I2C1->CR2 |= (1U<<16);
	I2C1->CR2 &= ~(1U<<17);
	I2C1->CR2 &= ~(1U<<18);
	I2C1->CR2 &= ~(1U<<19);
	I2C1->CR2 &= ~(1U<<20);
	I2C1->CR2 &= ~(1U<<21);
	I2C1->CR2 &= ~(1U<<22);
	I2C1->CR2 &= ~(1U<<23);

	// Set the slave address
	I2C1->CR2 |= sAddr << 1;

	// Set direction to write
	I2C1->CR2 &= ~I2Cx_CR2_RD_WRN;

	// Set AUTOEND when bytes are transferred
	//I2C1->CR2 |= I2Cx_CR2_AUTOEND;

	// Generate START
	I2C1->CR2 |= I2Cx_CR2_START;

	// Wait until the slave address is registered
	while (!(I2C1->ISR & I2Cx_ISR_ADDR)) {

	}

	// Clear address flag in SR
	I2C1->ICR |= I2Cx_ICR_ADDRCF;

	// Wait until transmit register is empty
	while (!(I2C1->ISR & I2Cx_ISR_TXIS)) {

	}

	// Transmit the register address in slave
	I2C1->TXDR = mAddr;

	// Wait until transfer is complete
	while (!(I2C1->ISR & I2Cx_ISR_TC)) {

	}

	// Set number of bytes to be read = len
	I2C1->CR2 |= (len << 16);

	// Set the slave address
	I2C1->CR2 |= sAddr << 1;

	// Set direction to read
	I2C1->CR2 |= I2Cx_CR2_RD_WRN;

	// Generate restart
	I2C1->CR2 |= I2Cx_CR2_START;

	// Wait until slave address is registered
	while (!(I2C1->ISR & I2Cx_ISR_ADDR)) {

	}

	// Clear address flag in SR
	I2C1->ICR |= I2Cx_ICR_ADDRCF;

	// Wait until transfer is completed
	while (!(I2C1->ISR & I2Cx_ISR_TC)) {
		while (!(I2C1->ISR & I2Cx_ISR_RXNE)) {

		}

		*data++ = I2C1->RXDR;
	}

	I2C1->CR2 |= I2Cx_CR2_STOP;
}

void I2C1_burst_write(char sAddr, char mAddr, int len, char* data) {
	// Set the master to operate in 7-bit addressing mode
	I2C1->CR2 &= ~I2Cx_CR2_ADD10;

	// Set number of bytes to be written = len
	I2C1->CR2 |= ((len + 1) << 16);

	// Set the slave address
	I2C1->CR2 |= sAddr << 1;

	// Set direction to write
	I2C1->CR2 &= ~I2Cx_CR2_RD_WRN;

	// Set AUTOEND when bytes are transferred
	//I2C1->CR2 |= I2Cx_CR2_AUTOEND;

	// Generate START
	I2C1->CR2 |= I2Cx_CR2_START;

	// Wait until slave address is registered
	while (!(I2C1->ISR & I2Cx_ISR_ADDR)) {

	}

	// Clear address flag in SR
	I2C1->ICR |= I2Cx_ICR_ADDRCF;

	// Wait for transmit register to be empty
	while (!(I2C1->ISR & I2Cx_ISR_TXIS)) {

	}

	// Transfer register address in slave
	I2C1->TXDR = mAddr;

	// Wait until transfer is complete
	while (!(I2C1->ISR & I2Cx_ISR_TC)) {
		while (!(I2C1->ISR & I2Cx_ISR_TXIS)) {

		}

		I2C1->TXDR = *data++;
	}

	I2C1->CR2 |= I2Cx_CR2_STOP;
}

static void GPIOB_set_AF4_pin_6_7(void) {
	GPIOB->AFR[0] &= ~(1U<<24);
	GPIOB->AFR[0] &= ~(1U<<25);
	GPIOB->AFR[0] |= (1U<<26);
	GPIOB->AFR[0] &= ~(1U<<27);

	GPIOB->AFR[0] &= ~(1U<<28);
	GPIOB->AFR[0] &= ~(1U<<29);
	GPIOB->AFR[0] |= (1U<<30);
	GPIOB->AFR[0] &= ~(1U<<31);
}

static void I2C1_set_timings_sm_100kHz(void) {
	// Set Prescaler to 3
	I2C1->TIMINGR |= (1U<<28);
	I2C1->TIMINGR |= (1U<<29);
	I2C1->TIMINGR &= ~(1U<<30);
	I2C1->TIMINGR &= ~(1U<<31);

	// Set SDADEL to 2
	I2C1->TIMINGR &= ~(1U<<16);
	I2C1->TIMINGR |= (1U<<17);
	I2C1->TIMINGR &= ~(1U<<18);
	I2C1->TIMINGR &= ~(1U<<19);

	// Set SCLDEL to 4
	I2C1->TIMINGR &= ~(1U<<20);
	I2C1->TIMINGR &= ~(1U<<21);
	I2C1->TIMINGR |= (1U<<22);
	I2C1->TIMINGR &= ~(1U<<23);

	// Set SCLH to 15
	I2C1->TIMINGR |= (1U<<8);
	I2C1->TIMINGR |= (1U<<9);
	I2C1->TIMINGR |= (1U<<10);
	I2C1->TIMINGR |= (1U<<11);
	I2C1->TIMINGR &= ~(1U<<12);
	I2C1->TIMINGR &= ~(1U<<13);
	I2C1->TIMINGR &= ~(1U<<14);
	I2C1->TIMINGR &= ~(1U<<15);

	// Set SCLL to 19
	I2C1->TIMINGR |= (1U<<0);
	I2C1->TIMINGR |= (1U<<1);
	I2C1->TIMINGR &= ~(1U<<2);
	I2C1->TIMINGR &= ~(1U<<3);
	I2C1->TIMINGR |= (1U<<4);
	I2C1->TIMINGR &= ~(1U<<5);
	I2C1->TIMINGR &= ~(1U<<6);
	I2C1->TIMINGR &= ~(1U<<7);
}
