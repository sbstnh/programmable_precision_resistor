/**
 * @file    trigger_bus.c
 * @author  sebas
 * @date    14.01.2023
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "trigger/trigger_bus.h"
#include "trigger/trigger_logic.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void TRIGBUS_ParamsSetup(TRIGBUS_ParamsTypeDef *trig_bus, bool (*detect_event)(TRIGBUS_ParamsTypeDef *))
{
	trig_bus->_detect_event = detect_event;
}

void TRIGBUS_ParamsSetBus(TRIGBUS_ParamsTypeDef *trig_bus, bool (*detect_event)(TRIGBUS_ParamsTypeDef *))
{
	trig_bus->_detect_event = detect_event;
}

void TRIGBUS_Init(TRIG_LogicTypeDef *trig_logic)
{
	TRIGBUS_ParamsTypeDef *params = (TRIGBUS_ParamsTypeDef *)trig_logic->params;

	// Make sure any previous trigger is being cleared
	params->_detect_event(params);
}

bool TRIGBUS_Cycle(TRIG_LogicTypeDef *trig_logic)
{
	TRIGBUS_ParamsTypeDef *params = (TRIGBUS_ParamsTypeDef *)trig_logic->params;
	return params->_detect_event(params);
}

/* Private functions ---------------------------------------------------------*/

