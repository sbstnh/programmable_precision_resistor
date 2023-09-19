/**
 * @file    ui.c
 * @author  sebas
 * @date    23.11.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "ui/ui_cal.h"
#include "ui/ui_main.h"
#include "ui/ui_off.h"
#include "ui/ui_text.h"
#include "ui/ui.h"
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

void UI_Run()
{
	SWA_Reset_Shift(&SWA);

	while (1)
	{
		if (APP_Get_CalibrationState())
		{
			UICAL_Show();
		}
		else if (!APP_Get_DisplayEnable())
		{
			UIOFF_Show();
		}
		else if (APP_Get_DisplayUserTextState())
		{
			UITEXT_Show();
		}
		else
		{
			UIMAIN_Show();
		}
	}
}


/* Private functions ---------------------------------------------------------*/

