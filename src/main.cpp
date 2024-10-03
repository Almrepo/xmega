#include "main.h"

int main()
{
    XmegaClock clock(XmegaClock::XMEGA_TYPE_OS_IN, XmegaClock::XMEGA_OS_HZ_32);
    // XmegaIntLvl intlvl(XmegaIntLvl::XMEGA_INT_LVL_ALL_EN);
    XmegaAdc adc(&ADCA, ADC_REFSEL_VCC_gc, ADC_PRESCALER_DIV256_gc, &ADCA.CH0);
    // adc.xmega_adc_multiple_mode_start(&ADCA, ADC_SWEEP_0_gc);
     adc.xmega_adc_single_mode_start(&ADCA.CH0);
    XmegaUsart usart0(&USARTC0, &PORTC, PIN3_bm, PIN2_bm, 9600, 32000000);
    uint16_t adcRes = 0;
    // adcRes = adc.xmega_adc_read_result(&ADCA.CH0);
    uint8_t h, l;
    h = ((adcRes & 0xFF00) >> 8);
    l = (adcRes & 0x00FF);
    

    while (1)
    {

        adcRes = adc.xmega_adc_read_result(&ADCA.CH0);
        _delay_ms(1000);
        h = ((adcRes & 0xFF00) >> 8);
        l = (adcRes & 0x00FF);
        usart0.xmega_usart_putchar(h);
        usart0.xmega_usart_putchar(l);
        
    }

    return 0;
}