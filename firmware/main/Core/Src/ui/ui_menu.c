/**
 * @file    ui_app_menu.c
 * @author  sebas
 * @date    23.11.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>
#include <string.h>

#include "ui/display_helper.h"
#include "ui/annunciator_helper.h"
#include "ui/ui_menu.h"

#include "cmsis_os2.h"

#include "ui/dialog/ui_dialog_info.h"

#include "ui/switch_array_def.h"
#include "ui/encoder_def.h"

#include "application/app_display.h"
#include "application/app_input.h"
#include "application/app_system.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

void _UIMENU_ProcessEncoder(UIMENU_TypeDef *uimenu);
void _UIMENU_ProcessSwitches(UIMENU_TypeDef *uimenu);

void _UIMENU_Action_Up(UIMENU_TypeDef *uimenu);
void _UIMENU_Action_Down(UIMENU_TypeDef *uimenu);
void _UIMENU_Action_Left(UIMENU_TypeDef *uimenu);
void _UIMENU_Action_Enter(UIMENU_TypeDef *uimenu);
void _UIMENU_Action_Abort(UIMENU_TypeDef *uimenu);

void _UIMENU_Display(const char* Text);

/* Exported functions --------------------------------------------------------*/

void UIMENU_SetRoot(UIMENU_TypeDef *uimenu, MENUITEM_TypeDef *root)
{
	MENU_SetRoot(&uimenu->_menu, root);
}

API_StatusTypeDef UIMENU_Show(UIMENU_TypeDef *uimenu, MENUITEM_TypeDef *item, bool show_applied)
{
	uimenu->_state = UIMENU_ENTRY;
	uimenu->_show_applied = show_applied;
	uimenu->_show_info = false;

	// Discard old switch and encoder values
	SWA_SkipAll_KeyCodes();
	ENC_SkipAll_Counts();

	MENU_Init(&uimenu->_menu, false, false);
	MENU_SetGenericWriteCallback(&uimenu->_menu, _UIMENU_Display);
	MENU_Navigate(&uimenu->_menu, item);

	// Loop
	while (APP_Get_DisplayEnable() && !APP_Get_DisplayUserTextState()
			&& uimenu->_state == UIMENU_ENTRY)
	{
		// Process inputs
		_UIMENU_ProcessEncoder(uimenu);
		_UIMENU_ProcessSwitches(uimenu);

		// Update annunciator
		ANNH_Update();

		osDelay(UI_LOOP_DELAY);
	}

	// Now let's check the result
	if (uimenu->_state == UIMENU_ABORTED)
	{
		return API_ABORTED;
	}

	return API_OK;
}

/* Private functions ---------------------------------------------------------*/


void _UIMENU_ProcessEncoder(UIMENU_TypeDef *uimenu)
{
	int16_t count = 0;

	if (!ENC_Get_Count(&count))
	{
		return;
	}

	APP_Run_SystemBeeperTick();

	while (count > 0)
	{
		_UIMENU_Action_Down(uimenu);
		count--;
	}
	while (count < 0)
	{
		_UIMENU_Action_Up(uimenu);
		count++;
	}
}


void _UIMENU_ProcessSwitches(UIMENU_TypeDef *uimenu)
{
	// Check for new key press
	SWA_KeyCodeTypeDef code = SWA_Get_KeyCode();

	if (code == SW_NONE)
	{
		return;
	}

	APP_Run_SystemBeeperBeepShort();

	switch (code)
	{
		case SW_UP: _UIMENU_Action_Up(uimenu); break;

		case SW_DOWN: _UIMENU_Action_Down(uimenu); break;

		case SW_BACK_DISP: _UIMENU_Action_Left(uimenu); break;

		case SW_ROT_ENT:
		case SW_ENTER: _UIMENU_Action_Enter(uimenu); break;

		case SW_MENU:
		case SW_SH_ENTER: _UIMENU_Action_Abort(uimenu); break;

		case SW_INP: APP_Run_InputStateToggle(); break;

		default: break;
	}
}


void _UIMENU_Action_Up(UIMENU_TypeDef *uimenu)
{
	if (MENU_NavigateUp(&uimenu->_menu) != API_OK && uimenu->_show_info)
	{
		UIDI_Show("FIRST ENTRY", UIDI_DEFAULT_TIMEOUT_SHORT, true);
		MENU_InvalidateText(&uimenu->_menu);
	}
}


void _UIMENU_Action_Down(UIMENU_TypeDef *uimenu)
{
	if (MENU_NavigateDown(&uimenu->_menu) != API_OK && uimenu->_show_info)
	{
		UIDI_Show("LAST ENTRY", UIDI_DEFAULT_TIMEOUT_SHORT, true);
		MENU_InvalidateText(&uimenu->_menu);
	}
}


void _UIMENU_Action_Left(UIMENU_TypeDef *uimenu)
{
	if (MENU_NavigateLeft(&uimenu->_menu) != API_OK)
	{
		uimenu->_state = UIMENU_ABORTED;

		if (uimenu->_show_info)
		{
			UIDI_Show("EXITING MENU", UIDI_DEFAULT_TIMEOUT_SHORT, true);
		}
	}
}


void _UIMENU_Action_Enter(UIMENU_TypeDef *uimenu)
{
	MENUITEM_TypeDef *child = MENU_CHILD(&uimenu->_menu);

	if (child == &NULL_MENU || child == NULL)
	{
		// Enter if no sub menu available
		API_StatusTypeDef status = MENU_EnterCurrentItem(&uimenu->_menu);

		if (status == API_TERMINATED)
		{
			_UIMENU_Action_Abort(uimenu);
			return;
		}

		if (status == API_UNCHANGED)
		{
			// Do nothing
		}
		else if (status == API_OK)
		{
			if (uimenu->_show_applied)
			{
				UIDI_Show("APPLIED", UIDI_DEFAULT_TIMEOUT_SHORT, true);
			}
		}
		else if (status == API_ABORTED)
		{
			if (uimenu->_show_info)
			{
				UIDI_Show("ABORTED", UIDI_DEFAULT_TIMEOUT_SHORT, true);
			}
		}
		else
		{
			UIDI_Show("ERROR OCCURRED", UIDI_DEFAULT_TIMEOUT_SHORT, true);
		}

		MENU_InvalidateText(&uimenu->_menu);

		return;
	}

	// Navigate right otherwise
	if (MENU_NavigateRight(&uimenu->_menu) != API_OK && uimenu->_show_applied)
	{
		UIDI_Show("NOT IMPLEMENTED", UIDI_DEFAULT_TIMEOUT_SHORT, true);
		MENU_InvalidateText(&uimenu->_menu);
	}
}


void _UIMENU_Action_Abort(UIMENU_TypeDef *uimenu)
{
	uimenu->_state = UIMENU_ABORTED;
	if (uimenu->_show_info)
	{
		UIDI_Show("EXITING MENU", UIDI_DEFAULT_TIMEOUT_SHORT, true);
	}
}


void _UIMENU_Display(const char* str)
{
	UI_Display_Update(str);
	ANNH_Update();
}

