/* 
 * File:   my_i2c.h
 * Author: Lenovo
 *
 * Created on September 14, 2024, 6:07 PM
 */
#ifndef MY_I2C_H
#define	MY_I2C_H
//STATUS CODES
// Master Transmitter (MT) mode
#define I2C_STATUS_MT_START         0x08  // Start condition transmitted
#define I2C_STATUS_MT_REP_START     0x10  // Repeated start condition transmitted
#define I2C_STATUS_MT_SLA_ACK       0x18  // SLA+W transmitted, ACK received
#define I2C_STATUS_MT_SLA_NO_ACK    0x20  // SLA+W transmitted, NACK received
#define I2C_STATUS_MT_DATA_ACK      0x28  // Data transmitted, ACK received
#define I2C_STATUS_MT_DATA_NO_ACK   0x30  // Data transmitted, NACK received
#define I2C_STATUS_MT_ARB_LOST      0x38  // Arbitration lost in SLA+W or data

// Master Receiver (MR) mode
#define I2C_STATUS_MR_ARB_LOST      0x38  // Arbitration lost in SLA+R or data
#define I2C_STATUS_MR_SLA_ACK       0x40  // SLA+R transmitted, ACK received
#define I2C_STATUS_MR_SLA_NO_ACK    0x48  // SLA+R transmitted, NACK received
#define I2C_STATUS_MR_DATA_ACK      0x50  // Data received, ACK returned
#define I2C_STATUS_MR_DATA_NO_ACK   0x58  // Data received, NACK returned

// Slave Transmitter (ST) mode
#define I2C_STATUS_ST_SLA_ACK       0xA8  // Own SLA+R received, ACK returned
#define I2C_STATUS_ST_ARB_LOST      0xB0  // Arbitration lost in SLA+RW
#define I2C_STATUS_ST_DATA_ACK      0xB8  // Data transmitted, ACK received
#define I2C_STATUS_ST_DATA_NO_ACK   0xC0  // Data transmitted, NACK received
#define I2C_STATUS_ST_LAST_DATA     0xC8  // Last data transmitted, ACK received

// Slave Receiver (SR) mode
#define I2C_STATUS_SR_SLA_ACK       0x60  // Own SLA+W received, ACK returned
#define I2C_STATUS_SR_ARB_LOST      0x68  // Arbitration lost in SLA+W
#define I2C_STATUS_SR_GEN_ACK       0x70  // General call received, ACK returned
#define I2C_STATUS_SR_GEN_ARB_LOST  0x78  // Arbitration lost in general call
#define I2C_STATUS_SR_DATA_ACK      0x80  // Data received, ACK returned
#define I2C_STATUS_SR_DATA_NO_ACK   0x88  // Data received, NACK returned
#define I2C_STATUS_SR_GEN_DATA_ACK  0x90  // General call data received, ACK returned
#define I2C_STATUS_SR_GEN_DATA_NO_ACK 0x98 // General call data received, NACK returned
#define I2C_STATUS_SR_STOP          0xA0  // Stop or repeated start condition received

// Miscellaneous states
#define I2C_STATUS_NO_INFO          0xF8  // No relevant state information
#define I2C_STATUS_BUS_ERROR        0x00  // Bus error due to illegal start/stop condition


/*
 REGISTERS:
 * TWBR ? TWI Bit Rate Register
 * TWCR ? TWI Control Register
 * TWSR ? TWI Status Register
 * TWDR ? TWI Data Register
 * TWAR ? TWI (Slave) Address Register
 
 */

#define ERROR   -1
#define TWI_GENERALL_ADDRESS        0x00

#define TWI_CLK_1       0
#define TWI_CLK_4       1
#define TWI_CLK_16      2
#define TWI_CLK_64      3

#define ENABLE_FUNCTION     TWCR = (1<<TWINT)| (1<<TWEN)


//wait for flag to be 1 (free to use data bus again)
#define WAIT_TWINT          while(!(TWCR & (1<<TWINT)))

void init_twi(char address);
void twi_clk_select(char clk);
void twi_int_en();
char twi_address_write(char address);
char twi_address_read(char address);


char twi_master_tans(char slave, char data);
char twi_master_rec(char slave);

char twi_master_tans_buffer(char slave_address, char* pdata, char arr_size);
char* twi_master_rec_buffer(char slave);



char twi_slave_trans(char data);
char twi_slave_rec();
void twi_slave_trans_buffer();
char twi_slave_rec_buffer(char* pdata, int arr_size);
#endif	/* MY_I2C_H */

