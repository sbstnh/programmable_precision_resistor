/**
 * @file    ui_dialog_info.c
 * @author  sebas
 * @date    21.12.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "cmsis_os2.h"

#include <string.h>

#include "ui/display_helper.h"
#include "ui/annunciator_helper.h"

#include "util/api.h"
#include "util/util.h"
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
/* Exported functions --------------------------------------------------------*/


API_StatusTypeDef UIDI_Show(const char *message, uint16_t timeout, bool centered)
{
	char str[DISP_USER_TEXT_LENGTH];
	uint16_t timer = timeout;

	if (centered)
	{
		UI_Display_FormatTextCentered(str, message, DISP_USER_TEXT_LENGTH);
	}
	else
	{
		strcpy(str, message);
	}

	ENC_SkipAll_Counts();
	SWA_SkipAll_KeyCodes();

	// Block the inputs for a predetermined period of time in order to avoid a
	// unintentional cancelation and potentially a following action.
	uint16_t allow_cancel = (timer > UIDI_ALLOW_CANCEL_AFTER) ? timer - UIDI_ALLOW_CANCEL_AFTER : 0;

	API_StatusTypeDef result = API_UNCHANGED;

	// Loop
	while (APP_Get_DisplayEnable() && !APP_Get_DisplayUserTextState() && (!timeout || timer))
	{
		int16_t count;

		uint8_t keycode = SWA_Get_KeyCode();

		if (keycode == SW_INP)
		{
			APP_Run_SystemBeeperBeepShort();
			APP_Run_InputStateToggle();
			keycode = SW_NONE;
		}

		if (timer <= allow_cancel && (keycode != SW_NONE || ENC_Get_Count(&count)))
		{
			APP_Run_SystemBeeperBeepShort();

			if (keycode == SW_MENU)
			{
				result = API_TERMINATED;
			}
			break;
		}

		// Update display
		UI_Display_Update(str);
		ANNH_Update();

		osDelay(UI_LOOP_DELAY);

		if (timer)
		{
			timer--;
		}
	}

	ENC_SkipAll_Counts();
	SWA_SkipAll_KeyCodes();

	return result;
}




/* Private functions ---------------------------------------------------------*/

