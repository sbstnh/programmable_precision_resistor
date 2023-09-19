/**
 * @file    scpi_util.c
 * @author  sebas
 * @date    04.12.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "communication/scpi_util.h"
#include "application/step.h"
#include "application/app_calibration.h"
#include "application/app_system.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

// --------------- Guard functions

scpi_result_t SCPI_HandleCalModeAndRLState(scpi_t *context)
{
	if (SCPI_HandleRLState(context) != SCPI_RES_OK || SCPI_HandleCalMode(context) != SCPI_RES_OK)
	{
		return SCPI_RES_ERR;
	}

	return SCPI_RES_OK;
}

scpi_result_t SCPI_HandleCalMode(scpi_t *context)
{
	if (APP_Get_CalibrationState())
	{
		SCPI_ErrorPush(context, SCPI_ERROR_EXECUTION_ERROR);
		return SCPI_RES_ERR;
	}

	return SCPI_RES_OK;
}

scpi_result_t SCPI_HandleRLState(scpi_t *context)
{
	if (APP_Get_SystemCommunicateRLState() == COMM_RLST_LOCal)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_INVAL_WHILE_IN_LOCAL);
		return SCPI_RES_ERR;
	}

	return SCPI_RES_OK;
}

// --------------- Functions for reading numbers from SCPI message

scpi_result_t SCPI_ParamIntValueTypeDef(scpi_t *context, INT_VALUE_TypeDef *value,
		bool (*unit_checker)(scpi_number_t *), double factor, LEV_STEP_TypeDef *step)
{
	scpi_number_t number;

	// Obtain number
    GET_PARAM_NUMBER_MANDATORY(scpi_special_numbers_def, &number);

    // Handle special values
    if (number.special)
    {
    	switch (number.content.tag)
		{
			case SCPI_NUM_MIN:
				value->value = value->min;
				break;

			case SCPI_NUM_MAX:
				value->value = value->max;
				break;

			case SCPI_NUM_DOWN:
				if (step != NULL)
				{
					value->value = STEP_CalculateDown(step, *value);
					break;
				}

			case SCPI_NUM_UP:
				if (step != NULL)
				{
					value->value = STEP_CalculateUp(step, *value);
					break;
				}

			default:
				SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
				return SCPI_RES_ERR;
		}

    	return SCPI_RES_OK;
    }

    // Handle normal numbers
    // Check unit
    if (!unit_checker(&number))
    {
    	SCPI_ErrorPush(context, SCPI_ERROR_INVALID_SUFFIX);
    	return SCPI_RES_ERR;
    }

    // Multiply with factor
    number.content.value *= factor;

	// Make sure that no overflow can occur
	if (number.content.value < INT32_MIN || number.content.value > INT32_MAX)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
		return SCPI_RES_ERR;
	}

	value->value = (int32_t) number.content.value;

	return SCPI_RES_OK;
}


// --------------- Functions for sending numbers as SCPI message

scpi_result_t SCPI_ResultIntValueTypeDefAsDouble(scpi_t *context, INT_VALUE_TypeDef value, double divisor)
{
	int32_t choice = -1;

	if (SCPI_ParamChoice(context, scpi_special_numbers_def, &choice, FALSE))
	{
		switch (choice)
		{
			case SCPI_NUM_MIN:
				SCPI_ResultDouble(context, ((double)value.min) / divisor);
				return SCPI_RES_OK;

			case SCPI_NUM_MAX:
				SCPI_ResultDouble(context, ((double)value.max) / divisor);
				return SCPI_RES_OK;

			default:
				SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
				return SCPI_RES_ERR;
		}
	}

	if (!SCPI_ParamErrorOccurred(context))
	{
		SCPI_ResultDouble(context, ((double)value.value) / divisor);
		return SCPI_RES_OK;
	}

	return SCPI_RES_ERR;
}

scpi_result_t SCPI_ResultIntValueTypeDefAsInt32(scpi_t *context, INT_VALUE_TypeDef value, int32_t divisor)
{
	int32_t choice = -1;

	if (SCPI_ParamChoice(context, scpi_special_numbers_def, &choice, FALSE))
	{
		switch (choice)
		{
			case SCPI_NUM_MIN:
				SCPI_ResultInt32(context, value.min);
				return SCPI_RES_OK;

			case SCPI_NUM_MAX:
				SCPI_ResultInt32(context, value.max);
				return SCPI_RES_OK;

			default:
				SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
				return SCPI_RES_ERR;
		}
	}
	else if (!SCPI_ParamErrorOccurred(context))
	{
		SCPI_ResultInt32(context, value.value / divisor);
		return SCPI_RES_OK;
	}

	return SCPI_RES_ERR;
}


// --------------- Functions for reading and processing from SCPI message


scpi_result_t SCPIUTIL_ParamIntValueTypeDef(scpi_t *context, INT_VALUE_TypeDef (*getter)(),
		API_StatusTypeDef (*setter)(int32_t), bool (*unit_checker)(scpi_number_t *), double factor,
		LEV_STEP_TypeDef *step)
{
	API_StatusTypeDef result;
	INT_VALUE_TypeDef int_value = getter();

	if (SCPI_ParamIntValueTypeDef(context, &int_value, unit_checker, factor, step) != SCPI_RES_OK)
	{
		return SCPI_RES_ERR;
	}

	// Try to set the new value
	result = setter(int_value.value);

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


scpi_result_t SCPIUTIL_ParamChoice(scpi_t *context, const scpi_choice_def_t * options, API_StatusTypeDef (*setter)(int32_t))
{
	int32_t choice;

	if (SCPI_ParamChoice(context, options, &choice, TRUE))
	{
		if (setter(choice) == API_OK)
		{
			return SCPI_RES_OK;
		}
	}

	return SCPI_RES_ERR;
}


scpi_result_t SCPIUTIL_ParamInt32(scpi_t *context, API_StatusTypeDef (*setter)(int32_t))
{
	SCPI_GUARD_RLSTATE(context);

	int32_t setup;
	GET_PARAM_INT32_MANDATORY(&setup);

	if (setter(setup) != API_OK)
	{
		return SCPI_RES_ERR;
	}

	return SCPI_RES_OK;
}



scpi_result_t SCPIUTIL_ParamUInt32(scpi_t *context, API_StatusTypeDef (*setter)(uint32_t))
{
	SCPI_GUARD_RLSTATE(context);

	uint32_t setup;
	GET_PARAM_UINT32_MANDATORY(&setup);

	if (setter(setup) != API_OK)
	{
		return SCPI_RES_ERR;
	}

	return SCPI_RES_OK;
}


scpi_result_t SCPIUTIL_ParamBool(scpi_t *context, API_StatusTypeDef (*setter)(bool))
{
	SCPI_GUARD_RLSTATE(context);

	bool state;
	GET_PARAM_BOOL_MANDATORY(&state);

	// Try to set the new value
	if (setter(state) != API_OK)
	{
		return SCPI_RES_ERR;
	}

	return SCPI_RES_OK;
}


// --------------- Functions for processing and sending choices as SCPI message


scpi_result_t SCPIUTIL_ResultIntValueTypeDefAsInt32(scpi_t *context, INT_VALUE_TypeDef value, int32_t divisor)
{
	int32_t choice = -1;

	if (SCPI_ParamChoice(context, scpi_special_numbers_def, &choice, FALSE))
	{
		switch (choice)
		{
			case SCPI_NUM_MIN:
				SCPI_ResultInt32(context, value.min);
				return SCPI_RES_OK;

			case SCPI_NUM_MAX:
				SCPI_ResultInt32(context, value.max);
				return SCPI_RES_OK;

			default:
				SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
				return SCPI_RES_ERR;
		}
	}
	else if (!SCPI_ParamErrorOccurred(context))
	{
		SCPI_ResultInt32(context, value.value / divisor);
		return SCPI_RES_OK;
	}

	return SCPI_RES_ERR;
}


scpi_result_t SCPIUTIL_ResultMnemonic(scpi_t *context, const scpi_choice_def_t * options, int32_t tag)
{
	const char * text;

	SCPI_ChoiceToName(options, tag, &text);
	SCPI_ResultMnemonic(context, text);
	return SCPI_RES_OK;
}


scpi_result_t SCPIUTIL_ResultUInt32(scpi_t *context, uint32_t value)
{
	SCPI_ResultUInt32(context, value);
	return SCPI_RES_OK;
}


scpi_result_t SCPIUTIL_ResultInt32(scpi_t *context, int32_t value)
{
	SCPI_ResultInt32(context, value);
	return SCPI_RES_OK;
}


scpi_result_t SCPIUTIL_ResultBool(scpi_t *context, bool value)
{
	SCPI_ResultBool(context, value);
	return SCPI_RES_OK;
}


// --------------- Functions for unit checks


bool SCPI_UnitCheckerNone(scpi_number_t *number)
{
	return number->unit == SCPI_UNIT_NONE ||
		number->unit == SCPI_UNIT_UNITLESS;
}


bool SCPI_UnitCheckerOhm(scpi_number_t *number)
{
	return number->unit == SCPI_UNIT_NONE ||
		number->unit == SCPI_UNIT_UNITLESS ||
		number->unit == SCPI_UNIT_OHM;
}


bool SCPI_UnitCheckerSecond(scpi_number_t *number)
{
	return number->unit == SCPI_UNIT_NONE ||
		number->unit == SCPI_UNIT_UNITLESS ||
		number->unit == SCPI_UNIT_SECOND;
}


/* Private functions ---------------------------------------------------------*/

