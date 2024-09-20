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
        case Timer0_mode_Normal:
            TCCR0 &= ~((1 << WGM00) | (1 << WGM01));
            timer0_TOV_INT_Enable();
            break;
        case Timer0_mode_CTC:
            OCR0 = Timer0_OCR0_val;
            TCCR0 &= ~(1 << WGM00);
            TCCR0 |= (1 << WGM01);
            timer0_COMP_INT_Enable();
            break;
        case Timer0_mode_PWM:
            OCR0 = Timer0_OCR0_val;
            TCCR0 &= ~(1 << WGM01);
            TCCR0 |= (1 << WGM00);
            break;
        case Timer0_mode_FPWM:
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

//timer 2

/*
  Registers 
 * 1) Timer/Counter (TCNT2)
 * 2) Output Compare Register (OCR2)
 * 3)Timer Interrupt Flag Register (TIFR)
 * 4) Timer Interrupt Mask Register (TIMSK)
 * 5)e Asynchronous Status Register (ASSR)
 * 6) Timer/Counter Control Register (TCCR2)
 * 
 * asynchronous mode in timer 2 :
 * : When switching between asynchronous and synchronous clocking of Timer/Counter2, the Timer
    Registers TCNT2, OCR2, and TCCR2 might be corrupted.
 * . A safe procedure for switching clock source is:
 * 1)disable timer2 interrupts
 * 2)set AS2
 * 3)Write new values to TCNT2, OCR2, and TCCR2.
 * 4)To switch to asynchronous operation: Wait for TCN2UB, OCR2UB, and TCR2UB.
 * 5)Clear the Timer/Counter2 Interrupt Flags.
 * 6)Enable interrupts, if needed.
 * 
 * register descriptions :
 * 
 * TCCR2:
 * |FOC2 | WGM20 |  COM21 | COM20 | WGM21 | CS22 | CS21 | CS20 |
 *   7       6        5       4       3       2      1      0
 * 
 * FOC2: force output compare  only active when the timer is in a non_pwm mode
 * 
 * Bit 6, 3 ? WGM2[1:0]: Waveform Generation Mode these bits determine the timer mode
 * 
 * Bit 5:4 ? COM2[1:0]: Compare Match Output Mode
 *  determine OC2 mode
 * 
 * CS2 2:0 :CLOCK SELECT
 * 
 * ASSR ? Asynchronous Status Register
 * 
 * | ? | ? | ? | ? | AS2 | TCN2UB | OCR2UB | TCR2UB |
 *  7   6   5    4   3      2        1       0
 *  Bit 3 ? AS2: Asynchronous Timer/Counter2 : 
 * When AS2 is written to zero, Timer/Counter 2 is clocked from the I/O clock, clkI/O
 * When AS2 is written to one,Timer/Counter2 is clocked from a Crystal Oscillator connected to 
 * the Timer Oscillator 1 (TOSC1) pin.
 * When the value of AS2 is changed, the contents of TCNT2, OCR2, and TCCR2 might be corrupted.
 * 
 * ? Bit 2 ? TCN2UB: Timer/Counter2 Update Busy
When Timer/Counter2 operates asynchronously and TCNT2 is written, this bit becomes set. When TCNT2 has
been updated from the temporary storage register, this bit is cleared by hardware. A logical zero in this bit indicates
that TCNT2 is ready to be updated with a new value.
 * 
 *  Bit 1 ? OCR2UB: Output Compare Register2 Update Busy
When Timer/Counter2 operates asynchronously and OCR2 is written, this bit becomes set. When OCR2 has been
updated from the temporary storage register, this bit is cleared by hardware. A logical zero in this bit indicates that
OCR2 is ready to be updated with a new value.
 * 
 * 
 *  Bit 0 ? TCR2UB: Timer/Counter Control Register2 Update Busy
When Timer/Counter2 operates asynchronously and TCCR2 is written, this bit becomes set. When TCCR2 has
been updated from the temporary storage register, this bit is cleared by hardware. A logical zero in this bit indicates
that TCCR2 is ready to be updated with a new value.
 * 
 *  TIMSK ? Timer/Counter Interrupt Mask Register
 * 
 * OCIE2 TOIE2 TICIE1 OCIE1A OCIE1B TOIE1 OCIE0 TOIE0 
 *   7     6     5       4     3      2     1    0
 * 
 * OCIE2 TOIE2 :timer 2 interrupts enable
 * 
 * 
 * 
 */

void init_timer2_syn(char mode, char freq) {

    timer2_select_freq(freq);

    timer2_select_mode(mode);

}

void timer2_select_freq(char freq) {
    TCCR2 &= ~((1 << CS22) | (1 << CS21) | (1 << CS20));
    TCCR2 |= freq;
}

void timer2_select_mode(char mode) {
    TCCR2 &= ~(1 << WGM21 | 1 << WGM20);
    switch (mode) {
        case TIMER2_NORMAL_MODE:
            //do nothing
            //enable tov int here if needed
            break;
        case TIMER2_PCPWM_MODE:
            TCCR2 |= (1 << WGM20);
            break;
        case TIMER2_CTC_MODE:
            TCCR2 |= (1 << WGM21);
            //enable oci here if needed
            break;
        case TIMER2_FPWM_MODE:
            TCCR2 |= (1 << WGM21 | 1 << WGM20);
            break;
    }
}

void timer2_TOV_int_en() {
    TIMSK |= (1 << TOIE2);
}

void timer2_COMP_int_en() {
    TIMSK |= (1 << OCIE2);
}

void init_OC2() {
    set_pin_dir('B', OC2, OUT);
}

void OC2_select_mode(char mode) {
    TCCR2 &= ~((1 << COM21) | (1 << COM20));
    TCCR2 |= (mode << COM20);
}

void timer2_select_comp_val(char val) {
    OCR2 = val;
}

void timer2_select_syn_asyn(char clk_mode) {
    char a, b, c;
    a = TCNT2;
    b = OCR2;
    c = TCCR2;

    DDRB &= ~((1 << PB6) | (1 << PB7));

    //1)disable interrupts
    TIMSK &= ~((1 << OCIE2) | (1 << TOIE2));
    //2)select clk mode
    switch (clk_mode) {
        case(clk_io):
            ASSR &= ~(1 << AS2);
            break;
        case (clk_osc):
            ASSR |= (1 << AS2);
            break;
    }
    //3)write new values
    TCNT2 = a;
    OCR2 = b;
    TCCR2 = c;
    //4)wait until busy flags are done
    while (ASSR & ((1 << TCR2UB) | (1 << OCR2UB) | (1 << TCN2UB)));

    //5)Clear the Timer/Counter2 Interrupt Flags.
    TIFR &= ~((1 << OCF2) | (1 << TOV2));

    //6)interrupts enable if needed
    //    timer2_COMP_int_en();
    //    timer2_TOV_int_en();
}

//timer1

/*
 * timer 1 is a 16 bit timer 
 * 
 * registers :
 * 
 * 1)TCNT1 ->TIMER\COUNTER REGISTER
 * 2)OCR1A AND OCR1B -> OUTPUT COMPARE REGISTER A AND B
 * 3)ICR1 -> INPUT CAPTURE REGISTER
 * THOSE THREE ARE 16 BIT REGISTERS ALL OF THEM HAVE H AND L 
 * 
 * 4)TIFR
 * 5)TIMSK
 * 6)TCCR1A
 * 7)TCCR1B
 * 8)ACSR
 * 
 * 
 * accessing 16 bit registers :
 * -The 16-bit register must be byte accessed using two read or write operations.
 * -Each 16-bit timer has a single 8-bit 
 * register for temporary storing of the high byte of the 16-bit access. 
 * -
 */

/**
 * 
 * @param mode
 * @param clk
 */
void init_timer1(char mode, char clk) {
    timer1_select_clk(clk);
    timer1_select_mode(mode);
}

/**
 * 
 * @param clk
 */
void timer1_select_clk(char clk) {
    TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
    TCCR1B |= clk;
}

/**
 * 
 * @param mode
 */
void timer1_select_mode(char mode) {
    TCCR1A &= ~((1 << WGM11) | (1 << WGM10));
    TCCR1B &= ~((1 << WGM13) | (1 << WGM12));
    switch (mode) {
        case TIMER_NORMAL://00 00
            //do nothing
            break;
        case TIMER_PWM_8BIT://00 01
            TCCR1A |= 1;
            break;
        case TIMER_PWM_9BIT://00 10
            TCCR1A |= 2;
            break;
        case TIMER_PWM_10BIT://00 11
            TCCR1A |= 3;
            break;
        case TIMER_CTC_OCR1A://01 00
            TCCR1B |= (1 << WGM12);
            break;
        case TIMER_FAST_PWM_8BIT://01 01
            TCCR1A |= 1;
            TCCR1B |= (1 << WGM12);
            break;
        case TIMER_FAST_PWM_9BIT://01 10
            TCCR1A |= 2;
            TCCR1B |= (1 << WGM12);
            break;
        case TIMER_FAST_PWM_10BIT://01 11
            TCCR1A |= 3;
            TCCR1B |= (1 << WGM12);
            break;
        case TIMER_PWM_FREQ_ICR1://10 00
            TCCR1B |= (2 << WGM12);
            break;
        case TIMER_PWM_FREQ_OCR1A://10 01
            TCCR1A |= 1;
            TCCR1B |= (2 << WGM12);
            break;
        case TIMER_PWM_ICR1://10 10
            TCCR1A |= 2;
            TCCR1B |= (2 << WGM12);
            break;
        case TIMER_PWM_OCR1://10 11
            TCCR1A |= 3;
            TCCR1B |= (2 << WGM12);
            break;
        case TIMER_CTC_ICR1://11 00
            TCCR1B |= (3 << WGM12);
            break;
        case TIMER_FAST_PWM_ICR1://11 10
            TCCR1A |= 2;
            TCCR1B |= (3 << WGM12);
            break;
        case TIMER_FAST_PWM_OCR1://11 11
            TCCR1A |= 3;
            TCCR1B |= (3 << WGM12);
            break;
    }
}

void timer1_TOV_int_en() {
    TIMSK |= 1 << TOIE1;
}

void timer1A_COMP_int_en() {
    TIMSK |= (1 << OCIE1A);
}

void init_OC1A() {
    set_pin_dir('D', OC1A, OUT);
}

/**
 * 
 * @param mode
 */
void timer1_OC1A_selectMode(char mode) {
    TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0));
    TCCR1A |= (mode << COM1A0);
}

void timer1B_COMP_int_en() {
    TIMSK |= (1 << OCIE1B);
}

void timer1_OC1B_init() {
    set_pin_dir('D', OC1B, OUT);
}

/**
 * 
 * @param mode
 */
void timer1_OC1B_selectMode(char mode) {
    TCCR1A &= ~((1 << COM1B1) | (1 << COM1B0));
    TCCR1A |= (mode << COM1B0);
}

void timer1_ICP_init() {
    set_pin_dir('D', ICP1, IN);
    ACSR &= ~(1 << ACIC);
}

void timer1_ICP_int_en() {
    TIMSK |= 1 << TICIE1;
}

void timer1_ICP_noise_filter() {
    TCCR1B |= 1 << ICNC1;
}

/**
 * 
 * @param edge
 */
void timer1_ICP_select_Edge(char edge) {
    TCCR1B &= ~(1 << ICES1);
    TCCR1B |= edge << ICES1;
}

int timer1_ICP_getValue(){
    return ICR1;
}