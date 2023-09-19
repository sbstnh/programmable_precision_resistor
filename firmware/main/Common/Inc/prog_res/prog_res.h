/*
 * prog_res.h
 *
 *  Created on: Oct 16, 2022
 *      Author: sebas
 */

#ifndef INC_APPLICATION_PROG_RES_H_
#define INC_APPLICATION_PROG_RES_H_

/* Includes ------------------------------------------------------------------*/

#include "util/api.h"
#include "hardware/stp16cp05.h"
#include "prog_res/decade.h"
#include "calibration/calibration.h"
#include "calibration/cal_mode.h"

/* Exported constants --------------------------------------------------------*/

#define OHM							1000

#define PRES_DECIMALS				3

#define PRES_DEC_COUNT				6
#define PRES_RESOLUTION				9

#define PRES_MIN_RES				1 * OHM
#define PRES_MAX_RES				999999 * OHM

#define PRES_RES_VALUE_COUNT		1000000

#define PRES_NUMBER_INTERMEDIATE_TAPS		3

/* Exported types ------------------------------------------------------------*/

typedef struct
{
	uint32_t hw_setpoint;						//!< (Contribution of a decade/recursion to the) hardware setpoint
	uint8_t hw_setpoint_digits[PRES_DEC_COUNT];	//!< digit representation of the hardware setpoint
	uint32_t actual_resistance;					//!< Actual resistance value
} PRES_Setpoint_TypeDef;

typedef struct PRES_t PRES_TypeDef;

typedef struct PRES_t
{
	void (*_requestRelayControl)(PRES_TypeDef *);	//!< Function pointer to relay controller
	uint32_t max_voltage;							//!< Maximum voltage of decade in µV
	uint32_t max_short_circuit_current;				//!< Maximum current for short circuit
	PRES_Setpoint_TypeDef current_setpoint;			//!< setpoint
	DEC_TypeDef decades[PRES_DEC_COUNT];			//!< Decade definition
} PRES_TypeDef;

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

//----------- Apply calibration

API_StatusTypeDef PRES_UpdateCalibration(PRES_TypeDef *progres, volatile CALDATA_TypeDef *cal_data);

//----------- Calculate resistance

/** Calculates the minimum resistance of the programmable resistor considering
 *  the calibration mode.
 *
 *  @param[in] pres      Pointer to the programmable resistor.
 *  @param[in] cal_mode  Calibration mode (@ref CAL_MODE) to base the calculation on.
 *	@return	             Minimum resistance in milli ohm.
 */
uint32_t PRES_CalcMinimumResistance(PRES_TypeDef *pres, CAL_Mode_TypeDef cal_mode);

/** Calculates the maximum resistance of the programmable resistor considering
 *  the calibration mode.
 *
 *  @param[in] pres      Pointer to the programmable resistor.
 *  @param[in] cal_mode  Calibration mode (@ref CAL_MODE) to base the calculation on.
 *	@return	             Maximum resistance in milli ohm.
 */
uint32_t PRES_CalcMaximumResistance(PRES_TypeDef *pres, CAL_Mode_TypeDef cal_mode);

/** Calculates the actual resistance based on the setpoint and the calibration mode
 *  used for calculating the hardware setpoint as well the calibration mode for
 *  calculating the actual resistance.
 *
 *  @param[in]  pres         Pointer to the programmable resistor.
 *  @param[out] result       The actual resistance according to the calibration data.
 *  @param[in]  hw_setpoint  Hardware setpoint in ohm to base the calculation on.
 *  @param[in]  cal_mode_setpoint_calc    Calibration mode (@ref CAL_MODE) to base the hw setpoint calculation on.
 *  @param[in]  cal_mode_resistance_calc  Calibration mode (@ref CAL_MODE) to base the resistance calculation on.
 *	@return	                 Returns the status code of this function
 */
API_StatusTypeDef PRES_CalcActualResistanceFromSetpoint(PRES_TypeDef *pres, uint32_t *result, uint32_t setpoint,
		CAL_Mode_TypeDef cal_mode_setpoint_calc, CAL_Mode_TypeDef cal_mode_resistance_calc);


//----------- Set setpoint


/** Calculates and applies the specified setpoint with optimization.
 *
 *  @param[in] pres         Pointer to the programmable resistor.
 *  @param[in] setpoint     Setpoint in milli ohm.
 *  @param[in] cal_mode     Calibration mode (@ref CAL_MODE) to base the calculation
 *                          of the actual resulting resistance on.
 *	@return	                Returns the status code of this function.
 */
API_StatusTypeDef PRES_SetSetpoint(PRES_TypeDef *pres, uint32_t setpoint, CAL_Mode_TypeDef cal_mode);


//----------- Switching

/** Sends the switching sequence to realize the setpoint set before.
 *
 *  @param[in] pres         Pointer to the programmable resistor.
 *  @param[in] use_bypass	Try to use the bypass tap to reduce total switch
 *  						contact resistance.
 *	@return	                Returns the status code of this function.
 */
API_StatusTypeDef PRES_SwitchSimple(PRES_TypeDef *pres, bool use_bypass);


/** Switches off all relays without updating the setpoint.
 *
 *  @param[in] pres         Pointer to the programmable resistor.
 *	@return	                Returns the status code of this function.
 */
API_StatusTypeDef PRES_SwitchOff(PRES_TypeDef *pres);


//----------- Calculate limit values

/** Calculates the maximum permissible current in the specified setting.
 *  This method considers secondary constraint, i. e. resulting from
 *  voltage limits.
 *
 *  @param[in]  pres        Pointer to the programmable resistor.
 *  @return                 The maximum permissible current in µA.
 */
uint32_t PRES_CalcIMax(PRES_TypeDef *pres);

/** Calculates the maximum permissible voltage in the specified setting.
 *
 *  @param[in] pres                Pointer to the programmable resistor.
 *  @return                        The maximum permissible voltage in mV.
 */
uint32_t PRES_CalcUMax(PRES_TypeDef *pres);

/** Calculates the maximum permissible power in the specified setting.
 *
 *  @param[in] pres                Pointer to the programmable resistor.
 *  @return                        The maximum permissible power in mW
 */
uint32_t PRES_CalcPMax(PRES_TypeDef *pres);

/* Private functions ---------------------------------------------------------*/

int8_t _PRES_HighestNonZeroDecade(PRES_TypeDef *pres);
void _PRES_OpenAllRelays(PRES_TypeDef *pres);
void _PRES_CloseSelectedRelays(DEC_TypeDef *dec);

//----------- Calculate resistance

/** Calculates the actual resistance based on the hardware setpoint and the
 *  calibration mode.
 *
 *  @param[in]  pres         Pointer to the programmable resistor.
 *  @param[out] result       The actual resistance according to the calibration data.
 *  @param[in]  hw_setpoint  Hardware setpoint in ohm to base the calculation on.
 *  @param[in]  cal_mode     Calibration mode (@ref CAL_MODE) to base the calculation on.
 *	@return	                 Returns the status code of this function
 */
API_StatusTypeDef _PRES_CalcActualResistanceFromHWSetpoint(PRES_TypeDef *pres, uint32_t *result, uint32_t hw_setpoint, CAL_Mode_TypeDef cal_mode);

//----------- Calculate hardware setpoint

/** Calculates the hardware setpoint from a resistance setpoint. The hardware setpoint
 *  is determined in a way that minimizes the deviation between the specified setpoint
 *  and the actual value according to the the @ref CAL_MODE selected.
 *
 *  @param[in]  pres         Pointer to the programmable resistor.
 *  @param[out] result       The calculated hardware setpoint. The actual resistance is based on the @ref CAL_MODE chosen.
 *  @param[in]  setpoint     Resistance setpoint in milli ohm to base the calculation on.
 *  @param[in]  cal_mode     Calibration mode (@ref CAL_MODE) to base the calculation of the actual resulting resistance on.
 *	@return	                 Returns the status code of this function
 */
API_StatusTypeDef _PRES_CalcHardwareSetpoint(PRES_TypeDef *pres, PRES_Setpoint_TypeDef *result, uint32_t setpoint, CAL_Mode_TypeDef cal_mode);

//----------- Apply setpoint

/** Applies the specified hardware setpoint
 *
 *  @param[in] pres         Pointer to the programmable resistor.
 *  @param[in] hw_setpoint  Hardware setpoint in Ohm
 *	@return	                Returns the status code of this function
 */
API_StatusTypeDef _PRES_ApplyHardwareSetpointByInt(PRES_TypeDef *pres, uint32_t setpoint);

//----------- Legacy functions

/** Calculates the hardware setpoint from a resistance setpoint by selecting the decade
 *  resistors according to the digits in the setpoint value.
 *
 *  @param[in]  pres         Pointer to the programmable resistor.
 *  @param[out] result       The calculated hardware setpoint. The actual resistance is based on the @ref CAL_MODE chosen.
 *  @param[in]  setpoint     Resistance setpoint in milli ohm to base the calculation on.
 *  @param[in]  cal_mode     Calibration mode (@ref CAL_MODE) to base the calculation of the actual resulting resistance on.
 *	@return	                 Returns the status code of this function
 */
API_StatusTypeDef PRES_CalcHardwareSetpointUncal(PRES_TypeDef *pres, PRES_Setpoint_TypeDef *result, uint32_t setpoint, CAL_Mode_TypeDef cal_mode);


/** Applies the specified hardware setpoint
 *
 *  @param[in] pres                Pointer to the programmable resistor.
 *  @param[in] hw_setpoint_digits  Array of the hardware setpoint digits
 *	@return	                       Returns the status code of this function
 */
API_StatusTypeDef PRES_SetHardwareSetpoint(PRES_TypeDef *pres, uint8_t *hw_setpoint_digits);


/** Calculates and applies the specified setpoint without optimization.
 *
 *  @param[in] pres         Pointer to the programmable resistor.
 *  @param[in] setpoint     Setpoint in milli ohm.
 *  @param[in] cal_mode     Calibration mode (@ref CAL_MODE) to base the calculation
 *                          of the actual resulting resistance on.
 *	@return	                Returns the status code of this function.
 */
API_StatusTypeDef PRES_ApplySetpointUncal(PRES_TypeDef *pres, uint32_t setpoint, CAL_Mode_TypeDef cal_mode);


#endif /* INC_APPLICATION_PROG_RES_H_ */
