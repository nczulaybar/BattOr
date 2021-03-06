#ifndef GPIO_H
#define GPIO_H

#include <avr/io.h>

void gpio_set_mode(PORT_t* port, uint8_t pin, uint8_t out_or_in);
//Set the specified pin on the specified port to be in output (1) or input (0) mode.

//If the specified pin on the specified port is in output mode, set the output of that pin to be on (1) or off (0).
inline void gpio_set_out(PORT_t* port, uint8_t pin, uint8_t on_or_off){
	if(on_or_off) port->OUTSET = pin;
	else port->OUTCLR = pin;
}

//If the specified pin on the specified port is in output mode, toggle the pin’s state (if 1 then 0, if 0 then 1).
inline void gpio_toggle_out(PORT_t* port, uint8_t pin){
	port->OUTTGL=pin;
}

//returns value of bit at a specified position in a specified uint8_t
inline uint8_t getBit(uint8_t target, uint8_t requestedBit){
	return (target & requestedBit);
}

//sets value of bit at a specified position in a specified uint8_t and returns changed uint8_t
inline uint8_t setBit(uint8_t target, uint8_t requestedBit, uint8_t requestedValue){
	uint8_t setValue = (requestedValue == 0) ? requestedBit : 0;
	return (target | requestedBit) & (0b11111111 ^ setValue); //could we do ~setValue
}

#endif