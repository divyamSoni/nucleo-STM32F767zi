#include "stm32f7xx.h"                  // Device header

int main(void){
	// Configure PB0 [AF2] as output for TIM3_CH3N [LED1 Green]
	
	RCC->AHB1ENR |= 2;										// Enable clock to GPIOB
	GPIOB->MODER |= 2;										// Set PB0 to Alternate Function
	GPIOB->AFR[0] |= 2;										// Set pin AF2 for PB0
	
	RCC->APB1ENR |= 2;										// Enable clock for TIM3
	TIM3->PSC = 10-1;											// Divide 16,000,000 by 10
	TIM3->ARR = 26667-1;									// Divide  1,600,000 by 26667
	TIM3->CNT = 0;												// Clear counter
	TIM3->CCMR2 = 0x60;										// PWM Mode
	TIM3->CCER = 0x100;										// Enable Channel 3
	TIM3->CCR3 = 8889-1;									// Set match mode
	TIM3->CR1 = 1;												// Enable TIM3

	while(1){}
}