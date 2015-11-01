//Read the wiper position (0 - 1023) of the potentiometer which has its CS pin connected to pot_cs_pin.
uint16_t pot_wiperpos_get(uint8_t pot_cs_pin){
  gpio_set_out(&PORTC, DIGIPOT_AMP_CS_gm, 0); //Pull down CS

  uint16_t returnable = -1;
  spi_txrx(SPIC, 0b00100000000000, returnable, 2);

  pot_high_impedience_sdo(pot_cs_pin); //Make it happen
  gpio_set_out(&PORTC, DIGIPOT_AMP_CS_gm, 1); //Pull up CS
}

//Write the wiper position (0 - 1023) of the potentiometer which has its CS pin connected to pot_cs_pin.
void pot_wiperpos_set(uint8_t pot_cs_pin, uint16_t pos){
  gpio_set_out(&PORTC, DIGIPOT_AMP_CS_gm, 0); //Pull down CS

  spi_txrx(SPIC, 0b00010000000000 | pos, NULL, 2);

  pot_high_impedience_sdo(pot_cs_pin);
  gpio_set_out(&PORTC, DIGIPOT_AMP_CS_gm, 1); //Pull up CS
}
