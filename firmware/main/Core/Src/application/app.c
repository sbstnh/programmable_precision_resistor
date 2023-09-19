/**
 * @file    app_cycle.c
 * @author  sebas
 * @date    24.11.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "application/app.h"
#include "cmsis_os2.h"
#include "util/util.h"
#include "trigger/trigger_def.h"

#include "application/app_calibration.h"
#include "application/app_init.h"
#include "application/app_input.h"
#include "application/app_memory.h"
#include "application/app_source.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

API_StatusTypeDef _APP_InhibitLatched();
API_StatusTypeDef _APP_InhibitLive();

API_StatusTypeDef _APP_Step(bool triggered);
API_StatusTypeDef _APP_Up(bool triggered);
API_StatusTypeDef _APP_Down(bool triggered);

API_StatusTypeDef _APP_List(bool triggered);
API_StatusTypeDef _APP_UTIL_ListGetNextDwellTime(int32_t *dwell_time);

/* Exported functions --------------------------------------------------------*/

API_StatusTypeDef APP_Init()
{
	// App struct is initialized with default values first
	APP_Run_RestoreDefault(&APP);

	// Try to load calibration from eeprom or default, then apply
	APP_Run_MemoryReadCalibration();
	APP_Run_CalibrationApply();

	// Try to load instrument settings
	APP_Run_MemoryReadInstData();

	// Try to load user settings
	APP_Run_MemoryRecall(0, true);

	APP_Set_SourceResistanceLevelImmediateAmplitudeForce(
			APP_Get_SourceResistanceLevelImmediateAmplitude().value,
			true);

	TRIG_Init(&TRIG, &TRIG_LOGIC_EDGE);
	TRIG_Init(&TRIG_INHIBIT, &TRIG_LOGIC_INHIBIT);

	return API_OK;
}

API_StatusTypeDef APP_Cycle()
{
	// Handle input inhibit first
	switch (APP.INPut.INHibit.MODE)
	{
		default:
		case INH_MODE_OFF:
			break;

		case INH_MODE_LATChing:
			if (_APP_InhibitLatched() != API_OK)
			{
				return API_ERROR;
			}
			break;

		case INH_MODE_LIVE:
			if (_APP_InhibitLive() != API_OK)
			{
				return API_ERROR;
			}
			break;
	}

	// Handle trigger
	bool triggered = TRIG_Cycle(&TRIG);

	switch (APP.SOURce.RESistance.MODE)
	{
		default:
		case RES_MODE_FIXed:
			return API_OK;

		case RES_MODE_STEP:
			return _APP_Step(triggered);

		case RES_MODE_UP:
			return _APP_Up(triggered);

		case RES_MODE_DOWN:
			return _APP_Down(triggered);

		case RES_MODE_LIST:
			return _APP_List(triggered);
	}
}

/* Private functions ---------------------------------------------------------*/


API_StatusTypeDef _APP_InhibitLatched()
{
	if (!TRIG_Cycle(&TRIG_INHIBIT))
	{
		return API_OK;
	}

	if (APP_Set_InputInhibitState(true) != API_OK)
	{
		return API_ERROR;
	}

	return API_OK;
}

API_StatusTypeDef _APP_InhibitLive()
{
	bool inhibit_detected =
	(
		(
			APP_Get_SourceDigitalPinFunction(SOUR_DIG_PIN1) == PIN_FUNC_INHibit
			&& APP_Get_SourceDigitalPinData(SOUR_DIG_PIN1)
		)
		||
		(
			APP_Get_SourceDigitalPinFunction(SOUR_DIG_PIN2) == PIN_FUNC_INHibit
			&& APP_Get_SourceDigitalPinData(SOUR_DIG_PIN2)
		)
	);

	if (APP_Set_InputInhibitState(inhibit_detected) != API_OK)
	{
		return API_ERROR;
	}

	return API_OK;
}


API_StatusTypeDef _APP_Step(bool triggered)
{
	if (triggered)
	{
		return APP_Set_SourceResistanceLevelImmediateAmplitude(
			APP.SOURce.RESistance.LEVel.TRIGgered.AMPLitude.value,
			true
		);
	}
	return API_OK;
}

API_StatusTypeDef _APP_Up(bool triggered)
{
	if (triggered)
	{
		return APP_Run_SourceResistanceLevelImmediateAmplitudeUp(true);
	}
	return API_OK;
}

API_StatusTypeDef _APP_Down(bool triggered)
{
	if (triggered)
	{
		return APP_Run_SourceResistanceLevelImmediateAmplitudeDown(true);
	}
	return API_OK;
}

API_StatusTypeDef _APP_List(bool triggered)
{
	if (APP.SOURce.LIST._state == LIST_STATE_INIT)
	{
		APP_Run_SourceListInit();
	}

	switch (APP.SOURce.LIST._state)
	{
		case LIST_STATE_INIT:
			return API_ERROR;

		case LIST_STATE_WAIT_FOR_TRIG:
			if (triggered)
			{
				APP.SOURce.LIST._state = LIST_STATE_RUN;
			}
			else
			{
				return API_OK;
			}
			// No break here, goto run immediately

		case LIST_STATE_RUN:
			return APP_Run_ListRun(triggered);

		case LIST_STATE_TERMINATE:
			APP_Run_ListTerminate();

			// Switch back to RES_MODE_FIXed
			return APP_Set_SourceResistanceMode(RES_MODE_FIXed);
	}

	return API_ERROR;
}
