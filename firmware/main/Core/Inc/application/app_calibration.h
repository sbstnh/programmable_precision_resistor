/**
 * @file    app_calibration.h
 * @author  sebas
 * @date    02.01.2023
 * @brief
 */
#ifndef INC_APPLICATION_APP_CALIBRATION_H_
#define INC_APPLICATION_APP_CALIBRATION_H_

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>
#include "application/app_params.h"
#include "util/api.h"
#include "util/util.h"

/* Exported constants --------------------------------------------------------*/

#define APP_CAL_DATE_MAX_LEN		48
#define APP_CAL_TEXT_MAX_LEN		48

/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

API_StatusTypeDef APP_Run_CalibrationApply();

bool APP_Get_CalibrationCalibrated();

uint32_t APP_Get_CalibrationCount();

const char * APP_Get_CalibrationDate();
API_StatusTypeDef APP_Set_CalibrationDate(const char *str);

API_StatusTypeDef APP_Run_CalibrationSave();

bool APP_Get_CalibrationSecure();
API_StatusTypeDef APP_Set_CalibrationSecure(bool secure);

int8_t APP_Get_CalibrationSetup();
API_StatusTypeDef APP_Set_CalibrationSetup(int32_t setup);
API_StatusTypeDef APP_Run_CalibrationSetupUp();
API_StatusTypeDef APP_Run_CalibrationSetupDown();

bool APP_Get_CalibrationState();
API_StatusTypeDef APP_Set_CalibrationState(bool state);

const char * APP_Get_CalibrationString();
API_StatusTypeDef APP_Set_CalibrationString(const char *str);

float APP_Get_CalibrationTemp();
API_StatusTypeDef APP_Set_CalibrationTemp(float temp);

API_StatusTypeDef APP_Get_CalibrationValue(int32_t *value);
API_StatusTypeDef APP_Set_CalibrationValue(int32_t value);

/* Private functions ---------------------------------------------------------*/


#endif /* INC_APPLICATION_APP_CALIBRATION_H_ */
