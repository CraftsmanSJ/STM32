#include "stm32f4xx.h"
int count;
int main(void)
{
	RCC -> AHB1ENR |= (1U << 2);
	
	GPIOC -> MODER |= (0U << 29);
	GPIOC -> MODER |= (1U << 28);
	
	SysTick -> LOAD = 16000000 - 1;
	SysTick -> VAL = 0;
	SysTick -> CTRL |= (1U << 0);
	SysTick -> CTRL |= (1U << 1);
	SysTick -> CTRL |= (1U << 2);
	
	while(1){}
}

void SysTick_Handler(void)
{
	count++;
	if(count >= 2 )
	{
		if(SysTick -> CTRL & (1U << 16))
		{
			GPIOC -> ODR ^= (1U << 14);
			count = 0;
		}
	}
}