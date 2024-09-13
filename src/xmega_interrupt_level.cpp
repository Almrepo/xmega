#include "xmega_interrupt_level.h"

XmegaIntLvl::XmegaIntLvl(xmega_int_lvl_t int_lvl)
{
    switch (int_lvl)
    {
    case 0:
        XmegaIntLvl::xmega_int_all_lvl_enable();
        break;
    case 1:
        XmegaIntLvl::xmega_int_lo_lvl_enable();
        break;
    case 2:
        XmegaIntLvl::xmega_int_med_lvl_enable();
        break;
    case 3:
        XmegaIntLvl::xmega_int_hi_lvl_enable();
        break;
    }
}

void XmegaIntLvl::xmega_int_all_lvl_enable()
{
    PMIC.CTRL = PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm;
}

void XmegaIntLvl::xmega_int_hi_lvl_enable()
{
    PMIC.CTRL = PMIC_HILVLEN_bm;
}
void XmegaIntLvl::xmega_int_med_lvl_enable()
{
    PMIC.CTRL = PMIC_MEDLVLEN_bm;
}
void XmegaIntLvl::xmega_int_lo_lvl_enable()
{
    PMIC.CTRL = PMIC_LOLVLEN_bm;
}
void XmegaIntLvl::xmega_int_all_lvl_disable()
{
    PMIC.CTRL &= ~(PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm);
}
void XmegaIntLvl::xmega_int_hi_lvl_disable()
{
    PMIC.CTRL &= ~(PMIC_HILVLEN_bm);
}
void XmegaIntLvl::xmega_int_med_lvl_disable()
{
    PMIC.CTRL &= ~(PMIC_MEDLVLEN_bm);
}
void XmegaIntLvl::xmega_int_lo_lvl_disable()
{
    PMIC.CTRL &= ~(PMIC_LOLVLEN_bm);
}