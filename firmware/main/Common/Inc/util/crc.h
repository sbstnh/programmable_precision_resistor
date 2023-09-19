/*
 * crc.h
 *
 *  Created on: Oct 22, 2022
 *      Author: sebas
 */

#ifndef INC_UTIL_CRC_H_
#define INC_UTIL_CRC_H_

#include <stdint.h>

uint32_t CRC_Calculate(uint8_t *data, uint16_t size);

#endif /* INC_UTIL_CRC_H_ */
