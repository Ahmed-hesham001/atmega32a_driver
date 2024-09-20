#include <avr/io.h>
#include "my_i2c.h"


////send start bit
//
//TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
//
////polling
//
//while (!(TWCR & (1 << TWINT)));
//
////read status reg
//
//code = TWSR & OxF8;

void init_twi(char address, char clk) {
    TWAR = my_address;
    TWBR = 18;
}

void twi_master_tans(char slave_command, char data) {
    //CREATE START CONDITION
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    //WAIT UNTIL OPERATION IS DONE
    while (!(TWCR & (1 << TWINT)));

    //read the status bits
    char status = TWSR & 0xF8;

    if (status != 0x08) {
        return ERROR;
    }

    TWDR = slave_command;

    TWCR = (1 << TWINT) | (1 << TWEN);
    
}