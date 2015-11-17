#include <avr/io.h>
#include "led.h"

void adc_init(){
	//Set to 12 bit resolution
	ADCB.CTRLB &= 0b000;
	
	//Select the external reference voltage connected to PORTA. 
	ADCB.REFCTRL |= 0b0100000;
	
	//Divide down the ADC’s clock rate so it is below the 2 MHz maximum clock rate of the ADC.
	ADCB.PRESCALER = 0b1; //Division by 8 to go from 16MHz to 2MHz
	
	//Set to signed mode, enabling differential input
	ADCB.CTRLB |= 0b10000;

	//Configure voltage and current ADC channel.
	ADCB_CH0_CTRL = 0b10; //Sets to differential, no gain
	ADCB_CH0_MUXCTRL |= 0b1000; //Pin 1 is current
	ADCB_CH0_MUXCTRL |= 0b101; // Pad ground
	
	ADCB_CH1_CTRL = 0b10; //Sets to differential, no gain
	ADCB_CH1_MUXCTRL |= 0b10000; //Pin 2 is voltage
	ADCB_CH1_MUXCTRL |= 0b101; //Pad ground
	
	ADCB.CTRLA |= 0b1; //Enable ADC
};