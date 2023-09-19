/**
 * @file    util.h
 * @author  sebas
 * @date    03.12.2022
 * @brief
 */

#ifndef UTIL_UTIL_H_
#define UTIL_UTIL_H_

/* Includes ------------------------------------------------------------------*/

#include <stddef.h>
#include <stdbool.h>
#include <inttypes.h>

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

typedef enum
{
	UTIL_LEAD_TRAIL_ZERO_SKIP = 0,
	UTIL_LEAD_TRAIL_ZERO_BLANK = 1,
	UTIL_LEAD_TRAIL_ZERO_ZERO = 2,
} UTIL_LeadTrailZeroTypeDef;


typedef enum
{
	UTIL_DIGITS_3	=      999,
	UTIL_DIGITS_3_5 =     1999,
	UTIL_DIGITS_4   =     9999,
	UTIL_DIGITS_4_5	=    19999,
	UTIL_DIGITS_5	=    99999,
	UTIL_DIGITS_5_5 =   199999,
	UTIL_DIGITS_6	=   999999,
	UTIL_DIGITS_6_5	=  1999999,
	UTIL_DIGITS_7   =  9999999,
	UTIL_DIGITS_7_5 = 19999999
} UTIL_DigitsTypeDef;

/* Exported macro ------------------------------------------------------------*/

#define COUNT_OF(x) 	((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

#ifndef MIN
	#define MIN(x, y)		((x) < (y) ? (x) : (y))
#endif
#ifndef MAX
	#define MAX(x, y)		((x) > (y) ? (x) : (y))
#endif

#ifndef LIM
	#define LIM(min, max, val)	( (val) < (min) ? (min) : ( (val) > (max) ? (max) : (val) ) )
#endif

#ifndef IN_RANGE
	#define IN_RANGE(min, max, val) ( (val) >= (min) && (val) <= (max) )
#endif

#ifndef IS_DIGIT
	#define IS_DIGIT(c)		((c) >= '0' && (c) <= '9')
#endif


/* Exported variables --------------------------------------------------------*/

extern const int32_t conversion_array[];

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void UTIL_UIntToDigitArray(uint8_t number_of_digits, uint8_t *digit_array, uint32_t value, bool reverse_order);
uint8_t UTIL_UIntToStr(char *str, uint32_t value, uint8_t number_of_digits, uint8_t decimal_places,
		UTIL_LeadTrailZeroTypeDef leading_zeros, UTIL_LeadTrailZeroTypeDef trailing_zeros);

uint8_t UTIL_UIntToStrEngineering(char *str, uint32_t value, UTIL_DigitsTypeDef counts, uint8_t scaler, UTIL_LeadTrailZeroTypeDef leading_zeros);

uint32_t UTIL_DigitArrayToUInt(uint8_t *digits, uint8_t length);

uint8_t UTIL_NumberOfDigitsUInt(uint32_t number);
uint8_t UTIL_NumberOfDigitsInt(int32_t number);

uint8_t UTIL_MostSignificantDigitUint(uint32_t number);
uint8_t UTIL_DigitAt(uint32_t number, uint8_t order);

int32_t UTIL_DivRoundClosestInt32(const int32_t n, const int32_t d);
int64_t UTIL_DivRoundClosestInt64(const int64_t n, const int64_t d);

int32_t UTIL_RoundToInt32(double number);

uint32_t UTIL_Power(uint32_t base, uint32_t exp);
uint64_t UTIL_PowerUInt64(uint64_t base, uint64_t exp);
uint8_t UTIL_FindClosestIndex(uint32_t *array, uint8_t length, uint32_t value);

char *UTIL_StrInsertChar(char *target, const char *source, const char insert, uint8_t pos);
char *UTIL_StrInsert(char *target, const char *source, const char *insert, uint8_t pos);

char *UTIL_StrNumberRemoveLeadingZeros(char *target, const char *source);
char *UTIL_StrNumberRemoveTrailingZeros(char *target, const char *source);

uint8_t UTIL_StrLenDisplay(const char *str, uint8_t max_len);

/* Private functions ---------------------------------------------------------*/

#endif /* UTIL_UTIL_H_ */
