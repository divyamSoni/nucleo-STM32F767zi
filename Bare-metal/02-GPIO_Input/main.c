/*****************************
** Pressing user button B1 	**
** turns on LD1, 2, 3		**
** using polling			**
** B1 <-> PC13				**
** LD1 - PB0				**
** LD2 - PB7				**
** LD3 - PB14 				**
******************************/

#include "stm32f7xx.h"                  // Device header

int main(){

		RCC->AHB1ENR |=  0x2; 			//Enables clock access to GPIOB
		RCC->AHB1ENR |=  0x4; 			//Enables clock access to GPIOC

		// Setting Output mode for LEDs

		GPIOB->MODER |= 0x1;			// LD1 <-> PB0
		GPIOB->MODER |= 0x4000;			// LD2 <-> PB7
		GPIOB->MODER |= 0x010000000;	// LD3 <-> PB14

		while(1){
			if(GPIOC->IDR & 0x2000){
			// if PC13 is high
				GPIOB->ODR = 0x4081UL;  	// LED 1,2,3 ON!
			}
			else{
				GPIOB->ODR &=~ 0x4081UL;	// LED 1,2,3 OFF
			}
		}
}
