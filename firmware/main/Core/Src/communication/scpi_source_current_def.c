/**
 * @file    scpi_source_current_def.c
 * @author  sebas
 * @date    04.12.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "communication/scpi_source_current_def.h"
#include "communication/scpi_util.h"
#include "application/app_source.h"

/* Private defines -----------------------------------------------------------*/

#define SCPI_DIVSIOR_TO_AMPERE		1000000

/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

scpi_result_t SCPI_CMD_SOUR_CURR_LEV_IMM_AMPLitude_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPI_ResultIntValueTypeDefAsDouble(
			context,
			APP_Get_SourceCurrentLevelImmediateAmplitude(),
			SCPI_DIVSIOR_TO_AMPERE);
}

/* Private functions ---------------------------------------------------------*/

