#ifndef GB_MEMORY_H
#define GB_MEMORY_H

// read directly from an address without incrementing the program counter
unsigned char mem_read_raw(const unsigned short address);

// read the byte pointed by the program counter and increment it afterwards
unsigned char mem_read();
// read 2 consecutive bytes pointed by the program counter and incrememnt it accordingly
unsigned short mem_read16();

// write a byte at an address
void mem_write(const unsigned short, const unsigned char);
// write 2 bytes at an address
void mem_write16(const unsigned short, const unsigned short);

void init_memory();
void load_file(struct FILE* f);

#endif