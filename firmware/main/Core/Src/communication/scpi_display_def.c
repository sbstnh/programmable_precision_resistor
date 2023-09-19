/**
 * @file    scpi_display_def.c
 * @author  sebas
 * @date    11.11.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include <string.h>

#include "communication/scpi_display_def.h"
#include "communication/scpi_util.h"

#include "application/app_display.h"

#include "hardware/ui_interface_def.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/

scpi_choice_def_t SCPI_DISP_MAIN_PRIM_RESolution[] =
{
		{ "THRee", PRIM_RES_THRee },
		{ "FOUR",  PRIM_RES_FOUR },
		{ "FIVE", PRIM_RES_FIVE },
		{ "SIX", PRIM_RES_SIX },
		{ "DEFault", PRIM_RES_SIX },
		SCPI_CHOICE_LIST_END
};

scpi_choice_def_t SCPI_DISP_MAIN_SEC_MODE[] =
{
		{ "STATe",  SEC_MODE_STATe },
		{ "CURRent", SEC_MODE_CURRent },
		{ "VOLTage", SEC_MODE_VOLTage },
		{ "POWer", SEC_MODE_POWer },
		{ "TRIGger", SEC_MODE_TRIGger },
		{ "RESistance", SEC_MODE_RESistance },
		{ "LINDex", SEC_MODE_LINDex },
		{ "LNUMber", SEC_MODE_LNUMber },
		{ "DEFault", SEC_MODE_STATe },
		SCPI_CHOICE_LIST_END
};

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/


scpi_result_t SCPI_CMD_DISP_ENABle(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ParamBool(context, APP_Set_DisplayEnable);
}

scpi_result_t SCPI_CMD_DISP_ENABle_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ResultBool(context, APP_Get_DisplayEnable());
}


scpi_result_t SCPI_CMD_DISP_USER_TEXT_DATA(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	char *str = APP_Get_DisplayUserTextData();
	size_t len;

	if (!SCPI_ParamCopyText(context, str, DISP_USER_TEXT_LENGTH, &len, TRUE))
	{
		return SCPI_RES_ERR;
	}

	if (len < 0 || len > 36)
	{
		RETURN_WITH_ILLEGAL_PARAMETER_VALUE();
	}

	APP_Set_DisplayUserTextState(true);

	return SCPI_RES_OK;
}

scpi_result_t SCPI_CMD_DISP_USER_TEXT_DATA_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	char *str = APP_Get_DisplayUserTextData();
	SCPI_ResultCharacters(context, str, strnlen(str, DISP_USER_TEXT_LENGTH));
	return SCPI_RES_OK;
}


scpi_result_t SCPI_CMD_DISP_USER_TEXT_STATe(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ParamBool(context, APP_Set_DisplayUserTextState);
}

scpi_result_t SCPI_CMD_DISP_USER_TEXT_STATe_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ResultBool(context, APP_Get_DisplayUserTextState());
}


scpi_result_t SCPI_CMD_DISP_USER_TEXT_CLEar(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	if (APP_Run_DisplayUserTextClear() != API_OK)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_SYSTEM_ERROR);
		return SCPI_RES_ERR;
	}

	return SCPI_RES_OK;
}


scpi_result_t SCPI_CMD_DISP_MAIN_PRIM_RESolution(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ParamChoice(
			context,
			SCPI_DISP_MAIN_PRIM_RESolution,
			(API_StatusTypeDef (*)(int32_t)) APP_Set_DisplayPrimaryResolution);
}

scpi_result_t SCPI_CMD_DISP_MAIN_PRIM_RESolution_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ResultMnemonic(context, SCPI_DISP_MAIN_PRIM_RESolution, APP_Get_DisplayPrimaryResolution());
}


scpi_result_t SCPI_CMD_DISP_MAIN_MODE(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ParamChoice(
			context,
			SCPI_DISP_MAIN_SEC_MODE,
			(API_StatusTypeDef (*)(int32_t)) APP_Set_DisplaySecondaryMode);
}

scpi_result_t SCPI_CMD_DISP_MAIN_MODE_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ResultMnemonic(context, SCPI_DISP_MAIN_SEC_MODE, APP_Get_DisplaySecondaryMode());
}

/* Private functions ---------------------------------------------------------*/

