#ifndef _XMEGA_USART_H_
#define _XMEGA_USART_H_
#include "main.h"

class XmegaUsart
{
private:
  USART_t *usart;
  PORT_t *port_name;
  uint8_t tx_pin_bm;
  uint8_t rx_pin_bm;
  uint32_t baud;
  uint32_t cpu_hz;

public:
  XmegaUsart(USART_t *usart_, PORT_t *port_name_, uint8_t tx_pin_bm_, uint8_t rx_pin_bm_, uint32_t baud_, uint32_t cpu_hz_);

  enum xmega_usart_int_level_t
  {
    USART_INT_LVL_OFF = 0x00,
    USART_INT_LVL_LO = 0x01,
    USART_INT_LVL_MED = 0x02,
    USART_INT_LVL_HI = 0x03
  };
  void xmega_usart_init();
  void xmega_usart_rx_enable();
  void xmega_usart_rx_disable();
  void xmega_usart_tx_enable();
  void xmega_usart_tx_disable();
  void xmega_usart_set_rx_interrupt_level(xmega_usart_int_level_t level);
  void xmega_usart_set_tx_interrupt_level(xmega_usart_int_level_t level);
  void xmega_usart_set_dre_interrupt_level(xmega_usart_int_level_t level);
  bool xmega_usart_data_register_is_empty();
  bool xmega_usart_rx_is_complete();
  bool xmega_usart_tx_is_complete();
  void xmega_usart_clear_tx_complete();
  void xmega_usart_clear_rx_complete();
  void xmega_usart_put(uint8_t txdata);
  uint8_t xmega_usart_get();
  void xmega_usart_format_set(USART_CHSIZE_t charSize, USART_PMODE_t parityMode, bool twoStopBits);
  uint8_t xmega_usart_getchar();
  void xmega_usart_putchar(uint8_t c);
  void xmega_usart_set_bsel_bscale_value(uint16_t bsel, uint8_t bscale);
  bool xmega_usart_set_baudrate(uint32_t baud, uint32_t cpu_hz);
};

#endif // _XMEGA_USART_H_