#include "gb_cpu.h"
#include "gb_memory.h"
#include <SDL_stdinc.h>

void cpu_init()
{
	SDL_memset(&reg, 0, sizeof(reg));

/*
* https://bgb.bircd.org/pandocs.htm#powerupsequence
* AF=$01B0
* BC=$0013
* DE=$00D8
* HL=$014D
* Stack Pointer=$FFFE
*/

	reg.af.r = 0x01b0;
	reg.bc.r = 0x0013;
	reg.de.r = 0x00d8;
	reg.hl.r = 0x014d;
	reg.sp = 0xfffe;
	reg.pc = 0x0100;
}

void cpu_tick()
{
	unsigned char opcode = mem_read(&reg.pc);
	cpu_process_opcode(opcode);
}