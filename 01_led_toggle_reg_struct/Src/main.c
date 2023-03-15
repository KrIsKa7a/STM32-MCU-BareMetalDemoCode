#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

// LED Location
// Port: A
// Pin: 0

#define PERIPH_BASE             (0x40000000UL)
#define AHB_PERIPH_OFFSET		(0x00018000UL)
#define AHB_PERIPH_BASE			(PERIPH_BASE + AHB_PERIPH_OFFSET) //0x4001 8000
#define APB2_PERIPH_OFFSET      (0x00010000UL)
#define APB2_BASE               (PERIPH_BASE + APB2_PERIPH_OFFSET)

#define GPIOA_OFFSET            (0x00000800UL)  //0x4001 0800
#define GPIOA_BASE 				(APB2_BASE + GPIOA_OFFSET) //0x4001 0800

#define RCC_OFFSET				(0x00009000UL)
#define RCC_BASE				(AHB_PERIPH_BASE + RCC_OFFSET) //0x4002 1000UL

#define GPIOA_EN 				(1U<<2)

#define PIN3					(1U<<3)
#define LED_PIN                 PIN3

typedef struct {
	volatile uint32_t CRL; //0x00
	volatile uint32_t DUMMY[2];
	volatile uint32_t ODR; //0x0C
} GPIO_TypeDef;

typedef struct {
	volatile uint32_t RCC_CR;
	volatile uint32_t RCC_CFGR;
	volatile uint32_t RCC_CIR;
	volatile uint32_t RCC_APB2RSTR;
	volatile uint32_t RCC_APB1RSTR;
	volatile uint32_t RCC_AHBENR;
	volatile uint32_t RCC_APB2ENR;
	volatile uint32_t RCC_APB1ENR;
	volatile uint32_t RCC_BDCR;
	volatile uint32_t RCC_CSR;
} RCC_TypeDef;

#define RCC 					((RCC_TypeDef*) RCC_BASE)
#define GPIO_A					((GPIO_TypeDef*) GPIOA_BASE)


int main(void)
{
	// Enable clock access to GPIOA
	RCC->RCC_APB2ENR |= GPIOA_EN;

	// Set pin 3 as output pin
	GPIO_A->CRL |= (1U<<13);
	GPIO_A->CRL &= ~(1U<<12);

	while(1) {
		GPIO_A->ODR|= LED_PIN;
	}
}
