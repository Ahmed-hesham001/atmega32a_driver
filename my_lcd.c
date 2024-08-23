
#include <avr/io.h>

#define F_CPU 16000000UL
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>

#include "DIO.h"
#include "my_lcd.h"
#include "my_functions.h"

void init_lcd8bits() {

    set_port_dir(lcd_data_dir, OUT);
    set_pin_dir('B', RS, OUT);
    set_pin_dir('B', RW, OUT);
    set_pin_dir('B', EN, OUT);

    _delay_ms(20);

    //write mode
    set_pin('B', RW, LOW);
    _delay_ms(1);

    //set mode
    lcd_cmd_8bits(mode_8bits);
    _delay_ms(1);

    //return home
    lcd_cmd_8bits(return_home);
    _delay_ms(1);

    //display on cur off
    lcd_cmd_8bits(display_on_cur_off);

    //clear
    lcd_cmd_8bits(clear);
    _delay_ms(2);

    //entry mode
    lcd_cmd_8bits(entry_mode);
    _delay_ms(1);

}

/**
 * 
 * @param cmd
 * @return 
 */
void lcd_cmd_8bits(char cmd) {
    lcd_control &= ~(1 << RS);
    _delay_ms(1);
    lcd_data = cmd;
    _delay_ms(1);
    lcd_EN();
}

void lcd_EN() {
    lcd_control |= (1 << EN);
    _delay_ms(1);
    lcd_control &= ~(1 << EN);
}

/**
 * 
 * @param data
 */
void lcd_print_char_8bits(char data) {
    lcd_control |= (1 << RS);
    lcd_data = data;
    lcd_EN();
    _delay_ms(20);
}

/**
 * 
 * @param str
 */
void lcd_print_str_8bits(char *str) {
    for (int i = 0; str[i] != '\0'; ++i) {
        lcd_print_char_8bits(str[i]);
        _delay_ms(1);
    }
}

/**
 * 
 * @param num
 */
void lcd_print_num_8bits(int num) {
    char str[11];
    itoa(num, str);
    _delay_ms(1);
    lcd_print_str_8bits(str);
    _delay_ms(1);
}

