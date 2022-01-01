#include "gb_cpu.h"

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
		mem_write(&reg.bc.r, reg.af.hi);
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

	default:
		break;
	}
}