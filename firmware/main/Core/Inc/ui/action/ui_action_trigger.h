/**
 * @file    ui_action_trigger.h
 * @author  sebas
 * @date    06.01.2023
 * @brief
 */
#ifndef INC_UI_ACTION_UI_ACTION_TRIGGER_H_
#define INC_UI_ACTION_UI_ACTION_TRIGGER_H_

/* Includes ------------------------------------------------------------------*/

#include "util/api.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

API_StatusTypeDef UIACT_TriggerSource();
API_StatusTypeDef UIACT_TriggerDelay();
API_StatusTypeDef UIACT_TriggerHoldoff();
API_StatusTypeDef UIACT_TriggerSlope();
API_StatusTypeDef UIACT_TriggerTimer();

API_StatusTypeDef UIACT_TriggerRunStop();
API_StatusTypeDef UIACT_TriggerSingleShotForce();
API_StatusTypeDef UIACT_TriggerManual();


/* Private functions ---------------------------------------------------------*/


#endif /* INC_UI_ACTION_UI_ACTION_TRIGGER_H_ */
