/**
 * @file    app_memory.c
 * @author  sebas
 * @date    19.01.2023
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include <string.h>

#include "application/app_init.h"
#include "application/app_memory.h"
#include "calibration/calibration.h"
#include "persistence/persistence_def.h"
#include "persistence/apply_persistence.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/


API_StatusTypeDef APP_Run_MemoryReadCalibration()
{
	if (PER_ReadCalData(&PER) != API_OK)
	{
		CAL_Reset(&APP.CALibration.cal_data);
		return API_ERROR;
	}

	PER_CopyToCalibration(&PER, &APP.CALibration.cal_data);

	if (CAL_ValidateAll(&APP.CALibration.cal_data) != API_OK)
	{
		CAL_Reset(&APP.CALibration.cal_data);
		return API_ERROR;
	}

	return API_OK;
}


API_StatusTypeDef APP_Run_MemorySaveCalibration()
{
	if (CAL_ValidateAll(&APP.CALibration.cal_data) != API_OK)
	{
		return API_ERROR;
	}

	PER_CopyFromCalibration(&PER, &APP.CALibration.cal_data);

	if (PER_WriteCalData(&PER) != API_OK)
	{
		return API_ERROR;
	}

	return API_OK;
}


API_StatusTypeDef APP_Run_MemoryReadInstData()
{
	API_StatusTypeDef status;

	status = PER_ReadInstData(&PER);

	if (status != API_OK)
	{
		APP_Run_RestoreDefaultInstrumentSettings(&APP);
		PER_CopyAppToInstData(&PER, (APP_ParamTypeDef *) &APP);
		return status;
	}

	PER_ApplyInstData(&PER, (APP_ParamTypeDef *) &APP);

	return API_OK;
}


API_StatusTypeDef APP_Run_MemorySaveInstData()
{
	PER_CopyAppToInstData(&PER, &APP);

	API_StatusTypeDef status;

	status = PER_WriteInstData(&PER);
	if (status != API_OK)
	{
		return API_HARDWARE_ERROR;
	}

	return API_OK;
}


API_StatusTypeDef APP_Run_MemoryRecall(uint8_t index, bool default_if_error)
{
	memset(&PER.user_data, 0, sizeof(USERDATA_TypeDef));

	if (PER_ReadUserData(&PER, index) != API_OK)
	{
		if (default_if_error)
		{
			APP_Run_RestoreDefaultUserSettings(&APP);
			PER_CopyAppToUserData(&PER, &APP);
		}
		return API_HARDWARE_ERROR;
	}

	PER_ApplyUserData(&PER, (APP_ParamTypeDef *) &APP);

	return API_OK;
}


API_StatusTypeDef APP_Run_MemorySave(uint8_t index)
{
	memset(&PER.user_data, 0, sizeof(USERDATA_TypeDef));
	PER_CopyAppToUserData(&PER, &APP);

	if (PER_WriteUserData(&PER, index) != API_OK)
	{
		return API_HARDWARE_ERROR;
	}

	return API_OK;
}



/* Private functions ---------------------------------------------------------*/

