#include "xmega_adc.h"
// Конструктор с инициализацией ADC с внешним контролируемым сигналом
XmegaAdc::XmegaAdc(ADC_t *adc, PORT_t *port_name, uint8_t pinAdc_bm, ADC_REFSEL_t ref, ADC_PRESCALER_t prescaler, ADC_CH_t *ch)
{
    xmega_adc_init(adc, port_name, pinAdc_bm, ref, prescaler, ch);
}

// Конструктор с инициализацией ADC с внутренним контролируемым сигналом
XmegaAdc::XmegaAdc(ADC_t *adc, ADC_REFSEL_t ref, ADC_PRESCALER_t prescaler, ADC_CH_t *ch)
{
    xmega_adc_init(adc, ref, prescaler, ch);
}

// Инициализация ADC с внутренним контролируемым сигналом
//  Example: adc(&ADCA, ADC_REFSEL_AREFA_gc, ADC_PRESCALER_DIV128_gc, &ADCA.CH0);
void XmegaAdc::xmega_adc_init(ADC_t *adc, ADC_REFSEL_t ref, ADC_PRESCALER_t prescaler, ADC_CH_t *ch)
{

    adc->REFCTRL = ref;
    adc->PRESCALER = prescaler; //
    adc->CTRLB = ADC_RESOLUTION_12BIT_gc;
    ch->CTRL = ADC_CH_INPUTMODE_SINGLEENDED_gc; // Внешний положительный (несимметричный) входной сигнал
    ch->MUXCTRL = ADC_CH_MUXPOS_PIN1_gc;
    xmega_adc_write_calibration_data(adc);
    adc->CTRLA |= ADC_ENABLE_bm; // включение ADC

    _delay_ms(10);
}

// Инициализация ADC с внешним контролируемым сигналом
//  Example: adc(&ADCA,&PORTA,PIN1_bm, ADC_REFSEL_AREFA_gc, ADC_PRESCALER_DIV128_gc, &ADCA.CH0);
void XmegaAdc::xmega_adc_init(ADC_t *adc, PORT_t *port_name, uint8_t pinAdc_bm, ADC_REFSEL_t ref, ADC_PRESCALER_t prescaler, ADC_CH_t *ch)
{
    port_name->DIRCLR = pinAdc_bm; // configure PORT PIN as input
    adc->REFCTRL = ref;
    adc->PRESCALER = prescaler; //
    adc->CTRLB = ADC_RESOLUTION_12BIT_gc;
    ch->CTRL = ADC_CH_INPUTMODE_SINGLEENDED_gc; // Внешний положительный (несимметричный) входной сигнал
    ch->MUXCTRL = ADC_CH_MUXPOS_PIN1_gc;
    xmega_adc_write_calibration_data(adc);
    adc->CTRLA |= ADC_ENABLE_bm; // включение ADC

    _delay_ms(10);
}

void XmegaAdc::xmega_adc_clock()
{
    OSC.PLLCTRL = OSC_PLLSRC_RC32M_gc;
}

/** Выбор опорного напряжения
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
// Example for ADCA 0 chanel: &ADCA.CH0
void XmegaAdc::xmega_adc_single_mode_start(ADC_t *adc, ADC_CH_t *ch)
{
    adc->CTRLB &= ~ADC_FREERUN_bm;
    ch->CTRL |= ADC_CH_START_bm;
}
// Остановка одиночного преобразования в нужном канале
// Example for ADCA 0 chanel: &ADCA.CH0
void XmegaAdc::xmega_adc_single_mode_stop(ADC_CH_t *ch)
{
    ch->CTRL &= ~ADC_CH_START_bm;
}

/**  Запуск автоматического преобразования в нужном канале
 * \param ADC_SWEEP_0_gc   enable ADC Channel 0
 * \param  ADC_SWEEP_01_gc enable ADC Channel 0,1
 * \param  ADC_SWEEP_012_gc enable ADC Channel 0,1,2
 * \param ADC_SWEEP_0123_gc enable ADC Channel 0,1,2,3
 */
void XmegaAdc::xmega_adc_multiple_mode_start(ADC_t *adc, ADC_SWEEP_t ch)
{
    adc->CTRLB |= ADC_FREERUN_bm; // включение многократного преобразования
    adc->EVCTRL = ch;             // включение нужных каналов
}
/** Остановка  автоматического преобразования
 * \param ADC_SWEEP_0_gc   disable ADC Channel 0
 * \param  ADC_SWEEP_01_gc disable ADC Channel 0,1
 * \param  ADC_SWEEP_012_gc disable ADC Channel 0,1,2
 * \param ADC_SWEEP_0123_gc disable ADC Channel 0,1,2,3
 */
void XmegaAdc::xmega_adc_multiple_mode_stop(ADC_t *adc, ADC_SWEEP_t ch)
{
    adc->CTRLB &= ~ADC_FREERUN_bm; // выключение многократного преобразования
    adc->EVCTRL &= ~ch;            // выключение каналов
}
// Запись числа в регистр сравнения
void XmegaAdc::xmega_adc_write_cmp_value(ADC_t *adc, uint16_t value)
{
    adc->CMPH = (uint8_t)(value & 0xFF00) >> 8;
    adc->CMPL = (uint8_t)(value & 0x00FF);
}
// Очистка конвеера АЦП.
void XmegaAdc::xmega_adc_clear(ADC_t *adc)
{
    adc->CTRLA = ADC_FLUSH_bm;
}
// Считываем сырой результат ADC
// Example: &ADCA.CH0
uint16_t XmegaAdc::xmega_adc_read_result(ADC_CH_t *ch)
{
    uint16_t adcResult = 0;

    while (!(ch->INTFLAGS))
        ;
    ch->INTFLAGS = ADC_CH_CHIF_bm;
    adcResult = ch->RES;
    return adcResult;
}

// Конвертация результата uint16_t  ADC в реальное число float . Аргументы : считанные данные с ADC, опорное напряжение в float формате , число отрезков-4096 для 12 бит(битность adc).
float XmegaAdc::xmega_adc_convert_result(uint16_t adcResult, float vref, uint16_t adcBit)
{
    float Result = 0;
    return (Result * vref / adcBit);
}

// Конвертация числа типа  float  в число типа uint8_t (*100 - два знака после запятой).
uint8_t XmegaAdc::convert_float_to_uint8(float value)
{
    return (uint8_t)(value * 100);
}

// Получение готового числа. Аргументы : канал (ADCa_b.CHn), опорное напряжение в float формате , число отрезков(битность adc).
float XmegaAdc::xmega_adc_get_result(ADC_CH_t *ch, float vref, uint16_t adcBit)
{
    float adcResult;
    for (uint8_t i = 0; i < 5; i++) // Усреднение
    {
        ch->CTRL |= ADC_CH_START_bm;
        while (!(ch->INTFLAGS))
            ;
        ch->INTFLAGS = ADC_CH_CHIF_bm;
        adcResult += ch->RES;
    }
    adcResult = adcResult / 5;            // Из 5 полученных результатов, ,берем среднее
    return ((adcResult * vref) / adcBit); // перевод в реальное значение
}

// Загрузка калибровочных данных
uint8_t XmegaAdc::xmega_adc_read_calibration_data(uint8_t index)
{
    uint8_t result;
    /* Load the NVM Command register to read the calibration row. */
    NVM_CMD = NVM_CMD_READ_CALIB_ROW_gc;
    result = pgm_read_byte(index);
    /* Clean up NVM Command register. */
    NVM_CMD = NVM_CMD_NO_OPERATION_gc;
    return (result);
}
// Запись колибровочных данных
void XmegaAdc::xmega_adc_write_calibration_data(ADC_t *adc)
{
    adc->CALL = xmega_adc_read_calibration_data(offsetof(NVM_PROD_SIGNATURES_t, ADCACAL0));
    adc->CALH = xmega_adc_read_calibration_data(offsetof(NVM_PROD_SIGNATURES_t, ADCACAL1));
}


   
