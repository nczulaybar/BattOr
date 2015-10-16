/*
 * BattOrProject1.c
 *
 * Created: 10/8/2015 8:14:33 PM
 * Author : nczulaybar
 */ 

#include <avr/io.h>
#include <avr/interrupt.h> //Gives sei function that enables all interrupts

volatile uint32_t globalTime;
uint32_t lastTime;
volatile uint8_t checkBlink;

#include "../../gpio.h"
#include "../../led.h"
#include "../../timer.h"
#include "../../blink.h"
#include "../../gpio.c"
#include "../../led.c"
#include "../../timer.c"
#include "../../blink.c"

int main(void)
{
	sei();
	PMIC.CTRL = PMIC.CTRL | 0b111;
	
	led_init();
	blink_init();
	blink_set(0, 100/2);
	blink_set(1, 250/2);
	blink_set(2, 500/2);

    while (1) 
    {
		if(checkBlink == 1) {
			blink_ms_timer_update();
			checkBlink = 0;
		}
		
    }
}

