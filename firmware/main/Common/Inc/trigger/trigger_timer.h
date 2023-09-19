/**
 * @file    trigger_bus.h
 * @author  sebas
 * @date    14.01.2023
 * @brief
 */
#ifndef INC_TRIGGER_TRIGGER_TIMER_H_
#define INC_TRIGGER_TRIGGER_TIMER_H_

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdint.h>
#include "trigger/trigger_logic.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

typedef struct TRIGTIM_Params_t
{
	bool (*_detect_event)(struct TRIGTIM_Params_t *);
	uint32_t _ticks;
} TRIGTIM_ParamsTypeDef;

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void TRIGTIM_ParamsSetup(TRIGTIM_ParamsTypeDef *trig_tim, bool (*detect_event)(struct TRIGTIM_Params_t *));
void TRIGTIM_ParamsSetBus(TRIGTIM_ParamsTypeDef *trig_tim, bool (*detect_event)(struct TRIGTIM_Params_t *));
void TRIGTIM_Init(TRIG_LogicTypeDef *trig_logic);
bool TRIGTIM_Cycle(TRIG_LogicTypeDef *trig_logic);


/* Private functions ---------------------------------------------------------*/


#endif /* INC_TRIGGER_TRIGGER_TIMER_H_ */
