/**
 * @file    kty82_sensor_def.h
 * @author  sebas
 * @date    04.09.2021
 * @brief
 */

#ifndef INC_HARDWARE_KTY82_SENSOR_DEF_H_
#define INC_HARDWARE_KTY82_SENSOR_DEF_H_

/* Includes ------------------------------------------------------------------*/

#include "hardware/kty82_sensor.h"

/* Exported constants --------------------------------------------------------*/

#define KTY82_SENSORS	2

#define KTY82_TEMP1		0
#define KTY82_TEMP2		1

/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

extern KTY82_TypeDef KTY82_TEMP[KTY82_SENSORS];

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#endif /* INC_HARDWARE_KTY82_SENSOR_DEF_H_ */
