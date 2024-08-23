#include <avr/io.h>

#define F_CPU 16000000UL
#include <util/delay.h>

#include "DIO.h"
#include "keypad.h"

void init_keypad() {
    set_port_dir_val('C', 0x0F);
    keypad_port |= 0x0F;
}

char read_key() {
    keypad_port |= 0x0F;
    while (1) {
        if (read_port('C')&0xF0) {
            keypad_port &= 0xF0;
            keypad_port |= 1 << 0;
            _delay_ms(5);
            if (read_port('C')&(1 << 4)) {
                _delay_us(500);
                return '7';
            } else if (read_port('C')&(1 << 5)) {
                _delay_us(500);
                return '8';
            } else if (read_port('C')&(1 << 6)) {
                _delay_us(500);
                return '9';
            } else if (read_port('C')&(1 << 7)) {
                _delay_us(500);
                return '/';
            } else {
                keypad_port &= 0xF0;
                keypad_port |= 1 << 1;
                _delay_ms(5);
                if (read_port('C')&(1 << 4)) {
                    _delay_us(500);
                    return '4';
                } else if (read_port('C')&(1 << 5)) {
                    _delay_us(500);
                    return '5';
                } else if (read_port('C')&(1 << 6)) {
                    _delay_us(500);
                    return '6';
                } else if (read_port('C')&(1 << 7)) {
                    _delay_us(500);
                    return '*';
                } else {
                    keypad_port &= 0xF0;
                    keypad_port |= 1 << 2;
                    _delay_ms(5);
                    if (read_port('C')&(1 << 4)) {
                        _delay_us(500);
                        return '1';
                    } else if (read_port('C')&(1 << 5)) {
                        _delay_us(500);
                        return '2';
                    } else if (read_port('C')&(1 << 6)) {
                        _delay_us(500);
                        return '3';
                    } else if (read_port('C')&(1 << 7)) {
                        _delay_us(500);
                        return '-';
                    } else {
                        keypad_port &= 0xF0;
                        keypad_port |= 1 << 3;
                        _delay_ms(5);
                        if (read_port('C')&(1 << 4)) {
                            _delay_us(500);
                            return 'T';
                        } else if (read_port('C')&(1 << 5)) {
                            _delay_us(500);
                            return '0';
                        } else if (read_port('C')&(1 << 6)) {
                            _delay_us(500);
                            return '=';
                        } else if (read_port('C')&(1 << 7)) {
                            _delay_us(500);
                            return '+';
                        } else {

                        }
                    }
                }
            }
        }
        keypad_port |= 0x0F;
    }
    return -1;
}