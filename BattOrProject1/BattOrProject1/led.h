#ifndef LED_H
#define LED_H

#define LED_RED_bm (1<<2)
#define LED_YELLOW_bm (1<<1)
#define LED_GREEN_bm (1<<0)

struct LED {
	uint16_t blinkInterval;
	uint16_t counter;
	};

extern struct LED LEDArray[3];

void led_init();
//Setup all of the LEDs so they are in output mode and off.

void led_on(uint8_t led);
//Turn on the specified led.

void led_off(uint8_t led);
//Turn off the specified led.

void led_toggle(uint8_t led);
//Toggle the specified led on and off.
#endif