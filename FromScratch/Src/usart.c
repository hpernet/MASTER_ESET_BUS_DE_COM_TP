#include <stdint.h>
#include <stm32f446xx.h>
#include "main.h"
#include "usart.h"


void USART2_Init(void)
{
	/* USART2 Init */
	GPIOA->MODER |= ALT_MODE<<4;
	GPIOA->MODER |= ALT_MODE<<6;
	GPIOA->AFR[0] |= 7<<8;
	GPIOA->AFR[0] |= 7<<12;
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	USART2->BRR  = 139;
	USART2->CR1 |= USART_CR1_TE | USART_CR1_RE;
	USART2->CR1 |= USART_CR1_UE;
}


void USART2_Transmit(uint8_t i_byte)
{
	while(0 == ((USART2->SR) & (1<<7)));
	USART2->DR = i_byte;
	while(0 == ((USART2->SR) & (1<<6)));
}


uint8_t USART2_Receive(void)
{
	uint8_t r_byte = 0;

	while(((USART2->SR) & (1<<5)) == 0);
	r_byte = USART2->DR;

	return r_byte;
}
