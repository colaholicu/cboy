#ifndef GB_CPU_INSTRUCTIONS_H
#define GB_CPU_INSTRUCTIONS_H

void ld(unsigned char* r, const unsigned char value);
void ld16(unsigned short* r, const unsigned short value);

void rlc(unsigned char* r);

void add(unsigned char* r, const unsigned char);
void add16(unsigned short* r, const unsigned short value);
void inc(unsigned char* r);
void inc16(unsigned short* r);
void sub(unsigned char* r, const unsigned char);
void dec(unsigned char* r);
void dec16(unsigned short* r);

void jump(const unsigned short address);

void set_flags(const unsigned char flags);

void push(const unsigned short r);
void pop(unsigned short* r);

#endif