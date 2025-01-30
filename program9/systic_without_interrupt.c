#include "stm32f4xx.h"
int tick_count  = 0;

int main(void)
{
	RCC -> AHB1ENR |= (1U << 0);
	RCC -> AHB1ENR |= (1U << 2);
	
	GPIOA -> MODER |= (0U << 13);
	GPIOA -> MODER |= (0U << 12);
	
	GPIOC -> MODER |= (0U << 29);
	GPIOC -> MODER |= (1U << 28);
	
	GPIOA -> PUPDR |= (0U << 13);
	GPIOA -> PUPDR |= (1U << 12);
	
	SysTick -> LOAD = 16000000 -1;
	SysTick -> VAL = 0;
	SysTick -> CTRL = 5;
	
	while(1)
	{
		if( SysTick -> CTRL & (1U << 16) )
		{
			GPIOC -> ODR ^= (1U << 14);
		}
	}
	
}