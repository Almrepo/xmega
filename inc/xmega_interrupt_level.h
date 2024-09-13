#ifndef _XMEGA_INTERRUPT_LEVEL_H_
#define _XMEGA_INTERRUPT_LEVEL_H_
#include <interrupt.h>

class XmegaIntLvl
{
public:
    enum xmega_int_lvl_t
    {
        XMEGA_INT_LVL_ALL_EN = 0x00,
        XMEGA_INT_LVL_LO_EN = 0x01,
        XMEGA_INT_LVL_MED_EN = 0x02,
        XMEGA_INT_LVL_HI_EN = 0x03
    };
    XmegaIntLvl(xmega_int_lvl_t);
    void xmega_int_all_lvl_enable();
    void xmega_int_hi_lvl_enable();
    void xmega_int_med_lvl_enable();
    void xmega_int_lo_lvl_enable();
    void xmega_int_all_lvl_disable();
    void xmega_int_hi_lvl_disable();
    void xmega_int_med_lvl_disable();
    void xmega_int_lo_lvl_disable();
};

#endif