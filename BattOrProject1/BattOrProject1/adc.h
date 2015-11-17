#ifndef ADC_H
#define ADC_H

void adc_init();

volatile uint16_t current;
volatile uint16_t voltage;

inline void adc_start_sample(){
	ADCB.CTRLA |= 0b1100;
}

#endif