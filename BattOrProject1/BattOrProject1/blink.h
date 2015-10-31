#ifndef BLINK_H
#define BLINK_H

//void stdinout_init1();
void blink_init();

//Initialize the state of all of the LEDs in local state of the blink library to have their blinks disabled. Also, setup a timer that will fire an interrupt once every millisecond. Note that the timer is clocked off of the peripheral clock, and the peripheral clock is clocked off of the system clock.

//ISR(TC[A,B,C,D]0_OVF_vect);
//Exactly what we're supposed to do with this is unclear
//Interrupt handler for the timer that you specify [A or B or C or D]. Note that variables that are modified in interrupt handlers must be declared as volatile. For more information about the volatile keyword check out this tutorial.

void blink_set(uint8_t led, uint16_t interval_ms);
//Set the specified led to blink at the specified interval_ms.

void blink_ms_timer_update();
//Update the state of the LEDs when a timer interrupt has occurred. This is the lower half handler for the timer interrupt, and should only be called if there was an unhandled timer interrupt that has occurred.

uint8_t binaryToPosition(uint8_t binary);
//Convert a bit position variable (eg. 0b10, 0b100) into a uint8_t reflecting its position (2, 3 for the examples given)

#endif
