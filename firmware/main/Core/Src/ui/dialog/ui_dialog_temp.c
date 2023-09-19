/**
 * @file    ui_dialog_temp.c
 * @author  sebas
 * @date    05.01.2023
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "cmsis_os2.h"

#include <stdbool.h>
#include <string.h>

#include "ui/dialog/ui_dialog_temp.h"
#include "ui/display_helper.h"
#include "ui/annunciator_helper.h"

#include "util/util.h"

#include "application/app_display.h"
#include "application/app_system.h"

#include "hardware/ui_interface_def.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

void _UIDT_TempToStr(char *str, float temp);

/* Exported functions --------------------------------------------------------*/

void _UIDT_Display(UIDE_TypeDef *uide)
{
	char str[32];

	// Initialize string
	memset(str, 0, sizeof(str));

	strcat(str, uide->_choices[uide->_index_selected].name);
	strcat(str, " ");

	float t1, t2;
	switch (uide->_index_selected)
	{
		default:
		case UIDT_STATE_IMMEDIATE:
			t1 = APP_Get_SystemTempImmediate(TEMP_SEL_1);
			t2 = APP_Get_SystemTempImmediate(TEMP_SEL_2);
			break;
		case UIDT_STATE_MINIMUM:
			t1 = APP_Get_SystemTempMinimum(TEMP_SEL_1);
			t2 = APP_Get_SystemTempMinimum(TEMP_SEL_2);
			break;
		case UIDT_STATE_MAXIMUM:
			t1 = APP_Get_SystemTempInternalMaximum(TEMP_SEL_1);
			t2 = APP_Get_SystemTempInternalMaximum(TEMP_SEL_2);
			break;
		case UIDT_STATE_AVERAGE:
			t1 = APP_Get_SystemTempAverage(TEMP_SEL_1);
			t2 = APP_Get_SystemTempAverage(TEMP_SEL_2);
			break;
	}

	_UIDT_TempToStr(str + strlen(str), t1);

	strcat(str, " ");

	_UIDT_TempToStr(str + strlen(str), t2);

	// Update display
	UI_Display_Update(str);
	ANNH_Update();
}

/* Private functions ---------------------------------------------------------*/

void _UIDT_TempToStr(char *str, float temp)
{
	uint8_t dec_offset = 0;

	temp *= 1000;

	if (temp < 0)
	{
		strcat(str, "<");
		dec_offset = 1;
		temp = 0;
	}

	UTIL_UIntToStr(str,
			UTIL_DivRoundClosestInt32((uint32_t) temp, 10),
			4 - dec_offset,
			2 - dec_offset,
			UTIL_LEAD_TRAIL_ZERO_BLANK,
			UTIL_LEAD_TRAIL_ZERO_ZERO);

	strcat(str, "\xB0" "C");
}
