/**
 * @file    led_def.h
 * @author  sebas
 * @date    Jan 15, 2023
 * @brief
 */
#ifndef INC_HARDWARE_ANNUNCIATOR_DEF_H_
#define INC_HARDWARE_ANNUNCIATOR_DEF_H_

/* Includes ------------------------------------------------------------------*/

#include <hardware/annunciator.h>

/* Exported constants --------------------------------------------------------*/

#define NUMBER_OF_ANNUNCIATORS		5

/* Exported types ------------------------------------------------------------*/

typedef enum
{
	ANN_REMOTE = 0,
	ANN_ENTRY = 1,
	ANN_INPUT = 2,
	ANN_UP = 3 ,
	ANN_DOWN = 4
} ANN_NameTypeDef;

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

extern ANN_TypeDef ANNS[NUMBER_OF_ANNUNCIATORS];

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void ANNA_SetupAndInitAll();

/* Private functions ---------------------------------------------------------*/


#endif /* INC_HARDWARE_ANNUNCIATOR_DEF_H_ */
