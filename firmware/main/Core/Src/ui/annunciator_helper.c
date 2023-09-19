/**
 * @file    annunciator_helper.c
 * @author  sebas
 * @date    16.01.2023
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "ui/annunciator_helper.h"
#include "ui/annunciator_array_def.h"
#include "ui/switch_array_def.h"

#include "application/app_calibration.h"
#include "application/app_input.h"
#include "application/app_source.h"
#include "application/app_system.h"
#include "application/app_trigger.h"

#include "hardware/ui_interface_def.h"

/* Private defines -----------------------------------------------------------*/

#define UI_ANN_TRIGGERED_TIMEOUT		5

/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

static uint8_t _ANNH_TriggeredTimeoutCounter = 0;

/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

void _ANNH_UpdateShift();
void _ANNH_UpdateLocalRemoteError();
void _ANNH_UpdateInput();
void _ANNH_UpdateTriggerRunStop();
void _ANNH_UpdateTriggerSingleForceAndTrigEvent();

/* Exported functions --------------------------------------------------------*/

void ANNH_Update()
{
	_ANNH_UpdateShift();
	_ANNH_UpdateLocalRemoteError();
	_ANNH_UpdateInput();
	_ANNH_UpdateTriggerRunStop();
	_ANNH_UpdateTriggerSingleForceAndTrigEvent();

	UIIF_AnnunciatorSwitch(&UIIF, ANNA_Get_State(&ANNA), false);
	UIIF_AnnunciatorBlink(&UIIF, ANNA_Get_Blink(&ANNA), false);
}


void ANNH_SwitchEntry(bool on)
{
	ANN_SetGreen(&ANNS[ANN_ENTRY], on ? ANN_COLOR_ON : ANN_COLOR_OFF);
}


void ANNH_OnTriggered()
{
	_ANNH_TriggeredTimeoutCounter = UI_ANN_TRIGGERED_TIMEOUT;
}

/* Private functions ---------------------------------------------------------*/

void _ANNH_UpdateShift()
{
	UIIF_AnnunciatorShiftSwitch(&UIIF, SWA_Get_Shift(&SWA), false);
}


void _ANNH_UpdateLocalRemoteError()
{
	switch (APP_Get_SystemCommunicateRLState())
	{
		case COMM_RLST_LOCal: ANN_SetState(&ANNS[ANN_REMOTE], ANN_OFF); break;
		case COMM_RLST_MIXed: ANN_SetState(&ANNS[ANN_REMOTE], ANN_GREEN); break;
		case COMM_RLST_REMote: ANN_SetState(&ANNS[ANN_REMOTE], ANN_ORANGE); break;
		case COMM_RLST_RWLock: ANN_SetState(&ANNS[ANN_REMOTE], ANN_RED); break;
	}

	ANN_Blink(&ANNS[ANN_REMOTE], !APP_Get_CalibrationCalibrated());
}


void _ANNH_UpdateInput()
{
	if (APP_Get_InputState())
	{
		if (APP_Get_SourceMode() == SOUR_MODE_UNCalibrated)
		{
			ANN_SetState(&ANNS[ANN_INPUT], ANN_RED);
		}
		else
		{
			ANN_SetState(&ANNS[ANN_INPUT], ANN_GREEN);
		}
	}
	else
	{
		ANN_SetState(&ANNS[ANN_INPUT], ANN_OFF);
	}

	if (APP_Get_InputInhibitState() && APP_Get_InputState())
	{
		ANN_Blink(&ANNS[ANN_INPUT], true);
	}
	else
	{
		ANN_Blink(&ANNS[ANN_INPUT], false);
	}
}


void _ANNH_UpdateTriggerRunStop()
{
	if (APP_Get_SourceResistanceMode() == RES_MODE_FIXed)
	{
		ANN_SetState(&ANNS[ANN_UP], ANN_OFF);
		return;
	}

	if (APP_Get_TriggerInitiated())
	{
		ANN_SetState(&ANNS[ANN_UP], ANN_GREEN);
	}
	else
	{
		ANN_SetState(&ANNS[ANN_UP], ANN_RED);
	}
}


void _ANNH_UpdateTriggerSingleForceAndTrigEvent()
{
	if (!APP_Get_TriggerInitiateContinuous() && APP_Get_TriggerInitiated())
	{
		// Single shot
		ANN_SetGreen(&ANNS[ANN_DOWN], ANN_COLOR_ON);
	}
	else
	{
		ANN_SetGreen(&ANNS[ANN_DOWN], ANN_COLOR_OFF);
	}

	// Trigger is an event, not a state. Hence it has to be handled via callback.
	// Also the annunciator shall only be lit for a short, pre-defined time
	if (_ANNH_TriggeredTimeoutCounter > 0)
	{
		ANN_SetRed(&ANNS[ANN_DOWN], ANN_COLOR_ON);
		_ANNH_TriggeredTimeoutCounter--;
	}
	else
	{
		ANN_SetRed(&ANNS[ANN_DOWN], ANN_COLOR_OFF);
	}
}
