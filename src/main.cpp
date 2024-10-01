#include "main.h"

int main()
{
    XmegaClock clock(XmegaClock::XMEGA_TYPE_OS_IN, XmegaClock::XMEGA_OS_HZ_32);
    XmegaIntLvl intlvl(XmegaIntLvl::XMEGA_INT_LVL_ALL_EN);
    XmegaAdc adc(&ADCA, ADC_REFSEL_AREFA_gc, ADC_PRESCALER_DIV128_gc,&ADCA.CH0 );
  

    while (1)
    {
    }

    return 0;
}