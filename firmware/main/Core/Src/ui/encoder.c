/**
 * @file    rot_encoder.c
 * @author  sebas
 * @date    24.12.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "ui/encoder.h"

#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "queue.h"

#include "util/util.h"
#include "util/util_rtos.h"

/* Private defines -----------------------------------------------------------*/

#define ENC_TIMEOUT			5

/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/

extern osMessageQueueId_t encoderQueueHandle;

/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void ENC_Init(ENC_TypeDef *encoder)
{
	encoder->valid = false;
}


void ENC_Process(ENC_TypeDef *encoder, int32_t received_count)
{
	if (!encoder->valid)
	{
		encoder->last = received_count;
		encoder->valid = true;

		return;
	}

	int16_t rot_count = received_count - encoder->last;
	encoder->last = received_count;

	if (rot_count && (encoder->gate == NULL || encoder->gate(encoder)))
	{
		osMessageQueuePut(encoderQueueHandle, &rot_count, 0, ENC_TIMEOUT);
	}
}


bool ENC_Peek_Count(int16_t *count)
{
	return osMessageQueuePeek(encoderQueueHandle, count, NULL, 0) == osOK;
}


bool ENC_Get_Count(int16_t *count)
{
	return osMessageQueueGet(encoderQueueHandle, count, NULL, 0) == osOK;
}


void ENC_SkipAll_Counts()
{
	osMessageQueueReset(encoderQueueHandle);
}

/* Private functions ---------------------------------------------------------*/

