#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "DIO.h"
#include "my_timer.h"

/**
 * 
 * @param freq
 */
void timer0_clk_select(char freq) {
    TCCR0 &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
    TCCR0 |= freq;
}

void timer0_TOV_INT_Enable() {
    TIMSK |= (1 << TOIE0);
}

void timer0_COMP_INT_Enable() {
    TIMSK |= (1 << OCIE0);
}

/**
 * 
 * @param mode
 */
void timer0_select_mode(char mode) {
    TCCR0 &= ~((1 << WGM00) | (1 << WGM01));
    switch (mode) {
        case Timer_mode_Normal:
            TCCR0 &= ~((1 << WGM00) | (1 << WGM01));
            timer0_TOV_INT_Enable();
            break;
        case Timer_mode_CTC:
            OCR0 = Timer0_OCR0_val;
            TCCR0 &= ~(1 << WGM00);
            TCCR0 |= (1 << WGM01);
            timer0_COMP_INT_Enable();
            break;
        case Timer_mode_PWM:
            OCR0 = Timer0_OCR0_val;
            TCCR0 &= ~(1 << WGM01);
            TCCR0 |= (1 << WGM00);
            break;
        case Timer_mode_FPWM:
            OCR0 = Timer0_OCR0_val;
            TCCR0 |= (1 << WGM01);
            TCCR0 |= (1 << WGM00);
            break;
    }
}

void init_timer0(char mode, char freq) {
    timer0_clk_select(freq);

    timer0_select_mode(mode);

}

/**
 * 
 * @param mode
 */
void OC0_select_mode(char mode) {
    TCCR0 &= ~((1 << COM00) | (1 << COM01));
    TCCR0 |= (mode << COM00);
}

/**
 * 
 * @param mode
 */
void init_OC0(char mode) {
    set_pin_dir('B', OC0, OUT);
    OC0_select_mode(mode);
}

/**
 * 
 * @param val
 */
void timer0_select_comp_val(char val) {
    OCR0 = val;
}