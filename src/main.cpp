#include "main.h"
uint8_t convert_float_to_uint8(float value)
{
    return (uint8_t)(value * 100);
}
int main()
{
    XmegaClock clock(XmegaClock::XMEGA_TYPE_OS_IN, XmegaClock::XMEGA_OS_HZ_32);
    // XmegaIntLvl intlvl(XmegaIntLvl::XMEGA_INT_LVL_ALL_EN);
    XmegaAdc adc(&ADCB, ADC_REFSEL_VCC_gc, ADC_PRESCALER_DIV256_gc, &ADCB.CH0);
    adc.xmega_adc_multiple_mode_start(&ADCB, ADC_SWEEP_0_gc);
    //  adc.xmega_adc_single_mode_start(&ADCB.CH0);
    XmegaUsart usart0(&USARTC0, &PORTC, PIN3_bm, PIN2_bm, 9600, 32000000);
    float adcRes = 0;

    uint8_t real, real2;
    // uint8_t h, l;
    // h = ((adcRes & 0xFF00) >> 8);
    // l = (adcRes & 0x00FF);

    while (1)
    {

        adcRes = adc.xmega_adc_read_result(&ADCB.CH0);

        real = convert_float_to_uint8(adcRes);
        // temp = adcRes * (1.88f / 4096);
        //  real = convert_float_to_uint8(temp);

        usart0.xmega_usart_putchar(real);

        _delay_ms(1000);
        // h = ((adcRes & 0xFF00) >> 8);
        // l = (adcRes & 0x00FF);
        // usart0.xmega_usart_putchar(h);
        // usart0.xmega_usart_putchar(l);
    }

    return 0;
}