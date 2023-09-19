/**
 * @file    ui_action_system.h
 * @author  sebas
 * @date    01.01.2023
 * @brief
 */
#ifndef INC_UI_ACTION_UI_ACTION_SYSTEM_H_
#define INC_UI_ACTION_UI_ACTION_SYSTEM_H_

/* Includes ------------------------------------------------------------------*/

#include "util/api.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

API_StatusTypeDef UIACT_SystemBeeper();

API_StatusTypeDef UIACT_SystemDefaultImmediate();

API_StatusTypeDef UIACT_SystemDigitalInputPolarity1();
API_StatusTypeDef UIACT_SystemDigitalInputFunction1();

API_StatusTypeDef UIACT_SystemDigitalInputPolarity2();
API_StatusTypeDef UIACT_SystemDigitalInputFunction2();

API_StatusTypeDef UIACT_SystemErrorCount();
API_StatusTypeDef UIACT_SystemErrorNext();

API_StatusTypeDef UIACT_SystemFirmwareVersionMainboard();
API_StatusTypeDef UIACT_SystemFirmwareVersionUI();

API_StatusTypeDef UIACT_SystemSecurityImmediate();

API_StatusTypeDef UIACT_SystemTemperature();
API_StatusTypeDef UIACT_SystemTemperatureReset();

/* Private functions ---------------------------------------------------------*/


#endif /* INC_UI_ACTION_UI_ACTION_SYSTEM_H_ */
