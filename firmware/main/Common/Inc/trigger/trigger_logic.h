/**
 * @file    trigger_logic.h
 * @author  sebas
 * @date    Nov 20, 2022
 * @brief
 */
#ifndef INC_TRIGGER_TRIGGER_LOGIC_H_
#define INC_TRIGGER_TRIGGER_LOGIC_H_

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

typedef struct TRIG_LogicTypeDef TRIG_LogicTypeDef;

struct TRIG_LogicTypeDef
{
	void (*trig_init)(TRIG_LogicTypeDef *);
	bool (*trig_cycle)(TRIG_LogicTypeDef *);

	void *params;
};

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


#endif /* INC_TRIGGER_TRIGGER_LOGIC_H_ */
