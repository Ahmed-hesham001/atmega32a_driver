/* 
 * File:   buttons.h
 * Author: Lenovo
 *
 * Created on August 22, 2024, 7:14 PM
 */

#ifndef BUTTONS_H
#define	BUTTONS_H

#include <avr/io.h>

#define BTN0 PB0
#define BTN1 PD6
#define BTN2 PD2

void init_buttons();
char is_pressed(int button_pin);

#endif	/* BUTTONS_H */
