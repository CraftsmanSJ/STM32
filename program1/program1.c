#include "stm32f4xx.h"

int main(void) {
    // Enable clocks for GPIOA and GPIOB
    RCC->AHB1ENR |= (1U << 2); // GPIOA clock enable
   
    // Set PA5 and PA6 as output (for LEDs)
    GPIOC->MODER |= (1U << 26); // Set PA5 to output
    GPIOC->MODER |= (0U << 27); // Set PA6 to output

    // Create an array with a mix of uppercase and lowercase letters
    while (1) 
		{
			GPIOC -> ODR &= ~(1U << 26);
		}
        
}