/*
 * persistence.h
 *
 *  Created on: 21.10.2022
 *      Author: sebas
 */

#ifndef INC_APPLICATION_PERSISTENCE_H_
#define INC_APPLICATION_PERSISTENCE_H_

#include "persistence/persistent_data.h"
#include "calibration/cal_data.h"
#include "hardware/eeprom.h"

#define FIXEDDATA_START			0

#define CALDATA_REL_START		0
#define INSTDATA_REL_START		(CALDATA_REL_START + CALDATA_MAX_BLOCK_SIZE)
#define USERDATA_REL_START		(INSTDATA_REL_START + INSTDATA_MAX_BLOCK_SIZE)

#define USERDATA_NUMBER_BLOCKS	10

typedef struct __attribute__((packed))
{
	CALDATA_TypeDef cal_data;
	INSTDATA_TypeDef inst_data;
	USERDATA_TypeDef user_data;

	EEPR_TypeDef *eeprom;
} PER_TypeDef;

void PER_CopyToCalibration(PER_TypeDef *pers, volatile CALDATA_TypeDef *cal_data);
void PER_CopyFromCalibration(PER_TypeDef *pers, volatile CALDATA_TypeDef *cal_data);
void PER_CopyAppToInstData(PER_TypeDef *per, volatile APP_ParamTypeDef *app);
void PER_CopyInstToAppData(PER_TypeDef *per, volatile APP_ParamTypeDef *app);
void PER_CopyAppToUserData(PER_TypeDef *per, volatile APP_ParamTypeDef *app);
void PER_CopyUserDataToApp(PER_TypeDef *per, volatile APP_ParamTypeDef *app);

API_StatusTypeDef PER_ReadPartData(PER_TypeDef *pers);
API_StatusTypeDef PER_ReadCalData(PER_TypeDef *pers);
API_StatusTypeDef PER_ReadInstData(PER_TypeDef *per);
API_StatusTypeDef PER_ReadUserData(PER_TypeDef *pers, uint8_t index);

API_StatusTypeDef PER_WriteAll(PER_TypeDef *per);
API_StatusTypeDef PER_WriteCalData(PER_TypeDef *pers);
API_StatusTypeDef PER_WriteInstData(PER_TypeDef *per);
API_StatusTypeDef PER_WriteUserData(PER_TypeDef *pers, uint8_t index);


#endif /* INC_APPLICATION_PERSISTENCE_H_ */
