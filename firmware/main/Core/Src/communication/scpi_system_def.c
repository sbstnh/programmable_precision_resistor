/**
 * @file    scpi_system_def.c
 * @author  sebas
 * @date    11.11.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "communication/scpi_system_def.h"
#include "communication/scpi_util.h"

#include "application/app_init.h"
#include "application/app_memory.h"
#include "application/app_params.h"
#include "application/app_system.h"

#include "persistence/persistence.h"

#include "hardware/ui_interface_def.h"

/* Private defines -----------------------------------------------------------*/

#define SCPI_CMD_SYSTEM_BEEP_DEFAULT_FREQUENCY		4000
#define SCPI_CMD_SYSTEM_BEEP_MIN_FREQUENCY			100
#define SCPI_CMD_SYSTEM_BEEP_MAX_FREQUENCY			8000

#define SCPI_CMD_SYSTEM_BEEP_DEFAULT_VOLUME			192

#define SCPI_CMD_SYSTEM_BEEP_DEFAULT_BEEP_DURATION	70
#define SCPI_CMD_SYSTEM_BEEP_MAX_BEEP_DURATION		5000

/* Private typedef -----------------------------------------------------------*/

scpi_choice_def_t SCPI_SYST_COMM_RLSTate[] =
{
		{ "LOCal",  COMM_RLST_LOCal },
		{ "MIXed",  COMM_RLST_MIXed },
		{ "REMote", COMM_RLST_REMote },
		{ "RWLock", COMM_RLST_RWLock },
		SCPI_CHOICE_LIST_END
};

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

scpi_result_t SCPI_CMD_SYST_BEEP_IMMediate(scpi_t *context)
{
	SCPI_GUARD_RLSTATE(context);

	int32_t frequency;
	int32_t duration;

	if (!SCPI_ParamInt32(context, &frequency, FALSE))
	{
		frequency = SCPI_CMD_SYSTEM_BEEP_DEFAULT_FREQUENCY;
		duration = SCPI_CMD_SYSTEM_BEEP_DEFAULT_BEEP_DURATION;
	}
	else
	{
		if (frequency < SCPI_CMD_SYSTEM_BEEP_MIN_FREQUENCY || frequency > SCPI_CMD_SYSTEM_BEEP_MAX_FREQUENCY)
		{
			RETURN_WITH_ILLEGAL_PARAMETER_VALUE();
		}

		if (!SCPI_ParamInt32(context, &duration, FALSE))
		{
			duration = SCPI_CMD_SYSTEM_BEEP_DEFAULT_BEEP_DURATION;
		}
		else if (duration < 0 || duration > SCPI_CMD_SYSTEM_BEEP_MAX_BEEP_DURATION)
		{
			RETURN_WITH_ILLEGAL_PARAMETER_VALUE();
		}
	}

	if (UIIF_Beep(&UIIF, frequency, SCPI_CMD_SYSTEM_BEEP_DEFAULT_VOLUME, duration) != API_OK)
	{
		RETURN_WITH_SYSTEM_ERROR();
	}

	return SCPI_RES_OK;
}

scpi_result_t SCPI_CMD_SYST_BEEP_STATe(scpi_t *context)
{
	SCPI_GUARD_RLSTATE(context);
	return SCPIUTIL_ParamBool(context, APP_Set_SystemBeeperState);
}

scpi_result_t SCPI_CMD_SYST_BEEP_STATe_Q(scpi_t *context)
{
	SCPI_GUARD_RLSTATE(context);
	return SCPIUTIL_ResultBool(context, APP_Get_SystemBeeperState());
}


scpi_result_t SCPI_CMD_SYST_COMM_RLSTate(scpi_t *context)
{
	return SCPIUTIL_ParamChoice(
			context,
			SCPI_SYST_COMM_RLSTate,
			(API_StatusTypeDef (*)(int32_t)) APP_Run_SystemCommunicateRLState);
}

scpi_result_t SCPI_CMD_SYST_COMM_RLSTate_Q(scpi_t *context)
{
	return SCPIUTIL_ResultMnemonic(
			context,
			SCPI_SYST_COMM_RLSTate,
			APP_Get_SystemCommunicateRLState());
}


scpi_result_t SCPI_CMD_SYST_DEF_IMMediate(scpi_t *context)
{
	if (APP_Run_SystemDefaultImmediate() == API_OK)
	{
		return SCPI_RES_OK;
	}

	return SCPI_RES_ERR;
}


scpi_result_t SCPI_CMD_SYST_FVER_MAIN_Q(scpi_t *context)
{
	SCPI_GUARD_RLSTATE(context);

	const char *str = APP_Get_SystemFirmwareVersionMainboard();
	SCPI_ResultCharacters(context, str, strnlen(str, APP_SYS_FIRM_VERS_MAX_LEN));
	return SCPI_RES_OK;
}


scpi_result_t SCPI_CMD_SYST_FVER_UI_Q(scpi_t *context)
{
	SCPI_GUARD_RLSTATE(context);

	const char *str = APP_Get_SystemFirmwareVersionUI();
	SCPI_ResultCharacters(context, str, strnlen(str, APP_SYS_FIRM_VERS_MAX_LEN));
	return SCPI_RES_OK;
}


scpi_result_t SCPI_CMD_SYST_LOCal(scpi_t *context)
{
	if (APP_Run_SystemCommunicateRLState(COMM_RLST_LOCal) == API_OK)
	{
		return SCPI_RES_OK;
	}

	return SCPI_RES_ERR;
}


scpi_result_t SCPI_CMD_SYST_MIXed(scpi_t *context)
{
	if (APP_Run_SystemCommunicateRLState(COMM_RLST_MIXed) == API_OK)
	{
		return SCPI_RES_OK;
	}

	return SCPI_RES_ERR;
}


scpi_result_t SCPI_CMD_SYST_REMote(scpi_t *context)
{
	if (APP_Run_SystemCommunicateRLState(COMM_RLST_REMote) == API_OK)
	{
		return SCPI_RES_OK;
	}

	return SCPI_RES_ERR;
}


scpi_result_t SCPI_CMD_SYST_RWLock(scpi_t *context)
{
	if (APP_Run_SystemCommunicateRLState(COMM_RLST_RWLock) == API_OK)
	{
		return SCPI_RES_OK;
	}

	return SCPI_RES_ERR;
}

scpi_result_t SCPI_CMD_SYST_SEC_IMMediate(scpi_t *context)
{
	if (APP_Run_SystemSecurityImmediate() == API_OK)
	{
		return SCPI_RES_OK;
	}

	return SCPI_RES_ERR;
}

/* Private functions ---------------------------------------------------------*/

