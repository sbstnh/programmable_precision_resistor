/**
 * @file    kty82_sensor.h
 * @author  Sebastian Harnisch
 * @date    04.09.2021
 * @brief   Convert ADC values for KTY82 into temperatures
 */

#ifndef INC_HARDWARE_KTY82_SENSOR_H_
#define INC_HARDWARE_KTY82_SENSOR_H_

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include "util/pt1.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

typedef struct
{
	volatile uint32_t *adc_register;

	float gradient;					//!< Gradient of inverse linearized transfer function
	float intercept;				//!< y-intercept of inverse linearized transfer function

	volatile float temperature;		//!< Temperature as measured and calculated by this module

	volatile float minimum;
	volatile float maximum;
	volatile float average;

	PT1_TypeDef _pt1;
} KTY82_TypeDef;

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void KTY82_Init(KTY82_TypeDef *kty);
void KTY82_ResetStats(KTY82_TypeDef *kty);
float KTY82_Process(KTY82_TypeDef *kty);

/* Private functions ---------------------------------------------------------*/

#endif /* INC_HARDWARE_KTY82_SENSOR_H_ */
