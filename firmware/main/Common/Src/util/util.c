/**
 * @file    util.c
 * @author  sebas
 * @date    03.12.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include <limits.h>
#include <util/util.h>
#include <string.h>

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

const int32_t conversion_array[] =
		{
				1,
				10,
				100,
				1000,
				10000,
				100000,
				1000000,
				10000000,
				100000000,
				1000000000
		};

/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/


/** @brief	Converts a signed integer number to a uint8_t array.
 *
 *  @param	number_of_digits	Number of digits to convert, maximum of 9 for uint32_t
 *  @param	*digit_array		uint8_t array to write the data to. Min length equals max digits of chosen int type
 *  @param	value				Value to be converted
 *  @param	reverse_order		Specifies whether the order of the digits shall be reversed (i. e. starting with 10^0)
 *  @retval	none
 */
void UTIL_UIntToDigitArray(uint8_t number_of_digits, uint8_t *digit_array, uint32_t value, bool reverse_order)
{
	uint8_t digit;
	uint8_t result_pos;

	while (value >= conversion_array[number_of_digits])
	{
		value -= conversion_array[number_of_digits];
	}

	number_of_digits--;

	for (int8_t i = number_of_digits; i >= 0; i--)
	{
		digit = 0;
		while (value >= conversion_array[i])
		{
			value -= conversion_array[i];
			digit++;
		}

		result_pos = reverse_order ? i : number_of_digits - i;
		digit_array[result_pos] = digit;
	}
}


/** @brief	Converts a signed integer number to a string.
 *
 *  @param	*str				pointer to write the data to.
 *  @param	number_of_digits	Number of digits to convert, maximum of 9 for uint32_t.
 *  @param	value				Value to be converted.
 *  @param	decimal_places		Inserts a decimal point in order to show the specified number of decimal places.
 *  @param  leading_zeros		Specifies whether leading zeros shall be blanked or skipped instead.
 *  @retval						Length of str.
 */
uint8_t UTIL_UIntToStr(char *str, uint32_t value, uint8_t number_of_digits, uint8_t decimal_places,
		UTIL_LeadTrailZeroTypeDef leading_zeros, UTIL_LeadTrailZeroTypeDef trailing_zeros)
{
	uint8_t digit;
	int8_t i, pos;
	bool significant = leading_zeros == UTIL_LEAD_TRAIL_ZERO_ZERO;
	bool decimal = false;


	if (number_of_digits < 10)
	{
		while (value >= conversion_array[number_of_digits])
		{
			value -= conversion_array[number_of_digits];
		}
	}

	number_of_digits--;

	for (i = number_of_digits, pos = 0; i >= 0; i--)
	{
		digit = 0;
		while (value >= conversion_array[i])
		{
			value -= conversion_array[i];
			digit++;
		}

		if (decimal_places)
		{
			if (pos == number_of_digits - decimal_places + 1)
			{
				decimal = true;

				if ((trailing_zeros != UTIL_LEAD_TRAIL_ZERO_SKIP && trailing_zeros != UTIL_LEAD_TRAIL_ZERO_BLANK)
						|| value || digit)
				{
					str[pos++] = '.';
				}
			}
		}

		if (decimal && !value && !digit)
		{
			if (trailing_zeros == UTIL_LEAD_TRAIL_ZERO_SKIP)
			{
				break;
			}
			else if (trailing_zeros == UTIL_LEAD_TRAIL_ZERO_BLANK)
			{
				str[pos++] = digit + ' ';
				continue;
			}
		}

		if (significant)
		{
			str[pos++] = digit + '0';
			continue;
		}

		if (digit || i == decimal_places)
		{
			significant = true;
			str[pos++] = digit + '0';
			continue;
		}

		if (leading_zeros == UTIL_LEAD_TRAIL_ZERO_BLANK)
		{
			str[pos++] = ' ';
			continue;
		}

		number_of_digits--;
	}
	str[pos] = '\0';
	return pos;
}



char _UTIL_UnitPrefixChar(int8_t order)
{
	if (order < -3) return 'u';
	if (order < 0) return 'm';
	if (order < 3) return ' ';
	if (order < 6) return 'K';
	return 'M';
}

char _UTIL_UnitPrefix(int8_t order)
{
	if (order < -3) return -6;
	if (order < 0) return -3;
	if (order < 3) return 0;
	if (order < 6) return 3;
	return 6;
}

uint8_t UTIL_UIntToStrEngineering(char *str, uint32_t value, UTIL_DigitsTypeDef counts, uint8_t scaler, UTIL_LeadTrailZeroTypeDef leading_zeros)
{
	uint32_t tmp;
	int8_t value_digits;
	int8_t target_digits;
	int8_t div_counter;
	int8_t decimal_places;
	int8_t mod;
	int8_t exp;
	int8_t prefix;
	uint8_t pos;

	// Calculate the number of digits in the target format
	target_digits = UTIL_NumberOfDigitsUInt(counts);

	// Handle possible overflow for given counts
	mod = 0;
	div_counter = 0;
	while (value > counts)
	{
		tmp = value / 10;
		mod = value % 10; // Should hopefully be optimized by gcc
		value = tmp;
		div_counter++;
	}
	if (mod >= 5)
	{
		value++;
	}

	// Determine prefix
	value_digits = UTIL_NumberOfDigitsUInt(value * UTIL_Power(10, div_counter));
	exp = (value_digits - 1 - scaler);
	prefix = _UTIL_UnitPrefix(exp);

	decimal_places = scaler - div_counter + prefix;

	// Now the conversion can be run. Keep the number of characters written
	// in memory for later use
	pos = UTIL_UIntToStr(str, value, target_digits, decimal_places, leading_zeros, UTIL_LEAD_TRAIL_ZERO_ZERO);

	// Add unit prefix to string
	str[pos++] = _UTIL_UnitPrefixChar(exp);
	str[pos] = '\0';

	return pos;
}


uint32_t UTIL_DigitArrayToUInt(uint8_t *digits, uint8_t length)
{
	uint32_t result = 0;
	for (uint8_t i = 0; i < length; i++)
	{
		result = result * 10 + digits[i];
	}
	return result;
}

uint8_t UTIL_NumberOfDigitsUInt(uint32_t number)
{
	// for int32_t: if (number < 0) number = (number == INT_MIN) ? INT_MAX : -number;
	if (number < 10) return 1;
	if (number < 100) return 2;
	if (number < 1000) return 3;
	if (number < 10000) return 4;
	if (number < 100000) return 5;
	if (number < 1000000) return 6;
	if (number < 10000000) return 7;
	if (number < 100000000) return 8;
	if (number < 1000000000) return 9;
	return 10;
}

uint8_t UTIL_MostSignificantDigitUint(uint32_t number)
{
	uint8_t digits = UTIL_NumberOfDigitsUInt(number);
	uint32_t sub = conversion_array[digits - 1];
	uint8_t msd;

	for (msd = 0; number >= sub; msd++, number -= sub);

	return msd;
}

uint8_t UTIL_DigitAt(uint32_t number, uint8_t order)
{
	uint8_t digit = 0;
	uint8_t start_digit;

	if (number < conversion_array[order])
	{
		return 0;
	}

	start_digit = UTIL_NumberOfDigitsUInt(number);

	for (int8_t i = start_digit; i >= 0 && i >= order; i--)
	{
		digit = 0;
		while (number >= conversion_array[i])
		{
			number -= conversion_array[i];
			digit++;
		}
	}

	return digit;
}


int32_t UTIL_DivRoundClosestInt32(const int32_t n, const int32_t d)
{
	return (int32_t) UTIL_DivRoundClosestInt64(n, d);
}


int64_t UTIL_DivRoundClosestInt64(const int64_t n, const int64_t d)
{
    int32_t rawResult = n / d;
    int32_t remainder = n % d;

    if ((remainder >= 0 && 2 * remainder >= d) || (remainder < 0 && 2 * remainder <= d))
	{
        if (n >= 0)
		{			
            rawResult++;
		}
        else
		{
            rawResult--;
		}
    }

    return rawResult;
}


int32_t UTIL_RoundToInt32(double number)
{
	return (int32_t) (number < 0 ? number - 0.5 : number + 0.5);
}


uint32_t UTIL_Power(uint32_t base, uint32_t exp)
{
    if (exp == 0) {
        return 1;
    }

    uint32_t result = 1;

    while (exp > 0) {
        if (exp & 1) {
            result *= base;
        }
        base *= base;
        exp >>= 1;
    }

    return result;
}

uint64_t UTIL_PowerUInt64(uint64_t base, uint64_t exp)
{
    if (exp == 0) {
        return 1;
    }

    uint64_t result = 1;

    while (exp > 0) {
        if (exp & 1) {
            result *= base;
        }
        base *= base;
        exp >>= 1;
    }

    return result;
}


uint8_t UTIL_FindClosestIndex(uint32_t *array, uint8_t length, uint32_t value)
{
	uint8_t index = 0;
	uint32_t current = array[0];
	uint32_t abs_array;
	uint32_t abs_current;

	for (uint8_t i = 0; i < length; i++)
	{
		abs_array = value > array[i] ? value - array[i] : array[i] - value;
		abs_current = value > current ? value - current : current - value;
		if (abs_array < abs_current)
		{
			current = array[i];
			index = i;
		}
	}

	return index;
}


char *UTIL_StrInsertChar(char *target, const char *source, const char insert, uint8_t pos)
{
	memcpy(target, source, pos);
	target[pos] = insert;
	target[pos + 1] = '\0';
	strcat(target, source + pos);
	return target;
}


char *UTIL_StrInsert(char *target, const char *source, const char *insert, uint8_t pos)
{
	strncpy(target, source, pos);
	strcat(target, insert);
	strcat(target, source + pos);
	return target;
}


uint8_t UTIL_StrLenDisplay(const char *str, uint8_t max_len)
{
	uint16_t i, len;

	// Note: This implementation only works for simple cases
	// where there are no two (or more) consecutive '.' or ':')
	for (i = 0, len = 0; i < max_len && str[i] != '\0'; i++)
	{
		len += (str[i] != '.' && str[i] != ':');
	}
	return len;
}


char *UTIL_StrNumberRemoveLeadingZeros(char *target, const char *source)
{
	uint8_t pos = 0;
	while (source[pos] == '0' && source[pos + 1] == '0')
	{
		pos++;
	}
	strcpy(target, source + pos);
	return target;
}


char *UTIL_StrNumberRemoveTrailingZeros(char *target, const char *source)
{
	bool decimal = false;
	bool consecutive = true;
	bool k = false;
	int8_t pos = strlen(source) - 1;
	uint8_t marker = pos + 1;

	if (source[pos] == 'K')
	{
		k = true;
		marker--;
		pos--;
	}

	while (pos >= 0)
	{
		if (source[pos] == '.')
		{
			decimal = true;
			break;
		}

		if (consecutive && source[pos] == '0')
		{
			marker = pos;
		}
		else
		{
			consecutive = false;
		}

		pos--;
	}

	if (decimal)
	{
		if (marker > 0 && source[marker - 1] == '.')
		{
			marker--;
		}

		memcpy(target, source, marker);
		//marker++;
		if (k)
		{
			target[marker] = 'K';
			marker++;
		}
		target[marker] = '\0';
	}
	else
	{
		memcpy(target, source, strlen(source) + 1);
	}

	return target;
}

