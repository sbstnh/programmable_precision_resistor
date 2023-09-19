/**
 * @file    util_rtos.h
 * @author  sebas
 * @date    22.12.2022
 * @brief
 */
#ifndef INC_UTIL_UTIL_RTOS_H_
#define INC_UTIL_UTIL_RTOS_H_

/* Includes ------------------------------------------------------------------*/

#include "cmsis_os2.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

osStatus_t osMessageQueuePeek (osMessageQueueId_t mq_id, void *msg_ptr, uint8_t *msg_prio, uint32_t timeout);

/* Private functions ---------------------------------------------------------*/


#endif /* INC_UTIL_UTIL_RTOS_H_ */
