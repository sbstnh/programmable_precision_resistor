/**
 * @file    ui_parser.c
 * @author  sebas
 * @date    22.12.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>
#include <string.h>
#include "ui/ui_parser.h"
#include "util/util.h"
#include "util/api.h"

/* Private defines -----------------------------------------------------------*/

#define K		'K'
#define DP		'.'
#define MINUS	'-'
#define END 	'\0'

/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

#define IS_DIGIT(c)		((c) >= '0' && (c) <= '9')

/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

char _UIPAR_Peek(UIPAR_TypeDef *parser);
char _UIPAR_Read(UIPAR_TypeDef *parser);
uint8_t _UIPAR_ReadDigits(UIPAR_TypeDef *parser, uint8_t max_count, int64_t *result);

/* Exported functions --------------------------------------------------------*/


//UIPAR_StatusTypeDef UIPAR_Parse_Integer(const char *str, uint8_t max_digits,
//		int64_t min, int64_t max, int64_t *result)
//{
//
//	// 	       ┌───┐                                      ┌───┐
//	//	    ┌──┤"-"├──┐	                              ┌──►│"K"├──┐
//	// 	    │  └───┘  │	                              │   └───┘  │
//	//      │         ▼ ┌──────────┐                  │          ▼
//	//    ┌─┴───────────┤ "0".."9" ├──────────────────────────┴────────────┐
//	//    │             └──────────┘                                       │
//	//    │                                                                │
//	//   ─┴────────────────────────────────────────────────────────────────┴─►
//
//	UIPAR_TypeDef parser =
//	{
//			.input = str,
//			.pos = 0,
//			.neg = false,
//			.result = 0,
//	};
//
//	char c = _UIPAR_Peek(&parser);
//
//	if (c == END)
//	{
//		return UIPAR_END_WITHOUT_INPUT;
//	}
//
//	if (c == MINUS)
//	{
//		parser.neg = true;
//		_UIPAR_Read(&parser);
//	}
//
//	*result = 0;
//
//	uint8_t decimals = _UIPAR_ReadDigits(&parser, max_digits, result);
//
//	if (!decimals)
//	{
//		return UIPAR_DIGIT_EXPECTED;
//	}
//
//	if (_UIPAR_Peek(&parser) == K)
//	{
//		*result *= 1000;
//		_UIPAR_Read(&parser);
//	}
//
//	if (_UIPAR_Read(&parser) == END)
//	{
//		if (parser.neg)
//		{
//			*result = -*result;
//		}
//
//		if (*result < min || *result > max)
//		{
//			return UIPAR_PARAM_OUT_OF_RANGE;
//		}
//
//		return UIPAR_OK;
//	}
//
//	return UIPAR_END_EXPECTED;
//}


UIPAR_StatusTypeDef UIPAR_Parse_Number(UIPAR_TypeDef *parser, const char *str, UIPAR_ResultTypeDef *result)
{
	const UIPAR_StatusTypeDef status = _UIPAR_Parse_NumberWithoutScaling(parser, str, result);

	if (status != UIPAR_OK)
	{
		return status;
	}

	const int8_t exp = parser->target_decimal_places - result->decimal_places;

	if (exp > 0)
	{
		result->result *= UTIL_PowerUInt64(10, exp);
	}
	else if (exp < 0)
	{
		result->result = UTIL_DivRoundClosestInt64(result->result, UTIL_PowerUInt64(10, -exp));
	}

	// Check the range of the resulting result
	if (!IN_RANGE(parser->min, parser->max, result->result))
	{
		return UIPAR_PARAM_OUT_OF_RANGE;
	}

	result->decimal_places = parser->target_decimal_places;
	return status;
}


/* Private functions ---------------------------------------------------------*/


UIPAR_StatusTypeDef _UIPAR_Parse_NumberWithoutScaling(UIPAR_TypeDef *parser, const char *str, UIPAR_ResultTypeDef *result)
{

    //                                                post: <= m-n
	//                                              ┌──────────────┐
	//	                                            │              │
	//        ┌───┐	      pre: <= m        ┌───┐	▼ ┌──────────┐ │	    ┌───┐
	//      ┌─┤"-"├──┐ ┌──────────────┐ ┌──┤"."├──────┤ "0".."9" ├─┴─┐	┌──►│"K"├──┐
	//      │ └───┘  │ │              │ │  └───┘	  └──────────┘   │	│   └───┘  │
	//      │        ▼ ▼ ┌──────────┐ │ │                            ▼  │          ▼
	//    ┌─┴────────────┤ "0".."9" ├─┴─┴───────────────────────────────┴────────────┐
	//    │              └──────────┘                                                │
	//    │                                                                          ▼
	//   ─┴────────────────────────────────────────────────────────────────────────────►

	parser->_input = str;
	parser->_pos = 0;

	// Initialize result
	memset(result, 0, sizeof(*result));

	const char c = _UIPAR_Peek(parser);

	// Detect empty strings
	if (c == END)
	{
		return UIPAR_END_WITHOUT_INPUT;
	}

	// Check whether the number is negative - store info, but don't act on it yet.
	if (c == MINUS)
	{
		result->neg = true;
		_UIPAR_Read(parser);
	}

	// Read as many decimals as possible, but not more than the specified number
	const uint8_t pre_decimals = _UIPAR_ReadDigits(parser, parser->max_digits, &result->result);

	// Check whether a decimal point was found and act accordingly
	if (parser->max_decimal_places && _UIPAR_Peek(parser) == DP)
	{
		_UIPAR_Read(parser);

		// Determine how many decimal places are allowed
		const uint8_t permissible_decimal_places = MIN(parser->max_digits - pre_decimals, parser->max_decimal_places);

		// Read as many decimal places as possible, but not more than allowed
		result->decimal_places = _UIPAR_ReadDigits(parser, permissible_decimal_places, &result->result);
	}

	// Handle a unit prefix if found
	if (_UIPAR_Peek(parser) == K)
	{
		result->result *= 1000;
		_UIPAR_Read(parser);
	}

	// End of string
	if (_UIPAR_Read(parser) == END)
	{
		// Evaluate the minus sign
		if (result->neg)
		{
			result->result = -result->result;
		}

		return UIPAR_OK;
	}

	return UIPAR_END_EXPECTED;
}


char _UIPAR_Peek(UIPAR_TypeDef *parser)
{
	return parser->_input[parser->_pos];
}


char _UIPAR_Read(UIPAR_TypeDef *parser)
{
	return parser->_input[parser->_pos++];
}

uint8_t _UIPAR_ReadDigits(UIPAR_TypeDef *parser, uint8_t max_count, int64_t *result)
{
	uint8_t count = max_count;

	while (count-- > 0 && IS_DIGIT(parser->_input[parser->_pos]))
	{
		*result = 10 * (*result) + (parser->_input[parser->_pos++] - '0');
	}

	return max_count - (count + 1);
}

