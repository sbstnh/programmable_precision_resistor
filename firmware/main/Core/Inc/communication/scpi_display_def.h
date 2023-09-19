/**
 * @file    scpi_display_def.h
 * @author  sebas
 * @date    11.11.2022
 * @brief
 */
#ifndef INC_COMMUNICATION_SCPI_DISPLAY_DEF_H_
#define INC_COMMUNICATION_SCPI_DISPLAY_DEF_H_

/* Includes ------------------------------------------------------------------*/

#include "scpi/scpi.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

scpi_result_t SCPI_CMD_DISP_ENABle(scpi_t *context);
scpi_result_t SCPI_CMD_DISP_ENABle_Q(scpi_t *context);

scpi_result_t SCPI_CMD_DISP_USER_TEXT_DATA(scpi_t *context);
scpi_result_t SCPI_CMD_DISP_USER_TEXT_DATA_Q(scpi_t *context);

scpi_result_t SCPI_CMD_DISP_USER_TEXT_STATe(scpi_t *context);
scpi_result_t SCPI_CMD_DISP_USER_TEXT_STATe_Q(scpi_t *context);

scpi_result_t SCPI_CMD_DISP_USER_TEXT_CLEar(scpi_t *context);

scpi_result_t SCPI_CMD_DISP_MAIN_PRIM_RESolution(scpi_t *context);
scpi_result_t SCPI_CMD_DISP_MAIN_PRIM_RESolution_Q(scpi_t *context);

scpi_result_t SCPI_CMD_DISP_MAIN_MODE(scpi_t *context);
scpi_result_t SCPI_CMD_DISP_MAIN_MODE_Q(scpi_t *context);

/* Private functions ---------------------------------------------------------*/


#endif /* INC_COMMUNICATION_SCPI_DISPLAY_DEF_H_ */
