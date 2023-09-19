/*
 * decade.c
 *
 *  Created on: 27.10.2022
 *      Author: sebas
 */

#include "prog_res/decade.h"
#include "prog_res/resistance.h"
#include "calibration/cal_mode.h"
#include "util/util.h"

uint8_t DEC_FindClosestCalibratedResistance(DEC_TypeDef *decade, uint32_t value, CAL_Mode_TypeDef cal_mode)
{
	uint8_t index = 0;
	uint32_t current = RES_GetResistance(&decade->resistances[0], cal_mode);
	uint32_t abs_array;
	uint32_t abs_current;
	uint32_t calibrated;

	for (uint8_t i = 0; i < COUNT_OF(decade->resistances); i++)
	{
		calibrated = RES_GetResistance(&decade->resistances[i], cal_mode);

		abs_array = value > calibrated ? value - calibrated : calibrated - value;
		abs_current = value > current ? value - current : current - value;
		if (abs_array < abs_current)
		{
			current = calibrated;
			index = i;
		}
	}

	return index;
}
