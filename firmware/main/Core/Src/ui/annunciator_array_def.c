/**
 * @file    led_array_def.c
 * @author  sebas
 * @date    16.01.2023
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "hardware/annunciator_def.h"
#include "ui/annunciator_array_def.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

ANNA_TypeDef ANNA =
{
		._annunciators = ANNS,
		._count = NUMBER_OF_ANNUNCIATORS
};

/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

