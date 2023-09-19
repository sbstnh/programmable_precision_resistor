/**
 * @file    trigger_def.h
 * @author  sebas
 * @date    03.12.2022
 * @brief
 */
#ifndef INC_TRIGGER_TRIGGER_DEF_H_
#define INC_TRIGGER_TRIGGER_DEF_H_

/* Includes ------------------------------------------------------------------*/

#include "trigger/trigger.h"
#include "trigger/trigger_bus.h"
#include "trigger/trigger_edge.h"
#include "trigger/trigger_immediate.h"
#include "trigger/trigger_manual.h"
#include "trigger/trigger_timer.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

extern TRIGEDGE_ParamsTypeDef TRIG_INHIBIT_PARAMS;
extern TRIG_LogicTypeDef TRIG_LOGIC_INHIBIT;
extern TRIG_TypeDef TRIG_INHIBIT;

extern TRIGEDGE_ParamsTypeDef TRIGEDGE_PARAMS;
extern TRIGBUS_ParamsTypeDef TRIGBUS_PARAMS;
extern TRIGMAN_ParamsTypeDef TRIGMAN_PARAMS;
extern TRIGTIM_ParamsTypeDef TRIGTIM_PARAMS;
extern TRIG_LogicTypeDef TRIG_LOGIC_EDGE;
extern TRIG_LogicTypeDef TRIG_LOGIC_BUS;
extern TRIG_LogicTypeDef TRIG_LOGIC_IMMEDIATE;
extern TRIG_LogicTypeDef TRIG_LOGIC_MANUAL;
extern TRIG_LogicTypeDef TRIG_LOGIC_TIMER;
extern TRIG_TypeDef TRIG;

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

bool TRIGEDGE_Inhibit_DetectEvent(TRIGEDGE_ParamsTypeDef *params);

bool TRIGEDGE_DetectEvent(TRIGEDGE_ParamsTypeDef *params);
bool TRIGBUS_DetectEvent(TRIGBUS_ParamsTypeDef *params);
bool TRIGMAN_DetectEvent(TRIGMAN_ParamsTypeDef *params);
bool TRIGTIM_DetectEvent(TRIGTIM_ParamsTypeDef *params);

/* Private functions ---------------------------------------------------------*/


#endif /* INC_TRIGGER_TRIGGER_DEF_H_ */
