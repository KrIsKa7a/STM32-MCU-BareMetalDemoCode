#include "adc.h"

#include "stm32f7xx.h"

#define GPIOA_EN			(1U<<0)
#define ADC_EN				(1U<<8)

#define ADC_CH1				(1U<<0)
#define ADC_SEQ_LEN			0x00
#define ADC_CR2_ADON		(1U<<0)
#define ADC_CR1_DISCEN		(1U<<11)
#define ADC_CR2_SWSTART 	(1U<<30)
#define ADC_SR_EOC			(1U<<1)

void pa1_adc1_init() {
	// Enable clock access for GPIOA
	RCC->AHB1ENR |= GPIOA_EN;

	// Set PA1 as analog mode
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);

	// Enable clock access for ADC1 Module
	RCC->APB2ENR |= ADC_EN;

	// Configure ADC1 Module parameters
	// Conversion sequence start
	ADC1->SQR3 = ADC_CH1;

	// Conversion sequence length
	ADC1->SQR1 = ADC_SEQ_LEN;

	// Enable ADC Module
	ADC1->CR2 |= ADC_CR2_ADON;
}

void start_conversion() {
	// Uncomment the following line if we want discontinious conversion (single conversion)
	//ADC1->CR2 |= ADC1_CR1_DISCEN;
	ADC1->CR2 |= ADC_CR2_SWSTART;
}

uint16_t adc_read_value() {
	while(!(ADC1->SR & ADC_SR_EOC)) {

	}

	return (ADC1->DR & 0xFF);
}
