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
#include "samplepower.h"

volatile uint8_t checkBlink;
volatile uint8_t finishedPrinting;
volatile uint8_t timerFlag;
uint16_t numSamples;

void setupAmplifier(){
	//pot_wiperpos_set(DIGIPOT_AMP_CS_PIN_gm, 1023);
	//Part 2, inputting desired gain
	printf("Enter your desired amplifier gain:\n");
	//pot_wiperpos_get(DIGIPOT_AMP_CS_PIN_gm);
	//printf("Enter your desired resistance in Ohms... \n");
	char* responseString;
	gets(responseString);
	long desiredGain = strtol(responseString, NULL, 10);
	long desiredResistance = 100000/(desiredGain - 1);
	//long desiredResistance = strtol(responseString, NULL, 10);
	printf("\t You requested %ld ohms.\n",desiredResistance);
	uint16_t toSend = ((desiredResistance*1024)/100000)-1;
	pot_wiperpos_set(DIGIPOT_AMP_CS_PIN_gm, toSend);
	uint16_t actualValue = pot_wiperpos_get(DIGIPOT_AMP_CS_PIN_gm);
	printf("\t The best I can give is %ld.\n", (((uint32_t)actualValue)*100000/1024)+100);
}

void setupAntiAliasingFilter(){
		// Pt. 3Set the digipot for the anti-aliasing filter for 500 Hz. Note, the capacitance of this RC filter is 10000pF.
		// This digipot is FILPOT, another digipot soldered onto your board in this project.
		//Omegacutoff = 1/RC = 500Hz; RC = 1/500
		//C = 10uF -> R = 200;
		long desiredResistance = 200;
		uint16_t toSend = ((desiredResistance*1024)/100000)-1;
		pot_wiperpos_set(DIGIPOT_AMP_CS_PIN_gm, toSend);
}

void calibrate(){
	//Set voltage and current inputs to gnd
	
	printf("===BEGIN CALIBRATION===");
	while(numSamples < 1000){
		blinkAndSample();
	}
	printf("===END CALIBRATION===");
	
	//Set back voltage and current inputs
}

void blinkAndSample(){
	if(timerFlag == 1){
		if(checkBlink >= 5) {
			blink_ms_timer_update();
			checkBlink = 0;
		}
		while(ADCB.INTFLAGS != 0b11); // do nothing while still sampling
		//Print raw samples over usartRINT
		current = ADCB_CH0_RES;
		voltage = ADCB_CH1_RES;
		printf("text %ld %ld \n",current, voltage);
		//printf(" ");
		//printf(voltage);
		//printf("\n");
		finishedPrinting = 0b1;
		numSamples++;
	}
}