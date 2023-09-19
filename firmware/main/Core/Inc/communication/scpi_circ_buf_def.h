/**
 * @file    circ_buf_def.h
 * @author  sebas
 * @date    12.11.2022
 * @brief   
 */
#ifndef INC_COMMUNICATION_SCPI_CIRC_BUF_DEF_H_
#define INC_COMMUNICATION_SCPI_CIRC_BUF_DEF_H_

/* Includes ------------------------------------------------------------------*/

#include "util/circ_buf.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

extern CBUF_TypeDef SCPI_CIRC_BUF_RX;	/**< Circular buffer for data received over USB */
extern CBUF_TypeDef SCPI_CIRC_BUF_TX;	/**< Circular buffer for data to be transmitted over USB */

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


#endif /* INC_COMMUNICATION_SCPI_CIRC_BUF_DEF_H_ */
