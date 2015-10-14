/*
 * BattOrProject1.c
 *
 * Created: 10/8/2015 8:14:33 PM
 * Author : nczulaybar
 */ 

#include <avr/io.h>
#include <avr/interrupt.h> //Gives sei function that enables all interrupts

volatile uint32_t globalTime;

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
	//SREG = SREG | 0b10000000;
	sei(); //Enables interrupts
	PMIC.CTRL = PMIC.CTRL | 0b111;
	
	led_init();
	//PORTC.DIR=0b111111;
	//PORTC.OUT=0b000000;
	
	//led_on(LED_RED_bm);
	//led_on(LED_GREEN_bm);
	//led_on(LED_YELLOW_bm);
	
	blink_init();
	
    while (1) 
    {
		blink_ms_timer_update();
    }
}

