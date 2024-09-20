/* 
 * File:   my_i2c.h
 * Author: Lenovo
 *
 * Created on September 14, 2024, 6:07 PM
 */

#ifndef MY_I2C_H
#define	MY_I2C_H

#define my_address  0x07
#define ERROR -1


void init_twi(char address, char clk);
void twi_master_tans(char slave , char data);
char twi_master_rec(char slave);

void twi_master_tans_buffer(char slave,char *pData);
char* twi_master_rec_buffer(char slave);

void twi_slave_trans();
char twi_slave_rev();
void twi_slave_trans();

#endif	/* MY_I2C_H */

