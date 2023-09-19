/**
 * @file    led.c
 * @author  sebas
 * @date    Jan 15, 2023
 * @brief
 */

/* Includes ------------------------------------------------------------------*/

#include <hardware/annunciator.h>

/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

const ANN_ColorTypeDef ANN_OFF = 	{ANN_COLOR_OFF,	ANN_COLOR_OFF,	ANN_COLOR_OFF};
const ANN_ColorTypeDef ANN_RED =	{ANN_COLOR_ON,	ANN_COLOR_OFF,	ANN_COLOR_OFF};
const ANN_ColorTypeDef ANN_GREEN = 	{ANN_COLOR_OFF,	ANN_COLOR_ON,	ANN_COLOR_OFF};
const ANN_ColorTypeDef ANN_ORANGE = {ANN_COLOR_ON,	ANN_COLOR_ON,	ANN_COLOR_OFF};

/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void ANN_Setup(ANN_TypeDef *ann, uint8_t tag_r, uint8_t tag_g, uint8_t tag_b)
{
	ann->tag_r = tag_r;
	ann->tag_g = tag_g;
	ann->tag_b = tag_b;
}

void ANN_Init(ANN_TypeDef *ann)
{
	ann->_state = ANN_OFF;
	ann->_blink = false;
}

void ANN_SetState(ANN_TypeDef *ann, ANN_ColorTypeDef state)
{
	ann->_state = state;
}

ANN_ColorTypeDef ANN_GetState(ANN_TypeDef *ann)
{
	return ann->_state;
}

void ANN_SetRed(ANN_TypeDef *ann, uint8_t red)
{
	ann->_state.red = red;
}

void ANN_SetGreen(ANN_TypeDef *ann, uint8_t green)
{
	ann->_state.green = green;
}

void ANN_SetBlue(ANN_TypeDef *ann, uint8_t blue)
{
	ann->_state.blue = blue;
}

void ANN_Blink(ANN_TypeDef *ann, bool blink)
{
	ann->_blink = blink;
}

/* Private functions ---------------------------------------------------------*/

