/**
 * @file    trigger_timer.c
 * @author  sebas
 * @date    15.01.2023
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "trigger/trigger_timer.h"
#include "trigger/trigger_logic.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void TRIGTIM_ParamsSetup(TRIGTIM_ParamsTypeDef *trig_tim, bool (*detect_event)(TRIGTIM_ParamsTypeDef *))
{
	trig_tim->_detect_event = detect_event;
	trig_tim->_ticks = 0;
}

void TRIGTIM_ParamsSetBus(TRIGTIM_ParamsTypeDef *trig_tim, bool (*detect_event)(TRIGTIM_ParamsTypeDef *))
{
	trig_tim->_detect_event = detect_event;
}

void TRIGTIM_Init(TRIG_LogicTypeDef *trig_logic)
{
	TRIGTIM_ParamsTypeDef *params = (TRIGTIM_ParamsTypeDef *)trig_logic->params;

	// Make sure any previous trigger is being cleared
	params->_detect_event(params);
	params->_ticks = 0;
}

bool TRIGTIM_Cycle(TRIG_LogicTypeDef *trig_logic)
{
	TRIGTIM_ParamsTypeDef *params = (TRIGTIM_ParamsTypeDef *)trig_logic->params;
	params->_ticks++;
	return params->_detect_event(params);
}

/* Private functions ---------------------------------------------------------*/

