#ifndef USART_H_
#define USART_H_


void USART2_Init(void);
void USART2_Transmit(uint8_t i_byte);
uint8_t USART2_Receive(void);
#endif
