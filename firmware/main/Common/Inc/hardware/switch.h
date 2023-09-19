/**
 * @file    switch.h
 * @author  Sebastian Harnisch
 * @date    22.05.2021
 * @brief	State machine for evaluating a switch input
 */

#ifndef SWITCH_H_
#define SWITCH_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/************************************************************************/
/* Module defines                                                       */
/************************************************************************/

#undef SW_AUTO_RESET
#define SW_EVENT_LIST_LENGTH	4	/**< Maximum number of event handlers that can be registered. */

/************************************************************************/
/* Type defs                                                            */
/************************************************************************/

/** Operating modes of a switch. */
typedef enum
{
	SW_MODE_NORMAL,					/**< Long presses don't trigger a new event */
	SW_MODE_REPETITION				/**< Long presses trigger new events, see @ref SWITCH_REPETITION_PERIOD. */
} SW_Modes;


/** Results of the state machine describing the determined switch state. */
typedef enum
{
	SW_RESULT_WAITFOR_PRESS,		/**< No press detected. */
	SW_RESULT_PRESSED_SHORT,		/**< Short press detected. */
	SW_RESULT_PRESSED_MEDIUM,		/**< Medium press detected. */
	SW_RESULT_PRESSED_LONG,			/**< Long press detected. */
	SW_RESULT_PRESSED_REPETITIVE	/**< Repetitive press detected. */
} SW_Results;

/** @internal Internal states of the state machine. */
typedef enum
{
	SW_STATE_OPEN,					/**< Switch is in state open. */
	SW_STATE_BLOCKED,				/**< Switch is in state blocked (after event handler was unregistered). */
	SW_STATE_PRESSED				/**< Switch is in state pressed. */
} SW_States;

typedef struct SW_t SW_TypeDef;

/** Internal and external properties and states of a switch. */
typedef struct SW_t
{
	uint8_t tag;
	SW_Modes mode;

	uint16_t min_short;
	uint16_t min_medium;
	uint16_t min_long;

	uint16_t rep_period;					//! Time between two repetitive events in repetition mode

	volatile SW_States _state;
	volatile SW_Results pressed;
	volatile SW_Results released;
	volatile uint16_t _counter;				//! Time with pushbutton pressed (in samples)
	volatile uint16_t _repetition_counter;
	volatile uint16_t _block_counter;

	bool (*gate)(SW_TypeDef*, SW_Results);	//! May be used to inhibit certain events

	// events
	volatile uint8_t _onPressedPointer;
	void (*_onPressed[SW_EVENT_LIST_LENGTH])(SW_TypeDef*);

} SW_TypeDef;

/************************************************************************/
/* Forward declarations                                                 */
/************************************************************************/

/** Initializes the configuration of a switch with user provided data.
 *
 * 	@param[in] sw		   Pointer to the switch.
 * 	@param[in] tag		   Identifier for the switch.
 * 	@param[in] mode		   Selects the operating mode of the switch, a value of @ref SWITCH_Modes.
 * 	@param[in] min_short   Minimum number of ticks that are evaluated as a short press.
 * 	@param[in] min_medium  Minimum number of ticks that are evaluated as a press of medium length.
 * 	@param[in] min_long    Minimum number of ticks that are evaluated as a long press.
 * 	@param[in] rep_period  Number of ticks between two consecutive repetition events.
 * 	@param[in] gate 	   Gate to inhibit events.
 */
void SW_Setup(SW_TypeDef *sw, uint8_t tag, SW_Modes mode, uint16_t min_short,
		uint16_t min_medium, uint16_t min_long, uint16_t rep_period,
		bool (*gate)(SW_TypeDef*, SW_Results));

/** Initializes the internal variables.
 *
 *  @param[in] sw  Pointer to the switch
 */
void SW_Init(SW_TypeDef *sw);


/** Registers an on-pressed event handler that will be called as soon as a press is detected.
 *  Only the event handler registered last will be called.
 *
 *  @param[in] sw  		   Pointer to the switch
 *  @param[in] on_pressed  Pointer to the function that shall be executed
 */
void SW_RegisterOnPressed(SW_TypeDef *sw, void (*on_pressed)(SW_TypeDef*));


/** Unregisters an on-pressed event handler.
 *
 *  @param[in] sw  Pointer to the switch
 */
void SW_UnregisterOnPressed(SW_TypeDef *sw);


/** Runs the internal state machine in order to determine the switch state. This function also calls
 *  the on_pressed event handler if registered. Has to be called periodically. The number of ticks
 *  that lead to a press event are based on this 'sampling time'.
 *
 *  @param[in] sw    Pointer to the switch.
 *  @param[in] open  Raw input state of the switch (contact bounce allowed). true if open, false else.
 */
void SW_Process(SW_TypeDef *sw, bool open);

#endif /* SWITCH_H_ */
