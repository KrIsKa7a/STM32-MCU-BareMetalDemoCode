//USART2_TX is on PA2
#include "stdio.h"

#include "stm32f7xx.h"
#include "usart.h"


int main(void) {
	while(1) {
		printf("Hello from my STM32 using USART2_TX!");

		for (int i = 0; i < 100000; i++) {

		}
	}
}
