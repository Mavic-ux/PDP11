
#include "pdp.h"



void test() {
    //2 bytes
    Adress a1 = 4;
    byte b1 = 0xcb;
    byte b0 = 0x0a;
    word w1 = 0xcb0a;
    w_write(a1, w1);

    word b0res = b_read(a1);

    word b1res = b_read(a1 + 1);

    printf("ww/br \t %04x = %02hhx%02hhx\n", w1, b1res, b0res);
   
    assert(b0 == b0res);
    assert(b1 == b1res);
}

int main()
{
    test(); 

    return 0;
}


