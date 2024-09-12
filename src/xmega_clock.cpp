
#include "xmega_clock.h"

// Выбор типа генератора (bool os) 0- внутренний (2 MHz или 32 MHz), 1 - внешний (16 MHz) и частоты (cpu_hz). Частоту (cpu_hz) вводить без '0'
XmegaClock::XmegaClock(xmega_type_os_t t_os, xmega_os_hz_t cpu_hz)
{

   switch (t_os)
   {
   case 0:
      switch (cpu_hz)
      {
      case 2:
         setInternalClockTo2MHz();
         break;
      case 32:
         setInternalClockTo32MHz();
         break;
      }
      break;
   case 1:
      setExternalClockTo16MHz();
      break;
   }
}

// Настройка внутреннего генератора на 32 MHz
void XmegaClock::setInternalClockTo32MHz()
{
   // CCP = CCP_IOREG_gc; // disable register security for oscillator update
   OSC.CTRL = OSC_RC32MEN_bm; // enable 32MHz oscillator
   while (!(OSC.STATUS & OSC_RC32MRDY_bm))
      ;                             // wait for oscillator to be ready
   CCP = CCP_IOREG_gc;              // disable register security for clock update
   CLK.CTRL = CLK_SCLKSEL_RC32M_gc; // switch to 32MHz clock
}

// Настройка внутреннего тактовогогенератора на 2 MHz
void XmegaClock::setInternalClockTo2MHz()
{
   // CCP = CCP_IOREG_gc;
   OSC.CTRL = OSC_RC2MEN_bm; // enable 2 MHz oscillator
   while (!(OSC.STATUS & OSC_RC2MRDY_bm))
      ;
   CCP = CCP_IOREG_gc;
   CLK.CTRL = CLK_SCLKSEL_RC2M_gc;
}

// Настройка внешнего тактового генератора 16MHz
void XmegaClock::setExternalClockTo16MHz()
{
   OSC_XOSCCTRL = OSC_FRQRANGE_12TO16_gc | OSC_XOSCSEL_XTAL_256CLK_gc; // параметры кварца
   OSC_CTRL = OSC_XOSCEN_bm;                                           // разрешаем работу внешнего кварца
   while (!(OSC_STATUS & OSC_XOSCRDY_bm))
      ;                            // Ожидание готовности тактового генератора
   CCP = CCP_IOREG_gc;             // Разрешение записи в защищённый регистр
   CLK_CTRL = CLK_SCLKSEL_XOSC_gc; // Подключение к тактовому генератору
}
