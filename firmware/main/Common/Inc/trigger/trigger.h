/**
 * @file    trigger.h
 * @author  sebas
 * @date    Nov 20, 2022
 * @brief
 */
#ifndef INC_TRIGGER_TRIGGER_H_
#define INC_TRIGGER_TRIGGER_H_

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>
#include "trigger/trigger_logic.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

typedef enum
{
	TRIG_STATE_IDLE,
	TRIG_STATE_INITIATED,
	TRIG_STATE_ARMED,
	TRIG_STATE_DELAYED,
	TRIG_STATE_HELDOFF
} TRIG_StatesTypeDef;

typedef struct
{
	bool _continuous;
	uint32_t _delay;
	uint32_t _holdoff;

	void (*on_armed)(void);
	void (*on_delayed)(void);
	void (*on_triggered)(void);
	void (*on_heldoff)(void);

	TRIG_LogicTypeDef *_trig_logic;
	uint32_t _delay_timer;
	uint32_t _holdoff_timer;
	TRIG_StatesTypeDef _state;
	bool _immediate;
} TRIG_TypeDef;

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void TRIG_Init(TRIG_TypeDef *trig, TRIG_LogicTypeDef *trig_logic);
void TRIG_SetLogic(TRIG_TypeDef *trig, TRIG_LogicTypeDef *trig_logic);
void TRIG_SetDelay(TRIG_TypeDef *trig, uint32_t delay);
void TRIG_SetHoldOff(TRIG_TypeDef *trig, uint32_t holdoff);
TRIG_StatesTypeDef TRIG_GetState(TRIG_TypeDef *trig);
void TRIG_Initiate(TRIG_TypeDef *trig);
void TRIG_Abort(TRIG_TypeDef *trig);
void TRIG_Continuous(TRIG_TypeDef *trig, bool continuous);
void TRIG_Immediate(TRIG_TypeDef *trig);
bool TRIG_Cycle(TRIG_TypeDef *trig);

/* Private functions ---------------------------------------------------------*/


#endif /* INC_TRIGGER_TRIGGER_H_ */
