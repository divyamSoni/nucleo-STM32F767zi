// 1. LED2(Blue) <-> PB7
// 2. AHB1 <-> GPIOB
// 3. RCC->AHB1ENR
// 4. GPIOx_MODER
// 5. GPIOx_ODR

#include "stm32f7xx.h"			// Device header

void delayMs(int delay);

int main(void)
{
	RCC->AHB1ENR |= 0x2;
	GPIOB->MODER |= 0x4000;

	while(1)
	{
		GPIOB->ODR = 0x80;
		delayMs(100);
		GPIOB->ODR &=~ 0x80;
		delayMs(100);
	}
}


void delayMs(int delay)
{
	int i;
	for(; delay>0; delay--){
		for(i=0; i<3195; i++);
	}
}
