#include "gb_cpu.h"
#include "gb_cpu_instructions.h"
#include "gb_memory.h"
#include <SDL_assert.h>


// references
// http://marc.rawer.de/Gameboy/Docs/GBCPUman.pdf

void cpu_process_opcode(unsigned char op_code)
{
	switch (op_code)
	{
	case 0x0:
		return;

	// LD nn, n
	case 0x06:
		ld(&reg.bc.hi, mem_read());
		break;
	case 0x0e:
		ld(&reg.bc.lo, mem_read());
		break;
	case 0x16:
		ld(&reg.de.hi, mem_read());
		break;
	case 0x1e:
		ld(&reg.de.lo, mem_read());
		break;
	case 0x26:
		ld(&reg.hl.hi, mem_read());
		break;
	case 0x2e:
		ld(&reg.hl.lo, mem_read());
		break;

	// LD r1, r2
#pragma region "LD A, r2 - opcodes: 0x78 to 0x7f"
	case 0x7f:
		ld(&reg.af.hi, reg.af.hi);
		break;
	case 0x78:
		ld(&reg.af.hi, reg.bc.hi);
		break;
	case 0x79:
		ld(&reg.af.hi, reg.bc.lo);
		break;
	case 0x7a:
		ld(&reg.af.hi, reg.de.hi);
		break;
	case 0x7b:
		ld(&reg.af.hi, reg.de.lo);
		break;
	case 0x7c:
		ld(&reg.af.hi, reg.hl.hi);
		break;
	case 0x7d:
		ld(&reg.af.hi, reg.hl.lo);
		break;
	case 0x7e:
		ld(&reg.af.hi, mem_read_raw(reg.hl.r));
		break;
#pragma endregion

#pragma region "LD B, r2 - opcodes: 0x40 to 0x46"
	case 0x40:
		ld(&reg.bc.hi, reg.bc.hi);
		break;
	case 0x41:
		ld(&reg.bc.hi, reg.bc.lo);
		break;
	case 0x42:
		ld(&reg.bc.hi, reg.de.hi);
		break;
	case 0x43:
		ld(&reg.bc.hi, reg.de.lo);
		break;
	case 0x44:
		ld(&reg.bc.hi, reg.hl.hi);
		break;
	case 0x45:
		ld(&reg.bc.hi, reg.hl.lo);
		break;
	case 0x46:
		ld(&reg.bc.hi, mem_read_raw(reg.hl.r));
		break;
#pragma endregion

#pragma region "LD C, r2 - opcodes: 0x48 to 0x4e"
	case 0x48:
		ld(&reg.bc.lo, reg.bc.hi);
		break;
	case 0x49:
		ld(&reg.bc.lo, reg.bc.lo);
		break;
	case 0x4a:
		ld(&reg.bc.lo, reg.de.hi);
		break;
	case 0x4b:
		ld(&reg.bc.lo, reg.de.lo);
		break;
	case 0x4c:
		ld(&reg.bc.lo, reg.hl.hi);
		break;
	case 0x4d:
		ld(&reg.bc.lo, reg.hl.lo);
		break;
	case 0x4e:
		ld(&reg.bc.lo, mem_read_raw(reg.hl.r));
		break;
#pragma endregion

#pragma region "LD D, r2 - opcodes: 0x50 to 0x56"
	case 0x50:
		ld(&reg.de.hi, reg.bc.hi);
		break;
	case 0x51:
		ld(&reg.de.hi, reg.bc.lo);
		break;
	case 0x52:
		ld(&reg.de.hi, reg.de.hi);
		break;
	case 0x53:
		ld(&reg.de.hi, reg.de.lo);
		break;
	case 0x54:
		ld(&reg.de.hi, reg.hl.hi);
		break;
	case 0x55:
		ld(&reg.de.hi, reg.hl.lo);
		break;
	case 0x56:
		ld(&reg.de.hi, mem_read_raw(reg.hl.r));
		break;
#pragma endregion

#pragma region "LD E, r2 - opcodes: 0x58 to 0x5e"
	case 0x58:
		ld(&reg.de.lo, reg.bc.hi);
		break;
	case 0x59:
		ld(&reg.de.lo, reg.bc.lo);
		break;
	case 0x5a:
		ld(&reg.de.lo, reg.de.hi);
		break;
	case 0x5b:
		ld(&reg.de.lo, reg.de.lo);
		break;
	case 0x5c:
		ld(&reg.de.lo, reg.hl.hi);
		break;
	case 0x5d:
		ld(&reg.de.lo, reg.hl.lo);
		break;
	case 0x5e:
		ld(&reg.de.lo, mem_read_raw(reg.hl.r));
		break;
#pragma endregion

#pragma region "LD H, r2 - opcodes: 0x60 to 0x66"
	case 0x60:
		ld(&reg.hl.hi, reg.bc.hi);
		break;
	case 0x61:
		ld(&reg.hl.hi, reg.bc.lo);
		break;
	case 0x62:
		ld(&reg.hl.hi, reg.de.hi);
		break;
	case 0x63:
		ld(&reg.hl.hi, reg.de.lo);
		break;
	case 0x64:
		ld(&reg.hl.hi, reg.hl.hi);
		break;
	case 0x65:
		ld(&reg.hl.hi, reg.hl.lo);
		break;
	case 0x66:
		ld(&reg.hl.hi, mem_read_raw(reg.hl.r));
		break;
#pragma endregion

#pragma region "LD L, r2 - opcodes: 0x68 to 0x6e"
	case 0x68:
		ld(&reg.hl.lo, reg.bc.hi);
		break;
	case 0x69:
		ld(&reg.hl.lo, reg.bc.lo);
		break;
	case 0x6a:
		ld(&reg.hl.lo, reg.de.hi);
		break;
	case 0x6b:
		ld(&reg.hl.lo, reg.de.lo);
		break;
	case 0x6c:
		ld(&reg.hl.lo, reg.hl.hi);
		break;
	case 0x6d:
		ld(&reg.hl.lo, reg.hl.lo);
		break;
	case 0x6e:
		ld(&reg.hl.lo, mem_read_raw(reg.hl.r));
		break;
#pragma endregion

#pragma region "LD &(nn), r2 - opcodes: 0x70 to 0x75, 0x36"
	case 0x70:
		mem_write(reg.hl.r, reg.bc.hi);
		break;
	case 0x71:
		mem_write(reg.hl.r, reg.bc.lo);
		break;
	case 0x72:
		mem_write(reg.hl.r, reg.de.hi);
		break;
	case 0x73:
		mem_write(reg.hl.r, reg.de.lo);
		break;
	case 0x74:
		mem_write(reg.hl.r, reg.hl.hi);
		break;
	case 0x75:
		mem_write(reg.hl.r, reg.hl.lo);
		break;
	case 0x36:
		mem_write(reg.hl.r, mem_read());
		break;
#pragma endregion

	// LD A, n
	case 0x0a:
		ld(&reg.af.hi, mem_read_raw(reg.bc.r));
		break;
	case 0x1a:
		ld(&reg.af.hi, mem_read_raw(reg.de.r));
		break;
	case 0xfa:
		ld(&reg.af.hi, mem_read_raw(mem_read16()));
		break;
	case 0x3e:
		SDL_assert(0, "I have no idea what this should do");
		break;

	// LD n, A
	case 0x47:
		ld(&reg.bc.hi, reg.af.hi);
		break;
	case 0x4f:
		ld(&reg.bc.lo, reg.af.hi);
		break;
	case 0x57:
		ld(&reg.de.hi, reg.af.hi);
		break;
	case 0x5f:
		ld(&reg.de.lo, reg.af.hi);
		break;
	case 0x67:
		ld(&reg.hl.hi, reg.af.hi);
		break;
	case 0x6f:
		ld(&reg.hl.lo, reg.af.hi);
		break;
	case 0x02:
		mem_write(reg.bc.r, reg.af.hi);
		break;
	case 0x12:
		mem_write(reg.de.r, reg.af.hi);
		break;
	case 0x77:
		mem_write(reg.hl.r, reg.af.hi);
		break;
	case 0xea:
		mem_write(mem_read16(), reg.af.hi);
		break;

	// various LDs to memory from a or to A from memory
	case 0xf2:
		ld(&reg.af.hi, mem_read_raw(0xff00 | (0x00ff & reg.bc.lo)));
		break;
	case 0xe2:
		mem_write(0xff00 | (0x00ff & reg.bc.lo), reg.af.hi);
		break;
	case 0x3a:
		ld(&reg.af.hi, mem_read_raw(reg.hl.r));
		dec16(&reg.hl.r);
		break;
	case 0x32:
		mem_write(reg.hl.r, reg.af.hi);
		dec16(&reg.hl.r);
		break;
	case 0x2a:
		ld(&reg.af.hi, mem_read_raw(reg.hl.r));
		inc16(&reg.hl.r);
		break;
	case 0x22:
		mem_write(reg.hl.r, reg.af.hi);
		inc16(&reg.hl.r);
		break;
	case 0xe0:
		mem_write(0xff00 | (0x00ff & mem_read()), reg.af.hi);
		break;
	case 0xf0:
		ld(&reg.af.hi, mem_read_raw(0xff00 | (0x00ff & mem_read())));
		break;

	// LD n, nn
	case 0x01:
		ld16(&reg.bc.r, mem_read16());
		break;
	case 0x11:
		ld16(&reg.de.r, mem_read16());
		break;
	case 0x21:
		ld16(&reg.hl.r, mem_read16());
		break;
	case 0x31:
		ld16(&reg.sp, mem_read16());
		break;

	// stack related LDs
	case 0xf9:
		ld16(&reg.sp, reg.hl.r);
		break;

	case 0xf8:
		SDL_assert(0, "To be continued");
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

	case 0x07:
		rlc(&reg.af.hi);
		break;

	case 0x08:
		mem_write16(mem_read16(), reg.sp);
		break;

	case 0x09:
		add(&reg.hl.r, reg.bc.r);
		break;

	case 0xc3:
		jump(mem_read16());
		break;

	case 0xf3:
		mem_write(0xffff, 0); // IME = 0
		break;

	case 0xfb:
		mem_write(0xffff, 1); // IME = 1
		break;

	default:
		SDL_assert(0, op_code); // invalid opcode
		break;
	}
}