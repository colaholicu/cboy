#ifndef GB_CPU_H
#define GB_CPU_H

typedef union _register16
{
	unsigned short r;
	struct {
		unsigned char hi;
		unsigned char lo;
	};
} register16;

typedef struct _gb_registers
{
	register16 af;
	register16 bc;
	register16 de;

	unsigned short sp; // stack pointer
	unsigned short pc; // program counter/pointer 
} gb_registers;

gb_registers reg;

void cpu_init();
void cpu_tick();
void cpu_process_opcode(unsigned char op_code);

// instructions
void ld(unsigned char* r, unsigned char value);
void ld16(unsigned short* r, unsigned short value);
void inc(unsigned char* r);
void inc16(unsigned short* r);
void dec(unsigned char* r);

#endif