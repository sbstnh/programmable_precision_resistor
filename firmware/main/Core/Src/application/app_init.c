/**
 * @file    app_init.c
 * @author  sebas
 * @date    04.03.2023
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>
#include <string.h>

#include "application/app_init.h"

/* Private defines -----------------------------------------------------------*/

#define APP_PARAM_DEF_RESISTANCE		1000000			// mOhm
#define APP_PARAM_MIN_RESISTANCE		0				// mOhm
#define APP_PARAM_MAX_RESISTANCE		999999000		// mOhm

#define APP_PARAM_DEF_STEP				1000			// mOhm
#define APP_PARAM_MIN_STEP				1				// mOhm
#define APP_PARAM_MAX_STEP				APP_PARAM_MAX_RESISTANCE	// mOhm

#define APP_PARAM_LIMIT_LOW				APP_PARAM_MIN_RESISTANCE	// mOhm
#define APP_PARAM_LIMIT_HIGH			APP_PARAM_MAX_RESISTANCE	// mOhm

#define APP_PARAM_MAX_LIST_RUNS			1000000			// 1

#define APP_PARAM_MAX_CURRENT			1000000			// µA
#define APP_PARAM_MAX_POWER				10000			// mW
#define APP_PARAM_MAX_VOLTAGE			1000000			// mV

#define APP_PARAM_MIN_TRIG_DELAY		0				// cycles
#define APP_PARAM_MAX_TRIG_DELAY		1000000000		// cycles

#define APP_PARAM_MIN_TRIG_HOLDOFF		0				// cycles
#define APP_PARAM_MAX_TRIG_HOLDOFF		1000000000		// cycles

#define APP_PARAM_MIN_TRIG_TIMER		1				// cycles
#define APP_PARAM_MAX_TRIG_TIMER		1000000000		// cycles

/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void APP_Run_RestoreDefault(volatile APP_ParamTypeDef *app)
{
	APP_Run_RestoreDefaultAppState(app);
	APP_Run_RestoreDefaultInstrumentSettings(app);
	APP_Run_RestoreDefaultUserSettings(app);
}


void APP_Run_RestoreDefaultAppState(volatile APP_ParamTypeDef *app)
{
	app->CALibration.SECure.STATe = true;
	app->CALibration.SETup = -1;
	app->CALibration.STATe = false;

	app->DISPlay.ENABle = true;
	memset((char *)app->DISPlay.USER.TEXT.DATA, 0, sizeof(app->DISPlay.USER.TEXT.DATA));
	app->DISPlay.USER.TEXT.STATe = false;
}


void APP_Run_RestoreDefaultInstrumentSettings(volatile APP_ParamTypeDef *app)
{
	app->INPut.INHibit.MODE = INH_MODE_OFF;

	app->SOURce.DIGital.PIN[SOUR_DIG_PIN1].FUNCtion = PIN_FUNC_DINPut;
	app->SOURce.DIGital.PIN[SOUR_DIG_PIN2].FUNCtion = PIN_FUNC_DINPut;
	app->SOURce.DIGital.PIN[SOUR_DIG_PIN1].POLarity = PIN_POL_POSitive;
	app->SOURce.DIGital.PIN[SOUR_DIG_PIN2].POLarity = PIN_POL_POSitive;

	app->SYSTem.BEEPer.STATe = true;
}


void APP_Run_RestoreDefaultUserSettings(volatile APP_ParamTypeDef *app)
{
	app->DISPlay.MAIN.PRIMary.RESolution = PRIM_RES_SIX;
	app->DISPlay.MAIN.SECondary.MODE = SEC_MODE_STATe;

	app->INPut.PON.STATe = PON_STAT_RST;
	app->INPut.STATe = false;

	app->SOURce.CURRent.LEVel.IMMediate.AMPLitude.max = APP_PARAM_MAX_CURRENT;
	app->SOURce.CURRent.LEVel.IMMediate.AMPLitude.min = -APP_PARAM_MAX_CURRENT;
	app->SOURce.CURRent.LEVel.IMMediate.AMPLitude.value = 0;
	app->SOURce.DIGital.PIN[SOUR_DIG_PIN1].DATA = 0;
	app->SOURce.DIGital.PIN[SOUR_DIG_PIN2].DATA = 0;
	app->SOURce.LIST.RESistance.DWELl.length.max = SOUR_LIST_LENGTH;
	app->SOURce.LIST.RESistance.DWELl.length.min = 1;
	app->SOURce.LIST.RESistance.DWELl.length.value = 1;
	memset((char *)app->SOURce.LIST.RESistance.DWELl.values, 0, sizeof(app->SOURce.LIST.RESistance.DWELl.values));
	app->SOURce.LIST.RESistance.DWELl.values[0] = 100;
	app->SOURce.LIST.RESistance.INDex.max = SOUR_LIST_LENGTH - 1;
	app->SOURce.LIST.RESistance.INDex.min = 0;
	app->SOURce.LIST.RESistance.INDex.value = 0;
	app->SOURce.LIST.RESistance.LEVel.length.max = SOUR_LIST_LENGTH;
	app->SOURce.LIST.RESistance.LEVel.length.min = 1;
	app->SOURce.LIST.RESistance.LEVel.length.value = 1;
	memset((char *)app->SOURce.LIST.RESistance.LEVel.values, 0, sizeof(app->SOURce.LIST.RESistance.LEVel.values));
	app->SOURce.LIST.RESistance.LEVel.values[0] = APP_PARAM_DEF_RESISTANCE;
	app->SOURce.LIST.RESistance.RUN.COUNt.max = APP_PARAM_MAX_LIST_RUNS;
	app->SOURce.LIST.RESistance.RUN.COUNt.min = 0;
	app->SOURce.LIST.RESistance.RUN.COUNt.value = 0;
	app->SOURce.LIST.RESistance.RUN.NUMBer.max = APP_PARAM_MAX_LIST_RUNS - 1;
	app->SOURce.LIST.RESistance.RUN.NUMBer.min = 0;
	app->SOURce.LIST.RESistance.RUN.NUMBer.value = 0;
	app->SOURce.LIST.STARt.INPut = false;
	app->SOURce.LIST.STARt.MODE = LIST_START_AUTO;
	app->SOURce.LIST.STEP = LIST_STEP_AUTO;
	app->SOURce.LIST.TERMinate.INPut = false;
	app->SOURce.LIST.TERMinate.LAST = true;
	app->SOURce.MODE = SOUR_MODE_TWIRe;
	app->SOURce.POWer.LEVel.IMMediate.AMPLitude.max = APP_PARAM_MAX_POWER;
	app->SOURce.POWer.LEVel.IMMediate.AMPLitude.min = -APP_PARAM_MAX_POWER;
	app->SOURce.POWer.LEVel.IMMediate.AMPLitude.value = 0;
	app->SOURce.RESistance.LEVel.IMMediate.AMPLitude.max = APP_PARAM_MAX_RESISTANCE;
	app->SOURce.RESistance.LEVel.IMMediate.AMPLitude.min = APP_PARAM_MIN_RESISTANCE;
	app->SOURce.RESistance.LEVel.IMMediate.AMPLitude.value = APP_PARAM_DEF_RESISTANCE;
	app->SOURce.RESistance.LEVel.STEP.INCRement.max = APP_PARAM_MAX_STEP;
	app->SOURce.RESistance.LEVel.STEP.INCRement.min = APP_PARAM_MIN_STEP;
	app->SOURce.RESistance.LEVel.STEP.INCRement.value = APP_PARAM_DEF_STEP;
	app->SOURce.RESistance.LEVel.STEP.MODE = STEP_MODE_LINear;
	app->SOURce.RESistance.LEVel.STEP.OVERflow = STEP_OVER_STAY;
	app->SOURce.RESistance.LEVel.TRIGgered.AMPLitude.max = APP_PARAM_MAX_RESISTANCE;
	app->SOURce.RESistance.LEVel.TRIGgered.AMPLitude.min = APP_PARAM_MIN_RESISTANCE;
	app->SOURce.RESistance.LEVel.TRIGgered.AMPLitude.value = APP_PARAM_DEF_RESISTANCE;
	app->SOURce.RESistance.LIMit.LOWer.max = APP_PARAM_MAX_RESISTANCE;
	app->SOURce.RESistance.LIMit.LOWer.min = APP_PARAM_MIN_RESISTANCE;
	app->SOURce.RESistance.LIMit.LOWer.value = APP_PARAM_LIMIT_LOW;
	app->SOURce.RESistance.LIMit.STATe = false;
	app->SOURce.RESistance.LIMit.UPPer.max = APP_PARAM_MAX_RESISTANCE;
	app->SOURce.RESistance.LIMit.UPPer.min = APP_PARAM_MIN_RESISTANCE;
	app->SOURce.RESistance.LIMit.UPPer.value = APP_PARAM_LIMIT_HIGH;
	app->SOURce.RESistance.MODE = RES_MODE_FIXed;
	app->SOURce.SWITching.MODE = SOUR_SWIT_AUTO;
	app->SOURce.SWITching._use_bypass = true;
	app->SOURce.VOLTage.LEVel.IMMediate.AMPLitude.max = APP_PARAM_MAX_VOLTAGE;
	app->SOURce.VOLTage.LEVel.IMMediate.AMPLitude.min = -APP_PARAM_MAX_VOLTAGE;
	app->SOURce.VOLTage.LEVel.IMMediate.AMPLitude.value = 0;

	app->SYSTem.COMMunicate.RLSTate = COMM_RLST_MIXed;

	app->TRIGger.INITiate.CONTinuous = false;
	app->TRIGger.SEQuence.DELay.max = APP_PARAM_MAX_TRIG_DELAY;
	app->TRIGger.SEQuence.DELay.min = APP_PARAM_MIN_TRIG_DELAY;
	app->TRIGger.SEQuence.DELay.value = 0;
	app->TRIGger.SEQuence.HOLDoff.max = APP_PARAM_MAX_TRIG_HOLDOFF;
	app->TRIGger.SEQuence.HOLDoff.min = APP_PARAM_MIN_TRIG_HOLDOFF;
	app->TRIGger.SEQuence.HOLDoff.value = 0;
	app->TRIGger.SEQuence.SOURce = SEQ_SOUR_BUS;
	app->TRIGger.SEQuence.SLOPe = SEQ_SLOP_POSITIVE;
	app->TRIGger.SEQuence.TIMer.max = APP_PARAM_MAX_TRIG_TIMER;
	app->TRIGger.SEQuence.TIMer.min = APP_PARAM_MIN_TRIG_TIMER;
	app->TRIGger.SEQuence.TIMer.value = 1000;
	app->TRIGger._bus_trig_received = false;
	app->TRIGger._manual_trig_received = false;
}


/* Private functions ---------------------------------------------------------*/

