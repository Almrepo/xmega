#include "main.h"

int main()
{
    XmegaClock clock(XmegaClock::XMEGA_TYPE_OS_IN, XmegaClock::XMEGA_OS_HZ_32);
    XmegaIntLvl intlvl(XmegaIntLvl::XMEGA_INT_LVL_ALL_EN);
    XmegaAdc adc;
    //adc.xmega_adc_init(&ADCA,A);

    while (1)
    {
        
       
    }

    return 0;
}