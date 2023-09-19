/**
 * @file    ui_number_entry.h
 * @author  sebas
 * @date    20.12.2022
 * @brief
 */
#ifndef INC_UI_UI_DIALOG_NUMBER_H_
#define INC_UI_UI_DIALOG_NUMBER_H_

/* Includes ------------------------------------------------------------------*/

#include "util/api.h"
#include "ui/ui.h"
#include "ui/ui_parser_def.h"

/* Exported constants --------------------------------------------------------*/

#define UIDN_PARSE_STR_LEN	13
#define UIDN_DESC_MAX_LEN	10

/* Exported types ------------------------------------------------------------*/

typedef enum
{
	UIDN_CURSOR_LEAVE = -1,
	UIDN_CURSOR_START = 0,
	UIDN_CURSOR_END = (UIDN_PARSE_STR_LEN + 1)
} UIDN_CursorPosTypeDef;

typedef enum
{
	UIDN_ENTRY,
	UIDN_ENTERED,
	UIDN_ABORTED,
	UIDN_TERMINATED
} UIDN_StateTypeDef;

typedef struct
{
	UIPAR_TypeDef *parser;
	UIDN_CursorPosTypeDef initial_pos;

	UIDN_StateTypeDef _state;
	int8_t _pos;

	char _entry_str[UIDN_PARSE_STR_LEN];
	char _parse_str[UIDN_PARSE_STR_LEN];
	UIPAR_StatusTypeDef _parse_status;
	UIPAR_ResultTypeDef _parse_result;
} UIDN_TypeDef;

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/


/** Set up the dialog to be used with a specific parser object and the initial cursor position.
 *
 * 	@param[in] uidn    		  Pointer to the dialog.
 * 	@param[in] parser  		  Pointer to parser to be used.
 * 	@param[in] pos    		  Initial cursor position.
 */
void UIDN_Setup(UIDN_TypeDef *uidn, UIPAR_TypeDef *parser, UIDN_CursorPosTypeDef cursor_position);


/** Show dialog for number entry.
 *
 * 	@param[in] uidn    		  Pointer to the dialog
 * 	@param[in] description    Description that shall be shown.
 * 	@param[in] default_value  Value that shall be shown initially.
 * 	@param[out] result  	  Result of the entry, if entry successful.
 * 	@return					  Exit status of the number entry process.
 */
API_StatusTypeDef UIDN_Show(UIDN_TypeDef *uidn, const char *description, const char *default_value, const char *unit, uint32_t *result);

/* Private functions ---------------------------------------------------------*/


#endif /* INC_UI_UI_DIALOG_NUMBER_H_ */
