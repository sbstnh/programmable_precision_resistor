/**
 * @file    scpi_source_digital_def.c
 * @author  sebas
 * @date    04.12.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "communication/scpi_source_digital_def.h"
#include "communication/scpi_util.h"
#include "application/app_source.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/

scpi_choice_def_t SCPI_SOUR_DIG_PIN_FUNCtion[] =
{
		{ "DINPut", PIN_FUNC_DINPut },
		{ "INHibit",  PIN_FUNC_INHibit },
		{ "TINPut", PIN_FUNC_TINPut },
		{ "DEFault", PIN_FUNC_DINPut },
		SCPI_CHOICE_LIST_END
};


scpi_choice_def_t SCPI_SOUR_DIG_PIN_POLarity[] =
{
		{ "POSitive", PIN_POL_POSitive },
		{ "NEGative",  PIN_POL_NEGative },
		{ "DEFault", PIN_POL_POSitive },
		SCPI_CHOICE_LIST_END
};

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

scpi_result_t SCPI_CMD_SOUR_DIG_PIN1_DATA_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ResultBool(context, APP_Get_SourceDigitalPinData(SOUR_DIG_PIN1));
}


scpi_result_t SCPI_CMD_SOUR_DIG_PIN2_DATA_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ResultBool(context, APP_Get_SourceDigitalPinData(SOUR_DIG_PIN2));
}


scpi_result_t SCPI_CMD_SOUR_DIG_PIN1_FUNCtion(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	int32_t choice;

	if (SCPI_ParamChoice(context, SCPI_SOUR_DIG_PIN_FUNCtion, &choice, TRUE))
	{
		if (APP_Set_SourceDigitalPinFunction(SOUR_DIG_PIN1, (PIN_POLarity_TypeDef) choice) == API_OK)
		{
			return SCPI_RES_OK;
		}
	}

	return SCPI_RES_ERR;
}

scpi_result_t SCPI_CMD_SOUR_DIG_PIN1_FUNCtion_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ResultMnemonic(context, SCPI_SOUR_DIG_PIN_FUNCtion, APP_Get_SourceDigitalPinFunction(SOUR_DIG_PIN1));
}


scpi_result_t SCPI_CMD_SOUR_DIG_PIN2_FUNCtion(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	int32_t choice;

	if (SCPI_ParamChoice(context, SCPI_SOUR_DIG_PIN_FUNCtion, &choice, TRUE))
	{
		if (APP_Set_SourceDigitalPinFunction(SOUR_DIG_PIN2, (PIN_POLarity_TypeDef) choice) == API_OK)
		{
			return SCPI_RES_OK;
		}
	}

	return SCPI_RES_ERR;
}

scpi_result_t SCPI_CMD_SOUR_DIG_PIN2_FUNCtion_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ResultMnemonic(context, SCPI_SOUR_DIG_PIN_FUNCtion, APP_Get_SourceDigitalPinFunction(SOUR_DIG_PIN2));
}


scpi_result_t SCPI_CMD_SOUR_DIG_PIN1_POLarity(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	int32_t choice;

	if (SCPI_ParamChoice(context, SCPI_SOUR_DIG_PIN_POLarity, &choice, TRUE))
	{
		if (APP_Set_SourceDigitalPinPolarity(SOUR_DIG_PIN1, (PIN_POLarity_TypeDef) choice) == API_OK)
		{
			return SCPI_RES_OK;
		}
	}

	return SCPI_RES_ERR;
}

scpi_result_t SCPI_CMD_SOUR_DIG_PIN1_POLarity_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ResultMnemonic(context, SCPI_SOUR_DIG_PIN_POLarity, APP_Get_SourceDigitalPinPolarity(SOUR_DIG_PIN1));
}


scpi_result_t SCPI_CMD_SOUR_DIG_PIN2_POLarity(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	int32_t choice;

	if (SCPI_ParamChoice(context, SCPI_SOUR_DIG_PIN_POLarity, &choice, TRUE))
	{
		if (APP_Set_SourceDigitalPinPolarity(SOUR_DIG_PIN2, (PIN_POLarity_TypeDef) choice) == API_OK)
		{
			return SCPI_RES_OK;
		}
	}

	return SCPI_RES_ERR;
}

scpi_result_t SCPI_CMD_SOUR_DIG_PIN2_POLarity_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);
	return SCPIUTIL_ResultMnemonic(context, SCPI_SOUR_DIG_PIN_POLarity, APP_Get_SourceDigitalPinPolarity(SOUR_DIG_PIN2));
}


/* Private functions ---------------------------------------------------------*/

