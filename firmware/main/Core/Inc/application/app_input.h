/**
 * @file    app_input.h
 * @author  sebas
 * @date    03.12.2022
 * @brief
 */
#ifndef INC_APPLICATION_APP_INPUT_H_
#define INC_APPLICATION_APP_INPUT_H_

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdint.h>
#include "util/api.h"
#include "application/app_params.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

bool APP_Get_InputState();
API_StatusTypeDef APP_Set_InputState(bool state);
API_StatusTypeDef APP_Run_InputStateToggle();

INH_MODE_TypeDef APP_Get_InputInhibitMode();
API_StatusTypeDef APP_Set_InputInhibitModeSave(INH_MODE_TypeDef mode, bool save);
API_StatusTypeDef APP_Set_InputInhibitMode(INH_MODE_TypeDef mode);

bool APP_Get_InputInhibitState();
API_StatusTypeDef APP_Set_InputInhibitState(bool state);

/* Private functions ---------------------------------------------------------*/


#endif /* INC_APPLICATION_APP_INPUT_H_ */
