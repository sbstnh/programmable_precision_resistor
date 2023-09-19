/**
 * @file    annunciator_array.c
 * @author  sebas
 * @date    Jan 15, 2023
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include <ui/annunciator_array.h>

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/


void ANNA_SetupAndInitAll(ANNA_TypeDef *anna)
{
	for (uint8_t i = 0; i < anna->_count; i++)
	{
		ANN_Init(&anna->_annunciators[i]);
	}
}

void ANNA_SwitchAllOff(ANNA_TypeDef *anna)
{
	for (uint8_t i = 0; i < anna->_count; i++)
	{
		ANN_SetState(&anna->_annunciators[i], ANN_OFF);
	}
}


uint16_t ANNA_Get_State(ANNA_TypeDef *anna)
{
	uint16_t state = 0;

	for (uint8_t i = 0; i < anna->_count; i++)
	{
		if (anna->_annunciators[i]._state.red)
		{
			state |= 1 << anna->_annunciators[i].tag_r;
		}
		if (anna->_annunciators[i]._state.green)
		{
			state |= 1 << anna->_annunciators[i].tag_g;
		}
	}

	return state;
}


uint16_t ANNA_Get_Blink(ANNA_TypeDef *anna)
{
	uint16_t blink = 0;

	for (uint8_t i = 0; i < anna->_count; i++)
	{
		if (anna->_annunciators[i]._blink)
		{
			blink |= (1 << anna->_annunciators[i].tag_r) | (1 << anna->_annunciators[i].tag_g);
		}
	}

	return blink;
}

/* Private functions ---------------------------------------------------------*/

