#include "systick.h"

#include "stm32f7xx.h"

#define SYST_LOAD_VAL_1MS	18750
#define SYST_CTRL_EN		(1U<<0)
#define SYST_CTRL_CLKSRC	(1U<<2)
#define SYST_CTRL_CNTFLAG	(1U<<16)

void systick_delay_ms(int msDelay) {
	// Load the value inside the VAL register
	SysTick->LOAD = SYST_LOAD_VAL_1MS;

	// Clear the previous value if there is some
	SysTick->VAL = 0;

	// Enable SysTick module inside Cortex-M7 processor and choose clock source
	SysTick->CTRL = (SYST_CTRL_EN | SYST_CTRL_CLKSRC);

	for	(int i = 0; i < msDelay; i++) {
		while (!(SysTick->CTRL & SYST_CTRL_CNTFLAG)) {

		}
	}
}
