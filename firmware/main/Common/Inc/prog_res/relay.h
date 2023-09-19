/*
 * relay.h
 *
 *  Created on: Oct 15, 2022
 *      Author: sebas
 */

#ifndef INC_RELAY_H_
#define INC_RELAY_H_

#include <stdbool.h>
#include "hardware/stp16cp05.h"

typedef enum
{
	RLY_OPEN,
	RLY_CLOSED
} RLY_STATE;

typedef struct
{
	RLY_STATE state;

	const uint8_t device;
	const uint8_t channel;

	uint32_t cycles;
} RLY_TypeDef;

void RLY_Init(RLY_TypeDef *relay);
void RLY_SetState(RLY_TypeDef *relay, RLY_STATE relay_state);
void RLY_Open(RLY_TypeDef *relay);
void RLY_Close(RLY_TypeDef *relay);


#endif /* INC_RELAY_H_ */
