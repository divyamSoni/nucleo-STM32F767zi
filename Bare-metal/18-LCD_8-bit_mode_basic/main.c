#include "rg2004a.h"

/**********************
** PD0 - PD7 = D0 - D7
** PB15 	 = R/S
** PB13		 = R/W
** PB12		 = EN
**********************/

int main(void){
	GPIOInit();
	lcd_init();
	
	while(1){
		lcd_command(1);			// Display clear
		lcd_write("RG2004A:20X4 LCD", l1);
		lcd_write("Hello World!", l2);
		lcd_write("Hitachi: HD44780", l3);
		lcd_write("5x8 Dot Matrix 8 bit", l4);
		sysTickDelayMs(1000);
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
	Character Font = 5x8 */
	lcd_command(0x38);	// 8 bit, 2 line, 5x8 dot
	lcd_command(0x08);	// Display off
	lcd_command(0x01);	// Display clear
	lcd_command(0x04);	// Entry mode set
	lcd_command(0x0F);	// Function set

}

void GPIOInit(void){

	RCC->AHB1ENR |= 0x0A;				      // Enable clock access to GPIO B,D
	GPIOB->MODER |= (1<<30)|(1<<26)|(1<<24);  // Set PB12,13,15 as output
	GPIOB->BSRR 	= (EN|RW)<<16;			  //  Set EN and RW low (PB12, PB13)
	GPIOD->MODER |= 0x5555;				      // Set PD0 - PD7 as output

}

void lcd_command(unsigned int command){

	GPIOB->BSRR = (RS|RW)<<16;		// RS = RW = 0
	GPIOD->ODR = command;
	GPIOB->BSRR = EN;				// E = 1
	sysTickDelayMs(50);
	GPIOB->BSRR = EN<<16;			// E = 0

}

void lcd_data(char data){

	GPIOB->BSRR = RS;				// RS = 1
	GPIOB->BSRR = RW<<16;			// RW = 0
	GPIOD->ODR = data;				// Pass data
	GPIOB->BSRR = EN;				// EN = 1
	sysTickDelayMs(30);
	GPIOB->BSRR = EN<<16;			// EN = 0

}

void lcd_write(char *p, unsigned int cmd){
	lcd_command(cmd);
	for(; *p != '\0'; p++){
		lcd_data(*p);
	}
}

void sysTickDelayMs(int n){
	// Clock 16 MHz
	SysTick->LOAD = 16000; 		// Load with number of clocks per milisecond
	SysTick->VAL = 0;		    // Clear current value register
	SysTick->CTRL = 0x5;		// Enable SysTick

	for(int i = 0; i<n; i++){
		// Wait until the count flag is set
		while((SysTick->CTRL & 0x10000) == 0){}
	}
	SysTick->CTRL = 0;
}
