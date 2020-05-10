
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

#define pc reg[7]

void b_write(Adress, byte);
byte b_read(Adress);
void w_write(Adress, word);
word w_read(Adress);

void do_MOV();
void do_ADD();
void do_HALT();
void do_CLR();
void do_SOB();


void trace (const char *  , ...);

void load_file(const char* file);

void NZVC();

void get_flag();

void run();

void print_reg();

#endif 
