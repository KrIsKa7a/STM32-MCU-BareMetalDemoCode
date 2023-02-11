//ULD3 is on PB14
//B1 is on PC13
#include "stm32f7xx.h"

#define GPIOB_EN  (1U<<1)
#define GPIOC_EN  (1U<<2)

#define PIN13	  (1U<<13)
#define PIN14	  (1U<<14)

#define LED_PIN   PIN14
#define BTN_PIN   PIN13

int main(void) {
	RCC->AHB1ENR |= GPIOB_EN;
	RCC->AHB1ENR |= GPIOC_EN;

	GPIOB->MODER |= (1U<<28);
	GPIOB->MODER &= ~(1U<<29);
	GPIOC->MODER &= ~(1U<<26);
	GPIOC->MODER &= ~(1U<<27);

	while(1) {
		if (GPIOC->IDR & BTN_PIN) {
			// Button is released because it has low active value
			GPIOB->BSRR |= (1U<<30);
		} else {
			GPIOB->BSRR |= LED_PIN;
		}
	}
}
