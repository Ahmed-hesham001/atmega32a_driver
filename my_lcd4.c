#include <avr/io.h>

#define F_CPU 16000000UL
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>

#include "DIO.h"
#include "my_lcd4.h"
#include "my_lcd.h"
#include "my_functions.h"

void lcd4_EN() {
    lcd_control |= (1 << EN);
    _delay_ms(5);
    lcd_control &= ~(1 << EN);
}

/**
 * 
 * @param cmd
 */
void lcd4_cmd(char cmd) {
    lcd_control &= ~(1 << RS);
    _delay_ms(5);

    lcd_data = (lcd_data & 0x0F) | (cmd & 0xF0);
    lcd4_EN();
    _delay_ms(1);

    lcd_data = (lcd_data & 0x0F) | (cmd << 4);
    lcd4_EN();
    _delay_ms(1);
}

void init_lcd4() {


    set_port_dir_val('A', 0xF0);
    set_pin_dir('B', RS, OUT);
    set_pin_dir('B', RW, OUT);
    set_pin_dir('B', EN, OUT);
    _delay_ms(20);

    //write mode
    lcd_control &= ~(1 << RW);

    //return home
    lcd4_cmd(return_home);

    //4bit mode
    lcd4_cmd(mode_4bits);

    //display on cur off
    lcd4_cmd(display_on_cur_off);

    //clear
    lcd4_cmd(clear);
}

/**
 * 
 * @param data
 */
void lcd4_print_char(char data) {
    lcd_control |= (1 << RS);

    lcd_data = (lcd_data & 0x0F) | (data & 0xF0);
    lcd4_EN();
    _delay_ms(1);

    lcd_data = (lcd_data & 0x0F) | (data << 4);
    lcd4_EN();
    _delay_ms(1);
}

/**
 * 
 * @param str
 */
void lcd4_print_str(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        lcd4_print_char(str[i]);
    }
}

/**
 * 
 * @param num
 */
void lcd4_ptint_int(int num) {
    char str[16];
    itoa(num, str);
    lcd4_print_str(str);
}

/**
 * 
 * @param row
 * @param column
 */
void lcd4_set_cur(char row, char column) {
    lcd4_cmd(0x80 | column | (row << 6));
}
