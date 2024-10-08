#include "xmega_adc.h"

// Конструктор с инициализацией ADC с внешним контролируемым сигналом
// Example: adc(&ADCA, &PORTA,PIN1_bm,ADC_REFSEL_AREFA_gc, ADC_PRESCALER_DIV128_gc, &ADCA.CH0
XmegaAdc::XmegaAdc(ADC_t *_adc, PORT_t *_portAdc, uint8_t _pinAdc, ADC_REFSEL_t _Vref, ADC_PRESCALER_t _prescaler, ADC_CH_INPUTMODE_t _source_signal, ADC_CH_MUXPOS_t _pin_muxpos, ADC_CH_t *_chanel)
    : adc(_adc), portAdc(_portAdc), pinAdc(_pinAdc), Vref(_Vref), prescaler(_prescaler), source_signal(_source_signal), pin_muxpos(_pin_muxpos), chanel(_chanel)
{

    portAdc->DIRCLR = pinAdc;
    xmega_adc_init();
}

// Конструктор с инициализацией ADC с внутренним контролируемым сигналом
XmegaAdc::XmegaAdc(ADC_t *_adc, ADC_REFSEL_t _Vref, ADC_PRESCALER_t _prescaler, ADC_CH_INPUTMODE_t _source_signal, ADC_CH_MUXPOS_t _pin_muxpos, ADC_CH_t *_chanel)
    : adc(_adc), Vref(_Vref), prescaler(_prescaler), source_signal(_source_signal), pin_muxpos(_pin_muxpos), chanel(_chanel)
{
    xmega_adc_init();
}

// Инициализация ADC с внутренним контролируемым сигналом
void XmegaAdc::xmega_adc_init()
{

    adc->REFCTRL = Vref;
    adc->PRESCALER = prescaler; //
    adc->CTRLB = ADC_RESOLUTION_12BIT_gc;
    chanel->CTRL = source_signal; // Внешний положительный (несимметричный) входной сигнал
    chanel->MUXCTRL = pin_muxpos;
    xmega_adc_write_calibration_data();
    adc->CTRLA |= ADC_ENABLE_bm; // включение ADC

    _delay_us(2);
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
void XmegaAdc::xmega_adc_select_vref(ADC_REFSEL_t ref)
{

    adc->REFCTRL = ref;
}

// Запуск одиночного преобразования в нужном канале
// Example for ADCA 0 chanel: &ADCA.CH0
void XmegaAdc::xmega_adc_single_mode_start(ADC_CH_t *ch)
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
void XmegaAdc::xmega_adc_multiple_mode_start(ADC_SWEEP_t ch)
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
void XmegaAdc::xmega_adc_multiple_mode_stop(ADC_SWEEP_t ch)
{
    adc->CTRLB &= ~ADC_FREERUN_bm; // выключение многократного преобразования
    adc->EVCTRL &= ~ch;            // выключение каналов
}
// Запись числа в регистр сравнения
void XmegaAdc::xmega_adc_write_cmp_value(uint16_t value)
{
    adc->CMPH = (uint8_t)(value & 0xFF00) >> 8;
    adc->CMPL = (uint8_t)(value & 0x00FF);
}
// Очистка конвеера АЦП.
void XmegaAdc::xmega_adc_clear()
{
    adc->CTRLA = ADC_FLUSH_bm;
}
// Считываем сырой результат ADC
// Example: &ADCA.CH0
uint16_t XmegaAdc::xmega_adc_read_result()
{
    uint16_t adcResult = 0;

    while (!(chanel->INTFLAGS))
        ;
    chanel->INTFLAGS = ADC_CH_CHIF_bm;
    adcResult = chanel->RES;
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
float XmegaAdc::xmega_adc_get_result(float vref, uint16_t adcBit)
{
    float adcResult;
    for (uint8_t i = 0; i < 5; i++) // Усреднение
    {
        chanel->CTRL |= ADC_CH_START_bm;
        while (!(chanel->INTFLAGS))
            ;
        chanel->INTFLAGS = ADC_CH_CHIF_bm;
        adcResult += chanel->RES;
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
void XmegaAdc::xmega_adc_write_calibration_data()
{
    adc->CALL = xmega_adc_read_calibration_data(offsetof(NVM_PROD_SIGNATURES_t, ADCACAL0));
    adc->CALH = xmega_adc_read_calibration_data(offsetof(NVM_PROD_SIGNATURES_t, ADCACAL1));
}
// Настройка и включение прерывания. Mode-выбор причины прерывания, level-уровень прерывания.
void XmegaAdc::xmega_adc_interrupt_enable(ADC_CH_INTMODE_t mode, ADC_CH_INTLVL_t level)
{
    chanel->INTCTRL = mode | level;
}

// Считывание значения offset. Нужный PIN (ADC_CH_MUXPOS_PIN1_gc) подтянуть на землю
uint8_t XmegaAdc::xmega_adc_read_offset(ADC_t *adc, ADC_CH_t *adc_ch, ADC_CH_MUXPOS_t muxpos_pin)
{
    uint8_t adcb_offset;
    unsigned int offs;

    // Read and save the ADC offset using channel 0
    // ADC1 pin connected to GND
    // adc_ch->CTRL = (0 << ADC_CH_START_bp) | ADC_CH_INPUTMODE_SINGLEENDED_gc;
    // adc_ch->MUXCTRL = muxpos_pin;
    // Enable the ADC in order to read the offset
    // adc->CTRLA |= ADC_ENABLE_bm;
    // Insert a delay to allow the ADC common mode voltage to stabilize
    _delay_us(2);
    // Perform several offset measurements and store the mean value
    offs = 0;
    for (uint8_t i = 0; i < 10; i++)
    {
        // Start the AD conversion on channel 0
        adc_ch->CTRL |= 1 << ADC_CH_START_bp;
        // Wait for the AD conversion to complete
        while ((adc_ch->INTFLAGS & ADC_CH_CHIF_bm) == 0)
            ;
        // Clear the interrupt flag
        adc_ch->INTFLAGS = ADC_CH_CHIF_bm;
        // Read the offset
        offs += (uint8_t)adc_ch->RESL;
    }
    // Disable the ADC
    adc->CTRLA &= ~ADC_ENABLE_bm;
    // Store the mean value of the offset
    adcb_offset = (uint8_t)(offs / 10);
    return adcb_offset;
}
// Порядок прерывания ADC
// 1) sei(); 2) PMIC 3)INTCTRL.INTMODE-причина прерывания 4)INTCTRL.INTLVL - уровень прерывания
//
// Обработчик прерываний нужного канала
//   ISR(ADCA_CH0_vect)
//   {

// }