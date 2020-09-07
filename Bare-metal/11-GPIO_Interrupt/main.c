// GPIO Interrupt

#include "stm32f7xx.h"                  // Device header

void sysTickDelayMs(int n);
void EXTI15_10_IRQHandler(void);

int main(void){
	
	__disable_irq();						// Disable global interrupt
	
	RCC->AHB1ENR |=  0x2; 			// Enable clock access to GPIOB
	RCC->AHB1ENR |=  0x4; 			// Enable clock access to GPIOC
	RCC->APB2ENR |= 0x4000;			// Enable clock access to SYSCFG
	
				
	// Setting Output mode for LEDs
	
	GPIOB->MODER |= 0x1;							// LD1 <-> PB0	
	GPIOB->MODER |= 0x4000;						// LD2 <-> PB7
	GPIOB->MODER |= 0x010000000;			// LD3 <-> PB14
	// By default PC13 is input (00)
	
	SYSCFG->EXTICR[3] |= 0x0020;	// Select Port C for EXTI13
	EXTI->IMR |= 0x2000;					// Unmask EXTI13
	EXTI->FTSR |= 0x2000;					// Select falling edge trigger
	
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	
	__enable_irq();							// Enable global interrupt
	
	while(1){}	// doing something here
}

void EXTI15_10_IRQHandler(void){
	
	GPIOB->ODR = 0x4081;
	sysTickDelayMs(400);
	GPIOB->ODR = 0;
	sysTickDelayMs(400);
	
	GPIOB->ODR = 0x4081;
	sysTickDelayMs(400);
	GPIOB->ODR = 0;
	sysTickDelayMs(400);
	
	EXTI->PR = 0x2000;					// Clear the interrupt flag
}

void sysTickDelayMs(int n){
	// Clock 16 MHz
	SysTick->LOAD = 16000; 		// Load with number of clocks per milisecond
	SysTick->VAL = 0;					// Clear current value register
	SysTick->CTRL = 0x5;			// Enable SysTick
	
	for(int i = 0; i<n; i++){	
		// Wait until the count flag is set
		while((SysTick->CTRL & 0x10000) == 0){}
	
	}
	
	SysTick->CTRL = 0;
}	
