/*
 * menu.h
 *
 *  Created on: 11.11.2022
 *      Author: sebas
 */

#ifndef INC_APPLICATION_MENU_H_
#define INC_APPLICATION_MENU_H_

/**

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

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "util/api.h"

/* Exported constants --------------------------------------------------------*/

#define MENU_MAX_DISP_LEVELS	4
#define MENU_MAX_TEXT_LENGTH	32

/* Exported types ------------------------------------------------------------*/

/** Type define for a menu item. Menu items should be initialized via the helper
 *  macro \ref MENU_ITEM(), not created from this type directly in user-code.
 */
typedef const struct menuitem {
	const char number; /**< Number of the entry in the current menu level */
	const struct menuitem *next; /**< Pointer to the next menu item of this menu item */
	const struct menuitem *previous; /**< Pointer to the previous menu item of this menu item */
	const struct menuitem *parent; /**< Pointer to the parent menu item of this menu item */
	const struct menuitem *child; /**< Pointer to the child menu item of this menu item */
	API_StatusTypeDef (*select_callback)(void); /**< Pointer to the optional menu-specific select callback of this menu item */
	API_StatusTypeDef (*enter_callback)(void); /**< Pointer to the optional menu-specific enter callback of this menu item */
	const char *text; /**< Menu item text to pass to the menu display callback function */
} MENUITEM_TypeDef;

typedef struct
{
	/** \internal
	 *  Defines whether to show the current menu level.
	 */
	bool display_level;


	/** \internal
	 *  Defines whether to allow navigation to siblings of
	 *  the root element.
	 */
	bool no_siblings_for_root;


	/** \internal
	 *  Pointer to the currently selected root menu item.
	 *  May differ from the actual root(s).
	 */
	MENUITEM_TypeDef* current_root_menu_item;


	/** \internal
	 *  Pointer to the currently selected menu item.
	 */
	MENUITEM_TypeDef* current_menu_item;


	/** \internal
	 *  Pointer to the generic menu text display function
	 *  callback, to display the configured text of a menu item
	 *  if no menu-specific display function has been set
	 *  in the select menu item.
	 */
	void (*write_func)(const char* Text);
} MENU_TypeDef;


/* Exported macro ------------------------------------------------------------*/


/** Creates a new menu item entry with the specified links and callbacks.
 *
 *  \param[in] name      Name of the menu entry, must be unique.
 *  \param[in] next      Name of the next linked menu item, or \ref NULL_MENU if no menu link.
 *  \param[in] previous  Name of the previous linked menu item, or \ref NULL_MENU if no menu link.
 *  \param[in] parent    Name of the parent linked menu item, or \ref NULL_MENU if no menu link.
 *  \param[in] child     Name of the child linked menu item, or \ref NULL_MENU if no menu link.
 *  \param[in] select_func  Function callback to execute when the menu item is selected, or \c NULL for no callback.
 *  \param[in] enter_func   Function callback to execute when the menu item is entered, or \c NULL for no callback.
 *  \param[in] text      Text associated with this menu item.
 */
#define MENU_ITEM(level, text, name, next, previous, parent, child, select_func, enter_func) \
	extern MENUITEM_TypeDef const next;     \
	extern MENUITEM_TypeDef const previous; \
	extern MENUITEM_TypeDef const parent;   \
	extern MENUITEM_TypeDef const child;  \
	MENUITEM_TypeDef const name = {level, &next, &previous, &parent, &child, select_func, enter_func, text}

/** Relative navigational menu entry for \ref Menu_Navigate(), to move to the menu parent. */
#define MENU_PARENT(menu)         MENU_GetCurrentMenu(menu)->parent

/** Relative navigational menu entry for \ref Menu_Navigate(), to move to the menu child. */
#define MENU_CHILD(menu)          MENU_GetCurrentMenu(menu)->child

/** Relative navigational menu entry for \ref Menu_Navigate(), to move to the next linked menu item. */
#define MENU_NEXT(menu)           MENU_GetCurrentMenu(menu)->next

/** Relative navigational menu entry for \ref Menu_Navigate(), to move to the previous linked menu item. */
#define MENU_PREVIOUS(menu)       MENU_GetCurrentMenu(menu)->previous


/* Exported variables --------------------------------------------------------*/


/** Null menu entry, used in \ref MENU_ITEM() definitions where no menu link is to be made. */
extern MENUITEM_TypeDef const NULL_MENU;


/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** Initializes the menu structures.
 *
 *  \param[in] menu  		  		Pointer to the menu that shall be initialized.
 *  \param[in] display_level  		Whether the menu level indication shall be visible.
 *  \param[in] no_siblings_for_root	Whether siblings of root are accessible.
 */
void MENU_Init(MENU_TypeDef *menu, bool display_level, bool no_siblings_for_root);

/** Sets a menu item as the root of the menu.
 *
 *  \param[in] menu  	Pointer to the menu that shall be initialized.
 *  \param[in] root     Pointer to the menu item that shall be set as root.
 */
void MENU_SetRoot(MENU_TypeDef *menu, MENUITEM_TypeDef *root);

/** Retrieves the currently selected meny item.
 *
 *  \return Pointer to the currently selected meny item.
 */
MENUITEM_TypeDef* MENU_GetCurrentMenu(MENU_TypeDef *menu);

/** Navigates to an absolute or relative menu entry.
 *
 * \param[in] menu      Pointer to the menu.
 * \param[in] new_menu  Pointer to the absolute menu item to select, or one of \ref MENU_PARENT,
 *                      \ref MENU_CHILD, \ref MENU_NEXT or \ref MENU_PREVIOUS for relative navigation.
 * \return              Status code of the operation
 */
API_StatusTypeDef MENU_Navigate(MENU_TypeDef *menu, MENUITEM_TypeDef* const new_menu);

/** Navigates to the parent menu. Stops at the absolute root or the current root, whatever comes first.
 *
 * \param[in] menu      Pointer to the menu.
 * \return              Status code of the operation
 */
API_StatusTypeDef MENU_NavigateLeft(MENU_TypeDef *menu);

/** Navigates to the child menu.
 *
 * \param[in] menu      Pointer to the menu.
 * \return              Status code of the operation
 */
API_StatusTypeDef MENU_NavigateRight(MENU_TypeDef *menu);

/** Navigates to the previous menu, if current entry is not root.
 *
 * \param[in] menu      Pointer to the menu.
 * \return              Status code of the operation
 */
API_StatusTypeDef MENU_NavigateUp(MENU_TypeDef *menu);

/** Navigates to the next menu, if current entry is not root.
 *
 * \param[in] menu      Pointer to the menu.
 * \return              Status code of the operation
 */
API_StatusTypeDef MENU_NavigateDown(MENU_TypeDef *menu);

/** Configures the menu text write callback function, fired for all menu items. Within this callback
 *  function the user should implement code to display the current menu text stored in const
 *  memory space.
 *
 *  \param[in] menu         Pointer to the menu.
 *  \param[in] write_func   Pointer to a callback function to execute for each selected menu item.
 *  \return              Status code of the operation
 */
API_StatusTypeDef MENU_SetGenericWriteCallback(MENU_TypeDef *menu, void (*write_func)(const char* text));

/** Enters the currently selected menu item, running its configured callback function (if any).
 *
 *  \param[in] menu  Pointer to the menu.
 *  \return              Status code of the operation
 */
API_StatusTypeDef MENU_EnterCurrentItem(MENU_TypeDef *menu);

/** Forces the current menu item to be written again.
 *
 *  \param[in] menu  Pointer to the menu.
 *  \return              Status code of the operation
 */
API_StatusTypeDef MENU_InvalidateText(MENU_TypeDef *menu);

#endif /* INC_APPLICATION_MENU_H_ */
