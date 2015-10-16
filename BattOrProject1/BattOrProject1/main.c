/*
 * BattOrProject1.c
 *
 * Created: 10/8/2015 8:14:33 PM
 * Author : nczulaybar
 */ 

#include <avr/io.h>
#include <avr/interrupt.h> //Gives sei function that enables all interrupts

volatile uint32_t globalTime;
uint32_t lastTime, ledCounter1, ledCounter2, ledCounter3, blinkInt1, blinkInt2, blinkInt3;

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
	blink_set(0, 100);
	blink_set(1, 250);
	blink_set(2, 500);

    while (1) 
    {
		blink_ms_timer_update();
    }
}

