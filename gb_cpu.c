#include "gb_cpu.h"
#include "gb_memory.h"
#include <SDL_stdinc.h>

void cpu_init()
{
	SDL_memset(&reg, 0, sizeof(reg));
}

void cpu_tick()
{
	unsigned char opcode = 0x05;// mem_read(&reg.pc);
	cpu_process_opcode(opcode);	
}