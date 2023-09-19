/*
 * base.c
 *
 *  Created on: Oct 15, 2022
 *      Author: sebas
 */

/* Includes ------------------------------------------------------------------*/

#include <application/app.h>
#include <stdbool.h>

#include "main.h"
#include "stm32g4xx_hal.h"

#include "cmsis_os2.h"

#include "build_def.h"

#include "hardware/stp16cp05_def.h"
#include "hardware/adc_channels.h"
#include "hardware/kty82_sensor_def.h"
#include "hardware/ui_interface_def.h"
#include "hardware/switch_def.h"

#include "ui/ui.h"
#include "ui/annunciator_array_def.h"
#include "ui/switch_array_def.h"
#include "ui/encoder_def.h"

#include "communication/scpi_def.h"
#include "communication/scpi_circ_buf_def.h"

#include "usbd_cdc_if.h"

#include "trigger/trigger_def.h"

#include "application/app_params.h"
#include "application/app_system.h"

/* Private defines -----------------------------------------------------------*/

#define SCPI_TMP_BUF_LEN	128

/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

volatile uint8_t SYSTICK_10ms = 0;
volatile uint16_t SYSTICK_1000ms = 0;
volatile uint32_t loop = 0;

/* External variables --------------------------------------------------------*/

extern volatile bool SYSTICK_1ms;
extern TIM_HandleTypeDef htim7;

/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

void _BASE_loop_1ms();
void _BASE_loop_10ms();
void _BASE_loop_1000ms();

/* Exported functions --------------------------------------------------------*/

// COMMON TODO_SECTION:

// TODO: Memory management (Stack size & co.)
// TODO: SCPI and other queue sizes
// TODO: Solve all other TODOS

void BASE_Init()
{
	STP_Init(&STP);
	STP_Transmit(&STP);

	HAL_GPIO_WritePin(RLY_PWR_GPIO_Port, RLY_PWR_Pin, GPIO_PIN_SET);

	ADC_CHANNELS_Init();

	// SCPI init
	SCPI_Init(&scpi_context,
			scpi_commands,
			&scpi_interface,
			scpi_units_def,
			SCPI_IDN1, SCPI_IDN2, SCPI_IDN3, SCPI_IDN4,
			scpi_input_buffer, SCPI_INPUT_BUFFER_LENGTH,
			scpi_error_queue_data, SCPI_ERROR_QUEUE_SIZE);

	// Initialization of business logic
	APP_Init();
	HAL_TIM_Base_Start_IT(&htim7);

	// Initialize inputs
	SW_SetupAndInitAll();
	ANNA_SetupAndInitAll(&ANNA);
	SWA_Init(&SWA);
	ENC_Init(&ENC);

	// Primitive delay
	for (loop = 0; loop < 4000000UL; loop++) {}

	// Initialize sensor
	KTY82_Init(&KTY82_TEMP[KTY82_TEMP1]);
	KTY82_Init(&KTY82_TEMP[KTY82_TEMP2]);
}


/** Function implementing the scpiTask thread.
 *
 * @param[in] argument  Not used.
 * @retval 				None
 */
void BASE_StartScpiTask(void *argument)
{
	uint8_t scpi_buf[SCPI_TMP_BUF_LEN];
	uint16_t len = 0;

	while (1)
	{
		// SCPI processing
		if (!CBUF_Empty(&SCPI_CIRC_BUF_RX))
		{
			len = CBUF_Read(&SCPI_CIRC_BUF_RX, scpi_buf, sizeof(scpi_buf));
			SCPI_Input(&scpi_context, (const char *) scpi_buf, len);
		}

		if (!CBUF_Empty(&SCPI_CIRC_BUF_TX) && CDC_TxNotBusy() == USBD_OK)
		{
			len = CBUF_Read(&SCPI_CIRC_BUF_TX, scpi_buf, sizeof(scpi_buf));
			CDC_Transmit_FS((uint8_t *) scpi_buf, len);
		}

		osDelay(10);
	}
}


/** Function implementing the uiTask thread.
 *
 * @param[in] argument  Not used.
 * @retval 				None
 */
void BASE_StartUiTask(void *argument)
{
	// Initialize UI
	UI_Run();
}


/** Timer callback implementing the App cycle call.
 *
 * @retval 				None
 */
void BASE_AppTick()
{
	APP_Cycle();
}


/** Function implementing a software timer thread.
 *
 * @param[in] argument  Not used.
 * @retval 				None
 */
void BASE_TimerTick_10ms(void *argument)
{
	// Keyboard
	uint32_t open;
	if (UIIF_ReadSwitches(&UIIF, &open) == API_OK)
	{
		SWA_Process(&SWA, open);
	}

	// Encoder
	int16_t received_count;
	if (UIIF_ReadEncoder(&UIIF, &received_count) == API_OK)
	{
		ENC_Process(&ENC, received_count);
	}

	// Sensor processing
	KTY82_Process(&KTY82_TEMP[KTY82_TEMP1]);
	KTY82_Process(&KTY82_TEMP[KTY82_TEMP2]);
}


/* Private functions ---------------------------------------------------------*/

