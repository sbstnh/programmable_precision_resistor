/**
 * @file    ui_action_calibration.c
 * @author  sebas
 * @date    07.01.2023
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include <string.h>

#include "util/util.h"

#include "ui/action/ui_action_calibration.h"
#include "ui/action/ui_action_util.h"
#include "ui/dialog/ui_dialog_info.h"
#include "ui/ui_parser_def.h"

#include "application/app_calibration.h"
#include "application/app_system.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/


API_StatusTypeDef UIACT_CalibrationCount()
{
	return UIACT_UtilDialogInfoInt("COUNt", "", APP_Get_CalibrationCount(), 8, 0);
}


API_StatusTypeDef UIACT_CalibrationDate()
{
	const char *date_str = APP_Get_CalibrationDate();

	if (UTIL_StrLenDisplay(date_str, APP_CAL_DATE_MAX_LEN) > 0)
	{
		return UIDI_Show(date_str, 0, false);
	}

	return UIDI_Show("NO CAL DATE SAVED", 0, true);
}


API_StatusTypeDef UIACT_CalibrationString()
{
	const char *str = APP_Get_CalibrationString();

	if (UTIL_StrLenDisplay(str, APP_CAL_TEXT_MAX_LEN) > 0)
	{
		return UIDI_Show(str, 0, false);
	}

	return UIDI_Show("NO CAL TEXT SAVED", 0, true);
}


API_StatusTypeDef UIACT_CalibrationTemp()
{
	char str[20] = "TEMP: ";
	float temp = APP_Get_CalibrationTemp();
	uint8_t dec_offset = 0;

	temp *= 1000;

	if (temp < 0)
	{
		strcat(str, "<");
		dec_offset = 1;
		temp = 0;
	}

	UTIL_UIntToStr(str + strlen(str),
			UTIL_DivRoundClosestInt32((uint32_t) temp, 10),
			4 - dec_offset,
			2 - dec_offset,
			UTIL_LEAD_TRAIL_ZERO_BLANK,
			UTIL_LEAD_TRAIL_ZERO_ZERO);

	strcat(str, "\xB0" "C");

	if (UTIL_StrLenDisplay(str, APP_CAL_TEXT_MAX_LEN) > 0)
	{
		return UIDI_Show(str, 0, false);
	}

	return UIDI_Show("NO CAL TEMP SAVED", 0, true);
}


API_StatusTypeDef UIACT_CalibrationSetup_New(UIDN_TypeDef *uidn, const char *default_value, UIDN_CursorPosTypeDef cursor_position)
{
	uint32_t setup;

	// TODO: Setup UIPAR_Number parser with correct min max values

	UIDN_Setup(uidn, &UIPAR_CAL_SETUP, cursor_position);

	API_StatusTypeDef status = UIDN_Show(uidn, "CAL SETUP", default_value, "", &setup);
	if (status != API_OK)
	{
		return status;
	}

	status = APP_Set_CalibrationSetup(setup);
	if (status != API_OK)
	{
		APP_Run_SystemBeeperBeepError();
		UIDI_Show("INVALID SETUP", UIDI_DEFAULT_TIMEOUT_MEDIUM, true);
	}

	return status;
}

API_StatusTypeDef UIACT_CalibrationSetup_Edit(UIDN_TypeDef *uidn, UIDN_CursorPosTypeDef cursor_position)
{
	char default_value[6];
	const int32_t value = APP_Get_CalibrationSetup();

	UTIL_UIntToStr(default_value, value, 3, 0, UTIL_LEAD_TRAIL_ZERO_SKIP, UTIL_LEAD_TRAIL_ZERO_SKIP);

	return UIACT_CalibrationSetup_New(uidn, default_value, cursor_position);
}


API_StatusTypeDef UIACT_CalibrationValue_New(UIDN_TypeDef *uidn, const char *default_value, UIDN_CursorPosTypeDef cursor_position)
{
	uint32_t cal_value;

	// TODO: Setup UIPAR_Number parser with correct min max values

	UIDN_Setup(uidn, &UIPAR_RESISTANCE, cursor_position);

	API_StatusTypeDef status = UIDN_Show(uidn, "CAL VALUE", default_value, "", &cal_value);
	if (status != API_OK)
	{
		return status;
	}

	status = APP_Set_CalibrationValue(cal_value);
	if (status != API_OK)
	{
		APP_Run_SystemBeeperBeepError();
		UIDI_Show("PARAM OUT OF RANGE", UIDI_DEFAULT_TIMEOUT_MEDIUM, true);
	}

	return status;
}

API_StatusTypeDef UIACT_CalibrationValue_Edit(UIDN_TypeDef *uidn, UIDN_CursorPosTypeDef cursor_position)
{
	char default_value[13];
	int32_t value;
	if (APP_Get_CalibrationValue(&value) != API_OK)
	{
		return API_ERROR;
	}

	UTIL_UIntToStr(default_value, value, 10, 3, UTIL_LEAD_TRAIL_ZERO_SKIP, UTIL_LEAD_TRAIL_ZERO_SKIP);

	return UIACT_CalibrationValue_New(uidn, default_value, cursor_position);
}

/* Private functions ---------------------------------------------------------*/

