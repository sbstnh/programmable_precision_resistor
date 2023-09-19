/**
 * @file    ui_parser.h
 * @author  sebas
 * @date    22.12.2022
 * @brief
 */
#ifndef INC_UI_UI_PARSER_H_
#define INC_UI_UI_PARSER_H_

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

typedef enum
{
	UIPAR_OK = 0,
	UIPAR_END_WITHOUT_INPUT,

	UIPAR_END_EXPECTED,
	UIPAR_DIGIT_EXPECTED,
	UIPAR_DIGIT_OR_END_EXPECTED,
	UIPAR_K_OR_END_EXPECTED,

	UIPAR_PARAM_OUT_OF_RANGE,
} UIPAR_StatusTypeDef;


typedef struct
{
	uint8_t max_digits;
	uint8_t max_decimal_places;

	int64_t min;
	int64_t max;

	uint8_t target_decimal_places;

	const char *_input;
	uint8_t _pos;
} UIPAR_TypeDef;


typedef struct
{
	bool neg;
	uint8_t decimal_places;
	uint64_t pre_decimal;
	uint64_t post_decimal;

	int64_t result;
} UIPAR_ResultTypeDef;


/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

UIPAR_StatusTypeDef UIPAR_Parse_Number(UIPAR_TypeDef *parser, const char *str,
		UIPAR_ResultTypeDef *result);

/* Private functions ---------------------------------------------------------*/
UIPAR_StatusTypeDef _UIPAR_Parse_NumberWithoutScaling(UIPAR_TypeDef *parser, const char *str,
		UIPAR_ResultTypeDef *result);
char _UIPAR_Peek(UIPAR_TypeDef *parser);
char _UIPAR_Read(UIPAR_TypeDef *parser);
uint8_t _UIPAR_ReadDigits(UIPAR_TypeDef *parser, uint8_t max_count, int64_t *result);

#endif /* INC_UI_UI_PARSER_H_ */
