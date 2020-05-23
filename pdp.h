
#ifndef pdp_h
#define pdp_h

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>

#define MEMSIZE 64*1024

typedef uint8_t byte;
typedef uint16_t word;
typedef word Adress;


#define pc reg[7]
#define sp reg[6]

void b_write(Adress, byte);
byte b_read(Adress);
void w_write(Adress, word);
word w_read(Adress);

void do_MOV();
void do_ADD();
void do_HALT();
void do_CLR();
void do_SOB();
void do_BR();
void do_BEQ();

void do_unknown();


void trace (const char *  , ...);

void load_file(const char* file);;

void print_new_val();

void NZVC();

void get_flag(word p);

void run();

void print_reg();

#endif 
