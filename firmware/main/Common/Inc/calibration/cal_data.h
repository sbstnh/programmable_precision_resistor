/*
 * cal_data.h
 *
 *  Created on: 28.10.2022
 *      Author: sebas
 */

#ifndef INC_APPLICATION_CAL_DATA_H_
#define INC_APPLICATION_CAL_DATA_H_

#include <stdint.h>

#define CALDATA_BLOCK_SIZE			768
#define CALDATA_BLOCK_SIZE_WO_CRC	(CALDATA_BLOCK_SIZE - 4)
#define CALDATA_MAX_BLOCK_SIZE		768

typedef union
{
	struct __attribute__((packed))
	{
		uint32_t CAL_CNT;
		uint8_t CALIBRATED;
		uint8_t RESERVED1[23];
		uint32_t CAL_TEMP;

		uint8_t CAL_DATE[48];
		uint8_t CAL_STR[48];

		uint32_t CAL_VAL_2W[60];
		uint32_t RESERVED3[4];

		uint32_t CAL_VAL_4W[60];
		uint32_t RESERVED4[4];

		uint32_t RESERVED5[31];

		uint32_t CRC_CHECKSUM;
	};
	uint8_t AS_BYTE[CALDATA_BLOCK_SIZE];
} CALDATA_TypeDef;

#endif /* INC_APPLICATION_CAL_DATA_H_ */
