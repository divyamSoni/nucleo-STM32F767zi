/*********************************
** Use callable SysTick to set  **
** desired delay and blink an   **
** LED                          **
*********************************/

#include "stm32f7xx.h"                  // Device header

void sysTickDelayMs(int n);

int main(void){

	RCC->AHB1ENR |= 2;         // Enable clock access to GPIOB
	GPIOB->MODER |=	0x4000;    // Set GPIOB_PIN_14 to output mode

	while(1){
		sysTickDelayMs(50);   // 50 millisecond
		GPIOB->ODR ^= 0x80;   // Toggle LED2 - BLUE
	}

}

void sysTickDelayMs(int n){
	// Clock 16 MHz
	SysTick->LOAD = 16000; 	// Load with number of clocks per millisecond
	SysTick->VAL = 0;		// Clear current value register
	SysTick->CTRL = 0x5;	// Enable SysTick

	for(int i = 0; i<n; i++){
		// Wait until the count flag is set
		while(!(SysTick->CTRL & 0x10000)){}
	}
	SysTick->CTRL = 0;     // Diable SysTick
}
