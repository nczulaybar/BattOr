/*
 * BattOrProject1.c
 *
 * Created: 10/8/2015 8:14:33 PM
 * Author : nczulaybar
 */

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
#include "adc.h"

volatile uint32_t globalTime;
uint32_t lastTime;

int main(void)
{
	
	sei();
	PMIC.CTRL = PMIC.CTRL | 0b111;

	led_init();
	blink_init();	
	
	clock_switch_to_ext_crystal();
	uart_init();
	stdinout_init();
	digipot_init();
	adc_init();
	blink_set(LED_GREEN_bm, 200);
	blink_set(LED_YELLOW_bm, 200);
	
	setupAmplifier();
	
	setupAntiAliasingFilter();
	
	//Main Loop
	
	blink_set(LED_YELLOW_bm, 0);
	blink_set(LED_GREEN_bm, 200);	
	while (1) {	
		blinkAndSample();
    }
	//return 0;
	
	while(1){};
}
