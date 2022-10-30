#ifndef SPI_H_
#define SPI_H_

void SPI2_Init(void);
void SPI2_Transmit(uint8_t i_byte);
uint8_t SPI2_Receive(void);

#endif /* SPI_H_ */
