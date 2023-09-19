/**
 * @file    ui_dialog_enum.c
 * @author  sebas
 * @date    30.12.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "cmsis_os2.h"

#include <stdbool.h>
#include <string.h>
#include "ui/display_helper.h"
#include "ui/annunciator_helper.h"

#include "util/util.h"
#include "ui/dialog/ui_dialog_enum.h"
#include "ui/dialog/ui_dialog_info.h"
#include "ui/switch_array_def.h"
#include "ui/encoder_def.h"

#include "application/app_display.h"
#include "application/app_input.h"
#include "application/app_system.h"

#include "hardware/ui_interface_def.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

API_StatusTypeDef _UIDE_ProcessEncoder(UIDE_TypeDef *uide);
API_StatusTypeDef _UIDE_ProcessSwitches(UIDE_TypeDef *uide);

API_StatusTypeDef _UIDE_Action_Previous(UIDE_TypeDef *uide);
API_StatusTypeDef _UIDE_Action_Next(UIDE_TypeDef *uide);
API_StatusTypeDef _UIDE_Action_Enter(UIDE_TypeDef *uide);
API_StatusTypeDef _UIDE_Action_Menu(UIDE_TypeDef *uide);
API_StatusTypeDef _UIDE_Action_Abort(UIDE_TypeDef *uide);

int8_t _UIDE_FindIndex(UIDE_ChoiceTypeDef *choices, int32_t tag);
uint8_t _UIDE_LenChoices(UIDE_ChoiceTypeDef *choices);

void _UIDE_Display(UIDE_TypeDef *uide);

/* Exported functions --------------------------------------------------------*/

API_StatusTypeDef UIDE_Show(UIDE_TypeDef *uide, const char *description, UIDE_ChoiceTypeDef *choices,
		int32_t current_value, bool allow_wrap, int32_t *result, void (*display_func)(struct uide_t *))
{
	uide->_state = UIDE_ENTRY;
	uide->_show_info = false;

	// Discard old switch and encoder values
	SWA_SkipAll_KeyCodes();
	ENC_SkipAll_Counts();

	//Initialize dialog variables
	uide->_description = description;
	uide->_choices = choices;
	uide->_allow_wrap = allow_wrap;
	uide->_index_current_value = _UIDE_FindIndex(choices, current_value);
	uide->_index_selected = uide->_index_current_value;
	uide->_index_max = _UIDE_LenChoices(choices) - 1;
	uide->_display_func = display_func;

	// Check whether start index actually exists
	if (uide->_index_selected > uide->_index_max)
	{
		return API_ERROR;
	}

	// Entry Annunciator on
	ANNH_SwitchEntry(true);

	// Loop
	while (APP_Get_DisplayEnable() && !APP_Get_DisplayUserTextState()
			&& uide->_state == UIDE_ENTRY)
	{
		// Process inputs
		_UIDE_ProcessEncoder(uide);
		_UIDE_ProcessSwitches(uide);

		// Update display
		if (uide->_display_func == NULL)
		{
			_UIDE_Display(uide);
		}
		else
		{
			uide->_display_func(uide);
		}

		osDelay(UI_LOOP_DELAY);
	}


	// Entry Annunciator off
	ANNH_SwitchEntry(false);

	// Now let's check the result
	if (uide->_state == UIDE_ABORTED)
	{
		return API_ABORTED;
	}
	else if (uide->_state == UIDE_TERMINATED)
	{
		return API_TERMINATED;
	}


	*result = choices[uide->_index_selected].tag;

	return API_OK;
}

/* Private functions ---------------------------------------------------------*/

API_StatusTypeDef _UIDE_ProcessEncoder(UIDE_TypeDef *uide)
{
	int16_t count = 0;

	if (!ENC_Get_Count(&count))
	{
		return API_OK;
	}

	APP_Run_SystemBeeperTick();

	while (count > 0)
	{
		if (_UIDE_Action_Next(uide) != API_OK)
		{
			APP_Run_SystemBeeperBeepError();
			return API_ERROR;
		}
		count--;
	}
	while (count < 0)
	{
		if (_UIDE_Action_Previous(uide) != API_OK)
		{
			APP_Run_SystemBeeperBeepError();
			return API_ERROR;
		}
		count++;
	}

	return API_OK;
}


API_StatusTypeDef _UIDE_ProcessSwitches(UIDE_TypeDef *uide)
{
	// Check for new key press
	SWA_KeyCodeTypeDef code = SWA_Get_KeyCode();

	if (code == SW_NONE)
	{
		return API_OK;
	}

	APP_Run_SystemBeeperBeepShort();

	API_StatusTypeDef status = API_ERROR;

	switch (code)
	{
		case SW_UP:
		case SW_LEFT: status = _UIDE_Action_Previous(uide); break;

		case SW_DOWN:
		case SW_RIGHT:status = _UIDE_Action_Next(uide); break;

		case SW_ROT_ENT:
		case SW_ENTER: status = _UIDE_Action_Enter(uide); break;

		case SW_MENU: status = _UIDE_Action_Menu(uide); break;
		case SW_BACK_DISP: status = _UIDE_Action_Abort(uide); break;

		case SW_INP: status = APP_Run_InputStateToggle(); break;

		default: break;
	}

	if (status == API_OK)
	{
		return API_OK;
	}

	APP_Run_SystemBeeperBeepError();
	return status;
}


API_StatusTypeDef _UIDE_Action_Previous(UIDE_TypeDef *uide)
{
	if (uide->_index_selected > 0)
	{
		uide->_index_selected--;
	}
	else if (uide->_allow_wrap)
	{
		uide->_index_selected = uide->_index_max;
	}
	else
	{
		if (uide->_show_info)
		{
			UIDI_Show("FIRST ENTRY", UIDI_DEFAULT_TIMEOUT_SHORT, true);
		}
	}

	return API_OK;
}


API_StatusTypeDef _UIDE_Action_Next(UIDE_TypeDef *uide)
{
	if (uide->_index_selected < uide->_index_max)
	{
		uide->_index_selected++;
	}
	else if (uide->_allow_wrap)
	{
		uide->_index_selected = 0;
	}
	else
	{
		if (uide->_show_info)
		{
			UIDI_Show("LAST ENTRY", UIDI_DEFAULT_TIMEOUT_SHORT, true);
		}
	}

	return API_OK;
}


API_StatusTypeDef _UIDE_Action_Enter(UIDE_TypeDef *uide)
{
	uide->_state = UIDE_ENTERED;
	return API_OK;
}


API_StatusTypeDef _UIDE_Action_Menu(UIDE_TypeDef *uide)
{
	uide->_state = UIDE_TERMINATED;
	return API_OK;
}


API_StatusTypeDef _UIDE_Action_Abort(UIDE_TypeDef *uide)
{
	uide->_state = UIDE_ABORTED;
	return API_OK;
}


int8_t _UIDE_FindIndex(UIDE_ChoiceTypeDef *choices, int32_t tag)
{
	uint8_t i;

	for (i = 0; choices[i].name != NULL && choices[i].tag != tag; i++);

	return i;
}


uint8_t _UIDE_LenChoices(UIDE_ChoiceTypeDef *choices)
{
	return _UIDE_FindIndex(choices, -1);
}


const char *_UIDE_FindName(UIDE_ChoiceTypeDef *choices, int32_t tag)
{
	uint8_t i;

	for (i = 0; choices[i].name != NULL && choices[i].tag != tag; i++);

	return choices[i].name;
}


void _UIDE_Display(UIDE_TypeDef *uide)
{
	char str[32];

	// Initialize string
	memset(str, 0, sizeof(str));

	// Write description for the number to be entered
	if (strnlen(uide->_description, 1) > 0)
	{
		strcat(str, uide->_description);
		strcat(str, ": ");
	}

	// Mark as dimmed
	if (uide->_index_selected != uide->_index_current_value)
	{
		strcat(str, "\x1E");
	}

	strcat(str, uide->_choices[uide->_index_selected].name);

	// Update display
	UI_Display_Update(str);
	ANNH_Update();
}
