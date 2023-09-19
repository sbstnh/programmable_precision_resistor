/*
 * sensor.c
 *
 *  Created on: Aug 29, 2021
 *      Author: sebas
 */

/* Includes ------------------------------------------------------------------*/
#include "hardware/adc_channels.h"
#include "stm32g4xx_hal.h"


/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

uint32_t ADC_results[ADC_CHANNELS_NUMBER_OF_CONVERSIONS];

/* External variables --------------------------------------------------------*/

extern ADC_HandleTypeDef hadc1;

/* Exported variables --------------------------------------------------------*/

float ADC_vrefint;


/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void ADC_CHANNELS_Init()
{
	HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*) ADC_results, ADC_CHANNELS_NUMBER_OF_CONVERSIONS);
}

void ADC_CHANNELS_ProcessVRefInt()
{
	ADC_vrefint = (float) (ADC_VREF_INT_OVERSAMP_CORR * ADC_VREF_INT_CHARAC * *VREFINT_CAL_ADDR)
			/ ADC_results[ADC_CHANNELS_ADC1_VREFINT];
}

/* Private functions ---------------------------------------------------------*/
