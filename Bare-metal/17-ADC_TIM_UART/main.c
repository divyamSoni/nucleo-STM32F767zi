#include "stm32f7xx.h"                  // Device header
#include <stdio.h>

int data;
double voltage;
double celsius;

int UART4_write(int ch);
void UART4_Init(void);

int main(void){
	
	RCC->AHB1ENR |= 1;
	RCC->APB1ENR |= 1;
	
	TIM2->PSC =  1600-1;
	TIM2->ARR = 10000-1;
	TIM2->CNT = 0;
	
	TIM2->CCMR1 = 0x6800;
	TIM2->CCER = 0x0010;
	TIM2->CCR2 = 50-1;
	TIM2->CR1 = 1;
	
	
	// ADC Setup
	RCC->APB2ENR |= 0x100;				// Enable clock access to ADC
	ADC->CCR |=  0x00800000;			// Temperature sensor and VREFINT channel enabled
	ADC->CCR &=~ 0x00400000;			// Disabled Vbat for temp sensor
	
	ADC1->CR2 = 0;								// Turn ADC off
	ADC1->SMPR1 = 0x00400000; 		// Sampling time minimum 10usec
	ADC1->SQR3 = 18;							// Temp sens. connected to CH18
	ADC1->CR2 |= 0x13000000;
	ADC1->CR2 |= 1;
	
	UART4_Init();
	printf("STM32F767zi Temperature \r\n");
	
	while(1){
		while(!(ADC1->SR & 2)){}
			data = ADC1->DR;
			voltage = (double)data/4095*3.3;
			celsius = (voltage - 0.76)/0.0025+25;
			
			printf("%d, %.2f\370C\r\n", data, celsius);
	}
}

void UART4_Init(void){
	
	RCC->APB1ENR |= 0x80000; 		// Enables clock access to UART4
	RCC->AHB1ENR |= 1;        	// Enables clock access to GPIOA
	
	UART4->BRR = 0x0682; 				// 9600 @16 MHz
	UART4->CR1 |= 0x0008;				// Enable Tx
	UART4->CR1 |= 1;     				// Enable UART
	
	GPIOA->AFR[0] = 8; 					// Enabling UART4 PA0 AF8
	GPIOA->MODER |= 2;  				// PA0 <-> Alternate function

}

struct __FILE{
	int handle;
};

FILE __stdout = {1};

int fputc(int c, FILE *f){
	return UART4_write(c);
}

int UART4_write(int ch){
	while(!(UART4->ISR & 0x0080)){}
		UART4->TDR = ch;
		return ch;
}
