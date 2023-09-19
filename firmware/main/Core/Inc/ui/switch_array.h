/*
 * switch_def.h
 *
 *  Created on: 11.11.2022
 *      Author: sebas
 */

#ifndef INC_HARDWARE_SWITCH_ARRAY_H_
#define INC_HARDWARE_SWITCH_ARRAY_H_


/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>
#include "hardware/switch.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

typedef struct swarr
{
	SW_TypeDef *switches;
	uint8_t switch_count;

	volatile bool _shift;
	volatile uint8_t _last_active;
	volatile uint8_t _on_pressed_pointer;
	bool (*gate)(struct swarr *, SW_TypeDef*);
} SWA_TypeDef;

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** Sets up and initializes the swdef object containing the switch array.
 *
 *	@param[in] swdef  Pointer to the @ref SWARR_TypeDef instance.
 */
void SWA_Init(SWA_TypeDef *swdef);


/** Returns the current shift state.
 *
 *	@param[in] swdef  Pointer to the @ref SWARR_TypeDef instance.
 *	@return			  The current shift state.
 */
bool SWA_Get_Shift(SWA_TypeDef *swdef);


/** Resets the shift flag to false.
 *
 *	@param[in] swdef  Pointer to the @ref SWARR_TypeDef instance.
 */
void SWA_Reset_Shift(SWA_TypeDef *swdef);


/** Unregister the callback that has been registered last.
 *
 * 	@param[in] swdef  Pointer to the @ref SWARR_TypeDef instance.
 * 	@param[in] open   Bits representing the state of the switches
 */
void SWA_Process(SWA_TypeDef *swdef, uint32_t open);


/** Return a switch that has been pressed or released, but don't discard event.
 *
 * 	@return           Pointer to the switch that was pressed or released or NULL.
 */
uint8_t SWA_Peek_KeyCode();


/** Return a switch that has been pressed or released and discard event.
 *
 * 	@return           Pointer to the switch that was pressed or released or NULL.
 */
uint8_t SWA_Get_KeyCode();


/** Mark all switches events as handled without further processing. */
void SWA_SkipAll_KeyCodes();

/* Private functions ---------------------------------------------------------*/

#endif /* INC_HARDWARE_SWITCH_ARRAY_H_ */
