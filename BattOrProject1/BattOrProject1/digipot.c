#define DIGIPOT_AMP_CS_PIN_gm (1<<3)

void digipot_init(){
	SPIC_CTRL = SPIC_CTRL | 1<<6; //Enable register
	SPIC_CTRL = SPIC_CTRL | 1<<4; //Turn to master mode
	SPIC_CTRL = SPIC_CTRL | 1<<5; //Set to transmit least significant first
	SPIC_CTRL = ((SPIC_CTRL | & 0b00) 0b01); //Rising, setup and falling sample
	
	//Set chip select pins to output mode
	gpio_set_mode(PORTC, DIGIPOT_AMP_CS_PIN_gm, 1);
	gpio_set_out(PORTC, DIGIPOT_AMP_CS_PIN_gm, 1);
	
	//Set output pin values to one
	gpio_set_mode(PORTC, 0b10000, 1);
	gpio_set_out(PORTC, 0b10000, 1);
	
	pot_high_impedience_sdo();
}

static void pot_high_impedience_sdo(uint8_t pot_cs_pin){
	//Send 1000 0000 0000 0001
	//Then send command c
}