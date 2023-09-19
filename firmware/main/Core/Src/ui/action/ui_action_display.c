/**
 * @file    menu_display.c
 * @author  sebas
 * @date    01.01.2023
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "ui/action/ui_action_resistance.h"
#include "ui/dialog/ui_dialog_enum.h"

#include "application/app_display.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

UIDE_ChoiceTypeDef UIACT_DIGIT_CHOICES[] =
{
		{ "3.5 DIG", PRIM_RES_THRee },
		{ "4.5 DIG", PRIM_RES_FOUR },
		{ "5.5 DIG", PRIM_RES_FIVE },
		{ "6.5 DIG", PRIM_RES_SIX },
		UIDE_CHOICE_LIST_END
};

/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/


API_StatusTypeDef UIACT_DisplayResolution()
{
	UIDE_TypeDef dialog;
	const PRIM_RESolution_TypeDef current = APP_Get_DisplayPrimaryResolution();
	int32_t result;

	API_StatusTypeDef status = UIDE_Show(&dialog,
										 "RESolution",
										 UIACT_DIGIT_CHOICES,
										 current,
										 false,
										 &result,
										 NULL);

	if (status != API_OK)
	{
		return status;
	}

	return APP_Set_DisplayPrimaryResolution((PRIM_RESolution_TypeDef) result);
}


API_StatusTypeDef UIACT_DisplaySwitchOff()
{
	return APP_Set_DisplayEnable(false);
}

/* Private functions ---------------------------------------------------------*/

