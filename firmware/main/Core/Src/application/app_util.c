/**
 * @file    app_util.c
 * @author  sebas
 * @date    03.12.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "application/app_util.h"

#include "cmsis_os2.h"

#include "hardware/relay_control.h"
#include "hardware/stp16cp05_def.h"

#include "stm32g4xx_hal.h"
#include "hardware/input_def.h"

#include "prog_res/prog_res_def.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/


API_StatusTypeDef _APP_UTIL_ApplyInput()
{
	API_StatusTypeDef status;

	// Limit value, if limit is active
	if (APP.SOURce.RESistance.LIMit.STATe)
	{
		APP.SOURce.RESistance.LEVel.IMMediate.AMPLitude.value = LIM(
				APP.SOURce.RESistance.LIMit.LOWer.value,
				APP.SOURce.RESistance.LIMit.UPPer.value,
				APP.SOURce.RESistance.LEVel.IMMediate.AMPLitude.value
		);
	}

	// Else Calculate and set immediate value
	status = PRES_SetSetpoint(&progres,
					 APP.SOURce.RESistance.LEVel.IMMediate.AMPLitude.value,
					 (CAL_Mode_TypeDef) APP.SOURce.MODE);

	if (status != API_OK)
	{
		return status;
	}

	// Calculate limit values
	APP.SOURce.CURRent.LEVel.IMMediate.AMPLitude.value = PRES_CalcIMax(&progres);
	APP.SOURce.VOLTage.LEVel.IMMediate.AMPLitude.value = PRES_CalcUMax(&progres);
	APP.SOURce.POWer.LEVel.IMMediate.AMPLitude.value = PRES_CalcPMax(&progres);

	// Check whether input has to be switched off
	if (!APP.INPut.STATe || APP.INPut.INHibit.STATe)
	{
		status = PRES_SwitchOff(&progres);
	}
	else
	{
		// Now do the switching
		switch (APP.SOURce.SWITching.MODE)
		{
			default:
			case SOUR_SWIT_AUTO:
				status = PRES_SwitchSimple(&progres, APP.SOURce.SWITching._use_bypass);
				break;

			case SOUR_SWIT_BBMake:
				status = PRES_SwitchOff(&progres);
				if (status != API_OK)
				{
					return status;
				}

				status = RLYCTRL_Update(&STP);
				if (status != API_OK)
				{
					return status;
				}

				osDelay(APP_UTIL_BBM_DELAY);

				status = PRES_SwitchSimple(&progres, APP.SOURce.SWITching._use_bypass);
				break;
			// TODO: Implement other switching strategies
		}
	}

	if (status != API_OK)
	{
		return status;
	}

	return RLYCTRL_Update(&STP);
}


API_StatusTypeDef _APP_UTIL_ListCheck()
{
	// Make sure that both the RES.LEV list and RES.DWEL are set up correctly
	if (APP.SOURce.LIST.STEP == LIST_STEP_AUTO || APP.SOURce.LIST.STEP == LIST_STEP_ONCE)
	{
		// Here we have to check the DWELl length
		if (APP.SOURce.LIST.RESistance.DWELl.length.value != 1
			&& APP.SOURce.LIST.RESistance.DWELl.length.value != APP.SOURce.LIST.RESistance.LEVel.length.value)
		{
			return API_ERROR;
		}
	}
	return API_OK;
}


API_StatusTypeDef _APP_UTIL_ListGetNextDwellTime(int32_t *dwell_time)
{
	if (APP.SOURce.LIST.RESistance.DWELl.length.value == 1)
	{
		*dwell_time = APP.SOURce.LIST.RESistance.DWELl.values[0];
		return API_OK;
	}
	else if (APP.SOURce.LIST.RESistance.DWELl.length.value >= APP.SOURce.LIST.RESistance.LEVel.length.value)
	{
		*dwell_time = APP.SOURce.LIST.RESistance.DWELl.values[APP.SOURce.LIST.RESistance.INDex.value];
		return API_OK;
	}
	*dwell_time = APP.SOURce.LIST.RESistance.DWELl.values[APP.SOURce.LIST.RESistance.DWELl.length.value - 1];
	return API_ERROR;
}

bool _APP_UTIL_IoPin1()
{
	bool input = HAL_GPIO_ReadPin(IN_EXTI1.GPIOx, IN_EXTI1.pin);
	return APP.SOURce.DIGital.PIN[SOUR_DIG_PIN1].POLarity == PIN_POL_POSitive
			? input
			: !input;
}


bool _APP_UTIL_IoPin2()
{
	bool input = HAL_GPIO_ReadPin(IN_EXTI2.GPIOx, IN_EXTI2.pin);
	return APP.SOURce.DIGital.PIN[SOUR_DIG_PIN2].POLarity == PIN_POL_POSitive
			? input
			: !input;
}

/* Private functions ---------------------------------------------------------*/

