/*
 * decade.h
 *
 *  Created on: 17.10.2022
 *      Author: sebas
 */

#ifndef INC_HARDWARE_DECADE_H_
#define INC_HARDWARE_DECADE_H_

#include "util/api.h"
#include "prog_res/relay.h"
#include "prog_res/resistance.h"

#define DEC_RES_COUNT				10
#define DEC_MIN_RES_SEL				0
#define DEC_MAX_RES_SEL				9

typedef struct
{
	const uint8_t order;						//!< Decade for values from n * 10^order with n in {1, .., 9}
	const uint32_t i_0;							//!< Maximum current of a single resistor (P_0 / R_0) [1uA]

	RES_TypeDef resistances[DEC_RES_COUNT]; //!< Resistance array

	RLY_TypeDef * relay_bypass;				//!< Relay used to bypass upper decades

	uint8_t next_selection;
	uint8_t selection;
} DEC_TypeDef;

uint8_t DEC_FindClosestCalibratedResistance(DEC_TypeDef *decade, uint32_t value, CAL_Mode_TypeDef cal_mode);

#endif /* INC_HARDWARE_DECADE_H_ */
