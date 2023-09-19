/**
 * @file    ui_dialog_number.c
 * @author  sebas
 * @date    20.12.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>
#include <string.h>

#include "cmsis_os2.h"
#include "util/util.h"

#include "ui/display_helper.h"
#include "ui/annunciator_helper.h"
#include "ui/dialog/ui_dialog_number.h"
#include "ui/switch_array_def.h"
#include "ui/encoder_def.h"

#include "application/app_display.h"
#include "application/app_input.h"
#include "application/app_system.h"

#include "hardware/ui_interface_def.h"

/* Private defines -----------------------------------------------------------*/

#define UI_NUMBER_ENTRY_NUMBER_MAX_LEN	(UIIF_DISP_DIGITS - UIDN_DESC_MAX_LEN - 1)

/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

void _UIDN_MoveToInitialCursorPosition(UIDN_TypeDef *uidn);

API_StatusTypeDef _UIDN_ProcessEncoder(UIDN_TypeDef *uidn);
API_StatusTypeDef _UIDN_ProcessSwitches(UIDN_TypeDef *uidn);

API_StatusTypeDef _UIDN_AddSymbol(UIDN_TypeDef *uidn, char symbol);
API_StatusTypeDef _UIDN_Left(UIDN_TypeDef *uidn);
API_StatusTypeDef _UIDN_Right(UIDN_TypeDef *uidn);
API_StatusTypeDef _UIDN_Backspace(UIDN_TypeDef *uidn);
API_StatusTypeDef _UIDN_ClearEntry(UIDN_TypeDef *uidn);
API_StatusTypeDef _UIDN_Enter(UIDN_TypeDef *uidn);
API_StatusTypeDef _UIDN_EnterK(UIDN_TypeDef *uidn);
API_StatusTypeDef _UIDN_Up(UIDN_TypeDef *uidn);
API_StatusTypeDef _UIDN_Down(UIDN_TypeDef *uidn);
API_StatusTypeDef _UIDN_Back(UIDN_TypeDef *uidn);
API_StatusTypeDef _UIDN_Menu(UIDN_TypeDef *uidn);
API_StatusTypeDef _UIDN_EnforceK(UIDN_TypeDef *uidn);

API_StatusTypeDef _UIDN_Parse(UIDN_TypeDef *uidn);

void _UIDN_Display(UIDN_TypeDef *uidn, const char *description, const char *number, const char *unit);

/* Exported functions --------------------------------------------------------*/

void UIDN_Setup(UIDN_TypeDef *uidn, UIPAR_TypeDef *parser, UIDN_CursorPosTypeDef cursor_position)
{
	uidn->parser = parser;
	uidn->initial_pos = cursor_position;
}


API_StatusTypeDef UIDN_Show(UIDN_TypeDef *uidn, const char *description, const char *default_value, const char *unit, uint32_t *result)
{
	// Initialize variables
	uidn->_state = UIDN_ENTRY;

	if (default_value == NULL)
	{
		memset(uidn->_parse_str, 0, sizeof(uidn->_parse_str));
	}
	else
	{
		strncpy(uidn->_entry_str, default_value, sizeof(uidn->_parse_str) - 1);

		if (_UIDN_Parse(uidn) != API_OK)
		{
			return API_ERROR;
		}
	}

	// Set cursor position
	_UIDN_MoveToInitialCursorPosition(uidn);

	// Discard old switch and encoder values
	ENC_SkipAll_Counts();

	// Entry Annunciator on
	ANNH_SwitchEntry(true);

	// Loop
	while (APP_Get_DisplayEnable() && !APP_Get_DisplayUserTextState()
			&& uidn->_state == UIDN_ENTRY)
	{
		// Process inputs
		_UIDN_ProcessEncoder(uidn);
		_UIDN_ProcessSwitches(uidn);

		// Update display
		_UIDN_Display(uidn, description, uidn->_parse_str, unit);

		osDelay(UI_LOOP_DELAY);
	}


	// Entry Annunciator on
	ANNH_SwitchEntry(false);


	// Now let's check the result
	if (uidn->_state == UIDN_ABORTED || uidn->_parse_status == UIPAR_END_WITHOUT_INPUT)
	{
		return API_ABORTED;
	}

	if (uidn->_state == UIDN_TERMINATED)
	{
		return API_TERMINATED;
	}

	// Parse result again, since the result might be invalid due to the latest
	// run
	memcpy(uidn->_entry_str, uidn->_parse_str, sizeof(uidn->_entry_str));
	if (_UIDN_Parse(uidn) != API_OK)
	{
		return API_ERROR;
	}

	// Set result and return
	*result = uidn->_parse_result.result;
	return API_OK;
}


/* Private functions ---------------------------------------------------------*/


void _UIDN_MoveToInitialCursorPosition(UIDN_TypeDef *uidn)
{
	if (uidn->initial_pos != UIDN_CURSOR_LEAVE)
	{
		uidn->_pos = uidn->initial_pos;
	}

	if (uidn->_pos < 0)
	{
		uidn->_pos = 0;
	}
	else if (uidn->_pos > strlen(uidn->_parse_str))
	{
		uidn->_pos = strlen(uidn->_parse_str);
	}
}


API_StatusTypeDef _UIDN_ProcessEncoder(UIDN_TypeDef *uidn)
{
	int16_t count = 0;

	if (!ENC_Get_Count(&count))
	{
		return API_OK;
	}

	APP_Run_SystemBeeperTick();

	while (count > 0)
	{
		if (_UIDN_Up(uidn) != API_OK)
		{
			APP_Run_SystemBeeperBeepError();
			return API_ERROR;
		}
		count--;
	}
	while (count < 0)
	{
		if (_UIDN_Down(uidn) != API_OK)
		{
			APP_Run_SystemBeeperBeepError();
			return API_ERROR;
		}
		count++;
	}

	return API_OK;
}


API_StatusTypeDef _UIDN_ProcessSwitches(UIDN_TypeDef *uidn)
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
		case SW_0: status = _UIDN_AddSymbol(uidn, '0'); break;
		case SW_1: status = _UIDN_AddSymbol(uidn, '1'); break;
		case SW_2: status = _UIDN_AddSymbol(uidn, '2'); break;
		case SW_3: status = _UIDN_AddSymbol(uidn, '3'); break;
		case SW_4: status = _UIDN_AddSymbol(uidn, '4'); break;
		case SW_5: status = _UIDN_AddSymbol(uidn, '5'); break;
		case SW_6: status = _UIDN_AddSymbol(uidn, '6'); break;
		case SW_7: status = _UIDN_AddSymbol(uidn, '7'); break;
		case SW_8: status = _UIDN_AddSymbol(uidn, '8'); break;
		case SW_9: status = _UIDN_AddSymbol(uidn, '9'); break;
		case SW_DP: status = _UIDN_AddSymbol(uidn, '.'); break;
		case SW_BACKSP: status = _UIDN_Backspace(uidn); break;
		case SW_SH_BACKSP: status = _UIDN_ClearEntry(uidn); break;

		case SW_LEFT: status = _UIDN_Left(uidn); break;
		case SW_RIGHT: status = _UIDN_Right(uidn); break;

		case SW_ROT_ENT:
		case SW_ENTER: status = _UIDN_Enter(uidn); break;
		case SW_SH_ENTER: status = _UIDN_EnterK(uidn); break;

		case SW_MENU: status = _UIDN_Menu(uidn); break;
		case SW_BACK_DISP: status = _UIDN_Back(uidn); break;

		case SW_UP: status = _UIDN_Up(uidn); break;
		case SW_DOWN: status = _UIDN_Down(uidn); break;

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


API_StatusTypeDef _UIDN_AddSymbol(UIDN_TypeDef *uidn, char symbol)
{
	// Symbols are always inserted in front of the current cursor position
	UTIL_StrInsertChar(uidn->_entry_str, uidn->_parse_str, symbol, uidn->_pos);

	// Check whether string could be parsed
	if (_UIDN_Parse(uidn) != API_OK)
	{
		return API_ERROR;
	}

	uidn->_pos++;

	return API_OK;
}


API_StatusTypeDef _UIDN_EnforceK(UIDN_TypeDef *uidn)
{
	// Symbols are always inserted in front of the current cursor position
	// Copy everything in front of the cursor
	memcpy(uidn->_entry_str, uidn->_parse_str, sizeof(uidn->_parse_str));

	// Append K
	const uint8_t len = strlen(uidn->_entry_str);
	if (len > 0 && uidn->_entry_str[len - 1] != 'K')
	{
		uidn->_entry_str[len] = 'K';
		uidn->_entry_str[len + 1] = '\0';
	}

	// Check whether string could be parsed
	if (_UIDN_Parse(uidn) != API_OK)
	{
		return API_ERROR;
	}

	uidn->_pos++;

	return API_OK;
}


API_StatusTypeDef _UIDN_Up(UIDN_TypeDef *uidn)
{
	int8_t temp_pos = uidn->_pos;

	strcpy(uidn->_entry_str, uidn->_parse_str);

	if (!IS_DIGIT(uidn->_entry_str[temp_pos]) && uidn->_entry_str[temp_pos] != '\0')
	{
		return API_ERROR;
	}

	bool completed = false;
	while (temp_pos >= 0)
	{
		if (uidn->_entry_str[temp_pos] == '\0')
		{
			uidn->_entry_str[temp_pos] = '0';
			uidn->_entry_str[temp_pos + 1] = '\0';
			completed = true;
			break;
		}

		if (!IS_DIGIT(uidn->_entry_str[temp_pos]))
		{
			temp_pos--;
			continue;
		}

		if (uidn->_entry_str[temp_pos] < '9')
		{
			uidn->_entry_str[temp_pos]++;
			completed = true;
			break;
		}

		uidn->_entry_str[temp_pos] = '0';
		temp_pos--;
	}

	if (!completed)
	{
		for (int8_t i = strlen(uidn->_entry_str) + 1; i > 0; i--)
		{
			uidn->_entry_str[i] = uidn->_entry_str[i - 1];
		}

		uidn->_entry_str[0] = '1';
	}

	if (_UIDN_Parse(uidn) != API_OK)
	{
		return API_ERROR;
	}

	if (!completed)
	{
		uidn->_pos++;
	}

	return API_OK;
}


API_StatusTypeDef _UIDN_Down(UIDN_TypeDef *uidn)
{
	int8_t temp_pos = uidn->_pos;

	strcpy(uidn->_entry_str, uidn->_parse_str);

	if (!IS_DIGIT(uidn->_entry_str[temp_pos]) && uidn->_entry_str[temp_pos] != '\0')
	{
		return API_ERROR;
	}

	while (temp_pos >= 0)
	{
		if (uidn->_entry_str[temp_pos] == '\0')
		{
			uidn->_entry_str[temp_pos] = '0';
			uidn->_entry_str[temp_pos + 1] = '\0';
			break;
		}

		if (!IS_DIGIT(uidn->_entry_str[temp_pos]))
		{
			temp_pos--;
			continue;
		}

		if (uidn->_entry_str[temp_pos] > '0')
		{
			uidn->_entry_str[temp_pos]--;
			break;
		}

		// Now we have to check whether there are any digits of higher significance left
		// That will be the case if iter_pos >= 0
		int8_t iter_pos = temp_pos - 1;

		while (iter_pos >= 0)
		{
			if (!IS_DIGIT(uidn->_entry_str[iter_pos]))
			{
				iter_pos--;
				continue;
			}

			if (uidn->_entry_str[iter_pos] > '0')
			{
				break;
			}
			iter_pos--;
		}

		if (iter_pos >= 0)
		{
			uidn->_entry_str[temp_pos] = '9';
			temp_pos--;
		}
		else
		{
			// Now we have to move to a higher digit if possible and
			// try to lower its value afterwards
			if (uidn->_pos + 1 < strlen(uidn->_entry_str))
			{
				uidn->_pos++;
				temp_pos = uidn->_pos;
				continue;
			}

			// It looks like we have reached a value of zero
			break;
		}
	}

	if (_UIDN_Parse(uidn) != API_OK)
	{
		return API_ERROR;
	}

	return API_OK;
}


API_StatusTypeDef _UIDN_Left(UIDN_TypeDef *uidn)
{
	uidn->_pos = uidn->_pos > 0 ? uidn->_pos - 1 : strlen(uidn->_parse_str);

	return API_OK;
}


API_StatusTypeDef _UIDN_Right(UIDN_TypeDef *uidn)
{
	const uint8_t len = strnlen(uidn->_parse_str, sizeof(uidn->_parse_str));
	uidn->_pos = uidn->_pos < len ? uidn->_pos + 1 : 0;

	return API_OK;
}


API_StatusTypeDef _UIDN_Backspace(UIDN_TypeDef *uidn)
{
	if (uidn->_pos == 0)
	{
		return API_ERROR;
	}

	// Symbols are always deleted in front of the current cursor position
	// Copy the symbols in front of the cursor except the one to be deleted
	memcpy(uidn->_entry_str, uidn->_parse_str, uidn->_pos - 1);

	// Copy everything beginning at the cursor position
	memcpy(uidn->_entry_str + uidn->_pos - 1, uidn->_parse_str + uidn->_pos, sizeof(uidn->_parse_str) - uidn->_pos);

	// Check whether string could be parsed
	if (_UIDN_Parse(uidn) != API_OK)
	{
		return API_ERROR;
	}

	uidn->_pos--;
	return API_OK;
}


API_StatusTypeDef _UIDN_ClearEntry(UIDN_TypeDef *uidn)
{
	uidn->_entry_str[0] = '\0';

	// Check whether string could be parsed
	if (_UIDN_Parse(uidn) != API_OK)
	{
		return API_ERROR;
	}

	uidn->_pos = 0;
	return API_OK;
}


API_StatusTypeDef _UIDN_Back(UIDN_TypeDef *uidn)
{
	uidn->_state = UIDN_ABORTED;
	return API_OK;
}


API_StatusTypeDef _UIDN_Menu(UIDN_TypeDef *uidn)
{
	uidn->_state = UIDN_TERMINATED;
	return API_OK;
}


API_StatusTypeDef _UIDN_Enter(UIDN_TypeDef *uidn)
{
	uidn->_state = UIDN_ENTERED;
	return API_OK;
}


API_StatusTypeDef _UIDN_EnterK(UIDN_TypeDef *uidn)
{
	if (_UIDN_EnforceK(uidn) != API_OK)
	{
		return API_ERROR;
	}

	uidn->_state = UIDN_ENTERED;
	return API_OK;
}


API_StatusTypeDef _UIDN_Parse(UIDN_TypeDef *uidn)
{
	uidn->_parse_status = UIPAR_Parse_Number(uidn->parser, uidn->_entry_str, &uidn->_parse_result);

	if (uidn->_parse_status == UIPAR_OK || uidn->_parse_status == UIPAR_END_WITHOUT_INPUT)
	{
		// Copy string into parse_str
		memcpy(uidn->_parse_str, uidn->_entry_str, sizeof(uidn->_entry_str));
		return API_OK;
	}

	return API_ERROR;
}


void _UIDN_Display(UIDN_TypeDef *uidn, const char *description, const char *number, const char *unit)
{
	char str[32];

	// Initialize string
	memset(str, 0, sizeof(str));

	// Write description for the number to be entered
	if (strnlen(description, 1) > 0)
	{
		strncat(str, description, UIDN_DESC_MAX_LEN);

		// Write blank
		strcat(str, ": ");
	}

	// Insert blink/dimmed marker at cursor position
	UTIL_StrInsertChar(str + strlen(str), number, DISP_CHAR_BLINK_DIMMED, uidn->_pos);

	// Write cursor if at the end of the string
	if (uidn->_pos == strnlen(uidn->_parse_str, sizeof(uidn->_parse_str)))
	{
		strcat(str, "_");
	}
	else
	{
		strcat(str, " ");
	}

	if (unit != NULL)
	{
		strcat(str, unit);
	}

	// Update display
	UI_Display_Update(str);
	ANNH_Update();
}


