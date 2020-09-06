#include "stm32f7xx.h"                  // Device header

float freq;
int period;
int prev_value = 0;
int pres_value = 0;
	
int main(void){
	
	//int prev_value = 0;
	//int pres_value = 0;
	
	// Configure PB0 [AF2] as output for TIM3_CH3N [LED1 Green]
	
	RCC->AHB1ENR |= 2;									// Enable clock to GPIOB
	GPIOB->MODER |= 2;									// Set PB0 to Alternate Function
	GPIOB->AFR[0] |= 2;									// Set pin AF2 for PB0
	
	RCC->APB1ENR |= 2;										// Enable clock for TIM3
	TIM3->PSC = 1600-1;										// Divide 16,000,000 by 1,600
	TIM3->ARR = 10000-1;										// Divide 10,000 by 10,000
	TIM3->CCMR2 = 0x30;										// Output compare 3 mode
	TIM3->CCR3 = 0;											// Set match mode
	TIM3->CCER |= 0x100;										// CH3 channel configured as input
	TIM3->CNT = 0;											// Clear counter
	TIM3->CR1 = 1;											// Enable TIM3
	
	// Configure PB6 [AF2] as input of TIM4_CH1

	RCC->AHB1ENR |= 2;								// Enable clock for GPIOB
	GPIOB->MODER |= 0x2000;								// Set PB6 to alternate function
	GPIOB->AFR[0] |= 0x2000000;							// Set pin AF2 for PB6
	
	RCC->APB1ENR |= 4;								// Enable clock for TIM4
	TIM4->PSC = 16000-1;								// Divide 16,000,000 by 16,000
	TIM4->CCMR1 = 0x41;								// CH1 channel configured as input
	TIM4->CCER = 0x0b;								// CH1 to capture at every edge
	TIM4->CNT = 0;
	TIM4->CR1 |= 1;									// Enable TIM4
	
	while(1){
			while(!(TIM4->SR & 2)){}			// wait until edge is captured
			pres_value = TIM4->CCR1;
			period = pres_value - prev_value;
			prev_value = pres_value;
			freq = 1000.0f/period;
	}
}
