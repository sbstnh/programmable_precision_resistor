/*
 * menu.c
 *
 *  Created on: 11.11.2022
 *      Author: sebas
 */


/*
This menu is based on:

              MICRO-MENU V2

          (C) Dean Camera, 2012
        www.fourwalledcubicle.com
     dean [at] fourwalledcubicle.com

        Royalty-free for all uses.

        Original sources: https://github.com/abcminiuser/micromenu-v2

Modified by Sebastian Harnisch
	                                  */

/* Includes ------------------------------------------------------------------*/

#include <string.h>
#include "util/api.h"
#include "ui/menu.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/** This is used when an invalid menu handle is required in
 *  a \ref MENU_ITEM() definition, i.e. to indicate that a
 *  menu has no linked parent, child, next or previous entry.
 */
MENUITEM_TypeDef const NULL_MENU = {0};

/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

void _MENU_WriteText(MENU_TypeDef *menu);

/* Exported functions --------------------------------------------------------*/

void MENU_Init(MENU_TypeDef *menu, bool display_level, bool no_siblings_for_root)
{
	menu->display_level = display_level;
	menu->no_siblings_for_root = no_siblings_for_root;
	menu->current_menu_item = &NULL_MENU;
}


void MENU_SetRoot(MENU_TypeDef *menu, MENUITEM_TypeDef *root)
{
	menu->current_root_menu_item = root;
}


MENUITEM_TypeDef* MENU_GetCurrentMenu(MENU_TypeDef *menu)
{
	return menu->current_menu_item;
}


API_StatusTypeDef MENU_Navigate(MENU_TypeDef *menu, MENUITEM_TypeDef* const new_menu)
{
	if ((new_menu == &NULL_MENU) || (new_menu == NULL))
		return API_INVALID_OPERATION;

	menu->current_menu_item = new_menu;

	if (menu->write_func)
		_MENU_WriteText(menu);

	API_StatusTypeDef (*select_callback)(void) = menu->current_menu_item->select_callback;

	if (!select_callback)
	{
		return API_OK;
	}

	return select_callback();
}


API_StatusTypeDef MENU_NavigateLeft(MENU_TypeDef *menu)
{
	if (menu->current_menu_item == menu->current_root_menu_item)
	{
		return API_INVALID_OPERATION;
	}

	if (menu->current_root_menu_item)
	{
		// Check whether we're at the top level for given root item
		MENUITEM_TypeDef *tmp = menu->current_menu_item;
		while (tmp && tmp != menu->current_root_menu_item)
		{
			tmp = tmp->previous;
		}

		if (tmp == menu->current_root_menu_item)
		{
			return API_INVALID_OPERATION;
		}
	}

	return MENU_Navigate(menu, menu->current_menu_item->parent);
}


API_StatusTypeDef MENU_NavigateRight(MENU_TypeDef *menu)
{
	return MENU_Navigate(menu, menu->current_menu_item->child);
}


API_StatusTypeDef MENU_NavigateUp(MENU_TypeDef *menu)
{
	if (menu->current_menu_item == menu->current_root_menu_item && menu->no_siblings_for_root)
	{
		return API_INVALID_OPERATION;
	}

	return MENU_Navigate(menu, menu->current_menu_item->previous);
}


API_StatusTypeDef MENU_NavigateDown(MENU_TypeDef *menu)
{
	if (menu->current_menu_item == menu->current_root_menu_item && menu->no_siblings_for_root)
	{
		return API_INVALID_OPERATION;
	}

	return MENU_Navigate(menu, menu->current_menu_item->next);
}


API_StatusTypeDef MENU_SetGenericWriteCallback(MENU_TypeDef *menu, void (*write_func)(const char* text))
{
	menu->write_func = write_func;
	return MENU_Navigate(menu, menu->current_menu_item);
}

API_StatusTypeDef MENU_EnterCurrentItem(MENU_TypeDef *menu)
{
	if ((menu->current_menu_item == &NULL_MENU) || (menu->current_menu_item == NULL))
		return API_INVALID_OPERATION;

	API_StatusTypeDef (*enter_callback)(void) = menu->current_menu_item->enter_callback;

	if (!enter_callback)
	{
		return API_OK;
	}

	API_StatusTypeDef status = enter_callback();

	// Rewrite this menu state because at this point, the display might
	// very well be overwritten by the callback
	if (menu->write_func && status != API_TERMINATED)
		_MENU_WriteText(menu);

	return status;
}


API_StatusTypeDef MENU_InvalidateText(MENU_TypeDef *menu)
{
	if (menu->write_func)
		_MENU_WriteText(menu);

	return API_OK;
}


/* Private functions ---------------------------------------------------------*/


void _MENU_WriteText(MENU_TypeDef *menu)
{
	if (!menu->display_level)
	{
		menu->write_func(menu->current_menu_item->text);
		return;
	}

	char levels[MENU_MAX_DISP_LEVELS];
	char str[MENU_MAX_TEXT_LENGTH];
	MENUITEM_TypeDef *trav = menu->current_menu_item;

	// Determine the levels leading to this menu item
	int8_t reversed_level;
	for (reversed_level = 0; trav->parent != &NULL_MENU && trav->parent != NULL && trav->parent != menu->current_root_menu_item && reversed_level < MENU_MAX_DISP_LEVELS - 1; reversed_level++)
	{
		trav = trav->parent;
		levels[reversed_level] = trav->number;
	}

	// Add dot separted list of levels to string
	int8_t pos = 0;
	for (--reversed_level; reversed_level >= 0; reversed_level--)
	{
		str[pos++] = levels[reversed_level];

		str[pos++] = '.';
	}
	str[pos++] = menu->current_menu_item->number;
	str[pos++] = '.';
	str[pos++] = ' ';
	str[pos] = '\0';

	// Add text of current menu item
	strcat(str + pos, menu->current_menu_item->text);

	// Finally write the string
	menu->write_func(str);
}
