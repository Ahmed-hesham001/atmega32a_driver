/*
 * File:   newavr-main.c
 * Author: Lenovo
 *
 * Created on August 22, 2024, 5:55 PM
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "DIO.h"
#include "buttons.h"
#include "leds.h"
#include "my_lcd.h"
#include "my_lcd4.h"
#include "keypad.h"
#include "adc.h"
#include "my_interrupt.h"

//password code
//int main(void) {
//    /* Replace with your application code */
//    init_keypad();
//    init_lcd4();
//    char password [] = "5555";
//    int tries = 3;
//    char input [17];
//
//    while (1) {
//        if (tries) {
//            lcd4_cmd(clear);
//            lcd4_print_str("password :");
//            lcd4_set_cur(1, 0);
//            for (int i = 0; i < 16; ++i) {
//                if (read_key() == '=') {
//                    _delay_ms(200);
//                    break;
//                } else {
//                    input[i] = read_key();
//                    _delay_ms(200);
//                    lcd4_print_char(input[i]);
//                }
//            }
//            if (!strcmp(input, password)) {
//                lcd4_cmd(clear);
//                lcd4_print_str("access granted");
//                _delay_ms(1000);
//                break;
//            } else {
//                lcd4_cmd(clear);
//                lcd4_print_str("access denied");
//                _delay_ms(1000);
//                --tries;
//            }
//        } else {
//            lcd4_cmd(clear);
//            lcd4_print_str("device blocked");
//            _delay_ms(1000);
//            break;
//        }
//    }
//}
char input;

ISR(INT0_vect) {
    lcd4_cmd(clear);
    lcd4_print_str("enter pot num: ");
    input = read_key();
}

int main(void) {
    sei();
    init_adc(AVCC, div_factor128, ch0);
    init_lcd4();
    init_keypad();
    init_INT0(INT_FALLING_EDGE);
    lcd4_cmd(clear);
    lcd4_print_str("enter pot num: ");
    input = read_key();
    while (1) {
        switch (input) {
            case '1':
                adc_select_channel(ch0);
                adc_sc();
                check_flag;
                lcd4_cmd(clear);
                lcd4_print_str("pot 1 : ");
                lcd4_ptint_int(ADCW * step);
                lcd4_print_str("mV");
                _delay_ms(500);
                break;
            case '2':
                adc_select_channel(ch1);
                adc_sc();
                check_flag;
                lcd4_cmd(clear);
                lcd4_print_str("pot 2 : ");
                lcd4_ptint_int(ADCW * step);
                lcd4_print_str("mV");
                _delay_ms(500);
                break;
            case '3':
                adc_select_channel(ch2);
                adc_sc();
                check_flag;
                lcd4_cmd(clear);
                lcd4_print_str("pot 3 : ");
                lcd4_ptint_int(ADCW * step);
                lcd4_print_str("mV");
                _delay_ms(500);
                break;
            default:
                lcd4_cmd(clear);
                lcd4_print_str("invalid input>:(");
                _delay_ms(1500);
                lcd4_cmd(clear);
                lcd4_print_str("enter pot num: ");
                input = read_key();
                break;

        }
    }
}