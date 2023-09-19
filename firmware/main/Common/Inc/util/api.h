/*
 * api.h
 *
 *  Created on: Aug 22, 2021
 *      Author: sebas
 */

#ifndef INC_API_H_
#define INC_API_H_

typedef enum
{
	API_OK = 0x00U,
	API_ERROR = 0x01U,

	API_BUSY = 0x02U,
	API_TIMEOUT = 0x03U,

	API_INVALID_OPERATION = 0x04U,
	API_PARAM_OUT_OF_RANGE = 0x05U,
	API_HARDWARE_ERROR = 0x06U,

	API_ABORTED = 0x07U,
	API_TERMINATED = 0x08U,
	API_CHANGED = 0x09U,
	API_UNCHANGED = 0x0AU
} API_StatusTypeDef;

#endif /* INC_API_H_ */
