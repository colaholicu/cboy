#ifndef GB_CPU_INSTRUCTIONS_H
#define GB_CPU_INSTRUCTIONS_H

void ld(unsigned char* r, unsigned char value);
void ld16(unsigned short* r, unsigned short value);

void rlc(unsigned char* r);

void add(unsigned short* r, unsigned short value);
void inc(unsigned char* r);
void inc16(unsigned short* r);
void dec(unsigned char* r);
void dec16(unsigned short* r);

void jump(unsigned short address);

#endif