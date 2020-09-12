#include "stm32f7xx.h"                  // Device header

/*
		Configure SysTick Interrupt to toggle LED
		at 1 Hz, System Clock is 16 MHz
*/

int main(void){
	
	__disable_irq();
	
	RCC->AHB1ENR |= 2;							// Clock access to GPIOB
	GPIOB->MODER |= 1;							// Output mode for LED1							
	
	SysTick->LOAD = 16000000 - 1;		// Get 1 Hz interrupt
	SysTick->VAL 	= 0;
	SysTick->CTRL = 7;							// Enable Interrupt for SysTick
	
	__enable_irq();
	
	while(1){}
	
}

void SysTick_Handler(void){			// Any Interrupt Service Routine
	GPIOB->ODR ^= 0x01;						// e.g. toggling LED
}