#include "stdio.h"
#include "stdint.h"

#include "adc.h"
#include "usart.h"

int main(void)
{
	usart2_rx_tx_init();
	pa1_adc1_init();

	uint16_t sensorValue;
	while (1) {
		start_conversion();
		sensorValue = adc_read_value();

		printf("Current measurement value is %d", (int)sensorValue);
	}
}
