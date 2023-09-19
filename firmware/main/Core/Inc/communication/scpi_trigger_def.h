/**
 * @file    scpi_trigger_def.h
 * @author  sebas
 * @date    10.12.2022
 * @brief
 */
#ifndef INC_COMMUNICATION_SCPI_TRIGGER_DEF_H_
#define INC_COMMUNICATION_SCPI_TRIGGER_DEF_H_

/* Includes ------------------------------------------------------------------*/

#include "scpi/scpi.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

scpi_result_t SCPI_CMD_TRIG_ABOR_IMMediate(scpi_t *context);

scpi_result_t SCPI_CMD_TRIG_INIT_IMMediate(scpi_t *context);

scpi_result_t SCPI_CMD_TRIG_INIT_CONTinuous(scpi_t *context);
scpi_result_t SCPI_CMD_TRIG_INIT_CONTinuous_Q(scpi_t *context);

scpi_result_t SCPI_CMD_TRIG_TRG(scpi_t *context);

scpi_result_t SCPI_CMD_TRIG_SEQ_IMMediate(scpi_t *context);

scpi_result_t SCPI_CMD_TRIG_SEQ_DELay(scpi_t *context);
scpi_result_t SCPI_CMD_TRIG_SEQ_DELay_Q(scpi_t *context);

scpi_result_t SCPI_CMD_TRIG_SEQ_HOLDoff(scpi_t *context);
scpi_result_t SCPI_CMD_TRIG_SEQ_HOLDoff_Q(scpi_t *context);

scpi_result_t SCPI_CMD_TRIG_SEQ_SOURce(scpi_t *context);
scpi_result_t SCPI_CMD_TRIG_SEQ_SOURce_Q(scpi_t *context);

scpi_result_t SCPI_CMD_TRIG_SEQ_SLOPe(scpi_t *context);
scpi_result_t SCPI_CMD_TRIG_SEQ_SLOPe_Q(scpi_t *context);

scpi_result_t SCPI_CMD_TRIG_SEQ_TIMer(scpi_t *context);
scpi_result_t SCPI_CMD_TRIG_SEQ_TIMer_Q(scpi_t *context);

/* Private functions ---------------------------------------------------------*/


#endif /* INC_COMMUNICATION_SCPI_TRIGGER_DEF_H_ */
