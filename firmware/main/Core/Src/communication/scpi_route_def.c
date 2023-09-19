/**
 * @file    scpi_route_def.c
 * @author  sebas
 * @date    11.11.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "communication/scpi_route_def.h"
#include "communication/scpi_util.h"

#include "hardware/stp16cp05_def.h"
#include "hardware/relay_control.h"
#include "hardware/relay_def.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

scpi_result_t SCPI_CMD_ROUT_REL_OPEN(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	int32_t relay_number;

	GET_PARAM_INT32_MANDATORY(&relay_number);

	if (relay_number < 0 || relay_number >= RLY_COUNT)
	{
		RETURN_WITH_ILLEGAL_PARAMETER_VALUE();
	}

	RLY_Open(&relays[relay_number]);
	RLYCTRL_Update(&STP);

	return SCPI_RES_OK;
}

scpi_result_t SCPI_CMD_ROUT_REL_CLOSe(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	int32_t relay_number;

	GET_PARAM_INT32_MANDATORY(&relay_number);

	if (relay_number < 0 || relay_number >= RLY_COUNT)
	{
		RETURN_WITH_ILLEGAL_PARAMETER_VALUE();
	}

	RLY_Close(&relays[relay_number]);
	RLYCTRL_Update(&STP);

	return SCPI_RES_OK;
}

scpi_result_t SCPI_CMD_ROUT_REL_STATe(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	int32_t relay_number;
	bool state;

	GET_PARAM_INT32_MANDATORY(&relay_number);
	GET_PARAM_BOOL_MANDATORY(&state);

	if (relay_number < 0 || relay_number >= RLY_COUNT)
	{
		RETURN_WITH_ILLEGAL_PARAMETER_VALUE();
	}

	RLY_SetState(&relays[relay_number], state);
	RLYCTRL_Update(&STP);

	return SCPI_RES_OK;
}


scpi_result_t SCPI_CMD_ROUT_REL_STATe_Q(scpi_t *context)
{
	SCPI_GUARD_CAL_RLSTATE(context);

	int32_t relay_number;

	GET_PARAM_INT32_MANDATORY(&relay_number);

	if (relay_number < 0 || relay_number >= RLY_COUNT)
	{
		RETURN_WITH_ILLEGAL_PARAMETER_VALUE();
	}

	SCPI_ResultBool(context, RLYCTRL_GetState(&relays[relay_number], &STP));

	return SCPI_RES_OK;
}

/* Private functions ---------------------------------------------------------*/

