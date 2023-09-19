/**
 * @file    kty82_sensor_def.c
 * @author  sebas
 * @date    04.09.2021
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "hardware/kty82_sensor.h"
#include "hardware/adc_channels.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

KTY82_TypeDef KTY82_TEMP[] =
{
		{
				.adc_register = &ADC_results[ADC_CHANNELS_ADC1_TEMP1],
				.gradient = 0.007744595,
				.intercept = -216.6866678
		},
		{
				.adc_register = &ADC_results[ADC_CHANNELS_ADC1_TEMP2],
				.gradient = 0.007744595,
				.intercept = -216.6866678
		}
};

/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
