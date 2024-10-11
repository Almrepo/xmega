#include "xmega_spi.h"

XmegaSpi::XmegaSpi(SPI_t *_spi, PORT_t *_port, uint8_t _pin_ss, SPI_PRESCALER_t _prescaler) : spi(_spi)
{
    xmega_spi_init();
}

void XmegaSpi::xmega_spi_init()
{
    xmega_spi_select_device();
    spi->CTRL = prescaler | SPI_MASTER_bm; // настройка SPI:делитель чатоты, мастер.
    spi->CTRL = SPI_ENABLE_bm;             // включение SPI
}
void XmegaSpi::xmega_spi_enable()
{
    spi->CTRL |=SPI_ENABLE_bm;
}
void XmegaSpi::xmega_spi_disable()
{
    spi->CTRL &=~SPI_ENABLE_bm;
}

//return 1 if the SPI is enabled, otherwise  0.
bool XmegaSpi::spi_is_enabled()
{
	return spi->CTRL & SPI_ENABLE_bm ? true : false;
}
void XmegaSpi::xmega_spi_select_ss()
{
    port->DIRSET = pin_ss;
}
void XmegaSpi::xmega_spi_transfer(uint8_t data)
{
spi->DATA=data;
while(!(spi->STATUS & SPI_IF_bm));
}

uint8_t XmegaSpi::xmega_spi_receive()
{
return spi->DATA;
}

void XmegaSpi::xmega_spi_select_device()
{
port->DIRSET= pin_ss;
port->OUTCLR=pin_ss;
}

void XmegaSpi::xmega_spi_deselect_device()
{
    port->OUTSET=pin_ss;
}
//включение прерывания, задавая его уровень
void XmegaSpi::xmega_spi_enable_interrupt(SPI_INTLVL_t level)
{
spi->INTCTRL=level;
}

//выключение прерывания SPI_INTLVL_OFF_gc
void XmegaSpi::xmega_spi_disable_interrupt(SPI_INTLVL_t level)
{
    spi->INTCTRL;
}