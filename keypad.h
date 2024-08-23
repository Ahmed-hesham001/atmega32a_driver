/* 
 * File:   keypad.h
 * Author: Lenovo
 *
 * Created on August 23, 2024, 2:26 AM
 */

#ifndef KEYPAD_H
#define	KEYPAD_H

#include <avr/io.h>

#define keypad_port_dir DDRC
#define keypad_port     PORTC

void init_keypad();

char read_key();


#endif	/* KEYPAD_H */

