/*********************************
** Make UART transmitter driver	**
** transmit a message and view 	**
** using any serial monitor			**
*********************************/

#include "stm32f7xx.h"

void UART2_Init(void);
void UART2_Transmit(int ch);
void GPIO_Init(void);
void Blue_Led2(void);
void Green_Led1(void);
void sysTickDelayMs(int n);

static char chara = '0';

int main(void){
	GPIO_Init();
	UART2_Init();
	
	while(1){
		UART2_Transmit('H');
		UART2_Transmit('i');
	}	
}

void GPIO_Init(void){
	RCC->AHB1ENR |= (1UL<<1)|(1UL<<3);  // Enables clock access to GPIOB, D
	
	GPIOB->MODER |= 1UL<<14;			// PB7 - output mode - LED2 - Blue
	GPIOB->MODER |= 1;						// PB0 - output mode - LED1 - Green
	
	GPIOD->AFR[0] &= ~(0xFUL<<20);	// Clear PD5 - AF
	GPIOD->AFR[0] = 7UL << 20; 			// AF7 (USART_B_TX) PD5
	
	GPIOD->AFR[0] &= ~(0xFUL<<24);	// Clear PD6 - AF
	GPIOD->AFR[0] = 7UL << 24; 			// AF7 (USART_B_RX) PD6
	
	GPIOD->MODER &=~ (0x3UL << 10);	// Clear PD5 mode
	GPIOD->MODER |= 1UL << 11;  		// PD5 - Alternate function
	
	GPIOD->MODER &=~ (0x3UL << 12);	// Clear PD6 mode
	GPIOD->MODER |= 1UL << 13;  		// PD6 - Alternate function
}

void UART2_Init(void){
	
	RCC->APB1ENR |= 1UL << 17; 		// Enables clock access to UART2
	
	USART2->BRR = 0x0682; 				// 9600 @16 MHz
	USART2->CR1 |= 0x0008;				// Enable Tx
	USART2->CR1 |= 1;     				// Enable UART
}

void UART2_Transmit(int ch){
	// wait while TX buffer is empty
	while(!(USART2->ISR & 0x0080)){}
	Green_Led1();
	chara = (char)USART2->TDR;
	USART2->TDR = (ch & 0x1FF);
}

void Blue_Led2(void){
	GPIOB->ODR ^= 0x80;
	sysTickDelayMs(500);
}

void Green_Led1(void){
	GPIOB->ODR ^= 1;
	sysTickDelayMs(500);
}

void sysTickDelayMs(int n){
	// Clock 16 MHz
	SysTick->LOAD = 16000; 	// Load with number of clocks per millisecond
	SysTick->VAL = 0;				// Clear current value register
	SysTick->CTRL = 0x5;		// Enable SysTick

	for(int i = 0; i<n; i++){
		// Wait until the count flag is set
		while(!(SysTick->CTRL & 0x10000)){}
	}
	SysTick->CTRL = 0;     // Diable SysTick
}
