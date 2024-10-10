#ifndef _XMEGA_SPI_H
#define _XMEGA_SPI_H

#include <avr/io.h>

class XmegaAdc
{
private:
PORT_t* port;
uint8_t ss_pin;

public:
    void xmega_spi_init();
};

#endif