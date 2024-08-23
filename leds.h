/* 
 * File:   leds.h
 * Author: Lenovo
 *
 * Created on August 22, 2024, 7:02 PM
 */

#ifndef LEDS_H
#define	LEDS_H

#include <avr/io.h>

#define LED0     PC2
#define LED1     PC7
#define LED2     PD3

void init_leds();
void set_led(int led_pin, int state);
void toggle_led(int led_pin);

#endif	/* LEDS_H */
