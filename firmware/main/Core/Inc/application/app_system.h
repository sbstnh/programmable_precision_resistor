/**
 * @file    app_system.h
 * @author  sebas
 * @date    05.12.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "util/api.h"
#include "application/app_params.h"

/* Private defines -----------------------------------------------------------*/

#define APP_SYS_FIRM_VERS_MAX_LEN		32

/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

bool APP_Get_SystemBeeperState();
API_StatusTypeDef APP_Set_SystemBeeperStateSave(bool state, bool save);
API_StatusTypeDef APP_Set_SystemBeeperState(bool state);

void APP_Run_SystemBeeperBeepShort();
void APP_Run_SystemBeeperBeepLong();
void APP_Run_SystemBeeperBeepError();
void APP_Run_SystemBeeperTick();

COMM_RLSTate_TypeDef APP_Get_SystemCommunicateRLState();
API_StatusTypeDef APP_Run_SystemCommunicateRLState(COMM_RLSTate_TypeDef rlstate);

API_StatusTypeDef APP_Run_SystemDefaultImmediate();

const char *APP_Get_SystemFirmwareVersionMainboard();
const char *APP_Get_SystemFirmwareVersionUI();

API_StatusTypeDef APP_Run_SystemSecurityImmediate();

float APP_Get_SystemTempImmediate(TEMP_SELection_TypeDef temp_sel);
float APP_Get_SystemTempAverage(TEMP_SELection_TypeDef temp_sel);
float APP_Get_SystemTempMinimum(TEMP_SELection_TypeDef temp_sel);
float APP_Get_SystemTempInternalMaximum(TEMP_SELection_TypeDef temp_sel);
API_StatusTypeDef APP_Run_SystemTempReset(TEMP_SELection_TypeDef temp_sel);

/* Private functions ---------------------------------------------------------*/

