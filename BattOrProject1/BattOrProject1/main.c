/*
 * BattOrProject1.c
 *
 * Created: 10/8/2015 8:14:33 PM
 * Author : nczulaybar
 */

#include <avr/io.h>
#include <avr/interrupt.h> //Gives sei function that enables all interrupts
#include "gpio.h"
#include "led.h"
#include "timer.h"
#include "blink.h"
#include "clock.h"
#include "stdinout.h"
#include "uart.h"

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
	
    while (1)
    {
		printf("hullo");
		
		if(checkBlink >= 5) {
			blink_ms_timer_update();
			checkBlink = 0;
		}
    }
	//return 0;
}
