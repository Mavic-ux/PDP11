
#include "pdp.h"



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

byte b_read(Adress a)
{
    byte b;
    if (a % 2 == 0)
        b = mem[a] & 0xFF;
    else
    {
        word w = mem[a - 1];
        b = w >> 8 & 0xFF;
    }
    
    return b;
}

void b_write(Adress a, byte b)
{
    if (a % 2 == 0)
        mem[a] = (word)b;
    else
    {
        mem[a - 1] |= (word)(b << 8);
    }
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
    p = fopen(filename, "rb");

    Adress adr = 01000;
    unsigned int n = 0;
    byte b = 0;

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



void print_reg()
{
    for(int i = 0; i < 8; i++)
    {
        trace("R%d:%06o ", i, reg[i]);
    }
    trace("\n");
   
}
