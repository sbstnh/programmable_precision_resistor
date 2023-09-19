/**
 * @file    app_cycle.h
 * @author  sebas
 * @date    24.11.2022
 * @brief
 */
#ifndef INC_APPLICATION_APP_H_
#define INC_APPLICATION_APP_H_

/* Includes ------------------------------------------------------------------*/

#include "application/app_params.h"
#include "util/api.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

API_StatusTypeDef APP_Init();
API_StatusTypeDef APP_Cycle();

/* Private functions ---------------------------------------------------------*/


#endif /* INC_APPLICATION_APP_H_ */
