#include "gb_memory.h"
#include <SDL_assert.h>

unsigned char g_memory[0xffff];

unsigned char mem_read(unsigned short* pc)
{
	(*pc)++;
	return *pc;
}

unsigned short mem_read16(unsigned short* pc)
{
	unsigned short ret = 0;
	unsigned char lsb = mem_read(pc);
	unsigned char msb = mem_read(pc);

	ret = (msb << 4) | (0x0f & lsb);

	return ret;
}

void mem_write(unsigned short* r, unsigned char value)
{
	SDL_assert(*r < 0xffff, "Invalid memory location");
	g_memory[*r] = value;
}