#include "stm32f7xx.h"
#include "stdint.h"
#include "usart.h"

#define GPIOB_EN		(1U<<1)
#define GPIOB_PIN_14	(1U<<14)

int main(void)
{
    char message[32] = "Hello from my STM32F722!\r\n";

    RCC->AHB1ENR |= GPIOB_EN;

    GPIOB->MODER |= (1U<<28);
    GPIOB->MODER &= ~(1U<<29);

    usart3_tx_init();
    dma1_stream3_ch4_init((uint32_t) message, (uint32_t)&USART3->TDR, 32);

    while (1) {

    }
}

void dma1_stream3_callback(void) {
	GPIOB->ODR ^= GPIOB_PIN_14;
}

void DMA1_Stream3_IRQHandler(void) {
	if (DMA1->LISR & DMA_TCIF3) {
		DMA1->LIFCR |= DMA_CTCIF3;

		dma1_stream3_callback();
	}
}
