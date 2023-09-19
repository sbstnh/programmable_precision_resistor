/**
 * @file    scpi_source_mode_def.c
 * @author  sebas
 * @date    04.12.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "communication/scpi_source_mode_def.h"
#include "communication/scpi_util.h"
#include "application/app_source.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

scpi_choice_def_t SCPI_SOUR_MODE[] =
{
		{ "UNCalibrated", SOUR_MODE_UNCalibrated },
		{ "TWIRe",  SOUR_MODE_TWIRe },
		{ "FWIRe", SOUR_MODE_FWIRe },
		{ "DEFault", SOUR_MODE_TWIRe },
		SCPI_CHOICE_LIST_END
};

/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

scpi_result_t SCPI_CMD_SOUR_MODE(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ParamChoice(
			context,
			SCPI_SOUR_MODE,
			(API_StatusTypeDef (*)(int32_t)) APP_Set_SourceMode);
}

scpi_result_t SCPI_CMD_SOUR_MODE_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ResultMnemonic(context, SCPI_SOUR_MODE, APP_Get_SourceMode());
}

/* Private functions ---------------------------------------------------------*/

