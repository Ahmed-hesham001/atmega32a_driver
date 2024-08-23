/* 
 * File:   adc.h
 * Author: Lenovo
 *
 * Created on August 23, 2024, 5:37 AM
 */

#ifndef ADC_H
#define	ADC_H

#define V_REF      0
#define AVCC       1
#define V_INTERNAL 3

#define ch0 0
#define ch1 1
#define ch2 2
#define ch3 3
#define ch4 4
#define ch5 5
#define ch6 6
#define ch7 7


#define div_factor2 0
#define div_factor4 2
#define div_factor8 3
#define div_factor16 4
#define div_factor32 5
#define div_factor64 6
#define div_factor128 7

#define check_flag       while (!(ADCSRA & (1<<ADIF)))

#define step 4.887585532746823069403714565

void adc_select_channel(char ch);
void adc_select_freq(char freq);
void adc_select_ref(char ref);
void adc_en();
void adc_int_en();
void adc_sc();
int adc_get_data();
void init_adc(char ref, char freq, char ch);

#endif	/* ADC_H */

