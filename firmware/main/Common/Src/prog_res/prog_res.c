/**
 * @file    prog_res.c
 * @author  Sebastian Harnisch
 * @date    16.10.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "hardware/relay_def.h"
#include "prog_res/prog_res.h"
#include "util/util.h"
#include <string.h>

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

int8_t _PRES_HighestNonZeroDecade(PRES_TypeDef *pres);
void _PRES_OpenAllRelays(PRES_TypeDef *pres);
void _PRES_CloseSelectedRelays(DEC_TypeDef *dec);
static PRES_Setpoint_TypeDef _PRES_CalcHardwareSetpointRec(PRES_TypeDef *pres,
											  	     uint32_t next_setpoint,
													 int32_t resistance_left,
													 uint32_t accumulator,
													 uint8_t order,
													 CAL_Mode_TypeDef cal_mode);

/* Exported functions --------------------------------------------------------*/

//----------- Apply calibration


API_StatusTypeDef PRES_UpdateCalibration(PRES_TypeDef *progres, volatile CALDATA_TypeDef *cal_data)
{
	if (CAL_ValidateAll(cal_data) != API_OK)
	{
		return API_ERROR;
	}

	for (uint8_t decade = 0; decade < PRES_DEC_COUNT; decade++)
	{
		for (uint8_t resistance = 0; resistance < DEC_RES_COUNT; resistance++)
		{
			int8_t setup = CAL_ConvertToSetup(decade, resistance);
			progres->decades[decade].resistances[resistance].calibrated_2w = cal_data->CAL_VAL_2W[setup];
			progres->decades[decade].resistances[resistance].calibrated_4w = cal_data->CAL_VAL_4W[setup];
		}
	}

	return API_OK;
}



//----------- Calculate resistance


uint32_t PRES_CalcMinimumResistance(PRES_TypeDef *pres, CAL_Mode_TypeDef cal_mode)
{
	uint32_t min_resistance = 0;

	for (uint8_t i = 0; i < COUNT_OF(pres->decades); i++)
	{
		min_resistance += RES_GetResistance(&pres->decades[i].resistances[0], cal_mode);
	}

	return min_resistance;
}


uint32_t PRES_CalcMaximumResistance(PRES_TypeDef *pres, CAL_Mode_TypeDef cal_mode)
{
	uint32_t max_resistance = 0;

	for (uint8_t i = 0; i < COUNT_OF(pres->decades); i++)
	{
		max_resistance += RES_GetResistance(&pres->decades[i].resistances[COUNT_OF(pres->decades[0].resistances) - 1],
											cal_mode);
	}

	return max_resistance;
}


API_StatusTypeDef PRES_CalcActualResistanceFromSetpoint(PRES_TypeDef *pres, uint32_t *result, uint32_t setpoint,
		CAL_Mode_TypeDef cal_mode_setpoint_calc, CAL_Mode_TypeDef cal_mode_resistance_calc)
{
	PRES_Setpoint_TypeDef hw_setpoint;

	_PRES_CalcHardwareSetpoint(pres, &hw_setpoint, setpoint, cal_mode_setpoint_calc);
	_PRES_CalcActualResistanceFromHWSetpoint(pres, result, hw_setpoint.hw_setpoint, cal_mode_resistance_calc);

	return API_OK;
}


API_StatusTypeDef PRES_SetSetpoint(PRES_TypeDef *pres, uint32_t setpoint, CAL_Mode_TypeDef cal_mode)
{
	if (_PRES_CalcHardwareSetpoint(pres, &pres->current_setpoint, setpoint, cal_mode) != API_OK)
	{
		return API_ERROR;
	}

	return _PRES_ApplyHardwareSetpointByInt(pres, pres->current_setpoint.hw_setpoint);
}


API_StatusTypeDef PRES_SwitchSimple(PRES_TypeDef *pres, bool use_bypass)
{
	int8_t highest_non_zero_decade;
	bool bypass_available;
	uint8_t decades_to_set;

	// Open all relays
	_PRES_OpenAllRelays(pres);

	// Determine the highest non-zero decade; for resistance 0 the function returns -1.
	// However, regarding bypassing this case should be handled as if was 0.
	highest_non_zero_decade = _PRES_HighestNonZeroDecade(pres);
	if (highest_non_zero_decade < 0)
	{
		highest_non_zero_decade = 0;
	}

	// Check whether a bypass is available
	bypass_available = highest_non_zero_decade >= 0 && pres->decades[highest_non_zero_decade].relay_bypass != NULL;

	if (use_bypass && bypass_available)
	{
		// Set bypass relay
		pres->decades[highest_non_zero_decade].relay_bypass->state = RLY_CLOSED;

		// All higher decades' relays don't have to be set if a bypass is active
		decades_to_set = highest_non_zero_decade + 1;
	}
	else
	{
		// If no bypass is available all higher decades have to be active no matter what
		decades_to_set = PRES_DEC_COUNT;
	}

	// Set the relays according to the selected resistances,
	// but don't set the decades above the highest non zero decade
	// because those will be bypassed if such a bypass relay is available
	for (uint8_t d = 0; d < decades_to_set; d++)
	{
		_PRES_CloseSelectedRelays(&pres->decades[d]);
	}

	// Transmit the new state
	if (pres->_requestRelayControl != NULL)
	{
		pres->_requestRelayControl(pres);
	}

	return API_OK;
}


API_StatusTypeDef PRES_SwitchOff(PRES_TypeDef *pres)
{
	_PRES_OpenAllRelays(pres);
	return API_OK;
}


uint32_t PRES_CalcIMax(PRES_TypeDef *pres)
{
	if (pres->current_setpoint.hw_setpoint == 0)
	{
		return pres->max_short_circuit_current;
	}

	int8_t highest_dec = _PRES_HighestNonZeroDecade(pres);
	uint8_t digit = pres->current_setpoint.hw_setpoint_digits[highest_dec];

	uint32_t i = pres->decades[highest_dec].resistances[digit].i_factor * pres->decades[highest_dec].i_0; // µA

	// Now factor in the maximum voltage of the decade
	uint32_t i_max = ((uint64_t)pres->max_voltage) / pres->current_setpoint.hw_setpoint;

	return MIN(i, i_max);
}

uint32_t PRES_CalcUMax(PRES_TypeDef *pres)
{
	uint64_t i_max = PRES_CalcIMax(pres); // µA
	uint64_t r = pres->current_setpoint.hw_setpoint; // Ohm

	return UTIL_DivRoundClosestInt64(r * i_max, 1000UL); // mV
}

uint32_t PRES_CalcPMax(PRES_TypeDef *pres)
{
	uint64_t i_max = PRES_CalcIMax(pres);
	uint64_t r = pres->current_setpoint.hw_setpoint; // Ohm

	return (uint32_t) UTIL_DivRoundClosestInt64((r * i_max) * i_max, 1000000000UL); // mW
}


/* Private functions ---------------------------------------------------------*/


int8_t _PRES_HighestNonZeroDecade(PRES_TypeDef *pres)
{
	int8_t i;

	for (i = PRES_DEC_COUNT - 1; i >= 0 && pres->decades[i].next_selection == 0; i--);

	return i;
}


API_StatusTypeDef _PRES_CalcActualResistanceFromHWSetpointLegacy(PRES_TypeDef *pres, uint32_t *result, uint32_t hw_setpoint, CAL_Mode_TypeDef cal_mode)
{
	uint8_t digit_array[COUNT_OF(pres->decades)];
	*result = 0;

	if (hw_setpoint >= PRES_RES_VALUE_COUNT)
	{
		return API_ERROR;
	}

	UTIL_UIntToDigitArray(PRES_DEC_COUNT, digit_array, hw_setpoint, false);

	for (uint8_t decade = 0; decade < COUNT_OF(pres->decades); ++decade)
	{
		*result += RES_GetResistance(&pres->decades[decade].resistances[digit_array[COUNT_OF(pres->decades) - 1 - decade]], cal_mode);
	}

	return API_OK;
}


API_StatusTypeDef _PRES_CalcActualResistanceFromHWSetpoint(PRES_TypeDef *pres, uint32_t *result, uint32_t hw_setpoint, CAL_Mode_TypeDef cal_mode)
{
	uint8_t digit_array[COUNT_OF(pres->decades)];
	*result = 0;

	if (hw_setpoint >= PRES_RES_VALUE_COUNT)
	{
		return API_ERROR;
	}

	UTIL_UIntToDigitArray(PRES_DEC_COUNT, digit_array, hw_setpoint, false);

	// Calibration values describe the effective resistance of a decade in each setting.
	// The taps after the one of the first three decades (that help to reduce contact resistance)
	// are not considered in those values.

	// Determine the highest non zero decade
	int8_t highest_nzdec = 0;
	while (highest_nzdec < COUNT_OF(pres->decades) && digit_array[highest_nzdec] == 0)
	{
		highest_nzdec++;
	}
	highest_nzdec = COUNT_OF(pres->decades) - 1 - highest_nzdec;

	if (highest_nzdec < 0)
	{
		highest_nzdec = 0;
	}

	// Determine which decades to iterate over in order to calculate the resistance.
	// Also, consider the contact resistance of an intermediate tap, if required.
	int8_t max_dec;
	if (highest_nzdec < PRES_NUMBER_INTERMEDIATE_TAPS)
	{
		// Initialize the result with the contact resistance of the intermediate tap
		*result = RES_GetResistance(&pres->decades[0].resistances[0], cal_mode) / 2;
		max_dec = highest_nzdec;
	}
	else
	{
		max_dec = COUNT_OF(pres->decades) - 1;
	}

	for (uint8_t decade = 0; decade <= max_dec; ++decade)
	{
		*result += RES_GetResistance(&pres->decades[decade].resistances[digit_array[COUNT_OF(pres->decades) - 1 - decade]], cal_mode);
	}

	return API_OK;
}



API_StatusTypeDef _PRES_CalcHardwareSetpoint(PRES_TypeDef *pres, PRES_Setpoint_TypeDef *result, uint32_t setpoint, CAL_Mode_TypeDef cal_mode)
{
	if (setpoint > PRES_CalcMaximumResistance(pres, cal_mode))
	{
		return API_ERROR;
	}

	*result = _PRES_CalcHardwareSetpointRec(pres, setpoint, setpoint, 0, PRES_DEC_COUNT - 1, cal_mode);

	return API_OK;
}


/** Method to calculate the optimal hardware setpoint recursively
 *
 */
static PRES_Setpoint_TypeDef _PRES_CalcHardwareSetpointRec(PRES_TypeDef *pres,
													 uint32_t next_setpoint,
													 int32_t resistance_left,
													 uint32_t accumulator,
													 uint8_t order,
													 CAL_Mode_TypeDef cal_mode)
{
	PRES_Setpoint_TypeDef result;
	DEC_TypeDef *dec = &pres->decades[order];

	memset(&result, 0, sizeof(result));

	if (order <= 0)
	{
		// Arrived at the lowest decade. At that point, there is not much choice, because
		// errors in this decade's resistances can't be corrected -- there simply are no
		// lower resistance values

		if (resistance_left < 0)
		{
			resistance_left = 0;
		}

		uint8_t closest_index = DEC_FindClosestCalibratedResistance(dec, resistance_left, cal_mode);

		result.actual_resistance = accumulator + RES_GetResistance(&dec->resistances[closest_index], cal_mode);
		result.hw_setpoint = closest_index;
		result.hw_setpoint_digits[order] = closest_index;
		return result;
	}

	if (resistance_left <= 0)
	{
		// The upper decades are sufficient to match or exceed the specified setpoint. Then
		// the setpoints of all lower decades would be 0.
		// So sum up and add all residual resistances (i. e. resistances for setpoint 0)
		for (int8_t d = 0 ; d < order; d++)
		{
			accumulator += RES_GetResistance(&pres->decades[d].resistances[0], cal_mode);
		}
		result.actual_resistance = accumulator;
		result.hw_setpoint = 0;
		result.hw_setpoint_digits[order] = 0;
		return result;
	}

	// If the exit conditions above are not met, the resistor selection process starts.
	//
	// There are 10 options--10 resistors to choose from. As we'll see, we can drastically
	// reduce the number of options to not more than two per cycle, which increases the
	// performance significantly.
	//
	// In many cases it's actually best to select the digit at the respective position.
	// Examples:
	// - order=5, resistance_left=123,456k => 1 (meaning "Resistor with the value 1*10^order")
	// - order=4, resistance_left=123,456k => 2 (2*10^order)
	// - order=0, resistance_left=001,234k => 4 (4*10^order)
	// - and so on.
	// The result value is stored in the digit_check variable.
	//
	// However, for a `resistance_left` value of e. g. 100,000k one could easily imagine cases
	// where the actual ("calibrated") resistance value of the 100k resistor is slightly above
	// or below this resistance_left value, e. g. 99,900k.
	// Then it might be possible to maximize accuracy by not selecting the 100k resistor, but
	// instead the 90k, 9k, and 900 Ohm resistor. So sometimes there is one other value that
	// is worth checking out. This value, also stored in the digit_check variable, can be
	// determined fairly easily, as is done below.

	// In some cases we might end up with a resistance_left value of more than what this and
	// the other decades left can provide, e. g. we ask for 99,900k, but actually get 100,100k
	// (calibrated). For order=4 (the most significant digit of the requested value), we would
	// still query the resistance_left variable for the digit at the same position and get 0--
	// hence introducing a significant error.

	uint8_t digits_check[2];

	digits_check[0] = UTIL_DigitAt(resistance_left, order + 3);
	digits_check[1] = 0xFF; 									// 0xFF => Don't check later on
	if (resistance_left > UTIL_Power(10, order + 3 + 1) - 1)
	{
		// So in such a case, the best thing we can do *with the previous selection* is to
		// maximize the resistance by effectively choosing 9.
		digits_check[0] = 9;
	}
	else
	{
		uint8_t digit_after = UTIL_DigitAt(resistance_left, order + 3 - 1);

		if (digits_check[0] == 0)
		{
			if (digit_after >= 9)
			{
				digits_check[1] = 1;
			}
		}
		else if (digits_check[0] == 9)
		{
			if (digit_after <= 1)
			{
				digits_check[1] = 8;
			}
		}
		else
		{
			if (digit_after == 0)
			{
				digits_check[1] = digits_check[0] - 1;
			}
			else if (digit_after == 9)
			{
				digits_check[1] = digits_check[0] + 1;
			}
		}
	}

	PRES_Setpoint_TypeDef sub_result[2];
	memset(sub_result, 0, sizeof(sub_result));

	// Now we know which digits to check. It's time to check the first of the options
	// (again: there might be one or two options).
	uint32_t resistance = RES_GetResistance(&dec->resistances[digits_check[0]], cal_mode);
	sub_result[0] = _PRES_CalcHardwareSetpointRec(pres,
										    next_setpoint,
										    resistance_left - resistance,
										    accumulator + resistance,
										    order - 1,
										    cal_mode);

	// It can very well be that the second selected value is way larger than what we
	// need, so we should disregard this value without further processing.
	// The threshold applied can be adjusted. 1.05 ... 1.2 seems reasonable (here: >> 3 -> ~1.125)
	if (digits_check[1] != 0xFF)
	{
		resistance = RES_GetResistance(&dec->resistances[digits_check[1]], cal_mode);
		if (resistance <= (resistance_left + (resistance_left >> 3) ))
		{
			sub_result[1] = _PRES_CalcHardwareSetpointRec(pres,
												    next_setpoint,
												    resistance_left - resistance,
												    accumulator + resistance,
												    order - 1,
												    cal_mode);

			uint32_t abs_0 = next_setpoint > sub_result[0].actual_resistance ? next_setpoint - sub_result[0].actual_resistance : sub_result[0].actual_resistance - next_setpoint;
			uint32_t abs_1 = next_setpoint > sub_result[1].actual_resistance ? next_setpoint - sub_result[1].actual_resistance : sub_result[1].actual_resistance - next_setpoint;

			uint8_t closest_index = abs_0 > abs_1;

			result.actual_resistance = sub_result[closest_index].actual_resistance;
			result.hw_setpoint = UTIL_Power(10, order) * digits_check[closest_index] + sub_result[closest_index].hw_setpoint;
			memcpy(&result.hw_setpoint_digits, &sub_result[0].hw_setpoint_digits, PRES_DEC_COUNT);
			result.hw_setpoint_digits[order] = digits_check[closest_index];

			return result;
		}
	}

	result.actual_resistance = sub_result[0].actual_resistance;
	result.hw_setpoint = UTIL_Power(10, order) * digits_check[0] + sub_result[0].hw_setpoint;
	memcpy(&result.hw_setpoint_digits, &sub_result[0].hw_setpoint_digits, PRES_DEC_COUNT);
	result.hw_setpoint_digits[order] = digits_check[0];

	return result;
}


API_StatusTypeDef _PRES_ApplyHardwareSetpointByInt(PRES_TypeDef *pres, uint32_t hw_setpoint)
{
	uint8_t digit_array[COUNT_OF(pres->decades)];

	if (hw_setpoint > PRES_RES_VALUE_COUNT - 1)
	{
		return API_ERROR;
	}

	//pres->next_hw_setpoint = hw_setpoint;

	UTIL_UIntToDigitArray(COUNT_OF(pres->decades), digit_array, hw_setpoint, false);

	for (uint8_t decade = 0; decade < COUNT_OF(pres->decades); ++decade)
	{
		pres->decades[COUNT_OF(pres->decades) - 1 - decade].next_selection = digit_array[decade];
	}

	return API_OK;
}


void _PRES_OpenAllRelays(PRES_TypeDef *pres)
{
	// Set all relays to open
	DEC_TypeDef *dec;
	RES_TypeDef *res;
	for (uint8_t i = 0; i < PRES_DEC_COUNT; i++)
	{
		dec = &pres->decades[i];
		if (dec->relay_bypass != NULL)
		{
			dec->relay_bypass->state = RLY_OPEN;
		}

		for (uint8_t j = 0; j < DEC_RES_COUNT; j++)
		{
			res = &dec->resistances[j];
			res->relay_tap->state = RLY_OPEN;
			if (res->relay_not_plus_one != NULL)
			{
				res->relay_not_plus_one->state = RLY_OPEN;
			}
		}
	}
}


void _PRES_CloseSelectedRelays(DEC_TypeDef *dec)
{
	RES_TypeDef *sel_res;

	sel_res = &dec->resistances[dec->next_selection];

	sel_res->relay_tap->state = RLY_CLOSED;
	if (sel_res->relay_not_plus_one != NULL)
	{
		sel_res->relay_not_plus_one->state = RLY_CLOSED;
	}
}


//----------- Legacy functions


API_StatusTypeDef PRES_CalcHardwareSetpointUncal(PRES_TypeDef *pres, PRES_Setpoint_TypeDef *result, uint32_t setpoint, CAL_Mode_TypeDef cal_mode)
{
	PRES_Setpoint_TypeDef hw_sp;

	uint32_t m = setpoint % OHM;
	uint32_t d = setpoint / OHM;

	hw_sp.hw_setpoint = (m >= (OHM / 2)) ? d + 0 : d;

	if (hw_sp.hw_setpoint > PRES_RES_VALUE_COUNT - 1)
	{
		hw_sp.hw_setpoint = PRES_RES_VALUE_COUNT - 1;
	}

	UTIL_UIntToDigitArray(COUNT_OF(pres->decades), hw_sp.hw_setpoint_digits, hw_sp.hw_setpoint, false);

	_PRES_CalcActualResistanceFromHWSetpoint(pres, &hw_sp.actual_resistance, hw_sp.hw_setpoint, cal_mode);

	*result = hw_sp;

	return API_OK;
}


API_StatusTypeDef PRES_SetHardwareSetpoint(PRES_TypeDef *pres, uint8_t *hw_setpoint_digits)
{
	//pres->next_hw_setpoint = UTIL_DigitArrayToUInt(hw_setpoint_digits, COUNT_OF(pres->decades));

	for (uint8_t decade = 0; decade < COUNT_OF(pres->decades); ++decade)
	{
		pres->decades[COUNT_OF(pres->decades) - 1 - decade].next_selection = hw_setpoint_digits[decade];
	}

	return API_OK;
}


API_StatusTypeDef PRES_ApplySetpointUncal(PRES_TypeDef *pres, uint32_t setpoint, CAL_Mode_TypeDef cal_mode)
{
	if (PRES_CalcHardwareSetpointUncal(pres, &pres->current_setpoint, setpoint, cal_mode) != API_OK)
	{
		return API_ERROR;
	}

	return _PRES_ApplyHardwareSetpointByInt(pres, pres->current_setpoint.hw_setpoint);
}
