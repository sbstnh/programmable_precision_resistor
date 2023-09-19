/**
 * @file    rot_encoder.h
 * @author  sebas
 * @date    24.12.2022
 * @brief
 */
#ifndef INC_HARDWARE_ENCODER_H_
#define INC_HARDWARE_ENCODER_H_

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>
#include "util/api.h"
#include "hardware/ui_interface.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

typedef struct enc
{
	bool valid;
	int16_t last;

	bool (*gate)(struct enc *);
} ENC_TypeDef;

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void ENC_Init(ENC_TypeDef *encoder);
void ENC_Process(ENC_TypeDef *encoder, int32_t received_count);

bool ENC_Peek_Count(int16_t *count);
bool ENC_Get_Count(int16_t *count);
void ENC_SkipAll_Counts();

/* Private functions ---------------------------------------------------------*/


#endif /* INC_HARDWARE_ENCODER_H_ */
