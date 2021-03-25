typedef struct __attribute__((__packed__)){
  unsigned int  id;       // Arbitration Id
  unsigned char data[8];  // Data field
  unsigned int  len;      // Length of data field in bytes
	unsigned int  format; // 0 - STANDARD, 1- EXTENDED IDENTIFIER
	unsigned int  type;   // 0 - DATA FRAME, 1 - REMOTE FRAME
} CAN_msg;

extern CAN_msg CAN_TxMsg;   // CAN messge for sending
extern CAN_msg CAN_RxMsg;   // CAN message for receiving

extern unsigned int  CAN1_TxRdy;  // CAN HW ready to transmit a message
extern unsigned int  CAN1_RxRdy;  // CAN HW received a message

#define CAN_ID_STD	0x00000001U
#define CAN_ID_EXT	0x00000004U

#define STANDARD_ID	0x00000000U
#define EXTENDED_ID	0x00000001U

#define DATA_FRAME	 0x00000000U
#define REMOTE_FRAME 0x00000001U

void CAN1_Init(void);
void CAN1_ready(void);
void CAN1_Tx(CAN_msg *msg);
void CAN1_Rx(CAN_msg *msg);
void CAN1_Tx_Info(unsigned int id,
                    char* mes,
				    unsigned int len,
					unsigned int format,
					unsigned int type);
void CAN1_Filter(unsigned int id, unsigned int format);
void Interrupt_Init(void);
void CAN1_TX_IRQHandler(void);
void CAN1_RX0_IRQHandler(void);

void GPIOA_Init(void);
void LED_toggle(unsigned h);
void sysTickDelayMs(int n);
