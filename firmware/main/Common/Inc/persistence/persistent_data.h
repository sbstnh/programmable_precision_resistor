/*
 * persistent_data.h
 *
 *  Created on: 21.10.2022
 *      Author: sebas
 */

#ifndef INC_APPLICATION_PERSISTENT_DATA_H_
#define INC_APPLICATION_PERSISTENT_DATA_H_

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdint.h>
#include "calibration/cal_data.h"

#include "application/app_params.h"

/* Exported constants --------------------------------------------------------*/

#define INSTDATA_BLOCK_SIZE			32
#define INSTDATA_BLOCK_SIZE_WO_CRC	(INSTDATA_BLOCK_SIZE - 4)
#define INSTDATA_MAX_BLOCK_SIZE		64

#define USERDATA_BLOCK_SIZE			96
#define USERDATA_BLOCK_SIZE_WO_CRC	(USERDATA_BLOCK_SIZE - 4)
#define USERDATA_MAX_BLOCK_SIZE		96

#define SIZE_WO_CRC(block_size)		((block_size) - 4)

/* Exported types ------------------------------------------------------------*/

typedef union
{
	struct __attribute__((packed))
	{
		INH_MODE_TypeDef INP_INH_MODE;										// 0
		PON_STATe_TypeDef INP_PON_STATe;									// 1

		PIN_FUNCtion_TypeDef SOUR_DIG_PIN_FUNCtion[SOUR_DIG_PIN_COUNT];		// 2
		PIN_POLarity_TypeDef SOUR_DIG_PIN_POLarity[SOUR_DIG_PIN_COUNT];		// 4

		bool SYST_BEEP_STATe;												// 6

		uint8_t RESERVED[21];												// 7

		uint32_t CRC_CHECKSUM;												// 28
	};
	uint8_t AS_BYTE[INSTDATA_BLOCK_SIZE];
} INSTDATA_TypeDef;


typedef union
{
	struct __attribute__((packed))
	{
		PRIM_RESolution_TypeDef DISP_PRIM_RESolution;		// 0
		SEC_MODE_TypeDef DISP_SEC_MODE;						// 1

		bool INP_STATe;										// 2

		SOUR_MODE_TypeDef SOUR_MODE;						// 3

		int32_t SOUR_RES_LEV_IMM_AMPlitude;					// 4
		int32_t SOUR_RES_LEV_TRIG_AMPlitude;				// 8

		int32_t SOUR_RES_LEV_STEP_INCRement;				// 12
		STEP_MODE_TypeDef SOUR_RES_LEV_STEP_MODE;			// 16
		STEP_OVERflow_TypeDef SOUR_RES_LEV_STEP_OVERflow;	// 17

		uint8_t RESERVED0[2];								// 18

		int32_t SOUR_RES_LIM_LOWer;							// 20
		bool SOUR_RES_LIM_STATe;							// 24
		uint8_t RESERVED1[3];								// 25

		int32_t SOUR_RES_LIM_UPPer;							// 28

		RES_MODE_TypeDef SOUR_RES_MODE;						// 32

		SOUR_SWITching_TypeDef SOUR_SWITching;				// 33

		uint8_t RESERVED2;									// 35

		int32_t TRIG_SEQ_DELay;								// 36
		int32_t TRIG_SEQ_HOLDoff;							// 40
		SEQ_SOURce_TypeDef TRIG_SEQ_SOURce;					// 44
		SEQ_SLOPe_TypeDef TRIG_SEQ_SLOPe;					// 45
		uint8_t RESERVED3[2];								// 46
		int32_t TRIG_SEQ_TIMer;								// 48

		uint8_t RESERVED4[40];								// 52
		uint32_t CRC_CHECKSUM;								// 92
	};
	uint8_t AS_BYTE[USERDATA_BLOCK_SIZE];
} USERDATA_TypeDef;

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


#endif /* INC_APPLICATION_PERSISTENT_DATA_H_ */
