#ifndef DIGIPOT_H
#define DIGIPOT_H

#include <stdint.h>

#define DIGIPOT_AMP_CS_PIN_gm (1<<3)
#define DIGIPOT_FIL_CS_PIN_gm (1<<4)

void digipot_init();
uint16_t pot_wiperpos_get(uint8_t pot_cs_pin);
void pot_wiperpos_set(uint8_t pot_cs_pin, uint16_t pos);

#endif
