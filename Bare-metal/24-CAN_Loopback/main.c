#include "can.h"
#include "stm32f7xx.h"      // Device header

/*	Configure the CAN in loopback mode
 *	with mailbox 0, when message is
 *	received it is acknowledged by
 *	blinking an LED
 */

int main(){
	// Message info to be transmitted
	CAN1_Tx_Info(0x15A,"_canBus_",8,0,0);
	CAN1_ready();
	GPIOA_Init();
	CAN1_Init();
	Interrupt_Init();

	while(1){
        if(CAN1_TxRdy){
            CAN1_TxRdy = 0;
            CAN1_Tx(&CAN_TxMsg);
        }
		sysTickDelayMs(500);
        if(CAN1_RxRdy){
            CAN1_RxRdy = 0;
            CAN1_Rx(&CAN_RxMsg);
        }
		for(int i = 0; i<8 ; i++){
            if(CAN_TxMsg.data[i] == CAN_RxMsg.data[i]){
                LED_toggle(0x80); // BLUE LED
			}
		}
	}
}

void GPIOA_Init(void){
	/*	PA11 - CAN1_Rx - AF9
		PA12 - CAN1_Tx - AF9  */
	RCC->AHB1ENR |= 3;             // Enable clock access to GPIOA,B

	GPIOB->MODER |= 0x1;           // LD1 <-> PB0  <-> Red     <-> 0x4000
	GPIOB->MODER |= 0x4000;        // LD2 <-> PB7  <-> Blue	   <-> 0x0080
	GPIOB->MODER |= 0x010000000;   // LD3 <-> PB14 <-> Green   <-> 0x0001

	GPIOA->AFR[1] |= 0x99000;              // Enabling CAN1 on PA11, PA12
	GPIOA->MODER |= (1UL<<23)|(1UL<<25);   // PA11, PA12 <-> Alternate Function

	GPIOA->PUPDR |= 1UL<<22;       // Pullup PA11/CAN_Rx - For Recessive state
}

void LED_toggle(unsigned h){
	GPIOB->ODR ^= h;
	sysTickDelayMs(250);
}

void sysTickDelayMs(int n){
    // Clock 16 MHz
	SysTick->LOAD = 16000; 	// Load with number of clocks per milisecond
	SysTick->VAL = 0;		// Clear current value register
	SysTick->CTRL = 0x5;	// Enable SysTick

	for(int i = 0; i<n; i++){
	   // Wait until the count flag is set
	   while((SysTick->CTRL & 0x10000) == 0){}
	}
	SysTick->CTRL = 0;
}
