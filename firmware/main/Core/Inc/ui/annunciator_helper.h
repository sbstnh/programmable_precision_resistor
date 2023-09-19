/**
 * @file    annunciator_helper.h
 * @author  sebas
 * @date    16.01.2023
 * @brief
 */
#ifndef INC_UI_ANNUNCIATOR_HELPER_H_
#define INC_UI_ANNUNCIATOR_HELPER_H_

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void ANNH_Update();
void ANNH_SwitchEntry(bool on);
void ANNH_OnTriggered();

/* Private functions ---------------------------------------------------------*/


#endif /* INC_UI_ANNUNCIATOR_HELPER_H_ */
