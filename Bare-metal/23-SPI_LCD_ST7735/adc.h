#ifndef __ADC_H
#define __ADC_H

#include "stm32f7xx_hal_conf.h"         // Keil::Device:STM32Cube Framework:Classic
#include "stm32f7xx_hal_adc.h"

void ADCI_Init(void);
extern ADC_HandleTypeDef hadc1;

#endif