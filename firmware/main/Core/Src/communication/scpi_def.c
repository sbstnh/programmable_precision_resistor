/*
 * scpi_implementation.c
 *
 *  Created on: Aug 9, 2021
 *      Author: sebas
 */

/* Includes ------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "scpi/scpi.h"
#include "communication/scpi_def.h"

#include "util/util.h"
#include "util/circ_buf.h"

#include "communication/scpi_circ_buf_def.h"
#include "communication/scpi_calibration_def.h"
#include "communication/scpi_common_def.h"
#include "communication/scpi_display_def.h"
#include "communication/scpi_eeprom_def.h"
#include "communication/scpi_input_def.h"
#include "communication/scpi_route_def.h"
#include "communication/scpi_source_current_def.h"
#include "communication/scpi_source_digital_def.h"
#include "communication/scpi_source_list_def.h"
#include "communication/scpi_source_mode_def.h"
#include "communication/scpi_source_power_def.h"
#include "communication/scpi_source_resistance_def.h"
#include "communication/scpi_source_switching_def.h"
#include "communication/scpi_source_voltage_def.h"
#include "communication/scpi_system_def.h"
#include "communication/scpi_system_temp_def.h"
#include "communication/scpi_trigger_def.h"
#include "application/app_system.h"

#include "hardware/ui_interface_def.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

static const char separator[] = ",\"";
static const char end[] = "\"\n";

/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

static size_t SCPI_Write(scpi_t *context, const char *data, size_t len);
static int SCPI_Error(scpi_t *context, int_fast16_t err);

/* Exported variables --------------------------------------------------------*/

scpi_interface_t scpi_interface =
{
		.error = SCPI_Error, //SCPI_Error,
		.write = SCPI_Write,
		.control = NULL, //SCPI_Control,
		.flush = NULL, //SCPI_Flush,
		.reset = NULL, //SCPI_Reset,
};

char scpi_input_buffer[SCPI_INPUT_BUFFER_LENGTH];
scpi_error_t scpi_error_queue_data[SCPI_ERROR_QUEUE_SIZE];

scpi_t scpi_context;


const scpi_command_t scpi_commands[] =
{
		/* IEEE Mandated Commands (SCPI std V1999.0 4.1.1) */
		{ .pattern = "*CLS",													.callback = SCPI_CoreCls, },
		{ .pattern = "*ESE",													.callback = SCPI_CoreEse, },
		{ .pattern = "*ESE?",													.callback = SCPI_CoreEseQ, },
		{ .pattern = "*ESR?",													.callback = SCPI_CoreEsrQ, },
		{ .pattern = "*IDN?",													.callback = SCPI_CoreIdnQ, },
		{ .pattern = "*OPC",													.callback = SCPI_CoreOpc, },
		{ .pattern = "*OPC?",													.callback = SCPI_CoreOpcQ, },
		{ .pattern = "*RST",													.callback = SCPI_CoreRst, },
		{ .pattern = "*SRE",													.callback = SCPI_CoreSre, },
		{ .pattern = "*SRE?",													.callback = SCPI_CoreSreQ, },
		{ .pattern = "*STB?",													.callback = SCPI_CoreStbQ, },
		{ .pattern = "*TST?",													.callback = SCPI_CMD_CoreTstQ, },
		{ .pattern = "*WAI",													.callback = SCPI_CoreWai, },

		/* Required SCPI commands (SCPI std V1999.0 4.2.1) */
		{ .pattern = "SYSTem:ERRor[:NEXT]?",									.callback = SCPI_SystemErrorNextQ, },
		{ .pattern = "SYSTem:ERRor:COUNt?",										.callback = SCPI_SystemErrorCountQ, },
		{ .pattern = "SYSTem:VERSion?",											.callback = SCPI_SystemVersionQ, },

		{ .pattern = "STATus:QUEStionable[:EVENt]?",							.callback = SCPI_StatusQuestionableEventQ, },
		{ .pattern = "STATus:QUEStionable:CONDition?",							.callback = SCPI_StatusQuestionableConditionQ, },
		{ .pattern = "STATus:QUEStionable:ENABle",								.callback = SCPI_StatusQuestionableEnable, },
		{ .pattern = "STATus:QUEStionable:ENABle?",								.callback = SCPI_StatusQuestionableEnableQ, },

		{ .pattern = "STATus:PRESet",											.callback = SCPI_StatusPreset, },

		/* Application level */

		{ .pattern = "*RCL",													.callback = SCPI_CMD_COMM_RCL, }, // <numeric_value>
		{ .pattern = "*SAV",													.callback = SCPI_CMD_COMM_SAV, }, // <numeric_value>
		{ .pattern = "*TRG",													.callback = SCPI_CMD_TRIG_TRG, },

		{ .pattern = "ABORt[:IMMediate]",										.callback = SCPI_CMD_TRIG_ABOR_IMMediate, }, // Aborts trigger activation

		{ .pattern = "CALibration:COUNt?",										.callback = SCPI_CMD_CAL_COUNt_Q, }, // <numeric_value>
		{ .pattern = "CALibration:DATE",										.callback = SCPI_CMD_CAL_DATE, }, // <string>
		{ .pattern = "CALibration:DATE?",										.callback = SCPI_CMD_CAL_DATE_Q, },
		{ .pattern = "CALibration:SAVE",										.callback = SCPI_CMD_CAL_SAVE, },
		{ .pattern = "CALibration:SECure[:STATe]",								.callback = SCPI_CMD_CAL_SEC_STATe, }, // <boolean>
		{ .pattern = "CALibration:SECure[:STATe]?",								.callback = SCPI_CMD_CAL_SEC_STATe_Q, },
		{ .pattern = "CALibration:SETup",										.callback = SCPI_CMD_CAL_SETup, }, // <numeric_value>
		{ .pattern = "CALibration:SETup?",										.callback = SCPI_CMD_CAL_SETup_Q, },
		{ .pattern = "CALibration[:STATe]",										.callback = SCPI_CMD_CAL_STATe, }, // <boolean>
		{ .pattern = "CALibration[:STATe]?",									.callback = SCPI_CMD_CAL_STATe_Q, },
		{ .pattern = "CALibration:STRing",										.callback = SCPI_CMD_CAL_STRing, }, // <string>
		{ .pattern = "CALibration:STRing?",										.callback = SCPI_CMD_CAL_STRing_Q, },
		{ .pattern = "CALibration:TEMPerature?",								.callback = SCPI_CMD_CAL_TEMPerature_Q, },
		{ .pattern = "CALibration:VALue",										.callback = SCPI_CMD_CAL_VALue, },
		{ .pattern = "CALibration:VALue?",										.callback = SCPI_CMD_CAL_VALue_Q, },

		{ .pattern = "DISPlay:ENABle",											.callback = SCPI_CMD_DISP_ENABle, }, // <Boolean>
		{ .pattern = "DISPlay:ENABle?",											.callback = SCPI_CMD_DISP_ENABle_Q, },
		{ .pattern = "DISPlay[:USER]:TEXT[:DATA]",								.callback = SCPI_CMD_DISP_USER_TEXT_DATA, }, // <string>
		{ .pattern = "DISPlay[:USER]:TEXT[:DATA]?",								.callback = SCPI_CMD_DISP_USER_TEXT_DATA_Q, },
		{ .pattern = "DISPlay[:USER]:TEXT:STATe",								.callback = SCPI_CMD_DISP_USER_TEXT_STATe, }, // <Boolean>
		{ .pattern = "DISPlay[:USER]:TEXT:STATe?",								.callback = SCPI_CMD_DISP_USER_TEXT_STATe_Q, },
		{ .pattern = "DISPlay[:USER]:TEXT:CLEar",								.callback = SCPI_CMD_DISP_USER_TEXT_CLEar, }, // Event
		{ .pattern = "DISPlay:MAIN[:PRIMary][:RESolution]",						.callback = SCPI_CMD_DISP_MAIN_PRIM_RESolution, }, // DEFault|THRee|FOUR|FIVE|SIX
		{ .pattern = "DISPlay:MAIN[:PRIMary][:RESolution]?",					.callback = SCPI_CMD_DISP_MAIN_PRIM_RESolution_Q, },
		{ .pattern = "DISPlay:MAIN:SECondary[:MODE]",							.callback = SCPI_CMD_DISP_MAIN_MODE, }, // DEFAULT|AUTO|STATe|CURRent|VOLTage|POWer|RESistance
		{ .pattern = "DISPlay:MAIN:SECondary[:MODE]?",							.callback = SCPI_CMD_DISP_MAIN_MODE_Q, },

		{ .pattern = "INITiate[:IMMediate]",									.callback = SCPI_CMD_TRIG_INIT_IMMediate, }, // Triggers immediately (Event), If the device is not in IDLE or if INITiate:CONTinuous is set to ON, an IMMediate command shall have no effect on the	trigger system and an error -213 shall be generated.
		{ .pattern = "INITiate:CONTinuous",										.callback = SCPI_CMD_TRIG_INIT_CONTinuous, }, // <Boolean>
		{ .pattern = "INITiate:CONTinuous?",									.callback = SCPI_CMD_TRIG_INIT_CONTinuous_Q, },

		{ .pattern = "INPut:INHibit:MODE",										.callback = SCPI_CMD_INP_INH_MODE, }, // LATChing|LIVE|OFF
		{ .pattern = "INPut:INHibit:MODE?",										.callback = SCPI_CMD_INP_INH_MODE_Q, },
		{ .pattern = "INPut:INHibit[:STATe]?",									.callback = SCPI_CMD_INP_INH_STATe_Q, },
		{ .pattern = "INPut:INHibit:CLEar",										.callback = SCPI_CMD_INP_INH_CLEar, },
		{ .pattern = "INPut[:STATe]",											.callback = SCPI_CMD_INP_STATe, }, // <Boolean>
		{ .pattern = "INPut[:STATe]?",											.callback = SCPI_CMD_INP_STATe_Q, },

		{ .pattern = "MEMory:FORMat",											.callback = SCPI_CMD_MEM_FORMat, },
		{ .pattern = "MEMory[:DATA][:VLENgth]",									.callback = SCPI_CMD_MEM_DATA_VLENgth, }, // <address(numeric_value)>,<length, 1..4>,<value>
		{ .pattern = "MEMory[:DATA][:VLENgth]?",								.callback = SCPI_CMD_MEM_DATA_VLENgth_Q, }, // <address(numeric_value)>,<length, 1..4>
		{ .pattern = "MEMory[:DATA]:BLOCk?",									.callback = SCPI_CMD_MEM_DATA_BLOCk_Q, }, // <address(numeric_value)>,<length>
		{ .pattern = "MEMory:PROTection[:STATe]",								.callback = SCPI_CMD_MEM_PROT_STATe, },  // <Boolean>
		{ .pattern = "MEMory:PROTection[:STATe]?",								.callback = SCPI_CMD_MEM_PROT_STATe_Q, },

		{ .pattern = "OUTPut[:STATe]",											.callback = SCPI_CMD_INP_STATe, }, // <Boolean>
		{ .pattern = "OUTPut[:STATe]?",											.callback = SCPI_CMD_INP_STATe_Q, },
		{ .pattern = "OUTPut:INHibit[:MODE]",									.callback = SCPI_CMD_INP_INH_MODE, }, // LATChing|LIVE|OFF
		{ .pattern = "OUTPut:INHibit[:MODE]?",									.callback = SCPI_CMD_INP_INH_MODE_Q, },
		{ .pattern = "OUTPut:INHibit[:STATe]?",									.callback = SCPI_CMD_INP_INH_STATe_Q, },
		{ .pattern = "OUTput:INHibit:CLEar",									.callback = SCPI_CMD_INP_INH_CLEar, },

		{ .pattern = "ROUTe[:RELay][:STATe]",									.callback = SCPI_CMD_ROUT_REL_STATe, }, // <boolean>
		{ .pattern = "ROUTe[:RELay][:STATe]?",									.callback = SCPI_CMD_ROUT_REL_STATe_Q, },
		{ .pattern = "ROUTe[:RELay]:OPEN",										.callback = SCPI_CMD_ROUT_REL_OPEN, },
		{ .pattern = "ROUTe[:RELay]:CLOSe",										.callback = SCPI_CMD_ROUT_REL_CLOSe, },

		{ .pattern = "[:SOURce]:CURRent[:LEVel][:IMMediate][:AMPLitude]?",		.callback = SCPI_CMD_SOUR_CURR_LEV_IMM_AMPLitude_Q, }, // MIN|MAX

		{ .pattern = "[:SOURce]:DIGital:PIN[:DATA]?",							.callback = SCPI_CMD_SOUR_DIG_PIN1_DATA_Q, },
		{ .pattern = "[:SOURce]:DIGital:PIN:FUNCtion",							.callback = SCPI_CMD_SOUR_DIG_PIN1_FUNCtion, },
		{ .pattern = "[:SOURce]:DIGital:PIN:FUNCtion?",							.callback = SCPI_CMD_SOUR_DIG_PIN1_FUNCtion_Q, },
		{ .pattern = "[:SOURce]:DIGital:PIN:POLarity",							.callback = SCPI_CMD_SOUR_DIG_PIN1_POLarity, }, // POSitive|NEGative|DEFault
		{ .pattern = "[:SOURce]:DIGital:PIN:POLarity?",							.callback = SCPI_CMD_SOUR_DIG_PIN1_POLarity_Q, },
		{ .pattern = "[:SOURce]:DIGital:PIN1[:DATA]?",							.callback = SCPI_CMD_SOUR_DIG_PIN1_DATA_Q, },
		{ .pattern = "[:SOURce]:DIGital:PIN1:FUNCtion",							.callback = SCPI_CMD_SOUR_DIG_PIN1_FUNCtion, },
		{ .pattern = "[:SOURce]:DIGital:PIN1:FUNCtion?",						.callback = SCPI_CMD_SOUR_DIG_PIN1_FUNCtion_Q, },
		{ .pattern = "[:SOURce]:DIGital:PIN1:POLarity",							.callback = SCPI_CMD_SOUR_DIG_PIN1_POLarity, }, // POSitive|NEGative|DEFault
		{ .pattern = "[:SOURce]:DIGital:PIN1:POLarity?",						.callback = SCPI_CMD_SOUR_DIG_PIN1_POLarity_Q, },
		{ .pattern = "[:SOURce]:DIGital:PIN2[:DATA]?",							.callback = SCPI_CMD_SOUR_DIG_PIN2_DATA_Q, },
		{ .pattern = "[:SOURce]:DIGital:PIN2:FUNCtion",							.callback = SCPI_CMD_SOUR_DIG_PIN2_FUNCtion, },
		{ .pattern = "[:SOURce]:DIGital:PIN2:FUNCtion?",						.callback = SCPI_CMD_SOUR_DIG_PIN2_FUNCtion_Q, },
		{ .pattern = "[:SOURce]:DIGital:PIN2:POLarity",							.callback = SCPI_CMD_SOUR_DIG_PIN2_POLarity, }, // POSitive|NEGative|DEFault
		{ .pattern = "[:SOURce]:DIGital:PIN2:POLarity?",						.callback = SCPI_CMD_SOUR_DIG_PIN2_POLarity_Q, },

		{ .pattern = "[:SOURce]:LIST:DWELl",									.callback = SCPI_CMD_SOUR_LIST_RES_DWELl, }, // Iterations: <number>{,<number>}
		{ .pattern = "[:SOURce]:LIST:DWELl?",									.callback = SCPI_CMD_SOUR_LIST_RES_DWELl_Q, }, // [MINimum|MAXimum]
		{ .pattern = "[:SOURce]:LIST:DWELl:POINts",								.callback = SCPI_CMD_SOUR_LIST_RES_DWEL_POINts, }, // <integer>
		{ .pattern = "[:SOURce]:LIST:DWELl:POINts?",							.callback = SCPI_CMD_SOUR_LIST_RES_DWEL_POINts_Q, }, // [MINimum|MAXimum]
		{ .pattern = "[:SOURce]:LIST[:RESistance]:INDex?",						.callback = SCPI_CMD_SOUR_LIST_RES_INDex_Q, }, // [MINimum|MAXimum] (current position in list)
		{ .pattern = "[:SOURce]:LIST[:RESistance][:LEVel]",						.callback = SCPI_CMD_SOUR_LIST_RES_LEVel, }, // <index>,<resistance>
		{ .pattern = "[:SOURce]:LIST[:RESistance][:LEVel]?",					.callback = SCPI_CMD_SOUR_LIST_RES_LEVel_Q, }, // [MINimum|MAXimum]
		{ .pattern = "[:SOURce]:LIST[:RESistance]:POINts",						.callback = SCPI_CMD_SOUR_LIST_RES_POINts, }, //<integer>
		{ .pattern = "[:SOURce]:LIST[:RESistance]:POINts?",						.callback = SCPI_CMD_SOUR_LIST_RES_POINts_Q, }, // [MINimum|MAXimum]
		{ .pattern = "[:SOURce]:LIST[:RESistance]:RUN[:NUMBer]?",				.callback = SCPI_CMD_SOUR_LIST_RES_RUN_NUMBer_Q, }, // Iterations: <numeric_value>|MINimum|MAXimum
		{ .pattern = "[:SOURce]:LIST[:RESistance]:RUN:COUNt",					.callback = SCPI_CMD_SOUR_LIST_RES_RUN_COUNt, }, // Iterations: <numeric_value>|MINimum|MAXimum|INFinity
		{ .pattern = "[:SOURce]:LIST[:RESistance]:RUN:COUNt?",					.callback = SCPI_CMD_SOUR_LIST_RES_RUN_COUNt_Q, }, // Iterations: [MINimum|MAXimum]
		{ .pattern = "[:SOURce]:LIST:STARt[:INPut]",							.callback = SCPI_CMD_SOUR_LIST_STAR_INPut, }, // AUTO|TRIGger|DEFault
		{ .pattern = "[:SOURce]:LIST:STARt[:INPut]?",							.callback = SCPI_CMD_SOUR_LIST_STAR_INPut_Q, },
		{ .pattern = "[:SOURce]:LIST:STARt:MODE",								.callback = SCPI_CMD_SOUR_LIST_STAR_MODE, }, // AUTO|TRIGger|DEFault
		{ .pattern = "[:SOURce]:LIST:STARt:MODE?",								.callback = SCPI_CMD_SOUR_LIST_STAR_MODE_Q, },
		{ .pattern = "[:SOURce]:LIST:STEP",										.callback = SCPI_CMD_SOUR_LIST_STEP, }, // AUTO|TRIGger|ONCE|DEFault (see also: Keysight EL34243 programming manual)
		{ .pattern = "[:SOURce]:LIST:STEP?",									.callback = SCPI_CMD_SOUR_LIST_STEP_Q, },
		{ .pattern = "[:SOURce]:LIST:TERMinate[:INPut]",						.callback = SCPI_CMD_SOUR_LIST_TERM_INPut, }, // <Boolean> (true disables input)
		{ .pattern = "[:SOURce]:LIST:TERMinate[:INPut]?",						.callback = SCPI_CMD_SOUR_LIST_TERM_INPut_Q, },
		{ .pattern = "[:SOURce]:LIST:TERMinate:LAST",							.callback = SCPI_CMD_SOUR_LIST_TERM_LAST, }, // <Boolean> (true: remain at last list step)
		{ .pattern = "[:SOURce]:LIST:TERMinate:LAST?",							.callback = SCPI_CMD_SOUR_LIST_TERM_LAST_Q, },

		{ .pattern = "[:SOURce]:MODE",											.callback = SCPI_CMD_SOUR_MODE, }, // DEFault|UNCalibrated|TWIRe|FWIRe
		{ .pattern = "[:SOURce]:MODE?",											.callback = SCPI_CMD_SOUR_MODE_Q, },

		{ .pattern = "[:SOURce]:POWer[:LEVel][:IMMediate][:AMPLitude]?",		.callback = SCPI_CMD_SOUR_POW_LEV_IMM_AMPLitude_Q, }, // MIN|MAX

		{ .pattern = "[:SOURce]:RESistance[:LEVel][:IMMediate][:AMPLitude]",	.callback = SCPI_CMD_SOUR_RES_LEV_IMM_AMPLitude, }, // <resistance>|MINimum|MAXimum|UP|DOWN
		{ .pattern = "[:SOURce]:RESistance[:LEVel][:IMMediate][:AMPLitude]?",	.callback = SCPI_CMD_SOUR_RES_LEV_IMM_AMPLitude_Q, }, // [MIN|MAX]
		{ .pattern = "[:SOURce]:RESistance[:LEVel][:IMMediate]:CALCulate?",		.callback = SCPI_CMD_SOUR_RES_LEV_IMM_CALCulate_Q, }, // UNCalibrated|TWIRe|FWIRe|DEFault
		{ .pattern = "[:SOURce]:RESistance[:LEVel]:TRIGgered[:AMPLitude]",		.callback = SCPI_CMD_SOUR_RES_LEV_TRIG_AMPLitude, }, // <resistance>|MINimum|MAXimum|UP|DOWN
		{ .pattern = "[:SOURce]:RESistance[:LEVel]:TRIGgered[:AMPLitude]?",		.callback = SCPI_CMD_SOUR_RES_LEV_TRIG_AMPLitude_Q, }, // [MINimum|MAXimum]
		{ .pattern = "[:SOURce]:RESistance[:LEVel]:TRIGgered:CALCulate?",		.callback = SCPI_CMD_SOUR_RES_LEV_TRIG_CALCulate_Q, }, // <resistance>|UNCalibrated|TWIRe|FWIRe|DEFault

		{ .pattern = "[:SOURce]:RESistance[:LEVel]:STEP[:INCRement]",			.callback = SCPI_CMD_SOUR_RES_LEV_STEP_INCRement, }, // <resistance>|DEFault|MINimum|MAXimum
		{ .pattern = "[:SOURce]:RESistance[:LEVel]:STEP[:INCRement]?",			.callback = SCPI_CMD_SOUR_RES_LEV_STEP_INCRement_Q, }, // [MINimum|MAXimum]
		{ .pattern = "[:SOURce]:RESistance[:LEVel]:STEP:MODE",					.callback = SCPI_CMD_SOUR_RES_LEV_STEP_MODE, }, // LINear|LDECade|L125|L13
		{ .pattern = "[:SOURce]:RESistance[:LEVel]:STEP:MODE?",					.callback = SCPI_CMD_SOUR_RES_LEV_STEP_MODE_Q, },
		{ .pattern = "[:SOURce]:RESistance[:LEVel]:STEP:OVERflow",				.callback = SCPI_CMD_SOUR_RES_LEV_STEP_OVERflow, }, // LIMit|STAY|RESet
		{ .pattern = "[:SOURce]:RESistance[:LEVel]:STEP:OVERflow?",				.callback = SCPI_CMD_SOUR_RES_LEV_STEP_OVERflow_Q, },

		{ .pattern = "[:SOURce]:RESistance:LIMit:LOW",							.callback = SCPI_CMD_SOUR_RES_LIM_LOW, }, // <resistance>|MINimum|MAXimum
		{ .pattern = "[:SOURce]:RESistance:LIMit:LOW?",							.callback = SCPI_CMD_SOUR_RES_LIM_LOW_Q, }, // [MINimum|MAXimum]
		{ .pattern = "[:SOURce]:RESistance:LIMit:HIGH",							.callback = SCPI_CMD_SOUR_RES_LIM_HIGH, }, // <resistance>|MINimum|MAXimum
		{ .pattern = "[:SOURce]:RESistance:LIMit:HIGH?",						.callback = SCPI_CMD_SOUR_RES_LIM_HIGH_Q, }, // [MINimum|MAXimum]
		{ .pattern = "[:SOURce]:RESistance:LIMit[:STATe]",						.callback = SCPI_CMD_SOUR_RES_LIM_STATe, }, // <Boolean>
		{ .pattern = "[:SOURce]:RESistance:LIMit[:STATe]?",						.callback = SCPI_CMD_SOUR_RES_LIM_STATe_Q, }, //

		{ .pattern = "[:SOURce]:RESistance:MODE",								.callback = SCPI_CMD_SOUR_RES_MODE, }, // FIXed|STEP|UP|DOWN|LIST
		{ .pattern = "[:SOURce]:RESistance:MODE?",								.callback = SCPI_CMD_SOUR_RES_MODE_Q, }, //

		{ .pattern = "[:SOURce]:SWITching[:MODE]",								.callback = SCPI_CMD_SOUR_SWIT_MODE, }, // DEFault|SIMPle|BBMake|MBBReak
		{ .pattern = "[:SOURce]:SWITching[:MODE]?",								.callback = SCPI_CMD_SOUR_SWIT_MODE_Q, },

		{ .pattern = "[:SOURce]:VOLTage[:LEVel][:IMMediate][:AMPLitude]?",		.callback = SCPI_CMD_SOUR_VOLT_LEV_IMM_AMPLitude_Q, }, // MIN|MAX

		{ .pattern = "SYSTem:BEEPer[:IMMediate]",								.callback = SCPI_CMD_SYST_BEEP_IMMediate, }, //
		{ .pattern = "SYSTem:BEEPer:STATe",										.callback = SCPI_CMD_SYST_BEEP_STATe, },
		{ .pattern = "SYSTem:BEEPer:STATe?",									.callback = SCPI_CMD_SYST_BEEP_STATe_Q, },

		{ .pattern = "SYSTem:COMMunicate:RLSTate",								.callback = SCPI_CMD_SYST_COMM_RLSTate, }, // LOCal|MIXed|REMote|RWLock
		{ .pattern = "SYSTem:COMMunicate:RLSTate?",								.callback = SCPI_CMD_SYST_COMM_RLSTate_Q, },

		{ .pattern = "SYSTem:DEFault[:IMMediate]",								.callback = SCPI_CMD_SYST_DEF_IMMediate, },

		{ .pattern = "SYSTem:FVERsion[:MAIN]?",									.callback = SCPI_CMD_SYST_FVER_MAIN_Q, },
		{ .pattern = "SYSTem:FVERsion:UI?",										.callback = SCPI_CMD_SYST_FVER_UI_Q, },

		{ .pattern = "SYSTem:LOCal",											.callback = SCPI_CMD_SYST_LOCal, },
		{ .pattern = "SYSTem:MIXed",											.callback = SCPI_CMD_SYST_MIXed, },
		{ .pattern = "SYSTem:REMote",											.callback = SCPI_CMD_SYST_REMote, },
		{ .pattern = "SYSTem:RWLock",											.callback = SCPI_CMD_SYST_RWLock, },

		{ .pattern = "SYSTem:SECurity[:IMMediate]",								.callback = SCPI_CMD_SYST_SEC_IMMediate, },

		{ .pattern = "SYSTem:TEMPerature[:IMMediate]?",							.callback = SCPI_CMD_SYST_TEMP_IMMediate_Q, },
		{ .pattern = "SYSTem:TEMPerature:AVERage?",								.callback = SCPI_CMD_SYST_TEMP_AVERage_Q, },
		{ .pattern = "SYSTem:TEMPerature:MINimum?",								.callback = SCPI_CMD_SYST_TEMP_MINimum_Q, },
		{ .pattern = "SYSTem:TEMPerature:MAXimum?",								.callback = SCPI_CMD_SYST_TEMP_MAXimum_Q, },
		{ .pattern = "SYSTem:TEMPerature:RESet",								.callback = SCPI_CMD_SYST_TEMP_RESet, },

		{ .pattern = "TRIGger:ABORt[:IMMediate]",								.callback = SCPI_CMD_TRIG_ABOR_IMMediate, }, // Returns trigger to idle state
		{ .pattern = "TRIGger:INITiate[:IMMediate]",							.callback = SCPI_CMD_TRIG_INIT_IMMediate, }, // Triggers immediately (Event), If the device is not in IDLE or if INITiate:CONTinuous is set to ON, an IMMediate command shall have no effect on the	trigger system and an error -213 shall be generated.
		{ .pattern = "TRIGger:INITiate:CONTinuous",								.callback = SCPI_CMD_TRIG_INIT_CONTinuous, }, // <Boolean>
		{ .pattern = "TRIGger:INITiate:CONTinuous?",							.callback = SCPI_CMD_TRIG_INIT_CONTinuous_Q, },
		{ .pattern = "TRIGger[:SEQuence][:IMMediate]",							.callback = SCPI_CMD_TRIG_SEQ_IMMediate, }, // Triggers immediately (Event), when already initiated
		{ .pattern = "TRIGger[:SEQuence]:DELay",								.callback = SCPI_CMD_TRIG_SEQ_DELay, }, // <numeric_value> (Error -222 when negative, 0/smallest value when *RST)
		{ .pattern = "TRIGger[:SEQuence]:DELay?",								.callback = SCPI_CMD_TRIG_SEQ_DELay_Q, }, // [MIN|MAX]
		{ .pattern = "TRIGger[:SEQuence]:HOLDoff",								.callback = SCPI_CMD_TRIG_SEQ_HOLDoff, }, // <numeric_value> (Error -222 when negative, 0/smallest value when *RST)
		{ .pattern = "TRIGger[:SEQuence]:HOLDoff?",								.callback = SCPI_CMD_TRIG_SEQ_HOLDoff_Q, }, // [MIN|MAX]
		{ .pattern = "TRIGger[:SEQuence]:SOURce",								.callback = SCPI_CMD_TRIG_SEQ_SOURce, }, // BUS|EXTernal1|EXTernal2|IMMediate|MANual|TIMer
		{ .pattern = "TRIGger[:SEQuence]:SOURce?",								.callback = SCPI_CMD_TRIG_SEQ_SOURce_Q, }, //

		{ .pattern = "TRIGger[:SEQuence]:SLOPe",								.callback = SCPI_CMD_TRIG_SEQ_SLOPe, }, // POSitive|NEGative|EITHer|DEFault
		{ .pattern = "TRIGger[:SEQuence]:SLOPe?",								.callback = SCPI_CMD_TRIG_SEQ_SLOPe_Q, }, //
		{ .pattern = "TRIGger[:SEQuence]:TIMer",								.callback = SCPI_CMD_TRIG_SEQ_TIMer, }, // <numeric_value> (Error -222 when negative)
		{ .pattern = "TRIGger[:SEQuence]:TIMer?",								.callback = SCPI_CMD_TRIG_SEQ_TIMer_Q, }, // MIN|MAX

		SCPI_CMD_LIST_END
};


/* Exported functions --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

static size_t SCPI_Write(scpi_t *context, const char *data, size_t len)
{
	(void) context;
	return CBUF_Write(&SCPI_CIRC_BUF_TX, (uint8_t *) data, len);
}

static int SCPI_Error(scpi_t *context, int_fast16_t err)
{
    char err_code_as_str[10];
    const char *err_message;

    (void)context;

    if (err)
    {
    	APP_Run_SystemBeeperBeepError();
    }

    SCPI_Int32ToStr(err, err_code_as_str, sizeof(err_code_as_str));
    CBUF_Write(&SCPI_CIRC_BUF_TX, (uint8_t *) err_code_as_str, strlen(err_code_as_str));
    CBUF_Write(&SCPI_CIRC_BUF_TX, (uint8_t *) separator, strlen(separator));
    err_message = SCPI_ErrorTranslate(err);
    CBUF_Write(&SCPI_CIRC_BUF_TX, (uint8_t *) err_message, strlen(err_message));
    CBUF_Write(&SCPI_CIRC_BUF_TX, (uint8_t *) end, strlen(end));

    return 0;
}
