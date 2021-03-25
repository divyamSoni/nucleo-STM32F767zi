#include "stm32f7xx.h"  // Device header
#include "can.h"

CAN_msg	CAN_TxMsg;      // CAN messge for sending
CAN_msg CAN_RxMsg;      // CAN message for receiving

unsigned int  CAN1_TxRdy = 0;  // CAN HW ready to transmit a message
unsigned int  CAN1_RxRdy = 0;	// CAN HW received a message

void CAN1_ready(void){
    while((CAN1->TSR & 1<<26) == 0){} // Transmit mailbox 0 is empty
    CAN1_TxRdy = 1;
}

void CAN1_Tx_Info(unsigned int id, char* mes,
				unsigned int len, unsigned int format,
				unsigned int type){
	CAN_TxMsg.id = id;
	for(int i=0;i<8;i++){
		CAN_TxMsg.data[i] = mes[i];
	}
	CAN_TxMsg.len = len;
	CAN_TxMsg.format = format;
	CAN_TxMsg.type = type;
}

void CAN1_Init(void){
	LED_toggle(0x1);       // Green LED HIGH
	RCC->APB1ENR |= 1<<25;		// Enable clock access to CAN1

	CAN1->MCR |= 1<<15;			// Master reset of bxCAN
	while(!(CAN1->MSR & 2)){}	// Wait for bxCAN to sleep

	CAN1->MCR &= ~(1UL<<1);		// Wake up bxCAN
	while(!(CAN1->MSR & 2)){}	// Wait for bxCAN to wake up

	CAN1->MCR |= 1;				// Put CAN in INIT mode
	while(!(CAN1->MSR & 1)){}	// Wait for CAN to go in INIT mode

	/**	PCLK
			16 MHz
		*	Bit-Rate 	accuracy	Pre-scaler	Seg1_tq
			250			0.0000		4			16
		*	(Prop_Seg+Phase_Seg1)	Seg 2	Sample Point
			13						2		87.5          */
	CAN1->BTR |= 0x001c0003;			// Time quanta and segment

	CAN1->BTR |= (unsigned int)0x1<<30;	// CAN1 in loopback mode

	CAN1_Filter(CAN_TxMsg.id, CAN_TxMsg.format);

	CAN1->MCR &= ~1UL;		// Switch to Normal Mode
	while(CAN1->MSR & 1){}	// Wait for Init exit
	LED_toggle(0x1);        // Green LED LOW
}

void CAN1_Filter(unsigned int id, unsigned int format){
	static unsigned short CAN_filterIdx = 0;
	unsigned int CAN_msgId = 0;

	if(CAN_filterIdx>13){
		return;
	}

	CAN1->FMR |= 1;					// Filter mode initialization
	while(!(CAN1->FMR & 1UL)){}		// Wait for initialization

	// Setup identifier information
  	if(format == 0){ 	// Standard ID
        CAN_msgId = (unsigned int)id<<21;
	}
  	else{     			// Extended ID
      CAN_msgId = (unsigned int)(id<<3) | 0x00000004U;
  	}

	CAN1->FMR  |=  0x01; 	// Set Init mode for filter banks
	CAN1->FA1R &=  (unsigned int)1<<CAN_filterIdx; 	// Deactivate filter_x

	// Initialize filter
	// Assigning filter_x to CAN1
	CAN1->FA1R &= ~(unsigned int)1<<CAN_filterIdx; // Deactivate filter_x
	CAN1->FMR |= (unsigned int)1<<CAN_filterIdx;   // filter_x assigned to CAN1
	CAN1->FM1R |= (unsigned int)1<<CAN_filterIdx;  // 2, 32-bt reg of filter bank 0 in identifier list mode
	CAN1->FS1R |= (unsigned int)1<<CAN_filterIdx;  // Single 32-bit scale config for filter_x

	CAN1->sFilterRegister[CAN_filterIdx].FR1 = CAN_msgId; // 32-bit identifier
	CAN1->sFilterRegister[CAN_filterIdx].FR2 = CAN_msgId; // 32-bit identifier

	RCC->APB1ENR &= ~(1UL<<26);	           // Disable clock to CAN2
	CAN2->MSR |= 1;                        // Set INRQ on CAN2
	CAN1->FFA1R &= ~(unsigned int)0x01;    // FIFO x assigned to CAN1

	CAN1->FA1R |= (unsigned int)1<<CAN_filterIdx;  // Activate filter_x
	CAN1->FMR &= ~1UL;		   // Active filter mode
	while(CAN1->FMR & 1UL){}   // Exit filter init
	CAN_filterIdx++;
}

void CAN1_Tx(CAN_msg *msg){
	LED_toggle(0x4000); // RED LED HIGH
	CAN1->sTxMailBox[0].TIR = (unsigned int)0;
	/*	Before transmission
	1. Select one empty mailbox
	2. Set up the identifier extension
	3. Set up identifier number
	3. Set up data length code
	4. Set up data
	*/
	while(!(CAN1->TSR & 1<<26)){}			// Wait for transmit mailbox 0 to be empty
	CAN1->sTxMailBox[0].TIR &= ~(1UL<<2);	// Standard identifier
	CAN1->sTxMailBox[0].TIR &= ~(1UL<<1);	// Date Frame
	CAN1->sTxMailBox[0].TIR |= msg->id<<21;	// Identifier number

	CAN1->sTxMailBox[0].TDHR = ((unsigned int)msg->data[7]<<24 	|
								(unsigned int)msg->data[6]<<16 	|
								(unsigned int)msg->data[5]<<8	|
								(unsigned int)msg->data[4]);

	CAN1->sTxMailBox[0].TDLR = ((unsigned int)msg->data[3]<<24 	|
								(unsigned int)msg->data[2]<<16 	|
								(unsigned int)msg->data[1]<<8	|
								(unsigned int)msg->data[0]);

	CAN1->sTxMailBox[0].TDTR &= ~(unsigned int)0xF; // reset DLC
	CAN1->sTxMailBox[0].TDTR |= msg->len & 0xF;   // 1 byte data
	CAN1->sTxMailBox[0].TIR |= 1;      // Req transmission

	LED_toggle(0x4000);	// RED LED LOW
}

void CAN1_Rx(CAN_msg *msg){
	if((CAN1->sFIFOMailBox[0].RIR & 0x00000004U) == 0){
		CAN_RxMsg.format = STANDARD_ID;
	}
	else{
		CAN_RxMsg.format = EXTENDED_ID;
	}

	if((CAN1->sFIFOMailBox[0].RIR & 0x00000002U) == 0){
		CAN_RxMsg.type = DATA_FRAME;
	}
	else{
		CAN_RxMsg.type = REMOTE_FRAME;
	}

	CAN_RxMsg.id = (CAN1->sFIFOMailBox[0].RIR>>21);

	msg->len 		 = (unsigned int)0x0000000F & CAN1->sFIFOMailBox[0].RDTR;

	msg->data[0] = (unsigned int)0x000000FF & CAN1->sFIFOMailBox[0].RDLR;
	msg->data[1] = (unsigned int)0x000000FF & CAN1->sFIFOMailBox[0].RDLR>>8;
	msg->data[2] = (unsigned int)0x000000FF & CAN1->sFIFOMailBox[0].RDLR>>16;
	msg->data[3] = (unsigned int)0x000000FF & CAN1->sFIFOMailBox[0].RDLR>>24;
	msg->data[4] = (unsigned int)0x000000FF & CAN1->sFIFOMailBox[0].RDHR;
	msg->data[5] = (unsigned int)0x000000FF & CAN1->sFIFOMailBox[0].RDHR>>8;
	msg->data[6] = (unsigned int)0x000000FF & CAN1->sFIFOMailBox[0].RDHR>>16;
	msg->data[7] = (unsigned int)0x000000FF & CAN1->sFIFOMailBox[0].RDHR>>24;

	CAN1->RF0R |= 1UL<<5;      // Release FIFO 0 mailbox
}

void Interrupt_Init(void){
	__disable_irq();	// Disable Global Interrupt

	CAN1->IER |= 0x01;	// Transmit mailbox0 empty interrupt enabled
	CAN1->IER |= 0x02;	// FIFO msg pending interrupt

	NVIC_EnableIRQ(CAN1_TX_IRQn);	// Interrupt Handler for CAN_Tx
	NVIC_EnableIRQ(CAN1_RX0_IRQn);	// Interrupt Handler for CAN_Rx

	__enable_irq();		// Enable Global Interrupt
}

void CAN1_TX_IRQHandler(void){
    if(CAN1->TSR & 0x01){    // Request completed mbx 0
        CAN1->TSR |= 0x01;     				// Reset request complete mbx 0
        CAN1->IER &= ~(unsigned int)1UL;  	// Disable  TME interrupt
		CAN1_TxRdy = 1;
    }
}

void CAN1_RX0_IRQHandler(void){
    if(CAN1->RF0R & 0x03){    // Message pending ?
	   CAN1_Rx(&CAN_RxMsg);   // Read the message
        CAN1_RxRdy = 1;       // Set Receive flag
    }
}
