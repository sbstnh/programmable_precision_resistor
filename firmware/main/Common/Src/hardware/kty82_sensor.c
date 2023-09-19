/*
 * kty82_sensor.c
 *
 *  Created on: 04.09.2021
 *      Author: sebas
 */

/* Includes ------------------------------------------------------------------*/

#include "hardware/kty82_sensor.h"

#include <math.h>

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void KTY82_Init(KTY82_TypeDef *kty)
{
	kty->temperature = 0;

	kty->minimum = NAN;
	kty->maximum = NAN;
	kty->average = NAN;

	PT1_Init(&kty->_pt1, 1, 1.0, 0.01);
}

void KTY82_ResetStats(KTY82_TypeDef *kty)
{
	kty->minimum = NAN;
	kty->maximum = NAN;
	kty->average = NAN;
}

float KTY82_Process(KTY82_TypeDef *kty)
{
	kty->temperature = (float) *kty->adc_register * kty->gradient + kty->intercept;

	if (isnan(kty->minimum) || kty->temperature < kty->minimum)
	{
		kty->minimum = kty->temperature;
	}
	if (isnan(kty->maximum) || kty->temperature > kty->maximum)
	{
		kty->maximum = kty->temperature;
	}
	if (isnan(kty->average))
	{
		kty->average = kty->temperature;
	}
	kty->average = PT1_Process(&kty->_pt1, kty->temperature);

	return kty->temperature;
}

/* Private functions ---------------------------------------------------------*/
