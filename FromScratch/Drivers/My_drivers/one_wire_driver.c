/*
 * one_wire_driver.cpp
 *
 *  Created on: 29 sept. 2022
 *      Author: hugop
 */

#include "one_wire_driver.h"

extern TIM_HandleTypeDef htim6;

uint8_t delay_us(uint16_t i_delay)
{
	uint16_t t = 0;

	// Reset timer value
	__HAL_TIM_SetCounter(&htim6, 0U);

	// Wait until delay is passed
	do
	{
		t = __HAL_TIM_GetCounter(&htim6);
	}
	while(t <= i_delay);
}

uint8_t ONE_WIRE_Reset(ONE_WIRE_Config* config)
{
	// Variable declaration
	uint8_t r_is_reset_happen = 0U;

	// Pull the bus down
	CLEAR_BIT(config->port->ODR, config->pin);

	// Wait for 480us
	delay_us(480);

	// Release the bus
	SET_BIT(config->port->ODR, config->pin);

	// Wait for 70us
	delay_us(70);

	if (0U != READ_BIT(config->port->IDR, config->pin))
	{
		r_is_reset_happen = 0;
	}
	else
	{
		r_is_reset_happen = 1;
	}

	// Wait for 410us
	delay_us(410U);

	// Return the
	return r_is_reset_happen;
}

void ONE_WIRE_Write_Bit0(ONE_WIRE_Config* config)
{
	// Pull the bus down
	CLEAR_BIT(config->port->ODR, config->pin);

	// Wait for 480us
	delay_us(60);

	// Release the bus
	SET_BIT(config->port->ODR, config->pin);

	// Wait for 480us
	delay_us(10);
}

void ONE_WIRE_Write_Bit1(ONE_WIRE_Config* config)
{
	// Pull the bus down
	CLEAR_BIT(config->port->ODR, config->pin);

	// Wait for 480us
	delay_us(6);

	// Release the bus
	SET_BIT(config->port->ODR, config->pin);

	// Wait for 480us
	delay_us(64);
}

uint8_t ONE_WIRE_Read_Bit(ONE_WIRE_Config* config)
{
	// Variable declaration
	uint8_t r_bit_val;

	// Pull the bus down
	CLEAR_BIT(config->port->ODR, config->pin);

	// Wait for 480us
	delay_us(6);

	// Release the bus
	SET_BIT(config->port->ODR, config->pin);

	// Wait for 480us
	delay_us(9);

	if (0U != READ_BIT(config->port->IDR, config->pin))
	{
		r_bit_val = 1;
	}
	else
	{
		r_bit_val = 0;
	}

	// Wait for 480us
	delay_us(55);

	// return bit value
	return r_bit_val;
}

void ONE_WIRE_Write_Byte(ONE_WIRE_Config* config, uint8_t i_byte)
{
		// Variable declaration
	uint8_t iBcl;

	for (iBcl=0; iBcl < 8; iBcl++)
	{
		if(1 == (0x01 & (i_byte>>iBcl)))
		{
			ONE_WIRE_Write_Bit1(config);
		}
		else
		{
			ONE_WIRE_Write_Bit0(config);
		}
	}

}

uint8_t ONE_WIRE_Read_Byte(ONE_WIRE_Config* config)
{
	// Variable declaration
	uint8_t r_byte;
	uint8_t iBcl;

	for (iBcl = 0; iBcl<8; iBcl++)
	{
		r_byte = r_byte | (ONE_WIRE_Read_Bit(config) << iBcl);
	}

	return r_byte;
}

