//Initialize the state of all of the LEDs in local state of the blink library to have their blinks disabled. Also, setup a timer that will fire an interrupt once every millisecond. Note that the timer is clocked off of the peripheral clock, and the peripheral clock is clocked off of the system clock.
void blink_init(){
	//Disable blinks
	timer_init(&TCC0, 0b11);
	timer_set(&TCC0, 0b001, 1000);
}

ISR(TCC0_OVF_vect){
	globalTime++;
}
//Exactly what we're supposed to do with this is unclear
//Interrupt handler for the timer that you specify [A or B or C or D]. Note that variables that are modified in interrupt handlers must be declared as volatile. For more information about the volatile keyword check out this tutorial.

//Set the specified led to blink at the specified interval_ms.
void blink_set(uint8_t led, uint16_t interval_ms){
	
}

//Update the state of the LEDs when a timer interrupt has occurred. This is the lower half handler for the timer interrupt, and should only be called if there was an unhandled timer interrupt that has occurred.
void blink_ms_timer_update(){
	if (globalTime > 1000) {
		led_toggle(LED_RED_bm);
		globalTime = 0;
	}
}

//%redLED.blinkInterval ==
