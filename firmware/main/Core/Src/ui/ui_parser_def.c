/**
 * @file    parser_def.c
 * @author  sebas
 * @date    21.12.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "ui/ui_parser_def.h"

#include "application/app_params.h"
#include "calibration/calibration.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

UIPAR_TypeDef UIPAR_RESISTANCE =
{
		.min = 0,
		.max = 1100000000,
		.max_digits = 10,
		.max_decimal_places = 9,
		.target_decimal_places = 3
};

UIPAR_TypeDef UIPAR_UINT =
{
		.min = 0,
		.max = UINT32_MAX,
		.max_digits = 10,
		.max_decimal_places = 9,
		.target_decimal_places = 0
};

UIPAR_TypeDef UIPAR_INT =
{
		.min = INT32_MIN,
		.max = INT32_MAX,
		.max_digits = 10,
		.max_decimal_places = 9,
		.target_decimal_places = 0
};

UIPAR_TypeDef UIPAR_TIME =
{
		.min = 0,
		.max = INT32_MAX,
		.max_digits = 10,
		.max_decimal_places = 2,
		.target_decimal_places = 2
};

UIPAR_TypeDef UIPAR_CAL_SETUP =
{
		.min = CAL_NO_SETUP,
		.max = CAL_SETUPS_TOTAL,
		.max_digits = 3,
		.max_decimal_places = 0,
		.target_decimal_places = 0
};

UIPAR_TypeDef UIPAR_SAVRCL =
{
		.min = 0,
		.max = 9,
		.max_digits = 1,
		.max_decimal_places = 0,
		.target_decimal_places = 0
};

UIPAR_TypeDef UIPAR_LIST =
{
		.min = 0,
		.max = SOUR_LIST_LENGTH - 1,
		.max_digits = 10,
		.max_decimal_places = 9,
		.target_decimal_places = 0
};

/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

