/**
 * @file    switch_array_def.c
 * @author  sebas
 * @date    23.11.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "ui/switch_array_def.h"
#include "hardware/switch_def.h"

#include "hardware/ui_interface_def.h"
#include "application/app_system.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

bool SWA_Gate(SWA_TypeDef *swa, SW_TypeDef *sw);

/* Exported variables --------------------------------------------------------*/

SWA_TypeDef SWA =
{
		.switches = SW,
		.switch_count = SW_NUMBER_OF_SWITCHES,
		.gate = SWA_Gate,
};

/* Exported functions --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

bool SWA_Gate(SWA_TypeDef *swa, SW_TypeDef *sw)
{
	// Implementation for enabling/disabling keys according to ui state (local/mixed/remote/rwlock)
	COMM_RLSTate_TypeDef rls_state = APP_Get_SystemCommunicateRLState();

	if (rls_state == COMM_RLST_RWLock)
	{
		// If RWLock is active, the keyboard is disabled completely
		return false;
	}

	if (rls_state == COMM_RLST_REMote)
	{
		// If REMote is active, the LOC key may be used to gain local control
		if (sw->tag == SW_9)
		{
			APP_Run_SystemCommunicateRLState(COMM_RLST_MIXed);
			APP_Run_SystemBeeperBeepShort();
		}

		// However, consume this key press
		return false;
	}

	// Handle shift modifier
	if (sw->tag == SW_SHIFT)
	{
		swa->_shift = !swa->_shift;
		APP_Run_SystemBeeperBeepShort();

		// Consume this key press
		return false;
	}

	return true;
}
