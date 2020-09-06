#include "stm32f7xx.h"                  // Device header

void sysTickDelayMs(int n);

int main(void){
	
	RCC->AHB1ENR |= 1;
	GPIOA->MODER |=	0x400;
	
	while(1){
		sysTickDelayMs(50);
		GPIOA->ODR ^= 0x20;
	}
	
}

void sysTickDelayMs(int n){
	// Clock 16 MHz
	SysTick->LOAD = 16000; 		// Load with number of clocks per milisecond
	SysTick->VAL = 0;		// Clear current value register
	SysTick->CTRL = 0x5;		// Enable SysTick
	
	for(int i = 0; i<n; i++){
		
		// Wait until the count flag is set
		while((SysTick->CTRL & 0x10000) == 0){}
	
	}
	
	SysTick->CTRL = 0;
}	
