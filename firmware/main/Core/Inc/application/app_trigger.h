/**
 * @file    app_trigger.h
 * @author  sebas
 * @date    10.12.2022
 * @brief
 */
#ifndef INC_APPLICATION_APP_TRIGGER_H_
#define INC_APPLICATION_APP_TRIGGER_H_

/* Includes ------------------------------------------------------------------*/

#include "util/api.h"
#include "application/app_params.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void APP_Run_TriggerAbortImmediate();
API_StatusTypeDef APP_Run_TriggerInitiateImmediate();

bool APP_Get_TriggerInitiated();

bool APP_Get_TriggerInitiateContinuous();
API_StatusTypeDef APP_Set_TriggerInitiateContinuous(bool continuous);

API_StatusTypeDef APP_Run_TriggerImmediate();

void APP_Run_TriggerBusTrg();
bool APP_Get_TriggerBusTrg();
void APP_Set_TriggerBusTrg(bool trg);

void APP_Run_TriggerManualTrigger();
bool APP_Get_TriggerManualTrigger();
void APP_Set_TriggerManualTrigger(bool trg);

void APP_Run_TriggerSequenceImmediate();

INT_VALUE_TypeDef APP_Get_TriggerSequenceDelay();
API_StatusTypeDef APP_Set_TriggerSequenceDelay(int32_t delay);

INT_VALUE_TypeDef APP_Get_TriggerSequenceHoldOff();
API_StatusTypeDef APP_Set_TriggerSequenceHoldOff(int32_t holdoff);

SEQ_SOURce_TypeDef APP_Get_TriggerSequenceSource();
API_StatusTypeDef APP_Set_TriggerSequenceSource(SEQ_SOURce_TypeDef source);

SEQ_SLOPe_TypeDef APP_Get_TriggerSequenceSlope();
API_StatusTypeDef APP_Set_TriggerSequenceSlope(SEQ_SLOPe_TypeDef slope);

INT_VALUE_TypeDef APP_Get_TriggerSequenceTimer();
API_StatusTypeDef APP_Set_TriggerSequenceTimer(int32_t timer);

/* Private functions ---------------------------------------------------------*/


#endif /* INC_APPLICATION_APP_TRIGGER_H_ */
