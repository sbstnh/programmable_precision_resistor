/*
 * stp16cp05_def.c
 *
 *  Created on: 13.10.2022
 *      Author: sebas
 */

#include "hardware/stp16cp05_def.h"
#include "hardware/output_def.h"


extern SPI_HandleTypeDef hspi1;


STP_TypeDef STP =
{
		.spi = &hspi1,
		.oe = &OUT_RLY_OE,
		.le = &OUT_RLY_LE,
		.values = { 0, 0, 0 }
};
