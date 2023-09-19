/*
 * input_def.h
 *
 *  Created on: Aug 22, 2021
 *      Author: sebas
 */

#ifndef INC_HARDWARE_INPUT_DEF_H_
#define INC_HARDWARE_INPUT_DEF_H_

#include "hardware/input_output.h"

/* Digital general purpose inputs for the UI interrupt -----------------------*/

extern const IO_TypeDef IN_INT_UI;

/* Digital general purpose inputs for EXT interface --------------------------*/

extern const IO_TypeDef IN_EXTI1;
extern const IO_TypeDef IN_EXTI2;

#endif /* INC_HARDWARE_INPUT_DEF_H_ */
