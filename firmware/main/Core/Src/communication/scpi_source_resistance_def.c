/**
 * @file    scpi_source_resistance_def.c
 * @author  sebas
 * @date    11.11.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "communication/scpi_source_resistance_def.h"
#include "prog_res/prog_res_def.h"
#include "communication/scpi_util.h"
#include "communication/scpi_source_mode_def.h"

#include "application/app_input.h"
#include "application/app_source.h"


/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/

scpi_choice_def_t SCPI_SOUR_RES_MODE[] =
{
		{ "FIXed",   RES_MODE_FIXed },
		{ "STEP",    RES_MODE_STEP },
		{ "UP",      RES_MODE_UP },
		{ "DOWN",    RES_MODE_DOWN },
		{ "LIST",    RES_MODE_LIST },
		{ "DEFault", RES_MODE_FIXed },
		SCPI_CHOICE_LIST_END
};


scpi_choice_def_t SCPI_SOUR_RES_LEV_STEP_MODE[] =
{
		{ "LINear",  STEP_MODE_LINear },
		{ "LDECade", STEP_MODE_LDECade },
		{ "L125",    STEP_MODE_L125 },
		{ "L13",     STEP_MODE_L13 },
		{ "DEFault", STEP_MODE_LINear },
		SCPI_CHOICE_LIST_END
};


scpi_choice_def_t SCPI_SOUR_RES_LEV_STEP_OVERflow[] =
{
		{ "LIMit",   STEP_OVER_LIMit },
		{ "STAY",    STEP_OVER_STAY },
		{ "RESet",   STEP_OVER_RESet },
		{ "DEFault", STEP_OVER_LIMit },
		SCPI_CHOICE_LIST_END
};

/* Private macros ------------------------------------------------------------*/

#define SCPI_TO_MILLI_OHM(x)		(SCPI_OHM_CONVERSION_FACTOR * (x))
#define SCPI_TO_OHM(x)				((x) / SCPI_OHM_CONVERSION_FACTOR)

/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

scpi_result_t SCPI_CMD_SOUR_RES_LEV_IMM_AMPLitude(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	API_StatusTypeDef result;
	INT_VALUE_TypeDef amplitude = APP_Get_SourceResistanceLevelImmediateAmplitude();
	LEV_STEP_TypeDef *step = (LEV_STEP_TypeDef *) APP_Get_SourceResistanceLevelStep();

	if (SCPI_ParamIntValueTypeDef(context, &amplitude, SCPI_UnitCheckerOhm, SCPI_DIVISOR_TO_OHM, step) != SCPI_RES_OK)
	{
		return SCPI_RES_ERR;
	}

	// Try to set the new value
	result = APP_Set_SourceResistanceLevelImmediateAmplitude(amplitude.value, true);

	if (result == API_PARAM_OUT_OF_RANGE)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
		return SCPI_RES_ERR;
	}

	if (result == API_HARDWARE_ERROR)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_HARDWARE_ERROR);
		return SCPI_RES_ERR;
	}

	if (result != API_OK)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_SYSTEM_ERROR);
		return SCPI_RES_ERR;
	}

	return SCPI_RES_OK;
}

scpi_result_t SCPI_CMD_SOUR_RES_LEV_IMM_AMPLitude_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPI_ResultIntValueTypeDefAsDouble(
			context,
			APP_Get_SourceResistanceLevelImmediateAmplitude(),
			SCPI_DIVISOR_TO_OHM);
}


scpi_result_t SCPI_CMD_SOUR_RES_LEV_IMM_CALCulate_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	SOUR_MODE_TypeDef mode;
	int32_t choice;
	int32_t calc;

	if (SCPI_ParamChoice(context, SCPI_SOUR_MODE, &choice, FALSE))
	{
    	switch (choice)
		{
			case SOUR_MODE_TWIRe:
			case SOUR_MODE_FWIRe:
			case SOUR_MODE_UNCalibrated:
				mode = (STEP_MODE_TypeDef) choice;
				break;
			default:
				mode = APP_Get_SourceMode();
				break;
		}
	}
	else if (!SCPI_ParamErrorOccurred(context))
	{
		mode = APP_Get_SourceMode();
	}
	else
	{
		return SCPI_RES_ERR;
	}

	if (APP_Run_SourceResistanceLevelImmediateCalculate(mode, &calc) != API_OK)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_SYSTEM_ERROR);
		return SCPI_RES_ERR;
	}

	SCPI_ResultDouble(context, SCPI_TO_OHM((double)calc));

    return SCPI_RES_OK;
}


scpi_result_t SCPI_CMD_SOUR_RES_LEV_TRIG_AMPLitude(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	API_StatusTypeDef result;
	INT_VALUE_TypeDef amplitude = APP_Get_SourceResistanceLevelTriggeredAmplitude();
	LEV_STEP_TypeDef *step = (LEV_STEP_TypeDef *) APP_Get_SourceResistanceLevelStep();

	if (SCPI_ParamIntValueTypeDef(context, &amplitude, SCPI_UnitCheckerOhm, SCPI_DIVISOR_TO_OHM, step) != SCPI_RES_OK)
	{
		return SCPI_RES_ERR;
	}

	// Try to set the new value
	result = APP_Set_SourceResistanceLevelTriggeredAmplitude(amplitude.value);

	if (result == API_PARAM_OUT_OF_RANGE)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
		return SCPI_RES_ERR;
	}

	if (result != API_OK)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_SYSTEM_ERROR);
		return SCPI_RES_ERR;
	}

	return SCPI_RES_OK;
}


scpi_result_t SCPI_CMD_SOUR_RES_LEV_TRIG_AMPLitude_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPI_ResultIntValueTypeDefAsDouble(
			context,
			APP_Get_SourceResistanceLevelTriggeredAmplitude(),
			SCPI_DIVISOR_TO_OHM);
}


scpi_result_t SCPI_CMD_SOUR_RES_LEV_TRIG_CALCulate_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	SOUR_MODE_TypeDef mode;
	int32_t choice;
	int32_t calc;

	if (SCPI_ParamChoice(context, SCPI_SOUR_MODE, &choice, FALSE))
	{
    	switch (choice)
		{
			case SOUR_MODE_TWIRe:
			case SOUR_MODE_FWIRe:
			case SOUR_MODE_UNCalibrated:
				mode = (STEP_MODE_TypeDef) choice;
				break;
			default:
				mode = APP_Get_SourceMode();
				break;
		}
	}
	else if (!SCPI_ParamErrorOccurred(context))
	{
		mode = APP_Get_SourceMode();
	}
	else
	{
		return SCPI_RES_ERR;
	}


	if (APP_Run_SourceResistanceLevelTriggeredCalculate(mode, &calc) != API_OK)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_SYSTEM_ERROR);
		return SCPI_RES_ERR;
	}

	SCPI_ResultDouble(context, SCPI_TO_OHM((double)calc));

    return SCPI_RES_OK;
}


scpi_result_t SCPI_CMD_SOUR_RES_LEV_STEP_INCRement(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	INT_VALUE_TypeDef increment = APP_Get_SourceResistanceLevelStepIncrement();

	if (SCPI_ParamIntValueTypeDef(context, &increment, SCPI_UnitCheckerOhm, SCPI_DIVISOR_TO_OHM, NULL) != SCPI_RES_OK)
	{
		return SCPI_RES_ERR;
	}

	// Try to set the new value
	if (APP_Set_SourceResistanceLevelStepIncrement(increment.value) != API_OK)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
		return SCPI_RES_ERR;
	}

	return SCPI_RES_OK;
}

scpi_result_t SCPI_CMD_SOUR_RES_LEV_STEP_INCRement_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPI_ResultIntValueTypeDefAsDouble(
			context,
			APP_Get_SourceResistanceLevelStepIncrement(),
			SCPI_DIVISOR_TO_OHM);
}


scpi_result_t SCPI_CMD_SOUR_RES_LEV_STEP_MODE(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ParamChoice(
			context,
			SCPI_SOUR_RES_LEV_STEP_MODE,
			(API_StatusTypeDef (*)(int32_t)) APP_Set_SourceResistanceLevelStepMode);
}

scpi_result_t SCPI_CMD_SOUR_RES_LEV_STEP_MODE_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ResultMnemonic(
			context,
			SCPI_SOUR_RES_LEV_STEP_MODE,
			APP_Get_SourceResistanceLevelStepMode());
}


scpi_result_t SCPI_CMD_SOUR_RES_LEV_STEP_OVERflow(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ParamChoice(
			context,
			SCPI_SOUR_RES_LEV_STEP_OVERflow,
			(API_StatusTypeDef (*)(int32_t)) APP_Set_SourceResistanceLevelStepOverflow);
}

scpi_result_t SCPI_CMD_SOUR_RES_LEV_STEP_OVERflow_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ResultMnemonic(
			context,
			SCPI_SOUR_RES_LEV_STEP_OVERflow,
			APP_Get_SourceResistanceLevelStepOverflow());
}


scpi_result_t SCPI_CMD_SOUR_RES_LIM_LOW(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	INT_VALUE_TypeDef low = APP_Get_SourceResistanceLimitLower();

	if (SCPI_ParamIntValueTypeDef(context, &low, SCPI_UnitCheckerOhm, SCPI_DIVISOR_TO_OHM, NULL) != SCPI_RES_OK)
	{
		return SCPI_RES_ERR;
	}

	// Try to set the new value
	API_StatusTypeDef result = APP_Set_SourceResistanceLimitLower(low.value);
	if (result == API_PARAM_OUT_OF_RANGE)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
		return SCPI_RES_ERR;
	}
	else if (result != API_OK)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_SYSTEM_ERROR);
		return SCPI_RES_ERR;
	}

	return SCPI_RES_OK;
}

scpi_result_t SCPI_CMD_SOUR_RES_LIM_LOW_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPI_ResultIntValueTypeDefAsDouble(
			context,
			APP_Get_SourceResistanceLimitLower(),
			SCPI_DIVISOR_TO_OHM);
}


scpi_result_t SCPI_CMD_SOUR_RES_LIM_STATe(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ParamBool(context, APP_Set_SourceResistanceLimitState);
}

scpi_result_t SCPI_CMD_SOUR_RES_LIM_STATe_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ResultBool(context, APP_Get_SourceResistanceLimitState());
}


scpi_result_t SCPI_CMD_SOUR_RES_LIM_HIGH(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	INT_VALUE_TypeDef high = APP_Get_SourceResistanceLimitUpper();

	if (SCPI_ParamIntValueTypeDef(context, &high, SCPI_UnitCheckerOhm, SCPI_DIVISOR_TO_OHM, NULL) != SCPI_RES_OK)
	{
		return SCPI_RES_ERR;
	}

	// Try to set the new value
	API_StatusTypeDef result = APP_Set_SourceResistanceLimitUpper(high.value);
	if (result == API_PARAM_OUT_OF_RANGE)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
		return SCPI_RES_ERR;
	}
	else if (result != API_OK)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_SYSTEM_ERROR);
		return SCPI_RES_ERR;
	}

	return SCPI_RES_OK;
}

scpi_result_t SCPI_CMD_SOUR_RES_LIM_HIGH_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPI_ResultIntValueTypeDefAsDouble(
			context,
			APP_Get_SourceResistanceLimitUpper(),
			SCPI_DIVISOR_TO_OHM);
}


scpi_result_t SCPI_CMD_SOUR_RES_MODE(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ParamChoice(
			context,
			SCPI_SOUR_RES_MODE,
			(API_StatusTypeDef (*)(int32_t)) APP_Set_SourceResistanceMode);
}

scpi_result_t SCPI_CMD_SOUR_RES_MODE_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ResultMnemonic(
			context,
			SCPI_SOUR_RES_MODE,
			APP_Get_SourceResistanceMode());
}

/* Private functions ---------------------------------------------------------*/

