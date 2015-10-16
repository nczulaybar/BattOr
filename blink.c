//Initialize the state of all of the LEDs in local state of the blink library to have their blinks disabled. Also, setup a timer that will fire an interrupt once every millisecond. Note that the timer is clocked off of the peripheral clock, and the peripheral clock is clocked off of the system clock.
void blink_init(){
	timer_init(&TCC0, 0b11); //high interrupt level
	timer_set(&TCC0, 0b1, 2000); //2000 ticks corresponds to 1ms, as of 10/15 10:32pm
}

ISR(TCC0_OVF_vect){
	globalTime++;
}

//Set the specified led to blink at the specified interval_ms.
void blink_set(uint8_t led, uint16_t interval_ms){
	LEDArray[led].blinkInterval = interval_ms;
}

//Update the state of the LEDs when a timer interrupt has occurred. This is the lower half handler for the timer interrupt, and should only be called if there was an unhandled timer interrupt that has occurred.
void blink_ms_timer_update(){
	
	lastTime = globalTime;

	for (int i = 0; i < 3; i++) {
		if (LEDArray[i].blinkInterval != 0) {
			if (lastTime < globalTime) {
				LEDArray[i].counter += (globalTime - lastTime); 
				}
			if (LEDArray[i].counter >= LEDArray[i].blinkInterval) {
				LEDArray[i].counter = LEDArray[i].counter-LEDArray[i].blinkInterval;
				led_toggle(0b1 << (i));
			}
		}
	}
}
//sizeof(LEDArray)/sizeof(LEDArray[0])
/*
uint8_t binaryToPosition(uint8_t binary){
	for(uint8_t pos = 0; pos<8; pos++){
		binary >> 1;
		if(binary & 0b1) return pos;
	}

	return 0;
}
*/