#include "stm32f7xx.h"                  // Device header

/*

Toggle the LED using TIM2
AF2 <-> TIM3_CH3N <-> PB0 <-> LED1 (GREEN)

*/

int main(){	
	RCC->AHB1ENR |= 2;										// Enable clock to GPIOB
	GPIOB->MODER |= 2;										// Set PB0 to Alternate Function
	GPIOB->AFR[0] |= 2;										// Set pin AF2 for AFR0

	RCC->APB1ENR |= 2;										// Enable clock for TIM3
	TIM3->PSC = 1600-1;										// Divide 16,000,000 by 1,600
	TIM3->ARR = 10000-1;										// Divide 10,000 by 10,000
	TIM3->CNT = 0;											// Clear the TIM3 counter
	TIM3->CR1 = 1;											// Enable the TIM3 counter
	TIM3->CCMR2 = 0x30;										// Output compare 3 mode
	TIM3->CCR1 = 0;											// Set match mode
	TIM3->CCER = 0x100;										// CH3 channel configured as input
	TIM3->CNT = 0;											// Clear counter
	TIM3->CR1 = 1;											// Enable TIM3
	
	while(1){}
}
