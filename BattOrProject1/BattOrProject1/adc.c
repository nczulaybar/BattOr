#include <avr/io.h>

void adc_init(){
	//Set the ADC to have a a bit depth of the ADC to 12-bits
	
	//Select the external reference voltage connected to PORTA. 
	ADCB.REFCTRL |= 0b0100000;
	
	//Set to signed mode, enabling differential input
	ADCB.CTRLB |= 0b10000;
	//Set to 12 bit resolution
	ADCB.CTRLB &= 0b000;
	
	//Divide down the ADC’s clock rate so it is below the 2 MHz maximum clock rate of the ADC.
	ADCB.PRESCALER = 0b1; //Division by 8 to go from 16MHz to 2MHz
	
	//Set channels 0 and 1 on sweep
	//ADCB.EVCTRL |= 0b01000000;
	//May not need this, since this is event-triggered
	
	//Configure voltage and current ADC channel.
	ADCB_CH0_CTRL = 0b01; //Sets to differential, no gain
	ADCB_CH0_MUXCTRL |= 0b10000; //Pin 1 is current
	ADCB_CH0_MUXCTRL |= 0b101; // Pad ground
	
	ADCB_CH1_CTRL = 0b10; //Sets to differential, no gain
	ADCB_CH1_MUXCTRL |= 0b10000; //Pin 2 is voltage
	ADCB_CH1_MUXCTRL |= 0b101; //Pad ground

	//Set scan to include channels 0 and 1
	ADCB_CH0_SCAN |= 0b1; //Set count to 1
	
	//Idk what to do about 
	//"Don’t forget to wait until the end of the scan." ??
	
	ADCB.CTRLA |= 0b1; //Enable ADC
};