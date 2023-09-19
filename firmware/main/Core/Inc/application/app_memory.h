/**
 * @file    app_memory.h
 * @author  sebas
 * @date    19.01.2023
 * @brief
 */
#ifndef INC_APPLICATION_APP_MEMORY_H_
#define INC_APPLICATION_APP_MEMORY_H_

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>
#include "application/app_params.h"
#include "util/api.h"
#include "util/util.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

API_StatusTypeDef APP_Run_MemoryReadCalibration();
API_StatusTypeDef APP_Run_MemorySaveCalibration();

API_StatusTypeDef APP_Run_MemoryReadInstData();
API_StatusTypeDef APP_Run_MemorySaveInstData();

API_StatusTypeDef APP_Run_MemoryRecall(uint8_t index, bool default_if_error);
API_StatusTypeDef APP_Run_MemorySave(uint8_t index);

/* Private functions ---------------------------------------------------------*/


#endif /* INC_APPLICATION_APP_MEMORY_H_ */
