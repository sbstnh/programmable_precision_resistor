/**
 * @file    scpi_system_def.h
 * @author  sebas
 * @date    11.11.2022
 * @brief
 */
#ifndef INC_COMMUNICATION_SCPI_SYSTEM_DEF_H_
#define INC_COMMUNICATION_SCPI_SYSTEM_DEF_H_

/* Includes ------------------------------------------------------------------*/

#include "scpi/scpi.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

scpi_result_t SCPI_CMD_SYST_BEEP_IMMediate(scpi_t *context);
scpi_result_t SCPI_CMD_SYSTEM_Beeper_Tick(scpi_t *context);

scpi_result_t SCPI_CMD_SYST_BEEP_STATe(scpi_t *context);
scpi_result_t SCPI_CMD_SYST_BEEP_STATe_Q(scpi_t *context);

scpi_result_t SCPI_CMD_SYST_COMM_RLSTate(scpi_t *context);
scpi_result_t SCPI_CMD_SYST_COMM_RLSTate_Q(scpi_t *context);

scpi_result_t SCPI_CMD_SYST_DEF_IMMediate(scpi_t *context);

scpi_result_t SCPI_CMD_SYST_FVER_MAIN_Q(scpi_t *context);
scpi_result_t SCPI_CMD_SYST_FVER_UI_Q(scpi_t *context);

scpi_result_t SCPI_CMD_SYST_LOCal(scpi_t *context);
scpi_result_t SCPI_CMD_SYST_MIXed(scpi_t *context);
scpi_result_t SCPI_CMD_SYST_REMote(scpi_t *context);
scpi_result_t SCPI_CMD_SYST_RWLock(scpi_t *context);

scpi_result_t SCPI_CMD_SYST_SEC_IMMediate(scpi_t *context);

/* Private functions ---------------------------------------------------------*/


#endif /* INC_COMMUNICATION_SCPI_SYSTEM_DEF_H_ */
