/*
 * spi_driver.h
 *
 *  Created on: Oct 6, 2022
 *      Author: hugop
 */

#ifndef MY_DRIVERS_SPI_DRIVER_H_
#define MY_DRIVERS_SPI_DRIVER_H_

#include "main.h"

#define SPI_BUFFER_SIZE     sizeof(uint8_t)

void SPI_Initialization(void);

void SPI_Write_Byte(uint8_t i_addr, uint8_t i_byte);

uint8_t SPI_Read_Byte(uint8_t i_addr);


#endif /* MY_DRIVERS_SPI_DRIVER_H_ */
