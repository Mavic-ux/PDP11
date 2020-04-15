
#include "pdp.h"

void w_write(Adress a, word w)
{
    mem[a] = w;
}

word w_read(Adress a)
{
    return mem[a];
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

