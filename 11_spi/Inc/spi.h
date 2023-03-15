#ifndef SPI_H_
#define SPI_H_

#include "stdint.h"

void spi1_config(void);
void spi1_transmit(uint8_t* data, uint32_t bytesCnt);
void spi1_receive(uint8_t* data, uint32_t bytesCnt);
void cs_enable(uint8_t pinNumber);
void cs_disable(uint8_t pinNumber);

#endif /* SPI_H_ */
