#ifndef _XMEGA_SPI_H
#define _XMEGA_SPI_H

#include <avr/io.h>

class XmegaSpi
{
private:
    SPI_t *spi;
    PORT_t *port;
    uint8_t pin_ss;
    SPI_PRESCALER_t prescaler;

public:
    XmegaSpi(SPI_t *_spi, PORT_t *_port, uint8_t _pin_ss, SPI_PRESCALER_t _prescaler);
    void xmega_spi_init();
    void xmega_spi_select_ss();
    void xmega_spi_transfer(uint8_t data);
    void xmega_spi_enable_interrupt(SPI_INTLVL_t level);
    void xmega_spi_disable_interrupt(SPI_INTLVL_t level);
    void xmega_spi_select_device();
    void xmega_spi_deselect_device();
    uint8_t xmega_spi_receive();
    void xmega_spi_enable();
    void xmega_spi_disable();
    bool spi_is_enabled();
};

#endif