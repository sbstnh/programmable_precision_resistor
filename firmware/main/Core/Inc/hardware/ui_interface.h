/**
 * @file    ui_interface.h
 * @author  sebas
 * @date    06.11.2022
 * @brief
 */

#ifndef INC_HARDWARE_UI_INTERFACE_H_
#define INC_HARDWARE_UI_INTERFACE_H_

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>
#include "stm32g4xx_hal.h"
#include "util/api.h"

/* Exported constants --------------------------------------------------------*/

#define UIIF_BEEP_FREQ				4000
#define UIIF_BEEP_VOL				192
#define UIIF_BEEP_SHORT				25
#define UIIF_BEEP_LONG				250
#define UIIF_BEEP_ERROR				500

#define UIIF_BUFFER					32
#define UIIF_DISP_DIGITS			18

/* Exported types ------------------------------------------------------------*/

typedef struct
{
	char cache[UIIF_BUFFER];
	bool _annunciator_cache;
	uint16_t _led_cache;
	uint16_t _led_blink_cache;

	I2C_HandleTypeDef *hi2c;
	uint8_t i2c_address;
} UIIF_TypeDef;

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

API_StatusTypeDef UIIF_ReadSwitches(UIIF_TypeDef *uiif, uint32_t *sw_state);
API_StatusTypeDef UIIF_ReadEncoder(UIIF_TypeDef *uiif, int16_t *rot_count);

API_StatusTypeDef UIIF_DisplayClear(UIIF_TypeDef *uiif);
API_StatusTypeDef UIIF_DisplayPuts(UIIF_TypeDef *uiif, const char *str, uint8_t size, bool force_update);

API_StatusTypeDef UIIF_AnnunciatorShiftSwitch(UIIF_TypeDef *uiif, bool on, bool force_update);
API_StatusTypeDef UIIF_AnnunciatorSwitch(UIIF_TypeDef *uiif, uint16_t on, bool force_update);
API_StatusTypeDef UIIF_AnnunciatorBlink(UIIF_TypeDef *uiif, uint16_t blink, bool force_update);

API_StatusTypeDef UIIF_Beep(UIIF_TypeDef *uiif, uint16_t frequency, uint8_t volume, uint16_t duration);
API_StatusTypeDef UIIF_Tick(UIIF_TypeDef *uiif);

API_StatusTypeDef UIIF_ReadFirmwareString(UIIF_TypeDef *uiif, char *str);

/* Private functions ---------------------------------------------------------*/

#endif /* INC_HARDWARE_UI_INTERFACE_H_ */
