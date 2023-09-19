/**
 * @file    ui_action_input.c
 * @author  sebas
 * @date    Jan 15, 2023
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "ui/action/ui_action_input.h"
#include "ui/action/ui_action_util.h"
#include "application/app_input.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/

UIDE_ChoiceTypeDef UIACT_INH_MODE_CHOICE[] =
{
		{ "OFF",		INH_MODE_OFF },
		{ "LATChing",	INH_MODE_LATChing },
		{ "LIVE",		INH_MODE_LIVE },
		UIDE_CHOICE_LIST_END
};

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

API_StatusTypeDef UIACT_InputInhibitMode()
{
	return UIACT_UtilDialogEnum("MODE",
			UIACT_INH_MODE_CHOICE,
			(ENUM_GETTER_TYPE) APP_Get_InputInhibitMode,
			(ENUM_SETTER_TYPE) APP_Set_InputInhibitMode);
}


API_StatusTypeDef UIACT_InputInhibitClear()
{
	API_StatusTypeDef status = APP_Set_InputInhibitState(false);

	if (status != API_OK)
	{
		UIDI_Show("NOT CLEARED", UIDI_DEFAULT_TIMEOUT_MEDIUM, true);
	}
	else
	{
		UIDI_Show("CLEARED", UIDI_DEFAULT_TIMEOUT_MEDIUM, true);
	}

	return API_UNCHANGED;
}


API_StatusTypeDef UIACT_InputInhibitState()
{
	return UIACT_UtilDialogEnum("STATe",
			UIACT_BOOL,
			(ENUM_GETTER_TYPE) APP_Get_InputInhibitState,
			(ENUM_SETTER_TYPE) APP_Set_InputInhibitState);
}

/* Private functions ---------------------------------------------------------*/

