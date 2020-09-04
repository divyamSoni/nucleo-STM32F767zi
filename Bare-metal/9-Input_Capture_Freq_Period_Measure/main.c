#include "stm32f7xx.h"                  // Device header

float freq;
int period;

int main(void){
	
	int prev_value = 0;
	int pres_value = 0;
	
	// Configure PB0 [AF2] as output for TIM3_CH3N [LED1 Green]
	
	RCC->AHB1ENR |= 2;										// Enable clock to GPIOB
	GPIOB->MODER |= 2;										// Set PB0 to Alternate Function
	GPIOB->AFR[0] |= 2;										// Set pin AF2 for PB0
	
	RCC->APB1ENR |= 2;										// Enable clock for TIM3
	TIM3->PSC = 1600-1;										// Divide 16,000,000 by 1,600
	TIM3->ARR = 10000-1;									// Divide 10,000 by 10,000
	TIM3->CCMR2 = 0x30;										// Output compare 3 mode
	TIM3->CCR3 = 0;												// Set match mode
	TIM3->CCER = 0x100;										// CH3 channel configured as input
	TIM3->CNT = 0;												// Clear counter
	TIM3->CR1 = 1;												// Enable TIM3
	
	// Configure PA0 [AF1] as input of TIM2_CH1N

	RCC->AHB1ENR |= 1;										// Enable clock for GPIOA
	GPIOA->MODER |= 2;										// Set PA0 to alternate function
	GPIOA->AFR[0] |= 1;										// Set pin AF1 for PA0
	
	RCC->APB1ENR |= 1;										// Enable clock for TIM2
	TIM2->PSC = 16000-1;									// Divide 16,000,000 by 16,000
	TIM2->CCMR1 = 0x41;										// CH1 to capture at every edge
	TIM2->CCER = 0x0B;										// CH1 channel: Input capture at both edges
	TIM2->CR1 = 1;												// Set match mode
	
	while(1){
			while(!(TIM2->SR & 2)){}					// wait until edge is captured
			pres_value = TIM2->CCR1;
			period = pres_value - prev_value;
			prev_value = pres_value;
			freq = 1000.0f/period;
	}
}