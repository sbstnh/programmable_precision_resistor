/**
 * @file    scpi_system_temp_def.c
 * @author  sebas
 * @date    Nov 12, 2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include <math.h>

#include "communication/scpi_system_def.h"
#include "communication/scpi_util.h"

#include "hardware/kty82_sensor.h"

#include "application/app_system.h"

/* Private defines -----------------------------------------------------------*/

#define SCPI_SYST_TEMP_SENS_TEMP1		0
#define SCPI_SYST_TEMP_SENS_TEMP2		1
#define SCPI_SYST_TEMP_SENS_AVERAGE		2
#define SCPI_SYST_TEMP_SENS_ALL			3

/* Private typedef -----------------------------------------------------------*/

scpi_choice_def_t temp_source[] = {
	{ "TEMPerature", TEMP_SEL_1 },
	{ "TEMPerature1", TEMP_SEL_1 },
    { "TEMPerature2", TEMP_SEL_2 },
	{ "AVERage", TEMP_SEL_AVG },
	{ "ALL", TEMP_SEL_ALL },
    SCPI_CHOICE_LIST_END /* termination of option list */
};

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

scpi_result_t SCPI_CMD_SYST_TEMP_IMMediate_Q(scpi_t *context)
{
	SCPI_GUARD_RLSTATE(context);

	int32_t choice = SCPI_SYST_TEMP_SENS_AVERAGE;

	if (SCPI_ParamChoice(context, temp_source, &choice, FALSE) || !SCPI_ParamErrorOccurred(context))
	{
		float temp = APP_Get_SystemTempImmediate(choice);

		if (temp == NAN)
		{
			RETURN_WITH_ILLEGAL_PARAMETER_VALUE();
		}

		SCPI_ResultFloat(context, temp);
		return SCPI_RES_OK;
	}

	return SCPI_RES_ERR;
}

scpi_result_t SCPI_CMD_SYST_TEMP_MINimum_Q(scpi_t *context)
{
	SCPI_GUARD_RLSTATE(context);

	int32_t choice = SCPI_SYST_TEMP_SENS_AVERAGE;

	if (SCPI_ParamChoice(context, temp_source, &choice, FALSE) || !SCPI_ParamErrorOccurred(context))
	{
		float temp = APP_Get_SystemTempMinimum(choice);

		if (temp == NAN)
		{
			RETURN_WITH_ILLEGAL_PARAMETER_VALUE();
		}


		SCPI_ResultFloat(context, temp);
		return SCPI_RES_OK;
	}

	return SCPI_RES_ERR;
}

scpi_result_t SCPI_CMD_SYST_TEMP_MAXimum_Q(scpi_t *context)
{
	SCPI_GUARD_RLSTATE(context);

	int32_t choice = SCPI_SYST_TEMP_SENS_AVERAGE;

	if (SCPI_ParamChoice(context, temp_source, &choice, FALSE) || !SCPI_ParamErrorOccurred(context))
	{
		float temp = APP_Get_SystemTempInternalMaximum(choice);

		if (temp == NAN)
		{
			RETURN_WITH_ILLEGAL_PARAMETER_VALUE();
		}

		SCPI_ResultFloat(context, temp);
		return SCPI_RES_OK;
	}

	return SCPI_RES_ERR;
}

scpi_result_t SCPI_CMD_SYST_TEMP_AVERage_Q(scpi_t *context)
{
	SCPI_GUARD_RLSTATE(context);

	int32_t choice = SCPI_SYST_TEMP_SENS_AVERAGE;

	if (SCPI_ParamChoice(context, temp_source, &choice, FALSE) || !SCPI_ParamErrorOccurred(context))
	{
		float temp = APP_Get_SystemTempAverage(choice);

		if (temp == NAN)
		{
			RETURN_WITH_ILLEGAL_PARAMETER_VALUE();
		}

		SCPI_ResultFloat(context, temp);
		return SCPI_RES_OK;
	}

	return SCPI_RES_ERR;
}

scpi_result_t SCPI_CMD_SYST_TEMP_RESet(scpi_t *context)
{
	SCPI_GUARD_RLSTATE(context);

	int32_t choice = SCPI_SYST_TEMP_SENS_ALL;

	if (SCPI_ParamChoice(context, temp_source, &choice, FALSE) || !SCPI_ParamErrorOccurred(context))
	{
		if (APP_Run_SystemTempReset(choice) != API_OK)
		{
			RETURN_WITH_ILLEGAL_PARAMETER_VALUE();
		}

		return SCPI_RES_OK;
	}

	return SCPI_RES_ERR;
}

/* Private functions ---------------------------------------------------------*/
