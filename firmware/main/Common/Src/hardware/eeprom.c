/**
 * @file    eeprom.c
 * @author  Sebastian Harnisch
 * @date    20.10.2022
 * @brief   Abstraction layer for I2C eeproms
 *
 *          This file contains:
 *           - Initializiation/Reset of EEPROM
 *           - Read and Write access
 */

/* Includes ------------------------------------------------------------------*/

#include <string.h>

#include "cmsis_os2.h"

#include "hardware/eeprom.h"

/* Private defines -----------------------------------------------------------*/

#define EEPROM_MUTEX_I2C_TIMEOUT		10

/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/

extern osMutexId_t i2cMutexHandle;

/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void EEPR_Init(EEPR_TypeDef *eeprom)
{
	eeprom->enable_write = false;
}

API_StatusTypeDef EEPR_Reset(EEPR_TypeDef *eeprom)
{
	uint8_t init_values[EEPR_PAGE_SIZE];
	memset(init_values, 0xFF, EEPR_PAGE_SIZE);

	if (!eeprom->enable_write)
	{
		return API_ERROR;
	}

	for (uint8_t page = 0; page < EEPR_PAGES; ++page)
	{
		if (EEPR_Write(eeprom, page * EEPR_PAGE_SIZE, init_values, EEPR_PAGE_SIZE) != API_OK)
		{
			return API_ERROR;
		}
	}

	return API_OK;
}

API_StatusTypeDef EEPR_Read(EEPR_TypeDef *eeprom, uint16_t memory_address, uint8_t *data, uint16_t size)
{
	HAL_StatusTypeDef status;
	uint16_t pos = 0;
	int32_t bytes_left = size;
	uint16_t bytes_left_on_page;
	uint16_t bytes_this_iteration;

	if (((uint32_t)memory_address) + size > EEPR_MEMORY_SIZE)
	{
		return API_ERROR;
	}

	if (osMutexAcquire(i2cMutexHandle, EEPROM_MUTEX_I2C_TIMEOUT) != osOK)
	{
		return API_ERROR;
	}

	while (bytes_left)
	{
		bytes_left_on_page = EEPR_PAGE_SIZE - ((memory_address + pos) & (EEPR_PAGE_SIZE - 1));
		bytes_this_iteration = (bytes_left_on_page < bytes_left) ? bytes_left_on_page : bytes_left;

		status = HAL_I2C_Mem_Read(eeprom->i2c, eeprom->device_address, memory_address + pos, EEPR_ADDRESS_SIZE, &data[pos], bytes_this_iteration, EEPR_TIMEOUT_TICKS);

		if (status != HAL_OK)
		{
			osMutexRelease(i2cMutexHandle);
			return API_ERROR;
		}

		bytes_left -= bytes_this_iteration;
		pos += bytes_this_iteration;
	}

	osMutexRelease(i2cMutexHandle);
	return API_OK;
}

#ifdef EEPR_INCL_VAR_ACCESS

API_StatusTypeDef EEPR_ReadUint8(EEPR_TypeDef *eeprom, uint16_t memory_address, uint8_t *data)
{
	return EEPR_Read(eeprom, memory_address, data, 1);
}

API_StatusTypeDef EEPR_ReadUint16(EEPR_TypeDef *eeprom, uint16_t memory_address, uint16_t *data)
{
	return EEPR_Read(eeprom, memory_address, (uint8_t *) data, 2);
}

API_StatusTypeDef EEPR_ReadUint32(EEPR_TypeDef *eeprom, uint16_t memory_address, uint32_t *data)
{
	return EEPR_Read(eeprom, memory_address, (uint8_t *) data, 4);
}

API_StatusTypeDef EEPR_ReadFloat(EEPR_TypeDef *eeprom, uint16_t memory_address, float *data)
{
	return EEPR_Read(eeprom, memory_address, (uint8_t *) data, 4);
}

#endif


void EEPR_EnableWrite(EEPR_TypeDef *eeprom)
{
	eeprom->enable_write = true;
}

void EEPR_DisableWrite(EEPR_TypeDef *eeprom)
{
	eeprom->enable_write = false;
}

bool EEPR_GetEnableWrite(EEPR_TypeDef *eeprom)
{
	return eeprom->enable_write;
}


API_StatusTypeDef EEPR_Write(EEPR_TypeDef *eeprom, uint16_t memory_address, uint8_t *data, uint16_t size)
{
	HAL_StatusTypeDef status;
	uint16_t pos = 0;
	int32_t bytes_left = size;
	uint16_t bytes_left_on_page;
	uint16_t bytes_this_iteration;
	uint8_t read_buffer[32];

	if (((uint32_t)memory_address) + size > EEPR_MEMORY_SIZE)
	{
		return API_INVALID_OPERATION;
	}

	if (osMutexAcquire(i2cMutexHandle, EEPROM_MUTEX_I2C_TIMEOUT) != osOK)
	{
		return API_ERROR;
	}

	while (bytes_left)
	{
		bytes_left_on_page = EEPR_PAGE_SIZE - ((memory_address + pos) & (EEPR_PAGE_SIZE - 1));
		bytes_this_iteration = (bytes_left_on_page < bytes_left) ? bytes_left_on_page: bytes_left;

		// First read the section
		status = HAL_I2C_Mem_Read(eeprom->i2c, eeprom->device_address, memory_address + pos,
								  EEPR_ADDRESS_SIZE, read_buffer, bytes_this_iteration,
								  EEPR_TIMEOUT_TICKS);

		if (status != HAL_OK)
		{
			osMutexRelease(i2cMutexHandle);
			return API_ERROR;
		}

		// Write if data don't already match
		if (memcmp(read_buffer, data + pos, bytes_this_iteration) != 0)
		{
			// Check that writing data to eeprom is still allowed
			if (!eeprom->enable_write)
			{
				osMutexRelease(i2cMutexHandle);
				return API_INVALID_OPERATION;
			}

			status = HAL_I2C_Mem_Write(eeprom->i2c, eeprom->device_address, memory_address + pos,
									   EEPR_ADDRESS_SIZE, data + pos, bytes_this_iteration,
									   EEPR_TIMEOUT_TICKS);

			if (status != HAL_OK)
			{
				osMutexRelease(i2cMutexHandle);
				return API_ERROR;
			}

			// Might not be required
			HAL_Delay(10);
		}

		bytes_left -= bytes_this_iteration;
		pos += bytes_this_iteration;
	}

	osMutexRelease(i2cMutexHandle);
	return API_OK;
}

#ifdef EEPR_INCL_VAR_ACCESS

API_StatusTypeDef EEPR_WriteUInt8(EEPR_TypeDef *eeprom, uint16_t memory_address, uint8_t data)
{
	return EEPR_Write(eeprom, memory_address, &data, 1);
}

API_StatusTypeDef EEPR_WriteUint16(EEPR_TypeDef *eeprom, uint16_t memory_address, uint16_t data)
{
	return EEPR_Write(eeprom, memory_address, (uint8_t *) &data, 2);
}

API_StatusTypeDef EEPR_WriteUint32(EEPR_TypeDef *eeprom, uint16_t memory_address, uint32_t data)
{
	return EEPR_Write(eeprom, memory_address, (uint8_t *) &data, 4);
}

API_StatusTypeDef EEPR_WriteFloat(EEPR_TypeDef *eeprom, uint16_t memory_address, float data)
{
	return EEPR_Write(eeprom, memory_address, (uint8_t *) &data, 4);
}

#endif

/* Private functions ---------------------------------------------------------*/
