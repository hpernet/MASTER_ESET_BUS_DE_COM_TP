/*
 * one_wire_driver.h
 *
 *  Created on: 29 sept. 2022
 *      Author: hugop
 */

#ifndef MY_DRIVERS_ONE_WIRE_DRIVER_H_
#define MY_DRIVERS_ONE_WIRE_DRIVER_H_

#include "main.h"

typedef struct
{
	GPIO_TypeDef* port;
	uint16_t      pin;
} ONE_WIRE_Config;


uint8_t ONE_WIRE_Reset(ONE_WIRE_Config* config);

void ONE_WIRE_Write_Bit0(ONE_WIRE_Config* config);

void ONE_WIRE_Write_Bit1(ONE_WIRE_Config* config);

uint8_t ONE_WIRE_Read_Bit(ONE_WIRE_Config* config);

void ONE_WIRE_Write_Byte(ONE_WIRE_Config* config, uint8_t i_byte);

uint8_t ONE_WIRE_Read_Byte(ONE_WIRE_Config* config);

#endif /* MY_DRIVERS_ONE_WIRE_DRIVER_H_ */
