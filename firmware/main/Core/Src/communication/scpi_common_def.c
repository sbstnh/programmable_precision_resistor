/**
 * @file    scpi_common_def.c
 * @author  sebas
 * @date    14.11.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "scpi/scpi.h"

#include "communication/scpi_util.h"
#include "communication/scpi_common_def.h"

#include "application/app_memory.h"

#include "persistence/persistence_def.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/


scpi_result_t SCPI_CMD_COMM_RCL(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	uint32_t index;

	GET_PARAM_UINT32_MANDATORY(&index);

	if (index >= USERDATA_NUMBER_BLOCKS)
	{
		RETURN_WITH_ILLEGAL_PARAMETER_VALUE();
	}

	if (APP_Run_MemoryRecall(index, false) != API_OK)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_SAVE_RECALL_MEMORY_LOST);
		return SCPI_RES_ERR;
	}

	return SCPI_RES_OK;
}


scpi_result_t SCPI_CMD_COMM_SAV(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	uint32_t index;

	GET_PARAM_UINT32_MANDATORY(&index);

	if (index >= USERDATA_NUMBER_BLOCKS)
	{
		RETURN_WITH_ILLEGAL_PARAMETER_VALUE();
	}

	if (APP_Run_MemorySave(index) != API_OK)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_MEMORY_ERROR);
	}

	return SCPI_RES_OK;
}


/**
 * Reimplement IEEE488.2 *TST?
 *
 * Result should be 0 if everything is ok
 * Result should be 1 if something goes wrong
 *
 * Return SCPI_RES_OK
 */
scpi_result_t SCPI_CMD_CoreTstQ(scpi_t *context)
{
	SCPI_ResultInt32(context, 0);
	return SCPI_RES_OK;
}

/* Private functions ---------------------------------------------------------*/
