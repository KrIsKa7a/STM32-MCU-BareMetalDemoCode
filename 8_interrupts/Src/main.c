#include "stm32f7xx.h"
#include "exti.h"
#include "usart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"

#define GPIOB_EN		(1U<<1)
#define GPIOx_PIN_14_M	(1U<<28 & ~(1U<<29))
#define GPIOB_PIN_14	(1U<<14)

void pc13_exti_callback(void);
void USART3_read_callback(void);

int sensorValue;

int main(void)
{
	RCC->AHB1ENR |= GPIOB_EN;

	GPIOB->MODER |= GPIOx_PIN_14_M;

	//pc13_exti_init();
	//usart3_rx_tx_init();
	tim2_ch1_1hz_interrupt_init();

    while (1) {

    }
}

void pc13_exti_callback(void) {
	GPIOB->ODR ^= GPIOB_PIN_14;
}

void EXTI15_10_IRQHandler(void) {
	if (EXTI->PR & LINE_13) {
		pc13_exti_callback();

		EXTI->PR |= LINE_13;
	}
}

void USART3_read_callback(void) {
	char key = USART3->RDR;

	if (key == '1') {
		GPIOB->ODR |= GPIOB_PIN_14;
	} else {
		GPIOB->ODR &= ~GPIOB_PIN_14;
	}
}

void USART3_IRQHandler(void) {
	if (USART3->ISR & USART_SR_RXNE) {
		USART3_read_callback();
	}
}

void ADC1_read_callback(void) {
	sensorValue = adc_read_value();
	printf("Sensor value is %d", sensorValue);
}

void ADC_IRQHandler(void) {
	if (ADC1->SR & ADC_EOC) {
		ADC1->SR &= ~ADC_EOC;

		ADC1_read_callback();
	}
}

void SysTick_callback(void) {
	GPIOB->ODR ^= GPIOB_PIN_14;
}

void SysTick_Handler(void) {
	SysTick_callback();
}

void TIM2_callback(void) {
	GPIOB->ODR ^= GPIOB_PIN_14;
}

void TIM2_IRQHandler(void) {
	TIM2->SR &= ~SR_UIF;

	TIM2_callback();
}
