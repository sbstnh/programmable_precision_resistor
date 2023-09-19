/**
 * @file    scpi_source_voltage_def.c
 * @author  sebas
 * @date    04.12.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "communication/scpi_source_voltage_def.h"
#include "communication/scpi_util.h"
#include "application/app_source.h"

/* Private defines -----------------------------------------------------------*/

#define SCPI_DIVSIOR_TO_VOLT		1000

/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

scpi_result_t SCPI_CMD_SOUR_VOLT_LEV_IMM_AMPLitude_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPI_ResultIntValueTypeDefAsDouble(
			context,
			APP_Get_SourceVoltageLevelImmediateAmplitude(),
			SCPI_DIVSIOR_TO_VOLT);
}

/* Private functions ---------------------------------------------------------*/

