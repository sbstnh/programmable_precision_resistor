/**
 * @file    app.c
 * @author  sebas
 * @date    Nov 12, 2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>
#include <string.h>

#include "application/app_params.h"
#include "util/util.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

volatile APP_ParamTypeDef APP;

/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/


API_StatusTypeDef APP_UpdateIntValue(volatile INT_VALUE_TypeDef *int_value, int32_t value)
{
	if (!IN_RANGE(int_value->min, int_value->max, value))
	{
		return API_ERROR;
	}

	int_value->value = value;

	return API_OK;
}

/* Private functions ---------------------------------------------------------*/

