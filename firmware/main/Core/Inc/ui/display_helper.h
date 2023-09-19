/**
 * @file    ui_display.h
 * @author  sebas
 * @date    19.12.2022
 * @brief
 */
#ifndef INC_UI_DISPLAY_HELPER_H_
#define INC_UI_DISPLAY_HELPER_H_

/* Includes ------------------------------------------------------------------*/

#include "application/app_params.h"

/* Exported constants --------------------------------------------------------*/

#define DISP_CHAR_BLINK_DIMMED		0x1B
#define DISP_CHAR_DIMMED			0x1C
#define DISP_SEQ_BLINK_DIMMED		0x1D
#define DISP_SEQ_DIMMED				0x1E

/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void UI_Display_FormatTextCentered(char *target, const char *str, uint8_t max_len);
void UI_Display_SectionModeIndicator(char *str, RES_MODE_TypeDef mode);
void UI_Display_SectionPrimary(char *str);
void UI_DisplaySectionSecondary(char *str);
void UI_Display_Update(const char * str);
void UI_Display_Disable();

void UI_Display_OnTriggered();

/* Private functions ---------------------------------------------------------*/


#endif /* INC_UI_DISPLAY_HELPER_H_ */
