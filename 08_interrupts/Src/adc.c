#include "stm32f7xx.h"

#include "adc.h"

#define GPIOA_EN	(1U<<0)
#define PIN1_AM		((1U<<2) | (1U<<3))

#define ADC1_EN		(1U<<8)
#define ADC_EOCIE	(1U<<5)
#define ADC_CH1		(1U<<0)
#define ADC_ADON	(1U<<0)
#define ADC_CONT	(1U<<1)
#define ADC_SWSTART	(1U<<30)

void pa1_adc1_interrupt_init() {
	// Enable clock access for GPIOA
	RCC->AHB1ENR |= GPIOA_EN;

	GPIOA->MODER |= PIN1_AM;

	RCC->APB2ENR |= ADC1_EN;

	// Enable interrupt on EOC
	ADC1->CR1 |= ADC_EOCIE;
	NVIC_EnableIRQ(ADC_IRQn);

	ADC1->SQR3 |= ADC_CH1;
	ADC1->SQR1 = 0x00;

	ADC1->CR2 |= ADC_ADON;
}

void start_conversion() {
	ADC1->CR2 |= ADC_CONT;
	ADC1->CR2 |= ADC_SWSTART;
}

uint16_t adc_read_value() {
	while(!(ADC1->SR & ADC_EOC)) {

	}

	return ADC1->DR & 0xFF;
}
