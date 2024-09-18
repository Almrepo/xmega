#ifndef _XMEGA_TWI_H_
#define _XMEGA_TWI_H_
#include <avr/io.h>

class XmegaTwi
{

public:
    enum xmega_twi_clock_t
    {
        XMEGA_TWI_CLOCK_100000 = 100000UL,
        XMEGA_TWI_CLOCK_400000 = 400000UL
    };
    enum xmega_twi_type_oper_t
    {
        WRITE = 0,
        READ = 1
    };
    XmegaTwi(TWI_t *twi, xmega_twi_clock_t TWI_HZ, uint32_t cpu_hz);
    void xmega_twi_init(TWI_t *twi, xmega_twi_clock_t twi_clock, uint32_t cpu_hz);
    uint8_t twi_write_data(TWI_t *twi, uint8_t address, uint8_t register_address, uint8_t *data, uint16_t msg_length);
    uint8_t twi_write_data(TWI_t *twi, uint8_t address, uint8_t *data, uint16_t msg_length);
    uint8_t twi_read_data(TWI_t *twi, uint8_t address, uint8_t register_address, uint8_t *data, uint16_t msg_length);
};

#endif