/* 
 * File:   my_lcd4.h
 * Author: Lenovo
 *
 * Created on August 23, 2024, 1:49 AM
 */

#ifndef MY_LCD4_H
#define	MY_LCD4_H

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

void lcd4_EN();
void lcd4_cmd(char cmd);
void init_lcd4();
void lcd4_print_char(char data);
void lcd4_print_str(char* str);
void lcd4_ptint_int(int num);
void lcd4_set_cur(char row, char column);

#endif	/* MY_LCD4_H */

