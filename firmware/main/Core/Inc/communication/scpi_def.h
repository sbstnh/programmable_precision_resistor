/**
 * @file    scpi_def.h
 * @author  sebas
 * @date    09.08.2021
 * @brief
 */

#ifndef INC_SCPI_DEF_H_
#define INC_SCPI_DEF_H_

/* Includes ------------------------------------------------------------------*/

#include "scpi/scpi.h"
#include "util/circ_buf.h"

/* Exported constants --------------------------------------------------------*/

#define SCPI_INPUT_BUFFER_LENGTH 256
#define SCPI_ERROR_QUEUE_SIZE 20
#define SCPI_IDN1 "SHARNISCH"
#define SCPI_IDN2 "PR-1M"
#define SCPI_IDN3 NULL
#define SCPI_IDN4 VERSION_STRING_MAINBOARD

/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

extern const scpi_command_t scpi_commands[];
extern scpi_interface_t scpi_interface;
extern char scpi_input_buffer[];
extern scpi_error_t scpi_error_queue_data[];
extern scpi_t scpi_context;

extern CBUF_TypeDef SCPI_CIRC_BUF_TX;

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

//size_t SCPI_Write(scpi_t *context, const char *data, size_t len);
//int SCPI_Error(scpi_t *context, int_fast16_t err);
scpi_result_t SCPI_Control(scpi_t *context, scpi_ctrl_name_t ctrl, scpi_reg_val_t val);
scpi_result_t SCPI_Reset(scpi_t *context);
scpi_result_t SCPI_Flush(scpi_t *context);

/* Private functions ---------------------------------------------------------*/

#endif /* INC_SCPI_DEF_H_ */
