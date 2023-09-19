/*
 * input_def.c
 *
 *  Created on: Sep 29, 2022
 *      Author: sebas
 */

#include "hardware/output_def.h"
#include "main.h"


/* Digital general purpose inputs for the UI interrupt -----------------------*/

const IO_TypeDef IN_INT_UI = { INT_UI_GPIO_Port, INT_UI_Pin };

/* Digital general purpose inputs for EXT interface --------------------------*/

const IO_TypeDef IN_EXTI1 = { GPIO_EXT_IN1_GPIO_Port, GPIO_EXT_IN1_Pin };
const IO_TypeDef IN_EXTI2 = { GPIO_EXT_IN2_GPIO_Port, GPIO_EXT_IN2_Pin };

