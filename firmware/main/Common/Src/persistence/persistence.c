/*
 * persistence.c
 *
 *  Created on: 21.10.2022
 *      Author: sebas
 */

#include <string.h>
#include "persistence/persistence.h"
#include "util/crc.h"

#define ADDR_OFFSET(x, y)							( ((void *)&(x)) - ((void *)&(y)) )

#define _PER_INDEX_GUARD() 							if (index >= USERDATA_NUMBER_BLOCKS) \
														return API_ERROR;

#define _PER_EEPROM_READ(address, pdata, size)		if (EEPR_Read(per->eeprom, (address), (pdata), (size)) != API_OK) \
														return API_ERROR;

#define _PER_CRC_CHECK(block, size)					if (CRC_Calculate((block).AS_BYTE, (size)) != (block).CRC_CHECKSUM) \
														return API_INVALID_OPERATION;

//#define _PER_CRC_CHECK(block, block_size)			if (CRC_Calculate((block), SIZE_WO_CRC(block_size)) != *((uint32_t *) ((block) + SIZE_WO_CRC(block_size))) )


#define _PER_CRC_SET(block, size)					(block).CRC_CHECKSUM = CRC_Calculate((block).AS_BYTE, (size));

//#define _PER_CRC_SET(block, block_size)				*((uint32_t *) ((block) + SIZE_WO_CRC(block_size))) = CRC_Calculate((block), SIZE_WO_CRC(block_size));

#define _PER_EEPROM_WRITE(address, pdata, size)		if (EEPR_Write(per->eeprom, (address), (pdata), (size)) != API_OK) \
														return API_ERROR;

API_StatusTypeDef PER_ReadCalData(PER_TypeDef *per)
{
	_PER_EEPROM_READ(FIXEDDATA_START + CALDATA_REL_START, per->cal_data.AS_BYTE, CALDATA_BLOCK_SIZE);
	_PER_CRC_CHECK(per->cal_data, SIZE_WO_CRC(CALDATA_BLOCK_SIZE));

	return API_OK;
}


API_StatusTypeDef PER_ReadInstData(PER_TypeDef *per)
{
	_PER_EEPROM_READ(FIXEDDATA_START + INSTDATA_REL_START, per->inst_data.AS_BYTE, INSTDATA_BLOCK_SIZE);
	_PER_CRC_CHECK(per->inst_data, SIZE_WO_CRC(INSTDATA_BLOCK_SIZE));

	return API_OK;
}


API_StatusTypeDef PER_ReadUserData(PER_TypeDef *per, uint8_t index)
{
	_PER_INDEX_GUARD();
	_PER_EEPROM_READ(FIXEDDATA_START + USERDATA_REL_START + sizeof(USERDATA_TypeDef) * index,
			per->user_data.AS_BYTE,
			USERDATA_BLOCK_SIZE);
	_PER_CRC_CHECK(per->user_data, SIZE_WO_CRC(USERDATA_BLOCK_SIZE));

	return API_OK;
}


API_StatusTypeDef PER_WriteCalData(PER_TypeDef *per)
{
	_PER_EEPROM_READ(FIXEDDATA_START + CALDATA_REL_START,
							 (uint8_t *)&per->cal_data.CAL_CNT,
							 sizeof(per->cal_data.CAL_CNT));

	per->cal_data.CAL_CNT++;

	_PER_CRC_SET(per->cal_data, SIZE_WO_CRC(CALDATA_BLOCK_SIZE));

	EEPR_EnableWrite(per->eeprom);
	_PER_EEPROM_WRITE(FIXEDDATA_START + CALDATA_REL_START,
							  (uint8_t *)&per->cal_data,
							  CALDATA_BLOCK_SIZE);
	EEPR_DisableWrite(per->eeprom);

	return API_OK;
}


API_StatusTypeDef PER_WriteInstData(PER_TypeDef *per)
{
	_PER_CRC_SET(per->inst_data, SIZE_WO_CRC(INSTDATA_BLOCK_SIZE));

	EEPR_EnableWrite(per->eeprom);
	_PER_EEPROM_WRITE(FIXEDDATA_START + INSTDATA_REL_START, (uint8_t *)&per->inst_data, INSTDATA_BLOCK_SIZE);
	EEPR_DisableWrite(per->eeprom);

	return API_OK;
}


API_StatusTypeDef PER_WriteUserData(PER_TypeDef *per, uint8_t index)
{
	_PER_INDEX_GUARD();

	_PER_CRC_SET(per->user_data, SIZE_WO_CRC(USERDATA_BLOCK_SIZE));

	EEPR_EnableWrite(per->eeprom);
	_PER_EEPROM_WRITE(FIXEDDATA_START + USERDATA_REL_START + sizeof(USERDATA_TypeDef) * index,
							  (uint8_t *)&per->user_data,
							  USERDATA_BLOCK_SIZE);
	EEPR_DisableWrite(per->eeprom);

	return API_OK;
}


void PER_CopyToCalibration(PER_TypeDef *pers, volatile CALDATA_TypeDef *cal_data)
{
	memcpy((CALDATA_TypeDef *)cal_data->AS_BYTE, pers->cal_data.AS_BYTE, sizeof(CALDATA_TypeDef));
}


void PER_CopyFromCalibration(PER_TypeDef *pers, volatile CALDATA_TypeDef *cal_data)
{
	memcpy(pers->cal_data.AS_BYTE, (CALDATA_TypeDef *)cal_data->AS_BYTE, sizeof(CALDATA_TypeDef));
}


void PER_CopyAppToInstData(PER_TypeDef *per, volatile APP_ParamTypeDef *app)
{
	INSTDATA_TypeDef *instdata = &per->inst_data;

	instdata->INP_INH_MODE = app->INPut.INHibit.MODE;

	instdata->SOUR_DIG_PIN_FUNCtion[SOUR_DIG_PIN1] = app->SOURce.DIGital.PIN[SOUR_DIG_PIN1].FUNCtion;
	instdata->SOUR_DIG_PIN_FUNCtion[SOUR_DIG_PIN2] = app->SOURce.DIGital.PIN[SOUR_DIG_PIN2].FUNCtion;
	instdata->SOUR_DIG_PIN_POLarity[SOUR_DIG_PIN1] = app->SOURce.DIGital.PIN[SOUR_DIG_PIN1].POLarity;
	instdata->SOUR_DIG_PIN_POLarity[SOUR_DIG_PIN2] = app->SOURce.DIGital.PIN[SOUR_DIG_PIN2].POLarity;

	instdata->SYST_BEEP_STATe = app->SYSTem.BEEPer.STATe;
}


void PER_CopyAppToUserData(PER_TypeDef *per, volatile APP_ParamTypeDef *app)
{
	USERDATA_TypeDef *setdata = &per->user_data;
	setdata->DISP_PRIM_RESolution = app->DISPlay.MAIN.PRIMary.RESolution;
	setdata->DISP_SEC_MODE = app->DISPlay.MAIN.SECondary.MODE;

	setdata->INP_STATe = app->INPut.STATe;

	setdata->SOUR_MODE = app->SOURce.MODE;
	setdata->SOUR_RES_LEV_IMM_AMPlitude = app->SOURce.RESistance.LEVel.IMMediate.AMPLitude.value;
	setdata->SOUR_RES_LEV_TRIG_AMPlitude = app->SOURce.RESistance.LEVel.TRIGgered.AMPLitude.value;
	setdata->SOUR_RES_LEV_STEP_INCRement = app->SOURce.RESistance.LEVel.STEP.INCRement.value;
	setdata->SOUR_RES_LEV_STEP_MODE = app->SOURce.RESistance.LEVel.STEP.MODE;
	setdata->SOUR_RES_LEV_STEP_OVERflow = app->SOURce.RESistance.LEVel.STEP.OVERflow;
	setdata->SOUR_RES_LIM_LOWer = app->SOURce.RESistance.LIMit.LOWer.value;
	setdata->SOUR_RES_LIM_STATe = app->SOURce.RESistance.LIMit.STATe;
	setdata->SOUR_RES_LIM_UPPer = app->SOURce.RESistance.LIMit.UPPer.value;
	setdata->SOUR_RES_MODE = app->SOURce.RESistance.MODE;
	setdata->SOUR_SWITching = app->SOURce.SWITching;

	setdata->TRIG_SEQ_DELay = app->TRIGger.SEQuence.DELay.value;
	setdata->TRIG_SEQ_HOLDoff = app->TRIGger.SEQuence.HOLDoff.value;
	setdata->TRIG_SEQ_SLOPe = app->TRIGger.SEQuence.SLOPe;
	setdata->TRIG_SEQ_SOURce = app->TRIGger.SEQuence.SOURce;
	setdata->TRIG_SEQ_TIMer = app->TRIGger.SEQuence.TIMer.value;
}
