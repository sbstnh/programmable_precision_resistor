/**
 * @file    app_trigger.c
 * @author  sebas
 * @date    10.12.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "application/app_trigger.h"
#include "application/app_util.h"

#include "trigger/trigger_def.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void APP_Run_TriggerAbortImmediate()
{
	TRIG_Abort(&TRIG);

	if (APP.TRIGger.INITiate.CONTinuous)
	{
		// Comply with SCPI standard and re-initiate immediately
		TRIG_Initiate(&TRIG);
	}
}


API_StatusTypeDef APP_Run_TriggerInitiateImmediate()
{
	if (TRIG_GetState(&TRIG) != TRIG_STATE_IDLE)
	{
		return API_INVALID_OPERATION;
	}

	TRIG_Initiate(&TRIG);
	return API_OK;
}

bool APP_Get_TriggerInitiated()
{
	return TRIG_GetState(&TRIG) != TRIG_STATE_IDLE;
}


bool APP_Get_TriggerInitiateContinuous()
{
	return APP.TRIGger.INITiate.CONTinuous;
}

API_StatusTypeDef APP_Set_TriggerInitiateContinuous(bool continuous)
{
	RETURN_OK_IF_TRUE(APP.TRIGger.INITiate.CONTinuous == continuous);

	APP.TRIGger.INITiate.CONTinuous = continuous;

	TRIG_Continuous(&TRIG, continuous);

	return API_OK;
}


API_StatusTypeDef APP_Run_TriggerImmediate()
{
	TRIG_Immediate(&TRIG);
	return API_OK;
}


void APP_Run_TriggerBusTrg()
{
	APP.TRIGger._bus_trig_received = true;
}

bool APP_Get_TriggerBusTrg()
{
	return APP.TRIGger._bus_trig_received;
}

void APP_Set_TriggerBusTrg(bool trg)
{
	APP.TRIGger._bus_trig_received = trg;
}


void APP_Run_TriggerManualTrigger()
{
	APP.TRIGger._manual_trig_received = true;
}

bool APP_Get_TriggerManualTrigger()
{
	return APP.TRIGger._manual_trig_received;
}

void APP_Set_TriggerManualTrigger(bool trg)
{
	APP.TRIGger._manual_trig_received = trg;
}


void APP_Run_TriggerSequenceImmediate()
{
	TRIG_Immediate(&TRIG);
}


INT_VALUE_TypeDef APP_Get_TriggerSequenceDelay()
{
	return APP.TRIGger.SEQuence.DELay;
}

API_StatusTypeDef APP_Set_TriggerSequenceDelay(int32_t delay)
{
	RETURN_OK_IF_TRUE(APP.TRIGger.SEQuence.DELay.value == delay);

	// Check for value out of range
	if (!INT_VALUE_IN_RANGE(APP.TRIGger.SEQuence.DELay, delay))
	{
		return API_PARAM_OUT_OF_RANGE;
	}

	APP.TRIGger.SEQuence.DELay.value = delay;

	TRIG_SetDelay(&TRIG, delay);

	return API_OK;
}


INT_VALUE_TypeDef APP_Get_TriggerSequenceHoldOff()
{
	return APP.TRIGger.SEQuence.HOLDoff;
}

API_StatusTypeDef APP_Set_TriggerSequenceHoldOff(int32_t holdoff)
{
	RETURN_OK_IF_TRUE(APP.TRIGger.SEQuence.HOLDoff.value == holdoff);

	// Check for value out of range
	if (!INT_VALUE_IN_RANGE(APP.TRIGger.SEQuence.HOLDoff, holdoff))
	{
		return API_PARAM_OUT_OF_RANGE;
	}

	APP.TRIGger.SEQuence.HOLDoff.value = holdoff;

	TRIG_SetHoldOff(&TRIG, holdoff);

	return API_OK;
}


SEQ_SOURce_TypeDef APP_Get_TriggerSequenceSource()
{
	return APP.TRIGger.SEQuence.SOURce;
}

API_StatusTypeDef APP_Set_TriggerSequenceSource(SEQ_SOURce_TypeDef source)
{
	RETURN_OK_IF_TRUE(APP.TRIGger.SEQuence.SOURce == source);

	// Check for value out of range
	if (source < SEQ_SOUR_BUS || source > SEQ_SOUR_TIMer)
	{
		return API_PARAM_OUT_OF_RANGE;
	}

	APP.TRIGger.SEQuence.SOURce = source;

	switch (source)
	{
		default:
		case SEQ_SOUR_BUS:
			TRIGBUS_ParamsSetup(&TRIGBUS_PARAMS, TRIGBUS_DetectEvent);
			TRIG_Init(&TRIG, &TRIG_LOGIC_BUS);
			break;

		case SEQ_SOUR_EXTernal:
			TRIGEDGE_ParamsSetup(&TRIGEDGE_PARAMS, TRIGEDGE_DetectEvent, APP.TRIGger.SEQuence.SLOPe, 1);
			TRIG_Init(&TRIG, &TRIG_LOGIC_EDGE);
			break;

		case SEQ_SOUR_IMMediate:
			TRIG_Init(&TRIG, &TRIG_LOGIC_IMMEDIATE);
			break;

		case SEQ_SOUR_MANual:
			TRIGMAN_ParamsSetup(&TRIGMAN_PARAMS, TRIGMAN_DetectEvent);
			TRIG_Init(&TRIG, &TRIG_LOGIC_MANUAL);
			break;

		case SEQ_SOUR_TIMer:
			TRIGTIM_ParamsSetup(&TRIGTIM_PARAMS, TRIGTIM_DetectEvent);
			TRIG_Init(&TRIG, &TRIG_LOGIC_TIMER);
			break;
	}

	return API_OK;
}


SEQ_SLOPe_TypeDef APP_Get_TriggerSequenceSlope()
{
	return APP.TRIGger.SEQuence.SLOPe;
}

API_StatusTypeDef APP_Set_TriggerSequenceSlope(SEQ_SLOPe_TypeDef slope)
{
	RETURN_OK_IF_TRUE(APP.TRIGger.SEQuence.SLOPe == slope);

	// Check for value out of range
	if (slope < SEQ_SLOP_POSITIVE || slope > SEQ_SLOP_EITHER)
	{
		return API_PARAM_OUT_OF_RANGE;
	}

	APP.TRIGger.SEQuence.SLOPe = slope;

	TRIGEDGE_ParamsSetSlope(&TRIGEDGE_PARAMS, (TRIGEDGE_SlopeTypeDef) slope);

	return API_OK;
}


INT_VALUE_TypeDef APP_Get_TriggerSequenceTimer()
{
	return APP.TRIGger.SEQuence.TIMer;
}

API_StatusTypeDef APP_Set_TriggerSequenceTimer(int32_t timer)
{
	RETURN_OK_IF_TRUE(APP.TRIGger.SEQuence.TIMer.value == timer);

	// Check for value out of range
	if (!INT_VALUE_IN_RANGE(APP.TRIGger.SEQuence.TIMer, timer))
	{
		return API_PARAM_OUT_OF_RANGE;
	}

	APP.TRIGger.SEQuence.TIMer.value = timer;

	// TODO: Implementation of timer trigger
	//TRIG_SetHoldOff(&TRIG, timer);

	return API_OK;
}

/* Private functions ---------------------------------------------------------*/

