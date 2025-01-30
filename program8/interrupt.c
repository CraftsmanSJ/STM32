#include "stm32f4xx.h"

int main(void)
{
	RCC -> AHB1ENR |= (1U << 0);
	RCC -> AHB1ENR |= (1U << 2);
	
	GPIOA -> MODER |= (0U << 13);
	GPIOA -> MODER |= (0U << 12);
	
	GPIOA -> MODER |= (0U << 15);
	GPIOA -> MODER |= (0U << 14);
	
	GPIOA -> PUPDR |= (0U << 13);
	GPIOA -> PUPDR |= (1U << 12);
	
	GPIOA -> PUPDR |= (0U << 15);
	GPIOA -> PUPDR |= (1U << 14);
	
	GPIOC -> MODER |= (0U << 29);
	GPIOC -> MODER |= (1U << 28);
	
	RCC -> APB2ENR |= (1U << 14);
	
	SYSCFG -> EXTICR[1] |= (0U << 11);
	SYSCFG -> EXTICR[1] |= (0U << 10);
	SYSCFG -> EXTICR[1] |= (0U << 9);
	SYSCFG -> EXTICR[1] |= (0U << 8);
	
	SYSCFG -> EXTICR[1] |= (0U << 15);
	SYSCFG -> EXTICR[1] |= (0U << 14);
	SYSCFG -> EXTICR[1] |= (0U << 13);
	SYSCFG -> EXTICR[1] |= (0U << 12);
	
	EXTI -> IMR |= (1U << 6);
	EXTI -> IMR |= (1U << 7);
	
	EXTI -> FTSR |= (1U << 6);
	EXTI -> FTSR |= (1U << 7);
	
	NVIC_EnableIRQ(EXTI9_5_IRQn);
	
	while(1){}
}

void EXTI9_5_IRQHandler()
{
	if(EXTI -> PR & (1U << 6))
	{
		EXTI -> PR |= (1U << 6);
		
		GPIOC -> ODR |= (1U << 14);
	}
	
	if(EXTI -> PR & (1U << 7))
	{
		EXTI -> PR |= (1U << 7);
		
		GPIOC -> ODR &= ~(1U << 14);
	}
}