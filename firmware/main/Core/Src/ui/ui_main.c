/**
 * @file    ui_app_main.c
 * @author  sebas
 * @date    23.11.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include <string.h>
#include "ui/action/ui_action_display.h"
#include "ui/action/ui_action_resistance.h"
#include "ui/action/ui_action_trigger.h"

#include "cmsis_os2.h"

#include "ui/ui_main.h"

#include "ui/display_helper.h"
#include "ui/annunciator_helper.h"

#include "ui/ui.h"
#include "ui/dialog/ui_dialog_number.h"
#include "ui/dialog/ui_dialog_info.h"

#include "ui/switch_array_def.h"

#include "ui/ui_menu.h"
#include "application/app_calibration.h"
#include "application/app_display.h"
#include "application/app_input.h"
#include "application/app_source.h"
#include "application/app_system.h"
#include "application/app_trigger.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

// This dialog is defined as a global variable in order to keep the current
// cursor position for the ui dialog
static UIDN_TypeDef uidn_immediate;


/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

void _UIMAIN_Keyboard();
void _UIMAIN_Display();

void _UIMAIN_Action_Channel();
void _UIMAIN_Action_Recall();
void _UIMAIN_Action_Mode();
void _UIMAIN_Action_ShiftMode();
void _UIMAIN_Action_Menu();

void _UIMAIN_Action_Error();
void _UIMAIN_Action_Extern();
void _UIMAIN_Action_Inhibit();
void _UIMAIN_Action_Trigger();
void _UIMAIN_Action_Param();
void _UIMAIN_Action_Limit();
void _UIMAIN_Action_System();

void _UIMAIN_Action_Entry(const char *default_value, UIDN_CursorPosTypeDef cursor_position);
void _UIMAIN_Action_Entry_WithImmediate(UIDN_CursorPosTypeDef cursor_position);

void _UIMAIN_Action_Disp();

void _UIMAIN_Action_Input();
void _UIMAIN_Action_Up();
void _UIMAIN_Action_Down();


/* Exported functions --------------------------------------------------------*/

void UIMAIN_Show()
{
	SWA_Reset_Shift(&SWA);

	while (APP_Get_DisplayEnable() && !APP_Get_DisplayUserTextState() && !APP_Get_CalibrationState())
	{
		_UIMAIN_Keyboard();
		_UIMAIN_Display();
		osDelay(UI_LOOP_DELAY);
	}
}


/* Private functions ---------------------------------------------------------*/

void _UIMAIN_Keyboard()
{
	SWA_KeyCodeTypeDef code = SWA_Peek_KeyCode();

	if (code == SW_NONE)
	{
		return;
	}

	APP_Run_SystemBeeperBeepShort();

	switch (code)
	{
		case SW_CH: _UIMAIN_Action_Channel(); break;
		case SW_SH_RCL: _UIMAIN_Action_Recall(); break;

		case SW_MODE: _UIMAIN_Action_Mode(); break;
		case SW_SH_MODE: _UIMAIN_Action_ShiftMode(); break;
		case SW_MENU: _UIMAIN_Action_Menu(); break;

		case SW_SH_ERR: _UIMAIN_Action_Error(); break;
		case SW_SH_CALM: UIACT_ResistanceCalMode(); break;

		case SW_SH_EXT: _UIMAIN_Action_Extern(); break;
		case SW_SH_INH: _UIMAIN_Action_Inhibit(); break;
		case SW_SH_TRIG: _UIMAIN_Action_Trigger(); break;
		case SW_SH_PAR: _UIMAIN_Action_Param(); break;
		case SW_SH_LIM: _UIMAIN_Action_Limit(); break;
		case SW_SH_SWIT: UIACT_ResistanceSwitchingMode(); break;
		case SW_SH_DIGIT: UIACT_DisplayResolution(); break;


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
			UIACT_ResistanceImmediateValue_New(&uidn_immediate, NULL, UIDN_CURSOR_END);
			break;

		case SW_BACKSP:
		case SW_ENTER:
		case SW_ROT_ENT:
			SWA_Get_KeyCode();
			UIACT_ResistanceImmediateValue_Edit(&uidn_immediate, UIDN_CURSOR_LEAVE);
			break;
		case SW_LEFT:
			SWA_Get_KeyCode();
			UIACT_ResistanceImmediateValue_Edit(&uidn_immediate, UIDN_CURSOR_END);
			break;
		case SW_RIGHT:
			SWA_Get_KeyCode();
			UIACT_ResistanceImmediateValue_Edit(&uidn_immediate, UIDN_CURSOR_START);
			break;

		// Display
		case SW_BACK_DISP: _UIMAIN_Action_Disp(); break;

		case SW_INP: _UIMAIN_Action_Input(); break;
		case SW_SH_INP_SETUP: _UIMAIN_Action_System(); break;

		//--- Trigger
		case SW_UP: _UIMAIN_Action_Up(); break;
		case SW_DOWN: _UIMAIN_Action_Down(); break;
		default:
			APP_Run_SystemBeeperBeepError();
			break;
	}

	// Make sure that the switch event is handled
	SWA_Get_KeyCode();
}


void _UIMAIN_Display()
{
	char str[32];

	memset(str, 0, sizeof(str));

	UI_Display_SectionModeIndicator(str, APP.SOURce.RESistance.MODE);
	strcat(str, " ");
	UI_Display_SectionPrimary(str + strlen(str));
	strcat(str, " ");
	UI_DisplaySectionSecondary(str + strlen(str));

	UI_Display_Update(str);
	ANNH_Update();
}


void _UIMAIN_Action_Channel()
{
	SWA_Get_KeyCode();
	UIDI_Show("CHANNEL 1", UIDI_DEFAULT_TIMEOUT_MEDIUM, true);
}


void _UIMAIN_Action_Recall()
{
	UIMENU_TypeDef uimenu;
	UIMENU_Show(&uimenu, &MENU_RCL, true);
}


void _UIMAIN_Action_Mode()
{
	SWA_Get_KeyCode();
	UIACT_SourceResistanceMode();
}


void _UIMAIN_Action_ShiftMode()
{
	SWA_Get_KeyCode();
	APP_Set_SourceResistanceMode(RES_MODE_FIXed);
}


void _UIMAIN_Action_Menu()
{
	UIMENU_TypeDef uimenu;
	UIMENU_Show(&uimenu, &MENU_CAL, true);
}


void _UIMAIN_Action_Error()
{
	UIMENU_TypeDef uimenu;
	UIMENU_SetRoot(&uimenu, &MENU_ERR_COUN);
	UIMENU_Show(&uimenu, &MENU_ERR_COUN, true);
}

void _UIMAIN_Action_Extern()
{
	UIMENU_TypeDef uimenu;
	UIMENU_SetRoot(&uimenu, &MENU_DIG_PIN1);
	UIMENU_Show(&uimenu, &MENU_DIG_PIN1, true);
}

void _UIMAIN_Action_Inhibit()
{
	UIMENU_TypeDef uimenu;
	UIMENU_SetRoot(&uimenu, &MENU_INH_MODE);
	UIMENU_Show(&uimenu, &MENU_INH_MODE, true);
}

void _UIMAIN_Action_Trigger()
{
	UIMENU_TypeDef uimenu;
	UIMENU_SetRoot(&uimenu, &MENU_SEQ_DEL);
	UIMENU_Show(&uimenu, &MENU_SEQ_DEL, true);
}

void _UIMAIN_Action_Param()
{
	UIMENU_TypeDef uimenu;
	MENUITEM_TypeDef *root = APP_Get_SourceResistanceMode() == RES_MODE_LIST ? &MENU_DWEL : &MENU_LEV_IMM;

	UIMENU_SetRoot(&uimenu, root);
	UIMENU_Show(&uimenu, root, true);
}

void _UIMAIN_Action_Limit()
{
	UIMENU_TypeDef uimenu;
	UIMENU_SetRoot(&uimenu, &MENU_LIM_LOW);
	UIMENU_Show(&uimenu, &MENU_LIM_LOW, true);
}

void _UIMAIN_Action_System()
{
	UIMENU_TypeDef uimenu;
	UIMENU_SetRoot(&uimenu, &MENU_SYST_BEEP);
	UIMENU_Show(&uimenu, &MENU_SYST_BEEP, true);
}


void _UIMAIN_Action_Disp()
{
	SWA_Get_KeyCode();
	APP_Run_DisplaySecondaryModeNext();
}


void _UIMAIN_Action_Input()
{
	SWA_Get_KeyCode();
	APP_Run_InputStateToggle();
}


void _UIMAIN_Action_Up()
{
	SWA_Get_KeyCode();

	switch (APP_Get_SourceResistanceMode())
	{
		default:
		case RES_MODE_FIXed:
			APP_Run_SourceResistanceLevelImmediateAmplitudeUp(true);
			break;

		case RES_MODE_STEP:
		case RES_MODE_UP:
		case RES_MODE_DOWN:
		case RES_MODE_LIST:
			UIACT_TriggerRunStop();
			break;
	}
}


void _UIMAIN_Action_Down()
{
	SWA_Get_KeyCode();

	switch (APP_Get_SourceResistanceMode())
	{
		default:
		case RES_MODE_FIXed:
			APP_Run_SourceResistanceLevelImmediateAmplitudeDown(true);
			break;

		case RES_MODE_STEP:
		case RES_MODE_UP:
		case RES_MODE_DOWN:
		case RES_MODE_LIST:
			UIACT_TriggerSingleShotForce();
			break;
	}
}
