/* 
 * File:   eeprom.h
 * Author: Lenovo
 *
 * Created on September 20, 2024, 12:12 PM
 */

#ifndef EEPROM_H
#define	EEPROM_H

#define EE_READ     0x03       //Read data from memory array beginning at selected address
#define EE_WRITE    0x02       //Write data to memory array beginning at selected address
#define EE_WREN     0x06       //Set the write enable latch (enable write operations)
#define EE_RDSR     0x05       //Read STATUS register
#define EE_WRSR     0x01       //Write STATUS register


void eeprom_write_str(char* data, char address);
void eeprom_write_char(char data, char address);
char eeprom_read_char (char address);

#endif	/* EEPROM_H */

