#include "stm32f7xx.h"

#include "exti.h"

#define GPIOC_EN			(1U<<2)
#define SYSCFG_EN			(1U<<14)
#define EXTICR_EXTI13_PC	(1U<<5)
#define EXTI_IMR_IM13		(1U<<13)
#define EXTI_FTSR_TR13		(1U<<13)

void pc13_exti_init(void) {
	// Disable global interrupts
	__disable_irq();

	// Enable clock access for GPIOC
	RCC->AHB1ENR |= GPIOC_EN;

	// Set pin 13 as input mode
	GPIOC->MODER &= ~(1U<<26);
	GPIOC->MODER &= ~(1U<<27);

	// Enable clock access for SYSCFG
	RCC->APB2ENR |= SYSCFG_EN;

	// Select Port C for EXTI13
	SYSCFG->EXTICR[3] |= EXTICR_EXTI13_PC;

	// Unmask EXTI13
	EXTI->IMR |= EXTI_IMR_IM13;

	// Select falling edge trigger
	EXTI->FTSR |= EXTI_FTSR_TR13;

	// Enable EXTI13 line in NVIC
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	// Enable global interrupts
	__enable_irq();
}
