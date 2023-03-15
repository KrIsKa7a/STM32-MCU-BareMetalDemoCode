// ULD3 is on PB14
#include "stm32f7xx.h"

#define GPIOB_EN    (1U<<1)

#define PIN14       (1U<<14)
#define LED_PIN 	PIN14

int main(void) {
	//Enable clock for AHB1
	RCC->AHB1ENR |= GPIOB_EN;

	//Configure mode for GPIOB pin 14
	GPIOB->MODER |= (1U<<28);
	GPIOB->MODER &= ~(1U<<29);

	while(1) {
		// Toggle the ULD3
		//GPIOB->ODR ^= LED_PIN; // Using ODR
		GPIOB->BSSR |= LED_PIN;
		GPIOB->BSRR |= (1U<<30);
	}
}
