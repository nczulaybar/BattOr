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

volatile uint32_t globalTime;

volatile uint8_t checkBlink;
uint32_t lastTime;

int main(void)
{
	sei();
	PMIC.CTRL = PMIC.CTRL | 0b111;
	
	
	led_init();
	blink_init();
	
	blink_set(LED_GREEN_bm, 100);
	blink_set(LED_YELLOW_bm, 250);
	blink_set(LED_RED_bm, 500);
	
	clock_switch_to_ext_crystal();
	
	uart_init();
	stdinout_init();
	digipot_init();
	pot_wiperpos_set(DIGIPOT_AMP_CS_PIN_gm, 1023);
	
	while (1)
    {
		
		//pot_wiperpos_get(DIGIPOT_AMP_CS_PIN_gm);
		printf("Enter your desired resistance in Ohms... \n");
		char* responseString;
		gets(responseString);
		long desiredResistance = strtol(responseString, NULL, 10);
		printf("\t You requested %ld ohms.\n",desiredResistance);
		uint16_t toSend = ((desiredResistance*1024)/100000)-1;
		printf("\t The best I can give is %ld. But at least you're not a processor reduced to a paltry resistor. \n", (97656 * (toSend+1) / 1000));
		pot_wiperpos_set(DIGIPOT_AMP_CS_PIN_gm, toSend);
		
		
		if(checkBlink >= 5) {
			blink_ms_timer_update();
			checkBlink = 0;
		}
    }
	//return 0;
}
