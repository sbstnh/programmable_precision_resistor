/**
 * @file    ui_action_util.c
 * @author  sebas
 * @date    01.01.2023
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include <string.h>
#include "util/util.h"
#include "ui/action/ui_action_util.h"

#include "application/app_system.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

UIDE_ChoiceTypeDef UIACT_BOOL[] =
{
		{ "OFF",	false },
		{ "ON",		true },
		UIDE_CHOICE_LIST_END
};

/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

API_StatusTypeDef UIACT_UtilDialogEnum(const char *description, UIDE_ChoiceTypeDef *choices, int32_t (*get_value)(void), API_StatusTypeDef (*set_value)(int32_t))
{
	UIDE_TypeDef dialog;
	const int32_t current = get_value();
	int32_t result;

	API_StatusTypeDef status = UIDE_Show(&dialog, description, choices, current, false, &result, NULL);

	if (status != API_OK)
	{
		return status;
	}

	if (set_value == NULL)
	{
		return API_OK;

	}

	return set_value(result);
}


API_StatusTypeDef UIACT_UtilDialogInfoInt(const char *description, const char *unit, int32_t value, uint8_t max_digits, uint8_t decimal_places)
{
	char str[20] = "\0";

	strcat(str, description);
	strcat(str, ": ");

	if (value < 0)
	{
		strcat(str + strlen(str), "-");
		value = -value;
	}

	UTIL_UIntToStr(str + strlen(str),
			       value,
				   max_digits,
				   decimal_places,
				   UTIL_LEAD_TRAIL_ZERO_SKIP,
				   UTIL_LEAD_TRAIL_ZERO_SKIP);

	strcat(str, unit);

	return UIDI_Show(str, 0, false);
}


API_StatusTypeDef UIACT_UtilDialogIntValueTypeDef(UIDN_TypeDef *uidn, UIPAR_TypeDef *parser, const char *description, const char *unit, UIDN_CursorPosTypeDef cursor_position,
		INT_VALUE_TypeDef (*get_value)(void), API_StatusTypeDef (*set_value)(int32_t))
{
	char start_value[13];
	uint32_t value;

	UTIL_UIntToStr(start_value, get_value().value, parser->max_digits, parser->target_decimal_places, UTIL_LEAD_TRAIL_ZERO_SKIP, UTIL_LEAD_TRAIL_ZERO_SKIP);

	// TODO: Setup UIPAR_Number parser with correct min max values

	UIDN_Setup(uidn, parser, cursor_position);

	API_StatusTypeDef status = UIDN_Show(uidn, description, start_value, unit, &value);
	if (status != API_OK)
	{
		return status;
	}

	if (set_value == NULL)
	{
		return API_OK;
	}

	status = set_value(value);

	switch (status)
	{
		case API_OK:
			break;

		case API_PARAM_OUT_OF_RANGE:
			APP_Run_SystemBeeperBeepError();
			UIDI_Show("OUT OF RANGE", UIDI_DEFAULT_TIMEOUT_MEDIUM, true);
			break;

		case API_HARDWARE_ERROR:
		default:
			APP_Run_SystemBeeperBeepError();
			UIDI_Show("INTERNAL ERROR", UIDI_DEFAULT_TIMEOUT_MEDIUM, true);
			break;
	}

	return status;
}

/* Private functions ---------------------------------------------------------*/

