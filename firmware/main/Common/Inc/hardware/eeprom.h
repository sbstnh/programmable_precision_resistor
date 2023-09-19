/**
 * @file    eeprom.h
 * @author  Sebastian Harnisch
 * @date    20.10.2022
 * @brief   Abstraction layer for I2C eeproms
 *
 *          This file contains:
 *           - data struture for accessing I2C eeproms with this library
 *           - function prototypes
 */

#ifndef INC_HARDWARE_EEPROM_H_
#define INC_HARDWARE_EEPROM_H_

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdint.h>
#include "stm32g4xx_hal.h"
#include "util/api.h"

/* Exported constants --------------------------------------------------------*/

#define EEPR_MEMORY_SIZE			4096
#define EEPR_ADDRESS_SIZE			2

#define EEPR_PAGE_NUMBER_BITS		5
#define EEPR_PAGE_SIZE				(1 << EEPR_PAGE_NUMBER_BITS)
#define EEPR_PAGES					(EEPR_MEMORY_SIZE >> EEPR_PAGE_NUMBER_BITS)

#define EEPR_TIMEOUT_TICKS			1000

#undef EEPR_INCL_VAR_ACCESS

/* Exported types ------------------------------------------------------------*/

typedef struct
{
	I2C_HandleTypeDef *i2c;
	const uint8_t device_address;

	bool enable_write;
} EEPR_TypeDef;

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** Initializes the EEPROM with zeros.
 *
 *	@param[in] eeprom  Pointer to the @ref EEPR_TypeDef struct
 */
API_StatusTypeDef EEPR_Reset(EEPR_TypeDef *eeprom);

void EEPR_Init(EEPR_TypeDef *eeprom);
API_StatusTypeDef EEPR_Read(EEPR_TypeDef *eeprom, uint16_t memory_address, uint8_t *data, uint16_t size);

#ifdef EEPR_INCL_VAR_ACCESS
API_StatusTypeDef EEPR_ReadUint8(EEPR_TypeDef *eeprom, uint16_t memory_address, uint8_t *data);
API_StatusTypeDef EEPR_ReadUint16(EEPR_TypeDef *eeprom, uint16_t memory_address, uint16_t *data);
API_StatusTypeDef EEPR_ReadUint32(EEPR_TypeDef *eeprom, uint16_t memory_address, uint32_t *data);
API_StatusTypeDef EEPR_ReadFloat(EEPR_TypeDef *eeprom, uint16_t memory_address, float *data);
#endif

void EEPR_EnableWrite(EEPR_TypeDef *eeprom);
void EEPR_DisableWrite(EEPR_TypeDef *eeprom);
bool EEPR_GetEnableWrite(EEPR_TypeDef *eeprom);

API_StatusTypeDef EEPR_Write(EEPR_TypeDef *eeprom, uint16_t memory_address, uint8_t *data, uint16_t size);

#ifdef EEPR_INCL_VAR_ACCESS
API_StatusTypeDef EEPR_WriteUInt8(EEPR_TypeDef *eeprom, uint16_t memory_address, uint8_t data);
API_StatusTypeDef EEPR_WriteUint16(EEPR_TypeDef *eeprom, uint16_t memory_address, uint16_t data);
API_StatusTypeDef EEPR_WriteUint32(EEPR_TypeDef *eeprom, uint16_t memory_address, uint32_t data);
API_StatusTypeDef EEPR_WriteFloat(EEPR_TypeDef *eeprom, uint16_t memory_address, float data);
#endif

/* Private functions ---------------------------------------------------------*/

#endif /* INC_HARDWARE_EEPROM_H_ */
