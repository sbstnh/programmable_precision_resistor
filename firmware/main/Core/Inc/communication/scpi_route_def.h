/**
 * @file    scpi_route_def.h
 * @author  sebas
 * @date    11.11.2022
 * @brief
 */

#ifndef INC_COMMUNICATION_SCPI_ROUTE_DEF_H_
#define INC_COMMUNICATION_SCPI_ROUTE_DEF_H_

/* Includes ------------------------------------------------------------------*/

#include "scpi/scpi.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

scpi_result_t SCPI_CMD_ROUT_REL_OPEN(scpi_t *context);
scpi_result_t SCPI_CMD_ROUT_REL_CLOSe(scpi_t *context);

scpi_result_t SCPI_CMD_ROUT_REL_STATe(scpi_t *context);
scpi_result_t SCPI_CMD_ROUT_REL_STATe_Q(scpi_t *context);

/* Private functions ---------------------------------------------------------*/


#endif /* INC_COMMUNICATION_SCPI_ROUTE_DEF_H_ */
