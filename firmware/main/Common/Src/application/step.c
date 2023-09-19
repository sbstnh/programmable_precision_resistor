/**
 * @file    step.c
 * @author  sebas
 * @date    03.12.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "application/step.h"
#include "util/util.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

static const int32_t LDEC_Sequence[] =
{
		1, 2, 3, 4, 5, 6, 7, 8, 9
};

static const int32_t L125_Sequence[] =
{
		1, 2, 5
};

static const int32_t L13_Sequence[] =
{
		1, 3
};

/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

int32_t _STEP_CalculateUpLinear(LEV_STEP_TypeDef *step, INT_VALUE_TypeDef value);
int32_t _STEP_CalculateDownLinear(LEV_STEP_TypeDef *step, INT_VALUE_TypeDef value);
int32_t STEP_CalculateUpDec(LEV_STEP_TypeDef *step, INT_VALUE_TypeDef value);
int32_t STEP_CalculateDownDec(LEV_STEP_TypeDef *step, INT_VALUE_TypeDef value);
int32_t _STEP_CalculateUpL(LEV_STEP_TypeDef *step, INT_VALUE_TypeDef value, const int32_t *sequence, uint8_t sequence_length);
int32_t _STEP_CalculateDownL(LEV_STEP_TypeDef *step, INT_VALUE_TypeDef value, const int32_t *sequence, uint8_t sequence_length);

int32_t _STEP_ApplyOverflowLogic(LEV_STEP_TypeDef *step, INT_VALUE_TypeDef value, int32_t new_value);

/* Exported functions --------------------------------------------------------*/

int32_t STEP_CalculateUp(LEV_STEP_TypeDef *step, INT_VALUE_TypeDef value)
{
	int32_t result;

	switch (step->MODE)
	{
		default:
		case STEP_MODE_LINear:
			result = _STEP_CalculateUpLinear(step, value);
			break;

		case STEP_MODE_LDECade:
			result = _STEP_CalculateUpL(step, value, LDEC_Sequence, COUNT_OF(LDEC_Sequence));
			break;

		case STEP_MODE_L125:
			result = _STEP_CalculateUpL(step, value, L125_Sequence, COUNT_OF(L125_Sequence));
			break;

		case STEP_MODE_L13:
			result = _STEP_CalculateUpL(step, value, L13_Sequence, COUNT_OF(L13_Sequence));
			break;
	}

	return _STEP_ApplyOverflowLogic(step, value, result);
}


int32_t STEP_CalculateDown(LEV_STEP_TypeDef *step, INT_VALUE_TypeDef value)
{
	int32_t result;

	switch (step->MODE)
	{
		default:
		case STEP_MODE_LINear:
			result = _STEP_CalculateDownLinear(step, value);
			break;

		case STEP_MODE_LDECade:
			result = _STEP_CalculateDownL(step, value, LDEC_Sequence, COUNT_OF(LDEC_Sequence));
			break;

		case STEP_MODE_L125:
			result = _STEP_CalculateDownL(step, value, L125_Sequence, COUNT_OF(L125_Sequence));
			break;

		case STEP_MODE_L13:
			result = _STEP_CalculateDownL(step, value, L13_Sequence, COUNT_OF(L13_Sequence));
			break;
	}

	return _STEP_ApplyOverflowLogic(step, value, result);
}

/* Private functions ---------------------------------------------------------*/


// TODO: Those methods currently only work for positive values!

int32_t _STEP_CalculateUpLinear(LEV_STEP_TypeDef *step, INT_VALUE_TypeDef value)
{
	return value.value + step->INCRement.value;
}

int32_t _STEP_CalculateDownLinear(LEV_STEP_TypeDef *step, INT_VALUE_TypeDef value)
{
	return value.value - step->INCRement.value;
}

int32_t _STEP_CalculateUpL(LEV_STEP_TypeDef *step, INT_VALUE_TypeDef value, const int32_t *sequence, uint8_t sequence_length)
{
	bool not_found = true;
	int64_t result = 0;
	for (int8_t j = 0; j <= 9 && not_found; j++)
	{
		for (int8_t i = 0; i < sequence_length; i++)
		{
			result = (int64_t)conversion_array[j] * sequence[i];
			if (result > value.value)
			{
				not_found = false;
				break;
			}
		}
	}

	return not_found ? value.max : result;
}

int32_t _STEP_CalculateDownL(LEV_STEP_TypeDef *step, INT_VALUE_TypeDef value, const int32_t *sequence, uint8_t sequence_length)
{
	bool not_found = true;
	int64_t result = 0;
	for (int8_t j = 9; j >= 0 && not_found; j--)
	{
		for (int8_t i = sequence_length - 1; i >= 0; i--)
		{
			result = (int64_t)conversion_array[j] * sequence[i];
			if (result < value.value)
			{
				not_found = false;
				break;
			}
		}
	}

	return not_found ? value.min : result;
}


int32_t _STEP_ApplyOverflowLogic(LEV_STEP_TypeDef *step, INT_VALUE_TypeDef value, int32_t new_value)
{
	switch (step->OVERflow)
	{
		default:
		case STEP_OVER_LIMit:
			return LIM(value.min, value.max, new_value);

		case STEP_OVER_STAY:
			if (!IN_RANGE(value.min, value.max, new_value))
			{
				return LIM(value.min, value.max, value.value);
			}
			return LIM(value.min, value.max, new_value);

		case STEP_OVER_RESet:
			if (new_value > value.max)
			{
				return value.min;
			}

			if (new_value < value.min)
			{
				return value.max;
			}
			return LIM(value.min, value.max, new_value);
	}
}
