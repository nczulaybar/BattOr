//Setup the specified timer peripheral. Clear out any timer state and reset all counters. Set it to have the specified interrupt_level.
void timer_init(TC0_t* timer, uint8_t int_level){
	timer->CTRLFSET = timer->CTRLFSET | 0b1000; //Executes reset command on CTRLFSet, see p179
	timer->INTCTRLA = 0b1 & int_level; //Enables overflow interrupt. See p134.
}

//Reset the timer’s counters, but do not reset the peripheral. The timer can be in the middle of execution when it is reset.
void timer_reset(TC0_t* timer){
	setBit(timer->CTRLFSET, 0b1000, 1); //Executes restart command on CTRLFSet, see p179
}

//Takes in period as time in microseconds between every overflow interrupt.
void timer_set(TC0_t* timer, uint8_t prescaler, uint16_t period){
	timer->CTRLA = (0b00000111 & prescaler); //Set prescaler by setting lower 3 bits of CLKSel;
	timer->PER = period;
}
