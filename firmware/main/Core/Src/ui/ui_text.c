/**
 * @file    ui_app_user.c
 * @author  sebas
 * @date    23.11.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "cmsis_os2.h"

#include "ui/ui_text.h"
#include "ui/display_helper.h"
#include "ui/annunciator_helper.h"
#include "ui/switch_array_def.h"

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

void UITEXT_Show()
{
	SWA_Reset_Shift(&SWA);

	while (APP_Get_DisplayEnable() && APP_Get_DisplayUserTextState() && !APP_Get_CalibrationState())
	{
		UI_Display_Update(APP_Get_DisplayUserTextData());
		ANNH_Update();

		osDelay(UI_LOOP_DELAY);
	}

	SWA_SkipAll_KeyCodes();
}


/* Private functions ---------------------------------------------------------*/

