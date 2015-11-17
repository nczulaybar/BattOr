#include <stdint.h>
#include <avr/io.h>
#include "timer.h"
#include "led.h"
#include "gpio.h"
#include "adc.h"
#include <avr/interrupt.h>

volatile uint32_t globalTime;
volatile uint8_t checkBlink;
uint32_t lastTime;
volatile uint8_t fivemscounter;
volatile uint8_t finishedPrinting;
volatile uint8_t timerFlag;


//Initialize the state of all of the LEDs in local state of the blink library to have their blinks disabled. Also, setup a timer that will fire an interrupt once every millisecond. Note that the timer is clocked off of the peripheral clock, and the peripheral clock is clocked off of the system clock.
void blink_init(){
	timer_init(&TCC0, 0b11); //high interrupt level
	timer_set(&TCC0, 0b1, 16000); //16000 ticks corresponds to 1ms, with the new clock
}

ISR(TCC0_OVF_vect){//Upper Half
	globalTime++;
	checkBlink ++;
	adc_start_sample();
	timerFlag = 0b1;
	// check to see if the lower half did not have time to complete printing the last sample. 
	while(finishedPrinting == 0){
		led_on(LED_RED_bm);
	}
	finishedPrinting = 0;
	
	// If so, the system should switch on the red light and go into an infinite loop of nothingness.
	
}

//Set the specified led to blink at the specified interval_ms.
void blink_set(uint8_t led, uint16_t interval_ms) {
	uint8_t i = 0;
	for (uint8_t pos = 0b1; pos < 0b1000; pos = pos << 1) {
		if(pos & led) LEDArray[i].blinkInterval = interval_ms;
		i++;
	}
}

//Update the state of the LEDs when a timer interrupt has occurred. This is the lower half handler for the timer interrupt, and should only be called if there was an unhandled timer interrupt that has occurred.
void blink_ms_timer_update(){
	for (uint8_t i = 0; i < 3; i++) {
		if (LEDArray[i].blinkInterval != 0) {
			if (lastTime < globalTime) {
				LEDArray[i].counter += (globalTime - lastTime); 
				}
			if (LEDArray[i].counter >= LEDArray[i].blinkInterval) {
				LEDArray[i].counter = LEDArray[i].counter-LEDArray[i].blinkInterval;
				led_toggle(0b1 << (i));
			}
		}
	}
	lastTime = globalTime;
}