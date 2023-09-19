/**
 * @file    app_display.h
 * @author  sebas
 * @date    21.12.2022
 * @brief
 */
#ifndef INC_APPLICATION_APP_DISPLAY_H_
#define INC_APPLICATION_APP_DISPLAY_H_

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

bool APP_Get_DisplayEnable();
API_StatusTypeDef APP_Set_DisplayEnable(bool enable);

char *APP_Get_DisplayUserTextData();

bool APP_Get_DisplayUserTextState();
API_StatusTypeDef APP_Set_DisplayUserTextState(bool state);

API_StatusTypeDef APP_Run_DisplayUserTextClear();

PRIM_RESolution_TypeDef APP_Get_DisplayPrimaryResolution();
UTIL_DigitsTypeDef APP_Get_DisplayPrimaryResolutionAsCounts();
API_StatusTypeDef APP_Set_DisplayPrimaryResolution(PRIM_RESolution_TypeDef resolution);

SEC_MODE_TypeDef APP_Get_DisplaySecondaryMode();
API_StatusTypeDef APP_Set_DisplaySecondaryMode(SEC_MODE_TypeDef mode);
API_StatusTypeDef APP_Run_DisplaySecondaryModeNext();

/* Private functions ---------------------------------------------------------*/


#endif /* INC_APPLICATION_APP_DISPLAY_H_ */
