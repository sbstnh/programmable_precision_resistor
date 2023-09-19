/**
 * @file    circ_buf.c
 * @author  sebas
 * @date    12.11.2022
 * @brief	This module implements a circular buffer
 */

/* Includes ------------------------------------------------------------------*/

#include "util/circ_buf.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/


/** Initializes circular buffer.
 *
 *	@param[in] cbuf	 Pointer to the circular buffer.
 *	@param[in] buf	 Reference to the buffer to be used.
 *	@param[in] size	 Size of the buffer, only size - 1 is available.
 */
void CBUF_Init(CBUF_TypeDef *cbuf, uint8_t *buf, uint16_t size)
{
	cbuf->size = size;
	cbuf->buf = buf;
	CBUF_Reset(cbuf);
}


/** Resets the circular buffer.
 *
 *	@param[in] cbuf	 Pointer to the circular buffer.
 */
void CBUF_Reset(CBUF_TypeDef *cbuf)
{
	cbuf->write = 0;
	cbuf->read = 0;
}


/** Returns whether the buffer is empty.
 *
 * 	@param[in] cbuf	 Pointer to the circular buffer.
 *
 *  @return true if empty.
 */
bool CBUF_Empty(CBUF_TypeDef *cbuf)
{
	return cbuf->read == cbuf->write;
}



/** Returns whether the buffer is full.
 *
 * 	@param[in] cbuf	 Pointer to the circular buffer.
 *
 *  @return true if full.
 */
bool CBUF_Full(CBUF_TypeDef *cbuf)
{
	return (cbuf->write + 1 == cbuf->read) || ((cbuf->read == 0) && (cbuf->write + 1 == cbuf->size));
}


/** Reads from the circular buffer.
 *
 * 	@param[in] cbuf	 Pointer to the circular buffer.
 * 	@param[in] buf	 Pointer to the buffer to write to.
 * 	@param[in] len   Number of bytes to read.
 *
 *  @return The number of bytes read.
 */
uint16_t CBUF_Read(CBUF_TypeDef *cbuf, uint8_t *buf, uint16_t len)
{
	uint8_t *buf_pointer = buf;
	uint16_t i = 0;
	
	while (i < len && !CBUF_Empty(cbuf))
	{
		*buf_pointer = cbuf->buf[cbuf->read];
		buf_pointer++;
		cbuf->read++;

		if (cbuf->read >= cbuf->size)
		{
			cbuf->read = 0;
		}
		
		i++;
	}
	return i;
}


/** Writes to the circular buffer. If the buffer is too small,
 *  the function returns with the number of bytes written.
 *
 *  @param[in] cbuf	 Pointer to the circular buffer.
 * 	@param[in] buf	 Pointer to the data to read into.
 * 	@param[in] len   Number of bytes to read.
 *
 * 	@return The number of bytes written.
 */
uint16_t CBUF_Write(CBUF_TypeDef *cbuf, const uint8_t *buf, uint16_t len)
{
	uint8_t *buf_pointer = (uint8_t *) buf;
	uint16_t i = 0;
	
	while (i < len && !CBUF_Full(cbuf))
	{
		cbuf->buf[cbuf->write] = *buf_pointer;
		cbuf->write++;
		buf_pointer++;

		if (cbuf->write >= cbuf->size)
		{
			cbuf->write = 0;
		}
		
		i++;
	}
	return i;
}

/* Private functions ---------------------------------------------------------*/

