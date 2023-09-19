/**
 * @file    scpi_source_switching_def.c
 * @author  sebas
 * @date    04.12.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "communication/scpi_source_switching_def.h"
#include "communication/scpi_util.h"
#include "application/app_source.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/

scpi_choice_def_t SCPI_SWIT_MODE[] =
{
		{ "AUTO",  SOUR_SWIT_AUTO },
		{ "BBMake",  SOUR_SWIT_BBMake },
		{ "DEFault", SOUR_SWIT_AUTO },
		SCPI_CHOICE_LIST_END
};

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

scpi_result_t SCPI_CMD_SOUR_SWIT_MODE(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ParamChoice(
			context,
			SCPI_SWIT_MODE,
			(API_StatusTypeDef (*)(int32_t)) APP_Set_SourceSwitching);
}


scpi_result_t SCPI_CMD_SOUR_SWIT_MODE_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ResultMnemonic(
			context,
			SCPI_SWIT_MODE,
			APP_Get_SourceSwitching());
}

/* Private functions ---------------------------------------------------------*/

