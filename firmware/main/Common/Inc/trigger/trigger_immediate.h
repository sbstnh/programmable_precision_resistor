/**
 * @file    trigger_immediate.h
 * @author  sebas
 * @date    14.01.2023
 * @brief
 */
#ifndef INC_TRIGGER_TRIGGER_IMMEDIATE_H_
#define INC_TRIGGER_TRIGGER_IMMEDIATE_H_

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>
#include "trigger/trigger_logic.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void TRIGIMM_Init(TRIG_LogicTypeDef *trig_logic);
bool TRIGIMM_Cycle(TRIG_LogicTypeDef *trig_logic);


/* Private functions ---------------------------------------------------------*/


#endif /* INC_TRIGGER_TRIGGER_IMMEDIATE_H_ */
