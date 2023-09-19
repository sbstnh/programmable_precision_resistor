/**
 * @file    scpi_common_def.h
 * @author  sebas
 * @date    14.11.2022
 * @brief
 */
#ifndef INC_COMMUNICATION_SCPI_COMMON_DEF_H_
#define INC_COMMUNICATION_SCPI_COMMON_DEF_H_

/* Includes ------------------------------------------------------------------*/

#include "scpi/scpi.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

scpi_result_t SCPI_CMD_COMM_RCL(scpi_t *context);
scpi_result_t SCPI_CMD_COMM_SAV(scpi_t *context);

scpi_result_t SCPI_CMD_CoreTstQ(scpi_t *context);

/* Private functions ---------------------------------------------------------*/


#endif /* INC_COMMUNICATION_SCPI_COMMON_DEF_H_ */
