/**
 * @file    apply_persistence.c
 * @author  sebas
 * @date    23.04.2023
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "persistence/apply_persistence.h"

#include "application/app_display.h"
#include "application/app_input.h"
#include "application/app_source.h"
#include "application/app_trigger.h"
#include "application/app_system.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/


void PER_ApplyInstData(PER_TypeDef *per, volatile APP_ParamTypeDef *app)
{
	INSTDATA_TypeDef *instdata = &per->inst_data;

	APP_Set_InputInhibitModeSave(instdata->INP_INH_MODE, false);

	APP_Set_SourceDigitalPinFunctionSave(SOUR_DIG_PIN1, instdata->SOUR_DIG_PIN_FUNCtion[SOUR_DIG_PIN1], false);
	APP_Set_SourceDigitalPinFunctionSave(SOUR_DIG_PIN2, instdata->SOUR_DIG_PIN_FUNCtion[SOUR_DIG_PIN2], false);
	APP_Set_SourceDigitalPinPolaritySave(SOUR_DIG_PIN1, instdata->SOUR_DIG_PIN_POLarity[SOUR_DIG_PIN1], false);
	APP_Set_SourceDigitalPinPolaritySave(SOUR_DIG_PIN2, instdata->SOUR_DIG_PIN_POLarity[SOUR_DIG_PIN2], false);

	APP_Set_SystemBeeperStateSave(instdata->SYST_BEEP_STATe, false);
}

void PER_ApplyUserData(PER_TypeDef *per, volatile APP_ParamTypeDef *app)
{
	USERDATA_TypeDef *setdata = &per->user_data;

	APP_Set_DisplayPrimaryResolution(setdata->DISP_PRIM_RESolution);
	APP_Set_DisplaySecondaryMode(setdata->DISP_SEC_MODE);

	APP_Set_InputState(setdata->INP_STATe);

	APP_Set_SourceMode(setdata->SOUR_MODE);
	APP_Set_SourceResistanceLevelImmediateAmplitude(setdata->SOUR_RES_LEV_IMM_AMPlitude, true);
	APP_Set_SourceResistanceLevelTriggeredAmplitude(setdata->SOUR_RES_LEV_TRIG_AMPlitude);
	APP_Set_SourceResistanceLevelStepIncrement(setdata->SOUR_RES_LEV_STEP_INCRement);
	APP_Set_SourceResistanceLevelStepMode(setdata->SOUR_RES_LEV_STEP_MODE);
	APP_Set_SourceResistanceLevelStepOverflow(setdata->SOUR_RES_LEV_STEP_OVERflow);
	APP_Set_SourceResistanceLimitLower(setdata->SOUR_RES_LIM_LOWer);
	APP_Set_SourceResistanceLimitState(setdata->SOUR_RES_LIM_STATe);
	APP_Set_SourceResistanceLimitUpper(setdata->SOUR_RES_LIM_UPPer);
	APP_Set_SourceResistanceMode(setdata->SOUR_RES_MODE);
	APP.SOURce.SWITching._use_bypass = setdata->SOUR_SWITching._use_bypass;
	APP_Set_SourceSwitching(setdata->SOUR_SWITching.MODE);

	APP_Set_TriggerSequenceDelay(setdata->TRIG_SEQ_DELay);
	APP_Set_TriggerSequenceHoldOff(setdata->TRIG_SEQ_HOLDoff);
	APP_Set_TriggerSequenceSlope(setdata->TRIG_SEQ_SLOPe);
	APP_Set_TriggerSequenceSource(setdata->TRIG_SEQ_SOURce);
	APP_Set_TriggerSequenceTimer(setdata->TRIG_SEQ_TIMer);
}

/* Private functions ---------------------------------------------------------*/

