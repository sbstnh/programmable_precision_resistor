/**
 * @file    encoder_def.c
 * @author  sebas
 * @date    24.12.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "ui/encoder_def.h"
#include "hardware/ui_interface_def.h"
#include "application/app_system.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

bool ENC_Gate(ENC_TypeDef *encoder);

/* Exported variables --------------------------------------------------------*/

ENC_TypeDef ENC =
{
		.gate = ENC_Gate
};

/* Exported functions --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

bool ENC_Gate(ENC_TypeDef *encoder)
{
	// Implementation for enabling/disabling encoder according to ui state (local/mixed/remote/rwlock)
	COMM_RLSTate_TypeDef rls_state = APP_Get_SystemCommunicateRLState();

	if (rls_state == COMM_RLST_RWLock || rls_state == COMM_RLST_REMote)
	{
		// If RWLock or REMote is active, the encoder is disabled completely
		return false;
	}

	return true;
}
