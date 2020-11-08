#include "stm32f7xx.h"                  // Device header

/*

PA5 - SCK
PA7 - MOSI
PA4 - SS

*/

void SPI_Init(void);
void SPI_write_data(unsigned char data);

int main(void){
	// SPI device not connected in this example
}

void SPI_Init(void){
	
	// Initialize the GPIO
	RCC->AHB1ENR |= 1UL;					// GPIOA clock access
	RCC->APB2ENR |= 1<<12;					// SPI1 clock access
	
	GPIOA->MODER &= ~(unsigned int)0x0000FF00;		// Clear PA-5, 7
	GPIOA->MODER |= 0x00008800;				// Alternate function PA-5, 7
	
	GPIOA->AFR[0] &= ~(unsigned int)0xF0F00000;		// Clear PA-5, 7
	GPIOA->AFR[0] |= 0x50500000;				// AF5 PA-5, 7
	
	GPIOA->MODER &= ~(unsigned int)0x00000300;		// Clear PA-4
	GPIOA->MODER |= 0x00000100;				// PA-4 as output (SS)
	
	// Initailize SPI
	SPI1->CR1 |= (1<<11)|(1<<4)|(1<<3);			// 8 bit data mode, baud rate
	SPI1->CR2 = 0;
	SPI1->CR1 |= (1<<6);					// SPI enable
}

void SPI_write_data(unsigned char data){
	
	while(!(SPI1->SR & 2)){}		// wait till TXE buffer is empty
	GPIOA->BSRR = 0x00100000;		// Reset PA-4 Slave Select
	SPI1->DR = data;						// not writing in memory map of slave right now
	while(SPI1->SR & 0x80){}		// Bus busy flag TX completion
	GPIOA->BSRR = 0x00000010;		// Set PA-4 Slave Select
}
