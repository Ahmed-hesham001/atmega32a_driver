/* 
 * File:   DIO.h
 * Author: Lenovo
 *
 * Created on August 22, 2024, 6:01 PM
 */

#ifndef DIO_H
#define	DIO_H

#include <avr/io.h>

#define IN 0
#define OUT 1

#define LOW 0
#define HIGH 1


void set_pin_dir(char port, int pin_num, int state);
void set_port_dir(char port, int state);
void set_port_dir_val(char port, int val);


void set_pin(char port, int pin_num, int state);
void set_port(char port, int state);
void set_port_val(char port, int val);


char read_pin(char port, int pin_num);
char read_port(char port);


void toggle_pin(char port, int pin_num);
void toggle_port(char port);


#endif	/* DIO_H */
