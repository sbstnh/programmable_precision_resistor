/*
 * stp16cp05.c
 *
 *  Created on: Sep 23, 2022
 *      Author: sebas
 */

#include "hardware/stp16cp05.h"


void STP_Init(STP_TypeDef *stp)
{
	for (uint8_t i = 0; i < STP_DEVICE_COUNT; ++i)
	{
		stp->values[i] = 0;
	}

	HAL_GPIO_WritePin(stp->oe->GPIOx, stp->oe->pin, GPIO_PIN_RESET);
}

bool STP_Get(STP_TypeDef *stp, uint8_t device, uint8_t channel)
{
	return (stp->values[device] >> channel) & 1;
}

void STP_Set(STP_TypeDef *stp, uint8_t device, uint8_t channel, bool on)
{
	if (on)
	{
		stp->values[device] |= 1L << channel;
	}
	else
	{
		stp->values[device] &= ~(1L << channel);
	}
}

void STP_Reset(STP_TypeDef *stp)
{
	for (uint8_t i = 0; i < STP_DEVICE_COUNT; ++i)
	{
		stp->values[i] = 0;
	}
}

API_StatusTypeDef STP_Transmit(STP_TypeDef *stp)
{
	if (HAL_SPI_Transmit(stp->spi, (uint8_t *)stp->values, STP_DEVICE_COUNT, 1000) != HAL_OK)
	{
		return API_HARDWARE_ERROR;
	}

	// Latch kurzzeitig deaktivieren
	HAL_GPIO_WritePin(stp->le->GPIOx, stp->le->pin, GPIO_PIN_SET);
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	HAL_GPIO_WritePin(stp->le->GPIOx, stp->le->pin, GPIO_PIN_RESET);

	return API_OK;
}
