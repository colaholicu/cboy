#include "gb_cpu.h"
#include "gb_cpu_instructions.h"
#include "gb_memory.h"

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

void ld(unsigned char* r, const unsigned char value)
{
	*r = value;
}

void ld16(unsigned short* r, const unsigned short value)
{
	*r = value;
}

void add(unsigned char* r, const unsigned char value)
{
	CLEAR_N;

	const unsigned char result = *r + value;
	// overflow bit 3
	if ((*r & 0x08) > (result & 0x08))
		SET_H;
	else
		CLEAR_H;

	// overflow bit 7
	if ((*r & 0x80) > (result & 0x80))
		SET_C;
	else
		CLEAR_C;

	if (result == 0)
		SET_Z;

	*r = result;
}

void add16(unsigned short* r, const unsigned short value)
{
	CLEAR_N;

	const unsigned short result = *r + value;
	// overflow bit 11
	if ((*r & 0x0800) > (result & 0x0800))
		SET_H;
	else
		CLEAR_H;

	// overflow bit 15
	if ((*r & 0x8000) > (result & 0x8000))
		SET_C;
	else
		CLEAR_C;

	*r = result;
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

void sub(unsigned char* r, const unsigned char value)
{
	SET_N;

	const unsigned char result = *r - value;
	// borrow bit 4
	if ((*r & 0x10) >= (result & 0x10))
		SET_H;
	else
		CLEAR_H;

	// borrow bit 8
	if ((*r & 0x80) >= (result & 0x80))
		SET_C;
	else
		CLEAR_C;

	if (result == 0)
		SET_Z;

	*r = result;
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

void jump(const unsigned short address)
{
	reg.pc = address;
}

void set_flags(const unsigned char flags)
{
	reg.af.lo = flags;
}

void push(const unsigned short r)
{
	mem_write16(reg.sp, r);
	reg.sp -= 2;
}

void pop(unsigned short* r)
{
	*r = (0x00ff & (mem_read_raw(reg.sp++)) | (mem_read_raw(reg.sp++) << 8) & 0xff00);
}