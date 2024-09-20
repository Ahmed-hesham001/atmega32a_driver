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

void init_twi(char my_address) {
    TWAR = my_address;
    TWBR = 18;
}

/**
 * 
 * @param clk
 */
void twi_clk_select(char clk) {
    TWSR &= ~((1 << TWPS0) | (1 << TWPS1));

    switch (clk) {
        case (TWI_CLK_1):
            TWSR |= clk;
            break;
        case(TWI_CLK_4):
            TWSR |= clk;
            break;
        case(TWI_CLK_16):
            TWSR |= clk;
            break;
        case(TWI_CLK_64):
            TWSR |= clk;
            break;
    }
}

void twi_int_en() {
    TWCR |= (1 << TWIE);
}

/**
 * 
 * @param address
 * @return 
 */
char twi_address_write(char address) {
    address = (address << 1); // Shift left to make room for R/W bit
    address &= 0xFE; //1111 1110
    return address;
}

/**
 * 
 * @param address
 * @return 
 */
char twi_address_read(char address) {
    address = (address << 1); // Shift left to make room for R/W bit
    address |= 0x01; //0000 0001
    return address;
}

/**
 * 
 * @param slave_address
 * @param data
 * @return 
 */
char twi_master_tans(char slave_address, char data) {
    //CREATE START CONDITION
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    //WAIT UNTIL OPERATION IS DONE
    WAIT_TWINT;

    //read the status bits
    char status = TWSR & 0xF8;

    if (status != I2C_STATUS_MT_START) {
        return ERROR;
    }

    TWDR = slave_address;

    TWCR = (1 << TWINT) | (1 << TWEN);

    WAIT_TWINT;

    status = TWSR & 0xF8;

    if (status != I2C_STATUS_MT_SLA_ACK)
        return ERROR;

    TWDR = data;

    TWCR = (1 << TWINT) | (1 << TWEN);

    WAIT_TWINT;

    status = TWSR & 0xF8;

    if (status != I2C_STATUS_MT_DATA_ACK)
        return ERROR;

    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);

    while (TWCR & (1 << TWSTO)); // Wait until stop condition is executed

    return 1;

}

/**
 * 
 * @param slave
 * @return 
 */
char twi_master_rec(char slave) {
    char statuscode = 0;
    char data = 0;

    //CREATE START CONDITION
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    //WAIT UNTIL OPERATION IS DONE
    WAIT_TWINT;

    statuscode = TWSR & 0xF8;
    
    if (statuscode != I2C_STATUS_MT_START)
        return ERROR;
    
    TWDR = slave;
    
    TWCR = (1<<TWINT)|(1<<TWEN);
    
    WAIT_TWINT;
    
    statuscode = TWSR & 0xF8;
    
    if (statuscode != I2C_STATUS_MR_SLA_ACK)
        return ERROR;
    
    TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN);
    WAIT_TWINT;
    
    data = TWDR;
    
    statuscode = TWSR & 0xF8;
    
    if (statuscode!= I2C_STATUS_MR_DATA_ACK)
        return ERROR;
    

     TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);

    while (TWCR & (1 << TWSTO)); // Wait until stop condition is executed

    return data;
}

char twi_slave_rec(){
    char statuscode = 0;
    
    //1)ready to receive my address (enable function ORed with enable ack(TWEA) bit)
    ENABLE_FUNCTION | (1<< TWEA);
    WAIT_TWINT;
    
    //2)read status register
    statuscode = TWSR & 0xF8;
    
    //wait till acknowledge is sent to master then receive data
    if (statuscode == I2C_STATUS_SR_SLA_ACK || statuscode == I2C_STATUS_SR_GEN_ACK){
        //3)ready to receive data (set acknowledge enable)
        ENABLE_FUNCTION | (1<< TWEA);
        WAIT_TWINT;

        //4)read status register
        statuscode = TWSR & 0xF8;
        //check for error 
        if (statuscode != I2C_STATUS_SR_DATA_ACK && statuscode != I2C_STATUS_SR_GEN_DATA_ACK)
            return ERROR;
    }
    else{
        return ERROR;
    }
 
    //5)return data
    return TWDR;
    
}