/* 
 * File:   eeprom_i2c.h
 * Author: Lenovo
 *
 * Created on September 20, 2024, 8:46 PM
 */

#ifndef EEPROM_I2C_H
#define	EEPROM_I2C_H

#define eeprom_address_r 0xA0
#define eeprom_address_w 0xA1

char eeprom_twi_write(int address , char data);
char eeprom_twi_read(int address);

#endif	/* EEPROM_I2C_H */

