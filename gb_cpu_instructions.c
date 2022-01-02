#include "gb_cpu.h"
#include "gb_cpu_instructions.h"

/*-----------------------------------
Bit	Name	Explanation
7	z		Zero flag
6	n		Subtraction flag(BCD)
5	h		Half Carry flag(BCD)
4	c		Carry flag
-----------------------------------*/

#define SET_Z (reg.af.lo |= 0x80)
#define CLEAR_Z (reg.af.lo &= ~0x80)

#define SET_N (reg.af.lo |= 0x40)
#define CLEAR_N (reg.af.lo &= ~0x40)

#define SET_H (reg.af.lo |= 0x20)
#define CLEAR_H (reg.af.lo &= ~0x20)

#define SET_C (reg.af.lo |= 0x10)
#define CLEAR_C (reg.af.lo &= ~0x10)

void ld(unsigned char* r, unsigned char value)
{
	*r = value;
}

void ld16(unsigned short* r, unsigned short value)
{
	*r = value;
}

void inc(unsigned char* r)
{
	CLEAR_N;

	// set overflow
	if ((*r)++ == 0x0f)
		SET_H;
	else
		CLEAR_H;
}

void inc16(unsigned short* r)
{
	++(*r);
}

void dec(unsigned char* r)
{
	SET_N;

	// set borrow
	if (((*r)-- & 0x10) == 0)
		SET_H;
	else
		CLEAR_H;

	if ((*r) == 0)
		SET_Z;
}

void dec16(unsigned short* r)
{
	--(*r);
}

void add(unsigned short* r, unsigned short value)
{
	CLEAR_N;

	// overflow bit 11
	if (((*r & value) & 0x0800) != 0)
		SET_H;
	else
		CLEAR_H;

	// overflow bit 15
	if (((*r & value) & 0x8000) != 0)
		SET_C;
	else
		CLEAR_C;
}

void rlc(unsigned char* r)
{
	CLEAR_Z;
	CLEAR_N;
	CLEAR_H;
	(*r) = (*r) << 1 | (*r) & 0x80;
	if (((*r) & 0x01) != 0)
		SET_C;
	else
		CLEAR_C;
}

void jump(unsigned short address)
{
	reg.pc = address;
}