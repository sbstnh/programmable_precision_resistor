/*
 * output_def.c
 *
 *  Created on: Aug 22, 2021
 *      Author: sebas
 */

#include "hardware/output_def.h"
#include "main.h"

/* Digital general purpose outputs for the relay control ----------------------*/

const IO_TypeDef OUT_RLY_PWR = { RLY_PWR_GPIO_Port, RLY_PWR_Pin };
const IO_TypeDef OUT_RLY_OE = { RLY_OE_GPIO_Port, RLY_OE_Pin };
const IO_TypeDef OUT_RLY_LE = { RLY_LE_GPIO_Port, RLY_LE_Pin };
