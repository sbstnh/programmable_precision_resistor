/**
 * @file    scpi_input_def.c
 * @author  sebas
 * @date    04.12.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>

#include "communication/scpi_input_def.h"
#include "communication/scpi_util.h"

#include "application/app_input.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/

scpi_choice_def_t SCPI_INP_INH_MODE[] =
{
		{ "OFF", INH_MODE_OFF },
		{ "LATChing",  INH_MODE_LATChing },
		{ "LIVE", INH_MODE_LIVE },
		{ "DEFault", INH_MODE_OFF },
		SCPI_CHOICE_LIST_END
};

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

scpi_result_t SCPI_CMD_INP_STATe(scpi_t *context)
{
	SCPI_GUARD_RLSTATE(context);
	return SCPIUTIL_ParamBool(context, APP_Set_InputState);
}

scpi_result_t SCPI_CMD_INP_STATe_Q(scpi_t *context)
{
	SCPI_GUARD_RLSTATE(context);
	return SCPIUTIL_ResultBool(context, APP_Get_InputState());
}


scpi_result_t SCPI_CMD_INP_INH_MODE(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ParamChoice(
			context,
			SCPI_INP_INH_MODE,
			(API_StatusTypeDef (*)(int32_t)) APP_Set_InputInhibitMode);
}

scpi_result_t SCPI_CMD_INP_INH_MODE_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ResultMnemonic(context, SCPI_INP_INH_MODE, APP_Get_InputInhibitMode());
}


scpi_result_t SCPI_CMD_INP_INH_STATe_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ResultBool(context, APP_Get_InputInhibitState());
}

scpi_result_t SCPI_CMD_INP_INH_CLEar(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	if (APP_Set_InputInhibitState(false) != API_OK)
	{
		return SCPI_RES_ERR;
	}

	return SCPI_RES_OK;
}

/* Private functions ---------------------------------------------------------*/

