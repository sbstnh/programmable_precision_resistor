/**
 * @file    trigger_bus.h
 * @author  sebas
 * @date    14.01.2023
 * @brief
 */
#ifndef INC_TRIGGER_TRIGGER_BUS_H_
#define INC_TRIGGER_TRIGGER_BUS_H_

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>
#include "trigger/trigger_logic.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

typedef struct TRIGBUS_Params_t
{
	bool (*_detect_event)(struct TRIGBUS_Params_t *);
} TRIGBUS_ParamsTypeDef;

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void TRIGBUS_ParamsSetup(TRIGBUS_ParamsTypeDef *trig_bus, bool (*detect_event)(TRIGBUS_ParamsTypeDef *));
void TRIGBUS_ParamsSetBus(TRIGBUS_ParamsTypeDef *trig_bus, bool (*detect_event)(TRIGBUS_ParamsTypeDef *));
void TRIGBUS_Init(TRIG_LogicTypeDef *trig_logic);
bool TRIGBUS_Cycle(TRIG_LogicTypeDef *trig_logic);


/* Private functions ---------------------------------------------------------*/


#endif /* INC_TRIGGER_TRIGGER_BUS_H_ */
