/**
 * @file    ui_action_system.c
 * @author  sebas
 * @date    01.01.2023
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>

#include "ui/action/ui_action_system.h"
#include "ui/action/ui_action_util.h"
#include "ui/dialog/ui_dialog_enum.h"
#include "ui/dialog/ui_dialog_info.h"
#include "ui/dialog/ui_dialog_temp.h"

#include "application/app_source.h"
#include "application/app_system.h"

#include "communication/scpi_def.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/

UIDE_ChoiceTypeDef UIACT_POLARITY_CHOICE[] =
{
		{ "POSitive",	PIN_POL_POSitive },
		{ "NEGative",	PIN_POL_NEGative },
		UIDE_CHOICE_LIST_END
};

UIDE_ChoiceTypeDef UIACT_FUNCTION_CHOICE[] =
{
		{ "DIGital",	PIN_FUNC_DINPut },
		{ "INHibit",	PIN_FUNC_INHibit },
		{ "TRIGger",	PIN_FUNC_TINPut },
		UIDE_CHOICE_LIST_END
};

UIDE_ChoiceTypeDef UIACT_TEMP_DISP_STATE[] =
{
		{ "IMM:",	UIDT_STATE_IMMEDIATE },
		{ "MIN:",	UIDT_STATE_MINIMUM },
		{ "MAX:",	UIDT_STATE_MAXIMUM },
		{ "AVG:",	UIDT_STATE_AVERAGE },
		UIDE_CHOICE_LIST_END
};

UIDE_ChoiceTypeDef UIACT_RESTORE_CHOICE[] =
{
		{ "NO",		false },
		{ "YES",	true },
		UIDE_CHOICE_LIST_END
};


/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

API_StatusTypeDef UIACT_SystemBeeper()
{
	return UIACT_UtilDialogEnum("STATe",
			UIACT_BOOL,
			(ENUM_GETTER_TYPE) APP_Get_SystemBeeperState,
			(ENUM_SETTER_TYPE) APP_Set_SystemBeeperState);
}


API_StatusTypeDef UIACT_SystemDefaultImmediate()
{
	UIDE_TypeDef dialog;
	int32_t result;

	API_StatusTypeDef status = UIDE_Show(&dialog, "RESTORE DEF", UIACT_RESTORE_CHOICE, false, false, &result, NULL);

	if (status != API_OK)
	{
		return status;
	}

	if (result)
	{
		return APP_Run_SystemDefaultImmediate();
	}

	return API_ABORTED;
}


API_StatusTypeDef UIACT_SystemDigitalInputPolarity1()
{
	return UIACT_UtilDialogEnum("POLarity",
			UIACT_POLARITY_CHOICE,
			(ENUM_GETTER_TYPE) APP_Get_SourceDigitalPin1Polarity,
			(ENUM_SETTER_TYPE) APP_Set_SourceDigitalPin1Polarity);
}


API_StatusTypeDef UIACT_SystemDigitalInputFunction1()
{
	return UIACT_UtilDialogEnum("FUNCtion",
			UIACT_FUNCTION_CHOICE,
			(ENUM_GETTER_TYPE) APP_Get_SourceDigitalPin1Function,
			(ENUM_SETTER_TYPE) APP_Set_SourceDigitalPin1Function);
}


API_StatusTypeDef UIACT_SystemDigitalInputPolarity2()
{
	return UIACT_UtilDialogEnum("POLarity",
			UIACT_POLARITY_CHOICE,
			(ENUM_GETTER_TYPE) APP_Get_SourceDigitalPin2Polarity,
			(ENUM_SETTER_TYPE) APP_Set_SourceDigitalPin2Polarity);
}

API_StatusTypeDef UIACT_SystemDigitalInputFunction2()
{
	return UIACT_UtilDialogEnum("FUNCtion",
			UIACT_FUNCTION_CHOICE,
			(ENUM_GETTER_TYPE) APP_Get_SourceDigitalPin2Function,
			(ENUM_SETTER_TYPE) APP_Set_SourceDigitalPin2Function);
}


API_StatusTypeDef UIACT_SystemErrorCount()
{
	return UIACT_UtilDialogInfoInt("COUNt", "", SCPI_ErrorCount(&scpi_context), 8, 0);
}


API_StatusTypeDef UIACT_SystemErrorNext()
{
	if (!SCPI_ErrorCount(&scpi_context))
	{
		UIDI_Show("NO ERRORS", UIDI_DEFAULT_TIMEOUT_MEDIUM, true);
		return API_UNCHANGED;
	}

	while (SCPI_ErrorCount(&scpi_context))
	{
		char str[64] = "\0";
		scpi_error_t error;
		SCPI_ErrorPop(&scpi_context, &error);

		int16_t error_code = error.error_code;

		if (error.error_code < 0)
		{
			strcat(str, "-");
			error_code = -error_code;
		}

		UTIL_UIntToStr(str + strlen(str),
				error_code,
				5,
				0,
				UTIL_LEAD_TRAIL_ZERO_SKIP,
				UTIL_LEAD_TRAIL_ZERO_ZERO);

		strcat(str, ":");
		strcat(str, SCPI_ErrorTranslate(error.error_code));

		if (UIDI_Show(str, 0, false) == API_TERMINATED)
		{
			break;
		}
	}

	return API_UNCHANGED;
}


API_StatusTypeDef UIACT_SystemFirmwareVersionMainboard()
{
	const char *str = APP_Get_SystemFirmwareVersionMainboard();

	if (UTIL_StrLenDisplay(str, APP_SYS_FIRM_VERS_MAX_LEN) > 0)
	{
		return UIDI_Show(str, 0, false);
	}

	return UIDI_Show("UNKNOWN FIRMWARE", 0, false);
}


API_StatusTypeDef UIACT_SystemFirmwareVersionUI()
{
	const char *str = APP_Get_SystemFirmwareVersionUI();

	if (UTIL_StrLenDisplay(str, APP_SYS_FIRM_VERS_MAX_LEN) > 0)
	{
		return UIDI_Show(str, 0, false);
	}

	return UIDI_Show("UNKNOWN FIRMWARE", 0, false);
}



API_StatusTypeDef UIACT_SystemSecurityImmediate()
{
	UIDE_TypeDef dialog;
	int32_t result;

	API_StatusTypeDef status = UIDE_Show(&dialog, "RESTORE ALL", UIACT_RESTORE_CHOICE, false, false, &result, NULL);

	if (status != API_OK)
	{
		return status;
	}

	if (result)
	{
		return APP_Run_SystemSecurityImmediate();
	}

	return API_ABORTED;
}


API_StatusTypeDef UIACT_SystemTemperature()
{
	UIDE_TypeDef dialog;
	int32_t result;

	if (UIDE_Show(&dialog, NULL, UIACT_TEMP_DISP_STATE, UIDT_STATE_IMMEDIATE, false, &result, _UIDT_Display) == API_TERMINATED)
	{
		return API_TERMINATED;
	}

	return API_UNCHANGED;
}


API_StatusTypeDef UIACT_SystemTemperatureReset()
{
	APP_Run_SystemTempReset(TEMP_SEL_ALL);

	return UIDI_Show("APPLIED", UIDI_DEFAULT_TIMEOUT_MEDIUM, true);
}

/* Private functions ---------------------------------------------------------*/

