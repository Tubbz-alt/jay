/* 
	PAVx -- Pod-Based Autonomous Vehicles 
	Library Created By: Sargis S Yonan
	March 2017
*/ 

// leds.c

#include "leds.h"

void leds_init(uint8_t led) {
	if (led == SYSTEM_LED) {
		SYSTEM_LED_DDR |= (1 << SYSTEM_LED_DDPORT);
	}
}
void toggle_led(uint8_t led) {
	if (led == SYSTEM_LED) {
		SYSTEM_LED_PORT ^= (1 << SYSTEM_LED_PIN);
	}
}