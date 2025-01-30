#include "stm32f4xx.h"

int main()
{
	RCC -> AHB1ENR |= (1U << 0); //port a as active
	RCC -> AHB1ENR |= (1U << 1); //port b as active
	RCC -> AHB1ENR |= (1U << 2); //port c as active
	
	//port a as input
	GPIOA -> MODER |= (0U << 12);
	GPIOA -> MODER |= (0U << 13);
	
	//port b as input
	GPIOB -> MODER |= (0U << 20);
	GPIOB -> MODER |= (0U << 21);
	
	//port c as output
	GPIOC -> MODER |= (1U << 28);
	GPIOC -> MODER |= (0U << 29);
	
	//assigning port a and b as pull up register
	//for a6
	GPIOA -> PUPDR &= ~0x00000003;
	GPIOA -> PUPDR |= (1U << 12);
	GPIOA -> PUPDR |= (0U << 13);
	
	//for b10
	GPIOB -> PUPDR &= ~0x00000003;
	GPIOB -> PUPDR |= (1U << 20);
	GPIOB -> PUPDR |= (0U << 21);
	
	while(1)
	{
		if( (GPIOA -> IDR & (1U << 6)) && (GPIOB -> IDR & (1U << 10)) )
		{
			GPIOC -> ODR &= ~(1U << 14);
		}
		else
		{
			GPIOC -> IDR |= (1U << 14);
			for(int i=0 ; i<180000 ; i++){;}
			GPIOC -> ODR |= (1U << 14);
		}
	}

}