/**
 * @file    app_init.h
 * @author  sebas
 * @date    04.03.2023
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "application/app_params.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void APP_Run_RestoreDefault(volatile APP_ParamTypeDef *app);
void APP_Run_RestoreDefaultAppState(volatile APP_ParamTypeDef *app);
void APP_Run_RestoreDefaultInstrumentSettings(volatile APP_ParamTypeDef *app);
void APP_Run_RestoreDefaultUserSettings(volatile APP_ParamTypeDef *app);

/* Private functions ---------------------------------------------------------*/

