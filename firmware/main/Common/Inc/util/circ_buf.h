/**
 * @file    circ_buf.h
 * @author  sebas
 * @date    12.11.2022
 * @brief
 */
#ifndef INC_UTIL_CIRC_BUF_H_
#define INC_UTIL_CIRC_BUF_H_

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

typedef struct
{
     uint8_t *buf;		/**< Buffer */
     uint16_t write;	/**< Always empty */
     uint16_t read;		/**< The "oldest" element */
     uint16_t size;		/**< Size of the buffer */
} CBUF_TypeDef;

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void CBUF_Init(CBUF_TypeDef *cbuf, uint8_t *buf, uint16_t size);
void CBUF_Reset(CBUF_TypeDef *cbuf);
bool CBUF_Empty(CBUF_TypeDef *cbuf);
bool CBUF_Full(CBUF_TypeDef *cbuf);
uint16_t CBUF_Read(CBUF_TypeDef *cbuf, uint8_t *buf, uint16_t len);
uint16_t CBUF_Write(CBUF_TypeDef *cbuf, const uint8_t *buf, uint16_t len);

/* Private functions ---------------------------------------------------------*/




#endif /* INC_UTIL_CIRC_BUF_H_ */
