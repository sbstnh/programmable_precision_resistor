/**
 * @file    scpi_eeprom_def.h
 * @author  sebas
 * @date    11.11.2021
 * @brief
 */

#ifndef INC_COMMUNICATION_SCPI_EEPROM_DEF_H_
#define INC_COMMUNICATION_SCPI_EEPROM_DEF_H_


/* Includes ------------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

scpi_result_t SCPI_CMD_MEM_FORMat(scpi_t *context);

scpi_result_t SCPI_CMD_MEM_DATA_VLENgth(scpi_t *context);
scpi_result_t SCPI_CMD_MEM_DATA_VLENgth_Q(scpi_t *context);

scpi_result_t SCPI_CMD_MEM_DATA_BLOCk_Q(scpi_t *context);

scpi_result_t SCPI_CMD_MEM_PROT_STATe(scpi_t *context);
scpi_result_t SCPI_CMD_MEM_PROT_STATe_Q(scpi_t *context);

/* Private functions ---------------------------------------------------------*/


#endif /* INC_COMMUNICATION_SCPI_EEPROM_DEF_H_ */
