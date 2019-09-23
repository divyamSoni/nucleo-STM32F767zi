#include "stm32f7xx.h"                  // Device header
// B1 <-> PC13
// LD1 - PB0
// LD2 - PB7
// LD3 - PB14

int main(){
		
		RCC->AHB1ENR |=  0x2; //Enables clock access to GPIOB
		RCC->AHB1ENR |=  0x4; //Enables clock access to GPIOC
		
		// By default PIN mode is Input
		// No need to change GPIOC->MODER 
	
		// Setting Output mode for LEDs
	
		GPIOB->MODER |= 0x1;				//LED2 <-> PB0	
		GPIOB->MODER |= 0x4000;			//LED2 <-> PB7
		GPIOB->MODER |= 0x10000000;	//LED3 <-> PB14
		
		while(1){
				if(GPIOC->IDR & 0x2000){ 
				//if PC13 is high 	
					GPIOB->ODR = 0x4081;  // LED 1,2,3 ON!	
				}
				else{
					GPIOB->ODR = 0;				// LED 1,2,3 OFF				
				}
		}
}