#include <avr/io.h>
#include "gpio.h"
#include "led.h"

#include "gpio.h"
#include "led.h"
#include "timer.h"
#include "blink.h"

void clock_switch_to_ext_crystal(){
	
	OSC.XOSCCTRL = 0b11001011;
	OSC.CTRL = OSC.CTRL | 0b1000;
	while(!(OSC.STATUS & 0b1000)){
	}
	CPU_CCP = CCP_IOREG_gc;
	CLK.CTRL = 0b11; //Changes multiplexer to set source to external oscillator
	
	
}
/* Start the clock
Wait for it to stabilize
Enable access to protected registers
Set the multiplexer to get clcok from the crystal
Disable all other clocks
*/