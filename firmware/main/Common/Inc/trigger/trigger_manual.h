/**
 * @file    trigger_manual.h
 * @author  sebas
 * @date    14.01.2023
 * @brief
 */
#ifndef INC_TRIGGER_TRIGGER_MANUAL_H_
#define INC_TRIGGER_TRIGGER_MANUAL_H_

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>
#include "trigger/trigger_logic.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

typedef struct TRIGMAN_Params_t
{
	bool (*_detect_event)(struct TRIGMAN_Params_t *);
} TRIGMAN_ParamsTypeDef;

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void TRIGMAN_ParamsSetup(TRIGMAN_ParamsTypeDef *trig_man, bool (*detect_event)(TRIGMAN_ParamsTypeDef *));
void TRIGMAN_ParamsSetBus(TRIGMAN_ParamsTypeDef *trig_man, bool (*detect_event)(TRIGMAN_ParamsTypeDef *));
void TRIGMAN_Init(TRIG_LogicTypeDef *trig_logic);
bool TRIGMAN_Cycle(TRIG_LogicTypeDef *trig_logic);


/* Private functions ---------------------------------------------------------*/


#endif /* INC_TRIGGER_TRIGGER_MANUAL_H_ */
