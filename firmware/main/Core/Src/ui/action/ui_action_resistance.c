/**
 * @file    ui_app_quick.c
 * @author  sebas
 * @date    30.12.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "ui/action/ui_action_resistance.h"
#include "ui/action/ui_action_util.h"
#include "ui/dialog/ui_dialog_enum.h"
#include "ui/dialog/ui_dialog_number.h"
#include "ui/dialog/ui_dialog_info.h"

#include "application/app_source.h"
#include "application/app_system.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

UIDE_ChoiceTypeDef UIACT_OPERATING_MODE_CHOICES[] =
{
		{ "FIXed",			RES_MODE_FIXed },
		{ "STEP on trig",   RES_MODE_STEP },
		{ "UP on trig",		RES_MODE_UP },
		{ "DOWN on trig",	RES_MODE_DOWN },
		{ "LIST",    		RES_MODE_LIST },
		UIDE_CHOICE_LIST_END
};


UIDE_ChoiceTypeDef UIACT_CAL_MODE_CHOICES[] =
{
		{ "UNCal",		SOUR_MODE_UNCalibrated },
		{ "TWIRe (2W)",	SOUR_MODE_TWIRe },
		{ "FWIRe (4W)",	SOUR_MODE_FWIRe },
		UIDE_CHOICE_LIST_END
};


UIDE_ChoiceTypeDef UIACT_STEP_MODE_CHOICES[] =
{
		{ "LINear",		STEP_MODE_LINear },
		{ "LDECade",	STEP_MODE_LDECade },
		{ "L125",		STEP_MODE_L125 },
		{ "L13",		STEP_MODE_L13 },
		UIDE_CHOICE_LIST_END
};


UIDE_ChoiceTypeDef UIACT_STEP_OVERFLOW_CHOICES[] =
{
		{ "LIMit",   STEP_OVER_LIMit },
		{ "STAY",    STEP_OVER_STAY },
		{ "RESet",   STEP_OVER_RESet },
		UIDE_CHOICE_LIST_END
};


UIDE_ChoiceTypeDef UIACT_RES_SWITCHING_CHOICES[] =
{
		{ "AUTO",    SOUR_SWIT_AUTO },
		{ "BBMake",  SOUR_SWIT_BBMake },
		UIDE_CHOICE_LIST_END
};



/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/


API_StatusTypeDef UIACT_SourceResistanceMode()
{
	return UIACT_UtilDialogEnum("MODE",
			UIACT_OPERATING_MODE_CHOICES,
			(ENUM_GETTER_TYPE) APP_Get_SourceResistanceMode,
			(ENUM_SETTER_TYPE) APP_Set_SourceResistanceMode);
}


API_StatusTypeDef UIACT_ResistanceCalMode()
{
	return UIACT_UtilDialogEnum("MODE",
			UIACT_CAL_MODE_CHOICES,
			(ENUM_GETTER_TYPE) APP_Get_SourceMode,
			(ENUM_SETTER_TYPE) APP_Set_SourceMode);
}


//---- Resistance Immediate Value

API_StatusTypeDef UIACT_ResistanceImmediateValue()
{
	UIDN_TypeDef uidn;
	return UIACT_ResistanceImmediateValue_Edit(&uidn, UIDN_CURSOR_START);
}

API_StatusTypeDef UIACT_ResistanceImmediateValue_Edit(UIDN_TypeDef *uidn, UIDN_CursorPosTypeDef cursor_position)
{
	char default_value[13];
	const int32_t value = APP_Get_SourceResistanceLevelImmediateAmplitude().value;

	UTIL_UIntToStr(default_value, value, 10, 3, UTIL_LEAD_TRAIL_ZERO_SKIP, UTIL_LEAD_TRAIL_ZERO_SKIP);

	return UIACT_ResistanceImmediateValue_New(uidn, default_value, cursor_position);
}


API_StatusTypeDef UIACT_ResistanceImmediateValue_New(UIDN_TypeDef *uidn, const char *default_value, UIDN_CursorPosTypeDef cursor_position)
{
	uint32_t immediate;

	// TODO: Setup UIPAR_Number parser with correct min max values

	UIDN_Setup(uidn, &UIPAR_RESISTANCE, cursor_position);

	API_StatusTypeDef status = UIDN_Show(uidn, "IMM", default_value, "OHM", &immediate);
	if (status != API_OK)
	{
		return status;
	}

	status = APP_Set_SourceResistanceLevelImmediateAmplitude(immediate, true);

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

//---- Resistance Triggered Value

API_StatusTypeDef UIACT_ResistanceTriggeredValue()
{
	UIDN_TypeDef uidn;

	return UIACT_UtilDialogIntValueTypeDef(&uidn,
			&UIPAR_RESISTANCE,
			"TRIG",
			"OHM",
			UIDN_CURSOR_START,
			APP_Get_SourceResistanceLevelTriggeredAmplitude,
			APP_Set_SourceResistanceLevelTriggeredAmplitude);
}

//---- Resistance Step Value

API_StatusTypeDef UIACT_ResistanceStepIncrement()
{
	UIDN_TypeDef uidn;

	return UIACT_UtilDialogIntValueTypeDef(&uidn,
			&UIPAR_RESISTANCE,
			"INC",
			"OHM",
			UIDN_CURSOR_START,
			APP_Get_SourceResistanceLevelStepIncrement,
			APP_Set_SourceResistanceLevelStepIncrement);
}

API_StatusTypeDef UIACT_ResistanceStepMode()
{
	return UIACT_UtilDialogEnum("MODE",
			UIACT_STEP_MODE_CHOICES,
			(ENUM_GETTER_TYPE) APP_Get_SourceResistanceLevelStepMode,
			(ENUM_SETTER_TYPE) APP_Set_SourceResistanceLevelStepMode);
}


API_StatusTypeDef UIACT_ResistanceStepOverflow()
{
	return UIACT_UtilDialogEnum("OVERflow",
			UIACT_STEP_OVERFLOW_CHOICES,
			(ENUM_GETTER_TYPE) APP_Get_SourceResistanceLevelStepOverflow,
			(ENUM_SETTER_TYPE) APP_Set_SourceResistanceLevelStepOverflow);
}

//---- Resistance Limit

API_StatusTypeDef UIACT_ResistanceLimitState()
{
	return UIACT_UtilDialogEnum("STATe",
			UIACT_BOOL,
			(ENUM_GETTER_TYPE) APP_Get_SourceResistanceLimitState,
			(ENUM_SETTER_TYPE) APP_Set_SourceResistanceLimitState);
}

API_StatusTypeDef UIACT_ResistanceLimitLow()
{
	UIDN_TypeDef uidn;

	return UIACT_UtilDialogIntValueTypeDef(&uidn,
			&UIPAR_RESISTANCE,
			"LOWer",
			"OHM",
			UIDN_CURSOR_START,
			APP_Get_SourceResistanceLimitLower,
			APP_Set_SourceResistanceLimitLower);
}

API_StatusTypeDef UIACT_ResistanceLimitHigh()
{
	UIDN_TypeDef uidn;

	return UIACT_UtilDialogIntValueTypeDef(&uidn,
			&UIPAR_RESISTANCE,
			"UPper",
			"OHM",
			UIDN_CURSOR_START,
			APP_Get_SourceResistanceLimitUpper,
			APP_Set_SourceResistanceLimitUpper);
}

//----Resistance Switching

API_StatusTypeDef UIACT_ResistanceSwitchingMode()
{
	return UIACT_UtilDialogEnum("MODE",
			UIACT_RES_SWITCHING_CHOICES,
			(ENUM_GETTER_TYPE) APP_Get_SourceSwitching,
			(ENUM_SETTER_TYPE) APP_Set_SourceSwitching);
}



/* Private functions ---------------------------------------------------------*/


