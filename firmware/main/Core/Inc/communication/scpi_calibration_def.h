/**
 * @file    scpi_calibration_def.h
 * @author  sebas
 * @date    07.01.2023
 * @brief
 */
#ifndef INC_COMMUNICATION_SCPI_CALIBRATION_DEF_H_
#define INC_COMMUNICATION_SCPI_CALIBRATION_DEF_H_

/* Includes ------------------------------------------------------------------*/

#include "scpi/scpi.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

scpi_result_t SCPI_CMD_CAL_COUNt_Q(scpi_t *context);
scpi_result_t SCPI_CMD_CAL_DATE(scpi_t *context);
scpi_result_t SCPI_CMD_CAL_DATE_Q(scpi_t *context);
scpi_result_t SCPI_CMD_CAL_SEC_STATe(scpi_t *context);
scpi_result_t SCPI_CMD_CAL_SEC_STATe_Q(scpi_t *context);
scpi_result_t SCPI_CMD_CAL_SETup(scpi_t *context);
scpi_result_t SCPI_CMD_CAL_SETup_Q(scpi_t *context);
scpi_result_t SCPI_CMD_CAL_STRing(scpi_t *context);
scpi_result_t SCPI_CMD_CAL_STRing_Q(scpi_t *context);
scpi_result_t SCPI_CMD_CAL_STATe(scpi_t *context);
scpi_result_t SCPI_CMD_CAL_STATe_Q(scpi_t *context);
scpi_result_t SCPI_CMD_CAL_SAVE(scpi_t *context);
scpi_result_t SCPI_CMD_CAL_TEMPerature_Q(scpi_t *context);
scpi_result_t SCPI_CMD_CAL_VALue(scpi_t *context);
scpi_result_t SCPI_CMD_CAL_VALue_Q(scpi_t *context);

/* Private functions ---------------------------------------------------------*/


#endif /* INC_COMMUNICATION_SCPI_CALIBRATION_DEF_H_ */
