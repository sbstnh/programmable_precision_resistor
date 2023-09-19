/**
 * @file    app_source.h
 * @author  sebas
 * @date    03.12.2022
 * @brief
 */
#ifndef INC_APPLICATION_APP_SOURCE_H_
#define INC_APPLICATION_APP_SOURCE_H_

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdint.h>
#include "application/app_params.h"
#include "application/app_util.h"
#include "util/api.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

// --------------- For SOURce.Current subsystem

INT_VALUE_TypeDef APP_Get_SourceCurrentLevelImmediateAmplitude();


// --------------- For SOURce.DIGital subsystem

bool APP_Get_SourceDigitalPinData(uint8_t ext);

PIN_FUNCtion_TypeDef APP_Get_SourceDigitalPinFunction(uint8_t pin);
PIN_FUNCtion_TypeDef APP_Get_SourceDigitalPin1Function();
PIN_FUNCtion_TypeDef APP_Get_SourceDigitalPin2Function();
API_StatusTypeDef APP_Set_SourceDigitalPinFunctionSave(uint8_t pin, PIN_FUNCtion_TypeDef function, bool save);
API_StatusTypeDef APP_Set_SourceDigitalPinFunction(uint8_t pin, PIN_FUNCtion_TypeDef function);
API_StatusTypeDef APP_Set_SourceDigitalPin1Function(PIN_FUNCtion_TypeDef function);
API_StatusTypeDef APP_Set_SourceDigitalPin2Function(PIN_FUNCtion_TypeDef function);

PIN_POLarity_TypeDef APP_Get_SourceDigitalPinPolarity(uint8_t ext);
PIN_POLarity_TypeDef APP_Get_SourceDigitalPin1Polarity();
PIN_POLarity_TypeDef APP_Get_SourceDigitalPin2Polarity();
API_StatusTypeDef APP_Set_SourceDigitalPinPolaritySave(uint8_t pin, PIN_POLarity_TypeDef polarity, bool save);
API_StatusTypeDef APP_Set_SourceDigitalPinPolarity(uint8_t ext, PIN_POLarity_TypeDef polarity);
API_StatusTypeDef APP_Set_SourceDigitalPin1Polarity(PIN_POLarity_TypeDef polarity);
API_StatusTypeDef APP_Set_SourceDigitalPin2Polarity(PIN_POLarity_TypeDef polarity);


// --------------- For SOURce.LIST subsystem

API_StatusTypeDef APP_Run_SourceListInit();

API_StatusTypeDef APP_Get_SourceListResistanceLevelValues(int32_t pos, int32_t *value);
API_StatusTypeDef APP_Set_SourceListResistanceLevelValues(int32_t pos, int32_t value);

INT_VALUE_TypeDef APP_Get_SourceListResistanceLength();
API_StatusTypeDef APP_Set_SourceListResistanceLength(int32_t length);

INT_VALUE_TypeDef APP_Get_SourceListResistanceIndex();
API_StatusTypeDef APP_Set_SourceListResistanceIndex(int32_t index);

INT_VALUE_TypeDef APP_Get_SourceListResistanceRunNumber();

INT_VALUE_TypeDef APP_Get_SourceListResistanceRunCount();
API_StatusTypeDef APP_Set_SourceListResistanceRunCount(int32_t count);

API_StatusTypeDef APP_Get_SourceListResistanceDwellValues(int32_t pos, int32_t *value);
API_StatusTypeDef APP_Set_SourceListResistanceDwellValues(int32_t pos, int32_t value);

INT_VALUE_TypeDef APP_Get_SourceListResistanceDwellLength();
API_StatusTypeDef APP_Set_SourceListResistanceDwellLength(int32_t length);

API_StatusTypeDef APP_Run_ListRun(bool triggered);

bool APP_Get_SourceListStartInput();
API_StatusTypeDef APP_Set_SourceListStartInput(bool input);

STARt_MODE_TypeDef APP_Get_SourceListStartMode();
API_StatusTypeDef APP_Set_SourceListStartMode(STARt_MODE_TypeDef start);

LIST_STEP_TypeDef APP_Get_SourceListStep();
API_StatusTypeDef APP_Set_SourceListStep(LIST_STEP_TypeDef step);

API_StatusTypeDef APP_Run_ListTerminate();

bool APP_Get_SourceListTerminateLast();
API_StatusTypeDef APP_Set_SourceListTerminateLast(bool last);

bool APP_Get_SourceListTerminateInput();
API_StatusTypeDef APP_Set_SourceListTerminateInput(bool input);


// --------------- For SOURce.MODE subsystem

SOUR_MODE_TypeDef APP_Get_SourceMode();
API_StatusTypeDef APP_Set_SourceMode(SOUR_MODE_TypeDef mode);


// --------------- For SOURce.POWer subsystem

INT_VALUE_TypeDef APP_Get_SourcePowerLevelImmediateAmplitude();


// --------------- For SOURce.RESistance.LEVel subsystem

INT_VALUE_TypeDef APP_Get_SourceResistanceLevelImmediateAmplitude();
API_StatusTypeDef APP_Set_SourceResistanceLevelImmediateAmplitudeForce(int32_t amplitude, bool backup_immediate);
API_StatusTypeDef APP_Run_SourceResistanceLevelImmediateAmplitudeFromBackup();
API_StatusTypeDef APP_Set_SourceResistanceLevelImmediateAmplitude(int32_t amplitude, bool backup_immediate);
API_StatusTypeDef APP_Run_SourceResistanceLevelImmediateAmplitudeMin(bool backup_immediate);
API_StatusTypeDef APP_Run_SourceResistanceLevelImmediateAmplitudeMax(bool backup_immediate);
API_StatusTypeDef APP_Run_SourceResistanceLevelImmediateAmplitudeUp(bool backup_immediate);
API_StatusTypeDef APP_Run_SourceResistanceLevelImmediateAmplitudeDown(bool backup_immediate);
API_StatusTypeDef APP_Run_SourceResistanceLevelImmediateCalculate(SOUR_MODE_TypeDef mode, int32_t *result);

INT_VALUE_TypeDef APP_Get_SourceResistanceLevelTriggeredAmplitude();
API_StatusTypeDef APP_Set_SourceResistanceLevelTriggeredAmplitude(int32_t amplitude);
API_StatusTypeDef APP_Run_SourceResistanceLevelTriggeredCalculate(SOUR_MODE_TypeDef mode, int32_t *result);

volatile LEV_STEP_TypeDef *APP_Get_SourceResistanceLevelStep();

INT_VALUE_TypeDef APP_Get_SourceResistanceLevelStepIncrement();
API_StatusTypeDef APP_Set_SourceResistanceLevelStepIncrement(int32_t increment);

//API_StatusTypeDef APP_SetSourceResistanceLevelStepPDecade(int32_t points_per_decade);

STEP_MODE_TypeDef APP_Get_SourceResistanceLevelStepMode();
API_StatusTypeDef APP_Set_SourceResistanceLevelStepMode(STEP_MODE_TypeDef mode);

STEP_OVERflow_TypeDef APP_Get_SourceResistanceLevelStepOverflow();
API_StatusTypeDef APP_Set_SourceResistanceLevelStepOverflow(STEP_OVERflow_TypeDef overflow);


// --------------- For SOURce.RESistance.LIMit subsystem

INT_VALUE_TypeDef APP_Get_SourceResistanceLimitLower();
API_StatusTypeDef APP_Set_SourceResistanceLimitLower(int32_t lower);

bool APP_Get_SourceResistanceLimitState();
API_StatusTypeDef APP_Set_SourceResistanceLimitState(bool state);

INT_VALUE_TypeDef APP_Get_SourceResistanceLimitUpper();
API_StatusTypeDef APP_Set_SourceResistanceLimitUpper(int32_t upper);


// --------------- For SOURce.RESistance.MODE subsystem

RES_MODE_TypeDef APP_Get_SourceResistanceMode();
API_StatusTypeDef APP_Set_SourceResistanceMode(RES_MODE_TypeDef mode);
API_StatusTypeDef APP_Run_SourceResistanceNext();

// --------------- For SOURce.SWITching subsystem

SWIT_MODE_TypeDef APP_Get_SourceSwitching();
API_StatusTypeDef APP_Set_SourceSwitching(SWIT_MODE_TypeDef switching);


// --------------- For SOURce.VOLTage subsystem

INT_VALUE_TypeDef APP_Get_SourceVoltageLevelImmediateAmplitude();

/* Private functions ---------------------------------------------------------*/


#endif /* INC_APPLICATION_APP_SOURCE_H_ */
