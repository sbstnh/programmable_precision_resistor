/*
 * resistance.c
 *
 *  Created on: 30.10.2022
 *      Author: sebas
 */


#include "prog_res/resistance.h"


uint32_t RES_GetResistance(RES_TypeDef *resistance, CAL_Mode_TypeDef cal_mode)
{
	switch (cal_mode)
	{
		default:
		case CAL_MODE_UNCAL:
			return resistance->nominal;
		case CAL_MODE_2W:
			return resistance->calibrated_2w;
		case CAL_MODE_4W:
			return resistance->calibrated_4w;
	}
}
