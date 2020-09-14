#include "stm32f7xx.h"                  // Device header

void UART4_Init(void);
void LED_play(int value);
void sysTickDelayMs(int n);

int main(void){

	__disable_irq();
	
	RCC->AHB1ENR |= 2;					// Enable clock access to GPIOB
	GPIOB->MODER |= 0x1;				// Set output mode for PB0
	
	UART4_Init();
	UART4->CR1 |= 0x0020;				// Enables RX Interrupt
	
	NVIC_EnableIRQ(UART4_IRQn);
	
	__enable_irq();
	
	while(1){}
		
}

void UART4_Init(void){
	
	RCC->APB1ENR |= 0x80000; 		// Enables clock access to UART4
	RCC->AHB1ENR |= 1;        	// Enables clock access to GPIOA
	
	UART4->BRR = 0x008B; 				// 115200 @16 MHz
	UART4->CR1 |= 0x0004;				// Enable Rx
	UART4->CR1 |= 1;     				// Enable UART
	
	GPIOA->AFR[0] = 8; 					// Enabling UART4 PA0 AF8
	GPIOA->MODER |= 2;  				// PA0 <-> Alternate function

}

void LED_play(int value){
	value%=16;
	for(; value>0; value--){
		GPIOB->ODR = 1;
		sysTickDelayMs(100);
		GPIOB->ODR = 0;
		sysTickDelayMs(100);
	}
	sysTickDelayMs(400);
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

void USART_IRQHandler(void){
	char c;
	if(UART4->ISR & 0x0020){
		c = UART4->RDR;
		LED_play(c);
	}
}