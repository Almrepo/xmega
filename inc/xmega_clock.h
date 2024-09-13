#ifndef _XMEGA_CLOCK_H_
#define _XMEGA_CLOCK_H_
#include <avr/io.h>

class XmegaClock
{

public:
    // Тип тактового генератора (внешний или внутренний)
    enum xmega_type_os_t
    {
        XMEGA_TYPE_OS_IN = 0x00,
        XMEGA_TYPE_OS_EX = 0x01
    };
    // Частота тактового генератора
    enum xmega_os_hz_t
    {
        XMEGA_OS_HZ_2 = 0x2,
        XMEGA_OS_HZ_32 = 0x20
    };
    XmegaClock(xmega_type_os_t t_os, xmega_os_hz_t cpi_hz); // Конструктор класса с передачей типа и частоты тактового генератора
    void setInternalClockTo32MHz();                         // Установка 32MHz для внутреннего тактового генератора
    void setInternalClockTo2MHz();                          // Установка 2MHz для внутреннего тактового генератора
    void setExternalClockTo16MHz();                         // Установка 16MHz для внешнего тактового генератора
};
#endif
