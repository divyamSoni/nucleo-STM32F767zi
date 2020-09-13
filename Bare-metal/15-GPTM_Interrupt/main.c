/*
	Configure General Purpose Timer
	as Interrupt
*/

#include "stm32f7xx.h"                  // Device header

int main(void){
	
	__disable_irq();
	
	RCC->AHB1ENR |= 2;
	GPIOB->MODER = 1;
	
	// TIM2 Config
	RCC->APB1ENR |= 1;
	TIM2->PSC = 16000-1;
	TIM2->ARR =  1000-1;
	TIM2->CR1 = 1;
	TIM2->DIER |= 1;				// Update Interrupt Enabled
	
	NVIC_EnableIRQ(TIM2_IRQn);
	
	__enable_irq();
	
	while(1){}

}

void TIM2_IRQHandler(void){
	TIM2->SR = 0;
	GPIOB->ODR ^= 1;
}
