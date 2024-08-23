
#include <avr/io.h>
#include "DIO.h"
#include "leds.h"

void init_leds() {
    set_pin_dir('C', LED0, OUT);
    set_pin_dir('C', LED1, OUT);
    set_pin_dir('D', LED2, OUT);
}

/**
 * 
 * @param led_pin
 * @param state
 */
void set_led(int led_pin, int state) {
    switch (led_pin) {
        case LED0:
            set_pin('C', led_pin, state);
            break;
        case LED1:
            set_pin('C', led_pin, state);
            break;
        case LED2:
            set_pin('D', led_pin, state);
            break;
    }
}

/**
 * 
 * @param led_pin
 */
void toggle_led(int led_pin) {
    switch (led_pin) {
        case LED0:
            toggle_pin('C', led_pin);
            break;
        case LED1:
            toggle_pin('C', led_pin);
            break;
        case LED2:
            toggle_pin('D', led_pin);
            break;
    }
}