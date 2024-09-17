#include "main.h"

int main()
{
    // uint8_t real_data[] = {0, 0, 0};
    uint8_t date[] = {0, 1, 2, 3};
    uint8_t cur_date[4] = {};
    XmegaClock clock(XmegaClock::XMEGA_TYPE_OS_IN, XmegaClock::XMEGA_OS_HZ_32);
    // XmegaIntLvl intlvl(XmegaIntLvl::XMEGA_INT_LVL_ALL_EN);
    DS1307 myi2c(&TWIE, XmegaTwi::XMEGA_TWI_CLOCK_100000, 32000000);

    myi2c.twi_write_data(&TWIE, DS1307_ADDR, date, 4);
    _delay_us(100);

    myi2c.twi_read_data(&TWIE, DS1307_ADDR, DS1307::SECONDS_REGISTER, cur_date, 4);
    
    while (1)
    {

        // for (uint8_t i = 0; i < 3; i++)
        // {
        //     myi2c.twi_read_data(&TWIE, DS1307_ADDR, DS1307::SECONDS_REGISTER, cur_date, 3);

        //     _delay_ms(5000);
        // }
    }
    return 0;
}
