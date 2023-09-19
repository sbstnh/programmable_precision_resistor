/**
 * @file    trigger.c
 * @author  sebas
 * @date    Nov 20, 2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "trigger/trigger.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void TRIG_Init(TRIG_TypeDef *trig, TRIG_LogicTypeDef *trig_logic)
{
	trig->_trig_logic = trig_logic;
	trig->_immediate = false;
	trig->_state = TRIG_STATE_IDLE;
}

void TRIG_SetLogic(TRIG_TypeDef *trig, TRIG_LogicTypeDef *trig_logic)
{
	trig->_trig_logic = trig_logic;
}

void TRIG_SetDelay(TRIG_TypeDef *trig, uint32_t delay)
{
	trig->_delay = delay;
}

void TRIG_SetHoldOff(TRIG_TypeDef *trig, uint32_t holdoff)
{
	trig->_holdoff = holdoff;
}

TRIG_StatesTypeDef TRIG_GetState(TRIG_TypeDef *trig)
{
	return trig->_state;
}

void TRIG_Initiate(TRIG_TypeDef *trig)
{
	trig->_state = TRIG_STATE_INITIATED;
}

void TRIG_Abort(TRIG_TypeDef *trig)
{
	trig->_state = TRIG_STATE_IDLE;
}

void TRIG_Continuous(TRIG_TypeDef *trig, bool continuous)
{
	trig->_continuous = continuous;

	if (continuous)
	{
		TRIG_Initiate(trig);
	}
}

void TRIG_Immediate(TRIG_TypeDef *trig)
{
	trig->_immediate = true;
}

bool TRIG_Cycle(TRIG_TypeDef *trig)
{
	bool triggered = trig->_immediate;
	trig->_immediate = false;

	switch (trig->_state)
	{
		default:
		case TRIG_STATE_IDLE:
			// Wait for Initiation
			break;

		case TRIG_STATE_INITIATED:

			trig->_trig_logic->trig_init(trig->_trig_logic);

			trig->_state = TRIG_STATE_ARMED;
			if (trig->on_armed)
			{
				trig->on_armed();
			}
			// No break here

		case TRIG_STATE_ARMED:

			// Skip this cycle if trigger logic doesn't return true
			if (!trig->_trig_logic || !trig->_trig_logic->trig_cycle(trig->_trig_logic))
			{
				break;
			}

			// Reset delay timer unconditionally
			trig->_delay_timer = 0;

			// Check whether a delay has to be inserted
			if (trig->_delay > 0)
			{
				trig->_state = TRIG_STATE_DELAYED;

				// Run callback if possible
				if (trig->on_delayed)
				{
					trig->on_delayed();
				}

				break;
			}

			// Otherwise run on_trigger callback if possible
			triggered = true;

			// Return to idle if trigger is not continuous
			if (!trig->_continuous)
			{
				trig->_state = TRIG_STATE_IDLE;
				break;
			}

			// reset holdoff timer unconditionally
			trig->_holdoff_timer = 0;

			// Check whether a holdoff period has to be inserted
			if (trig->_holdoff > 0)
			{
				trig->_state = TRIG_STATE_HELDOFF;

				if (trig->on_heldoff)
				{
					trig->on_heldoff();
				}
				break;
			}

			// Return to initiated to prepare for next trigger event
			trig->_state = TRIG_STATE_INITIATED;
			break;

		case TRIG_STATE_DELAYED:

			trig->_delay_timer++;

			// Nothing to do, if delay time not elapsed
			if (trig->_delay_timer < trig->_delay)
			{
				break;
			}

			// Delay time elapsed, run on_trigger callback if possible
			triggered = true;

			// Return to idle if trigger is not continuous
			if (!trig->_continuous)
			{
				trig->_state = TRIG_STATE_IDLE;
				break;
			}

			// Check whether we should go into hold off
			if (trig->_holdoff > 0)
			{
				trig->_holdoff_timer = trig->_delay_timer;
				trig->_state = TRIG_STATE_HELDOFF;

				if (trig->on_heldoff)
				{
					trig->on_heldoff();
				}
				break;
			}

			// Return to initiated to prepare for next trigger event
			trig->_state = TRIG_STATE_INITIATED;
			break;

		case TRIG_STATE_HELDOFF:
			trig->_holdoff_timer++;

			// Nothing to do, if holdoff time not elapsed
			if (trig->_holdoff_timer < trig->_holdoff)
			{
				break;
			}

			trig->_state = TRIG_STATE_INITIATED;
			break;
	}

	if (triggered && trig->on_triggered)
	{
		trig->on_triggered();
	}

	return triggered;
}

/* Private functions ---------------------------------------------------------*/

