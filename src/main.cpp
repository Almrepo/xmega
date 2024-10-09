#include "main.h"

int main()
{
    XmegaClock clock(XmegaClock::XMEGA_TYPE_OS_IN, XmegaClock::XMEGA_OS_HZ_32);
    // sei();
    // XmegaIntLvl intlvl(XmegaIntLvl::XMEGA_INT_LVL_ALL_EN);

    XmegaAdc adc(&ADCB, &PORTB, PIN1_bm, ADC_REFSEL_INT1V_gc, ADC_PRESCALER_DIV128_gc, ADC_CH_INPUTMODE_SINGLEENDED_gc, ADC_CH_MUXPOS_PIN1_gc, &ADCB.CH0);
    XmegaUsart usart0(&USARTC0, &PORTC, PIN3_bm, PIN2_bm, 9600, 32000000);
    uint16_t adcRes = 0;
    float result = 0;
    // adc.xmega_adc_multiple_mode_start(ADC_SWEEP_0_gc);
    uint8_t h;
    uint8_t l;
    while (1)
    {

        adc.xmega_adc_single_mode_start(&ADCB.CH0);
        //   _delay_us(100);
        // adc.xmega_adc_single_mode_start(&ADCB.CH0);
        adcRes = adc.xmega_adc_read_value();
        // h = (uint8_t)(adcRes & 0xFF00) >> 8;
        // l = (uint8_t)(adcRes & 0x00FF);
        result = adc.xmega_adc_convert_to_result(adcRes, 1.0, 4096);

        //  result = adc.xmega_adc_get_result(1.0, (4096));

        usart0.xmega_usart_putchar(adc.convert_float_to_uint8(result));

        _delay_ms(1000);
    }

    return 0;
}