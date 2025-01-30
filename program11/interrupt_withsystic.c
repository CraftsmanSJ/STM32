#include "stm32f4xx.h"
int count;
int duration;
int main(void)
{
	RCC -> AHB1ENR |= (1U << 0);
	RCC -> AHB1ENR |= (1U << 1);
	RCC -> AHB1ENR |= (1U << 2);
	
	GPIOA -> MODER |= (0U << 13);
	GPIOA -> MODER |= (0U << 12);
	
	GPIOA -> PUPDR |= (0U << 13);
	GPIOA -> PUPDR |= (1U << 12);
	
	GPIOB -> MODER |= (0U << 21);
	GPIOB -> MODER |= (0U << 20);
	
	GPIOB -> PUPDR |= (0U << 21);
	GPIOB -> PUPDR |= (1U << 20);
	
	GPIOC -> MODER |= (0U << 29);
	GPIOC -> MODER |= (1U << 28);
	
	GPIOC -> MODER |= (0U << 19);
	GPIOC -> MODER |= (1U << 18);
	
	RCC -> APB2ENR |= (1U << 14);
	
	SYSCFG -> EXTICR[1] |= (0U << 11);
	SYSCFG -> EXTICR[1] |= (0U << 10);
	SYSCFG -> EXTICR[1] |= (0U << 9);
	SYSCFG -> EXTICR[1] |= (0U << 8);
	
	SYSCFG -> EXTICR[2] |= (0U << 11);
	SYSCFG -> EXTICR[2] |= (0U << 10);
	SYSCFG -> EXTICR[2] |= (0U << 9);
	SYSCFG -> EXTICR[2] |= (1U << 8);
	
	EXTI -> IMR |= (1U << 6);
	EXTI -> IMR |= (1U << 10);
	
	EXTI -> FTSR |= (1U << 6);
	EXTI -> FTSR |= (1U << 10);
	
	NVIC_EnableIRQ(EXTI9_5_IRQn);
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	
	while(1){}
}

void EXTI9_5_IRQHandler(void)
{
	if (EXTI -> PR & (1U << 6))
	{
		EXTI -> PR |= (1U << 6);
		duration = 1;
		SysTick -> LOAD = 16000000-1;
		SysTick -> VAL = 0;
		SysTick -> CTRL = 7;
		count =0 ;
	}
}

void EXTI15_10_IRQHandler(void)
{
	if (EXTI -> PR & (1U << 10))
	{
		SysTick -> CTRL = 0;
	}
}


void SysTick_Handler(void)
{
	count++;
	if(SysTick -> CTRL & (1U << 16))
	{
		if (count == duration)
		{
			GPIOC -> ODR ^= (1U << 14);
			count = 0;
		}
	}
} 