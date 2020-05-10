
#include "pdp.h"
word mem[MEMSIZE] = {};
word reg[8] = {};

void w_write(Adress a, word w)
{
    if(a < 8)
        reg[a] = w;

    else
    {
        mem[a + 1] = (byte)(w >> 8);
        mem[a] = (byte)w;
       
    }


}

word w_read(Adress a)
{
    word w = 0;

    if(a < 8)
        w = reg[a];
    else
    {
        w = ((word)mem[a + 1]) << 8;
        w |= (word)mem[a];
    }
    
    return w;


}

byte b_read(Adress adr)
{
    byte b = 0;
    if (adr < 8)
        b = (byte)reg[adr];
    else
        b = mem[adr];
    
    return b;
}

void b_write(Adress adr, byte b)
{
    if (adr < 8)
    {
        if( b & 0x80)
            reg[adr] = 0xFF00;
        else 
            reg[adr] = 0x0000;
        reg[adr] |= (word)b;
    }
    else
        mem[adr] = b;
}

void trace (const char * fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);

}

void load_file(const char* filename)
{
    FILE* p;
    p = fopen(filename, "r");

    Adress adr = 01000;
    word n = 0;
    byte b = 0;
    
    if (p == NULL)
    {
        perror(filename);
        trace("File opening error.\n");
        exit(1);

    }
    while(fscanf(p, "%04x%04x", &adr, &n) == 2)
    {
        for (unsigned int i = 0; i < n; i++)
        {
            fscanf(p, "%02hhx ", &b);
            b_write(adr, b);
            adr++;
        }

    }

    fclose(p);
}

void print_halt()
{
    for(int i = 0; i < 4; i++)
    {
        trace("R%d:%06o ", i, reg[i]);
    }
    trace("\n");
    
    for(int i = 4; i < 8; i++)
    {
        trace("R%d:%06o ", i, reg[i]);
    }
    trace("\n");


}



void print_reg()
{
    for(int i = 0; i < 8; i++)
    {
        trace("R%d:%06o ", i, reg[i]);
    }
    trace("\n");
   
}
