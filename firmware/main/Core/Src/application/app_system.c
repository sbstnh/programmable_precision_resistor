/**
 * @file    app_system.c
 * @author  sebas
 * @date    05.12.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include <math.h>
#include <string.h>

#include "application/app_init.h"
#include "application/app_memory.h"
#include "application/app_params.h"
#include "application/app_system.h"

#include "hardware/ui_interface_def.h"
#include "hardware/kty82_sensor_def.h"

#include "persistence/persistence_def.h"

#include "build_def.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/


bool APP_Get_SystemBeeperState()
{
	return APP.SYSTem.BEEPer.STATe;
}

API_StatusTypeDef APP_Set_SystemBeeperStateSave(bool state, bool save)
{
	APP.SYSTem.BEEPer.STATe = state;
	if (save)
	{
		return APP_Run_MemorySaveInstData();
	}
	return API_OK;
}

API_StatusTypeDef APP_Set_SystemBeeperState(bool state)
{
	return APP_Set_SystemBeeperStateSave(state, true);
}

void APP_Run_SystemBeeperBeepShort()
{
	if (APP.SYSTem.BEEPer.STATe)
	{
		UIIF_Beep(&UIIF, UIIF_BEEP_FREQ, UIIF_BEEP_VOL, UIIF_BEEP_SHORT);
	}
}

void APP_Run_SystemBeeperBeepLong()
{
	if (APP.SYSTem.BEEPer.STATe)
	{
		UIIF_Beep(&UIIF, UIIF_BEEP_FREQ, UIIF_BEEP_VOL, UIIF_BEEP_LONG);
	}
}

void APP_Run_SystemBeeperBeepError()
{
	if (APP.SYSTem.BEEPer.STATe)
	{
		UIIF_Beep(&UIIF, UIIF_BEEP_FREQ, UIIF_BEEP_VOL, UIIF_BEEP_ERROR);
	}
}


void APP_Run_SystemBeeperTick()
{
	if (APP.SYSTem.BEEPer.STATe)
	{
		UIIF_Tick(&UIIF);
	}
}


COMM_RLSTate_TypeDef APP_Get_SystemCommunicateRLState()
{
	return APP.SYSTem.COMMunicate.RLSTate;
}

API_StatusTypeDef APP_Run_SystemCommunicateRLState(COMM_RLSTate_TypeDef rlstate)
{
	// TODO: Check implementation
	APP.SYSTem.COMMunicate.RLSTate = rlstate;
	return API_OK;
}


API_StatusTypeDef APP_Run_SystemDefaultImmediate()
{
	APP_Run_RestoreDefault(&APP);

	if (APP_Run_MemorySaveInstData() != API_OK)
	{
		return API_ERROR;
	}

	if (APP_Run_MemorySave(0) != API_OK)
	{
		return API_ERROR;
	}

	HAL_NVIC_SystemReset();

	return API_OK;
}


const char *APP_Get_SystemFirmwareVersionMainboard()
{
	return VERSION_STRING_MAINBOARD;
}


const char *APP_Get_SystemFirmwareVersionUI()
{
	UIIF_ReadFirmwareString(&UIIF, VERSION_STRING_UI);
	return VERSION_STRING_UI;
}


API_StatusTypeDef APP_Run_SystemSecurityImmediate()
{
	APP_Run_RestoreDefault(&APP);

	if (APP_Run_MemorySaveInstData() != API_OK)
	{
		return API_ERROR;
	}

	for (uint8_t i = 0; i < USERDATA_NUMBER_BLOCKS; i++)
	{
		if (APP_Run_MemorySave(i) != API_OK)
		{
			return API_ERROR;
		}
	}

	HAL_NVIC_SystemReset();

	return API_OK;
}


float APP_Get_SystemTempImmediate(TEMP_SELection_TypeDef temp_sel)
{
	switch (temp_sel)
	{
		case TEMP_SEL_1:
			return KTY82_TEMP[KTY82_TEMP1].temperature;
		case TEMP_SEL_2:
			return KTY82_TEMP[KTY82_TEMP2].temperature;
		case TEMP_SEL_AVG:
			return 0.5 * (KTY82_TEMP[KTY82_TEMP1].temperature + KTY82_TEMP[KTY82_TEMP2].temperature);
		default:
			return NAN;
	}
}


float APP_Get_SystemTempAverage(TEMP_SELection_TypeDef temp_sel)
{
	switch (temp_sel)
	{
		case TEMP_SEL_1:
			return KTY82_TEMP[KTY82_TEMP1].average;
		case TEMP_SEL_2:
			return KTY82_TEMP[KTY82_TEMP2].average;
		case TEMP_SEL_AVG:
			return 0.5 * (KTY82_TEMP[KTY82_TEMP1].average + KTY82_TEMP[KTY82_TEMP2].average);
		default:
			return NAN;
	}
}


float APP_Get_SystemTempMinimum(TEMP_SELection_TypeDef temp_sel)
{
	switch (temp_sel)
	{
		case TEMP_SEL_1:
			return KTY82_TEMP[KTY82_TEMP1].minimum;
		case TEMP_SEL_2:
			return KTY82_TEMP[KTY82_TEMP2].minimum;
		case TEMP_SEL_AVG:
			return 0.5 * (KTY82_TEMP[KTY82_TEMP1].minimum + KTY82_TEMP[KTY82_TEMP2].minimum);
		default:
			return NAN;
	}
}


float APP_Get_SystemTempInternalMaximum(TEMP_SELection_TypeDef temp_sel)
{
	switch (temp_sel)
	{
		case TEMP_SEL_1:
			return KTY82_TEMP[KTY82_TEMP1].maximum;
		case TEMP_SEL_2:
			return KTY82_TEMP[KTY82_TEMP2].maximum;
		case TEMP_SEL_AVG:
			return 0.5 * (KTY82_TEMP[KTY82_TEMP1].maximum + KTY82_TEMP[KTY82_TEMP2].maximum);
		default:
			return NAN;
	}
}


API_StatusTypeDef APP_Run_SystemTempReset(TEMP_SELection_TypeDef temp_sel)
{
	switch (temp_sel)
	{
		case TEMP_SEL_1:
			KTY82_ResetStats(&KTY82_TEMP[KTY82_TEMP1]);
			return API_OK;
		case TEMP_SEL_2:
			KTY82_ResetStats(&KTY82_TEMP[KTY82_TEMP2]);
			return API_OK;
		case TEMP_SEL_ALL:
			KTY82_ResetStats(&KTY82_TEMP[KTY82_TEMP1]);
			KTY82_ResetStats(&KTY82_TEMP[KTY82_TEMP2]);
			return API_OK;
		default:
			return API_ERROR;
	}
}


/* Private functions ---------------------------------------------------------*/

