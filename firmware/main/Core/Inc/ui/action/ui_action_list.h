/**
 * @file    ui_action_list.h
 * @author  sebas
 * @date    24.04.2023
 * @brief
 */
#ifndef INC_UI_ACTION_UI_ACTION_LIST_H_
#define INC_UI_ACTION_UI_ACTION_LIST_H_

/* Includes ------------------------------------------------------------------*/

#include "util/api.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

API_StatusTypeDef UIACT_ListResDwell();
API_StatusTypeDef UIACT_ListResDwellPoints();
API_StatusTypeDef UIACT_ListResIndex();
API_StatusTypeDef UIACT_ListResLevel();
API_StatusTypeDef UIACT_ListResPoints();
API_StatusTypeDef UIACT_ListResRunNumber();
API_StatusTypeDef UIACT_ListResRunCount();
API_StatusTypeDef UIACT_ListStartInput();
API_StatusTypeDef UIACT_ListStartMode();
API_StatusTypeDef UIACT_ListStep();
API_StatusTypeDef UIACT_ListTerminateInput();
API_StatusTypeDef UIACT_ListTerminateLast();

/* Private functions ---------------------------------------------------------*/


#endif /* INC_UI_ACTION_UI_ACTION_LIST_H_ */
