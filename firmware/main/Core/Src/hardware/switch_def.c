/*
 * switch_def.c
 *
 *  Created on: Aug 22, 2021
 *      Author: sebas
 */

/* Includes ------------------------------------------------------------------*/

#include "util/util.h"

#include "ui/switch_array_def.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

bool SW_Gate(SW_TypeDef *sw, SW_Results result);

/* Exported variables --------------------------------------------------------*/

SW_TypeDef SW[SW_NUMBER_OF_SWITCHES];

/* Exported functions --------------------------------------------------------*/

void SW_SetupAndInitAll()
{
	for (uint8_t s = 0; s < COUNT_OF(SW); s++)
	{
		SW_Setup(&SW[s], s, SW_MODE_NORMAL,
				SW_MIN_SHORT, SW_MIN_MEDIUM, SW_MIN_LONG,
				SW_REP_PERIOD,
				SW_Gate);
		SW_Init(&SW[s]);
	}

	// Enable repetitive mode for a few selected switches
	SW[SW_LEFT].mode = SW_MODE_REPETITION;
	SW[SW_RIGHT].mode = SW_MODE_REPETITION;
	SW[SW_BACKSP].mode = SW_MODE_REPETITION;
}

/* Private functions ---------------------------------------------------------*/

bool SW_Gate(SW_TypeDef *sw, SW_Results result)
{
	return !SWA_Get_Shift(&SWA) || result != SW_RESULT_PRESSED_REPETITIVE;
}
