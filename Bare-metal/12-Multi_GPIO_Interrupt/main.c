#include "stm32f7xx.h"                  // Device header

void sysTickDelayMs(int n);

volatile int PB10_counter = 0;
volatile int PC13_counter = 0;

int main(void){
	
	RCC->AHB1ENR |= 6;						// Enable GPIOB, C
	
	RCC->APB2ENR |= 0x4000;				// Enable SysConfig clock
	
	GPIOB->MODER |= 0x010004000;	// LED as output
		
	SYSCFG->EXTICR[3] |= 0x0020;	// Select Port C for EXTI13
	
	EXTI->IMR |= 0x2000;					// Unmask EXTI13
	EXTI->FTSR |= 0x2000;					// Select falling egde trigger
	
	GPIOB->PUPDR |= 00100000;			// Enable pull-up resistor for PB10
	
	SYSCFG->EXTICR[2] |= 0x0100;	// Select Port B for EXTI10
	EXTI->IMR |= 0x0400;					// Unmask EXTI10
	EXTI->FTSR |= 0x0400;					// Select falling edge trigger
	
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	
	__enable_irq();
	
	while(1){}
		
}

void EXTI15_10_IRQHandler(void){
	if(EXTI->PR == 0x2000){
		PC13_counter++;
	
		GPIOB->ODR = 0x4000;					// LED3 (RED) ON
		sysTickDelayMs(300);
		GPIOB->ODR = 0;
		sysTickDelayMs(300);
		GPIOB->ODR = 0x4000;					// LED3 (RED) ON
		sysTickDelayMs(300);
		GPIOB->ODR = 0;
	
		EXTI->PR = 0x2000;						// Clear interrupt pending flag
		
	}
	else if(EXTI->PR == 0x0400){
		PB10_counter++;
	
		GPIOB->ODR = 0x80;						// LED2 (BLUE) ON
		sysTickDelayMs(300);
		GPIOB->ODR = 0;
		sysTickDelayMs(300);
		GPIOB->ODR = 0x80;						// LED2 (BLUE) ON
		sysTickDelayMs(300);
		GPIOB->ODR = 0;
	
		EXTI->PR = 0x0400;						// Clear interrupt pending flag
	}
}

void sysTickDelayMs(int n){
	// Clock 16 MHz
	SysTick->LOAD = 16000; 		// Load with number of clocks per milisecond
	SysTick->VAL = 0;					// Clear current value register
	SysTick->CTRL = 0x5;			// Enable SysTick
	
	for(int i = 0; i<n; i++){
		
		// Wait until the count flag is set
		while((SysTick->CTRL & 0x10000) == 0){}
	
	}
	
	SysTick->CTRL = 0;
}
