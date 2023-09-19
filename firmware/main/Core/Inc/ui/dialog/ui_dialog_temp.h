/**
 * @file    ui_dialog_temp.h
 * @author  sebas
 * @date    05.01.2023
 * @brief
 */
#ifndef INC_UI_DIALOG_UI_DIALOG_TEMP_H_
#define INC_UI_DIALOG_UI_DIALOG_TEMP_H_

/* Includes ------------------------------------------------------------------*/

#include "util/api.h"
#include "ui/dialog/ui_dialog_enum.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

typedef enum
{
	UIDT_STATE_IMMEDIATE = 0,
	UIDT_STATE_MINIMUM = 1,
	UIDT_STATE_MAXIMUM = 2,
	UIDT_STATE_AVERAGE = 3
} UIDT_StateTypeDef;

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void _UIDT_Display(UIDE_TypeDef *uide);

/* Private functions ---------------------------------------------------------*/


#endif /* INC_UI_DIALOG_UI_DIALOG_TEMP_H_ */
