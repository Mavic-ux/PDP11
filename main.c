
#include "pdp.h"



/*..void test() {
    //2 bytes
    word w1 = 0xcb0a;
    w_write(a1, w1);

    word b0res = b_read(a1);

    word b1res = b_read(a1 + 1);

    printf("ww/br \t %04x = %02hhx%02hhx\n", w1, b1res, b0res);
   
    assert(b0 == b0res);
    assert(b1 == b1res);
}*/

int main(int argc, char * argv[])
{
    if ( argc == 1)
    {
        printf("User session:\n");
    }
    else 
    {
        load_file(argv[1]);
        printf(" File %s opened\n", argv[1]);
    }        
    return 0;
}



