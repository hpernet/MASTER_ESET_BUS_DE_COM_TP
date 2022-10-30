/*
 * spi_driver.c
 *
 *  Created on: Oct 6, 2022
 *      Author: hugop
 */
#include "spi_driver.h"

extern SPI_HandleTypeDef hspi1;
uint8_t RX_Buffer = 0;
uint8_t TX_Buffer = 0;

void SPI_Initialization(void)
{

}

void SPI_Write_Byte(uint8_t i_addr, uint8_t i_byte)
{
	TX_Buffer = i_addr | (0x80);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, &TX_Buffer, SPI_BUFFER_SIZE, 1000);
	TX_Buffer = i_byte;
	HAL_SPI_Transmit(&hspi1, &TX_Buffer, SPI_BUFFER_SIZE, 1000);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
}


uint8_t SPI_Read_Byte(uint8_t i_addr)
{
	TX_Buffer = i_addr;

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, &TX_Buffer, SPI_BUFFER_SIZE, 1000);
	HAL_SPI_Receive(&hspi1, &RX_Buffer, SPI_BUFFER_SIZE, 1000);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);

	return RX_Buffer;
}



