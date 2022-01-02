#include "gb_memory.h"
#include <SDL_assert.h>
#include <stdio.h>

unsigned char g_memory[0xffff + 1];

void init_memory()
{
	g_memory[0xff05] = 0x00; // TIMA
	g_memory[0xff06] = 0x00; // TMA
	g_memory[0xff07] = 0x00; // TAC
	g_memory[0xff10] = 0x80; // NR10
	g_memory[0xff11] = 0xbf; // NR11
	g_memory[0xff12] = 0xf3; // NR12
	g_memory[0xff14] = 0xbf; // NR14
	g_memory[0xff16] = 0x3f; // NR21
	g_memory[0xff17] = 0x00; // NR22
	g_memory[0xff19] = 0xbf; // NR24
	g_memory[0xff1a] = 0x7f; // NR30
	g_memory[0xff1b] = 0xff; // NR31
	g_memory[0xff1c] = 0x9f; // NR32
	g_memory[0xff1e] = 0xbf; // NR33
	g_memory[0xff20] = 0xff; // NR41
	g_memory[0xff21] = 0x00; // NR42
	g_memory[0xff22] = 0x00; // NR43
	g_memory[0xff23] = 0xbf; // NR30
	g_memory[0xff24] = 0x77; // NR50
	g_memory[0xff25] = 0xf3; // NR51
	g_memory[0xff26] = 0xf1; // - GB, 0xF0 - SGB; NR52
	g_memory[0xff40] = 0x91; // LCDC
	g_memory[0xff42] = 0x00; // SCY
	g_memory[0xff43] = 0x00; // SCX
	g_memory[0xff45] = 0x00; // LYC
	g_memory[0xff47] = 0xfc; // BGP
	g_memory[0xff48] = 0xff; // OBP0
	g_memory[0xff49] = 0xff; // OBP1
	g_memory[0xff4a] = 0x00; // WY
	g_memory[0xff4b] = 0x00; // WX
	g_memory[0xffff] = 0x00; // IE
}

unsigned char mem_read(unsigned short* pc)
{
	SDL_assert(*pc < 0xfffe);
	return g_memory[(*pc)++];
}

unsigned short mem_read16(unsigned short* pc)
{
	unsigned short ret = 0;
	unsigned char lsb = mem_read(pc);
	unsigned char msb = mem_read(pc);

	ret = (0xff00 & (msb << 8)) | (0x00ff & lsb);

	return ret;
}

void mem_write(unsigned short address, unsigned char value)
{
	if (address != 0xffff) // exception for IME flag
		SDL_assert(address < 0xfffe); // overflow
	SDL_assert(address >= 0x8000); // read-only data
	g_memory[address] = value;
}

void mem_write16(unsigned short address, unsigned short value)
{
	SDL_assert(address < 0xfffe); // overflow
	SDL_assert(address >= 0x8000); // read-only data
	g_memory[address] = value;
}

void load_file(FILE* f)
{
	fseek(f, 0, SEEK_END);
	long buffer_size = ftell(f);
	SDL_assert(buffer_size <= 0x8000);
	rewind(f);
	fread_s(&g_memory, buffer_size, 1, buffer_size, f);
}