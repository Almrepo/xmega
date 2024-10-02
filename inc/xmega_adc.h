#ifndef _ADC_H_
#define _ADC_H_

#endif

class XmegaAdc
{

public:
        XmegaAdc(ADC_t *adc, ADC_REFSEL_t ref, ADC_PRESCALER_t prescaler, ADC_CH_t *ch);
    void xmega_adc_init(ADC_t *adc, ADC_REFSEL_t ref, ADC_PRESCALER_t prescaler, ADC_CH_t *);
    void xmega_adc_clock();
    void xmega_adc_select_vref(ADC_t *adc, ADC_REFSEL_t ref_vcc);
    void xmega_adc_single_mode_start(ADC_CH_t *);
    void xmega_adc_single_mode_stop(ADC_CH_t *ch);
    void xmega_adc_multiple_mode_start(ADC_t *, ADC_SWEEP_t);
    void xmega_adc_multiple_mode_stop(ADC_t *adc, ADC_SWEEP_t ch);
    void xmega_adc_clear(ADC_t *);
    uint8_t xmega_adc_get_calibration_data(uint8_t index);
    void xmega_adc_write_calibration_data(ADC_t *adc_name);
};
