#include <stdint.h>
#include <avr/io.h>

//Set the specified pin on the specified port to be in output (1) or input (0) mode.
void gpio_set_mode(PORT_t* port, uint8_t pin, uint8_t out_or_in){
  if(out_or_in) port->DIRSET = pin;
  else port->DIRCLR = pin;
}


