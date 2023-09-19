/**
 * @file    switch_def.h
 * @author  sebas
 * @date    28.12.2022
 * @brief
 */
#ifndef INC_HARDWARE_SWITCH_DEF_H_
#define INC_HARDWARE_SWITCH_DEF_H_

/* Includes ------------------------------------------------------------------*/

#include "hardware/switch.h"

/* Exported constants --------------------------------------------------------*/

#define SW_NUMBER_OF_SWITCHES		24	/**< Number of switches available. */

#define SW_MIN_SHORT				5	/**< Minimum number of ticks that are evaluated as a short press. */
#define SW_MIN_MEDIUM				50	/**< Minimum number of ticks that are evaluated as a press of medium length. */
#define SW_MIN_LONG					100 /**< Minimum number of ticks that are evaluated as a long press. */
#define SW_REP_PERIOD 				15	/**< Number of ticks between two consecutive repetition events. */

#define SW_SHIFT_KEY_CODE_MODIFIER	(1 << 7)	/**< Offset to be added when shift is active. */

/* Exported types ------------------------------------------------------------*/


typedef enum
{
	SW_CH = 0,
	SW_MODE = 6,
	SW_MENU = 12,
	SW_SHIFT = 18,

	SW_0 = 19,
	SW_1 = 13,
	SW_2 = 14,
	SW_3 = 15,
	SW_4 = 7,
	SW_5 = 8,
	SW_6 = 9,
	SW_7 = 1,
	SW_8 = 2,
	SW_9 = 3,
	SW_DP = 20,
	SW_BACKSP = 21,

	SW_ROT_ENT = 5,
	SW_ENTER = 16, // 10
	SW_BACK_DISP = 22, // 4
	SW_LEFT = 4, // 22
	SW_RIGHT = 10, // 16

	SW_INP = 11,
	SW_UP = 17,
	SW_DOWN = 23,

	SW_SH_RCL		= (SW_SHIFT_KEY_CODE_MODIFIER | SW_CH),
	SW_SH_MODE		= (SW_SHIFT_KEY_CODE_MODIFIER | SW_MODE),
	SW_SH_MENU		= (SW_SHIFT_KEY_CODE_MODIFIER | SW_MENU),
	SW_SH_SHIFT		= (SW_SHIFT_KEY_CODE_MODIFIER | SW_SHIFT),

	SW_SH_DIGIT		= (SW_SHIFT_KEY_CODE_MODIFIER | SW_0),
	SW_SH_PAR		= (SW_SHIFT_KEY_CODE_MODIFIER | SW_1),
	SW_SH_LIM		= (SW_SHIFT_KEY_CODE_MODIFIER | SW_2),
	SW_SH_SWIT		= (SW_SHIFT_KEY_CODE_MODIFIER | SW_3),
	SW_SH_EXT		= (SW_SHIFT_KEY_CODE_MODIFIER | SW_4),
	SW_SH_INH		= (SW_SHIFT_KEY_CODE_MODIFIER | SW_5),
	SW_SH_TRIG		= (SW_SHIFT_KEY_CODE_MODIFIER | SW_6),
	SW_SH_ERR		= (SW_SHIFT_KEY_CODE_MODIFIER | SW_7),
	SW_SH_CALM		= (SW_SHIFT_KEY_CODE_MODIFIER | SW_8),
	SW_SH_SW9		= (SW_SHIFT_KEY_CODE_MODIFIER | SW_9),
	SW_SH_MINUS		= (SW_SHIFT_KEY_CODE_MODIFIER | SW_DP),
	SW_SH_BACKSP	= (SW_SHIFT_KEY_CODE_MODIFIER | SW_BACKSP),

	SW_SH_ENTER		= (SW_SHIFT_KEY_CODE_MODIFIER | SW_ENTER),
	SW_SH_ROT_ENT 	= (SW_SHIFT_KEY_CODE_MODIFIER | SW_ROT_ENT),
	SW_SH_BACK_DISP	= (SW_SHIFT_KEY_CODE_MODIFIER | SW_BACK_DISP),
	SW_SH_LEFT		= (SW_SHIFT_KEY_CODE_MODIFIER | SW_LEFT),
	SW_SH_RIGHT		= (SW_SHIFT_KEY_CODE_MODIFIER | SW_RIGHT),

	SW_SH_INP_SETUP	= (SW_SHIFT_KEY_CODE_MODIFIER | SW_INP),
	SW_SH_UP		= (SW_SHIFT_KEY_CODE_MODIFIER | SW_UP),
	SW_SH_DOWN		= (SW_SHIFT_KEY_CODE_MODIFIER | SW_DOWN),

	SW_NONE
} SWA_KeyCodeTypeDef;

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

extern SW_TypeDef SW[SW_NUMBER_OF_SWITCHES];

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void SW_SetupAndInitAll();

/* Private functions ---------------------------------------------------------*/


#endif /* INC_HARDWARE_SWITCH_DEF_H_ */
