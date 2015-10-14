void timer_init(TC0_t* timer, uint8_t int_level);
//Setup the specified timer peripheral. Clear out any timer state and reset all counters. Set it to have the specified interrupt_level.

void timer_reset(TC0_t* timer);
//Reset the timer’s counters, but do not reset the peripheral. The timer can be in the middle of execution when it is reset.

void timer_set(TC0_t* timer, uint8_t prescaler, uint16_t period);
//const uint8_t prescaleDivisors[] = {1, 1, 2, 4, 8, 64, 256, 1024};

//Set the clock prescaler for the timer based on the peripheral clock. 
//This specifies how many clock ticks the peripheral clock will tick for each count in the timer’s counter.
