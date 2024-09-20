#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "eeprom.h"
#include "spi.h"
#include "DIO.h"


/**
 * 
 * @param data
 * @param address
 */
void eeprom_write_char(char data, char address) {

    set_pin('B', SS, HIGH);
    set_pin('B', SS, LOW);

    spi_master_transmit_char(EE_WREN);

    set_pin('B', SS, HIGH);
    _delay_ms(5);
    set_pin('B', SS, LOW);

    spi_master_transmit_char(EE_WRITE);

    spi_master_transmit_char(address);

    spi_master_transmit_char(data);

    set_pin('B', SS, HIGH);
    _delay_ms(5);
}

/**
 * 
 * @param data
 * @param address
 */
void eeprom_write_str(char* data, char address) {

    set_pin('B', SS, HIGH);
    set_pin('B', SS, LOW);

    spi_master_transmit_char(EE_WREN);

    set_pin('B', SS, HIGH);
    _delay_ms(5);
    set_pin('B', SS, LOW);

    spi_master_transmit_char(EE_WRITE);

    spi_master_transmit_char(address);

    for (int i = 0; data[i] != '\0'; i++) {
        spi_master_transmit_char(data[i]);
    }

    set_pin('B', SS, HIGH);
    _delay_ms(5);
}

/**
 * 
 * @param address
 * @return 
 */
char eeprom_read_char (char address){ 
    set_pin('B', SS, HIGH);
    set_pin('B', SS, LOW);
    
    spi_master_transmit_char(EE_READ);
    
    spi_master_transmit_char(address);
    
    char data = spi_master_receive_char();
    
    set_pin('B', SS, HIGH);
    
    return data;
}