/*
 * pt1.h
 *
 *  Created on: 02.09.2021
 *      Author: sebas
 */

#ifndef INC_UTIL_PT1_H_
#define INC_UTIL_PT1_H_

/* Includes ------------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

typedef struct
{
	float K;					//!< Amplification factor
	float coefficient;			//!< Coefficient (as calculated by init function
	float output_last_cycle;	//!< Last value at output
} PT1_TypeDef;

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void PT1_Init(PT1_TypeDef *filter, float K, float T, float sampling_time);
float PT1_Process(PT1_TypeDef *filter, float input);

/* Private functions ---------------------------------------------------------*/

#endif /* INC_UTIL_PT1_H_ */
