#include "stm32f7xx.h"                  // Device header

int analogValue;

int main(void){
	
	RCC->AHB1ENR |= 1;
	GPIOA->MODER |= 0xC;				// Set PA1 to analog
	
	RCC->APB2ENR |= 0x100;			// Enable clock access to ADC
	ADC1->CR2 = 0;							// Turn ADC off
	ADC1->SQR3 = 1;							// Conversion sequence to start at CH1
	ADC1->CR2 |= 1;							// Enable the ADC
	
	
	while(1){
		ADC1->CR2 |= 0x40000000;	// CR2_SWSTART = 1, Start conversion of regular channels
		while(!(ADC1->SR & 2)){}	// wait for the end of conversion
		analogValue = ADC1->DR;
	}
}
