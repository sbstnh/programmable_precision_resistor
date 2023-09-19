/**
 * @file    scpi_eeprom_def.c
 * @author  sebas
 * @date    11.11.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "cmsis_os2.h"

#include "scpi/scpi.h"
#include "communication/scpi_util.h"

#include "hardware/eeprom_def.h"
#include "persistence/persistence_def.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/


scpi_result_t SCPI_CMD_MEM_FORMat(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	if (EEPR_Reset(&EEPROM) != API_OK)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_MEMORY_ERROR);
		return SCPI_RES_ERR;
	}

	return SCPI_RES_OK;
}


scpi_result_t SCPI_CMD_MEM_DATA_VLENgth(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	uint32_t addr;
	uint32_t len;
	uint32_t value = 0;

	GET_PARAM_UINT32_MANDATORY(&addr);
	GET_PARAM_UINT32_MANDATORY(&len);
	GET_PARAM_UINT32_MANDATORY(&value);

	if (addr >= EEPR_MEMORY_SIZE || len > 4 || (addr + len > EEPR_MEMORY_SIZE))
	{
		SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
		return SCPI_RES_ERR;
	}

	API_StatusTypeDef status = EEPR_Write(&EEPROM, addr, (uint8_t *)&value, len);
	if (status == API_INVALID_OPERATION)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_COMMAND_PROTECTED);
		return SCPI_RES_ERR;
	}
	else if (status == API_ERROR)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_HARDWARE_ERROR);
		return SCPI_RES_ERR;
	}

	return SCPI_RES_OK;
}


scpi_result_t SCPI_CMD_MEM_DATA_VLENgth_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	uint32_t addr;
	uint32_t len;
	uint32_t value = 0;

	GET_PARAM_UINT32_MANDATORY(&addr);
	GET_PARAM_UINT32_MANDATORY(&len);

	if (addr >= EEPR_MEMORY_SIZE || len > 4 || (addr + len > EEPR_MEMORY_SIZE))
	{
		SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
		return SCPI_RES_ERR;
	}

	if (EEPR_Read(&EEPROM, addr, (uint8_t *)&value, len) != API_OK)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_HARDWARE_ERROR);
		return SCPI_RES_ERR;
	}

	SCPI_ResultUInt32(context, value);
	return SCPI_RES_OK;
}

scpi_result_t SCPI_CMD_MEM_DATA_BLOCk_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	int32_t addr;
	int32_t len;
	uint8_t data[EEPR_PAGE_SIZE];

	GET_PARAM_INT32_MANDATORY(&addr);
	GET_PARAM_INT32_MANDATORY(&len);

	if (addr < 0 || addr >= EEPR_MEMORY_SIZE || len < 0 || len > EEPR_PAGE_SIZE)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
		return SCPI_RES_ERR;
	}

	if (addr + len > EEPR_MEMORY_SIZE)
	{
		len = EEPR_MEMORY_SIZE - addr;
	}

	if (EEPR_Read(&EEPROM, addr, data, len) != API_OK)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_HARDWARE_ERROR);
		return SCPI_RES_ERR;
	}

	SCPI_ResultArbitraryBlock(context, data, len);

	return SCPI_RES_OK;
}


scpi_result_t SCPI_CMD_MEM_PROT_STATe(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	bool state;

	GET_PARAM_BOOL_MANDATORY(&state);
	if (state)
	{
		EEPR_DisableWrite(&EEPROM);
	}
	else
	{
		EEPR_EnableWrite(&EEPROM);
	}

	return SCPI_RES_OK;
}

scpi_result_t SCPI_CMD_MEM_PROT_STATe_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ResultBool(context, !EEPR_GetEnableWrite(&EEPROM));
}

/* Private functions ---------------------------------------------------------*/
