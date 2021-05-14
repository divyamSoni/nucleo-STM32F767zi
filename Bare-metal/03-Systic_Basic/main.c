/*****************************
** Use SysTick to generate 	**
** constant delay to blink 	**
** an LED					**
*****************************/

#include "stm32f7xx.h"        // Device header

int main(void){
	RCC->AHB1ENR |= 2;		   // Enable clock access to GPIOB
	GPIOB->MODER |= 0x4000;	   // GPIOB_PIN_14 output mode

	//Configure Systick
	SysTick->LOAD = 3200000 - 1;   // 200ms (@16MHz)
	SysTick->VAL = 0;              // Clear current value register
	SysTick->CTRL = 5;             // Enable SysTick

	while(1){
		// Check if count flag is set
		if(SysTick->CTRL & 0x10000){
			GPIOB->ODR ^= 0x80; 	// Toggle LED2 - BLUE
		}
	}
}
