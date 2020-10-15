#include "stm32f7xx.h"                  // Device header

/*

PD0 - PD7 = D0 - D7 
PB15 				= R/S
PB13				= R/W
PB12				= EN

*/

static unsigned RS = 0x8000;			// 1000 0000 0000 0000
static unsigned RW = 0x2000;			// 0010 0000 0000 0000
static unsigned EN = 0x1000;			// 0001 0000 0000 0000

void GPIOInit(void);
void lcd_command(unsigned char command);
void lcd_data(char data);
void lcd_init(void);
void sysTickDelayMs(int n);

int main(void){
	GPIOInit();
	lcd_init();
	
	while(1){
		
		lcd_command(0x80);			// Write on Line 1
		lcd_data('R');
		lcd_data('S');
		lcd_data('2');
		lcd_data('0');
		lcd_data('0');
		lcd_data('4');
		lcd_data('a');
		lcd_data(':');
		lcd_data(' ');
		lcd_data('2');
		lcd_data('0');
		lcd_data('x');
		lcd_data('4');
		lcd_data(' ');
		lcd_data('L');
		lcd_data('C');
		lcd_data('D');
		
		lcd_command(0xc0);			// Write on Line 2
		lcd_data('H');
		lcd_data('e');
		lcd_data('l');
		lcd_data('l');
		lcd_data('o');
		lcd_data(' ');
		lcd_data('W');
		lcd_data('o');
		lcd_data('r');
		lcd_data('l');
		lcd_data('d');
		lcd_data('!');
	
		lcd_command(0x94);			// Write on Line 3
		lcd_data('H');
		lcd_data('i');
		lcd_data('t');
		lcd_data('a');
		lcd_data('c');
		lcd_data('h');
		lcd_data('i');
		lcd_data(':');
		lcd_data(' ');
		lcd_data('H');
		lcd_data('D');
		lcd_data('4');
		lcd_data('4');
		lcd_data('7');
		lcd_data('8');
		lcd_data('0');
		
		lcd_command(0xd4);			// Write on Line 4
		lcd_data('5');
		lcd_data('x');
		lcd_data('8');
		lcd_data(' ');
		lcd_data('D');
		lcd_data('o');
		lcd_data('t');
		lcd_data(' ');
		lcd_data('M');
		lcd_data('a');
		lcd_data('t');
		lcd_data('r');
		lcd_data('i');
		lcd_data('x');
		lcd_data(' ');
		lcd_data('8');
		lcd_data(' ');
		lcd_data('b');
		lcd_data('i');
		lcd_data('t');
		
		
		sysTickDelayMs(1000);
		lcd_command(1);					// Display clear
	}
}

void lcd_init(void){
	
	// Init sequence
	sysTickDelayMs(30);
	lcd_command(0x30);
	sysTickDelayMs(10);
	lcd_command(0x30);
	sysTickDelayMs(10);
	lcd_command(0x30);
	
	/* RG2004a 20x4 LCD
	Character Font = 5x8
	*/
	lcd_command(0x38);	// 8 bit, 2 line, 5x8 dot
	lcd_command(0x08);	// Display off
	lcd_command(0x01);	// Display clear
	lcd_command(0x04);	// Entry mode set
	lcd_command(0x0F);	// Function set

}

void GPIOInit(void){
	
	RCC->AHB1ENR |= 0x0A;				// Enable clock access to GPIO B,D
	GPIOB->MODER |= (1<<30)|(1<<26)|(1<<24); 	// Set PB12,13,15 as output
	GPIOB->BSRR 	= (EN|RW)<<16;			// Set EN and RW low (PB12, PB13)
	GPIOD->MODER |= 0x5555;				// Set PD0 - PD7 as output

}

void lcd_command(unsigned char command){

	GPIOB->BSRR = (RS|RW)<<16;			// RS = RW = 0
	GPIOD->ODR = command;
	GPIOB->BSRR = EN;				// E = 1
	sysTickDelayMs(50);
	GPIOB->BSRR = EN<<16;				// E = 0

}

void lcd_data(char data){
	
	GPIOB->BSRR = RS;					// RS = 1
	GPIOB->BSRR = RW<<16;					// RW = 0
	GPIOD->ODR = data;					// Pass data
	GPIOB->BSRR = EN;					// EN = 1
	sysTickDelayMs(30);
	GPIOB->BSRR = EN<<16;					// EN = 0

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
