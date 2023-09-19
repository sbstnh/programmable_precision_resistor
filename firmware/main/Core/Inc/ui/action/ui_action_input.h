/**
 * @file    ui_action_input.h
 * @author  sebas
 * @date    Jan 15, 2023
 * @brief
 */
#ifndef INC_UI_ACTION_UI_ACTION_INPUT_H_
#define INC_UI_ACTION_UI_ACTION_INPUT_H_

/* Includes ------------------------------------------------------------------*/

#include "util/api.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

API_StatusTypeDef UIACT_InputInhibitMode();
API_StatusTypeDef UIACT_InputInhibitClear();
API_StatusTypeDef UIACT_InputInhibitState();

/* Private functions ---------------------------------------------------------*/


#endif /* INC_UI_ACTION_UI_ACTION_INPUT_H_ */
