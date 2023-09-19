/**
 * @file    scpi_input_def.h
 * @author  sebas
 * @date    04.12.2022
 * @brief
 */
#ifndef INC_COMMUNICATION_SCPI_INPUT_DEF_H_
#define INC_COMMUNICATION_SCPI_INPUT_DEF_H_

/* Includes ------------------------------------------------------------------*/

#include "scpi/scpi.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

scpi_result_t SCPI_CMD_INP_STATe(scpi_t *context);
scpi_result_t SCPI_CMD_INP_STATe_Q(scpi_t *context);

scpi_result_t SCPI_CMD_INP_INH_MODE(scpi_t *context);
scpi_result_t SCPI_CMD_INP_INH_MODE_Q(scpi_t *context);

scpi_result_t SCPI_CMD_INP_INH_STATe_Q(scpi_t *context);
scpi_result_t SCPI_CMD_INP_INH_CLEar(scpi_t *context);

/* Private functions ---------------------------------------------------------*/


#endif /* INC_COMMUNICATION_SCPI_INPUT_DEF_H_ */
