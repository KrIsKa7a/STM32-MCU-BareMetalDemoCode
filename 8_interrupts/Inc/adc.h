#ifndef ADC_H_
#define ADC_H_

#define ADC_EOC		(1U<<1)

void pa1_adc1_init();
void start_conversion();
uint16_t adc_read_value();

#endif /* ADC_H_ */
