#include "main.h"

int main()
{

    uint8_t real_sec, real_min, real_hours, real_dayofwk, real_days, real_mon, real_year; // переменные для вывода готовых времени и дат
    uint8_t data[] = {0, 0x12, 0x16, 0x03, 0x18, 0x09, 0x24};                             // задаем нужное время и дату (сек,мин,час,день недели,число,месяц,год)
    uint8_t bcd_data[7] = {};                                                             // массив переданных от ds1307 по twi
    XmegaClock clock(XmegaClock::XMEGA_TYPE_OS_IN, XmegaClock::XMEGA_OS_HZ_32);
    // XmegaIntLvl intlvl(XmegaIntLvl::XMEGA_INT_LVL_ALL_EN);                          //включение всех уровней прерывания
    DS1307 myi2c(&TWIE, XmegaTwi::XMEGA_TWI_CLOCK_100000, 32000000); // объект класса DS1307. Для запуска часов передать 0 в секундный регистор 0x00;

    XmegaUsart usartc0(&USARTC0, &PORTC, PIN3_bm, PIN2_bm, 9600, 32000000); // объект класса usart

    myi2c.twi_write_data(&TWIE, DS1307_ADDR, DS1307::SECONDS_REGISTER, data, 7); // записть нужного времени и даты в ds1307 + запуск
    _delay_us(10);

    while (1)
    {
        myi2c.twi_read_data(&TWIE, DS1307_ADDR, DS1307::SECONDS_REGISTER, &bcd_data[0], 7); // считываем время и дату из ds1307

        _delay_ms(1000);
        // real_sec = myi2c.bcd_to_dec(bcd_data[0]);   //преобразование bcd данные часов в dec
        real_min = myi2c.bcd_to_dec(bcd_data[1]);
        real_hours = myi2c.bcd_to_dec(bcd_data[2]);
        // real_dayofwk = myi2c.bcd_to_dec(bcd_data[0]);
        // real_days = myi2c.bcd_to_dec(bcd_data[4]);
        // real_mon = myi2c.bcd_to_dec(bcd_data[5]);
        // real_year = myi2c.bcd_to_dec(bcd_data[6]);

        // usartc0.xmega_usart_putchar(real_sec);
        usartc0.xmega_usart_putchar(real_min);
        usartc0.xmega_usart_putchar(real_hours);
        // usartc0.xmega_usart_putchar(real_dayofwk);
        // usartc0.xmega_usart_putchar(real_days);
        // usartc0.xmega_usart_putchar(real_mon);
        // usartc0.xmega_usart_putchar(real_year);
    }
    return 0;
}
