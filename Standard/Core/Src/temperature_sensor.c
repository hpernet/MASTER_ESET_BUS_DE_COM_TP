/*
 * temperature_sensor.c
 *
 *  Created on: Oct 6, 2022
 *      Author: hugop
 */
#include "temperature_sensor.h"

extern TIM_HandleTypeDef htim6;
ONE_WIRE_Config OW_config;


void temp_sensor_setup(void)
{
	OW_config.pin = GPIO_PIN_6;
	OW_config.port = GPIOA;
	__HAL_TIM_ENABLE(&htim6);
	HAL_Delay(1000U);
}

void temp_sensor_run(void)
{
	uint8_t is_reset = 0;
	uint8_t data[8];
	uint8_t iBcl;
	int8_t  temp = 0;

	  if (ONE_WIRE_Reset(&OW_config))
	  {
//		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
		ONE_WIRE_Write_Byte(&OW_config, 0xCC);
		HAL_Delay(1);
		ONE_WIRE_Write_Byte(&OW_config, 0x44);
		HAL_Delay(10);

		if (ONE_WIRE_Reset(&OW_config))
		{
			ONE_WIRE_Write_Byte(&OW_config, 0xCC);
			ONE_WIRE_Write_Byte(&OW_config, 0xBE);
			temp = (ONE_WIRE_Read_Byte(&OW_config) >> 1);
		}
	  }
}
