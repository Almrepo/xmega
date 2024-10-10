#ifndef _ADC_H_
#define _ADC_H_
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stddef.h>
#include "xmega_adc.h"
#include <stddef.h>
#include <util/delay.h>
class XmegaAdc
{
private:
    volatile uint16_t adcResult = 0;

    ADC_t *adc;       // ADCA
    ADC_CH_t *chanel; // ADCA.CH0
    PORT_t *portAdc;  // PORTA
    uint8_t pinAdc;   // PIN1_bm
    ADC_REFSEL_t Vref;
    ADC_PRESCALER_t prescaler;
    ADC_SWEEP_t chanel_mode;
    ADC_CH_MUXPOS_t pin_muxpos;
    ADC_CH_INPUTMODE_t source_signal;

public:
    XmegaAdc(ADC_t *adc, PORT_t *port_name, uint8_t pinAdc_bm, ADC_REFSEL_t Vref, ADC_PRESCALER_t prescaler, ADC_CH_INPUTMODE_t signal, ADC_CH_MUXPOS_t pin_muxpos, ADC_CH_t *chanel);
    XmegaAdc(ADC_t *adc, ADC_REFSEL_t Vref, ADC_PRESCALER_t prescaler, ADC_CH_INPUTMODE_t signal, ADC_CH_MUXPOS_t pin_muxpos, ADC_CH_t *chanel);
    void xmega_adc_init();
    void xmega_adc_clock();
    void xmega_adc_select_vref(ADC_REFSEL_t ref_vcc);
    void xmega_adc_single_mode_start(ADC_CH_t *);
    void xmega_adc_single_mode_stop(ADC_CH_t *ch);
    void xmega_adc_multiple_mode_start(ADC_SWEEP_t);
    void xmega_adc_multiple_mode_stop(ADC_SWEEP_t ch);
    void xmega_adc_clear();
    uint16_t xmega_adc_read_value();
    uint8_t xmega_adc_read_calibration_data(uint8_t index);
    void xmega_adc_write_calibration_data();
    float xmega_adc_convert_value_to_result(uint16_t adcRes, float vref, uint16_t adcBit);
    uint8_t convert_float_to_uint8(float value);
    float xmega_adc_get_result(float vref, uint16_t adcBit);
    void xmega_adc_write_cmp_value(uint16_t value);
    void xmega_adc_interrupt_enable(ADC_CH_INTMODE_t mode, ADC_CH_INTLVL_t level);
    uint8_t xmega_adc_read_offset(ADC_t *adc, ADC_CH_t *adc_ch, ADC_CH_MUXPOS_t muxpos_pin);
    uint16_t xmega_adc_read_value_by_interrupt();
};
#endif