#include "stm32f7xx.h"                  // Device header

int main(){	
	RCC->AHB1ENR |= 0x2;		// Enable clock for GPIOB
	GPIOB->MODER |= 0x4000;	// General Purpose output mode for GPIOB_MODER7
	
	/* 	Timer config
			1 Hz TIMER
	*/
	RCC->APB1ENR |= 1;			// Enable clock for Timer2
	TIM2->PSC = 1600-1;			// Divide 16,000,000 by 1600
	TIM2->ARR = 10000-1;		// Divide 10,000 by 10,000
	TIM2->CNT = 0;					// Clear the Timer2 counter
	TIM2->CR1 = 1;					// Enable the Timer2 counter
	
	while(1){
		while(!(TIM2->SR & 1)){}
			TIM2->SR &=~ 1;		
			GPIOB->ODR ^= 0x80;	// Toggle ODR7
	}
}