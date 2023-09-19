/*
 * calibration.h
 *
 *  Created on: 28.10.2022
 *      Author: sebas
 */

#ifndef INC_APPLICATION_CALIBRATION_H_
#define INC_APPLICATION_CALIBRATION_H_

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>

#include "util/api.h"

#include "application/app_params.h"
#include "calibration/cal_data.h"
#include "persistence/persistence.h"
#include "prog_res/prog_res.h"

/* Exported constants --------------------------------------------------------*/

#define CAL_NO_SETUP			-1

#define CAL_SETUPS_PER_MODE		60
#define CAL_SETUPS_TOTAL		(2 * CAL_SETUPS_PER_MODE)

#define CAL_SETUP_2W_START		0
#define CAL_SETUP_4W_START		(CAL_SETUP_2W_START + CAL_SETUPS_PER_MODE)

#define CAL_TOL_DIVISOR			20  	// equals ~5%
#define CAL_TOL_ADD				500  	// equals 500mOhm

/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

int8_t CAL_ConvertToSetup(int8_t decade, int8_t resistor);
int8_t CAL_ConvertToResistor(int8_t setup);
uint8_t CAL_ConvertToDecade(int8_t setup);
int32_t CAL_IdealResistance(int8_t setup);

void CAL_Reset(volatile CALDATA_TypeDef *cal_data);

API_StatusTypeDef CAL_GetValue(volatile CALDATA_TypeDef *cal_data, int8_t setup, int32_t *value);
API_StatusTypeDef CAL_SetValue(volatile CALDATA_TypeDef *cal_data, int8_t setup, uint32_t cal_val);

API_StatusTypeDef CAL_ValidateValueForSetup(uint8_t setup, int32_t cal_val);
API_StatusTypeDef CAL_ValidateAll(volatile CALDATA_TypeDef *cal_data);

/* Private functions ---------------------------------------------------------*/

#endif /* INC_APPLICATION_CALIBRATION_H_ */
