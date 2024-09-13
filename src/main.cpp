#include "main.h"

int main()
{
    XmegaClock clock(XmegaClock::XMEGA_TYPE_OS_IN, XmegaClock::XMEGA_OS_HZ_32);
    XmegaUsart usart(&USARTC0, &PORTC, PIN1_bm, PIN0_bm, 9600, 320000);
    PORTC.DIRSET = PIN0_bm;

    while (1)
    {
    }

    return 0;
}