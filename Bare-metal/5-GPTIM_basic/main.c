#include "stm32f7xx.h"                  // Device header

int main(void){
	RCC->AHB1ENR |= 1;
	GPIOA->MODER |= 0x400;
	
	// TIM2 config
	RCC->APB1ENR |= 1;
																				// clock source = 16 MHz
	TIM2->PSC = 1600 - 1;									// Divide by 1600
	TIM2->ARR = 10000 - 1;								// Divide by 10000
	TIM2->CNT = 0;												// Clear timer counter
	TIM2->CR1 = 1;												// Enable TIM2
	
	while(1){
		while(TIM2->SR & 1){
			TIM2->SR &=~1;
			GPIOA->ODR ^= 0x20; 
		}
	}
}
