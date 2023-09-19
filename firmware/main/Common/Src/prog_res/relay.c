/*
 * relay.c
 *
 *  Created on: 22.10.2022
 *      Author: sebas
 */


#include "prog_res/relay.h"

void RLY_Init(RLY_TypeDef *relay)
{
	relay->cycles = 0;
}

void RLY_SetState(RLY_TypeDef *relay, RLY_STATE relay_state)
{
	relay->state = relay_state;
}

void RLY_Open(RLY_TypeDef *relay)
{
	relay->state = RLY_OPEN;
}

void RLY_Close(RLY_TypeDef *relay)
{
	relay->state = RLY_CLOSED;
}
