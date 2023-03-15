#ifndef TIM_H_
#define TIM_H_

#define SR_UIF 	 (1U<<0)
#define SR_CC3IF (1U<<3)

void tim2_1hz_init(void);
void tim2_input_capture_ch3(void);
void tim2_output_compare_ch2(void);

#endif /* TIM_H_ */
