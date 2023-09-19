/**
 * @file    scpi_source_resistance_def.h
 * @author  sebas
 * @date    11.11.2022
 * @brief
 */
#ifndef INC_COMMUNICATION_SCPI_SOURCE_RESISTANCE_DEF_H_
#define INC_COMMUNICATION_SCPI_SOURCE_RESISTANCE_DEF_H_

/* Includes ------------------------------------------------------------------*/

#include "scpi/scpi.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

scpi_result_t SCPI_CMD_SOUR_RES_LEV_IMM_AMPLitude(scpi_t *context);
scpi_result_t SCPI_CMD_SOUR_RES_LEV_IMM_AMPLitude_Q(scpi_t *context);
scpi_result_t SCPI_CMD_SOUR_RES_LEV_IMM_CALCulate_Q(scpi_t *context);

scpi_result_t SCPI_CMD_SOUR_RES_LEV_TRIG_AMPLitude(scpi_t *context);
scpi_result_t SCPI_CMD_SOUR_RES_LEV_TRIG_AMPLitude_Q(scpi_t *context);
scpi_result_t SCPI_CMD_SOUR_RES_LEV_TRIG_CALCulate_Q(scpi_t *context);

scpi_result_t SCPI_CMD_SOUR_RES_LEV_STEP_INCRement(scpi_t *context);
scpi_result_t SCPI_CMD_SOUR_RES_LEV_STEP_INCRement_Q(scpi_t *context);

scpi_result_t SCPI_CMD_SOUR_RES_LEV_STEP_MODE(scpi_t *context);
scpi_result_t SCPI_CMD_SOUR_RES_LEV_STEP_MODE_Q(scpi_t *context);

scpi_result_t SCPI_CMD_SOUR_RES_LEV_STEP_OVERflow(scpi_t *context);
scpi_result_t SCPI_CMD_SOUR_RES_LEV_STEP_OVERflow_Q(scpi_t *context);

scpi_result_t SCPI_CMD_SOUR_RES_LIM_LOW(scpi_t *context);
scpi_result_t SCPI_CMD_SOUR_RES_LIM_LOW_Q(scpi_t *context);

scpi_result_t SCPI_CMD_SOUR_RES_LIM_STATe(scpi_t *context);
scpi_result_t SCPI_CMD_SOUR_RES_LIM_STATe_Q(scpi_t *context);

scpi_result_t SCPI_CMD_SOUR_RES_LIM_HIGH(scpi_t *context);
scpi_result_t SCPI_CMD_SOUR_RES_LIM_HIGH_Q(scpi_t *context);

scpi_result_t SCPI_CMD_SOUR_RES_MODE(scpi_t *context);
scpi_result_t SCPI_CMD_SOUR_RES_MODE_Q(scpi_t *context);

/* Private functions ---------------------------------------------------------*/


#endif /* INC_COMMUNICATION_SCPI_SOURCE_RESISTANCE_DEF_H_ */
