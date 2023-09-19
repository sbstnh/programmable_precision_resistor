/**
 * @file    scpi_trigger_def.c
 * @author  sebas
 * @date    10.12.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "communication/scpi_trigger_def.h"
#include "communication/scpi_util.h"
#include "application/app_trigger.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/

scpi_choice_def_t SCPI_TRIG_SEQ_SOURce[] =
{
		{ "BUS",		SEQ_SOUR_BUS },
		{ "EXTernal",	SEQ_SOUR_EXTernal },
		{ "IMMediate",	SEQ_SOUR_IMMediate },
		{ "MANual",		SEQ_SOUR_MANual },
		{ "TIMer",		SEQ_SOUR_TIMer },
		{ "DEFault",	SEQ_SOUR_BUS },
		SCPI_CHOICE_LIST_END
};

scpi_choice_def_t SCPI_TRIG_SEQ_SLOPe[] =
{
		{ "POSitive",	SEQ_SLOP_POSITIVE },
		{ "NEGative",	SEQ_SLOP_NEGATIVE },
		{ "EITHer",		SEQ_SLOP_EITHER },
		{ "DEFault",	SEQ_SLOP_POSITIVE },
		SCPI_CHOICE_LIST_END
};

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

scpi_result_t SCPI_CMD_TRIG_ABOR_IMMediate(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	APP_Run_TriggerAbortImmediate();
	return SCPI_RES_OK;
}

scpi_result_t SCPI_CMD_TRIG_INIT_IMMediate(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	if (APP_Run_TriggerInitiateImmediate() != API_OK)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_INIT_IGNORED);
		return SCPI_RES_ERR;
	}

	return SCPI_RES_OK;
}


scpi_result_t SCPI_CMD_TRIG_INIT_CONTinuous(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ParamBool(context, APP_Set_TriggerInitiateContinuous);
}

scpi_result_t SCPI_CMD_TRIG_INIT_CONTinuous_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ResultBool(context, APP_Get_TriggerInitiateContinuous());
}


scpi_result_t SCPI_CMD_TRIG_TRG(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	APP_Run_TriggerBusTrg();
	return SCPI_RES_OK;
}


scpi_result_t SCPI_CMD_TRIG_SEQ_IMMediate(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	APP_Run_TriggerSequenceImmediate();
	return SCPI_RES_OK;
}


scpi_result_t SCPI_CMD_TRIG_SEQ_DELay(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	INT_VALUE_TypeDef delay = APP_Get_TriggerSequenceDelay();

	if (SCPI_ParamIntValueTypeDef(context, &delay, SCPI_UnitCheckerSecond, SCPI_DIVISOR_TO_SECOND, NULL) != SCPI_RES_OK)
	{
		return SCPI_RES_ERR;
	}

	// Try to set the new value
	if (APP_Set_TriggerSequenceDelay(delay.value) != API_OK)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
		return SCPI_RES_ERR;
	}

	return SCPI_RES_OK;
}

scpi_result_t SCPI_CMD_TRIG_SEQ_DELay_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPI_ResultIntValueTypeDefAsDouble(
			context,
			APP_Get_TriggerSequenceDelay(),
			SCPI_DIVISOR_TO_SECOND);
}


scpi_result_t SCPI_CMD_TRIG_SEQ_HOLDoff(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	INT_VALUE_TypeDef holdoff = APP_Get_TriggerSequenceHoldOff();

	if (SCPI_ParamIntValueTypeDef(context, &holdoff, SCPI_UnitCheckerSecond, SCPI_DIVISOR_TO_SECOND, NULL) != SCPI_RES_OK)
	{
		return SCPI_RES_ERR;
	}

	// Try to set the new value
	if (APP_Set_TriggerSequenceHoldOff(holdoff.value) != API_OK)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
		return SCPI_RES_ERR;
	}

	return SCPI_RES_OK;
}

scpi_result_t SCPI_CMD_TRIG_SEQ_HOLDoff_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPI_ResultIntValueTypeDefAsDouble(
			context,
			APP_Get_TriggerSequenceHoldOff(),
			SCPI_DIVISOR_TO_SECOND);
}


scpi_result_t SCPI_CMD_TRIG_SEQ_SOURce(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ParamChoice(
			context,
			SCPI_TRIG_SEQ_SOURce,
			(API_StatusTypeDef (*)(int32_t)) APP_Set_TriggerSequenceSource);
}

scpi_result_t SCPI_CMD_TRIG_SEQ_SOURce_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ResultMnemonic(
			context,
			SCPI_TRIG_SEQ_SOURce,
			APP_Get_TriggerSequenceSource());
}


scpi_result_t SCPI_CMD_TRIG_SEQ_SLOPe(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ParamChoice(
			context,
			SCPI_TRIG_SEQ_SLOPe,
			(API_StatusTypeDef (*)(int32_t)) APP_Set_TriggerSequenceSlope);
}

scpi_result_t SCPI_CMD_TRIG_SEQ_SLOPe_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ResultMnemonic(
			context,
			SCPI_TRIG_SEQ_SLOPe,
			APP_Get_TriggerSequenceSlope());
}


scpi_result_t SCPI_CMD_TRIG_SEQ_TIMer(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	INT_VALUE_TypeDef timer = APP_Get_TriggerSequenceHoldOff();

	if (SCPI_ParamIntValueTypeDef(context, &timer, SCPI_UnitCheckerSecond, SCPI_DIVISOR_TO_SECOND, NULL) != SCPI_RES_OK)
	{
		return SCPI_RES_ERR;
	}

	// Try to set the new value
	if (APP_Set_TriggerSequenceTimer(timer.value) != API_OK)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
		return SCPI_RES_ERR;
	}

	return SCPI_RES_OK;
}

scpi_result_t SCPI_CMD_TRIG_SEQ_TIMer_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPI_ResultIntValueTypeDefAsDouble(
			context,
			APP_Get_TriggerSequenceTimer(),
			SCPI_DIVISOR_TO_SECOND);
}


/* Private functions ---------------------------------------------------------*/

