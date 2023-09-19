/*
 * input.h
 *
 *  Created on: Sep 29, 2022
 *      Author: sebas
 */

#ifndef INC_HARDWARE_INPUT_OUTPUT_H_
#define INC_HARDWARE_INPUT_OUTPUT_H_

#include "stm32g4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct
{
	GPIO_TypeDef *GPIOx;
	uint16_t pin;

	bool inverted;
} IO_TypeDef;


#endif /* INC_HARDWARE_INPUT_OUTPUT_H_ */
