/**
 * @file    ui_cal.c
 * @author  sebas
 * @date    03.03.2023
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include <string.h>

#include "ui/ui_cal.h"
#include "cmsis_os2.h"

#include "ui/display_helper.h"
#include "ui/annunciator_helper.h"

#include "ui/switch_array_def.h"
#include "ui/encoder_def.h"

#include "ui/ui.h"

#include "ui/action/ui_action_calibration.h"
#include "ui/dialog/ui_dialog_number.h"

#include "calibration/calibration.h"

#include "application/app_calibration.h"
#include "application/app_display.h"
#include "application/app_input.h"
#include "application/app_system.h"


/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

// This dialog is defined as a global variable in order to keep the current
// cursor position for the ui dialog
static UIDN_TypeDef uidn_setup;
static UIDN_TypeDef uidn_cal_value;

/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

void _UICAL_Keyboard();
void _UICAL_Encoder();
void _UICAL_Display();

void _UICAL_Action_Input();
void _UICAL_Action_Up();
void _UICAL_Action_Down();

/* Exported functions --------------------------------------------------------*/

void UICAL_Show()
{
	// Discard old switch and encoder values
	SWA_Reset_Shift(&SWA);
	SWA_SkipAll_KeyCodes();
	ENC_SkipAll_Counts();

	while (APP_Get_CalibrationState() && APP_Get_DisplayEnable() && !APP_Get_DisplayUserTextState())
	{
		_UICAL_Keyboard();
		_UICAL_Encoder();
		_UICAL_Display();
		osDelay(UI_LOOP_DELAY);
	}

	SWA_SkipAll_KeyCodes();
}

/* Private functions ---------------------------------------------------------*/


void _UICAL_Keyboard()
{
	SWA_KeyCodeTypeDef code = SWA_Peek_KeyCode();

	if (code == SW_NONE)
	{
		return;
	}

	APP_Run_SystemBeeperBeepShort();

	switch (code)
	{
		// Numeric input

		case SW_0:
		case SW_1:
		case SW_2:
		case SW_3:
		case SW_4:
		case SW_5:
		case SW_6:
		case SW_7:
		case SW_8:
		case SW_9:
		case SW_DP:
			UIACT_CalibrationSetup_New(&uidn_setup, NULL, UIDN_CURSOR_END);
			break;

		case SW_BACKSP:
			SWA_Get_KeyCode();
			UIACT_CalibrationSetup_Edit(&uidn_setup, UIDN_CURSOR_LEAVE);
			break;
		case SW_LEFT:
			SWA_Get_KeyCode();
			UIACT_CalibrationSetup_Edit(&uidn_setup, UIDN_CURSOR_END);
			break;
		case SW_RIGHT:
			SWA_Get_KeyCode();
			UIACT_CalibrationSetup_Edit(&uidn_setup, UIDN_CURSOR_START);
			break;

		case SW_ENTER:
		case SW_ROT_ENT:
			SWA_Get_KeyCode();
			UIACT_CalibrationValue_Edit(&uidn_cal_value, UIDN_CURSOR_END);
			break;

		case SW_INP: _UICAL_Action_Input(); break;

		//--- Trigger
		case SW_UP: _UICAL_Action_Up(); break;
		case SW_DOWN: _UICAL_Action_Down(); break;

		default:
			APP_Run_SystemBeeperBeepError();
			break;
	}

	// Make sure that the switch event is handled
	SWA_Get_KeyCode();
}


void _UICAL_Encoder()
{
	int16_t count = 0;

	if (!ENC_Get_Count(&count))
	{
		return;
	}

	APP_Run_SystemBeeperTick();

	if (count > 0)
	{
		_UICAL_Action_Up();
	}
	else if (count < 0)
	{
		_UICAL_Action_Down();
	}
}


void _UICAL_Display()
{
	char str[20];
	int8_t setup = APP_Get_CalibrationSetup();

	strcpy(str, "CAL SETUP ");

	if (setup == CAL_NO_SETUP)
	{
		strcat(str, "NOT SEL");
	}
	else
	{
		UTIL_UIntToStr(str + strlen(str), setup, 3, 0, UTIL_LEAD_TRAIL_ZERO_SKIP, UTIL_LEAD_TRAIL_ZERO_SKIP);
	}

	UI_Display_Update(str);
}


void _UICAL_Action_Input()
{
	SWA_Get_KeyCode();
	APP_Run_InputStateToggle();
}


void _UICAL_Action_Up()
{
	SWA_Get_KeyCode();
	APP_Run_CalibrationSetupUp();
}


void _UICAL_Action_Down()
{
	SWA_Get_KeyCode();
	APP_Run_CalibrationSetupDown();
}

