
#ifndef pdp_h
#define pdp_h

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>

#define MEMSIZE 64*1024

typedef unsigned char byte;
typedef unsigned int word;
typedef word Adress;

word mem[MEMSIZE];

word reg[8];
#define pc reg[7]

void b_write(Adress, byte);
byte b_read(Adress);
void w_write(Adress, word);
word w_read(Adress);

void trace (const char *  , ...);

void load_file(const char* file);


#endif 
