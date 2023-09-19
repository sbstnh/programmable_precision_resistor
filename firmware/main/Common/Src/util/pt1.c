/*
 * pt1.c
 *
 *  Created on: 20.08.2021
 *      Author: sebas
 */

/* Includes ------------------------------------------------------------------*/

#include "util/pt1.h"
#include <math.h>

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** Initializes a PT1 filter.
 *
 * @param filter		 Zu initialiserende Filter-Struktur.
 * @param K				 Verstärkungsfaktor.
 * @param T				 Zeitkonstante des PT1-Glieds.
 * @param sampling_time	 Samplingzeit, mit der der Filter arbeitet.
 */
void PT1_Init(PT1_TypeDef *filter, float K, float T, float sampling_time)
{
	filter->K = K;
	filter->coefficient = 1 / ((T / sampling_time) + 1);
	filter->output_last_cycle = 0;
}

/** Calculates the output of the PT1 filter.
 *
 * @param	*filter			Pointer to the filter.
 * @param	input			The Next input value.
 * @return	y[n]
 */
float PT1_Process(PT1_TypeDef *filter, float input)
{
	if (isnan(filter->output_last_cycle) && !isnan(input))
	{
		filter->output_last_cycle = 0;
	}
	filter->output_last_cycle = filter->coefficient * (filter->K * input - filter->output_last_cycle)
			+ filter->output_last_cycle;
	return filter->output_last_cycle;
}

/* Private functions ---------------------------------------------------------*/
