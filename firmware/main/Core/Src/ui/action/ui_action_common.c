/**
 * @file    ui_action_common.c
 * @author  sebas
 * @date    23.04.2023
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include <string.h>

#include "util/util.h"

#include "ui/action/ui_action_common.h"
#include "ui/dialog/ui_dialog_info.h"
#include "ui/ui_parser_def.h"

#include "application/app_memory.h"
#include "application/app_system.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

API_StatusTypeDef UIACT_Rcl()
{
	UIDN_TypeDef uidn;
	uint32_t setup;

	UIDN_Setup(&uidn, &UIPAR_SAVRCL, UIDN_CURSOR_START);

	API_StatusTypeDef status = UIDN_Show(&uidn, "*RCL", "", "", &setup);
	if (status != API_OK)
	{
		return status;
	}

	status = APP_Run_MemoryRecall(setup, false);
	if (status != API_OK)
	{
		APP_Run_SystemBeeperBeepError();
		return status;
	}

	UIDI_Show("DONE", UIDI_DEFAULT_TIMEOUT_MEDIUM, true);
	return API_TERMINATED;
}


API_StatusTypeDef UIACT_Sav()
{
	UIDN_TypeDef uidn;
	uint32_t setup;

	UIDN_Setup(&uidn, &UIPAR_SAVRCL, UIDN_CURSOR_START);

	API_StatusTypeDef status = UIDN_Show(&uidn, "*SAV", "", "", &setup);
	if (status != API_OK)
	{
		return status;
	}

	status = APP_Run_MemorySave(setup);
	if (status != API_OK)
	{
		APP_Run_SystemBeeperBeepError();
		return status;
	}

	UIDI_Show("DONE", UIDI_DEFAULT_TIMEOUT_MEDIUM, true);
	return API_TERMINATED;
}

/* Private functions ---------------------------------------------------------*/

