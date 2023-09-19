/**
 * @file    app_display.c
 * @author  sebas
 * @date    21.12.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include <string.h>
#include "application/app_display.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

SEC_MODE_TypeDef _APP_Get_DisplaySecondaryModeMax();

/* Exported functions --------------------------------------------------------*/

bool APP_Get_DisplayEnable()
{
	return APP.DISPlay.ENABle;
}

API_StatusTypeDef APP_Set_DisplayEnable(bool enable)
{
	APP.DISPlay.ENABle = enable;
	return API_OK;
}


char *APP_Get_DisplayUserTextData()
{
	return (char *) APP.DISPlay.USER.TEXT.DATA;
}


bool APP_Get_DisplayUserTextState()
{
	return APP.DISPlay.USER.TEXT.STATe;
}

API_StatusTypeDef APP_Set_DisplayUserTextState(bool state)
{
	APP.DISPlay.USER.TEXT.STATe = state;
	return API_OK;
}


API_StatusTypeDef APP_Run_DisplayUserTextClear()
{
	memset((char *)APP.DISPlay.USER.TEXT.DATA, 0, sizeof(APP.DISPlay.USER.TEXT.DATA));
	return API_OK;
}

PRIM_RESolution_TypeDef APP_Get_DisplayPrimaryResolution()
{
	return APP.DISPlay.MAIN.PRIMary.RESolution;
}

UTIL_DigitsTypeDef APP_Get_DisplayPrimaryResolutionAsCounts()
{
	switch (APP.DISPlay.MAIN.PRIMary.RESolution)
	{
		case PRIM_RES_THRee: return UTIL_DIGITS_3_5;
		case PRIM_RES_FOUR: return UTIL_DIGITS_4_5;
		case PRIM_RES_FIVE: return UTIL_DIGITS_5_5;
		case PRIM_RES_SIX: return UTIL_DIGITS_6_5;
	}

	return UTIL_DIGITS_6_5;
}


API_StatusTypeDef APP_Set_DisplayPrimaryResolution(PRIM_RESolution_TypeDef resolution)
{
	if (resolution >= PRIM_RES_THRee && resolution <= PRIM_RES_SIX)
	{
		APP.DISPlay.MAIN.PRIMary.RESolution = resolution;
		return API_OK;
	}

	return API_PARAM_OUT_OF_RANGE;
}


SEC_MODE_TypeDef APP_Get_DisplaySecondaryMode()
{
	return APP.DISPlay.MAIN.SECondary.MODE;
}

API_StatusTypeDef APP_Set_DisplaySecondaryMode(SEC_MODE_TypeDef mode)
{

	if (mode >= SEC_MODE_STATe && mode <= _APP_Get_DisplaySecondaryModeMax())
	{
		APP.DISPlay.MAIN.SECondary.MODE = mode;
		return API_OK;
	}

	return API_PARAM_OUT_OF_RANGE;
}


SEC_MODE_TypeDef _APP_Get_DisplaySecondaryModeMax()
{
	return APP.SOURce.RESistance.MODE == RES_MODE_LIST
			? SEC_MODE_LNUMber
			: SEC_MODE_RESistance;
}


API_StatusTypeDef APP_Run_DisplaySecondaryModeNext()
{
	APP.DISPlay.MAIN.SECondary.MODE++;

	if (APP.DISPlay.MAIN.SECondary.MODE > _APP_Get_DisplaySecondaryModeMax())
	{
		APP.DISPlay.MAIN.SECondary.MODE = SEC_MODE_STATe;
	}

	return API_OK;
}


/* Private functions ---------------------------------------------------------*/

