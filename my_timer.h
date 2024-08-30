/* 
 * File:   my_timer.h
 * Author: Lenovo
 *
 * Created on August 30, 2024, 9:46 AM
 */

#ifndef MY_TIMER_H
#define	MY_TIMER_H

#define OC0     PB3

#define BTN_INC PB6
#define BTN_DEC PB7

#define OC0_Disable 0
#define OC0_CTC_TOGGLE  1
#define OC0_CTC_CLEAR   2
#define OC0_CTC_SET     3  



#define OC0_PWM_CLEAR_UP  2
#define OC0_PWM_SET_UP    3

#define OC0_FPWM_CLEAR    2
#define OC0_FPWM_SET      3

#define clockSelect_Timer_OFF         0
#define clockSelect_Clk_io            1
#define clockSelect_Clk_io_8          2
#define clockSelect_Clk_io_64         3
#define clockSelect_Clk_io_256        4
#define clockSelect_Clk_io_1024       5
#define clockSelect_EXT_CLK_Falling   6
#define clockSelect_EXT_CLK_Rising    7

#define Timer_mode_Normal             0
#define Timer_mode_CTC                1
#define Timer_mode_PWM                2
#define Timer_mode_FPWM               3

#define Timer0_OCR0_val              254


void timer0_clk_select(char freq); 
void timer0_TOV_INT_Enable();
void timer0_COMP_INT_Enable();
void timer0_select_mode(char mode);
void timer0_select_comp_val(char val);

void init_timer0(char mode, char freq);

void OC0_select_mode(char mode);
void init_OC0(char mode);

#endif	/* MY_TIMER_H */

