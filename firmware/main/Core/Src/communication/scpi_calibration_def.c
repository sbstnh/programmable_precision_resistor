/**
 * @file    scpi_calibration_def.c
 * @author  sebas
 * @date    07.01.2023
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include <string.h>

#include "util/util.h"

#include "communication/scpi_calibration_def.h"
#include "communication/scpi_util.h"

#include "application/app_calibration.h"
#include "application/app_memory.h"

#include "hardware/ui_interface_def.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/


scpi_result_t SCPI_CMD_CAL_COUNt_Q(scpi_t *context)
{
	SCPI_GUARD_RLSTATE(context);
	return SCPIUTIL_ResultUInt32(context, APP_Get_CalibrationCount());
}


scpi_result_t SCPI_CMD_CAL_DATE(scpi_t *context)
{
	SCPI_GUARD_RLSTATE(context);

	char str[APP_CAL_DATE_MAX_LEN];
	size_t len;

	if (!SCPI_ParamCopyText(context, str, APP_CAL_DATE_MAX_LEN, &len, TRUE))
	{
		return SCPI_RES_ERR;
	}

	if (len < 0 || len >= APP_CAL_DATE_MAX_LEN)
	{
		RETURN_WITH_ILLEGAL_PARAMETER_VALUE();
	}

	if (APP_Set_CalibrationDate(str) != API_OK)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_CALIBRATION_FAILED);
		return SCPI_RES_ERR;
	}

	return SCPI_RES_OK;
}

scpi_result_t SCPI_CMD_CAL_DATE_Q(scpi_t *context)
{
	SCPI_GUARD_RLSTATE(context);

	const char *str = APP_Get_CalibrationDate();
	SCPI_ResultCharacters(context, str, strnlen(str, DISP_USER_TEXT_LENGTH));
	return SCPI_RES_OK;
}


scpi_result_t SCPI_CMD_CAL_SAVE(scpi_t *context)
{
	SCPI_GUARD_RLSTATE(context);

	if (APP_Run_CalibrationSave() != API_OK)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_CALIBRATION_FAILED);
		return SCPI_RES_ERR;
	}

	if (APP_Run_CalibrationApply() != API_OK)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_CALIBRATION_MEMORY_LOST);
		return SCPI_RES_ERR;
	}

	return SCPI_RES_OK;
}


scpi_result_t SCPI_CMD_CAL_SEC_STATe(scpi_t *context)
{
	SCPI_GUARD_RLSTATE(context);
	return SCPIUTIL_ParamBool(context, APP_Set_CalibrationSecure);
}

scpi_result_t SCPI_CMD_CAL_SEC_STATe_Q(scpi_t *context)
{
	SCPI_GUARD_RLSTATE(context);
	return SCPIUTIL_ResultBool(context, APP_Get_CalibrationSecure());
}


scpi_result_t SCPI_CMD_CAL_SETup(scpi_t *context)
{
	SCPI_GUARD_RLSTATE(context);
	return SCPIUTIL_ParamInt32(context, APP_Set_CalibrationSetup);
}

scpi_result_t SCPI_CMD_CAL_SETup_Q(scpi_t *context)
{
	SCPI_GUARD_RLSTATE(context);
	return SCPIUTIL_ResultUInt32(context, APP_Get_CalibrationSetup());
}


scpi_result_t SCPI_CMD_CAL_STATe(scpi_t *context)
{
	SCPI_GUARD_RLSTATE(context);
	return SCPIUTIL_ParamBool(context, APP_Set_CalibrationState);
}

scpi_result_t SCPI_CMD_CAL_STATe_Q(scpi_t *context)
{
	SCPI_GUARD_RLSTATE(context);
	return SCPIUTIL_ResultBool(context, APP_Get_CalibrationState());
}


scpi_result_t SCPI_CMD_CAL_STRing(scpi_t *context)
{
	SCPI_GUARD_RLSTATE(context);

	char str[APP_CAL_TEXT_MAX_LEN];
	size_t len;

	if (!SCPI_ParamCopyText(context, str, APP_CAL_TEXT_MAX_LEN, &len, TRUE))
	{
		return SCPI_RES_ERR;
	}

	if (len < 0 || len >= APP_CAL_TEXT_MAX_LEN)
	{
		RETURN_WITH_ILLEGAL_PARAMETER_VALUE();
	}

	if (APP_Set_CalibrationString(str) != API_OK)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_CALIBRATION_FAILED);
		return SCPI_RES_ERR;
	}

	return SCPI_RES_OK;
}

scpi_result_t SCPI_CMD_CAL_STRing_Q(scpi_t *context)
{
	SCPI_GUARD_RLSTATE(context);

	const char *str = APP_Get_CalibrationString();
	SCPI_ResultCharacters(context, str, strnlen(str, APP_CAL_TEXT_MAX_LEN));
	return SCPI_RES_OK;
}


scpi_result_t SCPI_CMD_CAL_TEMPerature_Q(scpi_t *context)
{
	SCPI_GUARD_RLSTATE(context);

	SCPI_ResultDouble(context, APP_Get_CalibrationTemp());
	return SCPI_RES_OK;
}


scpi_result_t SCPI_CMD_CAL_VALue(scpi_t *context)
{
	SCPI_GUARD_RLSTATE(context);

	double cal_val;

	GET_PARAM_DOUBLE_MANDATORY(&cal_val);

	API_StatusTypeDef status = APP_Set_CalibrationValue(UTIL_RoundToInt32(cal_val * SCPI_DIVISOR_TO_OHM));

	switch (status)
	{
		case API_INVALID_OPERATION:
			SCPI_ErrorPush(context, SCPI_ERROR_EXECUTION_ERROR);
			return SCPI_RES_ERR;
		case API_PARAM_OUT_OF_RANGE:
			SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
			return SCPI_RES_ERR;
		default:
			return SCPI_RES_OK;
	}
}

scpi_result_t SCPI_CMD_CAL_VALue_Q(scpi_t *context)
{
	SCPI_GUARD_RLSTATE(context);

	int32_t cal_val;

	if (APP_Get_CalibrationValue(&cal_val) != API_OK)
	{
		return SCPI_RES_ERR;
	}

	SCPI_ResultDouble(context, ((double)cal_val) / SCPI_DIVISOR_TO_OHM);

	return SCPI_RES_OK;
}

/* Private functions ---------------------------------------------------------*/

