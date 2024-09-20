#include <avr/io.h>
#include "spi.h"
#include "DIO.h"

/**
 * 
 * @param mode
 */
void init_spi(int mode) {
    SPCR &= ~(1 << MSTR);
    SPCR |= (mode << MSTR);
    if (mode) {
        set_pin_dir('B', MOSI, OUT);
        set_pin_dir('B', SS, OUT);
        set_pin_dir('B', SCK, OUT);
    } else {
        set_pin_dir('B', MISO, OUT);
    }
    SPCR |= (1 << SPE);
}

void spi_int_en() {
    SPCR |= (1 << SPIE);
}

/**
 * 
 * @param data
 */
void spi_master_transmit_char(char data) {
    SPDR = data;
    while (!(SPSR & (1 << SPIF)));
}

char spi_slave_receive_char() {
    while (!(SPSR & (1 << SPIF)));
    return SPDR;
}

/**
 * 
 * @param data
 */
void spi_master_transmit_str(char* data) {
    for (int i = 0; data[i] != '\0'; i++) {
        spi_master_transmit_char(data [i]);
    }
}

char spi_master_receive_char() {
    spi_master_transmit_char(0x00);
    char data = SPDR;
    return data;
}

/**
 * 
 * @param order
 * @return 
 */
void spi_transmit_order(char order) {
    SPCR &= ~(1 << DORD);
    SPCR |= (order << DORD);
}

/**
 * 
 * @param clk
 */
void spi_clk_select(char clk) {
    //reset first
    SPCR &= ~(1 << SPR0 | 1 << SPR1);
    SPSR &= ~(1 << SPI2X);

    switch (clk) {
        case SPI_CLK_2://100
            SPSR |= (1 << SPI2X);
            break;
        case SPI_CLK_4://000
            break;
        case SPI_CLK_8://101
            SPCR |= (1 << SPR0);
            SPSR |= (1 << SPI2X);
            break;
        case SPI_CLK_16://001 or //010
            SPCR |= (1 << SPR0);
            break;
        case SPI_CLK_32://110
            SPCR |= (1 << SPR1);
            SPSR |= (1 << SPI2X);
            break;
        case SPI_CLK_64://111
            SPCR |= (1 << SPR0 | 1 << SPR1);
            SPSR |= (1 << SPI2X);
            break;
        case SPI_CLK_128://011
            SPCR |= (1 << SPR0 | 1 << SPR1);
            break;
    }
}

void spi_slave_select(char slave_pin, char slave_port) {

    set_pin(slave_port, slave_pin, LOW);

}

void spi_dissconnect_slave(char slave_pin, char slave_port) {

    set_pin(slave_port, slave_pin, HIGH);

}