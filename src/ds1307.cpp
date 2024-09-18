#include "ds1307.h"
#include <avr/io.h>

// For run ds1307 in sec/registor 0x00 write 0
DS1307::DS1307(TWI_t *twi, xmega_twi_clock_t TWI_HZ, uint32_t cpu_hz) : XmegaTwi(twi, TWI_HZ, cpu_hz)
{
	xmega_twi_init(twi, TWI_HZ, cpu_hz);
}

uint8_t DS1307::bcd_to_dec(uint8_t bcd)
{
	uint8_t decimalMultiplier = 1;
	uint8_t digit;
	uint8_t dec = 0;
	while (bcd > 0)
	{
		digit = bcd & 0xF;
		dec += digit * decimalMultiplier;
		decimalMultiplier *= 10;
		bcd >>= 4;
	}
	return dec;
}
uint8_t DS1307::dec_to_bcd(uint8_t dec)
{
	uint8_t binaryShift = 0;
	uint8_t digit;
	uint8_t bcd = 0;
	while (dec > 0)
	{
		digit = dec % 10;
		bcd += (digit << binaryShift);
		binaryShift += 4;
		dec /= 10;
	}
	return bcd;
}