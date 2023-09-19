/**
 * @file    scpi_source_list_def.c
 * @author  sebas
 * @date    04.12.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "communication/scpi_source_list_def.h"
#include "communication/scpi_util.h"
#include "communication/scpi_util.h"
#include "application/app_source.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/

scpi_choice_def_t SCPI_SOUR_LIST_STARt[] =
{
		{ "AUTO",    LIST_START_AUTO },
		{ "TRIGger", LIST_START_TRIGger },
		{ "DEFault", LIST_START_TRIGger },
		SCPI_CHOICE_LIST_END
};

scpi_choice_def_t SCPI_SOUR_LIST_STEP[] =
{
		{ "AUTO",    LIST_STEP_AUTO },
		{ "TRIGger", LIST_STEP_TRIGger },
		{ "ONCE",    LIST_STEP_ONCE },
		{ "DEFault", LIST_STEP_AUTO },
		SCPI_CHOICE_LIST_END
};

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/


scpi_result_t SCPI_CMD_SOUR_LIST_RES_LEVel(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	int32_t index;
	INT_VALUE_TypeDef level;

	// Determine index
	GET_PARAM_INT32_MANDATORY(&index);

	// Determine value
	if (SCPI_ParamIntValueTypeDef(context, &level, SCPI_UnitCheckerOhm, SCPI_DIVISOR_TO_OHM, NULL) != SCPI_RES_OK)
	{
		return SCPI_RES_ERR;
	}

	// Try to set the new value
	if (APP_Set_SourceListResistanceLevelValues(index, level.value) != API_OK)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
		return SCPI_RES_ERR;
	}

	return SCPI_RES_OK;
}

scpi_result_t SCPI_CMD_SOUR_LIST_RES_LEVel_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	int32_t index;
	int32_t value;

	// Determine index
	GET_PARAM_INT32_MANDATORY(&index);

	if (APP_Get_SourceListResistanceLevelValues(index, &value) != API_OK)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
		return SCPI_RES_ERR;
	}

	SCPI_ResultDouble(context, ((double) value) / SCPI_DIVISOR_TO_OHM);

	return SCPI_RES_OK;
}


scpi_result_t SCPI_CMD_SOUR_LIST_RES_POINts(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ParamInt32(context, APP_Set_SourceListResistanceLength);
}

scpi_result_t SCPI_CMD_SOUR_LIST_RES_POINts_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ResultIntValueTypeDefAsInt32(context, APP_Get_SourceListResistanceLength(), 1);
}


scpi_result_t SCPI_CMD_SOUR_LIST_RES_INDex_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ResultIntValueTypeDefAsInt32(context, APP_Get_SourceListResistanceIndex(), 1);
}


scpi_result_t SCPI_CMD_SOUR_LIST_RES_RUN_NUMBer_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ResultIntValueTypeDefAsInt32(context, APP_Get_SourceListResistanceRunNumber(), 1);
}


scpi_result_t SCPI_CMD_SOUR_LIST_RES_RUN_COUNt(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	INT_VALUE_TypeDef count = APP_Get_SourceListResistanceRunCount();

	if (SCPI_ParamIntValueTypeDef(context, &count, SCPI_UnitCheckerNone, 1, NULL) != SCPI_RES_OK)
	{
		return SCPI_RES_ERR;
	}

	// Try to set the new value
	if (APP_Set_SourceListResistanceRunCount(count.value) != API_OK)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
		return SCPI_RES_ERR;
	}

	return SCPI_RES_OK;
}

scpi_result_t SCPI_CMD_SOUR_LIST_RES_RUN_COUNt_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ResultIntValueTypeDefAsInt32(context, APP_Get_SourceListResistanceRunCount(), 1);
}


scpi_result_t SCPI_CMD_SOUR_LIST_RES_DWELl(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	int32_t index;
	INT_VALUE_TypeDef level;

	// Determine index
	GET_PARAM_INT32_MANDATORY(&index);

	// Determine value
	if (SCPI_ParamIntValueTypeDef(context, &level, SCPI_UnitCheckerSecond, SCPI_DIVISOR_TO_SECOND, NULL) != SCPI_RES_OK)
	{
		return SCPI_RES_ERR;
	}

	// Try to set the new value
	if (APP_Set_SourceListResistanceDwellValues(index, level.value) != API_OK)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
		return SCPI_RES_ERR;
	}

	return SCPI_RES_OK;
}

scpi_result_t SCPI_CMD_SOUR_LIST_RES_DWELl_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	int32_t index;
	int32_t value;

	// Determine index
	GET_PARAM_INT32_MANDATORY(&index);

	if (APP_Get_SourceListResistanceDwellValues(index, &value) != API_OK)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
		return SCPI_RES_ERR;
	}

	SCPI_ResultDouble(context, ((double) value) / SCPI_DIVISOR_TO_SECOND);

	return SCPI_RES_OK;
}


scpi_result_t SCPI_CMD_SOUR_LIST_RES_DWEL_POINts(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ParamInt32(context, APP_Set_SourceListResistanceDwellLength);
}

scpi_result_t SCPI_CMD_SOUR_LIST_RES_DWEL_POINts_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPI_ResultIntValueTypeDefAsInt32(context, APP_Get_SourceListResistanceDwellLength(), 1);
}


scpi_result_t SCPI_CMD_SOUR_LIST_STAR_INPut(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ParamBool(context, APP_Set_SourceListStartInput);
}

scpi_result_t SCPI_CMD_SOUR_LIST_STAR_INPut_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ResultBool(context, APP_Get_SourceListStartInput());
}


scpi_result_t SCPI_CMD_SOUR_LIST_STAR_MODE(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ParamChoice(
			context,
			SCPI_SOUR_LIST_STARt,
			(API_StatusTypeDef (*)(int32_t)) APP_Set_SourceListStartMode);
}

scpi_result_t SCPI_CMD_SOUR_LIST_STAR_MODE_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ResultMnemonic(context, SCPI_SOUR_LIST_STARt, APP_Get_SourceListStartMode());
}


scpi_result_t SCPI_CMD_SOUR_LIST_STEP(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ParamChoice(
			context,
			SCPI_SOUR_LIST_STEP,
			(API_StatusTypeDef (*)(int32_t)) APP_Set_SourceListStep);
}

scpi_result_t SCPI_CMD_SOUR_LIST_STEP_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ResultMnemonic(context, SCPI_SOUR_LIST_STEP, APP_Get_SourceListStep());
}


scpi_result_t SCPI_CMD_SOUR_LIST_TERM_INPut(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ParamBool(context, APP_Set_SourceListTerminateInput);
}

scpi_result_t SCPI_CMD_SOUR_LIST_TERM_INPut_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ResultBool(context, APP_Get_SourceListTerminateInput());
}


scpi_result_t SCPI_CMD_SOUR_LIST_TERM_LAST(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ParamBool(context, APP_Set_SourceListTerminateLast);
}

scpi_result_t SCPI_CMD_SOUR_LIST_TERM_LAST_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ResultBool(context, APP_Get_SourceListTerminateLast());
}

/* Private functions ---------------------------------------------------------*/

