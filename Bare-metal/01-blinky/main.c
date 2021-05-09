/***************************
** Use a loop delay to		**
** blink an LED						**
** 1. LED2(Blue) <-> PB7	**
** 2. AHB1 <-> GPIOB			**
** 3. RCC->AHB1ENR				**
***************************/

#include "stm32f7xx.h"			// Device header

void delayMs(int delay);

int main(void)
{
	RCC->AHB1ENR |= 0x2;			// Enable clock access to GPIOB
	GPIOB->MODER |= 0x4000;		// GPIOB_PIN_7 output mode

	while(1)
	{
		GPIOB->ODR |= 1UL << 7;			// LED2 ON
		delayMs(1000);							// Loop delay
		GPIOB->ODR &= ~(1UL << 7);	// LED2 OFF
		delayMs(1000);							// Loop delay
	}
}


void delayMs(int delay)
{
	volatile int i;
	for(; delay>0; delay--){
		for(i=0; i<3195; i++);
	}
}
