
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
void trace (const char * fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);

}
void load_file(const char* filename)
{
    FILE * p= NULL;
    p = fopen(filename, "rb");
    Adress a = 0;
    word num = 0;
    byte b = 0;
    if (p == NULL)
    {
        perror(filename);
        printf("File opening error. \n");
        exit(1);
    }
   /*while(fscanf(p, "%x%x", &a, &num) ....)
    {
       ... 
    
    }/*

    fclose(p);
}
