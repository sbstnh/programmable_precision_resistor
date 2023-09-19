/**
 * @file    trigger_input.h
 * @author  sebas
 * @date    Nov 20, 2022
 * @brief
 */
#ifndef INC_TRIGGER_TRIGGER_EDGE_H_
#define INC_TRIGGER_TRIGGER_EDGE_H_

/* Includes ------------------------------------------------------------------*/

#include <stdio.h>
#include <stdint.h>
#include "trigger_logic.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

typedef enum
{
	TRIGEDGE_SLOPE_POSITIVE,
	TRIGEDGE_SLOPE_NEGATIVE,
	TRIGEDGE_SLOPE_EITHER
} TRIGEDGE_SlopeTypeDef;

typedef enum
{
	TRIGEDGE_STATE_NEG,
	TRIGEDGE_STATE_RISING,
	TRIGEDGE_STATE_POS,
	TRIGEDGE_STATE_FALLING
} TRIGEDGE_StateTypeDef;

typedef struct TRIGINP_Params_t
{
	bool (*_detect_event)(struct TRIGINP_Params_t *);
	uint32_t _debounce_cycles;
	TRIGEDGE_SlopeTypeDef _slope;

	uint32_t _timer;
	TRIGEDGE_StateTypeDef _state;
} TRIGEDGE_ParamsTypeDef;

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void TRIGEDGE_ParamsSetup(TRIGEDGE_ParamsTypeDef *trig_inp, bool (*detect_event)(TRIGEDGE_ParamsTypeDef *), TRIGEDGE_SlopeTypeDef slope, uint32_t debounce_cycles);
void TRIGEDGE_ParamsSetEventDetector(TRIGEDGE_ParamsTypeDef *trig_inp, bool (*detect_event)(TRIGEDGE_ParamsTypeDef *));
void TRIGEDGE_ParamsSetSlope(TRIGEDGE_ParamsTypeDef *trig_inp, TRIGEDGE_SlopeTypeDef slope);
void TRIGEDGE_ParamsSetDebounceCycles(TRIGEDGE_ParamsTypeDef *trig_inp, uint32_t debounce_cycles);

void TRIGEDGE_Init(TRIG_LogicTypeDef *trig_logic);
bool TRIGEDGE_Cycle(TRIG_LogicTypeDef *trig_logic);

/* Private functions ---------------------------------------------------------*/


#endif /* INC_TRIGGER_TRIGGER_EDGE_H_ */
