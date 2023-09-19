/**
 * @file    scpi_source_list_def.h
 * @author  sebas
 * @date    04.12.2022
 * @brief
 */
#ifndef INC_COMMUNICATION_SCPI_SOURCE_LIST_DEF_H_
#define INC_COMMUNICATION_SCPI_SOURCE_LIST_DEF_H_

/* Includes ------------------------------------------------------------------*/

#include "scpi/scpi.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/


scpi_result_t SCPI_CMD_SOUR_LIST_RES_LEVel(scpi_t *context);
scpi_result_t SCPI_CMD_SOUR_LIST_RES_LEVel_Q(scpi_t *context);
scpi_result_t SCPI_CMD_SOUR_LIST_RES_POINts(scpi_t *context);
scpi_result_t SCPI_CMD_SOUR_LIST_RES_POINts_Q(scpi_t *context);

scpi_result_t SCPI_CMD_SOUR_LIST_RES_INDex_Q(scpi_t *context);

scpi_result_t SCPI_CMD_SOUR_LIST_RES_RUN_NUMBer_Q(scpi_t *context);

scpi_result_t SCPI_CMD_SOUR_LIST_RES_RUN_COUNt(scpi_t *context);
scpi_result_t SCPI_CMD_SOUR_LIST_RES_RUN_COUNt_Q(scpi_t *context);

scpi_result_t SCPI_CMD_SOUR_LIST_RES_DWELl(scpi_t *context);
scpi_result_t SCPI_CMD_SOUR_LIST_RES_DWELl_Q(scpi_t *context);
scpi_result_t SCPI_CMD_SOUR_LIST_RES_DWEL_POINts(scpi_t *context);
scpi_result_t SCPI_CMD_SOUR_LIST_RES_DWEL_POINts_Q(scpi_t *context);

scpi_result_t SCPI_CMD_SOUR_LIST_STAR_INPut(scpi_t *context);
scpi_result_t SCPI_CMD_SOUR_LIST_STAR_INPut_Q(scpi_t *context);

scpi_result_t SCPI_CMD_SOUR_LIST_STAR_MODE(scpi_t *context);
scpi_result_t SCPI_CMD_SOUR_LIST_STAR_MODE_Q(scpi_t *context);

scpi_result_t SCPI_CMD_SOUR_LIST_STEP(scpi_t *context);
scpi_result_t SCPI_CMD_SOUR_LIST_STEP_Q(scpi_t *context);

scpi_result_t SCPI_CMD_SOUR_LIST_TERM_INPut(scpi_t *context);
scpi_result_t SCPI_CMD_SOUR_LIST_TERM_INPut_Q(scpi_t *context);

scpi_result_t SCPI_CMD_SOUR_LIST_TERM_LAST(scpi_t *context);
scpi_result_t SCPI_CMD_SOUR_LIST_TERM_LAST_Q(scpi_t *context);

/* Private functions ---------------------------------------------------------*/


#endif /* INC_COMMUNICATION_SCPI_SOURCE_LIST_DEF_H_ */
