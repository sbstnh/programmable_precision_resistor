/**
 * @file    ui_interface.c
 * @author  sebas
 * @date    06.11.2022
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "cmsis_os2.h"
#include "hardware/ui_interface.h"

/* Private defines -----------------------------------------------------------*/

#define UIIF_MUTEX_TIMOUT			5

#define UIIF_I2C_BUFFER_SIZE		UIIF_BUFFER + 1
#define UIIF_I2C_TIMEOUT			5

#define UIIF_REG_SW_STATE			0
#define UIIF_REG_ROT_CNT			4

#define UIIF_REG_DISP_CLEAR			16
#define UIIF_REG_DISP_CURSOR_POS	17
#define UIIF_REG_DISP_CHARACTERS	18
#define UIIF_REG_DISP_APPLY			54
#define UIIF_REG_DISP_DIMMED		82
#define UIIF_REG_DISP_DP_Q_DIMMED	86
#define UIIF_REG_DISP_BLINK			90
#define UIIF_REG_DISP_DP_Q_BLINK	94
#define UIIF_REG_DISP_SHIFT_ANN		98

#define UIIF_REG_LEDS				112
#define UIIF_REG_LED_DIMMED			114
#define UIIF_REG_LED_BLINK			116

#define UIIF_REG_FREQUENCY			128
#define UIIF_REG_VOLUME				130
#define UIIF_REG_BEEP				131
#define UIIF_REG_TICK				133

#define UIIF_REG_FIRMWARE_STR		148
#define UIIF_REG_FIRMWARE_STR_LEN	28

/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/

extern osMutexId_t i2cMutexHandle;

/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

API_StatusTypeDef _UI_LL_I2C_Write(UIIF_TypeDef *uiif, uint8_t control_register, const uint8_t *data, uint8_t length, bool terminate);

/* Exported functions --------------------------------------------------------*/

API_StatusTypeDef UIIF_ReadSwitches(UIIF_TypeDef *uiif, uint32_t *sw_state)
{
	*sw_state = 0;

	if (osMutexAcquire(i2cMutexHandle, UIIF_MUTEX_TIMOUT) != osOK)
	{
		return API_ERROR;
	}

	// Read/set three bytes only, although 32-bit variable - we have 24 switches only
	if (HAL_I2C_Mem_Read(uiif->hi2c, uiif->i2c_address, (uint8_t)UIIF_REG_SW_STATE, sizeof(uint8_t), (uint8_t *)sw_state, 3, UIIF_I2C_TIMEOUT) != HAL_OK)
	{
		osMutexRelease(i2cMutexHandle);
		return API_ERROR;
	}

	osMutexRelease(i2cMutexHandle);
	return API_OK;
}

API_StatusTypeDef UIIF_ReadEncoder(UIIF_TypeDef *uiif, int16_t *rot_count)
{
	if (osMutexAcquire(i2cMutexHandle, UIIF_MUTEX_TIMOUT) != osOK)
	{
		return API_ERROR;
	}

	if (HAL_I2C_Mem_Read(uiif->hi2c, uiif->i2c_address, (uint8_t)UIIF_REG_ROT_CNT, sizeof(uint8_t), (uint8_t *)rot_count, 2, UIIF_I2C_TIMEOUT) != HAL_OK)
	{
		osMutexRelease(i2cMutexHandle);
		return API_ERROR;
	}

	osMutexRelease(i2cMutexHandle);
	return API_OK;
}

API_StatusTypeDef UIIF_DisplayClear(UIIF_TypeDef *uiif)
{
	if (osMutexAcquire(i2cMutexHandle, UIIF_MUTEX_TIMOUT) != osOK)
	{
		return API_ERROR;
	}

	const uint8_t clear = 1;

	if (_UI_LL_I2C_Write(uiif, UIIF_REG_DISP_CLEAR, (uint8_t *) &clear, sizeof(clear), false) != API_OK)
	{
		osMutexRelease(i2cMutexHandle);
		return API_ERROR;
	}

	osMutexRelease(i2cMutexHandle);
	return API_OK;
}


API_StatusTypeDef UIIF_DisplayPuts(UIIF_TypeDef *uiif, const char *str, uint8_t size, bool force_update)
{
	// Caching mechanism in order to write data less frequently.
	if (!force_update && strncmp(str, uiif->cache, UIIF_BUFFER) == 0)
	{
		return API_OK;
	}

	if (osMutexAcquire(i2cMutexHandle, UIIF_MUTEX_TIMOUT) != osOK)
	{
		return API_ERROR;
	}


	if (_UI_LL_I2C_Write(uiif, UIIF_REG_DISP_CHARACTERS, (uint8_t *) str, size, true) != API_OK)
	{
		osMutexRelease(i2cMutexHandle);
		return API_ERROR;
	}

	const uint8_t apply = 1;
	if (_UI_LL_I2C_Write(uiif, UIIF_REG_DISP_APPLY, (uint8_t *)&apply, sizeof(apply), false) != API_OK)
	{
		osMutexRelease(i2cMutexHandle);
		return API_ERROR;
	}

	// Copy string into cache
	strncpy(uiif->cache, str, UIIF_BUFFER);

	osMutexRelease(i2cMutexHandle);
	return API_OK;
}


API_StatusTypeDef UIIF_AnnunciatorShiftSwitch(UIIF_TypeDef *uiif, bool on, bool force_update)
{
	if (!force_update && uiif->_annunciator_cache == on)
	{
		return API_OK;
	}

	if (osMutexAcquire(i2cMutexHandle, UIIF_MUTEX_TIMOUT) != osOK)
	{
		return API_ERROR;
	}

	if (_UI_LL_I2C_Write(uiif, UIIF_REG_DISP_SHIFT_ANN, (uint8_t *) &on, sizeof(on), false) != API_OK)
	{
		osMutexRelease(i2cMutexHandle);
		return API_ERROR;
	}

	// Backup on
	uiif->_annunciator_cache = on;

	osMutexRelease(i2cMutexHandle);
	return API_OK;
}


API_StatusTypeDef UIIF_AnnunciatorSwitch(UIIF_TypeDef *uiif, uint16_t on, bool force_update)
{
	if (!force_update && uiif->_led_cache == on)
	{
		return API_OK;
	}

	if (osMutexAcquire(i2cMutexHandle, UIIF_MUTEX_TIMOUT) != osOK)
	{
		return API_ERROR;
	}

	if (_UI_LL_I2C_Write(uiif, UIIF_REG_LEDS, (uint8_t *) &on, sizeof(on), false) != API_OK)
	{
		osMutexRelease(i2cMutexHandle);
		return API_ERROR;
	}

	// back up led
	uiif->_led_cache = on;

	osMutexRelease(i2cMutexHandle);
	return API_OK;
}


API_StatusTypeDef UIIF_AnnunciatorBlink(UIIF_TypeDef *uiif, uint16_t blink, bool force_update)
{
	if (!force_update && uiif->_led_blink_cache == blink)
	{
		return API_OK;
	}

	if (osMutexAcquire(i2cMutexHandle, UIIF_MUTEX_TIMOUT) != osOK)
	{
		return API_ERROR;
	}

	if (_UI_LL_I2C_Write(uiif, UIIF_REG_LED_BLINK, (uint8_t *) &blink, sizeof(blink), false) != API_OK)
	{
		osMutexRelease(i2cMutexHandle);
		return API_ERROR;
	}

	// back up led
	uiif->_led_blink_cache = blink;

	osMutexRelease(i2cMutexHandle);
	return API_OK;
}


API_StatusTypeDef UIIF_Beep(UIIF_TypeDef *uiif, uint16_t frequency, uint8_t volume, uint16_t duration)
{
	if (osMutexAcquire(i2cMutexHandle, UIIF_MUTEX_TIMOUT) != osOK)
	{
		return API_ERROR;
	}

	if (_UI_LL_I2C_Write(uiif, UIIF_REG_FREQUENCY, (uint8_t *) &frequency, sizeof(frequency), false) != API_OK)
	{
		osMutexRelease(i2cMutexHandle);
		return API_ERROR;
	}

	if (_UI_LL_I2C_Write(uiif, UIIF_REG_VOLUME, (uint8_t *) &volume, sizeof(volume), false) != API_OK)
	{
		osMutexRelease(i2cMutexHandle);
		return API_ERROR;
	}

	if (_UI_LL_I2C_Write(uiif, UIIF_REG_BEEP, (uint8_t *) &duration, sizeof(duration), false) != API_OK)
	{
		osMutexRelease(i2cMutexHandle);
		return API_ERROR;
	}

	osMutexRelease(i2cMutexHandle);
	return API_OK;
}


API_StatusTypeDef UIIF_Tick(UIIF_TypeDef *uiif)
{
	if (osMutexAcquire(i2cMutexHandle, UIIF_MUTEX_TIMOUT) != osOK)
	{
		return API_ERROR;
	}

	const bool tick = true;
	if (_UI_LL_I2C_Write(uiif, UIIF_REG_TICK, (uint8_t *) &tick, sizeof(tick), false) != API_OK)
	{
		osMutexRelease(i2cMutexHandle);
		return API_ERROR;
	}

	osMutexRelease(i2cMutexHandle);
	return API_OK;
}



API_StatusTypeDef UIIF_ReadFirmwareString(UIIF_TypeDef *uiif, char *str)
{
	if (osMutexAcquire(i2cMutexHandle, UIIF_MUTEX_TIMOUT) != osOK)
	{
		return API_ERROR;
	}

	if (HAL_I2C_Mem_Read(uiif->hi2c, uiif->i2c_address, (uint8_t)UIIF_REG_FIRMWARE_STR, sizeof(uint8_t),
			(uint8_t *)str, UIIF_REG_FIRMWARE_STR_LEN, UIIF_I2C_TIMEOUT) != HAL_OK)
	{
		osMutexRelease(i2cMutexHandle);
		return API_ERROR;
	}

	osMutexRelease(i2cMutexHandle);
	return API_OK;
}


/* Private functions ---------------------------------------------------------*/

/**
 * @brief Write register(s) over I2C
 *
 * @param pca				Handle to @ref PCA_TypeDef
 * @param control_register	Address of control register to write to
 * @param data				Pointer to the data to be written
 * @param length			Number of bytes to write
 * @param terminate			Append a '\0' termination
 *
 * @return API status
 */
API_StatusTypeDef _UI_LL_I2C_Write(UIIF_TypeDef *uiif, uint8_t control_register, const uint8_t *data, uint8_t length, bool terminate)
{
	uint8_t buffer[UIIF_I2C_BUFFER_SIZE + 1];

	// protocol:
	// START cond | Slave Address + RW | >A< | Control Register | >A< | data for Register(s) | >A< | STOP cond
	buffer[0] = control_register; // control register
	memcpy(buffer + 1, data, length * sizeof(buffer[0]));

	if (terminate)
	{
		length++;
		buffer[length] = '\0';
	}

	const HAL_StatusTypeDef result = HAL_I2C_Master_Transmit(uiif->hi2c, uiif->i2c_address, buffer, length + 1, UIIF_I2C_TIMEOUT);

	if (result != HAL_OK)
	{
		return API_ERROR;
	}

	return API_OK;
}
