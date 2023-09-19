/**
 * @file    ui_action_util.h
 * @author  sebas
 * @date    01.01.2023
 * @brief
 */
#ifndef INC_UI_ACTION_UI_ACTION_UTIL_H_
#define INC_UI_ACTION_UI_ACTION_UTIL_H_

/* Includes ------------------------------------------------------------------*/

#include "util/api.h"

#include "ui/dialog/ui_dialog_enum.h"
#include "ui/dialog/ui_dialog_number.h"
#include "ui/dialog/ui_dialog_info.h"

#include "application/app_params.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

#define ENUM_GETTER_TYPE			int32_t (*)(void)
#define ENUM_SETTER_TYPE			API_StatusTypeDef (*)(int32_t)

/* Exported variables --------------------------------------------------------*/

extern UIDE_ChoiceTypeDef UIACT_BOOL[];

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

API_StatusTypeDef UIACT_UtilDialogEnum(const char *description, UIDE_ChoiceTypeDef *choices,
		int32_t (*get_value)(void), API_StatusTypeDef (*set_value)(int32_t));

API_StatusTypeDef UIACT_UtilDialogInfoInt(const char *description, const char *unit,
		int32_t value, uint8_t max_digits, uint8_t decimal_places);

API_StatusTypeDef UIACT_UtilDialogIntValueTypeDef(UIDN_TypeDef *uidn, UIPAR_TypeDef *parser,
		const char *description, const char *unit, UIDN_CursorPosTypeDef cursor_position,
		INT_VALUE_TypeDef (*get_value)(void), API_StatusTypeDef (*set_value)(int32_t));

/* Private functions ---------------------------------------------------------*/


#endif /* INC_UI_ACTION_UI_ACTION_UTIL_H_ */
