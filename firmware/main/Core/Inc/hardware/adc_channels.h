/*
 * sensor.h
 *
 *  Created on: Aug 29, 2021
 *      Author: sebas
 */

#ifndef INC_HARDWARE_ADC_CHANNELS_H_
#define INC_HARDWARE_ADC_CHANNELS_H_

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>

/* Exported constants --------------------------------------------------------*/

#define ADC_CHANNELS_NUMBER_OF_CONVERSIONS	8
#define ADC_CHANNELS_NATIVE_RESOLUTION		12
#define ADC_CHANNELS_RESOLUTION				16
#define ADC_CHANNELS_MAX_VALUE				(1UL << ADC_CHANNELS_RESOLUTION)

#define ADC_CHANNELS_ADC1_VREFINT			0
#define ADC_CHANNELS_ADC1_INTERNAL_TEMP		1
#define ADC_CHANNELS_ADC1_TEMP1				2
#define ADC_CHANNELS_ADC1_TEMP2				3

#define ADC_VREF_INT_CHARAC					3.0
#define ADC_VREF_INT_OVERSAMP_CORR			16

/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

extern uint32_t ADC_results[ADC_CHANNELS_NUMBER_OF_CONVERSIONS];
extern float ADC_vrefint;

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void ADC_CHANNELS_Init();
void ADC_CHANNELS_ProcessVRefInt();

/* Private functions ---------------------------------------------------------*/

#endif /* INC_HARDWARE_ADC_CHANNELS_H_ */
