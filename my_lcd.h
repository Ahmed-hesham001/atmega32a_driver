/* 
 * File:   my_lcd.h
 * Author: Lenovo
 *
 * Created on August 22, 2024, 9:20 PM
 */

#ifndef MY_LCD_H
#define	MY_LCD_H

#include <avr/io.h>

#define lcd_data PORTA
#define lcd_data_dir DDRA


#define lcd_control PORTB
#define lcd_control_dir DDRB
#define RS PB1
#define RW PB2
#define EN PB3

#define clear 0x01
#define return_home 0x02
#define entry_mode 0x06
#define display_on_cur_off 0x0C
#define mode_8bits 0x38
#define mode_4bits 0x28

void init_lcd8bits();
void lcd_cmd_8bits(char cmd);
void lcd_print_char_8bits(char data);
void lcd_print_str_8bits(char *str);
void lcd_print_num_8bits(int num);
void lcd_print_float_8bits(int num);
void lcd_EN();

#endif	/* MY_LCD_H */
