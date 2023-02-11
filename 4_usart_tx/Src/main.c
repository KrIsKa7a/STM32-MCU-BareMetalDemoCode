//USART2_TX is on PA2
#include "stdio.h"

#include "stm32f7xx.h"
#include "usart.h"

#define GPIOB_EN	(1U<<1)
#define LED_PIN		(1U<<14)

void init_ULD3(void);

int main(void) {
	init_ULD3();
	usart2_rx_tx_init();

	char key;
	while(1) {
		key = usart2_read();

		if (key == '1') {
			GPIOB->ODR |= LED_PIN;
		} else {
			GPIOB->ODR &= ~(LED_PIN);
		}
	}
}

void init_ULD3(void) {
	// We need to set PB14 as output mode
	RCC->AHB1ENR |= GPIOB_EN;

	GPIOB->MODER |= (1U<<28);
	GPIOB->MODER &= ~(1U<<29);
}
