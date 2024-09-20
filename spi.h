/* 
 * File:   spi.h
 * Author: Lenovo
 *
 * Created on September 13, 2024, 6:10 PM
 */

#ifndef SPI_H
#define	SPI_H

#define MASTER      1
#define SLAVE       0

#define SPI_CLK_2       0
#define SPI_CLK_4       1
#define SPI_CLK_8       2
#define SPI_CLK_16      3
#define SPI_CLK_32      4
#define SPI_CLK_64      5
#define SPI_CLK_128     6

#define MOSI        PB5
#define MISO        PB6
#define SCK         PB7
#define SS          PB4

void init_spi(int mode);
void spi_int_en();
void spi_master_transmit_char(char data);
char spi_slave_receive_char();
void spi_master_transmit_str(char* data);
void spi_clk_select(char clk);
void spi_slave_select (char slave_pin , char slave_port);
void spi_dissconnect_slave (char slave_pin , char slave_port);
char spi_master_receive_char();
void spi_transmit_order(char order);

//but i love the small things that you do are what remind me why i fell for you

#endif	/* SPI_H */

