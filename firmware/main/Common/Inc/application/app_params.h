/**
 * @file    app.h
 * @author  sebas
 * @date    Nov 12, 2022
 * @brief
 */
#ifndef INC_APPLICATION_APP_PARAMS_H_
#define INC_APPLICATION_APP_PARAMS_H_

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdint.h>
#include "calibration/cal_data.h"
#include "calibration/cal_mode.h"
#include "util/api.h"

/* Exported constants --------------------------------------------------------*/

#define DISP_USER_TEXT_LENGTH			64
#define SOUR_DIG_PIN_COUNT				2
#define SOUR_LIST_LENGTH				100

/* Exported types ------------------------------------------------------------*/

//--- Data types

typedef struct
{
	int32_t value;
	int32_t min;
	int32_t max;
} INT_VALUE_TypeDef;

typedef struct
{
	int32_t values[SOUR_LIST_LENGTH];
	INT_VALUE_TypeDef length;
} LIST_TypeDef;

//--- Common subsystems

typedef struct
{
	INT_VALUE_TypeDef AMPLitude;
} LEV_IMMediate_TypeDef;

typedef struct
{
	INT_VALUE_TypeDef AMPLitude;
} LEV_TRIGgered_TypeDef;


//--- CALibration subsystem

	typedef struct
	{
		bool STATe;
	} CAL_SECure_TypeDef;

typedef struct
{
	CAL_SECure_TypeDef SECure;
	int8_t SETup;
	bool STATe;

	CALDATA_TypeDef cal_data;

	uint64_t _cal_setup_2w_completed;
	uint64_t _cal_setup_4w_completed;

	float _start_temp;
	float _last_setup_temp;
} CALibration_TypeDef;

//--- DISPlay subsystem

		typedef struct
		{
			char DATA[DISP_USER_TEXT_LENGTH];
			bool STATe;
		} USER_TEXT_TypeDef;

	typedef struct
	{
		USER_TEXT_TypeDef TEXT;
	} DISP_USER_TypeDef;

			typedef enum
			{
				PRIM_RES_THRee,
				PRIM_RES_FOUR,
				PRIM_RES_FIVE,
				PRIM_RES_SIX
			} PRIM_RESolution_TypeDef;

		typedef struct
		{
			PRIM_RESolution_TypeDef RESolution;
		} DISP_PRIMary_TypeDef;

			typedef enum
			{
				SEC_MODE_STATe,
				SEC_MODE_CURRent,
				SEC_MODE_VOLTage,
				SEC_MODE_POWer,
				SEC_MODE_TRIGger,
				SEC_MODE_RESistance,
				SEC_MODE_LINDex,
				SEC_MODE_LNUMber
			} SEC_MODE_TypeDef;

		typedef struct
		{
			SEC_MODE_TypeDef MODE;
		} DISP_SECondary_TypeDef;

	typedef struct
	{
		DISP_PRIMary_TypeDef PRIMary;
		DISP_SECondary_TypeDef SECondary;
	} DISP_MAIN_TypeDef;

typedef struct
{
	bool ENABle;
	DISP_USER_TypeDef USER;
	DISP_MAIN_TypeDef MAIN;
} DISPlay_TypeDef;

//--- INPut (alias OUTPut) subsystem

		typedef enum
		{
			INH_MODE_OFF,
			INH_MODE_LATChing,
			INH_MODE_LIVE
		} INH_MODE_TypeDef;

	typedef struct
	{
		INH_MODE_TypeDef MODE;
		bool STATe;
	} INP_INHibit_TypeDef;

		typedef enum
		{
			PON_STAT_RST,
			PON_STAT_RCL0,
			PON_STAT_RCL1,
			PON_STAT_RCL2,
			PON_STAT_RCL3,
			PON_STAT_RCL4,
			PON_STAT_RCL5,
			PON_STAT_RCL6,
			PON_STAT_RCL7,
			PON_STAT_RCL8,
			PON_STAT_RCL9
		} PON_STATe_TypeDef;

	typedef struct
	{
		PON_STATe_TypeDef STATe;
	} INP_PON_TypeDef;

typedef struct
{
	INP_INHibit_TypeDef INHibit;
	INP_PON_TypeDef PON;
	bool STATe;
} INPut_TypeDef;

//--- SOURCE subsystem

		typedef struct
		{
			LEV_IMMediate_TypeDef IMMediate;
		} CURR_LEVel_TypeDef;

	typedef struct
	{
		CURR_LEVel_TypeDef LEVel;
	} SOUR_CURRent_TypeDef;

			typedef enum
			{
				PIN_FUNC_DINPut,
				PIN_FUNC_INHibit,
				PIN_FUNC_TINPut,
			} PIN_FUNCtion_TypeDef;

			typedef enum
			{
				PIN_POL_POSitive,
				PIN_POL_NEGative
			} PIN_POLarity_TypeDef;

		typedef struct
		{
			bool DATA;
			PIN_FUNCtion_TypeDef FUNCtion;
			PIN_POLarity_TypeDef POLarity;
		} DIG_PIN_TypeDef;

		typedef enum
		{
			SOUR_DIG_PIN1 = 0,
			SOUR_DIG_PIN2 = 1
		} DIG_PIN_Enum_TypeDef;

	typedef struct
	{
		DIG_PIN_TypeDef PIN[SOUR_DIG_PIN_COUNT];
	} SOUR_DIGital_TypeDef;

			typedef struct
			{
				INT_VALUE_TypeDef NUMBer;	///< Number of run (0-based, i. e. 0 stands for the first run)
				INT_VALUE_TypeDef COUNt;	///< Maximum number of runs, 0: infinity
			} LIST_RES_RUN_TypeDef;

		typedef struct
		{
			LIST_TypeDef LEVel;
			INT_VALUE_TypeDef INDex;
			LIST_RES_RUN_TypeDef RUN;
			LIST_TypeDef DWELl;

			int32_t _IMMediate_Backup;
			int32_t _DWELl_TimeLeft;
		} LIST_RESistance_TypeDef;

			typedef enum
			{
				LIST_START_AUTO,	///< Start automatically, immediately
				LIST_START_TRIGger	///< Start on next trigger event
			} STARt_MODE_TypeDef;

		typedef struct
		{
			bool INPut;
			STARt_MODE_TypeDef MODE;
		} LIST_STARt_TypeDef;

		typedef enum
		{
			LIST_STEP_AUTO,		///< Advance index automatically, solely based on DWELl time
			LIST_STEP_TRIGger,	///< Advance index on each trigger event, ignore DWELl time
			LIST_STEP_ONCE		///< Advance index on each trigger event, after DWELl time elapsed
		} LIST_STEP_TypeDef;

		typedef struct
		{
			bool INPut;
			bool LAST;
		} LIST_TERMinate_TypeDef;

		typedef enum
		{
			LIST_STATE_INIT,
			LIST_STATE_WAIT_FOR_TRIG,
			LIST_STATE_RUN,
			LIST_STATE_TERMINATE
		} LIST_StateTypeDef;

	typedef struct
	{
		LIST_RESistance_TypeDef RESistance;
		LIST_STARt_TypeDef STARt;
		LIST_STEP_TypeDef STEP;
		LIST_TERMinate_TypeDef TERMinate;

		LIST_StateTypeDef _state;
	} SOUR_LIST_TypeDef;

	typedef enum
	{
		SOUR_MODE_TWIRe,
		SOUR_MODE_FWIRe,
		SOUR_MODE_UNCalibrated

	} SOUR_MODE_TypeDef;

		typedef struct
		{
			LEV_IMMediate_TypeDef IMMediate;
		} POWer_LEVel_TypeDef;

	typedef struct
	{
		POWer_LEVel_TypeDef LEVel;
	} SOUR_POWer_TypeDef;

				typedef enum
				{
					STEP_MODE_LINear,
					STEP_MODE_LDECade,
					STEP_MODE_L125,
					STEP_MODE_L13
				} STEP_MODE_TypeDef;

				typedef enum
				{
					STEP_OVER_LIMit,
					STEP_OVER_STAY,
					STEP_OVER_RESet
				} STEP_OVERflow_TypeDef;

			typedef struct
			{
				INT_VALUE_TypeDef INCRement;
				//INT_VALUE_TypeDef PDECade;
				STEP_MODE_TypeDef MODE;
				STEP_OVERflow_TypeDef OVERflow;
			} LEV_STEP_TypeDef;

		typedef struct
		{
			LEV_IMMediate_TypeDef IMMediate; // ggf. SP_TypeDef immediate_setpoint;
			LEV_TRIGgered_TypeDef TRIGgered;
			LEV_STEP_TypeDef STEP;
		} RES_LEVel_TypeDef;

		typedef struct
		{
			INT_VALUE_TypeDef LOWer;
			bool STATe;
			INT_VALUE_TypeDef UPPer;
		} RES_LIMit_TypeDef;

		typedef enum
		{
			RES_MODE_FIXed,
			RES_MODE_STEP,
			RES_MODE_UP,
			RES_MODE_DOWN,
			RES_MODE_LIST
		} RES_MODE_TypeDef;

	typedef struct
	{
		RES_LEVel_TypeDef LEVel;
		RES_LIMit_TypeDef LIMit;
		RES_MODE_TypeDef MODE;
	} SOUR_RESistance_TypeDef;

		typedef enum
		{
			SOUR_SWIT_AUTO,
			SOUR_SWIT_BBMake
		} SWIT_MODE_TypeDef;

	typedef struct
	{
		SWIT_MODE_TypeDef MODE;
		bool _use_bypass;
	} SOUR_SWITching_TypeDef;

		typedef struct
		{
			LEV_IMMediate_TypeDef IMMediate;
		} VOLTage_LEVel_TypeDef;

	typedef struct
	{
		VOLTage_LEVel_TypeDef LEVel;
	} SOUR_VOLTage_TypeDef;

typedef struct
{
	SOUR_CURRent_TypeDef CURRent;
	SOUR_DIGital_TypeDef DIGital;
	SOUR_LIST_TypeDef LIST;
	SOUR_MODE_TypeDef MODE;
	SOUR_POWer_TypeDef POWer;
	SOUR_RESistance_TypeDef RESistance;
	SOUR_SWITching_TypeDef SWITching;
	SOUR_VOLTage_TypeDef VOLTage;
} SOURce_TypeDef;

// SYSTem subsystem

	typedef struct
	{
		bool STATe;
	} SYST_BEEPer_TypeDef;

		typedef enum
		{
			COMM_RLST_LOCal,
			COMM_RLST_MIXed,
			COMM_RLST_REMote,
			COMM_RLST_RWLock
		} COMM_RLSTate_TypeDef;

	typedef struct
	{
		COMM_RLSTate_TypeDef RLSTate;
	} SYST_COMMunicate_TypeDef;

		typedef enum
		{
			TEMP_SEL_1 = 0,
			TEMP_SEL_2 = 1,
			TEMP_SEL_AVG = 2,
			TEMP_SEL_ALL = 3
		} TEMP_SELection_TypeDef;

		typedef struct
		{
			uint32_t IMMediate;
			uint32_t AVERage;
			uint32_t MINimum;
			uint32_t MAXimum;
		} TEMP_INTernal_TypeDef;

	typedef struct
	{
		TEMP_INTernal_TypeDef INTernal;
	} SYST_TEMPeratur_TypeDef;

typedef struct
{
	SYST_BEEPer_TypeDef BEEPer;
	SYST_COMMunicate_TypeDef COMMunicate;
	SYST_TEMPeratur_TypeDef TEMPerature;
} SYSTem_TypeDef;

// TRIGger subsystem
	typedef struct
	{
		bool CONTinuous;
	} INITiate_TypeDef;

		typedef enum
		{
			SEQ_SOUR_BUS,
			SEQ_SOUR_EXTernal,
			SEQ_SOUR_IMMediate,
			SEQ_SOUR_MANual,
			SEQ_SOUR_TIMer,
		} SEQ_SOURce_TypeDef;

		typedef enum
		{
			SEQ_SLOP_POSITIVE,
			SEQ_SLOP_NEGATIVE,
			SEQ_SLOP_EITHER
		} SEQ_SLOPe_TypeDef;

	typedef struct
	{
		INT_VALUE_TypeDef DELay;
		INT_VALUE_TypeDef HOLDoff;
		SEQ_SOURce_TypeDef SOURce;
		SEQ_SLOPe_TypeDef SLOPe;
		INT_VALUE_TypeDef TIMer;
	} TRIG_SEQuence_TypeDef;

typedef struct
{
	INITiate_TypeDef INITiate;
	TRIG_SEQuence_TypeDef SEQuence;

	bool _bus_trig_received;
	bool _manual_trig_received;
} TRIGger_TypeDef;

//--- SCPI system

typedef struct
{
	CALibration_TypeDef CALibration;
	DISPlay_TypeDef DISPlay;
	INPut_TypeDef INPut;
	SOURce_TypeDef SOURce;
	SYSTem_TypeDef SYSTem;
	TRIGger_TypeDef TRIGger;
} APP_ParamTypeDef;

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

extern volatile APP_ParamTypeDef APP;

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

API_StatusTypeDef APP_UpdateIntValue(volatile INT_VALUE_TypeDef *int_value, int32_t value);

/* Private functions ---------------------------------------------------------*/


#endif /* INC_APPLICATION_APP_PARAMS_H_ */
