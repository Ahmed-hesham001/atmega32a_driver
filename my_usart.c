#include "my_usart.h"
#include "DIO.h"
#include "my_functions.h"

//INTIALIZATION STEPS
//SELECT CLOCK MODE
//SELECT BAUD RATE IF NEEDE
//SET DATA FRAME FORMATE
//ENABLE INTERRUPTS IF NEEDED
//ENABLE TX AND RX

/**
 * 
 * @param clk_mode ASYN DOUBLE_SPD_ASYN MASTER_SYN SLAVE_SYN
 * @param baud  INTEGER
 */
void init_uart(char clk_mode, int baud) {
    int UBRR;

    switch (clk_mode) {//SELECT CLOCK MODE
        case ASYN:
            UCSRA &= ~(1 << U2X);
            UCSRC = (UCSRC | (1 << URSEL)) & (~(1 << UMSEL));
            _delay_ms(5);
            UBRR = (F_CPU / 16.0 / baud) - 1;
            //    SET BAUD RATE
            UBRRH = UBRR >> 8;
            UBRRL = UBRR;
            break;
        case DOUBLE_SPD_ASYN:
            UCSRA |= (1 << U2X);
            UCSRC = (UCSRC | (1 << URSEL)) & (~(1 << UMSEL));
            _delay_ms(5);
            UBRR = (F_CPU / 8.0 / baud) - 1;
            //    SET BAUD RATE
            UBRRH = UBRR >> 8;
            UBRRL = UBRR;
            break;
        case MASTER_SYN:
            UCSRA &= ~(1 << U2X);
            UCSRC = (UCSRC | (1 << URSEL)) | (1 << UMSEL);
            set_pin_dir('B', XCK, OUT);
            _delay_ms(5);
            UBRR = (F_CPU / 2.0 / baud) - 1;
            //    SET BAUD RATE
            UBRRH = UBRR >> 8;
            UBRRL = UBRR;
            break;
        case SLAVE_SYN:
            UCSRA &= ~(1 << U2X);
            UCSRC = (UCSRC | (1 << URSEL)) | (1 << UMSEL);
            set_pin_dir('B', XCK, IN);
            _delay_ms(5);
            //            UBRR = (F_CPU / 2.0 / baud) - 1;
            //            //    SET BAUD RATE
            //            UBRRH = UBRR >> 8;
            //            UBRRL = UBRR;
            break;
    }


    //    SET THE DATA FRAME
    UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1); // 8-bit data, 1 stop bit

    //    INTERRUPT ENABLE
    //    UCSRB |= (1 << RXCIE);
    //    UCSRB |= (1 << TXCIE);
    //    UCSRB |= (1 << UDRIE);

    //    TX AND RX ENABLE
    UCSRB |= (1 << TXEN) | (1 << RXEN);
}

/**
 * 
 * @param data
 */
void uart_send_char(char data) {
    while (!(UCSRA & (1 << UDRE))); //polling to make sure there isn't an interrupt running

    UDR = data;
}

/**
 * 
 * @param pData
 */
void uart_send_str(char *pData) {
    for (int i = 0; pData[i] != '\0'; ++i) {
        uart_send_char(pData[i]);
        _delay_ms(10);
    }
}

char uart_receive_data() {
    UCSRB &= ~(1 << RXCIE);

    while (!(UCSRA & (1 << RXC)));

    char data = UDR;
    return data;
}

void uart_send_num(int num) {
    char str[16];
    itoa(num, str);
    uart_send_str(str);
}