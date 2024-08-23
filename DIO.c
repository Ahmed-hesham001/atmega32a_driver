
#include <avr/io.h>
#include "DIO.h"

/**
 * 
 * @param port
 * @param pin_num
 * @param state
 */
void set_pin_dir(char port, int pin_num, int state) {//function to set the data dir of the pin
    switch (state) {
        case OUT:
            switch (port) {
                case 'A':
                    DDRA |= 1 << pin_num;
                    break;
                case 'B':
                    DDRB |= 1 << pin_num;
                    break;
                case 'C':
                    DDRC |= 1 << pin_num;
                    break;
                case 'D':
                    DDRD |= 1 << pin_num;
                    break;
            }
            break;
        case IN:
            switch (port) {
                case 'A':
                    DDRA &= ~(1 << pin_num);
                    break;
                case 'B':
                    DDRB &= ~(1 << pin_num);
                    break;
                case 'C':
                    DDRC &= ~(1 << pin_num);
                    break;
                case 'D':
                    DDRD &= ~(1 << pin_num);
                    break;
            }
            break;
    }
}

/**
 * 
 * @param port
 * @param state
 */
void set_port_dir(char port, int state) {//function to set the dir of the whole port
    switch (state) {
        case OUT:
            switch (port) {
                case 'A':
                    DDRA = 0xFF;
                    break;
                case 'B':
                    DDRB = 0xFF;
                    break;
                case 'C':
                    DDRC = 0xFF;
                    break;
                case 'D':
                    DDRD = 0xFF;
                    break;
            }
            break;
        case IN:
            switch (port) {
                case 'A':
                    DDRA = 0x00;
                    break;
                case 'B':
                    DDRB = 0x00;
                    break;
                case 'C':
                    DDRC = 0x00;
                    break;
                case 'D':
                    DDRD = 0x00;
                    break;
            }
            break;
    }
}

/**
 * 
 * @param port
 * @param val
 */
void set_port_dir_val(char port, int val) {
    switch (port) {
        case 'A':
            DDRA = val;
            break;
        case 'B':
            DDRB = val;
            break;
        case 'C':
            DDRC = val;
            break;
        case 'D':
            DDRD = val;
            break;
    }
}

/**
 * 
 * @param port
 * @param pin_num
 * @param state
 */
void set_pin(char port, int pin_num, int state) {//function to set the pin value
    switch (state) {
        case HIGH:
            switch (port) {
                case 'A':
                    PORTA |= 1 << pin_num;
                    break;
                case 'B':
                    PORTB |= 1 << pin_num;
                    break;
                case 'C':
                    PORTC |= 1 << pin_num;
                    break;
                case 'D':
                    PORTD |= 1 << pin_num;
                    break;
            }
            break;
        case LOW:
            switch (port) {
                case 'A':
                    PORTA &= ~(1 << pin_num);
                    break;
                case 'B':
                    PORTB &= ~(1 << pin_num);
                    break;
                case 'C':
                    PORTC &= ~(1 << pin_num);
                    break;
                case 'D':
                    PORTD &= ~(1 << pin_num);
                    break;
            }
            break;
    }
}

/**
 * 
 * @param port
 * @param state
 */
void set_port(char port, int state) {
    switch (state) {
        case HIGH:
            switch (port) {
                case 'A':
                    PORTA = 0xFF;
                    break;
                case 'B':
                    PORTB = 0xFF;
                    break;
                case 'C':
                    PORTC = 0xFF;
                    break;
                case 'D':
                    PORTD = 0xFF;
                    break;
            }
            break;
        case LOW:
            switch (port) {
                case 'A':
                    PORTA = 0x00;
                    break;
                case 'B':
                    PORTB = 0x00;
                    break;
                case 'C':
                    PORTC = 0x00;
                    break;
                case 'D':
                    PORTD = 0x00;
                    break;
            }
            break;
    }
}

/**
 * 
 * @param port
 * @param val
 */
void set_port_val(char port, int val) {
    switch (port) {
        case 'A':
            PORTA = val;
            break;
        case 'B':
            PORTB = val;
            break;
        case 'C':
            PORTC = val;
            break;
        case 'D':
            PORTD = val;
            break;
    }
}

/**
 * 
 * @param port
 * @param pin_num
 * @return 
 */
char read_pin(char port, int pin_num) {
    switch (port) {
        case 'A':
            return (PINA & (1 << pin_num));
            break;
        case 'B':
            return (PINB & (1 << pin_num));
            break;
        case 'C':
            return (PINC & (1 << pin_num));
            break;
        case 'D':
            return (PIND & (1 << pin_num));
            break;
    }
    return -1;
}

/**
 * 
 * @param port
 * @return 
 */
char read_port(char port) {
    switch (port) {
        case 'A':
            return PINA;
            break;
        case 'B':
            return PINB;
            break;
        case 'C':
            return PINC;
            break;
        case 'D':
            return PIND;
            break;
        default:
            break;
    }
    return -1;
}

/**
 * 
 * @param port
 * @param pin_num
 */
void toggle_pin(char port, int pin_num) {
    switch (port) {
        case 'A':
            PORTA ^= 1 << pin_num;
            break;
        case 'B':
            PORTB ^= 1 << pin_num;
            break;
        case 'C':
            PORTC ^= 1 << pin_num;
            break;
        case 'D':
            PORTD ^= 1 << pin_num;
            break;
    }
}

/**
 * 
 * @param port
 */
void toggle_port(char port) {
    switch (port) {
        case 'A':
            PORTA ^= 0xFF;
            break;
        case 'B':
            PORTB ^= 0xFF;
            break;
        case 'C':
            PORTC ^= 0xFF;
            break;
        case 'D':
            PORTD ^= 0xFF;
            break;
    }
}