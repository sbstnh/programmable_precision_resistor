/**
 * @file    app_calibration.c
 * @author  sebas
 * @date    02.01.2023
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include <string.h>
#include <math.h>
#include "application/app.h"
#include "application/app_calibration.h"
#include "application/app_input.h"
#include "application/app_memory.h"
#include "application/app_source.h"
#include "application/app_system.h"
#include "application/app_util.h"

#include "calibration/calibration.h"
#include "persistence/persistence_def.h"
#include "prog_res/prog_res_def.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

#define CAL_UNSEC_GUARD()				if (APP.CALibration.SECure.STATe) \
											return API_ERROR;

#define CAL_UNSEC_AND_STATE_GUARD()		if (APP.CALibration.SECure.STATe || !APP.CALibration.STATe) \
											return API_ERROR;

/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

API_StatusTypeDef _APP_Run_CalibrationCalculation();

/* Exported functions --------------------------------------------------------*/


API_StatusTypeDef APP_Run_CalibrationApply()
{
	return PRES_UpdateCalibration(&progres, &APP.CALibration.cal_data);
}


bool APP_Get_CalibrationCalibrated()
{
	return APP.CALibration.cal_data.CALIBRATED;
}


uint32_t APP_Get_CalibrationCount()
{
	return APP.CALibration.cal_data.CAL_CNT;
}


const char * APP_Get_CalibrationDate()
{
	if (!strlen((const char *) APP.CALibration.cal_data.CAL_DATE))
	{
		return "<NO CAL DATE>";
	}

	return (const char *)APP.CALibration.cal_data.CAL_DATE;
}

API_StatusTypeDef APP_Set_CalibrationDate(const char *str)
{
	CAL_UNSEC_AND_STATE_GUARD();

	strncpy((char *)APP.CALibration.cal_data.CAL_DATE, str, sizeof(APP.CALibration.cal_data.CAL_DATE) - 1);
	APP.CALibration.cal_data.CAL_DATE[sizeof(APP.CALibration.cal_data.CAL_DATE) - 1] = '\0';
	return API_OK;
}


API_StatusTypeDef APP_Run_CalibrationSave()
{
	CAL_UNSEC_AND_STATE_GUARD();

	if (_APP_Run_CalibrationCalculation() != API_OK)
	{
		return API_ERROR;
	}

	APP.CALibration.cal_data.CALIBRATED = true;

	return APP_Run_MemorySaveCalibration();
}


bool APP_Get_CalibrationSecure()
{
	return APP.CALibration.SECure.STATe;
}

API_StatusTypeDef APP_Set_CalibrationSecure(bool secure)
{
	if (secure)
	{
		APP_Set_CalibrationState(false);
	}

	// Optional: Add password check

	APP.CALibration.SECure.STATe = secure;

	return API_OK;
}


int8_t APP_Get_CalibrationSetup()
{
	return APP.CALibration.SETup;
}

API_StatusTypeDef APP_Set_CalibrationSetup(int32_t setup)
{
	CAL_UNSEC_AND_STATE_GUARD();

	if (setup < CAL_NO_SETUP || setup >= CAL_SETUPS_TOTAL)
	{
		return API_ERROR;
	}

	APP.CALibration.SETup = setup;

	if (setup == CAL_NO_SETUP)
	{
		// Disable input
		return APP_Set_InputState(false);
	}

	// Determine and set the appropriate value
	int32_t setpoint = CAL_IdealResistance(setup);
	if (APP_Set_SourceResistanceLevelImmediateAmplitude(setpoint, true) != API_OK)
	{
		return API_ERROR;
	}

	// Enable input
	return APP_Set_InputState(true);
}


API_StatusTypeDef APP_Run_CalibrationSetupUp()
{
	return APP_Set_CalibrationSetup(APP_Get_CalibrationSetup() + 1);
}


API_StatusTypeDef APP_Run_CalibrationSetupDown()
{
	return APP_Set_CalibrationSetup(APP_Get_CalibrationSetup() - 1);
}


bool APP_Get_CalibrationState()
{
	return APP.CALibration.STATe;
}

API_StatusTypeDef APP_Set_CalibrationState(bool state)
{
	CAL_UNSEC_GUARD();

	RETURN_OK_IF_TRUE(APP.CALibration.STATe == state);

	APP_Init();
	APP.CALibration.SECure.STATe = false;

	if (state)
	{
		// Switch the input off
		APP_Set_InputState(false);

		// Force a fixed output
		APP_Set_SourceResistanceMode(RES_MODE_FIXed);

		// Force uncalibrated mode, so that the user may input
		// the measured value
		APP_Set_SourceMode(SOUR_MODE_UNCalibrated);

		// Force bypass off
		APP.SOURce.SWITching._use_bypass = false;

		// Initialize the temperature with NAN, so that it's
		// updated as soon as the first value is set
		APP.CALibration._start_temp = NAN;

		// Check whether all required calibration steps are done
		APP.CALibration._cal_setup_2w_completed = 0;
		APP.CALibration._cal_setup_4w_completed = 0;
	}
	else
	{
		// Since the calibration procedure might not have
		// been saved prior read the calibration again to
		// either restore the previous or the newly written
		// cal values
	}

	APP.CALibration.STATe = state;
	return API_OK;
}


const char * APP_Get_CalibrationString()
{
	if (!strlen((const char *)APP.CALibration.cal_data.CAL_STR))
	{
		return "<NO CAL STR>";
	}

	return (const char *)APP.CALibration.cal_data.CAL_STR;
}

API_StatusTypeDef APP_Set_CalibrationString(const char *str)
{
	CAL_UNSEC_AND_STATE_GUARD();

	strncpy((char *)APP.CALibration.cal_data.CAL_STR, str, sizeof(APP.CALibration.cal_data.CAL_STR) - 1);
	APP.CALibration.cal_data.CAL_STR[sizeof(APP.CALibration.cal_data.CAL_STR) - 1] = '\0';
	return API_OK;
}


float APP_Get_CalibrationTemp()
{
	// Avoid breaking strict aliasing rule by using memcpy (compiler will optimize)
	float temp;
	memcpy(&temp, (uint32_t *)&(APP.CALibration.cal_data.CAL_TEMP), sizeof(temp));
	return temp;
}


API_StatusTypeDef APP_Get_CalibrationValue(int32_t *value)
{
	if (CAL_GetValue(&APP.CALibration.cal_data, APP.CALibration.SETup, value) != API_OK)
	{
		return API_INVALID_OPERATION;
	}

	return API_OK;
}

API_StatusTypeDef APP_Set_CalibrationValue(int32_t value)
{
	CAL_UNSEC_AND_STATE_GUARD();

	if (APP.CALibration.SETup < 0 || APP.CALibration.SETup >= CAL_SETUPS_TOTAL)
	{
		return API_INVALID_OPERATION;
	}

	if (CAL_SetValue(&APP.CALibration.cal_data, APP.CALibration.SETup, value) != API_OK)
	{
		return API_PARAM_OUT_OF_RANGE;
	}

	if (APP.CALibration.SETup < CAL_SETUP_4W_START)
	{
		APP.CALibration._cal_setup_2w_completed |= 1ULL << APP.CALibration.SETup;
	}
	else
	{
		APP.CALibration._cal_setup_4w_completed |= 1ULL << (APP.CALibration.SETup - CAL_SETUP_4W_START);
	}

	// Update calibration temperature

	if (isnan(APP.CALibration._start_temp))
	{
		APP.CALibration._start_temp = APP_Get_SystemTempImmediate(TEMP_SEL_AVG);
	}
	APP.CALibration._last_setup_temp = APP_Get_SystemTempImmediate(TEMP_SEL_AVG);

	float avg = (APP.CALibration._start_temp + APP.CALibration._last_setup_temp) / 2;

	memcpy((float *)&APP.CALibration.cal_data.CAL_TEMP, &avg, sizeof(avg));

	return API_OK;
}

/* Private functions ---------------------------------------------------------*/


API_StatusTypeDef _APP_Run_CalibrationCalculation()
{
	// Only accept fully calibrated setups for 2W and 4W
	uint64_t mask = 0x0FFFFFFFFFFFFFFF;
	uint8_t number_of_relays = 12 - 2;

	if (APP.CALibration._cal_setup_2w_completed == mask)
	{
		// The contact resistance is calculated based on the zero ohm measurement.
		// For calibration, the bypass is not used. This puts more relays in series
		// and hence increases accuracy of the average contact resistance estimation.
		// In this case, the signal path for zero ohms includes a total of 12 relays.

		int32_t contact_resistance = 0;

		// A total of 6 zero ohm measurements are taken (setups 0 + n * 10 with n < 6).
		// This is not necessary. However, it allows for a simpler setup numbering,
		// where each resistor decade has 10 (instead of 9 per decade plus one zero ohm
		// measurement) setups. Also it might slightly increase the accuracy of the
		// esimation.
		// Here the average of all 6 zero ohm measurements is calculated.
		for (int8_t decade = 0; decade < CAL_SETUPS_PER_MODE; decade += DEC_RES_COUNT)
		{
			contact_resistance += APP.CALibration.cal_data.CAL_VAL_2W[decade];
		}
		contact_resistance /= PRES_DEC_COUNT;

		// Set calibration value for 0 ohms to calculated mean
		for (int8_t decade = 0; decade < CAL_SETUPS_PER_MODE; decade += DEC_RES_COUNT)
		{
			APP.CALibration.cal_data.CAL_VAL_2W[decade] = contact_resistance;
		}

		for (int8_t setup = 0; setup < CAL_SETUPS_PER_MODE; setup++)
		{
			// All odd setups represent odd resistance values. Those use only one
			// relay in the signal path. Even resistance values short the additional
			// series resistance with another relay (*), resulting in a total of two
			// relays in the signal path.
			// (*) Technically, the contact resistance is in parallel with the series
			// resistance. The error of this simplification is very small.

			// However, in both cases we have to reduce the measured value by all
			// relays that are not of this particular decade, i. e. 10 (regardless
			// of whether we measure an even or odd value).
			// The reason: Although for odd values there is only one relay in the
			// signal path, we also only measure the resistance of the one relay
			// in the signal path (in addition to those of all the other decades).
			// In contrast, the second relay of the particular decade isn't in
			// the signal path when measuring the resistance for calibration.
			// Hence we don't have to account for this relay either.
			APP.CALibration.cal_data.CAL_VAL_2W[setup] -= number_of_relays * contact_resistance / 12;
		}
	}

	if (APP.CALibration._cal_setup_4w_completed == mask)
	{
		int32_t contact_resistance = 0;

		for (int8_t decade = 0; decade < CAL_SETUPS_PER_MODE; decade += DEC_RES_COUNT)
		{
			contact_resistance += APP.CALibration.cal_data.CAL_VAL_4W[decade];
		}
		contact_resistance /= PRES_DEC_COUNT;

		for (int8_t decade = 0; decade < CAL_SETUPS_PER_MODE; decade += DEC_RES_COUNT)
		{
			APP.CALibration.cal_data.CAL_VAL_4W[decade] = contact_resistance;
		}

		for (int8_t setup = 0; setup < CAL_SETUPS_PER_MODE; setup++)
		{
			APP.CALibration.cal_data.CAL_VAL_4W[setup] -= number_of_relays * contact_resistance / 12;
		}
	}

	return API_OK;
}
