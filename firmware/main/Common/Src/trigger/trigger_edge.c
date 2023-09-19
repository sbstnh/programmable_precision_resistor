/**
 * @file    trigger_input.c
 * @author  sebas
 * @date    Nov 20, 2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "trigger/trigger_edge.h"
#include "trigger/trigger_logic.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void TRIGEDGE_ParamsSetup(TRIGEDGE_ParamsTypeDef *trig_edge, bool (*detect_event)(TRIGEDGE_ParamsTypeDef *), TRIGEDGE_SlopeTypeDef slope, uint32_t debounce_cycles)
{
	trig_edge->_detect_event = detect_event;
	trig_edge->_slope = slope;
	trig_edge->_debounce_cycles = debounce_cycles;
}

void TRIGEDGE_ParamsSetEventDetector(TRIGEDGE_ParamsTypeDef *trig_edge, bool (*detect_event)(TRIGEDGE_ParamsTypeDef *))
{
	trig_edge->_detect_event = detect_event;
}

void TRIGEDGE_ParamsSetSlope(TRIGEDGE_ParamsTypeDef *trig_edge, TRIGEDGE_SlopeTypeDef slope)
{
	trig_edge->_slope = slope;
}

void TRIGEDGE_ParamsSetDebounceCycles(TRIGEDGE_ParamsTypeDef *trig_edge, uint32_t debounce_cycles)
{
	trig_edge->_debounce_cycles = debounce_cycles;
}


void TRIGEDGE_Init(TRIG_LogicTypeDef *trig_logic)
{
	TRIGEDGE_ParamsTypeDef *params = (TRIGEDGE_ParamsTypeDef *)trig_logic->params;
	params->_state = params->_detect_event(params) ? TRIGEDGE_STATE_POS : TRIGEDGE_STATE_NEG;
}

bool TRIGEDGE_Cycle(TRIG_LogicTypeDef *trig_logic)
{
	TRIGEDGE_ParamsTypeDef *params = (TRIGEDGE_ParamsTypeDef *)trig_logic->params;
	bool value = params->_detect_event(params);

	switch (params->_state)
	{
		default:
		case TRIGEDGE_STATE_NEG:

			if (value)
			{
				params->_state = TRIGEDGE_STATE_RISING;
				params->_timer = 0;
			}
			return false;

		case TRIGEDGE_STATE_RISING:
			params->_timer++;

			if (params->_timer < params->_debounce_cycles)
			{
				return false;
			}

			if (value)
			{
				params->_state = TRIGEDGE_STATE_POS;
				return params->_slope == TRIGEDGE_SLOPE_POSITIVE || params->_slope == TRIGEDGE_SLOPE_EITHER;
			}

			params->_state = TRIGEDGE_STATE_NEG;
			return false;

		case TRIGEDGE_STATE_POS:
			if (!value)
			{
				params->_state = TRIGEDGE_STATE_FALLING;
				params->_timer = 0;
			}
			return false;

		case TRIGEDGE_STATE_FALLING:
			params->_timer++;

			if (params->_timer < params->_debounce_cycles)
			{
				return false;
			}

			if (!value)
			{
				params->_state = TRIGEDGE_STATE_NEG;
				return params->_slope == TRIGEDGE_SLOPE_NEGATIVE || params->_slope == TRIGEDGE_SLOPE_EITHER;
			}

			params->_state = TRIGEDGE_STATE_POS;
			return false;
	}
}

/* Private functions ---------------------------------------------------------*/

