/**
 * @file    ui_dialog_info.h
 * @author  sebas
 * @date    21.12.2022
 * @brief
 */
#ifndef INC_UI_UI_DIALOG_INFO_H_
#define INC_UI_UI_DIALOG_INFO_H_

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>

#include "util/api.h"
#include "ui/ui.h"

/* Exported constants --------------------------------------------------------*/

#define UIDI_ALLOW_CANCEL_AFTER			25

#define UIDI_DEFAULT_TIMEOUT_SHORT		25
#define UIDI_DEFAULT_TIMEOUT_MEDIUM		50
#define UIDI_DEFAULT_TIMEOUT_LONG		250

/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

API_StatusTypeDef UIDI_Show(const char *message, uint16_t timeout, bool centered);

/* Private functions ---------------------------------------------------------*/


#endif /* INC_UI_UI_DIALOG_INFO_H_ */
