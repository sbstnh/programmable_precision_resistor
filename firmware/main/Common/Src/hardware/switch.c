/**
 * @file    switch.c
 * @author  Sebastian Harnisch
 * @date    22.05.2021
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include <hardware/switch.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

#define SW_GATED_EVENT(target, event)  \
	if (sw->gate == NULL || sw->gate(sw, event)) \
	{ \
		target = (event); \
		if (sw->_onPressed[sw->_onPressedPointer] != NULL) \
		{ \
			sw->_onPressed[sw->_onPressedPointer](sw); \
		} \
	}

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* External functions --------------------------------------------------------*/

void SW_Setup(SW_TypeDef *sw, uint8_t tag, SW_Modes mode, uint16_t min_short,
		uint16_t min_medium, uint16_t min_long, uint16_t rep_period,
		bool (*gate)(SW_TypeDef*, SW_Results))
{
	sw->tag = tag;
	sw->mode = mode;

	sw->min_short = min_short;
	sw->min_medium = min_medium;
	sw->min_long = min_long;
	sw->rep_period = rep_period;

	sw->gate = gate;
}

void SW_Init(SW_TypeDef *sw)
{
	sw->_onPressedPointer = 0;
	sw->_onPressed[sw->_onPressedPointer] = NULL;

	sw->pressed = SW_RESULT_WAITFOR_PRESS;
	sw->released = SW_RESULT_WAITFOR_PRESS;

	sw->_state = SW_STATE_OPEN;
	sw->_counter = 0;
	sw->_repetition_counter = 0;
	sw->_block_counter = 0;
}

void SW_RegisterOnPressed(SW_TypeDef *sw, void (*onPressed)(SW_TypeDef*))
{
	if (sw->_onPressed[sw->_onPressedPointer] != NULL)
		sw->_onPressedPointer++;

	sw->_onPressed[sw->_onPressedPointer] = onPressed;
}

void SW_UnregisterOnPressed(SW_TypeDef *sw)
{
	sw->_state = SW_STATE_BLOCKED;
	sw->_onPressed[sw->_onPressedPointer] = NULL;

	if (sw->_onPressedPointer > 0)
		sw->_onPressedPointer--;
}

void SW_Process(SW_TypeDef *sw, bool open)
{

#ifdef SW_AUTO_RESET
	// Reset Results
	sw->pressed = SW_RESULT_WAITFOR_PRESS;
	sw->released = SW_RESULT_WAITFOR_PRESS;
#endif

	if (sw->_state == SW_STATE_OPEN)
	{
		if (!open)
		{
			// Was open, now low -> pressed
			sw->_state = SW_STATE_PRESSED;
			sw->_counter = 0;
			sw->_repetition_counter = 0;
		}
	}
	else if (sw->_state == SW_STATE_BLOCKED)
	{
		sw->_block_counter++;
		if (open && sw->_block_counter >= sw->min_short)
		{
			sw->_block_counter = 0;
			sw->_state = SW_STATE_OPEN;
		}
	}
	else
	{
		if (sw->_counter >= sw->min_short && sw->_counter < sw->min_medium)
		{
			if (open)
			{
				SW_GATED_EVENT(sw->released, SW_RESULT_PRESSED_SHORT);
				sw->_state = SW_STATE_OPEN;
			}
			else if (sw->_counter == sw->min_short)
			{
				SW_GATED_EVENT(sw->pressed, SW_RESULT_PRESSED_SHORT);
			}
		}
		else if (sw->_counter >= sw->min_medium && sw->_counter < sw->min_long)
		{
			if (open)
			{
				SW_GATED_EVENT(sw->released, SW_RESULT_PRESSED_MEDIUM);
				sw->_state = SW_STATE_OPEN;
			}
			else if (sw->_counter == sw->min_medium)
			{
				sw->_repetition_counter = 0;
				SW_GATED_EVENT(sw->pressed, SW_RESULT_PRESSED_MEDIUM);
			}
			else if (sw->mode == SW_MODE_REPETITION && sw->_repetition_counter == sw->rep_period)
			{
				sw->_repetition_counter = 0;
				SW_GATED_EVENT(sw->pressed, SW_RESULT_PRESSED_REPETITIVE);
			}
		}
		else if (sw->_counter >= sw->min_long)
		{
			if (open)
			{
				SW_GATED_EVENT(sw->released, SW_RESULT_PRESSED_LONG);
				sw->_state = SW_STATE_OPEN;
			}
			else if (sw->_counter == sw->min_long)
			{
				sw->_repetition_counter = 0;
				SW_GATED_EVENT(sw->pressed, SW_RESULT_PRESSED_LONG);
			}
			else if (sw->mode == SW_MODE_REPETITION && sw->_repetition_counter == sw->rep_period)
			{
				sw->_repetition_counter = 0;
				SW_GATED_EVENT(sw->pressed, SW_RESULT_PRESSED_REPETITIVE);
			}
		}

		sw->_counter++;
		sw->_repetition_counter++;
	}
}
