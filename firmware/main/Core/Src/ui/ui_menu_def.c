/*
 * menu_def.c
 *
 *  Created on: 11.11.2022
 *      Author: sebas
 */

/* Includes ------------------------------------------------------------------*/

#include "ui/menu.h"
#include "ui/action/ui_action_calibration.h"
#include "ui/action/ui_action_common.h"
#include "ui/action/ui_action_display.h"
#include "ui/action/ui_action_input.h"
#include "ui/action/ui_action_list.h"
#include "ui/action/ui_action_resistance.h"
#include "ui/action/ui_action_system.h"
#include "ui/action/ui_action_trigger.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

//        level,	text,				name,   			next,    			previous,  			parent,    		child,    		select_func,enter_func
MENU_ITEM('1',		"CALibration", 		MENU_CAL,			MENU_DIG, 			NULL_MENU, 			NULL_MENU, 		MENU_CAL_COUN,	NULL, 		NULL);
  MENU_ITEM('1',	"CAL:COUNt", 		MENU_CAL_COUN,		MENU_CAL_DATE,		NULL_MENU,			MENU_CAL, 		NULL_MENU,		NULL, 		UIACT_CalibrationCount);
  MENU_ITEM('2',	"CAL:DATE", 		MENU_CAL_DATE,		MENU_CAL_STR,		MENU_CAL_COUN, 		MENU_CAL, 		NULL_MENU,		NULL, 		UIACT_CalibrationDate);
  MENU_ITEM('3',	"CAL:STRing", 		MENU_CAL_STR,		MENU_CAL_TEMP,		MENU_CAL_DATE,		MENU_CAL, 		NULL_MENU,		NULL, 		UIACT_CalibrationString);
  MENU_ITEM('4',	"CAL:TEMPerature",	MENU_CAL_TEMP,		NULL_MENU,			MENU_CAL_STR,		MENU_CAL, 		NULL_MENU,		NULL, 		UIACT_CalibrationTemp);

MENU_ITEM('2',		"DIGital (EXT)",	MENU_DIG,			MENU_DISP,			MENU_CAL,			NULL_MENU, 		MENU_DIG_PIN1,	NULL, 		NULL);
  MENU_ITEM('1',	"DIG:PIN1",			MENU_DIG_PIN1,		MENU_DIG_PIN2,		NULL_MENU,			MENU_DIG,		MENU_PIN1_FUNC,	NULL, 		NULL);
    MENU_ITEM('1',	"DIG:PIN1:FUNCtion",MENU_PIN1_FUNC,		MENU_PIN1_POL,		NULL_MENU,		 	MENU_DIG_PIN1,	NULL_MENU,		NULL, 		UIACT_SystemDigitalInputFunction1);
    MENU_ITEM('2',	"DIG:PIN1:POLarity",MENU_PIN1_POL,		NULL_MENU,			MENU_PIN1_FUNC, 	MENU_DIG_PIN1,	NULL_MENU,		NULL, 		UIACT_SystemDigitalInputPolarity1);
  MENU_ITEM('2',	"DIG:PIN2",			MENU_DIG_PIN2,		NULL_MENU,			MENU_DIG_PIN1,		MENU_DIG,		MENU_PIN2_FUNC,	NULL, 		NULL);
    MENU_ITEM('1',	"DIG:PIN2:FUNCtion",MENU_PIN2_FUNC,		MENU_PIN2_POL,		NULL_MENU, 			MENU_DIG_PIN2,	NULL_MENU,		NULL, 		UIACT_SystemDigitalInputFunction2);
    MENU_ITEM('2',	"DIG:PIN2:POLarity",MENU_PIN2_POL,		NULL_MENU, 			MENU_PIN2_FUNC,		MENU_DIG_PIN2,	NULL_MENU,		NULL, 		UIACT_SystemDigitalInputPolarity2);

MENU_ITEM('3',		"DISPlay", 			MENU_DISP,			MENU_INP, 			MENU_DIG, 			NULL_MENU, 		MENU_DISP_ENAB,	NULL, 		NULL);
  MENU_ITEM('1',	"DISP:ENABle OFF",	MENU_DISP_ENAB,		MENU_DISP_MAIN,		NULL_MENU,			MENU_DISP, 		NULL_MENU,		NULL, 		UIACT_DisplaySwitchOff);
  MENU_ITEM('2',	"DISP:MAIN",		MENU_DISP_MAIN,		NULL_MENU,			MENU_DISP_ENAB,		MENU_DISP, 		MENU_MAIN_PRIM,	NULL, 		NULL);
    MENU_ITEM('1',	"D:MAIN:PRIMary",   MENU_MAIN_PRIM,		NULL_MENU,			NULL_MENU, 			MENU_DISP_MAIN,	MENU_PRIM_RES,	NULL, 		NULL);
      MENU_ITEM('1',"D:M:P:RESolution", MENU_PRIM_RES,		NULL_MENU,			NULL_MENU,			MENU_MAIN_PRIM,	NULL_MENU,		NULL, 		UIACT_DisplayResolution);

MENU_ITEM('4',		"INPut",			MENU_INP,			MENU_LIST, 			MENU_DISP, 			NULL_MENU, 		MENU_INP_INH,	NULL, 		NULL);
  MENU_ITEM('1',	"INP:INHibit",		MENU_INP_INH,		NULL_MENU,			NULL_MENU,			MENU_INP, 		MENU_INH_MODE,	NULL, 		NULL);
    MENU_ITEM('1',	"INP:INH:MODE",		MENU_INH_MODE,		MENU_INH_CLE,		NULL_MENU,			MENU_INP_INH,	NULL_MENU,		NULL, 		UIACT_InputInhibitMode);
    MENU_ITEM('2',	"INP:INH:CLEar",	MENU_INH_CLE,		MENU_INH_STAT,		MENU_INH_MODE,		MENU_INP_INH,	NULL_MENU,		NULL, 		UIACT_InputInhibitClear);
    MENU_ITEM('2',	"INP:INH:STATe",	MENU_INH_STAT,		NULL_MENU,			MENU_INH_CLE, 		MENU_INP_INH, 	NULL_MENU,		NULL, 		UIACT_InputInhibitState);

MENU_ITEM('5',		"LIST",				MENU_LIST,			MENU_MODE,			MENU_INP,			NULL_MENU, 		MENU_DWEL,		NULL, 		NULL);
  MENU_ITEM('1',	"LIST:DWELl", 		MENU_DWEL,			MENU_LIST_RES,		NULL_MENU,			MENU_LIST,		MENU_DWEL_POIN,	NULL, 		NULL);
      MENU_ITEM('1',"L:DWELl:POINts",   MENU_DWEL_POIN,		MENU_DWEL_VAL,		NULL_MENU,			MENU_DWEL,		NULL_MENU,		NULL, 		UIACT_ListResDwellPoints);
      MENU_ITEM('2',"L:DWELl[:VALues]",	MENU_DWEL_VAL,		NULL_MENU,			MENU_DWEL_POIN,		MENU_DWEL,		NULL_MENU,		NULL, 		UIACT_ListResDwell);
  MENU_ITEM('2',	"LIST[:RESistance]",MENU_LIST_RES,		MENU_LIST_STAR,		MENU_DWEL, 			MENU_LIST,		MENU_LRES_IND,	NULL, 		NULL);
    MENU_ITEM('1',	"LIST[:RES]:INDex", MENU_LRES_IND,		MENU_LRES_LEV,		NULL_MENU,			MENU_LIST_RES,	NULL_MENU,		NULL, 		UIACT_ListResIndex);
    MENU_ITEM('2',	"LIST[:RES]:[LEVel]",MENU_LRES_LEV,		MENU_LRES_POIN,		MENU_LRES_IND,		MENU_LIST_RES,	NULL_MENU,		NULL, 		UIACT_ListResLevel);
    MENU_ITEM('3',	"LIST[:RES]:POINts",MENU_LRES_POIN,		MENU_LRES_RUN,		MENU_LRES_LEV,		MENU_LIST_RES,	NULL_MENU,		NULL, 		UIACT_ListResPoints);
    MENU_ITEM('4',	"LIST[:RES]:RUN", 	MENU_LRES_RUN,		NULL_MENU,			MENU_LRES_POIN,		MENU_LIST_RES,	MENU_RUN_COUN,	NULL, 		NULL);
      MENU_ITEM('1',"L[:R]:RUN:COUNt",  MENU_RUN_COUN,		MENU_RUN_NUMB,		NULL_MENU,			MENU_LRES_RUN,	NULL_MENU,		NULL, 		UIACT_ListResRunCount);
      MENU_ITEM('2',"L[:R]:RUN[:NUMBer]",MENU_RUN_NUMB,		NULL_MENU,			MENU_RUN_COUN,		MENU_LRES_RUN,	NULL_MENU,		NULL, 		UIACT_ListResRunNumber);
  MENU_ITEM('3',	"LIST:STARt",	 	MENU_LIST_STAR,		MENU_LIST_STEP,		MENU_LIST_RES,		MENU_LIST,		MENU_LIST_INP,	NULL, 		NULL);
    MENU_ITEM('1',	"LIST:STARt:INPut",	MENU_LIST_INP,		MENU_LIST_MODE,		NULL_MENU, 			MENU_LIST_STAR,	NULL_MENU,		NULL, 		UIACT_ListStartInput);
    MENU_ITEM('2',	"LIST:STARt[:MODE]",MENU_LIST_MODE,		NULL_MENU, 			MENU_LIST_INP,		MENU_LIST_STAR,	NULL_MENU,		NULL, 		UIACT_ListStartMode);
  MENU_ITEM('4',	"LIST:STEP",	 	MENU_LIST_STEP,		MENU_LIST_TERM,		MENU_LIST_STAR,		MENU_LIST,		NULL_MENU,		NULL, 		UIACT_ListStep);
  MENU_ITEM('5',	"LIST:TERMinate",	MENU_LIST_TERM,		NULL_MENU, 			MENU_LIST_STEP,		MENU_LIST,		MENU_TERM_INP,	NULL, 		NULL);
    MENU_ITEM('1',	"LIST:TERM:INPut",	MENU_TERM_INP,		MENU_TERM_LAST,		NULL_MENU, 			MENU_LIST_TERM,	NULL_MENU,		NULL, 		UIACT_ListTerminateInput);
    MENU_ITEM('2',	"LIST:TERM:LAST",	MENU_TERM_LAST,		NULL_MENU, 			MENU_TERM_INP,		MENU_LIST_TERM,	NULL_MENU,		NULL, 		UIACT_ListTerminateLast);

MENU_ITEM('6',		"MODE (CAL)",		MENU_MODE,			MENU_RES, 			MENU_LIST,			NULL_MENU, 		NULL_MENU,		NULL, 		UIACT_ResistanceCalMode);

MENU_ITEM('7',		"RESistance",		MENU_RES,			MENU_SWIT, 			MENU_MODE, 			NULL_MENU, 		MENU_RES_LEV,	NULL, 		NULL);
  MENU_ITEM('1',	"RES:[LEVel]",		MENU_RES_LEV,		MENU_RES_LIM,		NULL_MENU, 			MENU_RES, 		MENU_LEV_IMM,	NULL, 		NULL);
    MENU_ITEM('1',	"RES::[IMMediate]", MENU_LEV_IMM,		MENU_LEV_TRIG,		NULL_MENU, 			MENU_RES_LEV, 	MENU_IMM_AMPL,	NULL, 		NULL);
      MENU_ITEM('1',"R:::[AMPLitude]",  MENU_IMM_AMPL,		NULL_MENU,			NULL_MENU, 			MENU_LEV_IMM, 	NULL_MENU,		NULL, 		UIACT_ResistanceImmediateValue);

    MENU_ITEM('2',	"RES::TRIGgered",	MENU_LEV_TRIG,		MENU_LEV_STEP,		MENU_LEV_IMM,		MENU_RES_LEV, 	MENU_TRIG_AMPL,	NULL, 		NULL);
      MENU_ITEM('1',"R:::[AMPLitude]",  MENU_TRIG_AMPL,		NULL_MENU,			NULL_MENU, 			MENU_LEV_TRIG,	NULL_MENU,		NULL, 		UIACT_ResistanceTriggeredValue);

    MENU_ITEM('3',	"RES::STEP", 		MENU_LEV_STEP,		NULL_MENU,			MENU_LEV_TRIG,		MENU_RES_LEV, 	MENU_STEP_INCR,	NULL, 		NULL);
      MENU_ITEM('1',"R::S:[INCRement]", MENU_STEP_INCR,		MENU_STEP_MODE,		NULL_MENU, 			MENU_LEV_STEP,	NULL_MENU,		NULL, 		UIACT_ResistanceStepIncrement);
      MENU_ITEM('2',"R::S:MODE",		MENU_STEP_MODE,		MENU_STEP_OVER,		MENU_STEP_INCR,		MENU_LEV_STEP,	NULL_MENU,		NULL, 		UIACT_ResistanceStepMode);
      MENU_ITEM('3',"R::S:OVERflow",	MENU_STEP_OVER,		NULL_MENU, 			MENU_STEP_MODE,		MENU_LEV_STEP,	NULL_MENU,		NULL, 		UIACT_ResistanceStepOverflow);

  MENU_ITEM('2',	"RES:LIMit",		MENU_RES_LIM,		MENU_RES_MODE,		MENU_RES_LEV,		MENU_RES, 		MENU_LIM_LOW,	NULL, 		NULL);
	MENU_ITEM('1',	"RES:LIMit:LOW",	MENU_LIM_LOW,		MENU_LIM_HIGH,		NULL_MENU,			MENU_RES_LIM, 	NULL_MENU,		NULL, 		UIACT_ResistanceLimitLow);
	MENU_ITEM('2',	"RES:LIMit:HIGH",	MENU_LIM_HIGH,		MENU_LIM_STAT, 		MENU_LIM_LOW, 		MENU_RES_LIM, 	NULL_MENU,		NULL, 		UIACT_ResistanceLimitHigh);
	MENU_ITEM('3',	"RES:LIMit:STATe",	MENU_LIM_STAT,		NULL_MENU,	 		MENU_LIM_HIGH,		MENU_RES_LIM, 	NULL_MENU,		NULL, 		UIACT_ResistanceLimitState);

  MENU_ITEM('3',	"RES:MODE",		 	MENU_RES_MODE,		NULL_MENU, 			MENU_RES_LIM,		MENU_RES, 		NULL_MENU,		NULL, 		UIACT_SourceResistanceMode);

MENU_ITEM('8',		"SWITching",		MENU_SWIT,			MENU_SYST,			MENU_RES, 			NULL_MENU, 		MENU_SWIT_MODE,	NULL, 		NULL);
  MENU_ITEM('1',	"SWIT:MODE",		MENU_SWIT_MODE,		NULL_MENU, 			NULL_MENU,			MENU_SWIT, 		NULL_MENU,		NULL, 		UIACT_ResistanceSwitchingMode);

MENU_ITEM('9',		"SYSTem", 			MENU_SYST,			MENU_TRIG, 			MENU_SWIT, 			NULL_MENU, 		MENU_SYST_BEEP,	NULL, 		NULL);
  MENU_ITEM('1',	"SYST:BEEPer", 		MENU_SYST_BEEP,		MENU_SYST_DEF, 		NULL_MENU, 			MENU_SYST, 		MENU_BEEP_STAT,	NULL, 		NULL);
    MENU_ITEM('1',	"SYST:BEEP:STATe", 	MENU_BEEP_STAT,		NULL_MENU,	 		NULL_MENU, 			MENU_SYST_BEEP, NULL_MENU,		NULL, 		UIACT_SystemBeeper);
  MENU_ITEM('2',	"SYST:DEFault", 	MENU_SYST_DEF,		MENU_SYST_ERR, 		MENU_SYST_BEEP, 	MENU_SYST, 		MENU_DEF_IMM,	NULL, 		NULL);
    MENU_ITEM('1',	"S:DEF:[IMMediate]",MENU_DEF_IMM,		NULL_MENU,	 		NULL_MENU, 			MENU_SYST_DEF, 	NULL_MENU,		NULL, 		UIACT_SystemDefaultImmediate);
  MENU_ITEM('3',	"SYST:ERRor", 		MENU_SYST_ERR,		MENU_SYST_TEMP, 	MENU_SYST_DEF, 		MENU_SYST, 		MENU_ERR_COUN,	NULL, 		NULL);
    MENU_ITEM('1',	"SYST:ERR:COUNt", 	MENU_ERR_COUN,		MENU_ERR_NEXT, 		NULL_MENU, 			MENU_SYST_ERR, 	NULL_MENU,		NULL, 		UIACT_SystemErrorCount);
    MENU_ITEM('2',	"SYST:ERR:NEXT", 	MENU_ERR_NEXT,		NULL_MENU, 			MENU_ERR_COUN,		MENU_SYST_ERR, 	NULL_MENU,		NULL, 		UIACT_SystemErrorNext);
  MENU_ITEM('4',	"SYST:TEMPerature",	MENU_SYST_TEMP,		MENU_SYST_FVER, 	MENU_SYST_ERR, 		MENU_SYST, 		MENU_TEMP_TEMP,	NULL, 		NULL);
    MENU_ITEM('1',	"SYST:TEMP:*",		MENU_TEMP_TEMP,		MENU_TEMP_RES, 		NULL_MENU, 			MENU_SYST_TEMP, NULL_MENU,		NULL, 		UIACT_SystemTemperature);
    MENU_ITEM('2',	"SYST:TEMP:RESet", 	MENU_TEMP_RES,		NULL_MENU, 			MENU_TEMP_TEMP,		MENU_SYST_TEMP, NULL_MENU,		NULL, 		UIACT_SystemTemperatureReset);
  MENU_ITEM('5',	"SYST:FVERsion",	MENU_SYST_FVER,		MENU_SYST_SEC, 		MENU_SYST_TEMP,		MENU_SYST, 		MENU_FVER_MAIN,	NULL, 		NULL);
    MENU_ITEM('1',	"SYST:FVER:MAIN",	MENU_FVER_MAIN,		MENU_FVER_UI, 		NULL_MENU, 			MENU_SYST_FVER, NULL_MENU,		NULL, 		UIACT_SystemFirmwareVersionMainboard);
    MENU_ITEM('2',	"SYST:FVER:UI",		MENU_FVER_UI,		NULL_MENU, 			MENU_FVER_MAIN, 	MENU_SYST_FVER, NULL_MENU,		NULL, 		UIACT_SystemFirmwareVersionUI);
  MENU_ITEM('6',	"SYST:SECurity", 	MENU_SYST_SEC,		NULL_MENU, 			MENU_SYST_FVER, 	MENU_SYST, 		MENU_SEC_IMM,	NULL, 		NULL);
    MENU_ITEM('1',	"S:SEC:[IMMediate]",MENU_SEC_IMM,		NULL_MENU,	 		NULL_MENU, 			MENU_SYST_SEC, 	NULL_MENU,		NULL, 		UIACT_SystemSecurityImmediate);

MENU_ITEM('A',		"TRIGger",			MENU_TRIG,			NULL_MENU, 			MENU_SYST,			NULL_MENU, 		MENU_TRIG_SEQ,	NULL, 		NULL);
  MENU_ITEM('1',	"TRIG:SEQuence",	MENU_TRIG_SEQ,		NULL_MENU, 			NULL_MENU,			MENU_TRIG, 		MENU_SEQ_DEL,	NULL, 		NULL);
    MENU_ITEM('1',	"TRIG:SEQ:DELay",	MENU_SEQ_DEL,		MENU_SEQ_HOLD,		NULL_MENU,			MENU_TRIG_SEQ, 	NULL_MENU,		NULL, 		UIACT_TriggerDelay);
    MENU_ITEM('2',	"TRIG:SEQ:HOLDoff", MENU_SEQ_HOLD,		MENU_SEQ_SOUR,		MENU_SEQ_DEL,		MENU_TRIG_SEQ, 	NULL_MENU,		NULL, 		UIACT_TriggerHoldoff);
    MENU_ITEM('3',	"TRIG:SEQ:SOURce",	MENU_SEQ_SOUR,		MENU_SEQ_SLOP,		MENU_SEQ_HOLD, 		MENU_TRIG_SEQ, 	NULL_MENU,		NULL, 		UIACT_TriggerSource);
    MENU_ITEM('4',	"TRIG:SEQ:SLOPe",	MENU_SEQ_SLOP,		MENU_SEQ_TIM,		MENU_SEQ_SOUR,		MENU_TRIG_SEQ, 	NULL_MENU,		NULL, 		UIACT_TriggerSlope);
    MENU_ITEM('5',	"TRIG:SEQ:TIMER",	MENU_SEQ_TIM,		NULL_MENU, 			MENU_SEQ_SLOP,		MENU_TRIG_SEQ, 	NULL_MENU,		NULL, 		UIACT_TriggerTimer);

MENU_ITEM('1',		"*RCL", 			MENU_USER_SET,		NULL_MENU, 			NULL_MENU, 			NULL_MENU, 		MENU_RCL,		NULL, 		NULL);
  MENU_ITEM('1',	"*RCL", 			MENU_RCL,			MENU_SAVE,			NULL_MENU,			MENU_USER_SET, 	NULL_MENU,		NULL, 		UIACT_Rcl);
  MENU_ITEM('2',	"*SAV", 			MENU_SAVE,			NULL_MENU,			MENU_RCL, 			MENU_USER_SET, 	NULL_MENU,		NULL, 		UIACT_Sav);

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
