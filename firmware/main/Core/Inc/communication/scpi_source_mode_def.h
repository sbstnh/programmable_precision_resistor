/**
 * @file    scpi_source_mode_def.h
 * @author  sebas
 * @date    04.12.2022
 * @brief
 */
#ifndef INC_COMMUNICATION_SCPI_SOURCE_MODE_DEF_H_
#define INC_COMMUNICATION_SCPI_SOURCE_MODE_DEF_H_

/* Includes ------------------------------------------------------------------*/

#include "scpi/scpi.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

extern scpi_choice_def_t SCPI_SOUR_MODE[];

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

scpi_result_t SCPI_CMD_SOUR_MODE(scpi_t *context);
scpi_result_t SCPI_CMD_SOUR_MODE_Q(scpi_t *context);

/* Private functions ---------------------------------------------------------*/


#endif /* INC_COMMUNICATION_SCPI_SOURCE_MODE_DEF_H_ */
