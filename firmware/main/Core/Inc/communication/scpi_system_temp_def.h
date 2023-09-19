/**
 * @file    scpi_system_temp_def.h
 * @author  sebas
 * @date    Nov 12, 2022
 * @brief
 */
#ifndef INC_COMMUNICATION_SCPI_SYSTEM_TEMP_DEF_H_
#define INC_COMMUNICATION_SCPI_SYSTEM_TEMP_DEF_H_

/* Includes ------------------------------------------------------------------*/

#include "scpi/scpi.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

scpi_result_t SCPI_CMD_SYST_TEMP_IMMediate_Q(scpi_t *context);
scpi_result_t SCPI_CMD_SYST_TEMP_MINimum_Q(scpi_t *context);
scpi_result_t SCPI_CMD_SYST_TEMP_MAXimum_Q(scpi_t *context);
scpi_result_t SCPI_CMD_SYST_TEMP_AVERage_Q(scpi_t *context);
scpi_result_t SCPI_CMD_SYST_TEMP_RESet(scpi_t *context);

/* Private functions ---------------------------------------------------------*/


#endif /* INC_COMMUNICATION_SCPI_SYSTEM_TEMP_DEF_H_ */
