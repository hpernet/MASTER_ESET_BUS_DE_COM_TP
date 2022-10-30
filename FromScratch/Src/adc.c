#include <stdint.h>
#include <stm32f446xx.h>
#include "main.h"
#include "adc.h"

/* Default : One shot regular conversion of IN0 (PA0), right justified */

void ADC_Init(void){
	/* ADC Init */
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	GPIOA->MODER |= ANALOG_MODE << 0;
	ADC1->CR2 |= ADC_CR2_ADON;
	ADC1->SMPR2 = 0xFFFF;
	ADC1->SMPR1 = 0xFFFF;
}

void ADC_Conv(void){

}

