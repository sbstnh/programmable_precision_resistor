/**
 * @file    trigger_manual.c
 * @author  sebas
 * @date    14.01.2023
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "trigger/trigger_manual.h"
#include "trigger/trigger_logic.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void TRIGMAN_ParamsSetup(TRIGMAN_ParamsTypeDef *trig_man, bool (*detect_event)(TRIGMAN_ParamsTypeDef *))
{
	trig_man->_detect_event = detect_event;
}

void TRIGMAN_ParamsSetBus(TRIGMAN_ParamsTypeDef *trig_man, bool (*detect_event)(TRIGMAN_ParamsTypeDef *))
{
	trig_man->_detect_event = detect_event;
}

void TRIGMAN_Init(TRIG_LogicTypeDef *trig_logic)
{
	TRIGMAN_ParamsTypeDef *params = (TRIGMAN_ParamsTypeDef *)trig_logic->params;

	// Make sure any previous trigger is being cleared
	params->_detect_event(params);
}

bool TRIGMAN_Cycle(TRIG_LogicTypeDef *trig_logic)
{
	TRIGMAN_ParamsTypeDef *params = (TRIGMAN_ParamsTypeDef *)trig_logic->params;
	return params->_detect_event(params);
}

/* Private functions ---------------------------------------------------------*/

