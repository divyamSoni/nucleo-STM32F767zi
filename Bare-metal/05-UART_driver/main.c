/*	
		RCC->APB1ENR bit 19 for UART4
		PA0 <-> AF8 <-> UART4_TX
*/

#include "stm32f7xx.h"

void UART2_Init(void);
void UART_write(int ch);
void delayms(int delay);

char chara = '0';

void UART4_Init(void){
	
	RCC->APB1ENR |= 0x80000; 		// Enables clock access to UART4
	RCC->AHB1ENR |= 1;        	// Enables clock access to GPIOA
	
	UART4->BRR = 0x0682; 				// 9600 @16 MHz
	UART4->CR1 |= 0x0008;				// Enable Tx
	UART4->CR1 |= 1;     				// Enable UART
	
	GPIOA->AFR[0] = 8; 					// Enabling UART4 PA0 AF8
	GPIOA->MODER |= 2;  				// PA0 <-> Alternate function

}

void UART_write(int ch){
	// wait while TX buffer is empty
	while(!(UART4->ISR & 0x0080)){}
		chara = UART4->TDR;
		UART4->TDR = (ch & 0x1FF);
		
}

void delayms(int delay){
	int i;
	for(; delay>0; delay--){
		for(i=0;i<3195;i++);
	}
}


int main(void){
	
	UART4_Init();
	
	while(1){
		UART_write('H');
		delayms(1000);
		UART_write('i');
		delayms(1000);
	}	
}
