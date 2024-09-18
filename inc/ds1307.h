#ifndef _DS1307_H_
#define _DS1307_H_
#include "xmega_twi.h"

#define DS1307_ADDR 0xd0

class DS1307 : public XmegaTwi
{
public:
    enum
    {
        SECONDS_REGISTER = 0x00,
        MINUTES_REGISTER = 0x01,
        HOURS_REGISTER = 0x02,
        DAYOFWK_REGISTER = 0x03,
        DAYS_REGISTER = 0x04,
        MONTHS_REGISTER = 0x05,
        YEARS_REGISTER = 0x06
    };
    DS1307(TWI_t *twi, xmega_twi_clock_t TWI_HZ, uint32_t cpu_hz);
    uint8_t bcd_to_dec(uint8_t bcd);
    uint8_t dec_to_bcd(uint8_t dec);
};

#endif