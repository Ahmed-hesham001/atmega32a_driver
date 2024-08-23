
#include <avr/io.h>
#include "DIO.h"
#include "buttons.h"

void init_buttons() {
    set_pin_dir('B', BTN0, IN);
    set_pin_dir('D', BTN1, IN);
    set_pin_dir('D', BTN2, IN);
}

char is_pressed(int button_pin) {
    switch (button_pin) {
        case BTN0:
            return read_pin('B', button_pin);
            break;
        case BTN1:
            return read_pin('D', button_pin);
            break;
        case BTN2:
            return read_pin('D', button_pin);
            break;
    }
    return -1;
}