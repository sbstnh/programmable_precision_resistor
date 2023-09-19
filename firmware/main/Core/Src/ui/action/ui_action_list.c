/**
 * @file    ui_action_list.c
 * @author  sebas
 * @date    24.04.2023
 * @brief
 */

/* Includes ------------------------------------------------------------------*/


#include "ui/action/ui_action_list.h"
#include "ui/action/ui_action_util.h"
#include "application/app_source.h"
#include "application/app_system.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/

UIDE_ChoiceTypeDef UIACT_LIST_START_CHOICE[] =
{
		{ "AUTO",    LIST_START_AUTO },
		{ "TRIGger", LIST_START_TRIGger },
		UIDE_CHOICE_LIST_END
};


UIDE_ChoiceTypeDef UIACT_LIST_STEP_CHOICE[] =
{
		{ "AUTO",    LIST_STEP_AUTO },
		{ "TRIGger", LIST_STEP_TRIGger },
		{ "ONCE",    LIST_STEP_ONCE },
		UIDE_CHOICE_LIST_END
};

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

INT_VALUE_TypeDef _int_value_helper;

/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

API_StatusTypeDef _APP_Set_SourceListResistanceIndexHelper(int32_t length);
INT_VALUE_TypeDef _APP_Get_SourceListResistanceIndexHelper();

API_StatusTypeDef _UIACT_ListValue(UIPAR_TypeDef *parser, const char *unit, int32_t list_pos, uint8_t decimal_places,
		API_StatusTypeDef (*get_value)(int32_t, int32_t *), API_StatusTypeDef (*set_value)(int32_t, int32_t));

/* Exported functions --------------------------------------------------------*/

API_StatusTypeDef UIACT_ListResDwell()
{
	UIDN_TypeDef uidn;
	API_StatusTypeDef result;

	_int_value_helper.value = 0;

	while (true)
	{
		result = UIACT_UtilDialogIntValueTypeDef(&uidn,
			&UIPAR_LIST,
			"INDex",
			"",
			UIDN_CURSOR_START,
			_APP_Get_SourceListResistanceIndexHelper,
			_APP_Set_SourceListResistanceIndexHelper);

		if (result == API_ERROR)
		{
			continue;
		}
		if (result == API_ABORTED || result == API_TERMINATED)
		{
			return result;
		}

		result = _UIACT_ListValue(
				&UIPAR_TIME,
				"s",
				_APP_Get_SourceListResistanceIndexHelper().value,
				2,
				APP_Get_SourceListResistanceDwellValues,
				APP_Set_SourceListResistanceDwellValues);

		if (result == API_OK)
		{
			UIDI_Show("APPLIED", UIDI_DEFAULT_TIMEOUT_MEDIUM, true);
		}
		if (result == API_ABORTED || result == API_TERMINATED)
		{
			return result;
		}
	}

	return result;
}


API_StatusTypeDef UIACT_ListResDwellPoints()
{
	UIDN_TypeDef uidn;

	return UIACT_UtilDialogIntValueTypeDef(&uidn,
			&UIPAR_UINT,
			"POINts",
			"",
			UIDN_CURSOR_START,
			APP_Get_SourceListResistanceDwellLength,
			APP_Set_SourceListResistanceDwellLength);
}


API_StatusTypeDef UIACT_ListResIndex()
{
	return UIACT_UtilDialogInfoInt("INDex", "", APP_Get_SourceListResistanceIndex().value, 9, 0);
}


API_StatusTypeDef UIACT_ListResLevel()
{
	UIDN_TypeDef uidn;
	API_StatusTypeDef result;

	_int_value_helper.value = 0;

	while (true)
	{
		result = UIACT_UtilDialogIntValueTypeDef(&uidn,
			&UIPAR_LIST,
			"INDex",
			"",
			UIDN_CURSOR_START,
			_APP_Get_SourceListResistanceIndexHelper,
			_APP_Set_SourceListResistanceIndexHelper);

		if (result == API_ERROR)
		{
			continue;
		}
		if (result == API_ABORTED || result == API_TERMINATED)
		{
			return result;
		}

		result = _UIACT_ListValue(
				&UIPAR_RESISTANCE,
				"OHM",
				_APP_Get_SourceListResistanceIndexHelper().value,
				3,
				APP_Get_SourceListResistanceLevelValues,
				APP_Set_SourceListResistanceLevelValues);

		if (result == API_OK)
		{
			UIDI_Show("APPLIED", UIDI_DEFAULT_TIMEOUT_MEDIUM, true);
		}
	}

	return result;
}


API_StatusTypeDef UIACT_ListResPoints()
{
	UIDN_TypeDef uidn;

	return UIACT_UtilDialogIntValueTypeDef(&uidn,
			&UIPAR_UINT,
			"POINts",
			"",
			UIDN_CURSOR_START,
			APP_Get_SourceListResistanceLength,
			APP_Set_SourceListResistanceLength);
}


API_StatusTypeDef UIACT_ListResRunNumber()
{
	return UIACT_UtilDialogInfoInt("NUMBer", "", APP_Get_SourceListResistanceRunNumber().value, 9, 0);
}


API_StatusTypeDef UIACT_ListResRunCount()
{
	UIDN_TypeDef uidn;

	return UIACT_UtilDialogIntValueTypeDef(&uidn,
			&UIPAR_UINT,
			"COUNt",
			"",
			UIDN_CURSOR_START,
			APP_Get_SourceListResistanceRunCount,
			APP_Set_SourceListResistanceRunCount);
}


API_StatusTypeDef UIACT_ListStartInput()
{
	return UIACT_UtilDialogEnum("INPut",
			UIACT_BOOL,
			(ENUM_GETTER_TYPE) APP_Get_SourceListStartInput,
			(ENUM_SETTER_TYPE) APP_Set_SourceListStartInput);
}


API_StatusTypeDef UIACT_ListStartMode()
{
	return UIACT_UtilDialogEnum("STARt",
			UIACT_LIST_START_CHOICE,
			(ENUM_GETTER_TYPE) APP_Get_SourceListStartMode,
			(ENUM_SETTER_TYPE) APP_Set_SourceListStartMode);
}


API_StatusTypeDef UIACT_ListStep()
{
	return UIACT_UtilDialogEnum("STEP",
			UIACT_LIST_STEP_CHOICE,
			(ENUM_GETTER_TYPE) APP_Get_SourceListStep,
			(ENUM_SETTER_TYPE) APP_Set_SourceListStep);
}


API_StatusTypeDef UIACT_ListTerminateInput()
{
	return UIACT_UtilDialogEnum("INPut",
			UIACT_BOOL,
			(ENUM_GETTER_TYPE) APP_Get_SourceListTerminateInput,
			(ENUM_SETTER_TYPE) APP_Set_SourceListTerminateInput);
}


API_StatusTypeDef UIACT_ListTerminateLast()
{
	return UIACT_UtilDialogEnum("LAST",
			UIACT_BOOL,
			(ENUM_GETTER_TYPE) APP_Get_SourceListTerminateLast,
			(ENUM_SETTER_TYPE) APP_Set_SourceListTerminateLast);
}

/* Private functions ---------------------------------------------------------*/


API_StatusTypeDef _APP_Set_SourceListResistanceIndexHelper(int32_t length)
{
	// Check if equal
	RETURN_OK_IF_TRUE(_int_value_helper.value == length);

	// Check for value out of range
	if (!IN_RANGE(0, SOUR_LIST_LENGTH - 1, length))
	{
		return API_PARAM_OUT_OF_RANGE;
	}

	// Finally set index
	_int_value_helper.value = length;

	return API_OK;
}

INT_VALUE_TypeDef _APP_Get_SourceListResistanceIndexHelper()
{
	return _int_value_helper;
}


API_StatusTypeDef _UIACT_ListValue(UIPAR_TypeDef *parser, const char *unit, int32_t list_pos, uint8_t decimal_places,
		API_StatusTypeDef (*get_value)(int32_t, int32_t *), API_StatusTypeDef (*set_value)(int32_t, int32_t))
{
	UIDN_TypeDef uidn;

	// Obtain old value
	char default_value[13];
	int32_t current_value;

	if (get_value(list_pos, &current_value) != API_OK)
	{
		return API_ERROR;
	}

	UTIL_UIntToStr(default_value, current_value, 10, decimal_places, UTIL_LEAD_TRAIL_ZERO_SKIP, UTIL_LEAD_TRAIL_ZERO_SKIP);

	uint32_t resistance;

	UIDN_Setup(&uidn, parser, UIDN_CURSOR_START);

	API_StatusTypeDef status = UIDN_Show(&uidn, "VALue", default_value, unit, &resistance);
	if (status != API_OK)
	{
		return status;
	}

	status = set_value(list_pos, resistance);

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
