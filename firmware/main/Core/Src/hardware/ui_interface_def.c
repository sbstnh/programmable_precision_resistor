/*
 * ui_interface_def.c
 *
 *  Created on: Nov 6, 2022
 *      Author: sebas
 */


#include "hardware/ui_interface_def.h"

extern I2C_HandleTypeDef hi2c1;

UIIF_TypeDef UIIF =
{
		.hi2c = &hi2c1,
		.i2c_address = UIIF_DEVICE_ADDRESS
};
