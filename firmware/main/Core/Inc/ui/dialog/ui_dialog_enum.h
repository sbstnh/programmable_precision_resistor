/**
 * @file    ui_dialog_enum.h
 * @author  sebas
 * @date    30.12.2022
 * @brief
 */
#ifndef INC_UI_UI_DIALOG_ENUM_H_
#define INC_UI_UI_DIALOG_ENUM_H_

/* Includes ------------------------------------------------------------------*/

#include <stddef.h>

#include "util/api.h"
#include "ui/ui.h"

/* Exported constants --------------------------------------------------------*/

#define UIDE_CHOICE_LIST_END   { NULL, -1 }

/* Exported types ------------------------------------------------------------*/

typedef struct
{
    const char *name;
    int32_t tag;
} UIDE_ChoiceTypeDef;

typedef enum
{
	UIDE_ENTRY,
	UIDE_ENTERED,
	UIDE_ABORTED,
	UIDE_TERMINATED
} UIDE_StateTypeDef;

typedef struct uide_t
{
	bool _allow_wrap;
	bool _show_info;

	const char *_description;
	UIDE_ChoiceTypeDef *_choices;

	uint8_t _index_current_value;
	uint8_t _index_selected;
	uint8_t _index_max;

	UIDE_StateTypeDef _state;

	void (*_display_func)(struct uide_t *);
} UIDE_TypeDef;

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

API_StatusTypeDef UIDE_Show(UIDE_TypeDef *uide, const char *description, UIDE_ChoiceTypeDef *choices,
		int32_t current_value, bool allow_wrap, int32_t *result, void (*display_func)(struct uide_t *));

/* Private functions ---------------------------------------------------------*/


#endif /* INC_UI_UI_DIALOG_ENUM_H_ */
