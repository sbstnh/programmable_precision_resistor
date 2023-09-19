/**
 * @file    ui_app_quick.h
 * @author  sebas
 * @date    30.12.2022
 * @brief
 */
#ifndef INC_UI_UI_APP_QUICK_H_
#define INC_UI_UI_APP_QUICK_H_

/* Includes ------------------------------------------------------------------*/

#include "util/api.h"
#include "ui/dialog/ui_dialog_number.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

API_StatusTypeDef UIACT_SourceResistanceMode();

API_StatusTypeDef UIACT_ResistanceCalMode();

API_StatusTypeDef UIACT_ResistanceImmediateValue();
API_StatusTypeDef UIACT_ResistanceImmediateValue_Edit(UIDN_TypeDef *uidn, UIDN_CursorPosTypeDef cursor_position);
API_StatusTypeDef UIACT_ResistanceImmediateValue_New(UIDN_TypeDef *uidn, const char *default_value, UIDN_CursorPosTypeDef cursor_position);

API_StatusTypeDef UIACT_ResistanceTriggeredValue();
API_StatusTypeDef UIACT_ResistanceTriggeredValue_Edit(UIDN_TypeDef *uidn, UIDN_CursorPosTypeDef cursor_position);
API_StatusTypeDef UIACT_ResistanceTriggeredValue_New(UIDN_TypeDef *uidn, const char *default_value, UIDN_CursorPosTypeDef cursor_position);

API_StatusTypeDef UIACT_ResistanceStepIncrement();
API_StatusTypeDef UIACT_ResistanceStepMode();
API_StatusTypeDef UIACT_ResistanceStepOverflow();

API_StatusTypeDef UIACT_ResistanceLimitState();
API_StatusTypeDef UIACT_ResistanceLimitLow();
API_StatusTypeDef UIACT_ResistanceLimitHigh();

API_StatusTypeDef UIACT_ResistanceSwitchingMode();


/* Private functions ---------------------------------------------------------*/


#endif /* INC_UI_UI_APP_QUICK_H_ */
