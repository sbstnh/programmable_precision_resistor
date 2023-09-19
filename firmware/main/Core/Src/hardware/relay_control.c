/*
 * relay_control.c
 *
 *  Created on: 19.10.2022
 *      Author: sebas
 */

/* Includes ------------------------------------------------------------------*/

#include "hardware/relay_control.h"
#include "hardware/relay_def.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void RLYCTRL_Init(RLY_TypeDef *relay)
{
	relay->cycles = 0;
}

bool RLYCTRL_GetState(RLY_TypeDef *relay, STP_TypeDef *stp)
{
	return STP_Get(stp, relay->device, relay->channel);
}

void RLYCTRL_SetState(RLY_TypeDef *relay, STP_TypeDef *stp)
{
	if (relay->state == RLY_CLOSED && !STP_Get(stp, relay->device, relay->channel))
	{
		// if relay shall be closed and relays is currently open, increase cycles now
		relay->cycles++;
	}

	// Set the STP register to the required state
	STP_Set(stp, relay->device, relay->channel, relay->state);
}

API_StatusTypeDef RLYCTRL_Update(STP_TypeDef *stp)
{
	for (uint8_t i = 0; i < RLY_COUNT; i++)
	{
		RLYCTRL_SetState(&relays[i], stp);
	}
	return STP_Transmit(stp);
}

/* Private functions ---------------------------------------------------------*/
