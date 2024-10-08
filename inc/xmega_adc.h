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
    // volatile uint16_t adcResult = 0;

public:
    XmegaAdc(ADC_t *adc, PORT_t *port_name, uint8_t pinAdc_bm, ADC_REFSEL_t ref, ADC_PRESCALER_t prescaler, ADC_CH_t *ch);
    XmegaAdc(ADC_t *adc, ADC_REFSEL_t ref, ADC_PRESCALER_t prescaler, ADC_CH_t *ch);
    void xmega_adc_init(ADC_t *adc, PORT_t *port_name, uint8_t pinAdc_bm, ADC_REFSEL_t ref, ADC_PRESCALER_t prescaler, ADC_CH_t *);
    void xmega_adc_init(ADC_t *adc, ADC_REFSEL_t ref, ADC_PRESCALER_t prescaler, ADC_CH_t *ch);
    void xmega_adc_clock();
    void xmega_adc_select_vref(ADC_t *adc, ADC_REFSEL_t ref_vcc);
    void xmega_adc_single_mode_start(ADC_t *, ADC_CH_t *);
    void xmega_adc_single_mode_stop(ADC_CH_t *ch);
    void xmega_adc_multiple_mode_start(ADC_t *, ADC_SWEEP_t);
    void xmega_adc_multiple_mode_stop(ADC_t *adc, ADC_SWEEP_t ch);
    void xmega_adc_clear(ADC_t *);
    uint16_t xmega_adc_read_result(ADC_CH_t *ch);
    uint8_t xmega_adc_read_calibration_data(uint8_t index);
    void xmega_adc_write_calibration_data(ADC_t *adc_name);
    float xmega_adc_convert_result(uint16_t adcRes, float vref, uint16_t adcBit);
    uint8_t convert_float_to_uint8(float value);
    float xmega_adc_get_result(ADC_CH_t *ch, float vref, uint16_t adcBit);
    void xmega_adc_write_cmp_value(ADC_t *adc, uint16_t value);
};
#endif