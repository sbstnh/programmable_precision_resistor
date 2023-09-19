/**
 * @file    trigger_def.c
 * @author  sebas
 * @date    03.12.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "trigger/trigger_def.h"
#include "application/app_trigger.h"
#include "application/app_source.h"
#include "application/app_input.h"

#include "ui/annunciator_helper.h"
#include "ui/display_helper.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

void TRIG_OnArmed();
void TRIG_OnTriggered();

/* Exported variables --------------------------------------------------------*/

//----- Input inhibit trigger

TRIGEDGE_ParamsTypeDef TRIG_INHIBIT_PARAMS =
{
		._detect_event = TRIGEDGE_Inhibit_DetectEvent,
		._debounce_cycles = 1,
		._slope = TRIGEDGE_SLOPE_POSITIVE
};

TRIG_LogicTypeDef TRIG_LOGIC_INHIBIT =
{
		.trig_init = TRIGEDGE_Init,
		.trig_cycle = TRIGEDGE_Cycle,

		.params = &TRIG_INHIBIT_PARAMS
};

TRIG_TypeDef TRIG_INHIBIT =
{
		._continuous = false,
		._delay = 0,
		._holdoff = 0,

		._trig_logic = &TRIG_LOGIC_INHIBIT
};

//----- Edge trigger

TRIGEDGE_ParamsTypeDef TRIGEDGE_PARAMS =
{
		._detect_event = TRIGEDGE_DetectEvent,
		._debounce_cycles = 1,
		._slope = TRIGEDGE_SLOPE_POSITIVE
};

TRIG_LogicTypeDef TRIG_LOGIC_EDGE =
{
		.trig_init = TRIGEDGE_Init,
		.trig_cycle = TRIGEDGE_Cycle,

		.params = &TRIGEDGE_PARAMS
};

//----- Bus trigger

TRIGBUS_ParamsTypeDef TRIGBUS_PARAMS =
{
		._detect_event = TRIGBUS_DetectEvent
};

TRIG_LogicTypeDef TRIG_LOGIC_BUS =
{
		.trig_init = TRIGBUS_Init,
		.trig_cycle = TRIGBUS_Cycle,

		.params = &TRIGBUS_PARAMS
};

//----- Immediate trigger

TRIG_LogicTypeDef TRIG_LOGIC_IMMEDIATE =
{
		.trig_init = TRIGIMM_Init,
		.trig_cycle = TRIGIMM_Cycle,

		.params = NULL
};

//----- Manual trigger

TRIGMAN_ParamsTypeDef TRIGMAN_PARAMS =
{
		._detect_event = TRIGMAN_DetectEvent
};

TRIG_LogicTypeDef TRIG_LOGIC_MANUAL =
{
		.trig_init = TRIGMAN_Init,
		.trig_cycle = TRIGMAN_Cycle,

		.params = &TRIGMAN_PARAMS
};

//----- Timer trigger

TRIGTIM_ParamsTypeDef TRIGTIM_PARAMS =
{
		._detect_event = TRIGTIM_DetectEvent
};

TRIG_LogicTypeDef TRIG_LOGIC_TIMER =
{
		.trig_init = TRIGTIM_Init,
		.trig_cycle = TRIGTIM_Cycle,

		.params = &TRIGTIM_PARAMS
};

//----- Trigger

TRIG_TypeDef TRIG =
{
		._continuous = false,
		._delay = 0,
		._holdoff = 0,

		.on_triggered = TRIG_OnTriggered,

		._trig_logic = &TRIG_LOGIC_EDGE
};

/* Exported functions --------------------------------------------------------*/


bool TRIGEDGE_Inhibit_DetectEvent(TRIGEDGE_ParamsTypeDef *params)
{
	(void) params;

	if (APP_Get_InputInhibitMode() != INH_MODE_LATChing)
	{
		return false;
	}

	if (APP_Get_SourceDigitalPinFunction(SOUR_DIG_PIN1) == PIN_FUNC_INHibit && APP_Get_SourceDigitalPinData(SOUR_DIG_PIN1))
	{
		return true;
	}
	if (APP_Get_SourceDigitalPinFunction(SOUR_DIG_PIN2) == PIN_FUNC_INHibit && APP_Get_SourceDigitalPinData(SOUR_DIG_PIN2))
	{
		return true;
	}

	return false;
}


bool TRIGEDGE_DetectEvent(TRIGEDGE_ParamsTypeDef *params)
{
	(void) params;

	if (APP_Get_TriggerSequenceSource() != SEQ_SOUR_EXTernal)
	{
		return false;
	}

	if (APP_Get_SourceDigitalPinFunction(SOUR_DIG_PIN1) == PIN_FUNC_TINPut && APP_Get_SourceDigitalPinData(SOUR_DIG_PIN1))
	{
		return true;
	}
	if (APP_Get_SourceDigitalPinFunction(SOUR_DIG_PIN2) == PIN_FUNC_TINPut && APP_Get_SourceDigitalPinData(SOUR_DIG_PIN2))
	{
		return true;
	}

	return false;
}


bool TRIGBUS_DetectEvent(TRIGBUS_ParamsTypeDef *params)
{
	(void) params;

	if (APP_Get_TriggerBusTrg())
	{
		APP_Set_TriggerBusTrg(false);
		return true;
	}

	return false;
}


bool TRIGMAN_DetectEvent(TRIGMAN_ParamsTypeDef *params)
{
	(void) params;

	if (APP_Get_TriggerManualTrigger())
	{
		APP_Set_TriggerManualTrigger(false);
		return true;
	}

	return false;
}


bool TRIGTIM_DetectEvent(TRIGTIM_ParamsTypeDef *params)
{
	if (params->_ticks < APP_Get_TriggerSequenceTimer().value)
	{
		return false;
	}

	params->_ticks = 0;
	return true;
}


void TRIG_OnTriggered()
{
	ANNH_OnTriggered();
	UI_Display_OnTriggered();
}

/* Private functions ---------------------------------------------------------*/
