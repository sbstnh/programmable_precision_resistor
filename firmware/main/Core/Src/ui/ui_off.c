/**
 * @file    ui_app_disabled.c
 * @author  sebas
 * @date    23.11.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "cmsis_os2.h"

#include "ui/ui_off.h"
#include "ui/display_helper.h"
#include "ui/annunciator_helper.h"
#include "ui/switch_array_def.h"
#include "ui/encoder_def.h"

#include "application/app_calibration.h"
#include "application/app_display.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void UIOFF_Show()
{

	// Discard old switch and encoder values
	SWA_Reset_Shift(&SWA);
	SWA_SkipAll_KeyCodes();
	ENC_SkipAll_Counts();

	// Disable display
	UI_Display_Disable();

	// Wait until state is changed through SCPI or the user interface
	while (!APP_Get_DisplayEnable() && !APP_Get_CalibrationState())
	{
		int16_t count;

		if (SWA_Get_KeyCode() != SW_NONE || ENC_Get_Count(&count))
		{
			break;
		}

		ANNH_Update();

		osDelay(UI_LOOP_DELAY);
	}

	// Enable display again and then leave this app
	APP_Set_DisplayEnable(true);
}

/* Private functions ---------------------------------------------------------*/

