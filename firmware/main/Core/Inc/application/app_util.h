/**
 * @file    app_util.h
 * @author  sebas
 * @date    03.12.2022
 * @brief
 */
#ifndef INC_APPLICATION_APP_UTIL_H_
#define INC_APPLICATION_APP_UTIL_H_

/* Includes ------------------------------------------------------------------*/

#include "application/app_params.h"
#include "util/util.h"
#include "util/api.h"

/* Exported constants --------------------------------------------------------*/

#define APP_UTIL_BBM_DELAY			50

/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

#define INT_VALUE_IN_RANGE(struct_var, value) 	IN_RANGE(struct_var.min, struct_var.max, (value))
#define RETURN_OK_IF_TRUE(expr)  if (expr) return API_OK

/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

API_StatusTypeDef _APP_UTIL_SwitchInput();
API_StatusTypeDef _APP_UTIL_ApplyInput();

API_StatusTypeDef _APP_UTIL_ListCheck();
API_StatusTypeDef _APP_UTIL_ListGetNextDwellTime(int32_t *dwell_time);

bool _APP_UTIL_IoPin1();
bool _APP_UTIL_IoPin2();

/* Private functions ---------------------------------------------------------*/


#endif /* INC_APPLICATION_APP_UTIL_H_ */
