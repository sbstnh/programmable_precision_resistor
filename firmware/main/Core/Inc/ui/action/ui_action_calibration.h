/**
 * @file    ui_action_calibration.h
 * @author  sebas
 * @date    07.01.2023
 * @brief
 */
#ifndef INC_UI_ACTION_UI_ACTION_CALIBRATION_H_
#define INC_UI_ACTION_UI_ACTION_CALIBRATION_H_

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

API_StatusTypeDef UIACT_CalibrationCount();
API_StatusTypeDef UIACT_CalibrationDate();
API_StatusTypeDef UIACT_CalibrationString();
API_StatusTypeDef UIACT_CalibrationTemp();
API_StatusTypeDef UIACT_CalibrationSetup_New(UIDN_TypeDef *uidn, const char *default_value, UIDN_CursorPosTypeDef cursor_position);
API_StatusTypeDef UIACT_CalibrationSetup_Edit(UIDN_TypeDef *uidn, UIDN_CursorPosTypeDef cursor_position);
API_StatusTypeDef UIACT_CalibrationValue_New(UIDN_TypeDef *uidn, const char *default_value, UIDN_CursorPosTypeDef cursor_position);
API_StatusTypeDef UIACT_CalibrationValue_Edit(UIDN_TypeDef *uidn, UIDN_CursorPosTypeDef cursor_position);

/* Private functions ---------------------------------------------------------*/


#endif /* INC_UI_ACTION_UI_ACTION_CALIBRATION_H_ */
