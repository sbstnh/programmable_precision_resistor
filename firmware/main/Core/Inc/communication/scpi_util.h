/**
 * @file    scpi_util.h
 * @author  sebas
 * @date    04.12.2022
 * @brief
 */
#ifndef INC_COMMUNICATION_SCPI_UTIL_H_
#define INC_COMMUNICATION_SCPI_UTIL_H_

/* Includes ------------------------------------------------------------------*/

#include "scpi/scpi.h"
#include "application/app_params.h"

/* Exported constants --------------------------------------------------------*/

#define SCPI_OHM_CONVERSION_FACTOR		1000
#define SCPI_DIVISOR_TO_OHM				SCPI_OHM_CONVERSION_FACTOR

#define SCPI_DIVISOR_TO_SECOND			100

/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

#define SCPI_GUARD_CAL_RLSTATE(context) \
	if (SCPI_HandleCalModeAndRLState(context) != SCPI_RES_OK) \
	{ \
		return SCPI_RES_ERR; \
	}

#define SCPI_GUARD_RLSTATE(context) \
	if (SCPI_HandleRLState(context) != SCPI_RES_OK) \
	{ \
		return SCPI_RES_ERR; \
	}


#define GET_PARAM_BOOL_MANDATORY(param) \
	if (!SCPI_ParamBool(context, (param), TRUE)) \
	{ \
		return SCPI_RES_ERR; \
	}

#define GET_PARAM_INT32_MANDATORY(param) \
	if (!SCPI_ParamInt32(context, (param), TRUE)) \
	{ \
		return SCPI_RES_ERR; \
	}

#define GET_PARAM_UINT32_MANDATORY(param) \
	if (!SCPI_ParamUInt32(context, (param), TRUE)) \
	{ \
		return SCPI_RES_ERR; \
	}

#define GET_PARAM_NUMBER_MANDATORY(choices, param) \
	if (!SCPI_ParamNumber(context, (choices), (param), TRUE)) \
	{ \
		return SCPI_RES_ERR; \
	}

#define GET_PARAM_DOUBLE_MANDATORY(param) \
	if (!SCPI_ParamDouble(context, (param), TRUE)) \
	{ \
		return SCPI_RES_ERR; \
	}

#define GET_PARAM_CHARACTERS_MANDATORY(param, len) \
	if (!SCPI_ParamCharacters(context, (param), (len), TRUE)) \
	{ \
		return SCPI_RES_ERR; \
	}

#define RETURN_WITH_ILLEGAL_PARAMETER_VALUE() \
		SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE); \
		return SCPI_RES_ERR;

#define RETURN_WITH_SYSTEM_ERROR() \
		SCPI_ErrorPush(context, SCPI_ERROR_SYSTEM_ERROR); \
		return SCPI_RES_ERR;


#define SET_PARAM_BOOL_TEMPLATE(param) bool par;\
	    if (!SCPI_ParamBool(context, &par, TRUE)) return SCPI_RES_ERR;\
	    param = par;\
	    return SCPI_RES_OK;

#define SET_PARAM_INT32_TEMPLATE(param, min, max) int32_t par;\
	    if (!SCPI_ParamInt32(context, &par, TRUE)) return SCPI_RES_ERR;\
	    par = ((par) < (min)) ? (min) : (((par) > (max)) ? (max) : (par));\
	    param = par;\
	    return SCPI_RES_OK;

#define SET_PARAM_FLOAT_TEMPLATE(param, min, max) float par;\
	    if (!SCPI_ParamFloat(context, &par, TRUE)) return SCPI_RES_ERR;\
	    par = ((par) < (min)) ? (min) : (((par) > (max)) ? (max) : (par));\
	    param = par;\
	    return SCPI_RES_OK;

/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

// --------------- Guard functions

scpi_result_t SCPI_HandleCalModeAndRLState(scpi_t *context);
scpi_result_t SCPI_HandleCalMode(scpi_t *context);
scpi_result_t SCPI_HandleRLState(scpi_t *context);

// --------------- Functions for reading numbers from SCPI message

scpi_result_t SCPI_ParamIntValueTypeDef(scpi_t *context, INT_VALUE_TypeDef *value,
		bool (*unit_checker)(scpi_number_t *), double factor, LEV_STEP_TypeDef *step);


// --------------- Functions for sending numbers as SCPI message

scpi_result_t SCPI_ResultIntValueTypeDefAsDouble(scpi_t *context, INT_VALUE_TypeDef value, double divisor);
scpi_result_t SCPI_ResultIntValueTypeDefAsInt32(scpi_t *context, INT_VALUE_TypeDef value, int32_t divisor);


// --------------- Functions for reading and processing choices from SCPI message

scpi_result_t SCPIUTIL_ParamIntValueTypeDef(scpi_t *context, INT_VALUE_TypeDef (*getter)(),
		API_StatusTypeDef (*setter)(int32_t), bool (*unit_checker)(scpi_number_t *), double factor,
		LEV_STEP_TypeDef *step);

scpi_result_t SCPIUTIL_ParamChoice(scpi_t *context, const scpi_choice_def_t * options, API_StatusTypeDef (*setter)(int32_t));

scpi_result_t SCPIUTIL_ParamInt32(scpi_t *context, API_StatusTypeDef (*setter)(int32_t));

scpi_result_t SCPIUTIL_ParamUInt32(scpi_t *context, API_StatusTypeDef (*setter)(uint32_t));

scpi_result_t SCPIUTIL_ParamBool(scpi_t *context, API_StatusTypeDef (*setter)(bool));


// --------------- Functions for processing and sending choices as SCPI message

scpi_result_t SCPIUTIL_ResultIntValueTypeDefAsInt32(scpi_t *context, INT_VALUE_TypeDef value, int32_t divisor);

scpi_result_t SCPIUTIL_ResultMnemonic(scpi_t *context, const scpi_choice_def_t * options, int32_t tag);

scpi_result_t SCPIUTIL_ResultInt32(scpi_t *context, int32_t value);

scpi_result_t SCPIUTIL_ResultUInt32(scpi_t *context, uint32_t value);

scpi_result_t SCPIUTIL_ResultBool(scpi_t *context, bool value);


// --------------- Functions for unit checks

bool SCPI_UnitCheckerNone(scpi_number_t *number);
bool SCPI_UnitCheckerOhm(scpi_number_t *number);
bool SCPI_UnitCheckerSecond(scpi_number_t *number);


/* Private functions ---------------------------------------------------------*/


#endif /* INC_COMMUNICATION_SCPI_UTIL_H_ */
