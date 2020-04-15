
#ifndef pdp_h
#define pdp_h

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


#define MEMSIZE 64*1024

typedef unsigned char byte;
typedef unsigned int word;
typedef word Adress;

word mem[MEMSIZE];

void b_write(Adress, byte);
byte b_read(Adress);
void w_write(Adress, word);
word w_read(Adress);


#endif 
