#include "stm32f4xx.h"
static int count = 0;
int main(void)
{
    // 1- Enable GPIOA and GPIOC clocks
    RCC->AHB1ENR |= (1U << 0);  // Enable clock for GPIOA (1U << 0 corresponds to GPIOAEN)
    RCC->AHB1ENR |= (1U << 2);  // Enable clock for GPIOC (1U << 2 corresponds to GPIOCEN)
		RCC->AHB1ENR |= (1U << 1);

    // 2- Set PC13 as output
    GPIOC->MODER &= ~(0x3 << 28); // Clear mode bits for PC13 (26 is the bit position)
    GPIOC->MODER |= (0x1 << 28);  // Set PC13 to output mode (01)
	
		GPIOB->MODER &= ~(0x3 << 18); // Clear mode bits for PC13 (26 is the bit position)
    GPIOB->MODER |= (0x1 << 18);
	
    // 3- Set PA0 as input
    GPIOA->MODER &= ~(0x3 << 12); // Set PA0 to input mode (bits 0 and 1)

    // Enable internal pull-up resistor for PA0
    GPIOA->PUPDR &= ~(0x3 << 12); // Clear pull-up/pull-down bits for PA0
    GPIOA->PUPDR |= (0x1 << 12);  // Set pull-up for PA0

    // 4- Enable SYSCFG clock
    RCC->APB2ENR |= (1U << 14); // Enable SYSCFG clock (1U << 14 corresponds to SYSCFGEN)

    // 5- Configure EXTI for PA0
    SYSCFG->EXTICR[1] &= ~(0xF << 0); // Clear EXTI0 configuration (PA0)
    SYSCFG->EXTICR[1] |= (0U << 11);  // Set PA0 as the source input for EXTI0
		SYSCFG->EXTICR[1] |= (0U << 10);
		SYSCFG->EXTICR[1] |= (0U << 9);
		SYSCFG->EXTICR[1] |= (0U << 8);

    // 6- Enable the Interrupt Mask register
    EXTI->IMR |= (1 << 6);   // Unmask EXTI line 0 (PA0)

    // 7- Select the Interrupt Trigger
    EXTI->FTSR |= (1 << 6);  // PA0 as Falling trigger

    // 8- NVIC Enable
    NVIC_EnableIRQ(EXTI9_5_IRQn);  // Enable EXTI0 interrupt (PA0 covers line 0)

    while (1)
    {
        // Main loop - do nothing, waiting for interrupts
    }
}

// EXTI0 interrupt handler (PA0 is on EXTI line 0)
void EXTI9_5_IRQHandler(void)
{
    count++;
    if (EXTI->PR & (1U << 6)) // Check if interrupt is pending on EXTI0
    {
        EXTI->PR |= (1U << 6); // Clear pending interrupt on EXTI0

        if(count % 2 != 0)
        {
            // Turn on LED on PC13
            GPIOC->ODR |= (1U << 14);
						GPIOB->ODR &= ~(1U << 9);
        }
        else
        {
            // Turn off LED on PC13
            GPIOC->ODR &= ~(1U << 14);
						GPIOB->ODR |= (1U << 9);
        }
    }
}
