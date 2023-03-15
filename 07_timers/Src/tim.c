#include "stm32f7xx.h"

#include "tim.h"

#define GPIOA_EN			(1U<<0)

#define TIM2_EN				(1U<<0)
#define CR1_CEN				(1U<<0)

#define CCMR_CC3S			(1U<<0)
#define CCER_CC3E			(1U<<8)
#define OC2_TOGGLE_MODE		((1U<<12) | (1U<<13))
#define CCER_CC2E			(1U<<4)

void tim2_1hz_init(void) {
	// Enable clock access for tim2 module
	RCC->APB1ENR |= TIM2_EN;

	// Set Prescaler
	TIM2->PSC = 1600 - 1; //16 000 000 / 1600 = 10 000

	// Set auto-load value
	TIM2->ARR = 10000 - 1; // 10000 / 10000 = 1

	// Clear the current value
	TIM2->CNT = 0;

	// Enable the timer
	TIM2->CR1 |= CR1_CEN;
}

void tim2_input_capture_ch3(void) {
	// Enable TIM2 clock access and for GPIOA
	RCC->APB1ENR |= TIM2_EN;
	RCC->AHB1ENR |= GPIOA_EN;

	// Set PA2 to alternate function mode
	GPIOA->MODER &= ~(1U<<4);
	GPIOA->MODER |= (1U<<5);

	// Set the alternate function AF1
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] &= ~(1U<<9);
	GPIOA->AFR[0] &= ~(1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);

	// Set Prescaler
	TIM2->PSC = 1600 - 1;

	// Set ARR value
	TIM2->ARR = 10000 - 1;

	// Set TIM2CH3 as input capture mode
	TIM2->CCMR2 |= CCMR_CC3S;

	// Configure CH3 to detect rising edges of the signal
	// To detect rising edges CC3P must have value of 00
	TIM2->CCER |= CCER_CC3E;

	// Clear the current value
	TIM2->CNT = 0;

	// Timer clock enable
	TIM2->CR1 |= CR1_CEN;
}

void tim2_output_compare_ch2(void) {
	// We will use PA1 alternate function AF1 (TIM2_CH2)
	RCC->APB1ENR |= TIM2_EN;
	RCC->AHB1ENR |= GPIOA_EN;

	// Set PA1 to alternate function mode
	GPIOA->MODER &= ~(1U<<2);
	GPIOA->MODER |= (1U<<3);

	// Set alternate function to be AF1
	GPIOA->AFR[0] |= (1U<<4);
	GPIOA->AFR[0] &= ~(1U<<5);
	GPIOA->AFR[0] &= ~(1U<<6);
	GPIOA->AFR[0] &= ~(1U<<7);

	TIM2->PSC = 1600 - 1;

	TIM2->ARR = 10000 - 1;

	// Set output compare toggle mode -> OC2M -> 0011
	TIM2->CCMR1 |= OC2_TOGGLE_MODE;

	// Enable TIM2CH2 in output compare mode
	TIM2->CCER |= CCER_CC2E;

	TIM2->CNT = 0;

	TIM2->CR1 |= CR1_CEN;
}
