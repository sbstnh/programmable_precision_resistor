/**
 * @file    ui_display.c
 * @author  sebas
 * @date    19.12.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include <string.h>

#include "util/util.h"

#include "ui/display_helper.h"
#include "ui/ui.h"
#include "application/app_display.h"
#include "application/app_input.h"
#include "application/app_source.h"
#include "trigger/trigger_def.h"

#include "hardware/ui_interface_def.h"

/* Private defines -----------------------------------------------------------*/

#define UI_DISPLAY_TRIGGERED_TIMEOUT		15

/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

static uint8_t UI_Display_TriggeredTimeoutCounter = 0;

/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

void _UI_Display_WriteSecondaryState(char *str);
void _UI_Display_WriteSecondaryValueEngineering(char *str, int32_t value, uint8_t scaler, const char *unit_str);
void _UI_Display_WriteSecondaryTriggerState(char *str);
void _UI_Display_WriteSecondaryValueResistance(char *str);
void _UI_Display_WriteSecondaryListIndex(char *str);
void _UI_Display_WriteSecondaryListNumber(char *str);

/* Exported functions --------------------------------------------------------*/


void UI_Display_FormatTextCentered(char *target, const char *str, uint8_t max_len)
{
	int16_t pos = (UIIF_DISP_DIGITS - UTIL_StrLenDisplay(str, max_len)) / 2;

	if (pos < 0)
	{
		pos = 0;
	}

	memset(target, ' ', pos);
	target[pos] = '\0';
	strncat(target + pos, str, max_len - pos);
}


void UI_Display_SectionPrimary(char *str)
{
	int32_t result;
	if (APP_Run_SourceResistanceLevelImmediateCalculate(APP_Get_SourceMode(), &result) == API_OK)
	{
		UTIL_UIntToStrEngineering(str, result, APP_Get_DisplayPrimaryResolutionAsCounts(), 3, UTIL_LEAD_TRAIL_ZERO_ZERO);
	}
	else
	{
		strcpy(str, "ERROR");
	}

	// Append spaces so that the primary part is always of the same length

	for (uint8_t i = UTIL_StrLenDisplay(str, 10); i < 8; i++)
	{
		strcat(str, " ");
	}
}


void UI_DisplaySectionSecondary(char *str)
{
	switch (APP_Get_DisplaySecondaryMode())
	{
		default:
		case SEC_MODE_STATe:
			_UI_Display_WriteSecondaryState(str);
			break;

		case SEC_MODE_CURRent:
			_UI_Display_WriteSecondaryValueEngineering(
					str,
					APP_Get_SourceCurrentLevelImmediateAmplitude().value,
					6,
					"A");
			break;

		case SEC_MODE_VOLTage:
			_UI_Display_WriteSecondaryValueEngineering(
					str,
					APP_Get_SourceVoltageLevelImmediateAmplitude().value,
					3,
					"V");
			break;

		case SEC_MODE_POWer:
			_UI_Display_WriteSecondaryValueEngineering(
					str,
					APP_Get_SourcePowerLevelImmediateAmplitude().value,
					3,
					"W");
			break;

		case SEC_MODE_TRIGger:
			_UI_Display_WriteSecondaryTriggerState(str);
			break;

		case SEC_MODE_RESistance:
			_UI_Display_WriteSecondaryValueResistance(str);
			break;

		case SEC_MODE_LINDex:
			_UI_Display_WriteSecondaryListIndex(str);
			break;

		case SEC_MODE_LNUMber:
			_UI_Display_WriteSecondaryListNumber(str);
			break;
	}
}


void UI_Display_SectionModeIndicator(char *str, RES_MODE_TypeDef mode)
{
	switch (mode)
	{
		case RES_MODE_FIXed: *str = 'F'; break;
		case RES_MODE_STEP: *str = 'S'; break;
		case RES_MODE_UP: *str = 'U'; break;
		case RES_MODE_DOWN: *str = 'D'; break;
		case RES_MODE_LIST: *str = 'L'; break;
		default: *str = 0; break;
	}
}


void UI_Display_Update(const char * str)
{
	UIIF_DisplayPuts(&UIIF, str, strnlen(str, UIIF_BUFFER), false);
}


void UI_Display_Disable()
{
	UIIF_DisplayClear(&UIIF);
	UIIF_DisplayPuts(&UIIF, "\0", 1, true);
}


void UI_Display_OnTriggered()
{
	UI_Display_TriggeredTimeoutCounter = UI_DISPLAY_TRIGGERED_TIMEOUT;
}

/* Private functions ---------------------------------------------------------*/

void _UI_Display_WriteSecondaryState(char *str)
{
	if (APP_Get_InputInhibitState())
	{
		strcat(str, "  INHIB");
	}
	else if (APP_Get_InputState())
	{
		strcat(str, "     ON");
	}
	else
	{
		strcat(str, "    OFF");
	}
}


void _UI_Display_WriteSecondaryValueEngineering(char *str, int32_t value, uint8_t scaler, const char *unit_str)
{
	if (value)
	{
		strcat(str, " ");
		UTIL_UIntToStrEngineering(str + 1, value, UTIL_DIGITS_3_5, scaler, UTIL_LEAD_TRAIL_ZERO_ZERO);
	}
	else
	{
		strcpy(str, " ---- ");
	}
	strcat(str, unit_str);
}


void _UI_Display_WriteSecondaryTriggerState(char *str)
{
	// "Triggered" is not a state, but an event, hence there has to be
	// special treatment for this
	if (UI_Display_TriggeredTimeoutCounter > 0)
	{
		strcat(str, " TRIG'D");
		UI_Display_TriggeredTimeoutCounter--;

		return;
	}

	// All states can be handled as usual
	switch (TRIG_GetState(&TRIG))
	{
		case TRIG_STATE_IDLE: 		strcat(str, "   IDLE"); break;
		case TRIG_STATE_INITIATED: 	strcat(str, "INITIAT"); break;
		case TRIG_STATE_ARMED:		strcat(str, "  ARMED"); break;
		case TRIG_STATE_DELAYED: 	strcat(str, "DELAYED"); break;
		case TRIG_STATE_HELDOFF:	strcat(str, "HELDOFF"); break;
	}
}


void _UI_Display_WriteSecondaryValueResistance(char *str)
{
	int32_t value;
	if (APP_Run_SourceResistanceLevelImmediateCalculate(SOUR_MODE_UNCalibrated, &value) == API_OK)
	{
		UTIL_UIntToStr(str, UTIL_DivRoundClosestInt32(value, 1000), 6, 0, UTIL_LEAD_TRAIL_ZERO_ZERO, UTIL_LEAD_TRAIL_ZERO_ZERO);
		strcat(str, "R");
	}
	else
	{
		strcpy(str, "------R");
	}
}


void _UI_Display_WriteSecondaryListIndex(char *str)
{
	char tmp[8];
	int32_t value = APP_Get_SourceListResistanceIndex().value;
	int32_t max = APP_Get_SourceListResistanceLength().value;
	UTIL_UIntToStr(tmp, value, 2, 0, UTIL_LEAD_TRAIL_ZERO_SKIP, UTIL_LEAD_TRAIL_ZERO_ZERO);
	strcat(tmp, "/");
	UTIL_UIntToStr(tmp + strlen(tmp), max, 3, 0, UTIL_LEAD_TRAIL_ZERO_SKIP, UTIL_LEAD_TRAIL_ZERO_ZERO);

	strcat(str, " ");
	for (uint8_t i = 0; i < (6 - strlen(tmp)); i++)
	{
		strcat(str, " ");
	}
	strcat(str, tmp);
}


void _UI_Display_WriteSecondaryListNumber(char *str)
{
	int32_t value = APP_Get_SourceListResistanceRunNumber().value;
	strcat(str, " ");
	UTIL_UIntToStr(str + strlen(str), value, 6, 0, UTIL_LEAD_TRAIL_ZERO_BLANK, UTIL_LEAD_TRAIL_ZERO_ZERO);
}
