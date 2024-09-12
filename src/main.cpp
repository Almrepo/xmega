#include "main.h"

int main()
{
    XmegaClock clock(XmegaClock::XMEGA_TYPE_OS_IN, XmegaClock::XMEGA_OS_HZ_32);

    PORTC.DIRSET = PIN0_bm;
    while (1)
    {
        PORTC.OUTTGL = PIN0_bm;
        _delay_ms(1000);
    }

    return 0;
}