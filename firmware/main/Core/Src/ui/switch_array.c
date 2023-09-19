/*
 * switch_def.c
 *
 *  Created on: 11.11.2022
 *      Author: sebas
 */

/* Includes ------------------------------------------------------------------*/

#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "queue.h"

#include "util/util.h"
#include "util/util_rtos.h"

#include "ui/switch_array.h"
#include "hardware/switch_def.h"

/* Private defines -----------------------------------------------------------*/

#define SWA_TIMEOUT			5

/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/

extern osMessageQueueId_t keycodeQueueHandle;

/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void SWA_Init(SWA_TypeDef *swa)
{
	swa->_last_active = 0;
	swa->_on_pressed_pointer = 0;
}


bool SWA_Get_Shift(SWA_TypeDef *swa)
{
	return swa->_shift;
}


void SWA_Reset_Shift(SWA_TypeDef *swa)
{
	swa->_shift = false;
}


void SWA_Process(SWA_TypeDef *swa, uint32_t open)
{
	uint8_t keycode;

	for (uint8_t s = 0; s < swa->switch_count; s++)
	{
		SW_Process(&swa->switches[s], (open >> s) & 1);

		if (swa->switches[s].pressed == SW_RESULT_WAITFOR_PRESS
				|| swa->switches[s].pressed == SW_RESULT_PRESSED_MEDIUM
				|| swa->switches[s].pressed == SW_RESULT_PRESSED_LONG)
		{
			swa->switches[s].pressed = SW_RESULT_WAITFOR_PRESS;
			continue;
		}

		swa->switches[s].pressed = SW_RESULT_WAITFOR_PRESS;

		if (swa->gate == NULL || swa->gate(swa, &swa->switches[s]))
		{
			keycode = swa->switches[s].tag;

			if (swa->_shift)
			{
				swa->_shift = false;
				keycode |= SW_SHIFT_KEY_CODE_MODIFIER;
			}

			osMessageQueuePut(keycodeQueueHandle, &keycode, 0, SWA_TIMEOUT);
		}
	}
}

uint8_t SWA_Peek_KeyCode()
{
	uint8_t keycode;
	if (osMessageQueuePeek(keycodeQueueHandle, &keycode, NULL, 0) == osOK)
	{
		return keycode;
	}
	return SW_NONE;
}


uint8_t SWA_Get_KeyCode()
{
	uint8_t keycode;
	if (osMessageQueueGet(keycodeQueueHandle, &keycode, NULL, 0) == osOK)
	{
		return keycode;
	}
	return SW_NONE;
}


void SWA_SkipAll_KeyCodes()
{
	osMessageQueueReset(keycodeQueueHandle);
}


/* Private functions ---------------------------------------------------------*/
