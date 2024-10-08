#include "main.h"
uint8_t convert_float_to_uint8(float value)
{
    return (uint8_t)(value * 100);
}
int main()
{
    XmegaClock clock(XmegaClock::XMEGA_TYPE_OS_IN, XmegaClock::XMEGA_OS_HZ_32);

    // XmegaIntLvl intlvl(XmegaIntLvl::XMEGA_INT_LVL_ALL_EN);
    XmegaAdc adc(&ADCB, ADC_REFSEL_INT1V_gc, ADC_PRESCALER_DIV256_gc, &ADCB.CH0);
    // adc.xmega_adc_multiple_mode_start(&ADCB, ADC_SWEEP_0_gc);
    adc.xmega_adc_single_mode_start(&ADCB, &ADCB.CH0);
    XmegaUsart usart0(&USARTC0, &PORTC, PIN3_bm, PIN2_bm, 9600, 32000000);
    uint16_t adcRes = 0;
    float result = 0;
    uint8_t result_to_usart;
    // uint8_t h, l;
    // h = ((adcRes & 0xFF00) >> 8);
    // l = (adcRes & 0x00FF);
    result_to_usart = adc.xmega_adc_read_offset(&ADCB, &ADCB.CH0, ADC_CH_MUXPOS_PIN2_gc);
    while (1)
    {

        // adcRes = adc.xmega_adc_read_result(&ADCB.CH0);
        // result = adc.xmega_adc_convert_result(adcRes, 1.0, (4096 +108));
        // result = adc.xmega_adc_get_result(&ADCB.CH0, 1.0, (4096 +108));

        //  usart0.xmega_usart_putchar(convert_float_to_uint8(result));
        usart0.xmega_usart_putchar(result_to_usart);

        _delay_ms(1000);
    }

    return 0;
}