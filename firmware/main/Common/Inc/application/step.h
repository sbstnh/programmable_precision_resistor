/**
 * @file    step.h
 * @author  sebas
 * @date    03.12.2022
 * @brief
 */
#ifndef INC_APPLICATION_STEP_H_
#define INC_APPLICATION_STEP_H_

/* Includes ------------------------------------------------------------------*/

#include "application/app_params.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

int32_t STEP_CalculateUp(LEV_STEP_TypeDef *step, INT_VALUE_TypeDef value);
int32_t STEP_CalculateDown(LEV_STEP_TypeDef *step, INT_VALUE_TypeDef value);

/* Private functions ---------------------------------------------------------*/

#endif /* INC_APPLICATION_STEP_H_ */
