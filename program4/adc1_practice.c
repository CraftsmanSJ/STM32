#include "stm32f4xx.h"
int data;
int threshold = 1024;


int main(void)
{
	RCC -> AHB1ENR |= (1U << 0);
	RCC -> AHB1ENR |= (1U << 2);
	
	RCC -> APB2ENR |= (1U << 8);
	
	GPIOA -> MODER |= (1U << 1);
	GPIOA -> MODER |= (1U << 0);
	
	GPIOC -> MODER |= (0U << 29);
	GPIOC -> MODER |= (1U << 28);
	
	ADC1 -> SMPR2 |= (0U << 0);
	ADC1 -> SMPR2 |= (0U << 1);
	ADC1 -> SMPR2 |= (0U << 2);
	
	ADC -> CCR |= (0U << 17);
	ADC -> CCR |= (1U << 16);
	
	ADC1 -> SQR3 |= (0U << 4);
	ADC1 -> SQR3 |= (0U << 3);
	ADC1 -> SQR3 |= (0U << 2);
	ADC1 -> SQR3 |= (0U << 1);
	ADC1 -> SQR3 |= (0U << 0);
	
	ADC1 -> SQR1 |= (0U << 23);
	ADC1 -> SQR1 |= (0U << 22);
	ADC1 -> SQR1 |= (0U << 21);
	ADC1 -> SQR1 |= (0U << 20);
	
	ADC1 -> CR2 = 0;
	
	ADC1 -> CR2 |= (1U << 1);
	
	ADC1 -> CR2 |= (1U << 0);
	
	while( (ADC1 -> CR2 & (1U << 0)) == 0 ){}
		
	ADC1 -> CR2 |= (1U << 30);
	
	while(1)
	{
		while( !(ADC1 -> SR & (1U << 1)) ){}
			
		data = ADC1 -> DR;
			
		if(data > threshold)
		{
			GPIOC -> ODR |= (1U << 14);
		}
		else
		{
			GPIOC -> ODR &= (0U << 14);
		}
	}
}