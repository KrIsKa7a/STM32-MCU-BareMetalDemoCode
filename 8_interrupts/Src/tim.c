#include "stm32f7xx.h"
#include "tim.h"

#define TIM2_EN		(1U<<0)
#define TIM2_CEN	(1U<<0)
#define TIM2_CC1IE	(1U<<1)

void tim2_ch1_1hz_interrupt_init(void) {
	RCC->APB1ENR |= TIM2_EN;

	TIM2->PSC = 1600 - 1; //16000000 / 1600 = 10000
	TIM2->ARR = 10000 - 1; //10000 / 10000 = 1

	TIM2->CR1 |= TIM2_CEN;

	TIM2->DIER |= TIM2_CC1IE;

	NVIC_EnableIRQ(TIM2_IRQn);
}
