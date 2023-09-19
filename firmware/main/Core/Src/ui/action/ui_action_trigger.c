/**
 * @file    ui_action_trigger.c
 * @author  sebas
 * @date    06.01.2023
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "ui/action/ui_action_util.h"
#include "ui/dialog/ui_dialog_enum.h"

#include "application/app_trigger.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/

UIDE_ChoiceTypeDef UIACT_TRIGGER_SOURCE_CHOICE[] =
{
		{ "BUS",		SEQ_SOUR_BUS },
		{ "EXTernal",	SEQ_SOUR_EXTernal },
		{ "IMMediate",	SEQ_SOUR_IMMediate },
		{ "MANual",		SEQ_SOUR_MANual },
		{ "TIMer",		SEQ_SOUR_TIMer },
		UIDE_CHOICE_LIST_END
};


UIDE_ChoiceTypeDef UIACT_TRIGGER_SLOPE_CHOICE[] =
{
		{ "POSitive",	SEQ_SLOP_POSITIVE },
		{ "NEGative",	SEQ_SLOP_NEGATIVE },
		{ "EITHer",		SEQ_SLOP_EITHER },
		UIDE_CHOICE_LIST_END
};

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

API_StatusTypeDef UIACT_TriggerSource()
{
	return UIACT_UtilDialogEnum("SOURCe",
			UIACT_TRIGGER_SOURCE_CHOICE,
			(ENUM_GETTER_TYPE) APP_Get_TriggerSequenceSource,
			(ENUM_SETTER_TYPE) APP_Set_TriggerSequenceSource);
}

API_StatusTypeDef UIACT_TriggerDelay()
{
	UIDN_TypeDef uidn;

	return UIACT_UtilDialogIntValueTypeDef(&uidn,
			&UIPAR_TIME,
			"DELay",
			"s",
			UIDN_CURSOR_START,
			APP_Get_TriggerSequenceDelay,
			APP_Set_TriggerSequenceDelay);
}

API_StatusTypeDef UIACT_TriggerHoldoff()
{
	UIDN_TypeDef uidn;

	return UIACT_UtilDialogIntValueTypeDef(&uidn,
			&UIPAR_TIME,
			"HOLDoff",
			"s",
			UIDN_CURSOR_START,
			APP_Get_TriggerSequenceHoldOff,
			APP_Set_TriggerSequenceHoldOff);
}

API_StatusTypeDef UIACT_TriggerSlope()
{
	return UIACT_UtilDialogEnum("SLOPe",
			UIACT_TRIGGER_SLOPE_CHOICE,
			(ENUM_GETTER_TYPE) APP_Get_TriggerSequenceSlope,
			(ENUM_SETTER_TYPE) APP_Set_TriggerSequenceSlope);
}

API_StatusTypeDef UIACT_TriggerTimer()
{
	UIDN_TypeDef uidn;

	return UIACT_UtilDialogIntValueTypeDef(&uidn,
			&UIPAR_TIME,
			"TIMer",
			"s",
			UIDN_CURSOR_START,
			APP_Get_TriggerSequenceTimer,
			APP_Set_TriggerSequenceTimer);
}


API_StatusTypeDef UIACT_TriggerRunStop()
{
	if (APP_Get_TriggerInitiated())
	{
		// Stop trigger
		APP_Set_TriggerInitiateContinuous(false);
		APP_Run_TriggerAbortImmediate();
	}
	else
	{
		// Start continuous trigger (Run)
		APP_Set_TriggerInitiateContinuous(true);
	}

	return API_OK;
}

API_StatusTypeDef UIACT_TriggerSingleShotForce()
{
	if (APP_Get_TriggerInitiateContinuous())
	{
		// If activated, deactivate continuous trigger (Stop)
		APP_Set_TriggerInitiateContinuous(false);
		APP_Run_TriggerAbortImmediate();
	}

	if (APP_Get_TriggerInitiated())
	{
		// If single shot already active, force a trigger (Force)
		if (APP_Get_TriggerSequenceSource() == SEQ_SOUR_MANual)
		{
			APP_Run_TriggerManualTrigger();
		}
		else
		{
			APP_Run_TriggerImmediate();
		}

		// Stop Trigger
		APP_Set_TriggerInitiateContinuous(false);
	}
	else
	{
		// Start single shot (Single)
		return APP_Run_TriggerInitiateImmediate();
	}

	return API_OK;
}

API_StatusTypeDef UIACT_TriggerManual()
{
	APP_Run_TriggerManualTrigger();
	return API_OK;
}


/* Private functions ---------------------------------------------------------*/

