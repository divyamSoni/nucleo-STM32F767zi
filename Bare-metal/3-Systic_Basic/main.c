#include "stm32f7xx.h"                  // Device header

int main(void){
	RCC->AHB1ENR |= 1;
	GPIOA->MODER |= 0x400;
	
	//Configure Systick
	SysTick->LOAD = 3200000 - 1; // 200ms (16MHz)
	SysTick->VAL = 0;
	SysTick->CTRL = 5;
	
	while(1){
		// Check if count flag is set
		if(SysTick->CTRL & 0x10000){
			GPIOA->ODR ^= 0x20; // Toggle LED
		}
	}
}