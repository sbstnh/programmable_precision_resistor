/**
 * @file    relay_control.h
 * @author  Sebastian Harnisch
 * @date    15.10.2021
 * @brief	Interface between relay-business logic and STP16 hardware abstraction.
 */


#ifndef INC_RELAY_CONTROL_H_
#define INC_RELAY_CONTROL_H_

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>
#include "prog_res/relay.h"
#include "hardware/stp16cp05.h"
#include "util/api.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void RLYCTRL_Init(RLY_TypeDef *relay);
bool RLYCTRL_GetState(RLY_TypeDef *relay, STP_TypeDef *stp);
void RLYCTRL_SetState(RLY_TypeDef *relay, STP_TypeDef *stp);
API_StatusTypeDef RLYCTRL_Update(STP_TypeDef *stp);

/* Private functions ---------------------------------------------------------*/


#endif /* INC_RELAY_CONTROL_H_ */
