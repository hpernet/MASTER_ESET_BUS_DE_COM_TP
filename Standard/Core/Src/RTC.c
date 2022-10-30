/*
 * RTC.c
 *
 *  Created on: Oct 6, 2022
 *      Author: hugop
 */
#include "RTC.h"

extern I2C_HandleTypeDef hi2c1;
uint8_t buffer = 0;
state_t state = STATE_IDLE;
date_s date;

void RTC_setup(void)
{
	HAL_I2C_Mem_Write(&hi2c1, WRITE_SALVE_ADDR, HOUR_COUNTER_ADDR, 1, 0x00, 1, 1000);
}

date_s RTC_get_date(void)
{
	date_s r_date;
	uint8_t readed_value;

	HAL_I2C_Mem_Read(&hi2c1, READ_SALVE_ADDR, SECOND_COUNTER_ADDR, 1, &readed_value, 1, 1000);
	r_date.second = (readed_value&0x0F) + 10*(readed_value>>4);

	HAL_I2C_Mem_Read(&hi2c1, READ_SALVE_ADDR, MINUTE_COUNTER_ADDR, 1, &readed_value, 1, 1000);
	r_date.minute = (readed_value&0x0F) + 10*(readed_value>>4);

	HAL_I2C_Mem_Read(&hi2c1, READ_SALVE_ADDR, HOUR_COUNTER_ADDR, 1, &readed_value, 1, 1000);
	r_date.hour = (readed_value&0x0F) + 10*(readed_value>>4);

	return r_date;
}

void RTC_start_date_request(void)
{
	state = STATE_REQ_SEC;
	HAL_I2C_Mem_Read_IT(&hi2c1, READ_SALVE_ADDR, SECOND_COUNTER_ADDR, 1, &buffer, 1);
}

void RTC_resume_date_request(void)
{
	switch (state)
	{
		case STATE_REQ_SEC :
			state = STATE_REQ_MIN;
			date.second = I2C1->DR; //(I2C1->DR&0x0F) + 10*(I2C1->DR>>4);
			HAL_I2C_Mem_Read_IT(&hi2c1, READ_SALVE_ADDR, MINUTE_COUNTER_ADDR, 1, &buffer, 1);
			break;
		case STATE_REQ_MIN :
			state = STATE_REQ_HOUR;
			date.minute = I2C1->DR; //(I2C1->DR&0x0F) + 10*(I2C1->DR>>4);
			HAL_I2C_Mem_Read_IT(&hi2c1, READ_SALVE_ADDR, HOUR_COUNTER_ADDR, 1, &buffer, 1);
			break;
		case STATE_REQ_HOUR :
			state = STATE_IDLE;
			date.hour = I2C1->DR; //(I2C1->DR&0x0F) + 10*(I2C1->DR>>4);

			break;
		case STATE_IDLE :
			break;
	}
}

