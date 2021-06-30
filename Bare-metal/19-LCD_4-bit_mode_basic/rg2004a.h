#include <stdio.h>
#include "stm32f7xx.h"                  // Device header

// LCD specific hex codes
static unsigned RS = 0x8000;			// 1000 0000 0000 0000
static unsigned RW = 0x2000;			// 0010 0000 0000 0000
static unsigned EN = 0x1000;			// 0001 0000 0000 0000

static unsigned int l1 = 0x0080;		// Line 1
static unsigned int l2 = 0x00c0;		// Line 1
static unsigned int l3 = 0x0094;		// Line 1
static unsigned int l4 = 0x00d4;		// Line 1

// Function Prototypes
void GPIOInit(void);
void lcd_write(char *p, unsigned int cmd);
void lcd_command(unsigned int command);
void lcd_data(char data);
void lcd_init(void);
void sysTickDelayMs(int n);
