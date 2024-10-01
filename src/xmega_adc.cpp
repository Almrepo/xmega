#include "xmega_adc.h"
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stddef.h>

void XmegaAdc::xmega_adc_clock()
{
    OSC.PLLCTRL = OSC_PLLSRC_RC32M_gc;
}

/*Выбор опорного напряжения
 * \param  ADC_REFSEL_INT1V_gc Внутреннее опорное напряжение 1.00В
 * \param  ADC_REFSEL_VCC_gc   Внутреннее напряжение VCC/1.6
 * \param  ADC_REFSEL_AREFA_gc Внешнее опорное напряжение с вывода AREF порта А
 * \param  ADC_REFSEL_AREFB_gc Внешнее опорное напряжение с вывода AREF порта B
 */
void XmegaAdc::xmega_adc_select_vref(ADC_t *adc, ADC_REFSEL_t ref_vcc)
{
    adc->REFCTRL = ref_vcc;
    
}

// Запуск одиночного преобразования в нужном канале
//Example for ADCA 0 chanel: &ADCA.CH0
void XmegaAdc::xmega_adc_single_start_chanel(ADC_CH_t *ch)
{
    ch->CTRL = ADC_CH_START_bm;
}

void XmegaAdc::xmega_adc_init(ADC_t *adc, ADC_REFSEL_t ref, ADC_PRESCALER_t prescaler, ADC_CH_t *ch)
{
    // PORTA.DIRCLR = PIN0_bm; // configure PORTA PIN0 as input

    adc->REFCTRL = ref;
    adc->PRESCALER = prescaler; //
    ch->CTRL = ADC_CH_START_bm; // выбор канала
    adc->CTRLA = ADC_ENABLE_bm; // включение ADC
}

// запуск автоматического преобразования в нужном канале
void XmegaAdc::xmega_adc_multiple_mode(ADC_t *adc)
{
    adc->CTRLB = ADC_FREERUN_bm; // включение многократного преобразования
    adc->EVCTRL = ADC_SWEEP0_bm; // выбор канала для автоматического преобразования: CH0
}

// Очистка конвеера АЦП.
void XmegaAdc::xmega_adc_clear(ADC_t *adc)
{
    adc->CTRLA = ADC_FLUSH_bm;
}

// загрузка калибровочных данных
uint8_t XmegaAdc::xmega_adc_get_calibration_data(uint8_t index)
{
    uint8_t result;
    /* Load the NVM Command register to read the calibration row. */
    NVM_CMD = NVM_CMD_READ_CALIB_ROW_gc;
    result = pgm_read_byte(index);
    /* Clean up NVM Command register. */
    NVM_CMD = NVM_CMD_NO_OPERATION_gc;
    return (result);
}

void XmegaAdc::xmega_adc_write_calibration_byte(ADC_t *adc)
{
    // ADCA.CALL = xmega_adc_get_calibration_data(offsetof(NVM_PROD_SIGNATURES_t, ADCACAL0));
    // ADCA.CALH = xmega_adc_get_calibration_data(offsetof(NVM_PROD_SIGNATURES_t, ADCACAL1));
    adc->CALL = xmega_adc_get_calibration_data(offsetof(NVM_PROD_SIGNATURES_t, ADCACAL0));
    adc->CALH = xmega_adc_get_calibration_data(offsetof(NVM_PROD_SIGNATURES_t, ADCACAL1));
}
