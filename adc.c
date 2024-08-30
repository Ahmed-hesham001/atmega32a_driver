#include <avr/io.h>

#define F_CPU 16000000UL
#include <util/delay.h>

#include "DIO.h"
#include "adc.h"

/**
 * 
 * @param ch
 */
void adc_select_channel(char ch) {
    ADMUX &= ~((1 << MUX2) | (1 << MUX1) | (1 << MUX0));
    _delay_ms(1);
    ADMUX |= ch;
    _delay_ms(1);
}

/**
 * 
 * @param freq
 */
void adc_select_freq(char freq) {
    ADCSRA &= ~((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0));
    _delay_ms(1);
    ADCSRA |= freq;
    _delay_ms(1);
}

/**
 * 
 * @param ref
 */
void adc_select_ref(char ref) {
    ADMUX &= ~((1 << REFS1) | (1 << REFS0));
    _delay_ms(1);
    ADMUX |= (ref << 6);
    _delay_ms(1);
}

void adc_en() {
    ADCSRA |= (1 << ADEN);
}

void adc_int_en() {
    ADCSRA |= (1 << ADIE);
}

/**
 * 
 * @param ref
 * @param freq
 * @param ch
 */
void init_adc(char ref, char freq, char ch) {

    adc_select_channel(ch);

    adc_select_freq(freq);

    adc_select_ref(ref);

    adc_int_en();

    adc_en();

}

void adc_sc() {
    ADCSRA |= (1 << ADSC);
}

int adc_get_data() {
    return ADCW*step;
}