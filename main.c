
#include "pdp.h"



int main(int argc, char * argv[])
{
    if ( argc == 1)
    {
        trace("Usage: ./a.out [listening file]: \n");
    }
    else 
    {
        load_file(argv[1]);
        trace("File %s opened\n", argv[1]);
        run();
    }  
     
    return 0;
}


