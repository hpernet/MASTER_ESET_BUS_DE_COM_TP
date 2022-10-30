/*
 * LoRa_Tr.c
 *
 *  Created on: Oct 6, 2022
 *      Author: hugop
 */
#include "LoRa_Tr.h"

	uint8_t ival = 0;

	extern SPI_HandleTypeDef hspi1;

	void LoRa_Tr_setup(void)
	{
		  SPI_Write_Byte(0x01, 0x80);
		  SPI_Write_Byte(0x35, 0x01);
	}

	void LoRa_Tr_run(void)
	{
		  SPI_Write_Byte(0x00, 0xAA);
	}
