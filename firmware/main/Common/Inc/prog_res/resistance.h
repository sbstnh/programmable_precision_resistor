/*
 * resistance.h
 *
 *  Created on: 18.10.2022
 *      Author: sebas
 */

#ifndef INC_APPLICATION_RESISTANCE_H_
#define INC_APPLICATION_RESISTANCE_H_

#include <stdbool.h>
#include "calibration/cal_mode.h"
#include "prog_res/relay.h"


typedef struct
{
	const uint8_t number;

	const uint32_t nominal;	//!< ideal resistance in mOhm
	uint32_t calibrated_2w;	//!< calibrated resistance in mOhm
	uint32_t calibrated_4w;	//!< calibrated resistance in mOhm

	const uint8_t i_factor;		//!< multiplier for current limit

	RLY_TypeDef * relay_tap;
	RLY_TypeDef * relay_not_plus_one;

}  RES_TypeDef;

uint32_t RES_GetResistance(RES_TypeDef *resistance, CAL_Mode_TypeDef cal_mode);


#endif /* INC_APPLICATION_RESISTANCE_H_ */
