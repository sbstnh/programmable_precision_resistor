/**
 * @file    app_input.c
 * @author  sebas
 * @date    03.12.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "application/app_input.h"
#include "application/app_memory.h"
#include "application/app_util.h"

#include "trigger/trigger_def.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

bool APP_Get_InputState()
{
	return APP.INPut.STATe;
}

API_StatusTypeDef APP_Set_InputState(bool state)
{
	RETURN_OK_IF_TRUE(APP.INPut.STATe == state);
	APP.INPut.STATe = state;
	return _APP_UTIL_ApplyInput();
}

API_StatusTypeDef APP_Run_InputStateToggle()
{
	return APP_Set_InputState(!APP.INPut.STATe);
}

INH_MODE_TypeDef APP_Get_InputInhibitMode()
{
	return APP.INPut.INHibit.MODE;
}

API_StatusTypeDef APP_Set_InputInhibitModeSave(INH_MODE_TypeDef mode, bool save)
{
	RETURN_OK_IF_TRUE(APP.INPut.INHibit.MODE == mode);

	// Check for value out of range
	if (mode < INH_MODE_OFF || mode > INH_MODE_LIVE)
	{
		return API_PARAM_OUT_OF_RANGE;
	}

	APP.INPut.INHibit.MODE = mode;

	API_StatusTypeDef status = API_OK;
	if (save)
	{
		status = APP_Run_MemorySaveInstData();
	}

	if (mode == INH_MODE_LATChing)
	{
		TRIGEDGE_ParamsSetup(&TRIG_INHIBIT_PARAMS, TRIGEDGE_Inhibit_DetectEvent, TRIGEDGE_SLOPE_POSITIVE, 0);
		TRIG_Init(&TRIG_INHIBIT, &TRIG_LOGIC_INHIBIT);
		TRIG_Continuous(&TRIG_INHIBIT, true);
		return status;
	}

	if (mode == INH_MODE_OFF)
	{
		APP_Set_InputInhibitState(false);
	}

	TRIG_Continuous(&TRIG_INHIBIT, false);
	TRIG_Abort(&TRIG_INHIBIT);

	return status;
}


API_StatusTypeDef APP_Set_InputInhibitMode(INH_MODE_TypeDef mode)
{
	return APP_Set_InputInhibitModeSave(mode, true);
}


bool APP_Get_InputInhibitState()
{
	return APP.INPut.INHibit.STATe;
}

API_StatusTypeDef APP_Set_InputInhibitState(bool state)
{
	RETURN_OK_IF_TRUE(APP.INPut.INHibit.STATe == state);

	APP.INPut.INHibit.STATe = state;
	return _APP_UTIL_ApplyInput();
}

/* Private functions ---------------------------------------------------------*/

