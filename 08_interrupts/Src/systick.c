#include "stm32f7xx.h"
#include "systick.h"

#define SYSTICK_CLK		16000000
#define SYSTICK_EN		(1U<<0)
#define SYSTICK_IE		(1U<<1)
#define SYSTICK_CLK_SRC	(1U<<2)

void sysTick_delay_ms_interrupt(int ms) {
	SysTick->LOAD = SYSTICK_CLK / 1000 * ms;

	SysTick->VAL = 0;

	SysTick->CTRL |= SYSTICK_EN;
	SysTick->CTRL |= SYSTICK_CLK_SRC;
	SysTick->CTRL |= SYSTICK_IE;
}
