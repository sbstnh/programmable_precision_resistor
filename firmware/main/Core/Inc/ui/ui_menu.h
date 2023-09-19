/**
 * @file    ui_app_menu.h
 * @author  sebas
 * @date    23.11.2022
 * @brief
 */
#ifndef INC_UI_UI_MENU_H_
#define INC_UI_UI_MENU_H_

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>
#include "ui/ui_menu_def.h"

#include "util/api.h"
#include "ui/ui.h"

#include "ui/menu.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/


typedef enum
{
	UIMENU_ENTRY,
	UIMENU_ENTERED,
	UIMENU_ABORTED
} UIMENU_StateTypeDef;

typedef struct
{
	bool _show_applied;
	bool _show_info;
	MENU_TypeDef _menu;
	UIMENU_StateTypeDef _state;
} UIMENU_TypeDef;

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void UIMENU_SetRoot(UIMENU_TypeDef *uimenu, MENUITEM_TypeDef *root);
API_StatusTypeDef UIMENU_Show(UIMENU_TypeDef *uimenu, MENUITEM_TypeDef *item, bool show_info);

/* Private functions ---------------------------------------------------------*/


#endif /* INC_UI_UI_MENU_H_ */
