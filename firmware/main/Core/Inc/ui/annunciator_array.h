/**
 * @file    annunciator_array.h
 * @author  sebas
 * @date    Jan 15, 2023
 * @brief
 */
#ifndef INC_UI_ANNUNCIATOR_ARRAY_H_
#define INC_UI_ANNUNCIATOR_ARRAY_H_

/* Includes ------------------------------------------------------------------*/

#include "hardware/annunciator.h"
#include "ui/annunciator_array.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

typedef struct
{
	ANN_TypeDef *_annunciators;
	uint8_t _count;
} ANNA_TypeDef;

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void ANNA_SetupAndInitAll(ANNA_TypeDef *anna);
void ANNA_SwitchAll(ANNA_TypeDef *anna, bool state);
uint16_t ANNA_Get_State(ANNA_TypeDef *anna);
uint16_t ANNA_Get_Blink(ANNA_TypeDef *anna);

/* Private functions ---------------------------------------------------------*/


#endif /* INC_UI_ANNUNCIATOR_ARRAY_H_ */
