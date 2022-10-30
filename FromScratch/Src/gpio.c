#include <stdint.h>
#include <stm32f446xx.h>
#include "main.h"
#include "gpio.h"

void GPIO_Init(void){
	/* Clock Init */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	/* GPIO Init */
	GPIOA->MODER |= OUTPUT_MODE<<10;
}

void GPIOA_Set(void)
{

}

void GPIOA_Reset(void)
{

}

void GPIOA_Toggle(void)
{

}
