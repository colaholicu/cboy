#include "gb_cpu.h"
#include "gb_cpu_instructions.h"
#include "gb_memory.h"
#include <SDL_assert.h>

void cpu_process_opcode(unsigned char op_code)
{
	switch (op_code)
	{
	case 0x0:
		return;

	case 0x01:
		ld16(&reg.bc.r, mem_read16(&reg.pc));
		break;

	case 0x02:
		mem_write(reg.bc.r, reg.af.hi);
		break;

	case 0x03:
		inc16(&reg.bc.r);
		break;

	case 0x04:
		inc(&reg.bc.hi);
		break;

	case 0x05:
		dec(&reg.bc.hi);
		break;

	case 0x06:
		ld(&reg.bc.hi, mem_read(&reg.pc));
		break;

	case 0x07:
		rlc(&reg.af.hi);
		break;

	case 0x08:
	{
		unsigned short address = mem_read16(&reg.pc);
		mem_write16(address, reg.sp);
		break;
	}

	case 0x09:
		add(&reg.hl.r, reg.bc.r);
		break;

	case 0xc3:
	{
		unsigned short address = mem_read16(&reg.pc);
		jp(address);
		break;
	}

	case 0xf3:
		mem_write(0xffff, 0); // IME = 0
		break;

	case 0xfb:
		mem_write(0xffff, 1); // IME = 1
		break;

	default:
		SDL_assert(0); // invalid opcode
		break;
	}
}