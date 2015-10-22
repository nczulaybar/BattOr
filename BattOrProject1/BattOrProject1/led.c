#include <stdint.h>
#include "gpio.h"
#include "led.h"

struct LED LEDArray[] = {
	{
		.blinkInterval = 0,
		.counter = 0
		},{
		.blinkInterval = 0,
		.counter = 0
		},{
		.blinkInterval = 0,
		.counter = 0
	}
};

//Setup all of the LEDs so they are in output mode and off.
void led_init(){
	gpio_set_mode(&PORTC, LED_GREEN_bm, 1);
	gpio_set_mode(&PORTC, LED_YELLOW_bm, 1);
	gpio_set_mode(&PORTC, LED_RED_bm, 1);
	led_off(LED_GREEN_bm);
	led_off(LED_YELLOW_bm);
	led_off(LED_RED_bm);
}

//Turn on the specified led.
void led_on(uint8_t led){
	gpio_set_out(&PORTC, led, 0);	
}

//Turn off the specified led.
void led_off(uint8_t led){
	gpio_set_out(&PORTC, led, 1);
}

//Toggle the specified led on and off.
void led_toggle(uint8_t led){
	gpio_toggle_out(&PORTC, led);
}
