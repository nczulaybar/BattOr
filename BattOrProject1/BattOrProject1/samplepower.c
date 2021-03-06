#include <avr/io.h>
#include <stdlib.h>
#include "led.h"
#include "blink.h"
#include "adc.h"
#include "digipot.h"

#include <avr/io.h>
#include <avr/interrupt.h> //Gives sei function that enables all interrupts
#include <stdlib.h>
#include "gpio.h"
#include "led.h"
#include "timer.h"
#include "blink.h"
#include "clock.h"
#include "stdinout.h"
#include "uart.h"
#include "digipot.h"
#include "spi.h"
#include "adc.h"
#include "samplepower.h"

volatile uint8_t checkBlink;
volatile uint8_t finishedPrinting;
volatile uint8_t timerFlag;
uint16_t numSamples;

void setupAmplifier(){
	printf("Enter your desired amplifier gain:\n");
	char* responseString;
	gets(responseString);
	long desiredGain = strtol(responseString, NULL, 10);
	long desiredResistance = 100000/(desiredGain - 1);
	printf("\t You requested %ld ohms.\n",desiredResistance);
	uint16_t toSend = ((desiredResistance*1024)/100000)-1;
	pot_wiperpos_set(DIGIPOT_AMP_CS_PIN_gm, toSend);
	uint16_t actualValue = pot_wiperpos_get(DIGIPOT_AMP_CS_PIN_gm);
	printf("\t The best I can give is %ld.\n", (((uint32_t)actualValue)*100000/1024)+100);
	
}

void setupAntiAliasingFilter(){
		// Pt. 3Set the digipot for the anti-aliasing filter for 500 Hz. Note, the capacitance of this RC filter is 10000pF.
		// This digipot is FILPOT
		//Omegacutoff = 1/RC = 500*2pi; 
		//C = 10nF -> R = 200;
		long desiredResistance = 32000;
		uint16_t toSend = ((desiredResistance*1024)/100000)-1;
		pot_wiperpos_set(DIGIPOT_FIL_CS_PIN_gm, toSend);
}

void calibrate(){

	//For current, set Muxctrl mode to ouput, then set output to 0
	gpio_set_mode(&PORTD, 0b0, 1);
	gpio_set_out(&PORTD, 0b0, 0);

	//Set voltage input to Pin7 GND
	ADCB_CH1_MUXCTRL |= 0b111000; //Set voltage input to gnd

	printf("===BEGIN CALIBRATION===");
	while(numSamples < 1000){
		blinkAndSample();
	}
	printf("===END CALIBRATION===");
	
	//For current, set muxctrl input high
	gpio_set_out(&PORTD, 0b0, 1);
	//Return voltage back to where it was before
	ADCB_CH1_MUXCTRL = (ADCB_CH1_MUXCTRL & 0b111) | 0b10000; //Pin 2 is voltage
}

void blinkAndSample(){
	if(timerFlag == 0b1){
		if(checkBlink >= 5) {
			blink_ms_timer_update();
			checkBlink = 0;
		}
		timerFlag = 0b0;
	}
	while(ADCB.INTFLAGS != 0b11); // do nothing while still sampling
	ADCB.INTFLAGS = 0b11; //Clear by writing 1 to location
	//Print raw samples over usartRINT
	current = ADCB_CH0_RES;
	voltage = ADCB_CH1_RES;
	printf("%d %d \n",current, voltage);
	finishedPrinting = 0b1;
	numSamples++;
}