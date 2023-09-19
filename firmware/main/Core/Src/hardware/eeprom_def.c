/**
 * @file    eeprom_def.c
 * @author  sebas
 * @date    20.10.2022
 * @brief
 */


#include "hardware/eeprom_def.h"

extern I2C_HandleTypeDef hi2c1;

EEPR_TypeDef EEPROM =
{
		.i2c = &hi2c1,
		.device_address = EEPR_DEVICE_ADDRESS
};
