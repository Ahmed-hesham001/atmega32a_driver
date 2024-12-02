#include <avr/io.h>
#include "eeprom_i2c.h"
#include "my_i2c.h"

/**
 * 
 * @param address
 * @param data
 */
char eeprom_twi_write(int address, char data) {
    char status = 0;
    //start condition

    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    WAIT_TWINT;

    status = TWSR & 0xF8;

    if (status != I2C_STATUS_MT_START)
        return ERROR;

    TWDR = eeprom_address_w;
    TWCR = (1 << TWINT) | (1 << TWEN);

    WAIT_TWINT;

    status = TWSR & 0xF8;

    if (status != I2C_STATUS_MT_SLA_ACK)
        return ERROR;

    TWDR = address << 8;
    TWCR = (1 << TWINT) | (1 << TWEN);
    WAIT_TWINT
    TWDR = address;
    TWCR = (1 << TWINT) | (1 << TWEN);

    WAIT_TWINT;

    status = TWSR & 0xF8;

    if (status != I2C_STATUS_MT_DATA_ACK)
        return ERROR;

    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);

    WAIT_TWINT;

    status = TWSR & 0xF8;

    if (status != I2C_STATUS_MT_DATA_ACK)
        return ERROR;

    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);

    return 1;

}

/**
 * 
 * @param address
 * @return 
 */
char eeprom_twi_read(int address) {
    char status = 0;
    //start condition

    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    WAIT_TWINT;

    status = TWSR & 0xF8;

    if (status != I2C_STATUS_MT_START)
        return ERROR;

    TWDR = eeprom_address_w;
    TWCR = (1 << TWINT) | (1 << TWEN);

    WAIT_TWINT;

    status = TWSR & 0xF8;

    if (status != I2C_STATUS_MT_SLA_ACK)
        return ERROR;

    TWDR = address << 8;
    TWCR = (1 << TWINT) | (1 << TWEN);
    WAIT_TWINT
    TWDR = address;
    TWCR = (1 << TWINT) | (1 << TWEN);

    WAIT_TWINT;

    status = TWSR & 0xF8;

    if (status != I2C_STATUS_MT_DATA_ACK)
        return ERROR;

    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    WAIT_TWINT;

    status = TWSR & 0xF8;

    if (status != I2C_STATUS_MT_REP_START)
        return ERROR;

    TWDR = eeprom_address_r;
    TWCR = (1 << TWINT) | (1 << TWEN);

    WAIT_TWINT;

    status = TWSR & 0xF8;

    if (status != I2C_STATUS_MR_SLA_ACK)
        return ERROR;

    WAIT_TWINT;
    status = TWSR & 0xF8;

    if (status != I2C_STATUS_MR_DATA_NO_ACK)
        return ERROR;

    char data = TWDR;

    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);

    return data;

}
