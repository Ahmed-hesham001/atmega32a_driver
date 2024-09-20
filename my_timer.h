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

#define Timer0_mode_Normal             0
#define Timer0_mode_CTC                1
#define Timer0_mode_PWM                2
#define Timer0_mode_FPWM               3

#define Timer0_OCR0_val              254


void timer0_clk_select(char freq);
void timer0_TOV_INT_Enable();
void timer0_COMP_INT_Enable();
void timer0_select_mode(char mode);
void timer0_select_comp_val(char val);

void init_timer0(char mode, char freq);

void OC0_select_mode(char mode);
void init_OC0(char mode);

//timer 2

//timer2 modes
#define TIMER2_NORMAL_MODE 0
#define TIMER2_PCPWM_MODE  1
#define TIMER2_CTC_MODE    2
#define TIMER2_FPWM_MODE   3

//OC2 MODES
#define OC2_NORMAL_NON_PWM_MODE  0
#define OC2_TOGGLE_NON_PWM_MODE  1
#define OC2_CLEAR_NON_PWM_MODE   2
#define OC2_SET_NON_PWM_MODE     3

#define OC2_NORMAL_PWM_MODE         0
#define OC2_NON_INVERTED_PWM_MODE   2
#define OC2_INVERTED_PWM_MODE       3
#define OC2                       PD7

#define clk_io  0
#define clk_osc 1

void init_timer2_syn(char mode, char freq);
void timer2_select_freq(char freq);
void timer2_select_mode(char mode);
void timer2_TOV_int_en();
void timer2_COMP_int_en();
void init_OC2();
void OC2_select_mode(char mode);
void timer2_select_comp_val(char val);
void timer2_select_syn_asyn(char clk_mode);


//timer 1

#define OC1A        PD5
#define OC1B        PD4
#define ICP1        PD6

//OC1 MODES
#define OC1_NORMAL_MODE 0

#define OC1_CTC_TOGGLE  1
#define OC1_CLC_CLEAR   2
#define OC1_CTC_SET     3

#define OC1_FPWM_TOGGLE_A       1
#define OC1_FPWM_NON_INVERTING  2
#define OC1_FPWM_INVERTING      3

#define OC1_PWM_TOGGLE_A        1
#define OC1_PWM_CLEAR_UP        2
#define OC1_PWM_SET_UP          3

//TIMER 1 MODES
#define TIMER_NORMAL                0 //0 to FFFF

#define TIMER_PWM_8BIT              1 //0 to 00FF to 0
#define TIMER_PWM_9BIT              2 //0 to 01FF to 0
#define TIMER_PWM_10BIT             3 //0 to 03FF to 0

#define TIMER_CTC_OCR1A             4 //0 TO OCR1A

#define TIMER_FAST_PWM_8BIT         5 //0 to 00FF
#define TIMER_FAST_PWM_9BIT         6 //0 to 01FF
#define TIMER_FAST_PWM_10BIT        7 //0 to 03FF

#define TIMER_PWM_FREQ_ICR1         8 //0 TO ICR1
#define TIMER_PWM_FREQ_OCR1A        9 //0 TO OCR1A

#define TIMER_PWM_ICR1              10 //0 TO ICR1
#define TIMER_PWM_OCR1              11 //0 TO OCR1A

#define TIMER_CTC_ICR1              12 //0 TO ICR1

#define TIMER_FAST_PWM_ICR1         14 //0 TO ICR1
#define TIMER_FAST_PWM_OCR1         15 //0 TO OCR1A

#define FALLING_EDGE    0
#define RISING_EDGE     1

int timer1_ICP_getValue();
void timer1_ICP_select_Edge(char edge);
void timer1_ICP_noise_filter();
void timer1_ICP_int_en();
void timer1_ICP_init();
void timer1_OC1B_selectMode(char mode);
void timer1_OC1B_init();
void timer1B_COMP_int_en();
void timer1_OC1A_selectMode(char mode);
void init_OC1A();
void timer1A_COMP_int_en();
void timer1_TOV_int_en();
void timer1_select_mode(char mode);
void timer1_select_clk(char clk);
void init_timer1(char mode, char clk);


#endif	/* MY_TIMER_H */

