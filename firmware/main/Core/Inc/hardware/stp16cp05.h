/*
 * stp16cp05.h
 *
 *  Created on: Sep 23, 2022
 *      Author: sebas
 */

#ifndef INC_STP16CP05_H_
#define INC_STP16CP05_H_

#include <stdbool.h>
#include <stdint.h>
#include "stm32g4xx_hal.h"
#include "util/api.h"
#include "hardware/input_output.h"

#define STP_DEVICE_COUNT		3

typedef struct
{
	SPI_HandleTypeDef *spi;
	const IO_TypeDef * oe;
	const IO_TypeDef * le;
	uint16_t values[STP_DEVICE_COUNT];
} STP_TypeDef;

void STP_Init(STP_TypeDef *stp);
bool STP_Get(STP_TypeDef *stp, uint8_t device, uint8_t channel);
void STP_Set(STP_TypeDef *stp, uint8_t device, uint8_t channel, bool on);
void STP_Reset(STP_TypeDef *stp);
API_StatusTypeDef STP_Transmit(STP_TypeDef *stp);


#endif /* INC_STP16CP05_H_ */
