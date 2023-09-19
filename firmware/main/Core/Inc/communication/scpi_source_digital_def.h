/**
 * @file    scpi_source_digital_def.h
 * @author  sebas
 * @date    04.12.2022
 * @brief
 */
#ifndef INC_COMMUNICATION_SCPI_SOURCE_DIGITAL_DEF_H_
#define INC_COMMUNICATION_SCPI_SOURCE_DIGITAL_DEF_H_

/* Includes ------------------------------------------------------------------*/

#include "scpi/scpi.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

scpi_result_t SCPI_CMD_SOUR_DIG_PIN1_DATA_Q(scpi_t *context);
scpi_result_t SCPI_CMD_SOUR_DIG_PIN2_DATA_Q(scpi_t *context);

scpi_result_t SCPI_CMD_SOUR_DIG_PIN1_FUNCtion(scpi_t *context);
scpi_result_t SCPI_CMD_SOUR_DIG_PIN1_FUNCtion_Q(scpi_t *context);

scpi_result_t SCPI_CMD_SOUR_DIG_PIN2_FUNCtion(scpi_t *context);
scpi_result_t SCPI_CMD_SOUR_DIG_PIN2_FUNCtion_Q(scpi_t *context);

scpi_result_t SCPI_CMD_SOUR_DIG_PIN1_POLarity(scpi_t *context);
scpi_result_t SCPI_CMD_SOUR_DIG_PIN1_POLarity_Q(scpi_t *context);

scpi_result_t SCPI_CMD_SOUR_DIG_PIN2_POLarity(scpi_t *context);
scpi_result_t SCPI_CMD_SOUR_DIG_PIN2_POLarity_Q(scpi_t *context);

/* Private functions ---------------------------------------------------------*/


#endif /* INC_COMMUNICATION_SCPI_SOURCE_DIGITAL_DEF_H_ */
