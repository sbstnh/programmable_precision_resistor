/**
 * @file    scpi_circ_buf_def.c
 * @author  sebas
 * @date    12.11.2022
 * @brief   
 */

/* Includes ------------------------------------------------------------------*/

#include "communication/scpi_circ_buf_def.h"

/* Private defines -----------------------------------------------------------*/


#define SCPI_CIRC_BUF_RX_LEN	256
#define SCPI_CIRC_BUF_TX_LEN	256

/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


static char scpi_buf_rx[SCPI_CIRC_BUF_RX_LEN];
static char scpi_buf_tx[SCPI_CIRC_BUF_TX_LEN];

/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

CBUF_TypeDef SCPI_CIRC_BUF_RX = { (uint8_t *) scpi_buf_rx, 0, 0, sizeof(scpi_buf_rx) };
CBUF_TypeDef SCPI_CIRC_BUF_TX = { (uint8_t *) scpi_buf_tx, 0, 0, sizeof(scpi_buf_tx) };

/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

