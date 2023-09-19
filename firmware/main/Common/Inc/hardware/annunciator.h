/**
 * @file    led.h
 * @author  sebas
 * @date    Jan 15, 2023
 * @brief
 */
#ifndef INC_HARDWARE_ANNUNCIATOR_H_
#define INC_HARDWARE_ANNUNCIATOR_H_

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdint.h>

/* Exported constants --------------------------------------------------------*/

#define ANN_COLOR_ON		0xFF
#define ANN_COLOR_OFF		0x00

/* Exported types ------------------------------------------------------------*/

typedef struct
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} ANN_ColorTypeDef;

typedef struct
{
	uint8_t tag_r;
	uint8_t tag_g;
	uint8_t tag_b;
	ANN_ColorTypeDef _state;
	bool _blink;
} ANN_TypeDef;

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

extern const ANN_ColorTypeDef ANN_OFF;
extern const ANN_ColorTypeDef ANN_RED;
extern const ANN_ColorTypeDef ANN_GREEN;
extern const ANN_ColorTypeDef ANN_ORANGE;

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void ANN_Setup(ANN_TypeDef *ann, uint8_t tag_r, uint8_t tag_g, uint8_t tag_b);
void ANN_Init(ANN_TypeDef *ann);

void ANN_SetState(ANN_TypeDef *ann, ANN_ColorTypeDef state);
ANN_ColorTypeDef ANN_GetState(ANN_TypeDef *ann);

void ANN_SetRed(ANN_TypeDef *ann, uint8_t red);
void ANN_SetGreen(ANN_TypeDef *ann, uint8_t green);
void ANN_SetBlue(ANN_TypeDef *ann, uint8_t blue);

void ANN_Blink(ANN_TypeDef *ann, bool blink);

/* Private functions ---------------------------------------------------------*/


#endif /* INC_HARDWARE_ANNUNCIATOR_H_ */
