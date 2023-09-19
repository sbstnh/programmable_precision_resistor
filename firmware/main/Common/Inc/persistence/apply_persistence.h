/**
 * @file    apply_persistence.h
 * @author  sebas
 * @date    23.04.2023
 * @brief
 */
#ifndef INC_PERSISTENCE_APPLY_PERSISTENCE_H_
#define INC_PERSISTENCE_APPLY_PERSISTENCE_H_

/* Includes ------------------------------------------------------------------*/

#include "persistence/persistence.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void PER_ApplyInstData(PER_TypeDef *per, volatile APP_ParamTypeDef *app);
void PER_ApplyUserData(PER_TypeDef *per, volatile APP_ParamTypeDef *app);

/* Private functions ---------------------------------------------------------*/


#endif /* INC_PERSISTENCE_APPLY_PERSISTENCE_H_ */
