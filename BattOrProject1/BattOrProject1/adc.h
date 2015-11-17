#ifndef ADC_H
#define ADC_H

void adc_init();

volatile uint16_t current;
volatile uint16_t voltage;

inline void adc_start_sample(){

	ADCB_CH0_CTRL |= 0b10000000; //Starts scan
	ADCB_CH1_CTRL |= 0b10000000; //May not need this because scan is enabled
}

#endif