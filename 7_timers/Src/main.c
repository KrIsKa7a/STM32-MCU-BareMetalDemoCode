#include "stm32f7xx.h"

#include "tim.h"

#define GPIOB_EN	(1U<<1)
#define LED_PIN		(1U<<14)

int main(void)
{
    RCC->AHB1ENR |= GPIOB_EN;

    GPIOB->MODER |= (1U<<28);
    GPIOB->MODER &= ~(1U<<29);

    //tim2_1hz_init();

    tim2_input_capture_ch3();
    tim2_output_compare_ch2();

    int timePassed = 0;
    while (1) {
//		while (!(TIM2->SR & SR_UIF)) {
//
//		}
//
//		GPIOB->ODR ^= LED_PIN;
//
//		TIM2->SR &= ~SR_UIF;
    	while (!(TIM2->SR & SR_CC3IF)) {

    	}

    	timePassed = (TIM2->CCR3 & 0xFF);
    }
}
