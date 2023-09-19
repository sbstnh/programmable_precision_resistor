/**
 * @file    led_def.c
 * @author  sebas
 * @date    Jan 15, 2023
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include <hardware/annunciator_def.h>
#include "util/util.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

ANN_TypeDef ANNS[NUMBER_OF_ANNUNCIATORS] =
{
		// REMOTE
		{ .tag_r = 0, .tag_g = 1 },

		// ENTER
		{ .tag_r = 4, .tag_g = 5 },

		// INPUT
		{ .tag_r = 11, .tag_g = 10 },

		// UP
		{ .tag_r = 8, .tag_g = 9 },

		// DOWN
		{ .tag_r = 6, .tag_g = 7 },
};

/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

