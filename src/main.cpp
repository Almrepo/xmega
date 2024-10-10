#include "main.h"
XmegaUsart usart0(&USARTC0, &PORTC, PIN3_bm, PIN2_bm, 9600, 32000000);
XmegaAdc adc(&ADCB, &PORTB, PIN1_bm, ADC_REFSEL_INT1V_gc, ADC_PRESCALER_DIV128_gc, ADC_CH_INPUTMODE_SINGLEENDED_gc, ADC_CH_MUXPOS_PIN1_gc, &ADCB.CH0);


uint16_t adcRes = 0;
int main()
{
    XmegaClock clock(XmegaClock::XMEGA_TYPE_OS_IN, XmegaClock::XMEGA_OS_HZ_32);
    sei();
    XmegaIntLvl intlvl(XmegaIntLvl::XMEGA_INT_LVL_MED_EN);

    adc.xmega_adc_interrupt_enable(ADC_CH_INTMODE_BELOW_gc, ADC_CH_INTLVL_MED_gc);
    
    
    float result = 0;
    // adc.xmega_adc_multiple_mode_start(ADC_SWEEP_0_gc);
 //  adcRes= adc.xmega_adc_get_result(1.0,4096);
 //adc.xmega_adc_write_cmp_value(adcRes);
     ADCB.CMPL = 0x00;
     ADCB.CMPH = 0x22; //~0,1V
    while (1)
    {
        

       adc.xmega_adc_single_mode_start(&ADCB.CH0);
        _delay_us(100);
        adcRes = adc.xmega_adc_read_value_by_interrupt();

        result = adc.xmega_adc_convert_value_to_result(adcRes, 1.0, 4096);

        //  result = adc.xmega_adc_get_result(1.0, 4096);

        usart0.xmega_usart_putchar(adc.convert_float_to_uint8(result));

        _delay_ms(1000);
    }

    return 0;
}
ISR(ADCB_CH0_vect)
{
    usart0.xmega_usart_putchar(0x00);
    // ADCB.CH0.INTFLAGS = ADC_CH_CHIF_bm;
}