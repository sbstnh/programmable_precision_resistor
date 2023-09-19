/**
 * @file    calibration.c
 * @author  sebas
 * @date    20.10.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "calibration/calibration.h"
#include "util/util.h"
#include "string.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/


int8_t CAL_ConvertToSetup(int8_t decade, int8_t resistor)
{
	return decade * DEC_RES_COUNT + resistor;
}


int8_t CAL_ConvertToResistor(int8_t setup)
{
	return setup % DEC_RES_COUNT;
}


uint8_t CAL_ConvertToDecade(int8_t setup)
{
	int8_t shifted_setup = (setup < CAL_SETUP_4W_START) ? setup : setup - CAL_SETUP_4W_START;

	return shifted_setup / DEC_RES_COUNT;
}


int32_t CAL_IdealResistance(int8_t setup)
{
	int8_t decade = CAL_ConvertToDecade(setup);
	int8_t resistor = CAL_ConvertToResistor(setup);

	return resistor * UTIL_Power(10, decade + PRES_RESOLUTION - PRES_DEC_COUNT);
}


void CAL_Reset(volatile CALDATA_TypeDef *cal_data)
{
	uint32_t ideal;

	cal_data->CALIBRATED = false;

	for (uint8_t decade = 0; decade < PRES_DEC_COUNT; decade++)
	{
		for (uint8_t resistor = 0; resistor < DEC_RES_COUNT; resistor++)
		{
			int8_t setup = CAL_ConvertToSetup(decade, resistor);
			ideal = CAL_IdealResistance(setup);

			cal_data->CAL_VAL_2W[setup] = ideal;
			cal_data->CAL_VAL_4W[setup] = ideal;
		}
	}
}


API_StatusTypeDef CAL_GetValue(volatile CALDATA_TypeDef *cal_data, int8_t setup, int32_t *value)
{
	if (setup < 0 || setup >= CAL_SETUPS_TOTAL)
	{
		return API_ERROR;
	}

	*value = (setup < CAL_SETUP_4W_START) ? cal_data->CAL_VAL_2W[setup] : cal_data->CAL_VAL_4W[setup - CAL_SETUP_4W_START];

	return API_OK;
}


API_StatusTypeDef CAL_SetValue(volatile CALDATA_TypeDef *cal_data, int8_t setup, uint32_t cal_val)
{
	if (setup < 0 || setup >= CAL_SETUPS_TOTAL)
	{
		return API_ERROR;
	}

	if (CAL_ValidateValueForSetup(setup, cal_val) != API_OK)
	{
		return API_ERROR;
	}

	if (setup < CAL_SETUP_4W_START)
	{
		cal_data->CAL_VAL_2W[setup] = cal_val;
	}
	else
	{
		cal_data->CAL_VAL_4W[setup - CAL_SETUP_4W_START] = cal_val;
	}

	return API_OK;
}


API_StatusTypeDef CAL_ValidateValueForSetup(uint8_t setup, int32_t cal_val)
{
	int32_t ideal = CAL_IdealResistance(setup);
	int32_t tolerance = CAL_TOL_ADD + ideal / CAL_TOL_DIVISOR;

	if (cal_val < MAX(ideal - tolerance, 0) || cal_val > (ideal + tolerance))
	{
		return API_ERROR;
	}

	return API_OK;
}


API_StatusTypeDef CAL_ValidateAll(volatile CALDATA_TypeDef *cal_data)
{
	for (int8_t setup = 0; setup < CAL_SETUPS_PER_MODE; setup++)
	{
		if (CAL_ValidateValueForSetup(setup, cal_data->CAL_VAL_2W[setup]) != API_OK)
		{
			return API_ERROR;
		}

		if (CAL_ValidateValueForSetup(setup, cal_data->CAL_VAL_4W[setup]) != API_OK)
		{
			return API_ERROR;
		}
	}

	return API_OK;
}


/* Private functions ---------------------------------------------------------*/
