/*
 * usart.h
 *
 *  Created on: Feb 9, 2023
 *      Author: Owner
 */

#ifndef USART_H_
#define USART_H_

#include "stm32f7xx.h"

void usart2_tx_init(void);
void usart2_write(int ch);

#endif /* USART_H_ */
