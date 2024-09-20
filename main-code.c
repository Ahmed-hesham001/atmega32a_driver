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
#include "my_timer.h"
#include "my_functions.h"
#include "my_usart.h"
#include "spi.h"
#include "eeprom.h"

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
//char input;
//
//ISR(INT0_vect) {
//    lcd4_cmd(clear);
//    lcd4_print_str("enter pot num: ");
//    input = read_key();
//}
//
//int main(void) {
//    init_adc(AVCC, div_factor128, ch0);
//    init_lcd4();
//    init_keypad();
//    init_INT0(INT_FALLING_EDGE);
//    _delay_ms(100);
//    lcd4_cmd(clear);
//    lcd4_print_str("enter pot num: ");
//    input = read_key();
//    
//    while (1) {
//        switch (input) {
//            case '1':
//                adc_select_channel(ch0);
//                adc_sc();
//                check_flag;
//                lcd4_cmd(clear);
//                lcd4_print_str("pot 1 : ");
//                lcd4_ptint_int(ADCW * step);
//                lcd4_print_str("mV");
//                _delay_ms(500);
//                break;
//            case '2':
//                adc_select_channel(ch1);
//                adc_sc();
//                check_flag;
//                lcd4_cmd(clear);
//                lcd4_print_str("pot 2 : ");
//                lcd4_ptint_int(ADCW * step);
//                lcd4_print_str("mV");
//                _delay_ms(500);
//                break;
//            case '3':
//                adc_select_channel(ch2);
//                adc_sc();
//                check_flag;
//                lcd4_cmd(clear);
//                lcd4_print_str("pot 3 : ");
//                lcd4_ptint_int(ADCW * step);
//                lcd4_print_str("mV");
//                _delay_ms(500);
//                break;
//            default:
//                lcd4_cmd(clear);
//                lcd4_print_str("invalid input>:(");
//                _delay_ms(1500);
//                lcd4_cmd(clear);
//                lcd4_print_str("enter pot num: ");
//                input = read_key();
//                break;
//
//        }
//    }
//}
//ISR(TIMER1_CAPT_vect){
//    lcd4_cmd(clear);
//    lcd4_ptint_int(timer1_ICP_getValue());
//}
//int main(void) {
//    init_lcd4();
//    init_timer1(TIMER_NORMAL,clockSelect_Clk_io_1024);
//    timer1_ICP_select_Edge(FALLING_EDGE);
//    timer1_ICP_init();
//    timer1_ICP_noise_filter();
//    timer1_ICP_int_en();
//    sei();
//    while (1) {
//    
//    }
//}

////////////////////////////////usart///////////////////////////////
//#define buzzer PA3
//
//int main() {
//    DDRA |= (1 << buzzer);
//    init_buttons();
//    init_lcd4();
//    init_usart(asyn, 1200);
//    char message[16];
//    char state = -1;
//    while (1) {
//
//        if (is_pressed(BTN1)) {
//            _delay_ms(100);
//            state = 1;
//
//        }
//        if (is_pressed(BTN2)) {
//            _delay_ms(100);
//            state = 2;
//        }
//        switch (state) {
//            case 1:
//                lcd4_cmd(clear);
//                strcpy(message, "RECEIVER");
//                lcd4_print_str(message);
//                lcd4_set_cur(1, 0);
////                for (int i = 0; i < 16; ++i) {
////                    lcd4_print_char(usart_receive_data());
////                }
////                _delay_ms(2000);
//                lcd4_print_char(usart_receive_data());
//                _delay_ms(2000);
////                if(usart_receive_data()){
////                    set_pin('A', buzzer, HIGH);
////                _delay_ms(250);
////                set_pin('A', buzzer, LOW);
////                }
//                state = -1;
//                break;
//            case 2:
//                lcd4_cmd(clear);
//                strcpy(message, "TRANSMITTER");
//                lcd4_print_str(message);
//                lcd4_set_cur(1, 0);
////                strcpy(message, "test yasta");
////                for (int i = 0; i < 16; ++i) {
////                    usart_send_data(message[i]);
////                    _delay_ms(500);
////                    }
//                usart_send_data('7');
//                _delay_ms(500);
//                state = -1;
//                break;
//            default:
//                state = -1;
//                lcd4_cmd(clear);
//                strcpy(message, "pick mode :");
//                lcd4_print_str(message);
//                break;
//        }
//
//    }
//    return 0;
//}

//int main() {
//    init_spi(master, SPI_CLK_128);
//    init_leds();

//    init_buttons();
//
//    init_lcd4();
//    _delay_ms(100);
//    while (1) {
//                if (is_pressed(BTN0)){
//                    _delay_ms(150);
//                    spi_send_data(1);
//                    lcd4_cmd(clear);
//                    lcd4_print_char('1');
//                }
//                if (is_pressed(BTN1)){
//                    _delay_ms(150);
//                    spi_send_data(2);
//                    lcd4_cmd(clear);
//                    lcd4_print_char('2');
//                }

//        char input = spi_get_data();
//
//        switch (input) {
//            case 1:
//                set_led(LED0, HIGH);
//                lcd4_cmd(clear);
//                lcd4_print_char('1');
//                break;
//            case 2:
//                set_led(LED0, LOW);
//                lcd4_cmd(clear);
//                lcd4_print_char('2');
//                break;
//        }

//    }

int main() {

    init_buttons();
    init_lcd4();
    spi_clk_select(SPI_CLK_128);
    init_spi(MASTER);

    char data = 'A';

    eeprom_write_char(data, 0x10);

    lcd4_print_char(eeprom_read_char(0x10));
    _delay_ms(50);

    int i = 0;
    while (1) {

        if (is_pressed(BTN0)) {
            if(i>=15 && i<32){
                lcd4_set_cur(1,0+i-16);
            }else if (i>=32){
                lcd4_cmd(clear);
                lcd4_set_cur(0,0);
                i=0;
            }
            eeprom_write_char(++data, 0x10);
            _delay_ms(200);
            lcd4_print_char(eeprom_read_char(0x10));
            ++i;
        }

    }
    return 0;
}