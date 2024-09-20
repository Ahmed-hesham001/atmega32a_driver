#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


#include "DIO.h"
#include "my_usart.h"

/**
 * 
 * @param mode
 * @param baud_rate
 */
void init_usart(char mode , int baud_rate){
//    usart_select_mode(mode);
    UCSRC |= (1<<URSEL)|(1<<UMSEL);
    UCSRC |= (1<<URSEL)|(1<<USBS);
    usart_select_baud_rate(baud_rate);
    set_pin_dir('B',PB0,IN);
    UCSRB |= ((1<<RXEN)|(1<<TXEN));
}
/**
 * 
 * @param mode
 */
void usart_select_mode(char mode){
//    char var = UCSRC;
//    var |= (1<<URSEL);
//    var &= ~(1<<UMSEL);
//    var |= mode;
//    UCSRC = var;
    
    
}
/**
 * 
 * @param baud_rate
 */
void usart_select_baud_rate(int baud_rate){
    short int temp = (F_CPU/2.0/baud_rate)-1;
    UBRRL = temp;
    UBRRH = temp>>8;
}

void usart_send_data (char data){
    while(!(UCSRA&(1<<UDRE)));
    UDR = data;
}

char usart_receive_data (){
    while(!(UCSRA&(1<<RXC)));
    return UDR ;
}