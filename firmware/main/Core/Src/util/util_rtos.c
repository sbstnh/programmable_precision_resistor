/**
 * @file    util_rtos.c
 * @author  sebas
 * @date    22.12.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include "util/util_rtos.h"
#include "FreeRTOS.h"
#include "queue.h"

#include "cmsis_compiler.h"

/* Private defines -----------------------------------------------------------*/

#ifndef IS_IRQ
#define IS_IRQ()             (__get_IPSR() != 0U)
#endif

/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

osStatus_t osMessageQueuePeek(osMessageQueueId_t mq_id, void *msg_ptr, uint8_t *msg_prio, uint32_t timeout)
{
	QueueHandle_t hQueue = (QueueHandle_t)mq_id;
	osStatus_t stat;
	BaseType_t yield;

	(void)msg_prio;

	stat = osOK;

	if (IS_IRQ())
	{
		if ((hQueue == NULL) || (msg_ptr == NULL) || (timeout != 0U))
		{
			stat = osErrorParameter;
		}
		else
		{
			yield = pdFALSE;

			if (xQueuePeekFromISR(hQueue, msg_ptr) != pdPASS)
			{
				stat = osErrorResource;
			}
			else
			{
				portYIELD_FROM_ISR (yield);
			}
		}
	}
	else
	{
		if ((hQueue == NULL) || (msg_ptr == NULL))
		{
			stat = osErrorParameter;
		}
		else
		{
			if (xQueuePeek(hQueue, msg_ptr, (TickType_t)timeout) != pdPASS)
			{
				if (timeout != 0U)
				{
					stat = osErrorTimeout;
				}
				else
				{
					stat = osErrorResource;
				}
			}
		}
	}

	return (stat);
}

/* Private functions ---------------------------------------------------------*/
