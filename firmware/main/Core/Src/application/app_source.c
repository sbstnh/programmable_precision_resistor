/**
 * @file    app_source.c
 * @author  sebas
 * @date    03.12.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "util/util.h"

#include "application/app_input.h"
#include "application/app_memory.h"
#include "application/app_source.h"
#include "application/app_trigger.h"
#include "application/step.h"

#include "prog_res/prog_res_def.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/


// --------------- For SOURce.Current subsystem

INT_VALUE_TypeDef APP_Get_SourceCurrentLevelImmediateAmplitude()
{
	return APP.SOURce.CURRent.LEVel.IMMediate.AMPLitude;
}


// --------------- For SOURce.DIGital subsystem

bool APP_Get_SourceDigitalPinData(uint8_t pin)
{
	if (pin == SOUR_DIG_PIN1)
	{
		return _APP_UTIL_IoPin1();
	}

	return _APP_UTIL_IoPin2();
}


PIN_FUNCtion_TypeDef APP_Get_SourceDigitalPinFunction(uint8_t pin)
{
	return APP.SOURce.DIGital.PIN[pin].FUNCtion;
}

PIN_FUNCtion_TypeDef APP_Get_SourceDigitalPin1Function()
{
	return APP_Get_SourceDigitalPinFunction(SOUR_DIG_PIN1);
}

PIN_FUNCtion_TypeDef APP_Get_SourceDigitalPin2Function()
{
	return APP_Get_SourceDigitalPinFunction(SOUR_DIG_PIN2);
}

API_StatusTypeDef APP_Set_SourceDigitalPinFunctionSave(uint8_t pin, PIN_FUNCtion_TypeDef function, bool save)
{
	if (!IN_RANGE(SOUR_DIG_PIN1, SOUR_DIG_PIN2, pin))
	{
		return API_PARAM_OUT_OF_RANGE;
	}

	if (function >= PIN_FUNC_DINPut && function <= PIN_FUNC_TINPut)
	{
		APP.SOURce.DIGital.PIN[pin].FUNCtion = function;

		if (save)
		{
			return APP_Run_MemorySaveInstData();
		}

		return API_OK;
	}

	return API_ERROR;
}

API_StatusTypeDef APP_Set_SourceDigitalPinFunction(uint8_t pin, PIN_FUNCtion_TypeDef function)
{
	return APP_Set_SourceDigitalPinFunctionSave(pin, function, true);
}

API_StatusTypeDef APP_Set_SourceDigitalPin1Function(PIN_FUNCtion_TypeDef function)
{
	return APP_Set_SourceDigitalPinFunction(SOUR_DIG_PIN1, function);
}

API_StatusTypeDef APP_Set_SourceDigitalPin2Function(PIN_FUNCtion_TypeDef function)
{
	return APP_Set_SourceDigitalPinFunction(SOUR_DIG_PIN2, function);
}


PIN_POLarity_TypeDef APP_Get_SourceDigitalPinPolarity(uint8_t ext)
{
	return APP.SOURce.DIGital.PIN[ext].POLarity;
}

PIN_POLarity_TypeDef APP_Get_SourceDigitalPin1Polarity()
{
	return APP_Get_SourceDigitalPinPolarity(SOUR_DIG_PIN1);
}

PIN_POLarity_TypeDef APP_Get_SourceDigitalPin2Polarity()
{
	return APP_Get_SourceDigitalPinPolarity(SOUR_DIG_PIN2);
}

API_StatusTypeDef APP_Set_SourceDigitalPinPolaritySave(uint8_t pin, PIN_POLarity_TypeDef polarity, bool save)
{
	if (!IN_RANGE(SOUR_DIG_PIN1, SOUR_DIG_PIN2, pin))
	{
		return API_PARAM_OUT_OF_RANGE;
	}

	if (polarity == PIN_POL_POSitive || polarity == PIN_POL_NEGative)
	{
		APP.SOURce.DIGital.PIN[pin].POLarity = polarity;

		if (save)
		{
			return APP_Run_MemorySaveInstData();
		}

		return API_OK;
	}

	return API_ERROR;
}

API_StatusTypeDef APP_Set_SourceDigitalPinPolarity(uint8_t pin, PIN_POLarity_TypeDef polarity)
{
	return APP_Set_SourceDigitalPinPolaritySave(pin, polarity, true);
}

API_StatusTypeDef APP_Set_SourceDigitalPin1Polarity(PIN_POLarity_TypeDef polarity)
{
	return APP_Set_SourceDigitalPinPolarity(SOUR_DIG_PIN1, polarity);
}

API_StatusTypeDef APP_Set_SourceDigitalPin2Polarity(PIN_POLarity_TypeDef function)
{
	return APP_Set_SourceDigitalPinPolarity(SOUR_DIG_PIN2, function);
}

// --------------- For SOURce.LIST subsystem


API_StatusTypeDef APP_Run_SourceListInit()
{
	APP.SOURce.LIST.RESistance._DWELl_TimeLeft = 0;
	APP.SOURce.LIST.RESistance.INDex.value = 0;
	APP.SOURce.LIST.RESistance.RUN.NUMBer.value = 0;

	APP.SOURce.LIST._state = APP.SOURce.LIST.STARt.MODE == LIST_START_AUTO ?
			LIST_STATE_RUN :
			LIST_STATE_WAIT_FOR_TRIG;

	return API_OK;
}

API_StatusTypeDef APP_Get_SourceListResistanceLevelValues(int32_t pos, int32_t *value)
{
	// Check for invalid position
	if (!IN_RANGE(0, SOUR_LIST_LENGTH - 1, pos))
	{
		return API_PARAM_OUT_OF_RANGE;
	}

	*value = APP.SOURce.LIST.RESistance.LEVel.values[pos];

	return API_OK;
}

API_StatusTypeDef APP_Set_SourceListResistanceLevelValues(int32_t pos, int32_t value)
{
	// Check for invalid position
	if (!IN_RANGE(0, SOUR_LIST_LENGTH - 1, pos))
	{
		return API_PARAM_OUT_OF_RANGE;
	}

	// Check if equal
	RETURN_OK_IF_TRUE(APP.SOURce.LIST.RESistance.LEVel.values[pos] == value);

	// Check for value out of range
	if (!INT_VALUE_IN_RANGE(APP.SOURce.RESistance.LEVel.IMMediate.AMPLitude, value))
	{
		return API_PARAM_OUT_OF_RANGE;
	}

	APP.SOURce.LIST.RESistance.LEVel.values[pos] = value;

	return API_OK;
}


INT_VALUE_TypeDef APP_Get_SourceListResistanceLength()
{
	return APP.SOURce.LIST.RESistance.LEVel.length;
}

API_StatusTypeDef APP_Set_SourceListResistanceLength(int32_t length)
{
	// Check if equal
	RETURN_OK_IF_TRUE(APP.SOURce.LIST.RESistance.LEVel.length.value == length);

	// Check for value out of range
	if (!IN_RANGE(0, SOUR_LIST_LENGTH, length))
	{
		return API_PARAM_OUT_OF_RANGE;
	}

	if (!INT_VALUE_IN_RANGE(APP.SOURce.LIST.RESistance.LEVel.length, length))
	{
		return API_PARAM_OUT_OF_RANGE;
	}

	// Reposition index if list got shorter than the current index
	if (APP.SOURce.LIST.RESistance.INDex.value >= length)
	{
		APP.SOURce.LIST.RESistance.INDex.value = 0;
	}

	// Finally set length
	APP.SOURce.LIST.RESistance.LEVel.length.value = length;

	return API_OK;
}


INT_VALUE_TypeDef APP_Get_SourceListResistanceIndex()
{
	return APP.SOURce.LIST.RESistance.INDex;
}

API_StatusTypeDef APP_Set_SourceListResistanceIndex(int32_t index)
{
	// Check if equal
	RETURN_OK_IF_TRUE(APP.SOURce.LIST.RESistance.INDex.value == index);

	// Check for value out of range
	if (!IN_RANGE(0, APP.SOURce.LIST.RESistance.LEVel.length.value - 1, index))
	{
		return API_PARAM_OUT_OF_RANGE;
	}

	APP.SOURce.LIST.RESistance.INDex.value = index;

	return API_OK;
}


INT_VALUE_TypeDef APP_Get_SourceListResistanceRunNumber()
{
	return APP.SOURce.LIST.RESistance.RUN.NUMBer;
}


INT_VALUE_TypeDef APP_Get_SourceListResistanceRunCount()
{
	return APP.SOURce.LIST.RESistance.RUN.COUNt;
}

API_StatusTypeDef APP_Set_SourceListResistanceRunCount(int32_t count)
{
	// Check if equal
	RETURN_OK_IF_TRUE(APP.SOURce.LIST.RESistance.RUN.COUNt.value == count);

	// Check for value out of range
	if (!INT_VALUE_IN_RANGE(APP.SOURce.LIST.RESistance.RUN.COUNt, count))
	{
		return API_PARAM_OUT_OF_RANGE;
	}

	APP.SOURce.LIST.RESistance.RUN.COUNt.value = count;

	return API_OK;
}


API_StatusTypeDef APP_Get_SourceListResistanceDwellValues(int32_t pos, int32_t *value)
{
	// Check for invalid position
	if (!IN_RANGE(0, SOUR_LIST_LENGTH - 1, pos))
	{
		return API_PARAM_OUT_OF_RANGE;
	}

	*value = APP.SOURce.LIST.RESistance.DWELl.values[pos];

	return API_OK;
}

API_StatusTypeDef APP_Set_SourceListResistanceDwellValues(int32_t pos, int32_t value)
{
	// Check for invalid position
	if (!IN_RANGE(0, SOUR_LIST_LENGTH - 1, pos))
	{
		return API_PARAM_OUT_OF_RANGE;
	}

	// Check if equal
	RETURN_OK_IF_TRUE(APP.SOURce.LIST.RESistance.DWELl.values[pos] == value);

	// Check for value out of range
	// TODO: Add better handling
	if (!IN_RANGE(1, 1000000000, value))
	{
		return API_PARAM_OUT_OF_RANGE;
	}

	APP.SOURce.LIST.RESistance.DWELl.values[pos] = value;

	return API_OK;
}


API_StatusTypeDef APP_Set_SourceListResistanceDwellLength(int32_t length)
{
	// Check if equal
	RETURN_OK_IF_TRUE(APP.SOURce.LIST.RESistance.DWELl.length.value == length);

	// Check for value out of range
	if (!IN_RANGE(0, SOUR_LIST_LENGTH, length))
	{
		return API_PARAM_OUT_OF_RANGE;
	}

	if (!INT_VALUE_IN_RANGE(APP.SOURce.LIST.RESistance.DWELl.length, length))
	{
		return API_PARAM_OUT_OF_RANGE;
	}

	APP.SOURce.LIST.RESistance.DWELl.length.value = length;

	return API_OK;
}

INT_VALUE_TypeDef APP_Get_SourceListResistanceDwellLength()
{
	return APP.SOURce.LIST.RESistance.DWELl.length;
}


API_StatusTypeDef APP_Run_ListRun(bool triggered)
{
	if ((APP.SOURce.LIST.STEP == LIST_STEP_TRIGger || APP.SOURce.LIST.RESistance._DWELl_TimeLeft == 0)
			&& (APP.SOURce.LIST.STEP == LIST_STEP_AUTO || triggered))
	{
		// Check whether termination required
		if (APP.SOURce.LIST.RESistance.RUN.COUNt.value > 0 && APP.SOURce.LIST.RESistance.RUN.NUMBer.value >= APP.SOURce.LIST.RESistance.RUN.COUNt.value)
		{
			APP.SOURce.LIST._state = LIST_STATE_TERMINATE;
			return API_OK;
		}

		// Pre-Run checks, make sure that everything is fine even if values
		// are changed during List run
		if (APP.SOURce.LIST.RESistance.INDex.value >= APP.SOURce.LIST.RESistance.LEVel.length.value)
		{
			APP.SOURce.LIST.RESistance.INDex.value = 0;
		}

		// Update IMMediate value
		int32_t value = APP.SOURce.LIST.RESistance.LEVel.values[APP.SOURce.LIST.RESistance.INDex.value];
		if (APP_Set_SourceResistanceLevelImmediateAmplitude(value, false) != API_OK)
		{
			return API_ERROR;
		}

		// Check whether the output has to be enabled (depending on configuration, first run)
		if (APP.SOURce.LIST.RESistance.RUN.NUMBer.value == 0 &&
				APP.SOURce.LIST.RESistance.INDex.value == 0 &&
				APP.SOURce.LIST.STARt.INPut)
		{
			APP_Set_InputState(true);
		}

		// Determine and apply dwell time
		int32_t dwell_time = 0;
		if (_APP_UTIL_ListGetNextDwellTime(&dwell_time) != API_OK)
		{
			return API_ERROR;
		}

		APP.SOURce.LIST.RESistance._DWELl_TimeLeft = dwell_time;

		// Update counters
		APP.SOURce.LIST.RESistance.INDex.value++;
		if (APP.SOURce.LIST.RESistance.INDex.value >= APP.SOURce.LIST.RESistance.LEVel.length.value)
		{
			APP.SOURce.LIST.RESistance.INDex.value = 0;
			APP.SOURce.LIST.RESistance.RUN.NUMBer.value++;

			// Nothing further to do except for avoiding the overflow of the RUN.NUMB variable
			if (APP.SOURce.LIST.RESistance.RUN.NUMBer.value > APP.SOURce.LIST.RESistance.RUN.NUMBer.max ||
					APP.SOURce.LIST.RESistance.RUN.NUMBer.value < 0)
			{
				// Reset on "overflow"
				APP.SOURce.LIST.RESistance.RUN.NUMBer.value = 0;
			}
		}
	}
	else if (APP.SOURce.LIST.RESistance._DWELl_TimeLeft > 0)
	{
		APP.SOURce.LIST.RESistance._DWELl_TimeLeft--;
	}

	return API_OK;
}


bool APP_Get_SourceListStartInput()
{
	return APP.SOURce.LIST.STARt.INPut;
}

API_StatusTypeDef APP_Set_SourceListStartInput(bool input)
{
	APP.SOURce.LIST.STARt.INPut = input;

	return API_OK;
}


STARt_MODE_TypeDef APP_Get_SourceListStartMode()
{
	return APP.SOURce.LIST.STARt.MODE;
}

API_StatusTypeDef APP_Set_SourceListStartMode(STARt_MODE_TypeDef start)
{
	// Check for value out of range
	if (start >= LIST_START_AUTO && start <= LIST_START_TRIGger)
	{
		APP.SOURce.LIST.STARt.MODE = start;

		return API_OK;
	}

	return API_ERROR;
}

LIST_STEP_TypeDef APP_Get_SourceListStep()
{
	return APP.SOURce.LIST.STEP;
}

API_StatusTypeDef APP_Set_SourceListStep(LIST_STEP_TypeDef step)
{
	// Check for value out of range
	if (step >= LIST_STEP_AUTO && step <= LIST_STEP_ONCE)
	{
		APP.SOURce.LIST.STEP = step;

		return API_OK;
	}

	return API_ERROR;
}


API_StatusTypeDef APP_Run_ListTerminate()
{
	if (APP.SOURce.LIST.TERMinate.INPut)
	{
		// Input shall be disabled
		if (APP_Set_InputState(false) != API_OK)
		{
			return API_ERROR;
		}
	}

	if (!APP.SOURce.LIST.TERMinate.LAST)
	{
		// Restore previous IMMediate value
		if (APP_Run_SourceResistanceLevelImmediateAmplitudeFromBackup() != API_OK)
		{
			return API_ERROR;
		}
	}

	return API_OK;
}


bool APP_Get_SourceListTerminateLast()
{
	return APP.SOURce.LIST.TERMinate.LAST;
}

API_StatusTypeDef APP_Set_SourceListTerminateLast(bool last)
{
	APP.SOURce.LIST.TERMinate.LAST = last;

	return API_OK;
}


bool APP_Get_SourceListTerminateInput()
{
	return APP.SOURce.LIST.TERMinate.INPut;
}

API_StatusTypeDef APP_Set_SourceListTerminateInput(bool input)
{
	APP.SOURce.LIST.TERMinate.INPut = input;

	return API_OK;
}


// --------------- For SOURce.MODE subsystem

SOUR_MODE_TypeDef APP_Get_SourceMode()
{
	return APP.SOURce.MODE;
}

API_StatusTypeDef APP_Set_SourceMode(SOUR_MODE_TypeDef mode)
{
	RETURN_OK_IF_TRUE(APP.SOURce.MODE == mode);

	if (mode >= SOUR_MODE_TWIRe && mode <= SOUR_MODE_UNCalibrated)
	{
		APP.SOURce.MODE = mode;

		// TODO: Update Min/Max values according to calibration

		return _APP_UTIL_ApplyInput();
	}

	return API_ERROR;
}


// --------------- For SOURce.POWer subsystem

INT_VALUE_TypeDef APP_Get_SourcePowerLevelImmediateAmplitude()
{
	return APP.SOURce.POWer.LEVel.IMMediate.AMPLitude;
}


// --------------- For SOURce.RESistance.LEVel subsystem

INT_VALUE_TypeDef APP_Get_SourceResistanceLevelImmediateAmplitude()
{
	return APP.SOURce.RESistance.LEVel.IMMediate.AMPLitude;
}

API_StatusTypeDef APP_Set_SourceResistanceLevelImmediateAmplitudeForce(int32_t amplitude, bool backup_immediate)
{
	// Check for value out of range
	if (!INT_VALUE_IN_RANGE(APP.SOURce.RESistance.LEVel.IMMediate.AMPLitude, amplitude))
	{
		return API_PARAM_OUT_OF_RANGE;
	}

	// Limit value, if limit is active
	if (APP.SOURce.RESistance.LIMit.STATe)
	{
		amplitude = LIM(APP.SOURce.RESistance.LIMit.LOWer.value,
				        APP.SOURce.RESistance.LIMit.UPPer.value,
						amplitude);
	}

	// Now it's safe to set the new immediate value
	APP.SOURce.RESistance.LEVel.IMMediate.AMPLitude.value = amplitude;

	// Backup the last immediate value for termination of list operation
	if (backup_immediate)
	{
		APP.SOURce.LIST.RESistance._IMMediate_Backup = amplitude;
	}

	// Set immediate Value Conditionally
	return _APP_UTIL_ApplyInput();
}

API_StatusTypeDef APP_Run_SourceResistanceLevelImmediateAmplitudeFromBackup()
{
	return APP_Set_SourceResistanceLevelImmediateAmplitude(APP.SOURce.LIST.RESistance._IMMediate_Backup, true);
}

API_StatusTypeDef APP_Set_SourceResistanceLevelImmediateAmplitude(int32_t amplitude, bool backup_immediate)
{
	// Check if equal
	RETURN_OK_IF_TRUE(APP.SOURce.RESistance.LEVel.IMMediate.AMPLitude.value == amplitude);

	return APP_Set_SourceResistanceLevelImmediateAmplitudeForce(amplitude, backup_immediate);
}

API_StatusTypeDef APP_Run_SourceResistanceLevelImmediateAmplitudeMin(bool backup_immediate)
{
	return APP_Set_SourceResistanceLevelImmediateAmplitude(APP.SOURce.RESistance.LEVel.IMMediate.AMPLitude.min, true);
}

API_StatusTypeDef APP_Run_SourceResistanceLevelImmediateAmplitudeMax(bool backup_immediate)
{
	return APP_Set_SourceResistanceLevelImmediateAmplitude(APP.SOURce.RESistance.LEVel.IMMediate.AMPLitude.max, true);
}

API_StatusTypeDef APP_Run_SourceResistanceLevelImmediateAmplitudeUp(bool backup_immediate)
{
	int32_t immediate = STEP_CalculateUp((LEV_STEP_TypeDef *)&APP.SOURce.RESistance.LEVel.STEP, APP.SOURce.RESistance.LEVel.IMMediate.AMPLitude);

	return APP_Set_SourceResistanceLevelImmediateAmplitude(immediate, backup_immediate);
}

API_StatusTypeDef APP_Run_SourceResistanceLevelImmediateAmplitudeDown(bool backup_immediate)
{
	int32_t immediate = STEP_CalculateDown((LEV_STEP_TypeDef *)&APP.SOURce.RESistance.LEVel.STEP, APP.SOURce.RESistance.LEVel.IMMediate.AMPLitude);

	return APP_Set_SourceResistanceLevelImmediateAmplitude(immediate, backup_immediate);
}


API_StatusTypeDef APP_Run_SourceResistanceLevelImmediateCalculate(SOUR_MODE_TypeDef mode, int32_t *result)
{
	if (PRES_CalcActualResistanceFromSetpoint(&progres,
			(uint32_t *)result,
			APP.SOURce.RESistance.LEVel.IMMediate.AMPLitude.value,
			(CAL_Mode_TypeDef) APP.SOURce.MODE,
			(CAL_Mode_TypeDef) mode) != API_OK)
	{
		return API_ERROR;
	}

	return API_OK;
}


INT_VALUE_TypeDef APP_Get_SourceResistanceLevelTriggeredAmplitude()
{
	return APP.SOURce.RESistance.LEVel.TRIGgered.AMPLitude;
}

API_StatusTypeDef APP_Set_SourceResistanceLevelTriggeredAmplitude(int32_t amplitude)
{
	// Check for value out of range
	if (!INT_VALUE_IN_RANGE(APP.SOURce.RESistance.LEVel.TRIGgered.AMPLitude, amplitude))
	{
		return API_PARAM_OUT_OF_RANGE;
	}

	APP.SOURce.RESistance.LEVel.TRIGgered.AMPLitude.value = amplitude;

	return API_OK;
}

API_StatusTypeDef APP_Run_SourceResistanceLevelTriggeredCalculate(SOUR_MODE_TypeDef mode, int32_t *result)
{
	if (PRES_CalcActualResistanceFromSetpoint(&progres,
			(uint32_t *)result,
			APP.SOURce.RESistance.LEVel.TRIGgered.AMPLitude.value,
			(CAL_Mode_TypeDef) APP.SOURce.MODE,
			(CAL_Mode_TypeDef) mode) != API_OK)
	{
		return API_ERROR;
	}

	return API_OK;
}

volatile LEV_STEP_TypeDef *APP_Get_SourceResistanceLevelStep()
{
	return &APP.SOURce.RESistance.LEVel.STEP;
}


INT_VALUE_TypeDef APP_Get_SourceResistanceLevelStepIncrement()
{
	return APP.SOURce.RESistance.LEVel.STEP.INCRement;
}

API_StatusTypeDef APP_Set_SourceResistanceLevelStepIncrement(int32_t increment)
{
	return APP_UpdateIntValue(&APP.SOURce.RESistance.LEVel.STEP.INCRement, increment);
}


//API_StatusTypeDef APP_SetSourceResistanceLevelStepPDecade(int32_t points_per_decade)
//{
//	return APP_UpdateIntValue(&APP.SOURce.RESistance.LEVel.STEP.PDECade, points_per_decade);
//}


STEP_MODE_TypeDef APP_Get_SourceResistanceLevelStepMode()
{
	return APP.SOURce.RESistance.LEVel.STEP.MODE;
}

API_StatusTypeDef APP_Set_SourceResistanceLevelStepMode(STEP_MODE_TypeDef mode)
{
	if (mode >= STEP_MODE_LINear && mode <= STEP_MODE_L13)
	{
		APP.SOURce.RESistance.LEVel.STEP.MODE = mode;
		return API_OK;
	}
	return API_ERROR;
}


STEP_OVERflow_TypeDef APP_Get_SourceResistanceLevelStepOverflow()
{
	return APP.SOURce.RESistance.LEVel.STEP.OVERflow;
}

API_StatusTypeDef APP_Set_SourceResistanceLevelStepOverflow(STEP_OVERflow_TypeDef overflow)
{
	if (overflow >= STEP_OVER_LIMit && overflow <= STEP_OVER_RESet)
	{
		APP.SOURce.RESistance.LEVel.STEP.OVERflow = overflow;
		return API_OK;
	}
	return API_ERROR;
}


// --------------- For SOURce.RESistance.LIMit subsystem

INT_VALUE_TypeDef APP_Get_SourceResistanceLimitLower()
{
	return APP.SOURce.RESistance.LIMit.LOWer;
}

API_StatusTypeDef APP_Set_SourceResistanceLimitLower(int32_t lower)
{
	RETURN_OK_IF_TRUE(APP.SOURce.RESistance.LIMit.LOWer.value == lower);

	// Check whether value is lower/equal than upper
	if (lower > APP.SOURce.RESistance.LIMit.UPPer.value)
	{
		return API_PARAM_OUT_OF_RANGE;
	}

	if (APP_UpdateIntValue(&APP.SOURce.RESistance.LIMit.LOWer, lower) != API_OK)
	{
		return API_ERROR;
	}

	return _APP_UTIL_ApplyInput();
}


bool APP_Get_SourceResistanceLimitState()
{
	return APP.SOURce.RESistance.LIMit.STATe;
}

API_StatusTypeDef APP_Set_SourceResistanceLimitState(bool state)
{
	RETURN_OK_IF_TRUE(APP.SOURce.RESistance.LIMit.STATe == state);

	APP.SOURce.RESistance.LIMit.STATe = state;
	if (state)
	{
		return _APP_UTIL_ApplyInput();
	}
	return API_OK;
}


INT_VALUE_TypeDef APP_Get_SourceResistanceLimitUpper()
{
	return APP.SOURce.RESistance.LIMit.UPPer;
}

API_StatusTypeDef APP_Set_SourceResistanceLimitUpper(int32_t upper)
{
	RETURN_OK_IF_TRUE(APP.SOURce.RESistance.LIMit.UPPer.value == upper);

	// Check whether value is higher/equal than lower
	if (upper < APP.SOURce.RESistance.LIMit.LOWer.value)
	{
		return API_PARAM_OUT_OF_RANGE;
	}

	// Try to update the limit and input
	if (APP_UpdateIntValue(&APP.SOURce.RESistance.LIMit.UPPer, upper) != API_OK)
	{
		return API_ERROR;
	}

	return _APP_UTIL_ApplyInput();
}

// --------------- For SOURce.RESistance.MODE subsystem

RES_MODE_TypeDef APP_Get_SourceResistanceMode()
{
	return APP.SOURce.RESistance.MODE;
}

API_StatusTypeDef APP_Set_SourceResistanceMode(RES_MODE_TypeDef mode)
{
	RETURN_OK_IF_TRUE(APP.SOURce.RESistance.MODE == mode);

	// Leaving List mode requires some special treatment
	if (APP.SOURce.RESistance.MODE == RES_MODE_LIST && mode != RES_MODE_LIST)
	{
		APP_Run_ListTerminate();
	}

	switch (mode)
	{
		case RES_MODE_FIXed:
			APP_Set_TriggerInitiateContinuous(false);
			APP_Run_TriggerAbortImmediate();
			break;

		case RES_MODE_LIST:
			APP_Run_SourceListInit();
			break;

		default:
			break;
	}

	APP.SOURce.RESistance.MODE = mode;
	return API_OK;
}

API_StatusTypeDef APP_Run_SourceResistanceNext()
{
	APP.SOURce.RESistance.MODE++;

	if (APP.SOURce.RESistance.MODE > RES_MODE_LIST)
	{
		APP.SOURce.RESistance.MODE = RES_MODE_FIXed;
	}

	return API_ERROR;
}

// --------------- For SOURce.SWITching subsystem

SWIT_MODE_TypeDef APP_Get_SourceSwitching()
{
	return APP.SOURce.SWITching.MODE;
}

API_StatusTypeDef APP_Set_SourceSwitching(SWIT_MODE_TypeDef switching)
{
	APP.SOURce.SWITching.MODE = switching;
	return API_OK;
}

// --------------- For SOURce.VOLTage subsystem

INT_VALUE_TypeDef APP_Get_SourceVoltageLevelImmediateAmplitude()
{
	return APP.SOURce.VOLTage.LEVel.IMMediate.AMPLitude;
}

/* Private functions ---------------------------------------------------------*/

