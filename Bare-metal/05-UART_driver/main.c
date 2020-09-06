/*	USART2 <-> APB1
	RCC->APB1ENR bit 17 for UART2
	PA2 <-> USART2_TX
	PA3 <-> USART2_RX
*/

#include "stm32f7xx.h"

void USART2_Init(void);
void USART_write(int ch);
void delayms(int delay);

int main(void){
	
	USART2_Init();
	
	while(1){
		USART_write('H');
		USART_write('i');
		delayms(10);
	}	
}

void USART2_Init(void){
	
	RCC->APB1ENR |= 0x20000; 		// Enables clock access to USART2
	RCC->AHB1ENR |= 1;        		// Enables clock access to GPIOA
	
	USART2->BRR = 0x0682; 			// 9600 @16 MHz
	USART2->CR1 = 0x0008; 			// Enable Tx
	USART2->CR1 |= 1;     			// Enable USART
	
	GPIOA->AFR[0] = 0x0700; 		// Enabling USART2 PA2 AF7
	GPIOA->AFR[1] = 0X0700;			// Enabling USART2 PA2 AF7
	GPIOA->MODER |= 0x0020;  		// PA2 <-> Alternate function
	GPIOA->MODER |= 0X0080;			// PA3 <-> Alternate function

}

void USART_write(int ch){
	// wait while TX buffer is empty
	while(!(USART2->ISR & 0x0080)){}
		USART2->TDR = (ch & 0xFF);
}

void delayms(int delay){
	int i;
	for(; delay>0; delay--){
		for(i=0;i<3195;i++);
	}
}
