#ifndef GB_MEMORY_H
#define GB_MEMORY_H

unsigned char mem_read(unsigned short*);
unsigned short mem_read16(unsigned short*);

void mem_write(unsigned short*, unsigned char);

#endif