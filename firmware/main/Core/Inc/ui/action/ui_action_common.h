/**
 * @file    ui_action_common.h
 * @author  sebas
 * @date    23.04.2023
 * @brief
 */
#ifndef INC_UI_ACTION_UI_ACTION_COMMON_H_
#define INC_UI_ACTION_UI_ACTION_COMMON_H_

/* Includes ------------------------------------------------------------------*/

#include "util/api.h"
#include "ui/action/ui_action_calibration.h"

#include "ui/dialog/ui_dialog_number.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

API_StatusTypeDef UIACT_Rcl();
API_StatusTypeDef UIACT_Sav();

/* Private functions ---------------------------------------------------------*/


#endif /* INC_UI_ACTION_UI_ACTION_COMMON_H_ */
