#include "systick.h"

#include "stm32f7xx.h"

#define GPIOB_EN	(1U<<1)
#define LED_PIN		(1U<<14)

int main(void)
{
	// Let's toggle the LD3 with frequency of 1Hz (1 time at a second)
	// Provide a clock to GPIOB
	RCC->AHB1ENR |= GPIOB_EN;

	// Configure pin 14 as generic output mode
	GPIOB->MODER |= (1U<<28);
	GPIOB->MODER &= ~(1U<<29);

	while(1) {
		GPIOB->ODR ^= LED_PIN;

		systick_delay_ms(1000);
	}
}
