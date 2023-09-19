/*
 * crc.c
 *
 *  Created on: Oct 22, 2022
 *      Author: sebas
 */

#include "util/crc.h"
#include "stm32g4xx.h"


extern CRC_HandleTypeDef hcrc;

uint32_t CRC_Calculate(uint8_t *data, uint16_t size)
{
	// Right now, there is only one implementation
	// If required implement software solution here
	return HAL_CRC_Calculate(&hcrc, (uint32_t *)data, size);
}

